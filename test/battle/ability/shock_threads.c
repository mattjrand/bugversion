#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Shock threads damages the attacker by 1/8")
{
    s16 shockthreadsDamage;

    GIVEN {
        PLAYER(SPECIES_GALVANTULA) { Ability(ABILITY_SHOCK_THREADS); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_STRING_SHOT);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STRING_SHOT, player);
        HP_BAR(opponent, captureDamage: &shockthreadsDamage);
    } THEN {
        EXPECT_EQ(shockthreadsDamage, opponent->maxHP / 8);
    }
}
