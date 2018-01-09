#ifndef ASCIICARDS_H
#define ASCIICARDS_H

static constexpr auto k_bigPokeSlot = R"(
,=============================================================,
|| STAGE $ST  //   $NAME$$$$$$$$$$$$$$$$$$$        [HP:$HP$$]||
||===========*'                          TYPE: $T$$$$$$$$$$$ ||
|| EVOLVES FROM $EVU$$$$$$$$$$$$$$                           ||
|| NEXT EVOLUTION $EVO$$$$$$$$$$$$$$                         ||
|| ENERGY ATTACHED: $Ex                                      ||
|| TOOL ATTACHED: $TOOL$$$$$$                                ||
||-----------------------------------------------------------||
|| ($AR0)            $A0$$$$$$$$$$$$$$$                 $D0$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| ($AR1)            $A1$$$$$$$$$$$$$$$                 $D1$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| ($AR2)            $A2$$$$$$$$$$$$$$$                 $D2$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
|| $TXT$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ||
||-----------------------------------------------------------||
||       ??STATUS: $STU$$??       //                      || ||
|| ------------------------------//  $COND$$$$$$$$$$$$$   || ||
|| WEAKNESS    RESISTANCE       //   $COND$$$$$$$$$$$$$   || ||
||   $WT$         $RT$         //    $COND$$$$$$$$$$$$$  .=' ||
||   x$WA$        x$RA$       //     $COND$$$$$$$$$$$$$ .=/  ||
|| --------------------------//                       .=='   ||
||                          '=========================*"`    ||
|| RETREAT  $RET$  x$REA$                                    ||
|| [ DECK $DK$$$$$$$$$$$$$$$$$$$$$$$$  ]        [ID:$ID/149] ||
'=============================================================')";

static constexpr auto k_sentinelSlot = R"(
*[$ID/149][$RH/$HPhp]*
| $NAME$$$$$$$$ [$T] |
| Energy: $Ex        |
| Tool: $TOOL$$$$$$  |
|--------------------|
| $A0$$$ $D0$ ($AR0) |
| $A1$$$ $D1$ ($AR1) |
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
|$D0$     $AR0|
|$A1$$$$$     |
|$D1$     $AR1|
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
|     \.      |
|     | "     |
| .  *   }  , |
| |\'  . *.'/ |
| \   /|   {  |
|  \ {  \  './|
| \.\'   "* / |
|  '*_____*'  |
*-------------*)";

static constexpr auto k_leafCard = R"(
*---[ENERG]---*
|     /|\     |
|    / | \    |
|   / \|/ \   |
|  / \ | / \  |
| | \ \|/ / | |
| \  \ | /  / |
|  `__\|/__`  |
|     |||     |
*-------------*)";

static constexpr auto k_waterCard = R"(
*---[ENERG]---*
|       ____  |
|     **'`    |
|   *'  |     |
|  /     *_   |
| |        '. |
| '  *``*   } |
|  \{    }  / |
|   '*__*_*'  |
*-------------*)";

#endif // ASCIICARDS_H
