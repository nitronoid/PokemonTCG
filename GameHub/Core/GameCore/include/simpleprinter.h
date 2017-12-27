#ifndef SIMPLEPRINTER_H
#define SIMPLEPRINTER_H
#include "guimodule.h"

class SimplePrinter : public GuiModule
{
public :
    SimplePrinter() = default;
    virtual ~SimplePrinter(){}
    virtual void drawBoard(Board* _board, const bool _isOp) override;

private:
    std::string slotStr(BoardSlot* const _slot) const;
    std::string activeStr(BoardSlot* const _activeSlot) const;
    std::string benchStr(Bench * const _bench) const;
    std::string handStr(Hand * const _hand) const;
    std::string cardStr(Card * const _card) const;
    std::string pokemonCardStr(PokemonCard * const _card) const;

    static constexpr auto m_sentinelSlot = R"(
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
    static constexpr auto m_blankSlot = R"(
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
    static constexpr auto m_sentinelPokemonCard = R"(
*---[$TYPE]---*
|        [$HP]|
|$NAME$   [$T]|
|$A0$$$$$     |
|$D0      $AR0|
|$A1$$$$$     |
|$D1      $AR1|
|[$W]     [$R]|
|[$C]         |
*-------------*
                         )";
    static constexpr auto m_blankCard = R"(
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
};

#endif // SIMPLEPRINTER_H
