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
    void pokemonStr(std::string &_str, PokemonCard * const _card) const;
    std::string bigSlotStr(BoardSlot* const _slot, Status *const _activeStatus) const;
    std::string slotStr(BoardSlot* const _slot) const;
    std::string activeStr(BoardSlot* const _activeSlot, Status * const _activeStatus) const;
    std::string benchStr(Bench * const _bench) const;
    std::string handStr(Hand * const _hand) const;
    std::string cardStr(Card * const _card) const;
    std::string energyCardStr(EnergyCard * const _card) const;
    std::string pokemonCardStr(PokemonCard * const _card) const;
    std::string trainerCardStr(TrainerCard * const _card, const std::string &_type) const;
    std::string prizeStr(PrizeCards * const _prize) const;
};

#endif // SIMPLEPRINTER_H
