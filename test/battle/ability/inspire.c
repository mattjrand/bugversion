#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Inspire raises partner's ATK and SPATK when user faints.")
{

    GIVEN {
        PLAYER(SPECIES_VOLTORB) { HP(1); Ability(ABILITY_INSPIRE); };
        PLAYER(SPECIES_ABRA)
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponentLeft, MOVE_SWIFT);}
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Swift!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, opponentLeft);
        MESSAGE("Voltorb fainted!");
        MESSAGE("Abra was inspired by their ally's final cry!");
        MESSAGE("Abra's Attack rose!");
        MESSAGE("Abra's Sp. Atk rose!");
    } 
}