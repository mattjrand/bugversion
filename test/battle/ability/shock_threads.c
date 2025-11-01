#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Shock threads damages foe by 1/8 hp only when Speed is lowered. Does not affect user.")
{
    s16 shockthreadsDamage;

    GIVEN {
        PLAYER(SPECIES_GALVANTULA) { Ability(ABILITY_SHOCK_THREADS); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_GROWL); MOVE(opponent, MOVE_STRING_SHOT);}
        TURN {MOVE(player, MOVE_STRING_SHOT);}
    } SCENE {
        HP_BAR(opponent, captureDamage: &shockthreadsDamage);
    } THEN {
        EXPECT_EQ(shockthreadsDamage, opponent->maxHP / 8);
        EXPECT_EQ(player->hp, player->maxHP);
    }
}

DOUBLE_BATTLE_TEST("Shock threads damages both opponents in a double battle. Also affects partner's speed lowering moves.")
{
        s16 shockthreadsDamage1;
        s16 shockthreadsDamage2;

    GIVEN {
        PLAYER(SPECIES_GALVANTULA) { Ability(ABILITY_SHOCK_THREADS); };
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) {HP(80);};
        OPPONENT(SPECIES_AGGRON) {HP(80);};
    } WHEN {
        TURN {MOVE(playerRight, MOVE_SCARY_FACE, target: opponentLeft);}
        TURN {MOVE(playerRight, MOVE_SCARY_FACE, target: opponentRight);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCARY_FACE, playerRight);
        HP_BAR(opponentLeft, captureDamage: &shockthreadsDamage1);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCARY_FACE, playerRight);
        HP_BAR(opponentRight, captureDamage: &shockthreadsDamage2);
    } THEN {
        EXPECT_EQ(shockthreadsDamage1, opponentLeft->maxHP / 8);
        EXPECT_EQ(shockthreadsDamage2, opponentRight->maxHP / 8);
    }
}
