#include "global.h"
#include "test/battle.h"



SINGLE_BATTLE_TEST("Reflective Scales bounces status moves after the user's turn")
{
GIVEN {
        PLAYER(SPECIES_WYNAUT) { Speed(10); Ability(ABILITY_REFLECTIVE_SCALES);}
        OPPONENT(SPECIES_CHATOT) { Speed(1);};
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CHARM);}
    } SCENE {
         {

            MESSAGE("The opposing Chatot's Attack harshly fell!");
         }
        }
    }    


DOUBLE_BATTLE_TEST("Reflective Scales bounces status moves for partner that are used after the user's turn")
{

    GIVEN {
        PLAYER(SPECIES_WYNAUT) { Speed(10); Ability(ABILITY_REFLECTIVE_SCALES);}
        PLAYER(SPECIES_CHATOT) { Speed(1);};
        OPPONENT(SPECIES_WOBBUFFET) { Speed(15);};
        OPPONENT(SPECIES_MAROWAK) { Speed(5);};
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_CHARM, target: playerRight); MOVE(playerLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CHARM, target: playerRight);}
    } SCENE {
         {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_CHARM, opponentLeft);
            MESSAGE("Chatot's Attack harshly fell!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft);
            MESSAGE("The opposing Marowak's Attack harshly fell!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        }

    }
}