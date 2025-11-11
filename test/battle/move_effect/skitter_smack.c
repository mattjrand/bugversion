#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_PROTECT) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_DETECT) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_KINGS_SHIELD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_SILK_TRAP) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_SPIKY_SHIELD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_WIDE_GUARD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_QUICK_GUARD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_CRAFTY_SHIELD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_BANEFUL_BUNKER) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_BURNING_BULWARK) == EFFECT_PROTECT);
    ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveMakesContact(MOVE_SCRATCH));
    ASSUME(GetMoveCategory(MOVE_LEER) == DAMAGE_CATEGORY_STATUS);
    ASSUME(GetMoveCategory(MOVE_WATER_GUN) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(!(MoveMakesContact(MOVE_WATER_GUN)));
}

SINGLE_BATTLE_TEST("Skitter Smack hits through all protect moves")
{
    u32 j;
    static const u16 protectMoves[] = {
        MOVE_PROTECT,
        MOVE_DETECT,
        MOVE_SPIKY_SHIELD,
        MOVE_BANEFUL_BUNKER,
        MOVE_BURNING_BULWARK,
    };
    u16 protectMove = MOVE_NONE;
    u16 usedMove = MOVE_NONE;

    for (j = 0; j < ARRAY_COUNT(protectMoves); j++)
    {
        PARAMETRIZE { protectMove = protectMoves[j]; usedMove = MOVE_SKITTER_SMACK; }
    }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, protectMove); MOVE(player, usedMove); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, protectMove, opponent);
        MESSAGE("The opposing Wobbuffet protected itself!");
        ANIMATION(ANIM_TYPE_MOVE, usedMove, player);
        MESSAGE("The opposing Wobbuffet fell for the feint!");
        NOT HP_BAR(opponent);
    }
}