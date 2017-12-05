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

enum class PHASE {
    DRAW,
    MAIN,
    ATTACK,
    NONE
};

enum class DURATION {
    SINGLE,
    MULTIPLE,
    PERMANENT
};

enum class CARD {
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
    BENCH,
    PRIZE
};

enum class ACTION {
    DRAW,
    DISCARD,
    PLAY,
    VIEW
};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

}

#endif // POKEMONENUMS_H
