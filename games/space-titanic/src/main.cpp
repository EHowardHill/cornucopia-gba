/*
    Cornucopia, by Ethan Hill

    License for Butano:

    Copyright (c) 2020-2022 Gustavo Valiente gustavo.valiente@protonmail.com
    zlib License, see LICENSE file.
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
#include "bn_random.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_bg_palette_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_palette_ptr.h"
#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"

// My assets
#include "bn_sprite_items_beegui.h"
#include "bn_sprite_items_tukatuka.h"
#include "bn_sprite_items_cinemint.h"
#include "bn_sprite_items_chari.h"
#include "bn_sprite_items_world.h"
#include "bn_sprite_items_items.h"
#include "bn_sprite_items_buttons.h"
#include "bn_sprite_items_buttons_green.h"
#include "bn_sprite_items_buttons_red.h"
#include "bn_sprite_items_projectiles.h"
#include "bn_sprite_items_logo.h"
#include "bn_sprite_items_vegons_01.h"
#include "bn_sprite_items_item_pots.h"
#include "bn_sprite_items_veggies.h"
#include "bn_sprite_items_squares.h"

// Backgrounds
#include "bn_regular_bg_items_bg_carpet.h"
#include "bn_regular_bg_items_bg_cinemint.h"
#include "bn_regular_bg_items_bg_space.h"
#include "bn_regular_bg_items_bg_message.h"
#include "bn_regular_bg_items_bg_door.h"

// Credits
#include "bn_regular_bg_items_bg_message.h"
#include "bn_regular_bg_items_bg_message2.h"

// Writing systems
#include "bn_sprite_items_ws_arabic.h"
#include "bn_sprite_items_ws_latin.h"

// Cutscenes
#include "bn_sprite_items_cutscene00.h"
#include "bn_sprite_items_cutscene01.h"
#include "bn_sprite_items_cutscene02.h"
#include "bn_sprite_items_cutscene03.h"
#include "bn_sprite_items_cutscene04.h"
#include "bn_sprite_items_cutscene05.h"
#include "bn_sprite_items_cutscene06.h"
#include "bn_sprite_items_cutscene07.h"
#include "bn_sprite_items_cutscene08.h"
#include "bn_sprite_items_cutscene09.h"
#include "bn_sprite_items_cutscene10.h"
#include "bn_sprite_items_cutscene11.h"
#include "bn_sprite_items_cutscene12.h"
#include "bn_sprite_items_cutscene13.h"
#include "bn_sprite_items_cutscene14.h"
#include "bn_sprite_items_cutscene15.h"
#include "bn_sprite_items_cutscene16.h"
#include "bn_sprite_items_cutscene17.h"
#include "bn_sprite_items_cutscene18.h"
#include "bn_sprite_items_cutscene19.h"
#include "bn_sprite_items_cutscene20.h"
#include "bn_sprite_items_cutscene21.h"
#include "bn_sprite_items_cutscene22.h"
#include "bn_sprite_items_cutscene23.h"
#include "bn_sprite_items_cutscene24.h"
#include "bn_sprite_items_cutscene25.h"
#include "bn_sprite_items_cutscene26.h"
#include "bn_sprite_items_cutscene27.h"
#include "bn_sprite_items_cutscene28.h"
#include "bn_sprite_items_cutscene29.h"
#include "bn_sprite_items_cutscene30.h"
#include "bn_sprite_items_cutscene31.h"
#include "bn_sprite_items_cutscene32.h"
#include "bn_sprite_items_cutscene33.h"
#include "bn_sprite_items_cutscene34.h"
#include "bn_sprite_items_cutscene35.h"
#include "bn_sprite_items_cutscene36.h"
#include "bn_sprite_items_cutscene37.h"
#include "bn_sprite_items_cutscene38.h"
#include "bn_sprite_items_cutscene38b.h"
#include "bn_sprite_items_cutscene39.h"
#include "bn_sprite_items_cutscene40.h"
#include "bn_sprite_items_cutscene41.h"
#include "bn_sprite_items_cutscene42.h"
#include "bn_sprite_items_cutscene43.h"
#include "bn_sprite_items_cutscene44.h"
#include "bn_sprite_items_cutscene45.h"
#include "bn_sprite_items_cutscene46.h"
#include "bn_sprite_items_cutscene47.h"
#include "bn_sprite_items_cutscene48.h"
#include "bn_sprite_items_cutscene49.h"
#include "bn_sprite_items_cutscene50.h"
#include "bn_sprite_items_cutscene51.h"
#include "bn_sprite_items_cutscene52.h"
#include "bn_sprite_items_cutscene53.h"
#include "bn_sprite_items_cutscene54.h"
#include "bn_sprite_items_cutscene55.h"
#include "bn_sprite_items_cutscene56.h"
#include "bn_sprite_items_cutscene57.h"

#define IWRAM_CODE __attribute__((section(".iwram.text"), long_call))
#define EWRAM_CODE __attribute__((section(".ewram.text"), long_call))
#define IWRAM_DATA __attribute__((section(".iwram.data")))
#define EWRAM_DATA __attribute__((section(".ewram.data")))

#define encode_x(x) (x * 16) - 120 + 8
#define encode_y(y) (y * 16) - 80 + 8
#define resolve_x(x) ((x % 15) * 16) - 112
#define resolve_y(y) ((y / 15) * 16) - 72
#define decode(x, y) ((x + 120) / 16) + (15 * (((y + 80) / 16) % 15))
#define lerp(a, b, t) (a * (1 - t) + b * t)
#define escape(x, y) (x < -120 || x > 120 || y < -80 || y > 80)

#define push_tile(q) tiles.push_back(bn::sprite_items::q.create_sprite(-64 + (x * 64), -32 + (y * 64) - 8, (frame * 2) + y + (x * maxframes * 2)));

inline bool gravity_allow(int x)
{
    return (x == 0 || x == -1 || x == -5 || (x < -16));
}

inline bool antigravity_allow(int x)
{
    return (x != 1 || (x < -1 && x != -10));
}

inline bn::fixed distance(bn::sprite_ptr sprite1, bn::sprite_ptr sprite2)
{
    return bn::abs(bn::abs(sprite1.x() - sprite2.x()) + bn::abs(sprite1.y() - sprite2.y()));
}

inline void music_stop()
{
    if (bn::music::playing())
        bn::music::stop();
}

const int D_LEFT = 1;
const int D_RIGHT = 2;
const int D_UP = 3;
const int D_DOWN = 4;

const int LUNA = 0;
const int XYLIA = 13;
const int JASPER = 26;

// My custom functions
#include "./levels.h"
#include "./dialogue.h"

const bn::sprite_palette_item palette_brown = bn::sprite_items::world.palette_item();
const bn::sprite_palette_item palette_blue = bn::sprite_items::projectiles.palette_item();
const bn::bg_palette_item palette_bg_carpet = bn::regular_bg_items::bg_carpet.palette_item();
const bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);

// Big fat global variable
struct global_data
{
    int current_level;
    int chari_offset;
};
global_data *global;

class Barrel
{
    int steps = 0;
    bn::fixed x_speed = 0;
    bn::fixed y_speed = 0;

public:
    bn::sprite_ptr sprite = bn::sprite_items::items.create_sprite(0, 0, 1);
    int type = 0;
    int state = 0;
    Room *current_room;

    Barrel(int x, int y, Room *new_level, int new_type = 0)
    {
        current_room = new_level;
        current_room->map[decode(x, y)] = 1;
        type = new_type;

        switch (type)
        {
        case 1:
        {
            sprite = bn::sprite_items::items.create_sprite(x, y, 2);
            break;
        }
        default:
        {
            sprite.set_x(x);
            sprite.set_y(y);
            break;
        }
        }
    }

    // poosh
    void push(bn::fixed x, bn::fixed y)
    {
        switch (type)
        {
        case 2:
        {
            x_speed = x;
            y_speed = y;
            steps = 0;
            break;
        }
        case 1:
        {
            bn::sound_items::crunch.play();
            state = 1;
            sprite = bn::sprite_items::items.create_sprite(sprite.x(), sprite.y(), 3);
            sprite.put_below();
            int *base_level = (int *)current_room->resolve_level;
            current_room->map[decode(sprite.x().integer(), sprite.y().integer())] = base_level[decode(sprite.x().integer(), sprite.y().integer())];
            break;
        }
        default:
        {
            x_speed = x;
            y_speed = y;
            int *base_level = (int *)current_room->resolve_level;
            current_room->map[decode(sprite.x().integer(), sprite.y().integer())] = base_level[decode(sprite.x().integer(), sprite.y().integer())];
            steps = 0;
            break;
        }
        }
    }

    void update()
    {
        bn::fixed init_x = sprite.x();
        bn::fixed init_y = sprite.y();
        bn::fixed x_speed_prior = x_speed;
        bn::fixed y_speed_prior = y_speed;

        if (x_speed != 0 || y_speed != 0)
        {
            sprite.set_x(sprite.x() + x_speed);
            sprite.set_y(sprite.y() + y_speed);
            steps++;
        }

        switch (type)
        {
        case 2:
        {
            if (current_room->map[decode(
                    (sprite.x() + (x_speed / 2) + (x_speed * 96)).integer(),
                    (sprite.y() + (y_speed / 2) + (y_speed * 96)).integer())] == 1)
            {
                x_speed = 0;
                y_speed = 0;
                current_room->map[decode(sprite.x().integer(), sprite.y().integer())] = 1;
                if (steps == 1)
                {
                    sprite.set_x(init_x);
                    sprite.set_y(init_y);
                }
            }
            break;
        }
        default:
        {
            if (current_room->map[decode(
                    (sprite.x() + (x_speed / 2) + (x_speed * 4)).integer(),
                    (sprite.y() + (y_speed / 2) + (y_speed * 4)).integer())] == 1)
            {
                x_speed = 0;
                y_speed = 0;
                current_room->map[decode(sprite.x().integer(), sprite.y().integer())] = 1;
                if (steps == 1)
                {
                    sprite.set_x(init_x);
                    sprite.set_y(init_y);
                }
            }
            break;
        }
        }

        if (x_speed_prior != x_speed || y_speed_prior != y_speed)
        {
            bn::sound_items::box_01.play(0.5);
        }
    }
};

class Veggie
{
public:
    bn::sprite_ptr sprite = bn::sprite_items::veggies.create_sprite(0, 0, 1);
    bn::sprite_animate_action<2> sprite_action = bn::create_sprite_animate_action_forever(
        sprite, 3, bn::sprite_items::veggies.tiles_item(), 0, 1);

    Veggie(int x, int y, int veg)
    {
        sprite.set_position(x, y);
        sprite_action = bn::create_sprite_animate_action_forever(
            sprite, 3, bn::sprite_items::veggies.tiles_item(), veg * 2, (veg * 2) + 1);
    }

    void update()
    {
        sprite_action.update();
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
        case JASPER:
        {
            bn::sound_items::push_jasper.play(0.5);
            break;
        }
        case XYLIA:
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
        case JASPER:
        {
            bn::sound_items::wah_jasper.play(0.5);
            break;
        }
        case XYLIA:
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

int intro()
{
    bn::sound_items::nana.play(0.5);

    // Background stuff
    bn::regular_bg_ptr bg_cinemint = bn::regular_bg_items::bg_cinemint.create_bg(0, 0);

    // Bullet
    bn::sprite_ptr cinemint = bn::sprite_items::cinemint.create_sprite(-42, 0);
    bn::sprite_animate_action<36> cinemint_action = bn::create_sprite_animate_action_forever(
        cinemint, 3, bn::sprite_items::cinemint.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35);

    int frame = 0;
    while (true)
    {
        if (frame < 142)
        {
            cinemint_action.update();
        }
        else if (frame > 164)
        {
            return 0;
        }
        frame++;
        bn::core::update();
    }

    return 0;
}

int linear_gameplay()
{
    // Set up world
    Room current_room;
    current_room.setup(global->current_level);

    // Variable init
    bool indicate = false;
    int pros_x = current_room.start_x;
    int pros_y = current_room.start_y;
    int freefall = 0;
    int rotate = 90;
    int dead = 0;
    int orientation = 0;
    int notice = 0;
    int window_y = 120;
    int trig_offset = 0;
    int bullet_count = 0;
    int text_delay = 0;
    int exit_door_loc = 0;
    int ticker = -1;
    int jump = 0;
    int boss_lives = 12;
    int xray_kill_x = 0;
    bool boss_battle = false;
    bool exit_door_init = false;
    bool exit_button_init = false;
    bn::sprite_ptr exit_button = bn::sprite_items::items.create_sprite(resolve_x(-1), resolve_y(-1), 4);
    bn::sprite_ptr exit_door = bn::sprite_items::items.create_sprite(resolve_x(-1), resolve_y(-1), 6);
    bn::sprite_ptr boss_ammo = bn::sprite_items::projectiles.create_sprite(0, 0, 6);
    bn::sprite_ptr button = bn::sprite_items::buttons.create_sprite(-8 * 16, 72, 0);
    boss_ammo.set_palette(bn::sprite_items::buttons_green.palette_item());
    boss_ammo.set_visible(false);

    bn::fixed bullet_x;
    bn::fixed bullet_y;
    bn::random rnd;

    // Entrance door
    bn::sprite_ptr entr_door = bn::sprite_items::items.create_sprite(0, 0, 7);
    entr_door.set_horizontal_scale(0.1);

    // Set up vectors
    bn::vector<bn::sprite_ptr, 128> sprites_v;
    bn::vector<Barrel, 26> sprites_b;
    bn::vector<Veggie, 2> veggies;
    bn::vector<bn::sprite_ptr, 28> text_sprites;
    bn::vector<bn::sprite_ptr, 4> xray_sprites;

    // Background stuff
    bn::regular_bg_ptr bg_carpet = bn::regular_bg_items::bg_carpet.create_bg(0, 0);

    // Entrance / exit window
    bn::rect_window external_window = bn::rect_window::external();
    external_window.set_show_bg(bg_carpet, false);
    external_window.set_show_sprites(false);
    external_window.set_boundaries(-80, -120, 80, window_y);

    // Create wall tiles
    for (int i = 0; i < 135; i++)
    {
        BN_LOG(current_room.map[i]);

        // Hole
        if (current_room.map[i] == -1)
        {
            bn::sprite_ptr n = bn::sprite_items::items.create_sprite(resolve_x(i), resolve_y(i), 0);
            n.put_below();
            sprites_v.push_back(n);
        }
        // Barrel
        else if (current_room.map[i] == -2)
        {
            sprites_b.push_back(Barrel(resolve_x(i), resolve_y(i), &current_room));
            current_room.map[i] = 1;
        }
        else if (current_room.map[i] == -3)
        {
            sprites_b.push_back(Barrel(resolve_x(i), resolve_y(i), &current_room, 1));
            current_room.map[i] = 1;
        }
        // Special items
        else if (current_room.map[i] == -5)
        {
            exit_button.set_position(resolve_x(i), resolve_y(i));
            exit_button.put_below();
            exit_button_init = true;
        }
        else if (current_room.map[i] == -6)
        {
            entr_door.set_position(resolve_x(i) - 10, resolve_y(i));
            current_room.map[i] = 1;
        }
        else if (current_room.map[i] == -7)
        {
            exit_door_loc = i;
            exit_door_init = true;
            exit_door.set_position(resolve_x(i), resolve_y(i));
            current_room.map[i] = 1;
        }
        else if (current_room.map[i] == -8)
        {
            bn::sprite_ptr n = bn::sprite_items::projectiles.create_sprite(resolve_x(i), resolve_y(i), 4);
            n.put_below();
            sprites_v.push_back(n);
        }
        else if (current_room.map[i] == -9)
        {
            // Vegons
            exit_button = bn::sprite_items::vegons_01.create_sprite(resolve_x(i), resolve_y(i), 0);
            exit_button.put_above();
            exit_door = bn::sprite_items::item_pots.create_sprite(resolve_x(i) + 32, resolve_y(i) + 32, 0);
            exit_door.put_below();
            veggies.push_back(Veggie(resolve_x(i) + 32, resolve_y(i) + 32, 2));
            boss_battle = true;
        }
        else if (current_room.map[i] == -68)
        {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), 19);
            n.put_below();
            sprites_v.push_back(n);
            xray_kill_x = resolve_x(i);
        }
        else if (current_room.map[i] == -69)
        {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), 0);
            n.put_below();
            sprites_v.push_back(n);
        }
        else if (current_room.map[i] == -70)
        {
            bn::sprite_ptr n = bn::sprite_items::projectiles.create_sprite(resolve_x(i), resolve_y(i), 4);
            n.put_below();
            sprites_v.push_back(n);
        }
        else if (current_room.map[i] == -71)
        {
            sprites_b.push_back(Barrel(resolve_x(i), resolve_y(i), &current_room, 2));
            sprites_b.at(sprites_b.size() - 1).push(0, -0.1);
            current_room.map[i] = 0;
        }
        else if (current_room.map[i] < -16)
        {
            // xray_sprites
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), current_room.map[i] * -1);
            n.put_below();
            n.set_visible(false);
            xray_sprites.push_back(n);
        }
        // Everything else
        else if (current_room.map[i] > 0)
        {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), current_room.map[i] - 1);
            sprites_v.push_back(n);
            if (current_room.map[i] == 17)
            {
                current_room.map[i] = 1;
            }
        }
    }

    exit_door.set_horizontal_scale(1);

    // Spiral
    bn::sprite_ptr spiral = bn::sprite_items::projectiles.create_sprite(0, 0, 6);
    spiral.put_below();
    spiral.set_visible(false);

    // Aim
    bn::sprite_ptr aim = bn::sprite_items::projectiles.create_sprite(0, 0, 7);
    aim.set_visible(false);

    // Bullet
    bn::sprite_ptr bullet = bn::sprite_items::projectiles.create_sprite(0, 0, 2);
    bn::sprite_animate_action<2> bullet_action = bn::create_sprite_animate_action_forever(
        bullet, 1, bn::sprite_items::projectiles.tiles_item(), 2, 3);
    bullet.set_visible(false);
    bullet.set_z_order(0);

    // Create player
    bn::sprite_ptr player = bn::sprite_items::chari.create_sprite(pros_x, pros_y, 1);

    bn::sprite_animate_action<4> action = bn::create_sprite_animate_action_forever(
        player, 4, bn::sprite_items::chari.tiles_item(), global->chari_offset, global->chari_offset, global->chari_offset, global->chari_offset);

    while (true)
    {
        ticker += 1;
        spiral.set_visible(false);
        aim.set_visible(false);
        if (current_room.intro_monologue == 0)
        {
            notice = 0;
        }
        else
        {
            notice = 2;
        }

        // Handle window
        if (window_y > -80)
        {
            window_y -= 10;
            external_window.set_boundaries(-80, -120, window_y, 120);
        }

        // Handle door
        int entr_door_max = 1;
        if (entr_door.horizontal_scale() < entr_door_max)
        {
            auto scale = entr_door.horizontal_scale() + bn::fixed(0.1);
            if (scale < entr_door_max)
            {
                entr_door.set_horizontal_scale(scale);
            }
            else
            {
                bn::sound_items::box_01.play();
                entr_door.set_horizontal_scale(entr_door_max);
            }
            entr_door.set_x(entr_door.x() + 1);
        }

        // Handle barrels
        for (int i = 0; i < sprites_b.size(); i++)
        {
            if (sprites_b.at(i).sprite.y().integer() == pros_y)
            {
                if (sprites_b.at(i).sprite.x().integer() == pros_x - 16)
                {
                    switch (sprites_b.at(i).type)
                    {
                    case 1:
                    {
                        if (sprites_b.at(i).state == 0)
                            notice = 3;
                        break;
                    }
                    default:
                    {
                        notice = 1;
                        break;
                    }
                    }

                    if (bn::keypad::a_pressed() && !current_room.gravity)
                    {
                        if (sprites_b.at(i).type == 0)
                        {
                            freefall = D_RIGHT;
                            bn::sound_items::box_01.play(0.5);
                            chari_sound(global->chari_offset, 1);
                            if (!current_room.gravity)
                            {
                                sprites_b.at(i).push(-2, 0);
                            }
                        }
                        else
                        {
                            sprites_b.at(i).push(-2, 0);
                        }
                    }
                }
                else if (sprites_b.at(i).sprite.x().integer() == pros_x + 16)
                {
                    switch (sprites_b.at(i).type)
                    {
                    case 1:
                    {
                        if (sprites_b.at(i).state == 0)
                            notice = 3;
                        break;
                    }
                    default:
                    {
                        notice = 1;
                        break;
                    }
                    }
                    if (bn::keypad::a_pressed() && !current_room.gravity)
                    {
                        if (sprites_b.at(i).type == 0)
                        {
                            freefall = D_LEFT;
                            bn::sound_items::box_01.play(0.5);
                            chari_sound(global->chari_offset, 1);
                            if (!current_room.gravity)
                            {
                                sprites_b.at(i).push(2, 0);
                            }
                        }
                        else
                        {
                            sprites_b.at(i).push(2, 0);
                        }
                    }
                }
            }
            else if (sprites_b.at(i).sprite.x().integer() == pros_x)
            {
                if (sprites_b.at(i).sprite.y().integer() == pros_y - 16)
                {
                    switch (sprites_b.at(i).type)
                    {
                    case 1:
                    {
                        if (sprites_b.at(i).state == 0)
                            notice = 3;
                        break;
                    }
                    default:
                    {
                        notice = 1;
                        break;
                    }
                    }
                    if (bn::keypad::a_pressed() && !current_room.gravity)
                    {
                        if (sprites_b.at(i).type == 0)
                        {
                            freefall = D_DOWN;
                            bn::sound_items::box_01.play(0.5);
                            chari_sound(global->chari_offset, 1);
                            if (!current_room.gravity)
                            {
                                sprites_b.at(i).push(0, -2);
                            }
                        }
                        else
                        {
                            sprites_b.at(i).push(0, -2);
                        }
                    }
                }
                else if (sprites_b.at(i).sprite.y().integer() == pros_y + 16)
                {
                    switch (sprites_b.at(i).type)
                    {
                    case 1:
                    {
                        if (sprites_b.at(i).state == 0)
                            notice = 3;
                        break;
                    }
                    default:
                    {
                        notice = 1;
                        break;
                    }
                    }
                    if (bn::keypad::a_pressed() && !current_room.gravity)
                    {
                        if (sprites_b.at(i).type == 0)
                        {
                            freefall = D_UP;
                            bn::sound_items::box_01.play(0.5);
                            chari_sound(global->chari_offset, 1);
                            if (!current_room.gravity)
                            {
                                sprites_b.at(i).push(0, 2);
                            }
                        }
                        else
                        {
                            sprites_b.at(i).push(0, 2);
                        }
                    }
                }
            }

            // Is bullet?
            if (bullet.visible() && distance(sprites_b.at(i).sprite, bullet) < 8 && sprites_b.at(i).type == 2)
            {
                bullet.set_visible(false);
            }

            // Update function, obviously
            sprites_b.at(i).update();

            // Delete if it leaves the world
            if (escape(sprites_b.at(i).sprite.x().integer(), sprites_b.at(i).sprite.y().integer()))
            {
                sprites_b.erase(&sprites_b.at(i));
            }
        }

        // Handle buttons
        if (boss_battle)
        {
            bn::blending::set_intensity_alpha(lerp(bn::blending::intensity_alpha(), 0, bn::fixed(0.01)));
            exit_door = bn::sprite_items::item_pots.create_sprite(exit_door.x(), exit_door.y(), (ticker / 6) % 3);
            exit_door.put_below();
            boss_ammo.set_visible(false);

            for (int t = 0; t < veggies.size(); t++)
            {
                veggies.at(t).update();
            }

            if (boss_lives > 0)
            {
                if (ticker % 1024 == 512)
                {
                    bn::sound_items::shepard.play();
                }
                else if (ticker % 1024 == 640)
                {
                    bn::sound_items::pew.play();
                }
                else if (ticker % 1024 == 0)
                {
                    bn::sound_items::rufus_02.play();
                }

                switch ((ticker / 256) % 4)
                {
                case 1:
                {
                    exit_button.set_blending_enabled(true);
                    if (jump == 0)
                    {
                        if (exit_button.horizontal_scale() < 2)
                        {
                            bn::blending::set_transparency_alpha(lerp(bn::blending::transparency_alpha(), 0, bn::fixed(0.05)));
                            exit_button.set_scale(exit_button.horizontal_scale() + bn::fixed(0.05), exit_button.horizontal_scale() + bn::fixed(0.05));
                        }
                        else
                        {
                            jump = 1;
                            bn::sound_items::crunch.play();
                        }
                    }
                    else if (jump == 1)
                    {
                        bool in = true;
                        int spot = 0;
                        do
                        {
                            spot = rnd.get_int() % 135;
                            if (current_room.map[spot] == 0)
                            {
                                exit_button.set_position(resolve_x(spot), resolve_y(spot));
                                in = false;
                            }
                        } while (in);
                        current_room.map[spot] = 1;
                        current_room.map[decode(exit_button.x().integer(), exit_button.y().integer())] = 0;
                        jump = 2;
                    }
                    else
                    {
                        if (exit_button.horizontal_scale() > 1)
                        {
                            bn::blending::set_transparency_alpha(lerp(bn::blending::transparency_alpha(), 1, bn::fixed(0.05)));
                            exit_button.set_scale(exit_button.horizontal_scale() - bn::fixed(0.05), exit_button.horizontal_scale() - bn::fixed(0.05));
                        }
                        else
                        {
                            if (distance(player, exit_button) < 8 && dead == 0)
                            {
                                exit_button.set_visible(false);
                                chari_sound(global->chari_offset, 0);
                                dead = 1;
                            }
                            jump = 0;
                        }
                    }
                    break;
                }
                case 2:
                {
                    bn::blending::set_transparency_alpha(lerp(bn::blending::transparency_alpha(), 1, bn::fixed(0.7)));
                    exit_button = bn::sprite_items::vegons_01.create_sprite(exit_button.x(), exit_button.y(), (((ticker / 4) % 4) * 4) + 2);

                    if ((ticker / 128) % 8 == 4)
                    {
                        boss_ammo.set_position(exit_button.x(), exit_button.y() - 16);
                    }
                    else
                    {
                        exit_button = bn::sprite_items::vegons_01.create_sprite(exit_button.x(), exit_button.y(), ((ticker / 4) % 4) * 4);

                        // Approach player
                        bn::fixed toVector_x = player.x() - boss_ammo.x();
                        bn::fixed toVector_y = player.y() - boss_ammo.y();
                        bn::fixed maxDistanceDelta = bn::fixed(1);
                        bn::fixed sqDist = (toVector_x * toVector_x) + (toVector_y * toVector_y);
                        if (sqDist == 0 || (maxDistanceDelta >= 0 && sqDist <= maxDistanceDelta * maxDistanceDelta))
                        {
                            boss_ammo.set_position(boss_ammo.x(), boss_ammo.y());
                        }
                        else
                        {
                            bn::fixed dist = sqrt(sqDist);
                            boss_ammo.set_position(
                                boss_ammo.x() + ((toVector_x / dist) * maxDistanceDelta),
                                boss_ammo.y() + ((toVector_y / dist) * maxDistanceDelta));
                        }
                    }

                    if (distance(player, boss_ammo) < 8 && dead == 0)
                    {
                        dead = 1;
                        chari_sound(global->chari_offset, 0);
                        bn::sound_items::pew_die.play();
                    }

                    boss_ammo.set_rotation_angle((ticker * 4) % 360);
                    boss_ammo.put_above();
                    boss_ammo.set_visible(true);
                    break;
                }
                default:
                {
                    bn::blending::set_transparency_alpha(lerp(bn::blending::transparency_alpha(), 1, bn::fixed(0.7)));
                    if (distance(bullet, exit_button) < 24 && bullet.visible())
                    {
                        bullet.set_visible(false);
                        bn::sound_items::pew_die.play();
                        bn::sound_items::rufus_01.play();
                        bn::blending::set_intensity_alpha(1);
                        boss_lives--;
                    }

                    if (exit_button.horizontal_scale() > 1)
                    {
                        exit_button.set_scale(exit_button.horizontal_scale() - bn::fixed(0.1));
                    }

                    exit_button = bn::sprite_items::vegons_01.create_sprite(exit_button.x(), exit_button.y(), ((ticker / 4) % 4) * 4);

                    if (distance(player, exit_button) < 8)
                    {
                        dead = 1;
                    }
                    break;
                }
                }
            }
            else
            {
                return 1;
            }

            exit_button.set_blending_enabled(true);
        }
        else
        {
            if (exit_button_init)
            {
                if (
                    (distance(player, exit_button) < 16) ||
                    (distance(bullet, exit_button) < 16 && bullet.visible()) ||
                    (current_room.map[decode(exit_button.x().integer(), exit_button.y().integer())] == 1))
                {
                    exit_button_init = false;
                    exit_button.set_visible(false);
                    bn::sound_items::box_01.play();
                    int leg_x = exit_button.x().integer();
                    int leg_y = exit_button.y().integer();
                    exit_button = bn::sprite_items::items.create_sprite(leg_x, leg_y, 5);
                    exit_button.put_below();
                }
            }
            else if (exit_door_init)
            {
                bn::fixed scale = exit_door.horizontal_scale() - bn::fixed(0.1);
                if (scale > 0)
                {
                    exit_door.set_horizontal_scale(scale);
                    exit_door.set_x(exit_door.x() - 1);
                }
                else
                {
                    exit_door.set_visible(false);
                    exit_door_init = false;
                    current_room.map[exit_door_loc] = 0;
                    bn::sound_items::box_02.play();
                }
            }
        }

        // Xray killer
        if (xray_kill_x != 0 && global->chari_offset == JASPER && xray_kill_x < player.x().integer() && indicate == 1)
        {
            dead = 1;
        }

        // Is intro monologue happening?
        if (text_sprites.size() > 0)
        {
            for (int i = 0; i < text_sprites.size(); i++)
            {
                if (text_sprites.at(i).y() < 72)
                {
                    text_sprites.at(i).set_y(text_sprites.at(i).y() + 1);
                }
                else if (text_delay < 16)
                {
                    text_delay++;
                }
                else if (!text_sprites.at(i).visible())
                {
                    text_sprites.at(i).set_visible(true);
                    text_delay = 0;
                    bn::sound_items::click.play(0.3);
                    i = text_sprites.size();
                }
            }
        }
        if (notice == 2)
        {
            if (button.x() < -7 * 16)
            {
                button.set_x(button.x() + 2);
            }

            if (text_sprites.size() == 0)
            {
                const char *base_string = (char *)resolve_dialogue(current_room.intro_monologue, current_room.intro_monologue_pos);
                if (base_string[0] == '$')
                {
                    notice = 0;
                    current_room.intro_monologue = 0;
                }
                else
                {
                    text_generator.generate(-6 * 16, 68, &base_string[0], text_sprites);
                    for (int i = 0; i < text_sprites.size(); i++)
                    {

                        text_sprites.at(i).set_visible(false);
                    }
                }
            }

            if (bn::keypad::a_pressed())
            {
                current_room.intro_monologue_pos++;
                text_sprites.clear();
                button.set_x(button.x() - 4);
            }

            if (bn::keypad::b_pressed())
            {
                current_room.intro_monologue = 0;
                notice = 0;
            }
        }
        else
        {
            // Handle strope bar
            if (notice == 1 && button.x() < -7 * 16 && !current_room.gravity)
            {
                button.set_x(button.x() + 2);
                if (text_sprites.size() == 0)
                {
                    const char *base_string = (char *)resolve_dialogue(0);
                    text_generator.generate(-6 * 16, 72, &base_string[0], text_sprites);
                    for (int i = 0; i < text_sprites.size(); i++)
                    {
                        text_sprites.at(i).set_visible(false);
                    }
                }
            }
            else if (notice == 3 && button.x() < -7 * 16 && !current_room.gravity)
            {
                button.set_x(button.x() + 2);
                if (text_sprites.size() == 0)
                {
                    const char *base_string = (char *)resolve_dialogue(0, 1);
                    text_generator.generate(-6 * 16, 72, &base_string[0], text_sprites);
                    for (int i = 0; i < text_sprites.size(); i++)
                    {
                        text_sprites.at(i).set_visible(false);
                    }
                }
            }
            else if (notice == 0 && button.x() > -8 * 16)
            {
                button.set_x(button.x() - 2);
                text_sprites.clear();
            }

            // Handle bullet
            if (bullet.visible())
            {

                if (global->chari_offset == LUNA)
                {
                    bn::fixed proj_x = bn::degrees_cos(bullet.rotation_angle()) * 4;
                    bn::fixed proj_y = -bn::degrees_sin(bullet.rotation_angle()) * 4;
                    int spot = decode((bullet.x() + proj_x).integer(), (bullet.y() + proj_y).integer());

                    if (current_room.map[spot] == 1 || current_room.map[spot] == -8)
                    {
                        for (int i = 0; i < sprites_b.size(); i++)
                        {
                            if (distance(sprites_b.at(i).sprite, bullet) < 18)
                            {
                                sprites_b.at(i).push(0, 0);
                            }
                        }

                        int deduction = 360;
                        if (bn::abs(decode(bullet.x().integer(), bullet.y().integer()) - spot) <= 2)
                            deduction = 540;
                        bullet.set_rotation_angle((deduction - bullet.rotation_angle().integer()) % 360);
                        bullet_count++;
                        if (bullet_count <= 8)
                        {
                            bn::sound_items::pew.play();
                        }
                        else
                        {
                            bn::sound_items::pew_die.play();
                            bullet.set_visible(false);
                        }

                        proj_x = bn::degrees_cos(bullet.rotation_angle()) * 4;
                        proj_y = -bn::degrees_sin(bullet.rotation_angle()) * 4;
                    }

                    bullet.set_position(bullet.x() + proj_x, bullet.y() + proj_y);
                }
                else if (global->chari_offset == XYLIA)
                {
                    int spot = decode(bullet.x().integer(), bullet.y().integer());
                    if (current_room.map[spot] > 0 || current_room.map[spot] == -8)
                    {
                        bn::sound_items::pew_die.play();
                        bullet.set_visible(false);
                        indicate = false;
                    }

                    bullet.set_rotation_angle((bullet.rotation_angle().integer() + 1) % 360);

                    if (bn::keypad::left_held())
                    {
                        bullet_x -= bn::fixed(0.02);
                    }

                    if (bn::keypad::right_held())
                    {
                        bullet_x += bn::fixed(0.02);
                    }

                    if (bn::keypad::up_held())
                    {
                        bullet_y -= bn::fixed(0.02);
                    }

                    if (bn::keypad::down_held())
                    {
                        bullet_y += bn::fixed(0.02);
                    }

                    bullet.set_position(bullet.x() + bullet_x, bullet.y() + bullet_y);
                    bullet.put_above();
                }
            }

            // If special power is in effect
            if (indicate == 1)
            {
                switch (global->chari_offset)
                {
                case JASPER:
                {
                    break;
                }
                case XYLIA:
                {
                    spiral.set_visible(true);
                    spiral.set_rotation_angle((spiral.rotation_angle().integer() + 10) % 360);
                    spiral.set_scale((bn::sin(trig_offset) * bn::fixed(0.5)) + bn::fixed(1.5), (bn::cos(trig_offset) * bn::fixed(0.5)) + bn::fixed(1.5));
                    spiral.set_position(player.x(), player.y());
                    if (spiral.rotation_angle().integer() % 65 == 0)
                    {
                        bn::sound_items::shepard.play(0.1);
                    }
                    break;
                }
                default:
                {
                    aim.set_visible(true);
                    if (bn::keypad::up_held() || bn::keypad::left_held())
                    {
                        trig_offset = (trig_offset + 4) % 360;
                        if (trig_offset % 12 == 0)
                        {
                            bn::sound_items::click.play(0.3);
                        }
                    }
                    else if (bn::keypad::down_held() || bn::keypad::right_held())
                    {
                        trig_offset = (trig_offset - 4) % 360;
                        if (trig_offset % 12 == 0)
                        {
                            bn::sound_items::click.play(0.3);
                        }
                    }
                    if (trig_offset < 0)
                        trig_offset = 360;
                    aim.set_position(pros_x + (bn::degrees_sin(trig_offset) * bn::fixed(16)).integer(), pros_y + (bn::degrees_cos(trig_offset) * bn::fixed(16)).integer());
                    aim.set_rotation_angle((trig_offset + 90) % 360);
                    break;
                }
                }
            }

            // Handle player rotation
            if (current_room.gravity)
            {
                rotate = 0;
            }
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
                if (bn::keypad::l_pressed() || bn::keypad::r_pressed())
                {
                    indicate = false;

                    BN_LOG(global->chari_offset);
                    global->chari_offset = (global->chari_offset + XYLIA) % 39;

                    if (global->current_level < 6 && global->chari_offset > LUNA)
                    {
                        global->chari_offset = LUNA;
                    }
                    else if (global->current_level < 24 && global->chari_offset > XYLIA)
                    {
                        global->chari_offset = LUNA;
                    }
                    else if (global->chari_offset > JASPER)
                    {
                        global->chari_offset = LUNA;
                    }

                    if (global->current_level == 39 && global->chari_offset == LUNA)
                    {
                        global->chari_offset = XYLIA;
                    }

                    // If gravity, set sprite
                    if (current_room.gravity)
                    {
                        action = bn::create_sprite_animate_action_forever(
                            player, 4, bn::sprite_items::chari.tiles_item(), global->chari_offset, global->chari_offset, global->chari_offset, global->chari_offset);
                    }

                    bullet.set_visible(false);
                    for (int i = 0; i < sprites_v.size(); i++)
                    {
                        bn::sprite_palette_ptr palette = sprites_v.at(i).palette();
                        palette.set_inverted(false);
                    }
                    for (int i = 0; i < xray_sprites.size(); i++)
                    {
                        xray_sprites.at(i).set_visible(false);
                    }
                    bn::bg_palette_ptr bg_palette = bg_carpet.palette();
                    bg_palette.set_inverted(false);
                    bn::sound_items::click.play();
                }

                // If on black hole
                if (current_room.map[decode(pros_x, pros_y)] == -1 && dead != 1)
                {
                    chari_sound(global->chari_offset, 0);
                    dead = 1;
                }
                else if (current_room.map[decode(pros_x, pros_y)] == -8 && dead != 1)
                {
                    chari_sound(global->chari_offset, 0);
                    bn::sound_items::pew_die.play();
                    dead = 1;
                }

                if (dead == 0)
                {
                    // No thingy
                    if (indicate == 0)
                    {
                        // Activate thingy
                        if (bn::keypad::b_released())
                        {
                            indicate = true;
                            if (global->chari_offset == LUNA)
                            {
                                bullet_action = bn::create_sprite_animate_action_forever(
                                    bullet, 1, bn::sprite_items::projectiles.tiles_item(), 2, 3);
                                bn::sound_items::push_luna.play(0.5);
                                bullet_count = 0;
                            }
                            else if (global->chari_offset == XYLIA)
                            {
                                bullet_action = bn::create_sprite_animate_action_forever(
                                    bullet, 1, bn::sprite_items::projectiles.tiles_item(), 0, 1);
                                bullet_count = 0;
                                bullet.set_visible(true);
                                bullet.set_position(pros_x, pros_y);
                            }
                            else if (global->chari_offset == JASPER)
                            {
                                for (int i = 0; i < sprites_v.size(); i++)
                                {
                                    bn::sprite_palette_ptr palette = sprites_v.at(i).palette();
                                    palette.set_inverted(true);
                                }
                                for (int i = 0; i < xray_sprites.size(); i++)
                                {
                                    xray_sprites.at(i).set_visible(true);
                                }
                                bn::bg_palette_ptr bg_palette = bg_carpet.palette();
                                bg_palette.set_inverted(true);
                                bn::sound_items::space_01.play();
                            }
                        }

                        // When current_room.gravity is activated
                        if (current_room.gravity)
                        {

                            int held_key = 0;

                            if (bn::keypad::left_held())
                            {
                                held_key = 1;
                                if (gravity_allow(current_room.map[decode(pros_x - 16, pros_y)]))
                                {
                                    pros_x -= 16;
                                }
                            }

                            else if (bn::keypad::right_held())
                            {
                                held_key = 2;
                                if (gravity_allow(current_room.map[decode(pros_x + 16, pros_y)]))
                                {
                                    pros_x += 16;
                                }
                            }

                            else if (bn::keypad::up_held())
                            {
                                held_key = 3;
                                if (gravity_allow(current_room.map[decode(pros_x, pros_y - 16)]))
                                {
                                    pros_y -= 16;
                                }
                            }

                            else if (bn::keypad::down_held())
                            {
                                held_key = 4;
                                if (gravity_allow(current_room.map[decode(pros_x, pros_y + 16)]))
                                {
                                    pros_y += 16;
                                }
                                if (current_room.gravity)
                                {
                                    player.set_horizontal_flip(false);
                                }
                            }

                            if (held_key == 0)
                            {
                                if (orientation == 1)
                                {
                                    action = bn::create_sprite_animate_action_forever(
                                        player, 4, bn::sprite_items::chari.tiles_item(), 3 + global->chari_offset, 3 + global->chari_offset, 3 + global->chari_offset, 3 + global->chari_offset);
                                    orientation = 0;
                                    player.set_horizontal_flip(true);
                                }
                                else if (orientation == 2)
                                {
                                    action = bn::create_sprite_animate_action_forever(
                                        player, 4, bn::sprite_items::chari.tiles_item(), 3 + global->chari_offset, 3 + global->chari_offset, 3 + global->chari_offset, 3 + global->chari_offset);
                                    orientation = 0;
                                    player.set_horizontal_flip(false);
                                }
                                else if (orientation == 3)
                                {
                                    action = bn::create_sprite_animate_action_forever(
                                        player, 4, bn::sprite_items::chari.tiles_item(), 10 + global->chari_offset, 10 + global->chari_offset, 10 + global->chari_offset, 10 + global->chari_offset);
                                    orientation = 0;
                                    player.set_horizontal_flip(false);
                                }
                                else if (orientation == 4)
                                {
                                    action = bn::create_sprite_animate_action_forever(
                                        player, 4, bn::sprite_items::chari.tiles_item(), 0 + global->chari_offset, 0 + global->chari_offset, 0 + global->chari_offset, 0 + global->chari_offset);
                                    orientation = 0;
                                    player.set_horizontal_flip(false);
                                }
                            }

                            // No current_room.gravity, but stable
                        }
                        else if (freefall == 0)
                        {

                            int is_held = 0;

                            if (bn::keypad::left_held())
                            {
                                is_held = 1;
                                // current_room.map[decode(pros_x - 16, pros_y)] != 1 && current_room.map[decode(pros_x - 16, pros_y)] < -1
                                if (antigravity_allow(current_room.map[decode(pros_x - 16, pros_y)]))
                                {
                                    if (current_room.map[decode(pros_x - 16, pros_y - 16)] == 1 || current_room.map[decode(pros_x - 16, pros_y - 16)] > 2)
                                    {
                                        rotate = 270;
                                        pros_x -= 16;
                                    }
                                    else if (current_room.map[decode(pros_x - 16, pros_y + 16)] == 1 || current_room.map[decode(pros_x - 16, pros_y + 16)] > 2)
                                    {
                                        rotate = 90;
                                        pros_x -= 16;
                                    }
                                    else
                                    {
                                        freefall = D_LEFT;
                                        rotate = 0;
                                        chari_sound(global->chari_offset, 1);
                                    }
                                }
                            }

                            if (bn::keypad::right_held())
                            {
                                is_held = 2;
                                if (antigravity_allow(current_room.map[decode(pros_x + 16, pros_y)]))
                                {
                                    if (current_room.map[decode(pros_x + 16, pros_y - 16)] == 1 || current_room.map[decode(pros_x + 16, pros_y - 16)] > 2)
                                    {
                                        rotate = 270;
                                        pros_x += 16;
                                    }
                                    else if (current_room.map[decode(pros_x + 16, pros_y + 16)] == 1 || current_room.map[decode(pros_x + 16, pros_y + 16)] > 2)
                                    {
                                        rotate = 90;
                                        pros_x += 16;
                                    }
                                    else
                                    {
                                        freefall = D_RIGHT;
                                        rotate = 180;
                                        chari_sound(global->chari_offset, 1);
                                    }
                                }
                            }

                            if (bn::keypad::up_held())
                            {
                                is_held = 3;
                                if (antigravity_allow(current_room.map[decode(pros_x, pros_y - 16)]))
                                {
                                    if (current_room.map[decode(pros_x + 16, pros_y - 16)] == 1 || current_room.map[decode(pros_x + 16, pros_y - 16)] > 2)
                                    {
                                        pros_y -= 16;
                                        rotate = 180;
                                    }
                                    else if (current_room.map[decode(pros_x - 16, pros_y - 16)] == 1 || current_room.map[decode(pros_x - 16, pros_y - 16)] > 2)
                                    {
                                        pros_y -= 16;
                                        rotate = 0;
                                    }
                                    else
                                    {
                                        freefall = D_UP;
                                        rotate = 270;
                                        chari_sound(global->chari_offset, 1);
                                    }
                                }
                            }

                            if (bn::keypad::down_held())
                            {
                                is_held = 4;
                                if (antigravity_allow(current_room.map[decode(pros_x, pros_y + 16)]))
                                {
                                    if (current_room.map[decode(pros_x + 16, pros_y + 16)] == 1 || current_room.map[decode(pros_x + 16, pros_y + 16)] > 2)
                                    {
                                        pros_y += 16;
                                        rotate = 180;
                                    }
                                    else if (current_room.map[decode(pros_x - 16, pros_y + 16)] == 1 || current_room.map[decode(pros_x - 16, pros_y + 16)] > 2)
                                    {
                                        pros_y += 16;
                                        rotate = 0;
                                    }
                                    else
                                    {
                                        freefall = D_DOWN;
                                        rotate = 90;
                                        chari_sound(global->chari_offset, 1);
                                    }
                                }
                            }

                            if (is_held == 0)
                            {
                                action = bn::create_sprite_animate_action_forever(
                                    player, 4, bn::sprite_items::chari.tiles_item(), 6 + global->chari_offset, 6 + global->chari_offset, 6 + global->chari_offset, 6 + global->chari_offset);
                            }
                            orientation = 0;
                        }
                        else if (freefall == D_LEFT)
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset);

                            if (pros_x == player.x())
                            {
                                if (current_room.map[decode(pros_x - 16, pros_y)] != 1)
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
                                player, 4, bn::sprite_items::chari.tiles_item(), 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset);

                            if (pros_x == player.x())
                            {
                                if (current_room.map[decode(pros_x + 16, pros_y)] != 1)
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
                                player, 4, bn::sprite_items::chari.tiles_item(), 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset);

                            if (pros_y == player.y())
                            {
                                if (current_room.map[decode(pros_x, pros_y - 16)] != 1)
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
                                player, 4, bn::sprite_items::chari.tiles_item(), 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset, 8 + global->chari_offset);

                            if (pros_y == player.y())
                            {
                                if (current_room.map[decode(pros_x, pros_y + 16)] != 1)
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
                    }
                    else
                    {
                        // Activate thingy
                        if (bn::keypad::b_released())
                        {
                            indicate = false;
                            if (global->chari_offset == LUNA)
                            {
                                bullet.set_visible(true);
                                bullet.set_position(pros_x, pros_y);
                                bullet.set_rotation_angle((aim.rotation_angle().integer() + 180) % 360);
                                bn::sound_items::pew.play();
                            }
                            else if (global->chari_offset == XYLIA)
                            {
                                bullet.set_visible(false);
                                bullet.set_position(pros_x, pros_y);
                            }
                            else if (global->chari_offset == JASPER)
                            {
                                for (int i = 0; i < sprites_v.size(); i++)
                                {
                                    bn::sprite_palette_ptr palette = sprites_v.at(i).palette();
                                    palette.set_inverted(false);
                                }
                                for (int i = 0; i < xray_sprites.size(); i++)
                                {
                                    xray_sprites.at(i).set_visible(false);
                                }
                                bn::bg_palette_ptr bg_palette = bg_carpet.palette();
                                bg_palette.set_inverted(false);
                                bn::sound_items::space_02.play();
                            }
                        }

                        switch (global->chari_offset)
                        {
                        case JASPER:
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 45, 45, 45, 45);
                            break;
                        }
                        case XYLIA:
                        {
                            rotate = 0;
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 47, 47, 47, 47);
                            break;
                        }
                        default:
                        {
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
                        return 0;
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
                        if (current_room.gravity)
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 3 + global->chari_offset, 4 + global->chari_offset, 3 + global->chari_offset, 5 + global->chari_offset);
                        }
                        else
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 7 + global->chari_offset, 8 + global->chari_offset, 7 + global->chari_offset, 8 + global->chari_offset);
                        }
                        orientation = 1;
                        player.set_horizontal_flip(current_room.gravity);
                    }

                    // Go right
                }
                else if (pros_x > player.x())
                {
                    player.set_x(player.x() + 1);
                    if (orientation != 2)
                    {
                        if (current_room.gravity)
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 3 + global->chari_offset, 4 + global->chari_offset, 3 + global->chari_offset, 5 + global->chari_offset);
                        }
                        else
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 7 + global->chari_offset, 8 + global->chari_offset, 7 + global->chari_offset, 8 + global->chari_offset);
                        }

                        orientation = 2;
                        player.set_horizontal_flip(false);
                    }
                }

                else if (pros_y < player.y())
                {
                    player.set_y(player.y() - 1);
                    if (orientation != 3)
                    {
                        if (current_room.gravity)
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 10 + global->chari_offset, 11 + global->chari_offset, 10 + global->chari_offset, 12 + global->chari_offset);
                        }
                        else
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 7 + global->chari_offset, 8 + global->chari_offset, 7 + global->chari_offset, 8 + global->chari_offset);
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
                        if (current_room.gravity)
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 0 + global->chari_offset, 1 + global->chari_offset, 0 + global->chari_offset, 2 + global->chari_offset);
                        }
                        else
                        {
                            action = bn::create_sprite_animate_action_forever(
                                player, 4, bn::sprite_items::chari.tiles_item(), 7 + global->chari_offset, 8 + global->chari_offset, 7 + global->chari_offset, 8 + global->chari_offset);
                        }

                        orientation = 4;
                        player.set_horizontal_flip(false);
                    }
                }
            }

            // Cosmetic character transition animation frames (whew)
            if (bn::keypad::b_held())
            {
                switch (global->chari_offset)
                {
                case XYLIA:
                {
                    action = bn::create_sprite_animate_action_forever(
                        player, 4, bn::sprite_items::chari.tiles_item(), 44, 44, 44, 44);
                    break;
                }
                case JASPER:
                {
                    action = bn::create_sprite_animate_action_forever(
                        player, 4, bn::sprite_items::chari.tiles_item(), 48, 48, 48, 48);
                    break;
                }
                default:
                {
                    action = bn::create_sprite_animate_action_forever(
                        player, 4, bn::sprite_items::chari.tiles_item(), 43, 43, 43, 43);
                    break;
                }
                }
            }

            // If we're good to leave
            if (escape(pros_x, pros_y))
            {
                while (window_y < 80)
                {
                    window_y += 10;
                    external_window.set_boundaries(-80, -120, window_y, 120);
                    bn::core::update();
                }
                return 1;
            }

            action.update();
            bullet_action.update();
        }

        bn::core::update();
    }
    return 0;
}

int show_cutscenes(int scene)
{
    int frame = 0;
    int maxframes = 30;
    int pos = 0;
    int cutscene = 1;
    int window_y = 120;
    bool loaded = false;
    bool primed = false;
    char color = 0;
    bn::vector<bn::sprite_ptr, 6> tiles;
    bn::vector<bn::sprite_ptr, 28> text_sprites1;
    bn::vector<bn::sprite_ptr, 28> text_sprites2;

    // bn::music_items::bored2.play(0.5);

    // Background stuff
    bn::regular_bg_ptr bg_space = bn::regular_bg_items::bg_space.create_bg(0, 0);
    bn::sprite_ptr button = bn::sprite_items::buttons.create_sprite(-8 * 16, 72, 0);

    // Entrance / exit window
    bn::rect_window external_window = bn::rect_window::external();
    external_window.set_show_bg(bg_space, false);
    external_window.set_show_sprites(false);
    external_window.set_boundaries(-80, -120, 80, window_y);

    while (true)
    {
        // 6:1 loop
        tiles.clear();

        bg_space.set_x((bg_space.x() + 1).integer() % 256);
        if (button.x() < (-7 * 16))
        {
            button.set_x(button.x() + 1);
        }

        // Set cutscene
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 2; y++)
            {
                switch (cutscene)
                {
                case 0:
                {
                    maxframes = 3;
                    push_tile(cutscene00);
                    break;
                }
                case 1:
                {
                    maxframes = 30;
                    push_tile(cutscene01);
                    break;
                }
                case 2:
                {
                    maxframes = 3;
                    push_tile(cutscene02);
                    break;
                }
                case 3:
                {
                    maxframes = 3;
                    push_tile(cutscene03);
                    break;
                }
                case 4:
                {
                    maxframes = 3;
                    push_tile(cutscene04);
                    break;
                }
                case 5:
                {
                    maxframes = 26;
                    push_tile(cutscene05);
                    break;
                }
                case 6:
                {
                    maxframes = 6;
                    push_tile(cutscene06);
                    break;
                }
                case 7:
                {
                    maxframes = 15;
                    push_tile(cutscene07);
                    break;
                }
                case 8:
                {
                    maxframes = 13;
                    push_tile(cutscene08);
                    break;
                }
                case 9:
                {
                    maxframes = 9;
                    push_tile(cutscene09);
                    break;
                }
                case 10:
                {
                    maxframes = 18;
                    push_tile(cutscene10);
                    break;
                }
                case 11:
                {
                    maxframes = 19;
                    push_tile(cutscene11);
                    break;
                }
                case 12:
                {
                    maxframes = 18;
                    push_tile(cutscene12);
                    break;
                }
                case 13:
                {
                    maxframes = 27;
                    push_tile(cutscene13);
                    break;
                }
                case 14:
                {
                    maxframes = 3;
                    push_tile(cutscene14);
                    break;
                }
                case 15:
                {
                    maxframes = 3;
                    push_tile(cutscene15);
                    break;
                }
                case 16:
                {
                    maxframes = 6;
                    push_tile(cutscene16);
                    break;
                }
                case 17:
                {
                    maxframes = 3;
                    push_tile(cutscene17);
                    break;
                }
                case 18:
                {
                    maxframes = 3;
                    push_tile(cutscene18);
                    break;
                }
                case 19:
                {
                    maxframes = 51;
                    push_tile(cutscene19);
                    break;
                }
                case 20:
                {
                    maxframes = 3;
                    push_tile(cutscene20);
                    break;
                }
                case 21:
                {
                    maxframes = 3;
                    push_tile(cutscene21);
                    break;
                    //
                }
                case 22:
                {
                    maxframes = 3;
                    push_tile(cutscene22);
                    break;
                }
                case 23:
                {
                    maxframes = 3;
                    push_tile(cutscene23);
                    break;
                }
                case 24:
                {
                    maxframes = 3;
                    push_tile(cutscene24);
                    break;
                }
                case 25:
                {
                    maxframes = 3;
                    push_tile(cutscene25);
                    break;
                }
                case 26:
                {
                    maxframes = 16;
                    push_tile(cutscene26);
                    break;
                }
                case 27:
                {
                    maxframes = 3;
                    push_tile(cutscene27);
                    break;
                }
                case 28:
                {
                    maxframes = 8;
                    push_tile(cutscene28);
                    break;
                }
                case 29:
                {
                    maxframes = 3;
                    push_tile(cutscene29);
                    break;
                }
                case 30:
                {
                    maxframes = 25;
                    push_tile(cutscene30);
                    break;
                }
                case 31:
                {
                    maxframes = 3;
                    push_tile(cutscene31);
                    break;
                }
                case 32:
                {
                    maxframes = 3;
                    push_tile(cutscene32);
                    break;
                }
                case 33:
                {
                    maxframes = 7;
                    push_tile(cutscene33);
                    break;
                }
                case 34:
                {
                    maxframes = 10;
                    push_tile(cutscene34);
                    break;
                }
                case 35:
                {
                    maxframes = 7;
                    push_tile(cutscene35);
                    break;
                }
                case 36:
                {
                    maxframes = 3;
                    push_tile(cutscene36);
                    break;
                }
                case 37:
                {
                    maxframes = 3;
                    push_tile(cutscene37);
                    break;
                }
                case 38:
                {
                    maxframes = 32;
                    push_tile(cutscene38);
                    break;
                }
                case 39:
                {
                    maxframes = 3;
                    push_tile(cutscene39);
                    break;
                }
                case 40:
                {
                    maxframes = 3;
                    push_tile(cutscene40);
                    break;
                }
                case 41:
                {
                    maxframes = 3;
                    push_tile(cutscene41);
                    break;
                }
                case 42:
                {
                    maxframes = 3;
                    push_tile(cutscene42);
                    break;
                }
                case 43:
                {
                    maxframes = 27;
                    push_tile(cutscene43);
                    break;
                }
                case 44:
                {
                    maxframes = 4;
                    push_tile(cutscene44);
                    break;
                }
                case 45:
                {
                    maxframes = 3;
                    push_tile(cutscene45);
                    break;
                }
                case 46:
                {
                    maxframes = 6;
                    push_tile(cutscene46);
                    break;
                }
                case 47:
                {
                    maxframes = 5;
                    push_tile(cutscene47);
                    break;
                }
                case 48:
                {
                    maxframes = 4;
                    push_tile(cutscene48);
                    break;
                }
                case 49:
                {
                    maxframes = 5;
                    push_tile(cutscene49);
                    break;
                }
                case 50:
                {
                    maxframes = 10;
                    push_tile(cutscene50);
                    break;
                }
                case 51:
                {
                    maxframes = 3;
                    push_tile(cutscene51);
                    break;
                }
                case 52:
                {
                    maxframes = 18;
                    push_tile(cutscene52);
                    break;
                }
                case 53:
                {
                    maxframes = 17;
                    push_tile(cutscene53);
                    break;
                }
                case 54:
                {
                    maxframes = 3;
                    push_tile(cutscene54);
                    break;
                }
                case 55:
                {
                    maxframes = 3;
                    push_tile(cutscene55);
                    break;
                }
                case 56:
                {
                    maxframes = 3;
                    push_tile(cutscene56);
                    break;
                }
                case 57:
                {
                    maxframes = 12;
                    push_tile(cutscene57);
                    break;
                }
                case 58:
                {
                    maxframes = 3;
                    push_tile(cutscene38b);
                    break;
                }
                default:
                {
                    maxframes = 30;
                    push_tile(cutscene01);
                    break;
                }
                }
            }
        }

        if (!primed)
        {
            primed = true;
            for (int i = 0; i < 6; i++)
            {
                tiles.at(i).set_visible(false);
                frame = -1;
            }
        }

        if (maxframes == 3)
        {
            // frame = frame + 1;
            loaded = true;
            if (frame >= maxframes)
            {
                frame = maxframes - 3;
            }
        }
        if (frame < maxframes - 3)
        {
            frame = (frame + 1) % maxframes;
        }
        else
        {
            frame = frame + 1;
            loaded = true;
            if (frame >= maxframes)
            {
                frame = maxframes - 3;
            }
        }

        // Is intro monologue happening?
        if (loaded)
        {
            if (text_sprites1.size() > 0)
            {
                for (int i = 0; i < text_sprites1.size(); i++)
                {
                    if (!text_sprites1.at(i).visible())
                    {
                        text_sprites1.at(i).set_visible(true);
                        switch (color)
                        {
                        default:
                        {
                            bn::sound_items::speech_luna.play(0.3);
                            break;
                        }
                        case '1':
                        {
                            bn::sound_items::speech_luna.play(0.3);
                            break;
                        }
                        }
                        i = text_sprites1.size();
                    }
                }
            }
            if (text_sprites2.size() > 0)
            {
                for (int i = 0; i < text_sprites2.size(); i++)
                {
                    if (!text_sprites2.at(i).visible())
                    {
                        text_sprites2.at(i).set_visible(true);
                        i = text_sprites2.size();
                    }
                }
            }
        }

        // 1:1 loop
        for (int n = 0; n < 6; n++)
        {
            // Handle window
            if (window_y > -80)
            {
                window_y -= 10;
                external_window.set_boundaries(-80, -120, window_y, 120);
            }

            if (bn::keypad::a_pressed())
            {
                button.set_x(button.x() - 1);
                text_sprites1.clear();
                text_sprites2.clear();
                pos++;
            }

            if (text_sprites1.size() == 0)
            {
                const char *base_string = (char *)resolve_dialogue(scene, pos);
                char sent1[29] = {};
                char sent2[28] = {};

                color = base_string[0];
                for (int i = 1; i < 71; i++)
                {
                    if (base_string[i] == 0)
                    {
                        break;
                    }
                    else
                    {
                        if (i < 29)
                        {
                            sent1[i - 1] = base_string[i];
                        }
                        else
                        {
                            sent2[i - 29] = base_string[i];
                        }
                    }
                }

                if (strcmp(sent1, "$") == 0)
                {
                    return 0;
                }
                else if (strcmp(sent1, "S00") == 0)
                {
                    cutscene = 0;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S01") == 0)
                {
                    cutscene = 1;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S02") == 0)
                {
                    cutscene = 2;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S03") == 0)
                {
                    cutscene = 3;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S04") == 0)
                {
                    cutscene = 4;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S05") == 0)
                {
                    cutscene = 5;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S06") == 0)
                {
                    cutscene = 6;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S07") == 0)
                {
                    cutscene = 7;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S08") == 0)
                {
                    cutscene = 8;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S09") == 0)
                {
                    cutscene = 9;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S10") == 0)
                {
                    cutscene = 10;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S11") == 0)
                {
                    cutscene = 11;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S12") == 0)
                {
                    cutscene = 12;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S13") == 0)
                {
                    cutscene = 13;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S14") == 0)
                {
                    cutscene = 14;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S15") == 0)
                {
                    cutscene = 15;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S16") == 0)
                {
                    cutscene = 16;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S17") == 0)
                {
                    cutscene = 17;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S18") == 0)
                {
                    cutscene = 18;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S19") == 0)
                {
                    bn::sound_items::pew_long.play();
                    cutscene = 19;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S20") == 0)
                {
                    cutscene = 20;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S21") == 0)
                {
                    cutscene = 21;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S22") == 0)
                {
                    cutscene = 22;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S23") == 0)
                {
                    cutscene = 23;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S24") == 0)
                {
                    cutscene = 24;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S25") == 0)
                {
                    cutscene = 25;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S26") == 0)
                {
                    bn::sound_items::pew.play();
                    cutscene = 26;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S27") == 0)
                {
                    cutscene = 27;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S28") == 0)
                {
                    cutscene = 28;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S29") == 0)
                {
                    cutscene = 29;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S30") == 0)
                {
                    cutscene = 30;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S31") == 0)
                {
                    cutscene = 31;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S32") == 0)
                {
                    cutscene = 32;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S33") == 0)
                {
                    cutscene = 33;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S34") == 0)
                {
                    cutscene = 34;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S35") == 0)
                {
                    cutscene = 35;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S36") == 0)
                {
                    cutscene = 36;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S37") == 0)
                {
                    cutscene = 37;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S38") == 0)
                {
                    cutscene = 38;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S38b") == 0)
                {
                    cutscene = 58;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S39") == 0)
                {
                    cutscene = 39;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S40") == 0)
                {
                    cutscene = 40;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S41") == 0)
                {
                    cutscene = 41;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S42") == 0)
                {
                    cutscene = 42;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S43") == 0)
                {
                    bn::sound_items::pew.play(0.5);
                    cutscene = 43;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S44") == 0)
                {
                    cutscene = 44;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S45") == 0)
                {
                    cutscene = 45;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S46") == 0)
                {
                    cutscene = 46;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S47") == 0)
                {
                    cutscene = 47;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S48") == 0)
                {
                    cutscene = 48;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S49") == 0)
                {
                    cutscene = 49;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S50") == 0)
                {
                    cutscene = 50;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S51") == 0)
                {
                    cutscene = 51;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S52") == 0)
                {
                    cutscene = 52;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S53") == 0)
                {
                    cutscene = 53;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S54") == 0)
                {
                    cutscene = 54;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S55") == 0)
                {
                    cutscene = 55;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S56") == 0)
                {
                    cutscene = 56;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "S57") == 0)
                {
                    cutscene = 57;
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "M_KILL") == 0)
                {
                    music_stop();
                    frame = 0;
                    pos++;
                }
                else if (strcmp(sent1, "M_ANATA") == 0)
                {
                    bn::music_items::anata.play(0.5);
                    frame = 0;
                    pos++;
                }
                else
                {
                    text_generator.generate(-6 * 16, 64, sent1, text_sprites1);
                    text_generator.generate(-6 * 16, 74, sent2, text_sprites2);
                    for (int i = 0; i < text_sprites1.size(); i++)
                    {
                        if (color == '1')
                        {
                            text_sprites1.at(i).set_palette(bn::sprite_items::buttons.palette_item());
                        }
                        else if (color == '2')
                        {
                            text_sprites1.at(i).set_palette(bn::sprite_items::buttons_green.palette_item());
                        }
                        else if (color == '3')
                        {
                            text_sprites1.at(i).set_palette(bn::sprite_items::buttons_red.palette_item());
                        }
                        text_sprites1.at(i).set_visible(false);
                    }
                    for (int i = 0; i < text_sprites2.size(); i++)
                    {
                        if (color == '1')
                        {
                            text_sprites2.at(i).set_palette(bn::sprite_items::buttons.palette_item());
                        }
                        else if (color == '2')
                        {
                            text_sprites2.at(i).set_palette(bn::sprite_items::buttons_green.palette_item());
                        }
                        else if (color == '3')
                        {
                            text_sprites2.at(i).set_palette(bn::sprite_items::buttons_red.palette_item());
                        }
                        text_sprites2.at(i).set_visible(false);
                    }
                }
            }

            bn::core::update();
        }
    }

    return 0;
}

int mainmenu()
{
    int window_y = 120;

    // Background stuff
    bn::regular_bg_ptr bg_space = bn::regular_bg_items::bg_space.create_bg(0, 0);

    bn::sprite_ptr logo[3] = {
        bn::sprite_items::logo.create_sprite(-74, 0, 0),
        bn::sprite_items::logo.create_sprite(0, 0, 1),
        bn::sprite_items::logo.create_sprite(74, 0, 2)};

    bn::sprite_ptr beegui = bn::sprite_items::beegui.create_sprite(0, -128);
    beegui.set_blending_enabled(true);

    bn::sprite_ptr fire = bn::sprite_items::tukatuka.create_sprite(-180, -8, 1);
    bn::sprite_ptr ship = bn::sprite_items::tukatuka.create_sprite(-180, 0);

    bn::sprite_animate_action<2> fire_action = bn::create_sprite_animate_action_forever(
        fire, 3, bn::sprite_items::tukatuka.tiles_item(), 1, 2);

    // Entrance / exit window
    bn::rect_window external_window = bn::rect_window::external();
    external_window.set_show_bg(bg_space, false);
    external_window.set_show_sprites(false);
    external_window.set_boundaries(-80, -120, 80, window_y);

    logo[0].set_scale(2);
    logo[1].set_scale(2);
    logo[2].set_scale(2);
    int stage = 0;

    while (true)
    {

        // Handle window
        if (window_y > -80)
        {
            window_y -= 10;
            external_window.set_boundaries(-80, -120, window_y, 120);
        }
        else
        {
            bn::fixed scale = logo[0].horizontal_scale() - bn::fixed(0.1);
            bg_space.set_x(bg_space.x() + bn::fixed(0.2));

            if (scale >= 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    logo[i].set_scale(scale, scale);
                    logo[i].set_blending_enabled(true);
                }
                logo[0].set_x(logo[0].x() + 1);
                logo[2].set_x(logo[2].x() - 1);
            }
            else if (stage == 0)
            {
                bn::sound_items::pew.play();
                stage = 1;
                bn::music_items::hon.play(1);
            }
            else if (stage < 48)
            {
                stage++;
            }
            else if (stage == 48)
            {
                stage = 49;
            }
            else if (stage == 49)
            {
                beegui.set_y(lerp(beegui.y(), -60, bn::fixed(0.15)));
                for (int i = 0; i < 3; i++)
                {
                    logo[i].set_y(lerp(logo[i].y(), 50, bn::fixed(0.15)));
                }
            }
            else if (stage > 49)
            {
                stage++;
                bn::blending::set_transparency_alpha(lerp(bn::blending::transparency_alpha(), 0, bn::fixed(0.05)));

                ship.set_x(ship.x() + bn::fixed(1.2));
                fire.set_x(ship.x() - 60);

                if (stage % 42 == 0)
                {
                    bn::sound_items::shepard.play(0.3);
                }

                if (stage > 360)
                {
                    return 0;
                }
            }
        }

        if ((bn::keypad::a_pressed() || bn::keypad::start_pressed()) && stage < 50)
        {
            stage = 50;
            bn::sound_items::click.play();
            music_stop();
        }

        fire_action.update();
        bn::core::update();
    }
}

int text_demo()
{
    bn::vector<bn::sprite_ptr, 28> text;

    int start_x = 100;
    int start_y = 0;
    int offset = -8;
    int ref[256] = {
        33, 14, 22, 52, 3, 14, 4, 18, 52, 19, 7, 8, 18, 52, 22, 14, 17, 10, -1};

    int val = 0;
    do
    {
        bn::sprite_ptr n = bn::sprite_items::ws_arabic.create_sprite(start_x, start_y, ref[val]);
        n.set_visible(false);
        text.push_back(n);
        start_x += offset;
        val++;
    } while (ref[val] != -1);

    while (true)
    {

        for (int t = 0; t < text.size(); t++)
        {
            if (!text.at(t).visible())
            {
                if (t % 3 == 0)
                {
                    bn::sound_items::click.play();
                }

                text.at(t).set_visible(true);
                t = text.size();
            }
        }

        bn::core::update();
    }

    return 0;
}

int grid_minigame(int level = 0)
{
    const int size = 5;
    bn::vector<bn::sprite_ptr, size * size> tiles;
    bn::vector<bn::sprite_ptr, 28> text_sprites;
    bn::sprite_ptr button = bn::sprite_items::buttons.create_sprite(-8 * 16, 72, 1);
    bn::regular_bg_ptr bg_door = bn::regular_bg_items::bg_door.create_bg(0, 0);
    int ref[size * size] = {0};
    int temp[size * size] = {0};
    int text_delay = 0;
    int window_y = 120;

    // Entrance / exit window
    bn::rect_window external_window = bn::rect_window::external();
    external_window.set_show_bg(bg_door, false);
    external_window.set_show_sprites(false);
    external_window.set_boundaries(-80, -120, 80, window_y);

    switch (level)
    {
    case 4:
    {
        ref[0] = 1;
        ref[1] = 1;
        ref[2] = 1;
        ref[3] = 1;
        ref[4] = 1;
        ref[5] = 1;
        ref[6] = 1;
        ref[7] = 1;
        ref[8] = 1;
        ref[9] = 1;
        ref[15] = 1;
        ref[16] = 1;
        ref[17] = 1;
        ref[18] = 1;
        ref[19] = 1;
        ref[20] = 1;
        ref[21] = 1;
        ref[22] = 1;
        ref[23] = 1;
        ref[24] = 1;
        break;
    }
    case 3:
    {
        ref[0] = 1;
        ref[4] = 1;
        ref[6] = 1;
        ref[8] = 1;
        ref[16] = 1;
        ref[18] = 1;
        ref[20] = 1;
        ref[24] = 1;
        break;
    }
    case 2:
    {
        ref[1] = 1;
        ref[3] = 1;
        ref[5] = 1;
        ref[6] = 1;
        ref[8] = 1;
        ref[9] = 1;
        ref[15] = 1;
        ref[16] = 1;
        ref[18] = 1;
        ref[19] = 1;
        ref[21] = 1;
        ref[23] = 1;
        break;
    }
    case 1:
    {
        ref[0] = 1;
        ref[1] = 1;
        ref[3] = 1;
        ref[4] = 1;
        ref[5] = 1;
        ref[9] = 1;
        break;
    }
    default:
    {
        ref[16] = 1;
        ref[17] = 1;
        ref[18] = 1;
        ref[20] = 1;
        ref[22] = 1;
        ref[24] = 1;
        break;
    }
    }

    for (int t = 0; t < size * size; t++)
    {
        temp[t] = ref[t];
        bn::sprite_ptr n = bn::sprite_items::squares.create_sprite(((t % size) * 16) - ((size / 2) * 16) - 1, ((t / size) * 16) - ((size / 2) * 16) - 16, ref[t]);
        tiles.push_back(n);
    }

    int dest_x = size >> 1;
    int dest_y = size >> 1;
    bn::sprite_ptr tab = bn::sprite_items::buttons.create_sprite(0, 0);

    while (true)
    {
        // Handle window
        if (window_y > -80)
        {
            window_y -= 10;
            external_window.set_boundaries(-80, -120, window_y, 120);
        }

        // Handle bottom thing
        if (button.x() < -7 * 16)
        {
            button.set_x(button.x() + 2);
            if (text_sprites.size() == 0)
            {
                const char *base_string = (char *)resolve_dialogue(0, 2);
                text_generator.generate(-6 * 16, 72, &base_string[0], text_sprites);
                for (int i = 0; i < text_sprites.size(); i++)
                {
                    text_sprites.at(i).set_visible(false);
                }
            }
        }

        if (text_sprites.size() > 0)
        {
            for (int i = 0; i < text_sprites.size(); i++)
            {
                if (text_sprites.at(i).y() < 72)
                {
                    text_sprites.at(i).set_y(text_sprites.at(i).y() + 1);
                }
                else if (text_delay < 16)
                {
                    text_delay++;
                }
                else if (!text_sprites.at(i).visible())
                {
                    text_sprites.at(i).set_visible(true);
                    text_delay = 0;
                    bn::sound_items::click.play(0.3);
                    i = text_sprites.size();
                }
            }
        }

        if (bn::keypad::left_pressed())
        {
            dest_x--;
            if (dest_x < 0)
            {
                dest_x = size - 1;
            }
        }
        else if (bn::keypad::right_pressed())
        {
            dest_x++;
            dest_x = dest_x % size;
        }
        else if (bn::keypad::up_pressed())
        {
            dest_y--;
            if (dest_y < 0)
            {
                dest_y = size - 1;
            }
        }
        else if (bn::keypad::down_pressed())
        {
            dest_y++;
            dest_y = dest_y % size;
        }

        tab.set_position(
            lerp(tab.x(), ((dest_x * 16) - 32), bn::fixed(0.5)),
            lerp(tab.y(), ((dest_y * 16) - 48), bn::fixed(0.5)));

        if (bn::keypad::a_pressed())
        {
            bn::sound_items::box_01.play(0.5);
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (x == 0 || y == 0)
                    {
                        int nx = x + dest_x;
                        int ny = y + dest_y;
                        if (nx > -1 && ny > -1 && nx < size && ny < size)
                        {
                            int n = (nx % size) + (ny * size);
                            ref[n] = (ref[n] + 1) % 2;
                            tiles.at(n) = bn::sprite_items::squares.create_sprite(tiles.at(n).x(), tiles.at(n).y(), ref[n]);
                        }
                    }
                }
            }

            bool pass = true;
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    if (ref[(x % size) + (y * size)] == 1)
                        pass = false;
                }
            }
            if (pass == true)
            {
                bn::sound_items::alert.play(0.5);
                for (int n = 0; n < 24; n++)
                {
                    bn::core::update();
                }
                while (window_y < 80)
                {
                    window_y += 10;
                    external_window.set_boundaries(-80, -120, window_y, 120);
                    bn::core::update();
                }
                return true;
            }
            tab.put_above();
        }
        else if (bn::keypad::b_pressed())
        {
            bn::sound_items::box_02.play();
            for (int n = 0; n < size * size; n++)
            {
                ref[n] = temp[n];
                tiles.at(n) = bn::sprite_items::squares.create_sprite(tiles.at(n).x(), tiles.at(n).y(), ref[n]);
            }
            tab.put_above();
        }

        bn::core::update();
    }

    return 0;
}

int main()
{
    // Initialization
    bn::core::init();
    global_data global_instance = {
        0,  // current level
        0}; // current character
    global = &global_instance;

    intro();
    mainmenu();

    music_stop();
    // CHAPTER ONE
    bn::music_items::bored.play(0.6);
    show_cutscenes(2);
    bn::music_items::harp.play(0.5);
    while (global->current_level < 6)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    music_stop();

    // CHAPTER TWO
    bn::music_items::bored2.play(0.6);
    show_cutscenes(3);
    bn::music_items::harp.play(0.5);
    while (global->current_level < 12)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    music_stop();

    // CHAPTER THREE
    bn::music_items::bored2.play(0.6);
    show_cutscenes(5);
    bn::music_items::harp.play(0.5);
    while (global->current_level < 18)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    music_stop();

    // Boss fight 1
    bn::music_items::boss.play(0.6);
    show_cutscenes(6);
    while (global->current_level < 19)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level = 19;
        global->current_level += linear_gameplay();
    }
    music_stop();

    // CHAPTER FOUR
    bn::music_items::bored2.play(0.6);
    show_cutscenes(7);
    bn::music_items::harp.play(0.5);
    while (global->current_level < 24)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    music_stop();

    // CHAPTER FIVE
    bn::music_items::bored2.play(0.6);
    show_cutscenes(8);
    bn::music_items::harp.play(0.5);
    while (global->current_level < 28)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    grid_minigame(1);
    while (global->current_level < 31)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    grid_minigame(0);
    music_stop();

    // BOSS 2
    bn::music_items::boss.play(0.6);
    while (global->current_level < 32)
    {
        bn::sound_items::alert.play(0.5);
        global->current_level += linear_gameplay();
    }
    music_stop();

    // CHAPTER SIX
    bn::music_items::bored2.play(0.5);
    music_stop();
    show_cutscenes(12);
    bn::music_items::harp.play(0.5);
    while (global->current_level < 34)
    {
        global->current_level += linear_gameplay();
    }
    grid_minigame(2);
    while (global->current_level < 36)
    {
        global->current_level += linear_gameplay();
    }
    grid_minigame(3);
    music_stop();

    // CHAPTER SEVEN
    bn::music_items::bored.play(0.5);
    show_cutscenes(13);
    bn::music_items::harp.play(0.5);
    music_stop();
    while (global->current_level < 38)
    {
        global->current_level += linear_gameplay();
    }
    music_stop();
    grid_minigame(4);

    bn::music_items::boss.play(0.5);
    while (global->current_level < 39)
    {
        global->current_level += linear_gameplay();
    }
    show_cutscenes(14);
    global->chari_offset = XYLIA;
    while (global->current_level < 40)
    {
        global->current_level += linear_gameplay();
    }

    music_stop();
    bn::music_items::bored.play(0.5);
    show_cutscenes(15);

    // Credits
    bn::music_items::anata.play(0.5);
    bn::regular_bg_ptr bg_message = bn::regular_bg_items::bg_message.create_bg(0, 0);
    while (!bn::keypad::a_released())
    {
        bn::core::update();
    }
    bn::sound_items::pew.play();
    bg_message = bn::regular_bg_items::bg_message2.create_bg(0, 0);
    while (true)
    {
        bn::core::update();
    }
}