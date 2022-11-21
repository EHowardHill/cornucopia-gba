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
#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

// My assets
#include "bn_sprite_items_ninja.h"
#include "bn_sprite_items_world.h"

// My custom functions
#include "./levels.h"

#define encode_x(x) (x * 16) - 120 + 8
#define encode_y(y) (y * 16) - 80 + 8
#define resolve_x(x) ((x % 15) * 16) - 112
#define resolve_y(y) ((y / 15) * 16) - 72
#define decode(x,y) ((x + 120) / 16) + (15 * (((y + 80) / 16) % 15))
#define lerp(a,b,t) (a * (1 - t) + b * t)
#define escape(x,y) (x < -120 || x > 120 || y < -80 || y > 80)

#define T_WALL 1
#define T_HOLE 2
#define D_LEFT 1
#define D_RIGHT 2
#define D_UP 3
#define D_DOWN 4

// Custom classes
class Barrel {
    int steps = 0;
    int x_speed = 0;
    int y_speed = 0;

    public:
    bn::sprite_ptr sprite = bn::sprite_items::world.create_sprite(0,0,2);
    
    Barrel(int x, int y, int *level) {
        sprite.set_x(x);
        sprite.set_y(y);
        level[decode(x,y)] = 1;
    }

    void push(int x, int y, int *level) {
        x_speed = x;
        y_speed = y;
        level[decode(sprite.x().integer(), sprite.y().integer())] = 0;
        steps = 0;
    }

    void update(int *level) {
        int init_x = sprite.x().integer();
        int init_y = sprite.y().integer();

        if (x_speed != 0 || y_speed != 0) {
            sprite.set_x(sprite.x().integer() + x_speed);
            sprite.set_y(sprite.y().integer() + y_speed);
            steps++;
        } 

        if (level[decode(
                sprite.x().integer() + (x_speed / 2) + (x_speed * 4),
                sprite.y().integer() +  + (y_speed / 2) + (y_speed * 4))] == 1) {
            x_speed = 0;
            y_speed = 0;
            level[decode(sprite.x().integer(),sprite.y().integer())] = 1;
            if (steps == 1) {
                sprite.set_x(init_x);
                sprite.set_y(init_y);
            }
        }
    }
};

// Big fat global variables
int current_level = 0;
bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

