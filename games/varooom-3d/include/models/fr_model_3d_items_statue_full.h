/*
 * Copyright (c) 2021
 * Gustavo Valiente gustavo.valiente@protonmail.com
 * Licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license
 */

#ifndef FR_MODEL_3D_ITEMS_STATUE_FULL_H
#define FR_MODEL_3D_ITEMS_STATUE_FULL_H

#include "fr_model_3d_item.h"

namespace fr::model_3d_items
{
    constexpr inline vertex_3d statue_full_vertices[] = {
        vertex_3d(3.81, 45.32, -4.44),
        vertex_3d(-4.1, 45.32, -4.44),
        vertex_3d(-4.1, 45.13, 4.11),
        vertex_3d(3.81, 45.13, 4.11),
        vertex_3d(-3.16, 32.0, 3.0),
        vertex_3d(2.87, 32.0, 3.0),
        vertex_3d(3.32, 33.0, -3.0),
        vertex_3d(-3.61, 33.0, -3.0),
        vertex_3d(11.72, 27.39, 0.0),
        vertex_3d(-12.01, 27.39, 0.0),
        vertex_3d(-8.0, 23.0, 6.0),
        vertex_3d(8.0, 23.0, 6.0),
        vertex_3d(8.0, 25.0, -6.0),
        vertex_3d(-8.0, 25.0, -6.0),
        vertex_3d(-8.0, -3.0, 5.0),
        vertex_3d(8.0, -3.0, 5.0),
        vertex_3d(-8.0, -3.0, -5.0),
        vertex_3d(8.0, -3.0, -5.0),
        vertex_3d(16.04, -5.97, 3.0),
        vertex_3d(20.02, -5.13, 0.0),
        vertex_3d(-20.31, -5.13, 0.0),
        vertex_3d(-16.33, -5.97, 3.0),
        vertex_3d(-16.18, -4.67, -4.0),
        vertex_3d(15.89, -4.67, -3.58),
        vertex_3d(11.0, -45.0, -4.0),
        vertex_3d(7.0, -45.0, -4.0),
        vertex_3d(0.0, -3.0, -5.0),
        vertex_3d(7.0, -45.0, 1.5),
        vertex_3d(11.0, -45.0, 1.5),
        vertex_3d(0.0, -3.0, 5.0),
        vertex_3d(-7.0, -45.0, -4.0),
        vertex_3d(-11.0, -45.0, -4.0),
        vertex_3d(-11.0, -45.0, 1.5),
        vertex_3d(-7.0, -45.0, 1.5),
        vertex_3d(-6.5, -50.0, 10.0),
        vertex_3d(-11.5, -50.0, 10.0),
        vertex_3d(11.5, -50.0, -4.0),
        vertex_3d(6.5, -50.0, -4.0),
        vertex_3d(6.5, -50.0, 10.0),
        vertex_3d(11.5, -50.0, 10.0),
        vertex_3d(-6.5, -50.0, -4.0),
        vertex_3d(-11.5, -50.0, -4.0),
        vertex_3d(12.5, 8.57, 4.51),
        vertex_3d(17.0, 11.2, 0.0),
        vertex_3d(12.5, 10.22, -4.8),
        vertex_3d(-17.0, 12.03, 0.0),
        vertex_3d(-12.5, 9.32, 4.58),
        vertex_3d(-12.5, 10.98, -5.06),
        vertex_3d(-8.0, 10.0, 5.5),
        vertex_3d(8.0, 10.0, 5.5),
        vertex_3d(-8.0, 11.0, -5.5),
        vertex_3d(8.0, 11.0, -5.5),
    };

    constexpr inline int statue_full_head_top_color = 3;
    constexpr inline int statue_full_head_top_shading = 7;

    constexpr inline int statue_full_head_side_a_color = 3;
    constexpr inline int statue_full_head_side_a_shading = 4;

    constexpr inline int statue_full_head_side_b_color = 3;
    constexpr inline int statue_full_head_side_b_shading = 2;

    constexpr inline int statue_full_torso_top_a_color = 7;
    constexpr inline int statue_full_torso_top_a_shading = 7;

    constexpr inline int statue_full_torso_top_b_color = 7;
    constexpr inline int statue_full_torso_top_b_shading = 6;

    constexpr inline int statue_full_torso_top_c_color = 7;
    constexpr inline int statue_full_torso_top_c_shading = 5;

    constexpr inline int statue_full_torso_side_a_color = 7;
    constexpr inline int statue_full_torso_side_a_shading = 4;

