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
    switch(_slot->active()->type())
    {
    case PTCG::TYPE::COLOURLESS : {pType.push_back('C'); break;}
    case PTCG::TYPE::DARKNESS : {pType.push_back('D'); break;}
    case PTCG::TYPE::DRAGON : {pType.push_back('N'); break;}
    case PTCG::TYPE::FAIRY : {pType.push_back('Y'); break;}
    case PTCG::TYPE::FIGHTING : {pType.push_back('F'); break;}
    case PTCG::TYPE::FIRE : {pType.push_back('R'); break;}
    case PTCG::TYPE::GRASS : {pType.push_back('G'); break;}
    case PTCG::TYPE::LIGHTNING : {pType.push_back('L'); break;}
    case PTCG::TYPE::METAL : {pType.push_back('M'); break;}
    case PTCG::TYPE::PSYCHIC : {pType.push_back('P'); break;}
    case PTCG::TYPE::WATER : {pType.push_back('W'); break;}
    case PTCG::TYPE::ERROR : {pType.push_back('-'); break;}
    default : break;
    }
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
            switch(_slot->active()->attacks().at(o).requirements().at(p))
            {
            case PTCG::TYPE::COLOURLESS : {tmp.push_back('C'); break;}
            case PTCG::TYPE::DARKNESS : {tmp.push_back('D'); break;}
            case PTCG::TYPE::DRAGON : {tmp.push_back('N'); break;}
            case PTCG::TYPE::FAIRY : {tmp.push_back('Y'); break;}
            case PTCG::TYPE::FIGHTING : {tmp.push_back('F'); break;}
            case PTCG::TYPE::FIRE : {tmp.push_back('R'); break;}
            case PTCG::TYPE::GRASS : {tmp.push_back('G'); break;}
            case PTCG::TYPE::LIGHTNING : {tmp.push_back('L'); break;}
            case PTCG::TYPE::METAL : {tmp.push_back('M'); break;}
            case PTCG::TYPE::PSYCHIC : {tmp.push_back('P'); break;}
            case PTCG::TYPE::WATER : {tmp.push_back('W'); break;}
            case PTCG::TYPE::ERROR : {tmp.push_back('-'); break;}
            default : break;
            }
        }
        temp.push_back(tmp);
        attackInfo.push_back(temp);
    }
    unsigned retreat = _slot->active()->retreatCost();
    std::string weak;
    switch(_slot->active()->weakness())
    {
    case PTCG::TYPE::COLOURLESS : {weak.push_back('C'); break;}
    case PTCG::TYPE::DARKNESS : {weak.push_back('D'); break;}
    case PTCG::TYPE::DRAGON : {weak.push_back('N'); break;}
    case PTCG::TYPE::FAIRY : {weak.push_back('Y'); break;}
    case PTCG::TYPE::FIGHTING : {weak.push_back('F'); break;}
    case PTCG::TYPE::FIRE : {weak.push_back('R'); break;}
    case PTCG::TYPE::GRASS : {weak.push_back('G'); break;}
    case PTCG::TYPE::LIGHTNING : {weak.push_back('L'); break;}
    case PTCG::TYPE::METAL : {weak.push_back('M'); break;}
    case PTCG::TYPE::PSYCHIC : {weak.push_back('P'); break;}
    case PTCG::TYPE::WATER : {weak.push_back('W'); break;}
    case PTCG::TYPE::ERROR : {weak.push_back('-'); break;}
    default : break;
    }
    std::string res;
    switch(_slot->active()->resistance())
    {
    case PTCG::TYPE::COLOURLESS : {res.push_back('C'); break;}
    case PTCG::TYPE::DARKNESS : {res.push_back('D'); break;}
    case PTCG::TYPE::DRAGON : {res.push_back('N'); break;}
    case PTCG::TYPE::FAIRY : {res.push_back('Y'); break;}
    case PTCG::TYPE::FIGHTING : {res.push_back('F'); break;}
    case PTCG::TYPE::FIRE : {res.push_back('R'); break;}
    case PTCG::TYPE::GRASS : {res.push_back('G'); break;}
    case PTCG::TYPE::LIGHTNING : {res.push_back('L'); break;}
    case PTCG::TYPE::METAL : {res.push_back('M'); break;}
    case PTCG::TYPE::PSYCHIC : {res.push_back('P'); break;}
    case PTCG::TYPE::WATER : {res.push_back('W'); break;}
    case PTCG::TYPE::ERROR : {res.push_back('-'); break;}
    default : break;
    }
    std::string conditions;
    for(unsigned r=0; r<_slot->conditions().size(); ++r)
    {
        switch(_slot->conditions().at(r))
        {
        case PTCG::CONDITION::ASLEEP : {conditions.push_back('A'); break;}
        case PTCG::CONDITION::BURNED : {conditions.push_back('B'); break;}
        case PTCG::CONDITION::CONFUSED : {conditions.push_back('C'); break;}
        case PTCG::CONDITION::PARALYZED : {conditions.push_back('R'); break;}
        case PTCG::CONDITION::POISONED : {conditions.push_back('P'); break;}
        default : break;
        }
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
