#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Ruthless Horn's base power is doubled if it attacks before the target")
{
    GIVEN {
        PLAYER(SPECIES_SCOLIPEDE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RUTHLESS_HORNS); }
    } SCENE {
        
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RUTHLESS_HORNS, player);

        
        
    } 
}