    constexpr inline int statue_full_torso_side_b_color = 7;
    constexpr inline int statue_full_torso_side_b_shading = 3;

    constexpr inline int statue_full_torso_side_c_color = 7;
    constexpr inline int statue_full_torso_side_c_shading = 2;

    constexpr inline int statue_full_torso_side_d_color = 7;
    constexpr inline int statue_full_torso_side_d_shading = 1;

    constexpr inline int statue_full_torso_bottom_color = 7;
    constexpr inline int statue_full_torso_bottom_shading = 0;

    constexpr inline int statue_full_hand_bottom_color = 3;
    constexpr inline int statue_full_hand_bottom_shading = 0;

    constexpr inline int statue_full_leg_side_a_color = 1;
    constexpr inline int statue_full_leg_side_a_shading = 4;

    constexpr inline int statue_full_leg_side_b_color = 1;
    constexpr inline int statue_full_leg_side_b_shading = 2;

    constexpr inline int statue_full_leg_bottom_color = 1;
    constexpr inline int statue_full_leg_bottom_shading = 0;

    constexpr inline int statue_full_foot_side_a_color = 4;
    constexpr inline int statue_full_foot_side_a_shading = 6;

    constexpr inline int statue_full_foot_side_b_color = 4;
    constexpr inline int statue_full_foot_side_b_shading = 2;

    constexpr inline int statue_full_foot_bottom_color = 4;
    constexpr inline int statue_full_foot_bottom_shading = 0;

