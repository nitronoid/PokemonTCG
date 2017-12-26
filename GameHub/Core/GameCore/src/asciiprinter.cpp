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
    std::cout<<"TODO SLOTS"<<std::endl;
    std::cout<<m_line<<std::endl;
    std::cout<<"TODO HAND"<<std::endl;
    std::cout<<m_line<<std::endl;
    std::array<unsigned,6> opPrize = getPrizeCards(_board);
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

void AsciiPrinter::drawBoard(Board* _board, const bool _isOp)
{
    if(_isOp)
    {
        std::cout<<"TODO OPPONENT"<<std::endl;
    }
    else
    {
        std::cout<<"TODO SELF"<<std::endl;
    }
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
    std::vector<std::string> allLines(12,"");
    //LINE NO.0
    allLines.at(0).append("*["+std::to_string(id)+"]");
    std::string hpStr;
    hpStr.append('['+std::to_string(hp)+"hp]*");
    unsigned lineSize=m_slotWidth-allLines.at(0).size()-hpStr.size();
    for(unsigned t=0; t<lineSize; ++t) allLines.at(0).push_back('-');
    allLines.at(0).append(hpStr);
    //LINE NO.1
    allLines.at(1).append("| ");
    int len = m_slotWidth - (name.size()+2+pType.size()+3);
    if(len >= 0)
    {
        allLines.at(1).append(name);
        for(int g=0; g<len; ++g)
        {
            allLines.at(1).push_back(' ');
        }
    }
    else
    {
        for(unsigned j=0; j<name.size()+len; ++j)//in this case len will be negative so it would subtract from name length
        {
            allLines.at(1).push_back(name.at(j));
        }
    }
    allLines.at(1).append('['+pType+"]|");
    //LINE NO.2
    allLines.at(2).append("| Energy: "+energ+'x');
    unsigned lnSz0 = m_slotWidth - (1+allLines.at(2).size());
    for(unsigned f=0; f<lnSz0; ++f)
        allLines.at(2).push_back(' ');
    allLines.at(2).push_back('|');
    //LINE NO.3
    allLines.at(3).append("| Tool: ");
    int tSize = m_slotWidth - (tool.size()+allLines.at(3).size()+1);
    if(tSize < 0)
    {
        for(int u=0; u<(int)(tool.size()+tSize); ++u)
            allLines.at(3).push_back(tool.at(u));
    }
    else
    {
        allLines.at(3).append(tool);
        for(int k=0; k<tSize; ++k)
            allLines.at(3).push_back(' ');
    }
    allLines.at(3).push_back('|');
    //LINE NO.4
    allLines.at(4).append(m_slotCardLineMid);
    //LINE NO.5,6,7,8
    for(unsigned i=0; i<4; ++i)
    {
        allLines.at(i+5).append("| ");
        int lnSz1 = m_slotWidth - (7+attackInfo.at(i).at(0).size()+attackInfo.at(i).at(1).size()+attackInfo.at(i).at(2).size());
        if(lnSz1 < 0) //too long name
        {
            for(int y=0; y<(int)(attackInfo.at(i).at(0).size()+lnSz1); ++y) //lnSz1 negative
                allLines.at(i+5).push_back(attackInfo.at(i).at(0).at(y));
            allLines.at(i+5).append(' '+attackInfo.at(i).at(1)+" ("+attackInfo.at(i).at(2)+')');
        }
        else //all good
        {
            allLines.at(i+5).append(attackInfo.at(i).at(0)+' '+attackInfo.at(i).at(1)+" ("+attackInfo.at(i).at(2)+')');
            for(int u=0; u<lnSz1; ++u)
                allLines.at(i+5).push_back(' ');
        }
        allLines.at(i+5).push_back('|');
    }
    //LINE NO.9
    allLines.at(9).append(m_slotCardLineMid);
    //LINE NO.10
    allLines.at(10).append("|["+retreat+']');
    unsigned lnSz2 = m_slotWidth - (allLines.at(10).size()+5+weak.size()+res.size());
    unsigned diff = lnSz2%2;
    for(unsigned a=0; a<lnSz2/2+diff; ++a)
        allLines.at(10).push_back(' ');
    allLines.at(10).append('['+weak+']');
    for(unsigned b=0; b<lnSz2/2; ++b)
        allLines.at(10).push_back(' ');
    allLines.at(10).append('['+res+"]|");
    //LINE NO.11
    allLines.at(11).append("|["+conditions+']');
    unsigned lnSz3 = m_slotWidth - (allLines.at(11).size() + 1);
    for(unsigned i=0; i<lnSz3; ++i)
        allLines.at(11).push_back(' ');
    allLines.at(11).push_back('|');
    //LINE NO.12
    allLines.at(12).append(m_slotCardLine);
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

std::array<unsigned,6> AsciiPrinter::getPrizeCards(Board *_board)
{
    std::array<unsigned,6> ret;
    for(int i=0; i<6; ++i)
    {
        if(_board->m_prizeCards.view().at(i) != nullptr)
        {
            ret.at(i)=1;
        }
        else
        {
            ret.at(i)=0;
        }
    }
    return ret;
}

std::array<unsigned,6> getSlots(Board* _board)
{
    std::array<unsigned,6> ret;
    for(int i=0; i<6; ++i)
    {

        if(_board->m_bench.view().at(i).active() != nullptr)
        {
            ret.at(i)=1;
        }
        else
        {
            ret.at(i)=0;
        }
    }
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
    default : {ret='-'; break;}
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
    default : {ret='-'; break;}
    }
    return ret;
}
