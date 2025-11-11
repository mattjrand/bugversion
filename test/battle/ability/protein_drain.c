#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Protein Drain boosts ATK and DEF after using a draining move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET){ Ability(ABILITY_PROTEIN_DRAIN); };
        OPPONENT(SPECIES_BURMY);
    } WHEN {
        TURN { MOVE(player, MOVE_ABSORB); }
        TURN { MOVE(player, MOVE_ABSORB); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ABSORB, player);
        MESSAGE("Wobbuffet's Attack rose!");
        MESSAGE("Wobbuffet's Defense rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ABSORB, player);
        NONE_OF {MESSAGE("Wobbuffet's Attack rose!");
        MESSAGE("Wobbuffet's Defense rose!");}
}
}