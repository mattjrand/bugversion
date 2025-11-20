#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Intoxicating Scent infatuates opponents and reduces damage by a third", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_OBLIVIOUS; }
    PARAMETRIZE { ability = ABILITY_ARMOR_TAIL; }
    GIVEN {
        PLAYER(SPECIES_ABRA);
        PLAYER(SPECIES_CLEFAIRY) { Ability(ABILITY_INTOXICATING_SCENT);};
        OPPONENT(SPECIES_MAGNEMITE);
        OPPONENT(SPECIES_MAGNETON) {Ability(ability);};
    } WHEN {
        TURN { MOVE(opponentRight, MOVE_SWIFT); }

    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, opponentRight);
        HP_BAR(playerRight, captureDamage: &results[i].damage);
    } FINALLY{
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.67), results[1].damage);
    }
}