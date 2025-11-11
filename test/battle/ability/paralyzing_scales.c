#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Paralyzing Scales lowers speed of opponents when hit by a move")
{
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) > 0);
        PLAYER(SPECIES_WYNAUT) { Ability(ABILITY_PARALYZING_SCALES); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ABILITY_POPUP(player, ABILITY_PARALYZING_SCALES);
    }
}