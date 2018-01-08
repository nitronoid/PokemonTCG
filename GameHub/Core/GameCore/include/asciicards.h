#ifndef ASCIICARDS_H
#define ASCIICARDS_H

static constexpr auto k_bigPokeSlot = R"(
*=============================================================*
|| STAGE $ST  //   $NAME$$$$$$$$$$$$$$$$$$$        [HP:$hp$$]||
||===========//                          TYPE: $T$$$$$$$$$$$ ||
|| EVOLVES FROM $EV$$$$$$$$$$$$$$$                           ||
|| ENERGY ATTACHED: $Ex                                      ||
|| TOOL ATTACHED: $TOOL$$$$$$                                ||
||-----------------------------------------------------------||
|| ($AR0)            $A0$$$$$$$$$$$$$$$                 $D0$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| ($AR0)            $A0$$$$$$$$$$$$$$$                 $D0$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| ($AR0)            $A0$$$$$$$$$$$$$$$                 $D0$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                                           ||
||                                              [ID:$ID/149] ||
*=============================================================*)";

this attack does 20 dmamage to each of your opponentss pokemon (donnt apply weakness and resistance for benched pokemon).

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
*--------------------*)";
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
*--------------------*)";
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
*-------------*)";
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
*-------------*)";
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
*-------------*)";
static constexpr auto k_prizeCard = R"(
*---*
| ? |
*---*)";
static constexpr auto k_emptyPrize = R"(
-----
-----
-----)";

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
*-------------*)";
static constexpr auto k_fireCard = R"(
*---[ENERG]---*
|     |\      |
|  |\ \ \ /|  |
|  / \/    /  |
|  \    /| \  |
|   |/| \ \ | |
|  / \ \/  || |
|  \  \   //  |
|   -------   |
*-------------*)";
static constexpr auto k_leafCard = R"(
*---[ENERG]---*
|     /|\     |
|    /_|_\    |
|   /  |  \   |
|  | __|__ |  |
|  |   |   |  |
|   \ _|_ /   |
|    \ | /    |
|     | |     |
*-------------*)";
static constexpr auto k_waterCard = R"(
*---[ENERG]---*
|             |
|    //       |
|  /  |       |
| |    \__    |
| |        \  |
| |    _    | |
|  \  |_|  /  |
|    -----    |
*-------------*)";

#endif // ASCIICARDS_H