    constexpr inline face_3d statue_full_faces[] = {
        face_3d(statue_full_vertices, vertex_3d(0.0, 0.99975317783161, 0.022216737285146622), 0, 1, 2, 3, statue_full_head_top_color, statue_full_head_top_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.08423873699894756, 0.9964456007172805), 3, 2, 4, 5, statue_full_head_side_a_color, statue_full_head_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.11609279666544346, -0.993238371471016), 6, 7, 1, 0, statue_full_head_side_a_color, statue_full_head_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.9974553954294081, -0.07127569975448335, -0.0015839044389884995), 5, 6, 0, 3, statue_full_head_side_b_color, statue_full_head_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.9974553954294081, -0.0712756997544833, -0.0015839044389884978), 1, 7, 4, 2, statue_full_head_side_b_color, statue_full_head_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.5015160925774349, 0.8464924263170992, 0.17869577799615746), 8, 6, 5, statue_full_torso_top_a_color, statue_full_torso_top_a_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.5015160925774349, 0.8464924263170992, 0.17869577799615743), 4, 7, 9, statue_full_torso_top_a_color, statue_full_torso_top_a_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.5010123641525634, 0.5039573302901245, 0.7035720433709043), 9, 10, 4, statue_full_torso_top_b_color, statue_full_torso_top_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.5040306367982342, 0.5177331596208167, 0.6913070899374695), 8, 5, 11, statue_full_torso_top_b_color, statue_full_torso_top_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, 0.31622776601683794, 0.9486832980505138), 10, 11, 5, 4, statue_full_torso_top_b_color, statue_full_torso_top_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.5842776878849928, 0.5615247727799931, -0.5859262009793929), 8, 12, 6, statue_full_torso_top_c_color, statue_full_torso_top_c_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.5802309942692182, 0.5452721834462383, -0.6049878009093459), 13, 9, 7, statue_full_torso_top_c_color, statue_full_torso_top_c_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, 0.3511234415883917, -0.9363291775690445), 12, 13, 7, 6, statue_full_torso_top_c_color, statue_full_torso_top_c_shading),
        face_3d(statue_full_vertices, vertex_3d(0.7364934190541247, 0.2401905653246311, 0.6323653501094124), 42, 43, 8, 11, statue_full_torso_side_a_color, statue_full_torso_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.7204823644328477, 0.23406295563280663, 0.65277844276729), 9, 45, 46, 10, statue_full_torso_side_a_color, statue_full_torso_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.03843312210120439, 0.9992611746313143), 10, 14, 15, 11, statue_full_torso_side_a_color, statue_full_torso_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.7741199558212476, 0.25246160387499605, -0.5805182448193804), 44, 12, 8, 43, statue_full_torso_side_b_color, statue_full_torso_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.7576781339666844, 0.2461467375321455, -0.6044300033180386), 9, 13, 47, 45, statue_full_torso_side_b_color, statue_full_torso_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.03569153051241249, -0.9993628543475496), 13, 12, 17, 16, statue_full_torso_side_b_color, statue_full_torso_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.668170347809633, 0.12888367431526138, 0.7327601140912022), 45, 20, 21, 46, statue_full_torso_side_c_color, statue_full_torso_side_c_shading),
        face_3d(statue_full_vertices, vertex_3d(0.6656889980405964, 0.1231096616094673, 0.736004190956892), 18, 19, 43, 42, statue_full_torso_side_c_color, statue_full_torso_side_c_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.7253031621600337, 0.13990404817888755, -0.6740639289146211), 45, 47, 22, 20, statue_full_torso_side_d_color, statue_full_torso_side_d_shading),
        face_3d(statue_full_vertices, vertex_3d(0.7097146629578164, 0.1312515788201228, -0.6921546938653945), 23, 44, 43, 19, statue_full_torso_side_d_color, statue_full_torso_side_d_shading),
        face_3d(statue_full_vertices, vertex_3d(0.9502450973289648, -0.3072648817710425, -0.05121081362850708), 13, 10, 46, 47, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(1.0, -0.0, 0.0), 51, 12, 11, 49, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(-1.0, 0.0, -0.0), 48, 50, 16, 14, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.9549401637520318, -0.2927601274134763, -0.04879335456891272), 12, 44, 42, 11, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(0.9702033299793148, -0.23877785116247252, -0.04111734781428469), 21, 22, 47, 46, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.9717682894658156, -0.23231692856421066, -0.041173247275074945), 18, 42, 44, 23, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(-1.0, 0.0, -0.0), 10, 13, 50, 48, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(1.0, -0.0, 0.0), 17, 51, 49, 15, statue_full_torso_bottom_color, statue_full_torso_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(0.05980323842337108, -0.9790207635306839, -0.1947868508135858), 19, 18, 23, statue_full_hand_bottom_color, statue_full_hand_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.06858373235841422, -0.98060881973066, -0.18358271792908856), 22, 21, 20, statue_full_hand_bottom_color, statue_full_hand_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.023802777946288958, -0.9997166737441362), 24, 25, 26, 17, statue_full_leg_side_a_color, statue_full_leg_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.08304547985373997, 0.9965457582448797), 27, 28, 15, 29, statue_full_leg_side_a_color, statue_full_leg_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.023802777946288958, -0.9997166737441362), 26, 30, 31, 16, statue_full_leg_side_a_color, statue_full_leg_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -0.08304547985373997, 0.9965457582448797), 29, 14, 32, 33, statue_full_leg_side_a_color, statue_full_leg_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.997458699830735, 0.07124704998790964, 0.0), 14, 16, 31, 32, statue_full_leg_side_b_color, statue_full_leg_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.997458699830735, 0.07124704998790964, -0.0), 28, 24, 17, 15, statue_full_leg_side_b_color, statue_full_leg_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.9863939238321437, -0.1643989873053573, -0.0), 27, 29, 26, 25, statue_full_leg_bottom_color, statue_full_leg_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(0.9863939238321437, -0.1643989873053573, 0.0), 29, 33, 30, 26, statue_full_leg_bottom_color, statue_full_leg_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.0, 0.8619342151577696, 0.5070201265633938), 34, 33, 32, 35, statue_full_foot_side_a_color, statue_full_foot_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, 0.0, -1.0), 25, 24, 36, 37, statue_full_foot_side_a_color, statue_full_foot_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.0, 0.8619342151577696, 0.5070201265633938), 28, 27, 38, 39, statue_full_foot_side_a_color, statue_full_foot_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, 0.0, -1.0), 30, 40, 41, 31, statue_full_foot_side_a_color, statue_full_foot_side_a_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.9950371902099892, 0.09950371902099892, 0.0), 35, 32, 31, 41, statue_full_foot_side_b_color, statue_full_foot_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.9950371902099892, 0.09950371902099892, 0.0), 34, 40, 30, 33, statue_full_foot_side_b_color, statue_full_foot_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.9950371902099892, 0.09950371902099892, 0.0), 24, 28, 39, 36, statue_full_foot_side_b_color, statue_full_foot_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(-0.9950371902099892, 0.09950371902099892, 0.0), 25, 37, 38, 27, statue_full_foot_side_b_color, statue_full_foot_side_b_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -1.0, 0.0), 40, 34, 35, 41, statue_full_foot_bottom_color, statue_full_foot_bottom_shading),
        face_3d(statue_full_vertices, vertex_3d(0.0, -1.0, 0.0), 36, 39, 38, 37, statue_full_foot_bottom_color, statue_full_foot_bottom_shading),
    };

    constexpr inline model_3d_item statue_full(statue_full_vertices, statue_full_faces);
}

#endif

