#include "global.h"
#include "test/battle.h"



SINGLE_BATTLE_TEST("Flame Feast is super effective against FIRE Types")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_RAPIDASH);
    } WHEN {
        TURN { MOVE(player, MOVE_FLAME_FEAST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FLAME_FEAST, player);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Sledge Claw is super effective against ROCK Types")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ROGGENROLA);
    } WHEN {
        TURN { MOVE(player, MOVE_SLEDGE_CLAW); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SLEDGE_CLAW, player);
        MESSAGE("It's super effective!");
    }
}