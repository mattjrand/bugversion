#include "global.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Heal Order heals the user by 1/2 of its HP and cures STATUS")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(80); HP(50); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_POISON_POWDER);}
        TURN { MOVE(player, MOVE_HEAL_ORDER); }
    } SCENE {
        s32 maxHP = GetMonData(&PLAYER_PARTY[0], MON_DATA_MAX_HP);
        MESSAGE("Wobbuffet was hurt by its poisoning!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_ORDER, player);
        HP_BAR(player, damage: -maxHP / 2);
        NOT MESSAGE("Wobbuffet was hurt by its poisoning!");
    }
}