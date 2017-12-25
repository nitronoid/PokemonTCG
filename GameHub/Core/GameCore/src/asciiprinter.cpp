#include "asciiprinter.h"

void AsciiPrinter::init()
{
    for(unsigned i=0; i<m_width; ++i)
    {
        m_line.push_back('=');
    }
    for(unsigned i=0; i<m_slotWidth; ++i)
    {
        if(i==0 || i==m_slotWidth)
        {
            m_slotCardLine.push_back('*');
        }
        else
        {
            m_slotCardLine.push_back('-');
        }
    }
    for(unsigned i=0; i<m_slotWidth; ++i)
    {
        if(i==0 || i==m_slotWidth)
        {
            m_slotCardLineMid.push_back('|');
        }
        else
        {
            m_slotCardLineMid.push_back('-');
        }
    }
    for(unsigned i=0; i<m_handWidth; ++i)
    {
        if(i==0 || i==m_handWidth)
        {
            m_handLine.push_back('*');
        }
        else
        {
            m_handLine.push_back('-');
        }
    }
}

void AsciiPrinter::init(char _blank)
{
    init();
    m_emptyChar = _blank;
}

void AsciiPrinter::drawBoard(Board *_board)
{
    std::cout<<m_line<<std::endl;
    std::vector<unsigned> opPrize = getPrizeCards(_board);
    for(unsigned m=0; m<3; ++m)
    {
        for(unsigned i=0; i<opPrize.size(); ++i)
        {
            if(opPrize.at(i) == 1)
            {
                std::cout<<m_prizeCardLine1;
            }
            else
            {
                std::cout<<"`````";
            }
            if(i == opPrize.size()-1) std::cout<<m_emptyChar;
        }
        std::cout<<std::endl;
    }
    std::cout<<m_line<<std::endl;

}

std::vector<std::string> AsciiPrinter::getSlotCardLines(std::unique_ptr<BoardSlot> _slot)
{
    unsigned id = _slot->active()->getID();
    unsigned hp = _slot->active()->hp();
    std::string name = _slot->active()->getName();
    std::string pType;
    pType.push_back(charify(_slot->active()->type()));
    unsigned energ = _slot->numEnergy();
    std::string tool = _slot->viewTool()->getName();
    std::vector<std::vector<std::string>> attackInfo;
    for(unsigned o=0; o<_slot->active()->attacks().size(); ++o)
    {
        std::vector<std::string> temp;
        temp.push_back(_slot->active()->attacks().at(o).name());
        temp.push_back("NA");
        std::string tmp;
        for(unsigned p=0; p<_slot->active()->attacks().at(o).requirements().size(); ++p)
        {
            tmp.push_back(charify(_slot->active()->attacks().at(o).requirements().at(p)));
        }
        temp.push_back(tmp);
        attackInfo.push_back(temp);
    }
    unsigned retreat = _slot->active()->retreatCost();
    std::string weak;
    weak.push_back(charify(_slot->active()->weakness()));
    std::string res;
    res.push_back(charify(_slot->active()->resistance()));
    std::string conditions;
    for(unsigned r=0; r<_slot->conditions().size(); ++r)
    {
        conditions.push_back(charify(_slot->conditions().at(r)));
    }
    std::vector<std::string> allLines;
    return allLines;
}

std::vector<std::string> AsciiPrinter::getPokemonCardLines(std::unique_ptr<PokemonCard> _card)
{
    std::vector<std::string> allLines;
    return allLines;
}

std::vector<std::string> AsciiPrinter::getEnergyCardLines(std::unique_ptr<EnergyCard> _card)
{
    std::vector<std::string> allLines;
    return allLines;
}

std::vector<std::string> AsciiPrinter::getToolCardLines(std::unique_ptr<TrainerCard> _card)
{
    std::vector<std::string> allLines;
    return allLines;
}

std::vector<unsigned> AsciiPrinter::getPrizeCards(Board *_board)
{
    std::vector<unsigned> ret;
    return ret;
}

char AsciiPrinter::charify(PTCG::TYPE _in)
{
    char ret;
    switch(_in)
    {
    case PTCG::TYPE::COLOURLESS : {ret='C'; break;}
    case PTCG::TYPE::DARKNESS : {ret='D'; break;}
    case PTCG::TYPE::DRAGON : {ret='N'; break;}
    case PTCG::TYPE::FAIRY : {ret='Y'; break;}
    case PTCG::TYPE::FIGHTING : {ret='F'; break;}
    case PTCG::TYPE::FIRE : {ret='R'; break;}
    case PTCG::TYPE::GRASS : {ret='G'; break;}
    case PTCG::TYPE::LIGHTNING : {ret='L'; break;}
    case PTCG::TYPE::METAL : {ret='M'; break;}
    case PTCG::TYPE::PSYCHIC : {ret='P'; break;}
    case PTCG::TYPE::WATER : {ret='W'; break;}
    case PTCG::TYPE::ERROR : {ret='-'; break;}
    default : break;
    }
    return ret;
}

char AsciiPrinter::charify(PTCG::CONDITION _in)
{
    char ret;
    switch(_in)
    {
    case PTCG::CONDITION::ASLEEP : {ret='A'; break;}
    case PTCG::CONDITION::BURNED : {ret='B'; break;}
    case PTCG::CONDITION::CONFUSED : {ret='C'; break;}
    case PTCG::CONDITION::PARALYZED : {ret='R'; break;}
    case PTCG::CONDITION::POISONED : {ret='P'; break;}
    default : break;
    }
    return ret;
}
