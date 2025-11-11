#include "global.h"
#include "test/battle.h"



SINGLE_BATTLE_TEST("Defend Order increases the user's Defense and Sp. Defense by 2 stages each")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DEFEND_ORDER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DEFEND_ORDER, player);
        MESSAGE("Wobbuffet's Defense sharply rose!");
        MESSAGE("Wobbuffet's Sp. Def sharply rose!");
    }
}