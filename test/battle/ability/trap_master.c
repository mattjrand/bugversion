#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Trap Master add two layers of Toxic Spikes")
{
    GIVEN {
        PLAYER(SPECIES_ACCELGOR) { Ability(ABILITY_TRAP_MASTER); }
        OPPONENT(SPECIES_GLACEON);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TOXIC_SPIKES); }
        TURN {SWITCH(opponent, 1);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC_SPIKES, player);
        MESSAGE("The opposing Wobbuffet was badly poisoned!");
    }
}

SINGLE_BATTLE_TEST("Trap Master add two layers of Spikes", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_HYPER_CUTTER; }
    PARAMETRIZE { ability = ABILITY_TRAP_MASTER; }
    GIVEN {
        PLAYER(SPECIES_ACCELGOR) { Ability(ability); }
        OPPONENT(SPECIES_GLACEON);
        OPPONENT(SPECIES_WOBBUFFET) { HP(48); MaxHP(48);}
    } WHEN {
        TURN { MOVE(player, MOVE_SPIKES); }
        TURN {SWITCH(opponent, 1);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPIKES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        HP_BAR(opponent, captureDamage: &results[i].damage);
        MESSAGE("The opposing Wobbuffet was hurt by the spikes!");

    } FINALLY{
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(0.75), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Trap Master extends duration of Room moves")
{
    GIVEN {
        PLAYER(SPECIES_ACCELGOR) { Speed(100); Ability(ABILITY_TRAP_MASTER); }
        OPPONENT(SPECIES_WOBBUFFET) {Speed(25);};
    } WHEN {
        TURN { MOVE(player, MOVE_TRICK_ROOM); }
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}

    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TRICK_ROOM, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        
    }
}

SINGLE_BATTLE_TEST("Trap Master extends duration of Sport moves")
{
    GIVEN {
        PLAYER(SPECIES_ACCELGOR) {Ability(ABILITY_TRAP_MASTER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_SPORT); }
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}

    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_SPORT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);        
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        MESSAGE("The effects of Water Sport have faded.");
        
    }
}