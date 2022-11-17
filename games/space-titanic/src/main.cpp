/*
* Copyright (c) 2020-2022 Gustavo Valiente gustavo.valiente@protonmail.com
* zlib License, see LICENSE file.
*/

#include "bn_core.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_first_attributes.h"
#include "bn_sprite_third_attributes.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_sprite_first_attributes_hbe_ptr.h"
#include "bn_sprite_third_attributes_hbe_ptr.h"
#include "bn_sprite_affine_second_attributes.h"
#include "bn_sprite_regular_second_attributes.h"
#include "bn_sprite_affine_second_attributes_hbe_ptr.h"
#include "bn_sprite_regular_second_attributes_hbe_ptr.h"

#include "bn_sprite_items_ninja.h"
#include "bn_sprite_items_blue_sprite.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#define decode(x,y) ((x + 120) / 16) + (15 * (((y + 80) / 16) % 15))

int main()
{
    // Initialization
    bn::core::init();
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));
    bn::vector<bn::sprite_ptr, 64> sprites_v;

    bn::sprite_ptr ninja = bn::sprite_items::ninja.create_sprite(-16, -56, 1);

    int pros_x = ninja.x().integer();
    int pros_y = ninja.y().integer();
    bool gravity = false;

    const int my_level [] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    for (int i = 0; i < 120; i++) {
        if (my_level[i] == 1) {
            bn::sprite_ptr n = bn::sprite_items::ninja.create_sprite(((i % 15) * 16) - 112, ((i / 15) * 16) - 72, 0);
            sprites_v.push_back(n);
        }
    }

    while(!bn::keypad::start_pressed())
    {
        if (ninja.x() == pros_x && ninja.y() == pros_y) {

            // When gravity is activated
            if (gravity) {
                if (bn::keypad::left_held()) {
                    if (my_level[decode(pros_x - 16, pros_y)] == 0) {
                        pros_x -= 16;
                    }
                }

                if (bn::keypad::right_held()) {
                    if (my_level[decode(pros_x + 16, pros_y)] == 0) {
                        pros_x += 16;
                    }
                }

                if (bn::keypad::up_held()) {
                    if (my_level[decode(pros_x, pros_y - 16)] == 0) {
                        pros_y -= 16;
                    }
                }

                if (bn::keypad::down_held()) {
                    if (my_level[decode(pros_x, pros_y + 16)] == 0) {
                        pros_y += 16;
                    }
                }
            } else {
                if (bn::keypad::left_held()) {
                    if (my_level[decode(pros_x - 16, pros_y)] == 0 && (
                        my_level[decode(pros_x, pros_y - 16)] != 0 ||
                        my_level[decode(pros_x, pros_y + 16)] != 0)
                    ) {
                        pros_x -= 16;
                    }
                }

                if (bn::keypad::right_held()) {
                    if (my_level[decode(pros_x + 16, pros_y)] == 0 && (
                        my_level[decode(pros_x, pros_y - 16)] != 0 ||
                        my_level[decode(pros_x, pros_y + 16)] != 0)) {
                        pros_x += 16;
                    }
                }

                if (bn::keypad::up_held()) {
                    if (my_level[decode(pros_x, pros_y - 16)] == 0 && (
                        my_level[decode(pros_x - 16, pros_y)] != 0 ||
                        my_level[decode(pros_x + 16, pros_y)] != 0)) {
                        pros_y -= 16;
                    }
                }

                if (bn::keypad::down_held()) {
                    if (my_level[decode(pros_x, pros_y + 16)] == 0 && (
                        my_level[decode(pros_x - 16, pros_y)] != 0 ||
                        my_level[decode(pros_x + 16, pros_y)] != 0)) {
                        pros_y += 16;
                    }
                }
            }

        } else {
            if (pros_x < ninja.x()) {
                ninja.set_x(ninja.x() - 1);
            } else if (pros_x > ninja.x()) {
                ninja.set_x(ninja.x() + 1);
            }

            if (pros_y < ninja.y()) {
                ninja.set_y(ninja.y() - 1);
            } else if (pros_y > ninja.y()) {
                ninja.set_y(ninja.y() + 1);
            }
        }

        bn::core::update();
    }
}
