#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Insectivore increases the power of Grass moves against Bug types", s16 damage)
{
    u32 move;
    u16 ability;
    PARAMETRIZE { move = MOVE_VINE_WHIP; ability = ABILITY_INSECTIVORE; }
    PARAMETRIZE { move = MOVE_VINE_WHIP; ability = ABILITY_STEADFAST; }
    PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_INSECTIVORE; }
    PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_STEADFAST; }

    GIVEN {
        PLAYER(SPECIES_BELLSPROUT) { Ability(ability); }
        OPPONENT(SPECIES_BURMY);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(4), results[0].damage); // Sharpness affects slicing moves
        EXPECT_EQ(results[2].damage, results[3].damage); // Sharpness does not affect non-slicing moves
    }
}
