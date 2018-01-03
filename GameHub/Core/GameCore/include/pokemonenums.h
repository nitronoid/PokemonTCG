
#ifndef POKEMONENUMS_H
#define POKEMONENUMS_H

namespace PTCG
{
enum class TYPE {
  COLOURLESS,
  FIGHTING,
  LIGHTNING,
  GRASS,
  PSYCHIC,
  METAL,
  WATER,
  DARKNESS,
  FIRE,
  DRAGON,
  FAIRY,
  ERROR
};

enum class CONDITION {
  ASLEEP,
  BURNED,
  POISONED,
  CONFUSED,
  PARALYZED
};

enum class TRIGGER {
  NOW,
  ATTACK,
  END,
  NONE
};

enum class DURATION {
  SINGLE,
  MULTIPLE,
  PERMANENT
};

enum class CARD {
  ENERGY,
  POKEMON,
  ITEM,
  TOOL,
  SUPPORT,
  STADIUM
};

enum class PLAYER {
  SELF,
  ENEMY
};

enum class PILE {
  DECK,
  HAND,
  DISCARD,
  PRIZE
};

enum class ACTION {
  DRAW,
  DISCARD,
  PLAY,
  VIEW,
  MOVE,
  HEAL
};

enum class ORDER {
  BEFORE,
  AFTER
};

}

#endif // POKEMONENUMS_H