int gameplay() {
    // Configure globals
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    // Set up world
    int my_level [135] = {0};
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

    // Set up vectors
    bn::vector<bn::sprite_ptr, 64> sprites_v;
    bn::vector<Barrel, 4> sprites_b;

    // Create wall tiles
    for (int i = 0; i < 135; i++) {
        if (my_level[i] == 1) {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), my_level[i] - 1);
            sprites_v.push_back(n);
        } else if (my_level[i] == 2) {
            bn::sprite_ptr n = bn::sprite_items::world.create_sprite(resolve_x(i), resolve_y(i), my_level[i] - 1);
            n.put_below();
            sprites_v.push_back(n);
        } else if (my_level[i] == 3) {
            sprites_b.push_back(Barrel(resolve_x(i), resolve_y(i), my_level));
            sprites_b.at(sprites_b.size()-1).sprite.put_above();
        }
    }

    // Create player
    bn::sprite_ptr player = bn::sprite_items::ninja.create_sprite(start_x, start_y, 1);

    while(!bn::keypad::start_pressed())
    {
        // Handle barrels
        for (int i = 0; i < sprites_b.size(); i++) {
            if (bn::keypad::a_pressed()) {
                if (sprites_b.at(i).sprite.y().integer() == pros_y) {
                    if (sprites_b.at(i).sprite.x().integer() == pros_x - 16) {
                        sprites_b.at(i).push(-2,0,my_level);
                        freefall = D_RIGHT;
                    } else if (sprites_b.at(i).sprite.x().integer() == pros_x + 16) {
                        sprites_b.at(i).push(2,0,my_level);
                        freefall = D_LEFT;
                    }
                } else if (sprites_b.at(i).sprite.x().integer() == pros_x) {
                    if (sprites_b.at(i).sprite.y().integer() == pros_y - 16) {
                        sprites_b.at(i).push(0,-2,my_level);
                        freefall = D_DOWN;
                    } else if (sprites_b.at(i).sprite.y().integer() == pros_y + 16) {
                        sprites_b.at(i).push(0,2,my_level);
                        freefall = D_UP;
                    }
                }
            }

            sprites_b.at(i).update(my_level);

            // Delete if it leaves the world
            if (escape(sprites_b.at(i).sprite.x().integer(), sprites_b.at(i).sprite.y().integer())) {
                sprites_b.erase(&sprites_b.at(i));
            }
        }

        // Handle player rotation
        if (rotate < player.rotation_angle()) {
            player.set_rotation_angle(player.rotation_angle() - 10);
        } else if (rotate > player.rotation_angle()) {
            player.set_rotation_angle(player.rotation_angle() + 10);
        }

        // If ready for next move
        if (player.x() == pros_x && player.y() == pros_y) {

            // If on black hole
            if (my_level[decode(pros_x,pros_y)] == 2) {
                dead = 1;
            }

            if (dead == 0) {

                // When gravity is activated
                if (gravity) {
                    if (bn::keypad::left_held()) {
                        if (my_level[decode(pros_x - 16, pros_y)] != 1) {
                            pros_x -= 16;
                        }
                    }

                    if (bn::keypad::right_held()) {
                        if (my_level[decode(pros_x + 16, pros_y)] != 1) {
                            pros_x += 16;
                        }
                    }

                    if (bn::keypad::up_held()) {
                        if (my_level[decode(pros_x, pros_y - 16)] != 1) {
                            pros_y -= 16;
                        }
                    }

                    if (bn::keypad::down_held()) {
                        if (my_level[decode(pros_x, pros_y + 16)] != 1) {
                            pros_y += 16;
                        }
                    }

                // No gravity, but stable
                } else if (freefall == 0) {
                    
                    if (bn::keypad::left_held()) {
                        if (my_level[decode(pros_x - 16, pros_y)] != 1) {
                            if (my_level[decode(pros_x - 16, pros_y - 16)] == 1) {
                                rotate = 0;
                                pros_x -= 16;
                            } else if (my_level[decode(pros_x - 16, pros_y + 16)] == 1) {
                                rotate = 180;
                                pros_x -= 16;
                            } else {
                                freefall = D_LEFT;
                                rotate = 90;
                            }
                        }
                    }

                    if (bn::keypad::right_held()) {
                        if (my_level[decode(pros_x + 16, pros_y)] != 1) {
                            if (my_level[decode(pros_x + 16, pros_y - 16)] == 1) {
                                rotate = 0;
                                pros_x += 16;
                            } else if (my_level[decode(pros_x + 16, pros_y + 16)] == 1) {
                                rotate = 180;
                                pros_x += 16;
                            } else {
                                freefall = D_RIGHT;
                                rotate = 270;
                            }
                        }
                    }

                    if (bn::keypad::up_held()) {
                        if (my_level[decode(pros_x, pros_y - 16)] != 1) {
                            if (my_level[decode(pros_x + 16, pros_y - 16)] == 1) {
                                pros_y -= 16;
                                rotate = 270;
                            } else if (my_level[decode(pros_x - 16, pros_y - 16)] == 1) {
                                pros_y -= 16;
                                rotate = 90;
                            } else {
                                freefall = D_UP;
                                rotate = 0;
                            }
                        }
                    }

                    if (bn::keypad::down_held()) {
                        if (my_level[decode(pros_x, pros_y + 16)] != 1) {
                            if (my_level[decode(pros_x + 16, pros_y + 16)] == 1) {
                                pros_y += 16;
                                rotate = 270;
                            } else if (my_level[decode(pros_x - 16, pros_y + 16)] == 1) {
                                pros_y += 16;
                                rotate = 90;
                            } else {
                                freefall = D_DOWN;
                                rotate = 180;
                            }
                        }
                    }
                } else if (freefall == D_LEFT) {
                    if (pros_x == player.x()) {
                        if (my_level[decode(pros_x - 16, pros_y)] != 1) {
                            pros_x -= 16;
                        } else {
                            freefall = 0;
                            rotate = 90;
                        }
                    }
                } else if (freefall == D_RIGHT) {
                    if (pros_x == player.x()) {
                        if (my_level[decode(pros_x + 16, pros_y)] != 1) {
                            pros_x += 16;
                        } else {
                            freefall = 0;
                            rotate = 270;
                        }
                    }
                } else if (freefall == D_UP) {
                    if (pros_y == player.y()) {
                        if (my_level[decode(pros_x, pros_y - 16)] != 1) {
                            pros_y -= 16;
                        } else {
                            freefall = 0;
                            rotate = 0;
                        }
                    }
                } else if (freefall == D_DOWN) {
                    if (pros_y == player.y()) {
                        if (my_level[decode(pros_x, pros_y + 16)] != 1) {
                            pros_y += 16;
                        } else {
                            freefall = 0;
                            rotate = 180;
                        }
                    }
                } 

            } else {

                if (player.horizontal_scale() > bn::fixed(0.1)) {
                    player.set_scale(player.horizontal_scale() - 0.05);
                } else {
                    return current_level;
                }
            }

        } else {
            if (pros_x < player.x()) {
                player.set_x(player.x() - 1);
            } else if (pros_x > player.x()) {
                player.set_x(player.x() + 1);
            }

            if (pros_y < player.y()) {
                player.set_y(player.y() - 1);
            } else if (pros_y > player.y()) {
                player.set_y(player.y() + 1);
            }
        }

        if (escape(pros_x, pros_y)) {
            return current_level + 1;
        }

        bn::core::update();
    }

    return current_level;
}

int main()
{
    // Initialization
    bn::core::init();

    bn::music_items::bored2.play(0.5);

    // Main gameplay loop
    while (current_level < 6) {
        bn::sound_items::alert.play(0.5);
        current_level = gameplay();
    }
    
    // Fallback so it doesn't up and crash
    while (true) {
        bn::core::update();
    }
}