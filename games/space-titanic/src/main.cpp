/*
 * Copyright (c) 2020-2022 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

// Butano libraries
#include "bn_core.h"
#include "bn_log.h"
#include "bn_music.h"

#include "bn_music_actions.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "bn_rect_window_actions.h"
#include "bn_rect_window_boundaries_hbe_ptr.h"
#include "bn_sram.h"
#include "bn_math.h"
#include "bn_cstring.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

// My assets
#include "bn_sprite_items_chari.h"
#include "bn_sprite_items_ninja.h"
#include "bn_sprite_items_world.h"
#include "bn_sprite_items_buttons.h"
#include "bn_sprite_items_projectiles.h"
#include "bn_regular_bg_items_bg_carpet.h"

// My custom functions
#include "./levels.h"

#define encode_x(x) (x * 16) - 120 + 8
#define encode_y(y) (y * 16) - 80 + 8
#define resolve_x(x) ((x % 15) * 16) - 112
#define resolve_y(y) ((y / 15) * 16) - 72
#define decode(x, y) ((x + 120) / 16) + (15 * (((y + 80) / 16) % 15))
#define lerp(a, b, t) (a * (1 - t) + b * t)
#define escape(x, y) (x < -120 || x > 120 || y < -80 || y > 80)

#define T_WALL 1
#define T_HOLE 2
#define D_LEFT 1
#define D_RIGHT 2
#define D_UP 3
#define D_DOWN 4

// Custom classes
class Barrel
{
    int steps = 0;
    int x_speed = 0;
    int y_speed = 0;

public:
    bn::sprite_ptr sprite = bn::sprite_items::world.create_sprite(0, 0, 2);

    Barrel(int x, int y, int *level)
    {
        sprite.set_x(x);
        sprite.set_y(y);
        level[decode(x, y)] = 1;
    }

    void push(int x, int y, int *level)
    {
        x_speed = x;
        y_speed = y;
        level[decode(sprite.x().integer(), sprite.y().integer())] = 0;
        steps = 0;
    }

    void update(int *level)
    {
        int init_x = sprite.x().integer();
        int init_y = sprite.y().integer();
        int x_speed_prior = x_speed;
        int y_speed_prior = y_speed;

        if (x_speed != 0 || y_speed != 0)
        {
            sprite.set_x(sprite.x().integer() + x_speed);
            sprite.set_y(sprite.y().integer() + y_speed);
            steps++;
        }

        if (level[decode(
                sprite.x().integer() + (x_speed / 2) + (x_speed * 4),
                sprite.y().integer() + +(y_speed / 2) + (y_speed * 4))] == 1)
        {
            x_speed = 0;
            y_speed = 0;
            level[decode(sprite.x().integer(), sprite.y().integer())] = 1;
            if (steps == 1)
            {
                sprite.set_x(init_x);
                sprite.set_y(init_y);
            }
        }

        if (x_speed_prior != x_speed || y_speed_prior != y_speed)
        {
            bn::sound_items::box_01.play(0.5);
        }
    }
};

void chari_sound(int chari, int sound)
{
    switch (sound)
    {
    case 1:
    {
        switch (chari)
        {
        case 26:
        {
            bn::sound_items::push_jasper.play(0.5);
            break;
        }
        case 13:
        {
            bn::sound_items::push_xylia.play(0.5);
            break;
        }
        default:
            bn::sound_items::push_luna.play(0.5);
            break;
        }
        break;
    }
    default:
    {
        switch (chari)
        {
        case 26:
        {
            bn::sound_items::wah_luna.play(0.5);
            break;
        }
        case 13:
        {
            bn::sound_items::wah_xylia.play(0.5);
            break;
        }
        default:
            bn::sound_items::wah_luna.play(0.5);
            break;
        }
        break;
    }
    }
}

// Big fat global variables
int current_level = 0;
bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

int gameplay()
{
    // Set up world
    int my_level[135] = {0};
    bn::memcpy(my_level, resolve_level(current_level), sizeof(my_level));

    // Variable init
    int start_x = encode_x(7);
    int start_y = encode_y(7);
    int pros_x = start_x;
    int pros_y = start_y;
    bool gravity = false;
    int freefall = 0;
    int rotate = 0;
    int dead = 0;
    int orientation = 0;
    int chari_offset = 0 * 13;
    int notice = 0;
    int window_y = 120;
    int indicate = 0;
    int trig_offset = 0;
    int bullet_count = 0;

    bn::fixed bullet_x;
    bn::fixed bullet_y;

    // Set up vectors
    bn::vector<bn::sprite_ptr, 64> sprites_v;
    bn::vector<Barrel, 4> sprites_b;
    bn::sprite_ptr button = bn::sprite_items::buttons.create_sprite(-8 * 16, 72, 0);
    bn::regular_bg_ptr bg_carpet = bn::regular_bg_items::bg_carpet.create_bg(0, 0);
    bn::vector<bn::sprite_ptr, 32> text_sprites;

    // Entrance / exit window
    bn::rect_window external_window = bn::rect_window::external();
    external_window.set_show_bg(bg_carpet, false);
    external_window.set_show_sprites(false);
    external_window.set_boundaries(-80, -120, 80, window_y);

    // Create wall tiles
    for (int i = 0; i < 135; i++)
    {
        if (my_level[i] == 1)
        {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), my_level[i] - 1);
            sprites_v.push_back(n);
        }
        else if (my_level[i] == 2)
        {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), my_level[i] - 1);
            n.put_below();
            sprites_v.push_back(n);
        }
        else if (my_level[i] == 3)
        {
            sprites_b.push_back(Barrel(resolve_x(i), resolve_y(i), my_level));
            sprites_b.at(sprites_b.size() - 1).sprite.put_above();
        }
    }

    // Spiral
    bn::sprite_ptr spiral = bn::sprite_items::projectiles.create_sprite(0, 0, 6);
    spiral.put_below();
    spiral.set_visible(false);

    // Aim
    bn::sprite_ptr aim = bn::sprite_items::projectiles.create_sprite(0,0,7);
    aim.set_visible(false);

    // Bullet
    bn::sprite_ptr bullet = bn::sprite_items::projectiles.create_sprite(0,0,2);
    bn::sprite_animate_action<2> bullet_action = bn::create_sprite_animate_action_forever(
        bullet, 1, bn::sprite_items::projectiles.tiles_item(), 2, 3);
    bullet.set_visible(false);
    bullet.set_z_order(0);

    // Create player
    bn::sprite_ptr player = bn::sprite_items::chari.create_sprite(start_x, start_y, 1);

    bn::sprite_animate_action<4> action = bn::create_sprite_animate_action_forever(
        player, 4, bn::sprite_items::chari.tiles_item(), 0, 0, 0, 0);

    while (true)
    {
        spiral.set_visible(false);
        aim.set_visible(false);

        // Handle window
        if (window_y > -80)
        {
            window_y -= 10;
            external_window.set_boundaries(-80, -120, window_y, 120);
        }

        // Handle strope bar
        if (notice == 1 && button.x() < -7 * 16)
        {
            button.set_x(button.x() + 2);
            if (text_sprites.size() == 0)
            {
                text_generator.generate(-6 * 16, 72, "Push crate", text_sprites);
            }
        }
        else if (notice == 0 && button.x() > -8 * 16)
        {
            button.set_x(button.x() - 2);
            text_generator.generate(-6 * 16, 72, "", text_sprites);
            if (text_sprites.size() > 0)
            {
                text_sprites.clear();
            }
        }

        if (bullet.visible()) {
            if (chari_offset == 0) {
                bn::fixed proj_x = bn::degrees_cos(bullet.rotation_angle()) * 4;
                bn::fixed proj_y = -bn::degrees_sin(bullet.rotation_angle()) * 4;
                int spot = decode((bullet.x() + (proj_x)).integer(), (bullet.y() + (proj_y)).integer());

                if (my_level[spot] > 0) {

                    if (bn::abs(decode(bullet.x().integer(), bullet.y().integer()) - spot) <= 2) {
                        bullet.set_rotation_angle((540 - bullet.rotation_angle().integer()) % 360);
                        bullet_count++;
                        if (bullet_count <= 8) bn::sound_items::pew.play();
                    } else {
                        bullet.set_rotation_angle((360 - bullet.rotation_angle().integer()) % 360);
                        bullet_count++;
                        if (bullet_count <= 8) bn::sound_items::pew.play();
                    }

                    proj_x = bn::degrees_cos(bullet.rotation_angle()) * 4;
                    proj_y = -bn::degrees_sin(bullet.rotation_angle()) * 4;
                }

                bullet.set_position(
                    bullet.x() + proj_x,
                    bullet.y() + proj_y
                );

                if (bullet_count > 8) {
                    bn::sound_items::pew_die.play();
                    bullet.set_visible(false);
                }
            } else if (chari_offset == 13) {
                bullet.set_rotation_angle((bullet.rotation_angle().integer() + 1) % 360);

                if (bn::keypad::left_held()) {
                    bullet_x -= bn::fixed(0.02);
                }

                if (bn::keypad::right_held()) {
                    bullet_x += bn::fixed(0.02);
                }

                if (bn::keypad::up_held()) {
                    bullet_y -= bn::fixed(0.02);
                }

                if (bn::keypad::down_held()) {
                    bullet_y += bn::fixed(0.02);
                }

                bullet.set_position(bullet.x() + bullet_x, bullet.y() + bullet_y);
                bullet.put_above();
            }
        }

        if (indicate == 1)
        {
            switch (chari_offset)
            {
            case 13:
            {
                spiral.set_visible(true);
                spiral.set_rotation_angle((spiral.rotation_angle().integer() + 10) % 360);
                spiral.set_scale((bn::sin(trig_offset) * bn::fixed(0.5)) + bn::fixed(1.5), (bn::cos(trig_offset) * bn::fixed(0.5)) + bn::fixed(1.5));
                spiral.set_position(player.x(), player.y());
                if (spiral.rotation_angle().integer() % 65 == 0) {
                    BN_LOG(trig_offset);
                    bn::sound_items::shepard.play(0.1);
                }
                break;
            }
            default:
            {
                aim.set_visible(true);
                if (bn::keypad::up_held() || bn::keypad::left_held()) {
                    trig_offset = (trig_offset + 4) % 360;
                } else if (bn::keypad::down_held() || bn::keypad::right_held()) {
                    trig_offset = (trig_offset - 4) % 360;
                }
                if (trig_offset < 0) trig_offset = 360;
                aim.set_position(pros_x + (bn::degrees_sin(trig_offset) * bn::fixed(16)).integer(), pros_y + (bn::degrees_cos(trig_offset) * bn::fixed(16)).integer());
                aim.set_rotation_angle((trig_offset + 90) % 360);
                break;
            }
            }
        }

        // Handle barrels
        notice = 0;
        for (int i = 0; i < sprites_b.size(); i++)
        {
            if (sprites_b.at(i).sprite.y().integer() == pros_y)
            {
                if (sprites_b.at(i).sprite.x().integer() == pros_x - 16)
                {
                    notice = 1;
                    if (bn::keypad::a_pressed())
                    {
                        sprites_b.at(i).push(-2, 0, my_level);
                        freefall = D_RIGHT;
                        bn::sound_items::box_01.play(0.5);
                        chari_sound(chari_offset, 1);
                    }
                }
                else if (sprites_b.at(i).sprite.x().integer() == pros_x + 16)
                {
                    notice = 1;
                    if (bn::keypad::a_pressed())
                    {
                        sprites_b.at(i).push(2, 0, my_level);
                        freefall = D_LEFT;
                        bn::sound_items::box_01.play(0.5);
                        chari_sound(chari_offset, 1);
                    }
                }
            }
            else if (sprites_b.at(i).sprite.x().integer() == pros_x)
            {
                if (sprites_b.at(i).sprite.y().integer() == pros_y - 16)
                {
                    notice = 1;
                    if (bn::keypad::a_pressed())
                    {
                        sprites_b.at(i).push(0, -2, my_level);
                        freefall = D_DOWN;
                        bn::sound_items::box_01.play(0.5);
                        chari_sound(chari_offset, 1);
                    }
                }
                else if (sprites_b.at(i).sprite.y().integer() == pros_y + 16)
                {
                    notice = 1;
                    if (bn::keypad::a_pressed())
                    {
                        sprites_b.at(i).push(0, 2, my_level);
                        freefall = D_UP;
                        bn::sound_items::box_01.play(0.5);
                        chari_sound(chari_offset, 1);
                    }
                }
            }

            sprites_b.at(i).update(my_level);

            // Delete if it leaves the world
            if (escape(sprites_b.at(i).sprite.x().integer(), sprites_b.at(i).sprite.y().integer()))
            {
                sprites_b.erase(&sprites_b.at(i));
            }
        }

        // Handle player rotation
        if (rotate < player.rotation_angle())
        {
            player.set_rotation_angle(player.rotation_angle() - 10);
        }
        else if (rotate > player.rotation_angle())
        {
            player.set_rotation_angle(player.rotation_angle() + 10);
        }

        // If ready for next move
        if (player.x() == pros_x && player.y() == pros_y)
        {

            // Swap characters
            if (bn::keypad::l_pressed() || bn::keypad::r_pressed()) {
                indicate = 0;
                chari_offset = (chari_offset + 13) % 39;
            }

            // If on black hole
            if (my_level[decode(pros_x, pros_y)] == 2)
            {
                if (dead != 1)
                {
                    chari_sound(chari_offset, 0);
                }
                dead = 1;
            }

            if (dead == 0)
            {
                // No thingy
                if (indicate == 0)
                {
                    // Activate thingy
                    if (bn::keypad::b_pressed()) {
                        indicate = 1;
                        if (chari_offset == 0) {
                            bullet_action = bn::create_sprite_animate_action_forever(
                                bullet, 1, bn::sprite_items::projectiles.tiles_item(), 2, 3);
                            bn::sound_items::push_luna.play(0.5);
                            bullet_count = 0;
                        } else if (chari_offset == 13) {
                            bullet_action = bn::create_sprite_animate_action_forever(
                                bullet, 1, bn::sprite_items::projectiles.tiles_item(), 0, 1);
                            bullet_count = 0;
                            bullet.set_visible(true);
                            bullet.set_position(pros_x, pros_y);
                        }
                    }

                    // When gravity is activated
                    if (gravity)
                    {

                        int held_key = 0;

                        if (bn::keypad::left_held())
                        {
                            held_key = 1;
                            if (my_level[decode(pros_x - 16, pros_y)] != 1)
                            {
                                pros_x -= 16;
                            }
                        }

                        if (bn::keypad::right_held())
                        {
                            held_key = 2;
                            if (my_level[decode(pros_x + 16, pros_y)] != 1)
                            {
                                pros_x += 16;
                            }
                        }

                        if (bn::keypad::up_held())
                        {
                            held_key = 3;
                            if (my_level[decode(pros_x, pros_y - 16)] != 1)
                            {
                                pros_y -= 16;
                            }
                        }

                        if (bn::keypad::down_held())
                        {
                            held_key = 4;
                            if (my_level[decode(pros_x, pros_y + 16)] != 1)
                            {
                                pros_y += 16;
                            }
                        }

                        if (held_key == 0)
                        {
                            if (orientation == 1)
                            {
                                action = bn::create_sprite_animate_action_forever(
                                    player, 4, bn::sprite_items::chari.tiles_item(), 3 + chari_offset, 3 + chari_offset, 3 + chari_offset, 3 + chari_offset);
                                orientation = 0;
                                player.set_horizontal_flip(true);
                            }
                            else if (orientation == 2)
                            {
                                action = bn::create_sprite_animate_action_forever(
                                    player, 4, bn::sprite_items::chari.tiles_item(), 3 + chari_offset, 3 + chari_offset, 3 + chari_offset, 3 + chari_offset);
                                orientation = 0;
                                player.set_horizontal_flip(false);
                            }
                            else if (orientation == 3)
                            {
                                action = bn::create_sprite_animate_action_forever(
                                    player, 4, bn::sprite_items::chari.tiles_item(), 10 + chari_offset, 10 + chari_offset, 10 + chari_offset, 10 + chari_offset);
                                orientation = 0;
                                player.set_horizontal_flip(false);
                            }
                            else if (orientation == 4)
                            {
                                action = bn::create_sprite_animate_action_forever(
                                    player, 4, bn::sprite_items::chari.tiles_item(), 0 + chari_offset, 0 + chari_offset, 0 + chari_offset, 0 + chari_offset);
                                orientation = 0;
                                player.set_horizontal_flip(false);
                            }
                        }

                        // No gravity, but stable
                    }
                    else if (freefall == 0)
                    {

                        int is_held = 0;

                        if (bn::keypad::left_held())
                        {
                            is_held = 1;
                            if (my_level[decode(pros_x - 16, pros_y)] != 1)
                            {
                                if (my_level[decode(pros_x - 16, pros_y - 16)] == 1)
                                {
                                    rotate = 270;
                                    pros_x -= 16;
                                }
                                else if (my_level[decode(pros_x - 16, pros_y + 16)] == 1)
                                {
                                    rotate = 90;
                                    pros_x -= 16;
                                }
                                else
                                {
                                    freefall = D_LEFT;
                                    rotate = 0;
                                    chari_sound(chari_offset, 1);
                                }
                            }
                        }

                        if (bn::keypad::right_held())
                        {
                            is_held = 2;
                            if (my_level[decode(pros_x + 16, pros_y)] != 1)
                            {
                                if (my_level[decode(pros_x + 16, pros_y - 16)] == 1)
                                {
                                    rotate = 270;
                                    pros_x += 16;
                                }
                                else if (my_level[decode(pros_x + 16, pros_y + 16)] == 1)
                                {
                                    rotate = 90;
                                    pros_x += 16;
                                }
                                else
                                {
                                    freefall = D_RIGHT;
                                    rotate = 180;
                                    chari_sound(chari_offset, 1);
                                }
                            }
                        }

                        if (bn::keypad::up_held())
                        {
                            is_held = 3;
                            if (my_level[decode(pros_x, pros_y - 16)] != 1)
                            {
                                if (my_level[decode(pros_x + 16, pros_y - 16)] == 1)
                                {
                                    pros_y -= 16;
                                    rotate = 180;
                                }
                                else if (my_level[decode(pros_x - 16, pros_y - 16)] == 1)
                                {
                                    pros_y -= 16;
                                    rotate = 0;
                                }
                                else
                                {
                                    freefall = D_UP;
                                    rotate = 270;
                                    chari_sound(chari_offset, 1);
                                }
                            }
                        }

                        if (bn::keypad::down_held())
                        {
                            is_held = 4;
                            if (my_level[decode(pros_x, pros_y + 16)] != 1)
                            {
                                if (my_level[decode(pros_x + 16, pros_y + 16)] == 1)
                                {
                                    pros_y += 16;
                                    rotate = 180;
                                }
                                else if (my_level[decode(pros_x - 16, pros_y + 16)] == 1)
                                {
                                    pros_y += 16;
                                    rotate = 0;
                                }
                                else
                                {
                                    freefall = D_DOWN;
                                    rotate = 90;
                                    chari_sound(chari_offset, 1);
                                }
                            }
                        }

                        if (is_held == 0)
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 6 + chari_offset, 6 + chari_offset, 6 + chari_offset, 6 + chari_offset);
                        }
                        orientation = 0;
                    }
                    else if (freefall == D_LEFT)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 8 + chari_offset, 8 + chari_offset, 8 + chari_offset, 8 + chari_offset);

                        if (pros_x == player.x())
                        {
                            if (my_level[decode(pros_x - 16, pros_y)] != 1)
                            {
                                pros_x -= 16;
                            }
                            else
                            {
                                freefall = 0;
                                rotate = 0;
                                bn::sound_items::box_01.play(0.5);
                            }
                        }
                    }
                    else if (freefall == D_RIGHT)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 8 + chari_offset, 8 + chari_offset, 8 + chari_offset, 8 + chari_offset);

                        if (pros_x == player.x())
                        {
                            if (my_level[decode(pros_x + 16, pros_y)] != 1)
                            {
                                pros_x += 16;
                            }
                            else
                            {
                                freefall = 0;
                                rotate = 180;
                                bn::sound_items::box_01.play(0.5);
                            }
                        }
                    }
                    else if (freefall == D_UP)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 8 + chari_offset, 8 + chari_offset, 8 + chari_offset, 8 + chari_offset);

                        if (pros_y == player.y())
                        {
                            if (my_level[decode(pros_x, pros_y - 16)] != 1)
                            {
                                pros_y -= 16;
                            }
                            else
                            {
                                freefall = 0;
                                rotate = 270;
                                bn::sound_items::box_01.play(0.5);
                            }
                        }
                    }
                    else if (freefall == D_DOWN)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 8 + chari_offset, 8 + chari_offset, 8 + chari_offset, 8 + chari_offset);

                        if (pros_y == player.y())
                        {
                            if (my_level[decode(pros_x, pros_y + 16)] != 1)
                            {
                                pros_y += 16;
                            }
                            else
                            {
                                freefall = 0;
                                rotate = 90;
                                bn::sound_items::box_01.play(0.5);
                            }
                        }
                    }
                
                } else if (indicate == 1) {
                    // Activate thingy
                    if (bn::keypad::b_pressed()) {
                        indicate = 0;
                        if (chari_offset == 0) {
                            bullet.set_visible(true);
                            bullet.set_position(pros_x, pros_y);
                            bullet.set_rotation_angle((aim.rotation_angle().integer() + 180) % 360);
                            bn::sound_items::pew.play();
                        } else if (chari_offset == 13) {
                            bullet.set_visible(false);
                            bullet.set_position(pros_x, pros_y);
                        }
                    }

                    switch (chari_offset) {
                        case 13: {
                            rotate = 0;
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 47, 47, 47, 47);
                            break;
                        }
                        default: {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 46, 46, 46, 46);
                            break;
                        }
                    }
                }
            }
            else
            {

                if (player.horizontal_scale() > bn::fixed(0.1))
                {
                    player.set_scale(player.horizontal_scale() - 0.05);
                }
                else
                {
                    return current_level;
                }
            }
        }
        else
        {
            // Go left
            if (pros_x < player.x())
            {
                player.set_x(player.x() - 1);
                if (orientation != 1)
                {
                    if (gravity)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 3 + chari_offset, 4 + chari_offset, 3 + chari_offset, 5 + chari_offset);
                    }
                    else
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 7 + chari_offset, 8 + chari_offset, 7 + chari_offset, 8 + chari_offset);
                    }
                    orientation = 1;
                    player.set_horizontal_flip(false);
                }

                // Go right
            }
            else if (pros_x > player.x())
            {
                player.set_x(player.x() + 1);
                if (orientation != 2)
                {
                    if (gravity)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 3 + chari_offset, 4 + chari_offset, 3 + chari_offset, 5 + chari_offset);
                    }
                    else
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 7 + chari_offset, 8 + chari_offset, 7 + chari_offset, 8 + chari_offset);
                    }

                    orientation = 2;
                    player.set_horizontal_flip(false);
                }
            }

            if (pros_y < player.y())
            {
                player.set_y(player.y() - 1);
                if (orientation != 3)
                {
                    if (gravity)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 10 + chari_offset, 11 + chari_offset, 10 + chari_offset, 12 + chari_offset);
                    }
                    else
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 7 + chari_offset, 8 + chari_offset, 7 + chari_offset, 8 + chari_offset);
                    }

                    orientation = 3;
                    player.set_horizontal_flip(false);
                }
            }
            else if (pros_y > player.y())
            {
                player.set_y(player.y() + 1);
                if (orientation != 4)
                {
                    if (gravity)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 0 + chari_offset, 1 + chari_offset, 0 + chari_offset, 2 + chari_offset);
                    }
                    else
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), 7 + chari_offset, 8 + chari_offset, 7 + chari_offset, 8 + chari_offset);
                    }

                    orientation = 4;
                    player.set_horizontal_flip(false);
                }
            }
        }

        if (escape(pros_x, pros_y))
        {
            while (window_y < 80)
            {
                window_y += 10;
                external_window.set_boundaries(-80, -120, window_y, 120);
                bn::core::update();
            }

            return current_level + 1;
        }

        action.update();
        bullet_action.update();
        bn::core::update();
    }

    return current_level;
}

int main()
{
    // Initialization
    bn::core::init();

    bn::music_items::harp.play(0.5);

    // Main gameplay loop
    while (current_level < 6)
    {
        bn::sound_items::alert.play(0.5);
        current_level = gameplay();
    }

    // Fallback so it doesn't up and crash
    while (true)
    {
        bn::core::update();
    }
}