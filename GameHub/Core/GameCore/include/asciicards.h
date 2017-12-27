#ifndef ASCIICARDS_H
#define ASCIICARDS_H

static constexpr auto k_sentinelSlot = R"(
*[$ID/149]----[$HPhp]*
| $NAME$$$$$$$$ [$T] |
| Energy: $Ex        |
| Tool: $TOOL$$$$$$  |
|--------------------|
| $A0$$$$ $D0 ($AR0) |
| $A1$$$$ $D1 ($AR1) |
|--------------------|
| [$W]   [$R]   [$C] |
| [$STATUS$$$$$$$$$] |
*--------------------*
                     )";
static constexpr auto k_blankSlot = R"(
*--------------------*
|                    |
|                    |
|                    |
|                    |
|         --         |
|                    |
|                    |
|                    |
|                    |
*--------------------*
                     )";
static constexpr auto k_sentinelPokemonCard = R"(
*---[$TYPE]---*
|$NAME$  [$HP]|
|         [$T]|
|$A0$$$$$     |
|$D0      $AR0|
|$A1$$$$$     |
|$D1      $AR1|
|[$W]     [$R]|
|[$C]         |
*-------------*
                     )";
static constexpr auto k_blankCard = R"(
*---[BLANK]---*
|             |
|             |
|             |
|             |
|      -      |
|             |
|             |
|             |
*-------------*
                     )";
static constexpr auto k_sentinelTrainerCard = R"(
*---[$TYPE]---*
|$NAME$$$$$$$$|
|             |
|             |
|  ---------  |
|  |TRAINER|  |
|  ---------  |
|             |
|             |
*-------------*
                     )";

static constexpr auto k_electricCard = R"(
*---[ENERG]---*
|      /=====/|
|     /====/  |
|    /===/    |
|      /====/ |
|     /===/   |
|    /==/     |
|   /=/       |
|  /          |
*-------------*
                    )";

#endif // ASCIICARDS_H
