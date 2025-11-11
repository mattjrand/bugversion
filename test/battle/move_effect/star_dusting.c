#include "global.h"
#include "test/battle.h"


DOUBLE_BATTLE_TEST("Star Dusting increases critical hit ratio by 1 for ally")
{
    bool32 useStarDusting = 0;
    u32 genConfig = 0, chance = 0;
    for (u32 j = GEN_1; j <= GEN_9; j++) {
        PARAMETRIZE { genConfig = j; useStarDusting = FALSE; chance = j >= GEN_7 ? 24 : 16; } // 6.25% with Wobbuffet's base speed
        PARAMETRIZE { genConfig = j; useStarDusting = TRUE;  chance = 8; }  // 12.5% with Wobbuffet's base speed
    }
    PASSES_RANDOMLY(1, chance, RNG_CRITICAL_HIT);
    GIVEN {
        WITH_CONFIG(GEN_CONFIG_CRIT_CHANCE, genConfig);
        ASSUME(GetMoveCriticalHitStage(MOVE_SCRATCH) == 0);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {
            if (useStarDusting)
                MOVE(playerLeft, MOVE_STAR_DUSTING);
            MOVE(playerRight, MOVE_SCRATCH, target: opponentLeft);
        }
    } SCENE {
        if (useStarDusting) {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_STAR_DUSTING);
            MESSAGE("Wobbuffet is getting pumped!");
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, playerRight);
        MESSAGE("A critical hit!");
    }
}

DOUBLE_BATTLE_TEST("Star Dusting increases critical hit ratio by 1 for user")
{
    PASSES_RANDOMLY(1, 8, RNG_CRITICAL_HIT);
    GIVEN {
        ASSUME(GetMoveCriticalHitStage(MOVE_SCRATCH) == 0);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_STAR_DUSTING);}
        TURN { MOVE(playerLeft, MOVE_SCRATCH, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STAR_DUSTING);
        MESSAGE("Wobbuffet is getting pumped!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, playerLeft);
        MESSAGE("A critical hit!");
    }
}

DOUBLE_BATTLE_TEST("Star Dusting fails if critical hit stage was already increased by Focus Energy")
{
    GIVEN {
        ASSUME(GetMoveCriticalHitStage(MOVE_SLASH) == 1);
        ASSUME(GetMoveEffect(MOVE_FOCUS_ENERGY) == EFFECT_FOCUS_ENERGY);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_FOCUS_ENERGY); MOVE(playerRight, MOVE_STAR_DUSTING); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FOCUS_ENERGY, playerLeft);
        MESSAGE("But it failed!");
    }
}




