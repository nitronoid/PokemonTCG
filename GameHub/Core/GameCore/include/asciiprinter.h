#ifndef ASCIIPRINTER_H
#define ASCIIPRINTER_H
#include "guimodule.h"
#include <vector>
#include <string>

class AsciiPrinter : public GuiModule
{
public :
    AsciiPrinter() = default;

    void init(); //default
    void init(char _blank); //change symbol for empty spaces

    virtual void drawBoard(Board* _board) override;
    virtual void drawBoard(Board* _board, const bool _isOp=false) override;
private :
    std::vector<std::string> getSlotCardLines(std::unique_ptr<BoardSlot> _slot);
    std::vector<std::string> getPokemonCardLines(std::unique_ptr<PokemonCard> _card);
    std::vector<std::string> getEnergyCardLines(std::unique_ptr<EnergyCard> _card);
    std::vector<std::string> getToolCardLines(std::unique_ptr<TrainerCard> _card);

    char charify(PTCG::TYPE _in);
    char charify(PTCG::CONDITION _in);

    std::array<unsigned,6> getPrizeCards(Board *_board);
    std::array<unsigned,6> getSlots(Board* _board);

    const unsigned m_width = 128;
    const unsigned m_slotWidth = 20;
    const unsigned m_handWidth = 12;
    const unsigned m_prizeWidth = 5;
    char m_emptyChar = '`';
    std::vector<std::string> m_printout;
    std::string m_line;
    std::string m_slotCardLine;
    std::string m_slotCardLineMid;
    std::string m_handLine;
    std::string m_prizeCardLine1 = "*---*";
    std::string m_prizeCardLine2 = "|`@`|";
    std::string m_energyPart1 = "|``````````|";
    std::string m_energyPart2 = "|``|====/``|";
    std::string m_energyPart3 = "|``|===/```|";
    std::string m_energyPart4 = "|````/=/```|";
    std::string m_energyPart5 = "|```//`````|";
};

#endif // ASCIIPRINTER_H