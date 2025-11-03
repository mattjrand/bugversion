#include "global.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Puppet Master doubles HP of created substitute")
{
    GIVEN {
        PLAYER(SPECIES_ACCELGOR) { HP(100); MaxHP(100); Ability(ABILITY_PUPPET_MASTER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SUBSTITUTE); }
        TURN { MOVE(opponent, MOVE_DRAGON_RAGE);}
        TURN { MOVE(opponent, MOVE_DRAGON_RAGE);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, player);
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, opponent);
        NOT HP_BAR(player);
        
    }
}

SINGLE_BATTLE_TEST("Puppet Master doesn't affect substitute when not in use")
{
    GIVEN {
        PLAYER(SPECIES_ACCELGOR) { HP(100); MaxHP(100);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SUBSTITUTE); }
        TURN { MOVE(opponent, MOVE_DRAGON_RAGE);}
        TURN { MOVE(opponent, MOVE_DRAGON_RAGE);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, player);
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, opponent);
        MESSAGE("The substitute took damage for Accelgor!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, opponent);
        HP_BAR(player);
        
    }
}