#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Flaming Scales reduce power of opposing Fire moves for Partner", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_HYPER_CUTTER; }
    PARAMETRIZE { ability = ABILITY_FLAMING_SCALES; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_FLETCHLING);
        OPPONENT(SPECIES_FLETCHLING);
    } WHEN {
        TURN { MOVE(opponentRight, MOVE_HEAT_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAT_WAVE, opponentRight);
        HP_BAR(playerRight, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage);
    }
}

DOUBLE_BATTLE_TEST("Flaming Scales reduce power of opposing Fire moves for User", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_HYPER_CUTTER; }
    PARAMETRIZE { ability = ABILITY_FLAMING_SCALES; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_FLETCHLING);
        OPPONENT(SPECIES_FLETCHLING);
    } WHEN {
        TURN { MOVE(opponentRight, MOVE_HEAT_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAT_WAVE, opponentRight);
        HP_BAR(playerLeft, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage);
    }
}