#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Toxic Thread poisons and sharply lowers SPD and DEF")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TOXIC_THREAD); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC_THREAD, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        MESSAGE("The opposing Wobbuffet's Speed sharply fell!");
    }
}