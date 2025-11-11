#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Friend Guard (but not Queenly Majesty) reduces damage by 25 percent for user", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_HYPER_CUTTER; }
    PARAMETRIZE { ability = ABILITY_FRIEND_GUARD; }
    PARAMETRIZE { ability = ABILITY_QUEENLY_MAJESTY; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); };
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SURF); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, playerLeft);
        HP_BAR(opponentLeft, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.75), results[1].damage);
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[2].damage);
    }
}

DOUBLE_BATTLE_TEST("Friend Guard and Queenly Majesty reduces damage by 25 percent for ally", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_HYPER_CUTTER; }
    PARAMETRIZE { ability = ABILITY_FRIEND_GUARD; }
    PARAMETRIZE { ability = ABILITY_QUEENLY_MAJESTY; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); };
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SURF); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, playerLeft);
        HP_BAR(opponentRight, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.75), results[1].damage);
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.75), results[2].damage);
    }
}