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

void AsciiPrinter::drawBoard(Board* _board, const bool _isOp)
{
    if(_isOp)
    {
        std::cout<<"TODO OPPONENT"<<std::endl;
        std::cout<<m_line<<std::endl;
        //DRAW PRIZE
        std::array<unsigned,6> opPrize = getPrizeCards(_board);
        drawPrize(opPrize);
        std::cout<<m_line<<std::endl;
        //DRAW SLOTS
        std::array<unsigned,6> opSlots = getSlots(_board);
        drawSlots(opSlots);
        std::cout<<"TODO SLOTS"<<std::endl;
        std::cout<<m_line<<std::endl;
    }
    else
    {
        std::cout<<"TODO SELF"<<std::endl;
        std::cout<<m_line<<std::endl;
        //DRAW SLOTS
        std::array<unsigned,6> mySlots = getSlots(_board);
        drawSlots(mySlots);
        std::cout<<"TODO SLOTS"<<std::endl;
        std::cout<<m_line<<std::endl;
        //DRAW HAND
        drawHand(_board->m_hand);
        std::cout<<"TODO HAND"<<std::endl;
        std::cout<<m_line<<std::endl;
        //DRAW PRIZE
        std::array<unsigned,6> myPrize = getPrizeCards(_board);
        drawPrize(myPrize);
        std::cout<<m_line<<std::endl;
    }
}

std::array<std::string,13> AsciiPrinter::getSlotCardLines(std::unique_ptr<BoardSlot> _slot)
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
    std::array<std::string,13> allLines;
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

std::array<std::string,10> AsciiPrinter::getPokemonCardLines(std::unique_ptr<PokemonCard> _card)
{
    std::array<std::string,10> allLines;
    std::vector<std::vector<std::string>> attackInfo;
    for(unsigned o=0; o<_card->attacks().size(); ++o)
    {
        std::vector<std::string> temp;
        temp.push_back(_card->attacks().at(o).name());
        temp.push_back("NA");
        std::string tmp;
        for(unsigned p=0; p<_card->attacks().at(o).requirements().size(); ++p)
        {
            tmp.push_back(charify(_card->attacks().at(o).requirements().at(p)));
        }
        temp.push_back(tmp);
        attackInfo.push_back(temp);
    }
    unsigned retreat = _card->retreatCost();
    std::string weak;
    weak.push_back(charify(_card->weakness()));
    std::string res;
    res.push_back(charify(_card->resistance()));

    //LINE NO.0
    allLines.at(0).append("*--[POKE]--*");
    //LINE NO.1
    std::string temp1 = std::to_string(_card->hp());
    int snLen1 = m_handWidth - (_card->getName().size()+2);
    if(snLen1 > 0) //all good
    {
        allLines.at(1).append("| "+_card->getName());
        for(int i=0; i<snLen1; ++i)
        {
            allLines.at(1).push_back(' ');
        }
    }
    else //name is too long
    {
        allLines.at(1).append("| "+_card->getName().substr(0,_card->getName().size()+snLen1));
    }
    allLines.at(1).push_back('|');
    //LINE NO.2
    allLines.at(2).append("| ["+temp1+"hp]");
    unsigned snLen0 = m_handWidth - (allLines.at(2).size()+1);
    for(unsigned l=0; l<snLen0; ++l)
        allLines.at(2).push_back(' ');
    allLines.at(2).push_back('|');
    //LINE NO.3,4,5,6
    unsigned attackNum = attackInfo.size();
    for(unsigned i=0; i<attackNum; ++i)
    {
        int snLen2 = m_handWidth - (attackInfo.at(i).at(0).size()+attackInfo.at(i).at(1).size()+attackInfo.at(i).at(2).size()+1);
        if(snLen2 >=0) //all good
        {
            allLines.at(i+3).append('|'+attackInfo.at(i).at(0).substr(0,(attackInfo.at(i).at(0).size()+snLen2)));
            for(int t=0; t<snLen2; ++t)
            {
                allLines.at(i+3).push_back(' ');
            }
        }
        else //too long name
        {
            allLines.at(i+3).append('|'+attackInfo.at(i).at(0).substr(0,(attackInfo.at(i).at(0).size()+snLen2))+' ');
        }
        allLines.at(i+3).append(attackInfo.at(i).at(1)+attackInfo.at(i).at(2)+'|');
    }
    if(attackNum < 4) //if not all 4 lines dedicated to attacks are filled
    {
        unsigned tmp4 = 4-attackNum;
        for(unsigned i=0; i<tmp4; ++i)
        {
            allLines.at(i+3+attackNum).push_back('|');
            for(unsigned f=0; f<(m_handWidth-2); ++f)
                allLines.at(i+3+attackNum).push_back(' ');
            allLines.at(i+3+attackNum).push_back('|');
        }
    }
    //LINE NO.7
    allLines.at(7).push_back('|');
    for(unsigned f=0; f<(m_handWidth-2); ++f)
        allLines.at(7).push_back('-');
    allLines.at(7).push_back('|');
    //LINE NO.8
    allLines.at(8).append('|'+std::to_string(retreat)+' '+weak+' '+res);
    unsigned snLine3 = m_handWidth - allLines.at(8).size();
    for(unsigned r=0; r<snLine3; ++r)
        allLines.at(8).push_back(' ');
    allLines.at(8).push_back('|');
    //LINE NO.9
    allLines.at(9).append(m_handLine);
    return allLines;
}

std::array<std::string,10> AsciiPrinter::getEnergyCardLines(std::unique_ptr<EnergyCard> _card)
{
    std::array<std::string,10> allLines;
    //LINE NO.0
    allLines.at(0).append("*--[ENRG]--*");
    //LINE NO.1
    allLines.at(1).append("|["+charify(_card->type())+']');
    std::string enVal = std::to_string(_card->amount());
    int enLin1 = m_handWidth - (allLines.at(1).size()+2+enVal.size());
    if(enLin1 >= 0) //all good
    {
        for(int y=0; y<enLin1; ++y)
            allLines.at(1).push_back('`');
        allLines.at(1).append('['+enVal+"]|");
    }
    else //value too big => error
    {
        for(unsigned u=allLines.at(1).size(); u<m_handWidth-1; ++u)
            allLines.at(1).push_back('#');
        allLines.at(1).push_back('|');
    }
    //LINE NO.2
    allLines.at(2).append(m_energyPart1);
    //LINE NO.3
    allLines.at(3).append(m_energyPart2);
    //LINE NO.4
    allLines.at(4).append(m_energyPart3);
    //LINE NO.5
    allLines.at(5).append(m_energyPart2);
    //LINE NO.6
    allLines.at(6).append(m_energyPart4);
    //LINE NO.7
    allLines.at(7).append(m_energyPart5);
    //LINE NO.8
    allLines.at(8).append(m_energyPart1);
    //LINE NO.9
    allLines.at(9).append(m_handLine);
    return allLines;
}

std::array<std::string,10> AsciiPrinter::getToolCardLines(std::unique_ptr<TrainerCard> _card)
{
    std::array<std::string,10> allLines;
    std::string trType;
    switch(_card->cardType())
    {
    case(PTCG::CARD::TOOL) : {trType="TOOL";break;}
    case(PTCG::CARD::ITEM) : {trType="ITEM";break;}
    case(PTCG::CARD::STADIUM) : {trType="STAD";break;}
    default : {trType="ERRO";break;}
    }
    //LINE NO.0
    allLines.at(0).append("*--[TRNR]--*");
    //LINE NO.1
    allLines.at(1).append("|["+trType+']');
    unsigned trLn1 = m_handWidth - (allLines.at(1).size()+1);
    for(unsigned i=0; i<trLn1; ++i)
        allLines.at(1).push_back(',');
    allLines.at(1).push_back('|');
    //LINE NO.2
    std::string trName = _card->getName();
    if(trName.size() > m_handWidth-2)
    {
        allLines.at(2).append('|'+trName.substr(0,m_handWidth-2)+'|');
    }
    else
    {
        allLines.at(2).append('|'+trName);
        for(int i=0; i<(int)(m_handWidth-allLines.at(2).size()); ++i)
            allLines.at(2).push_back(',');
        allLines.at(2).push_back('|');
    }
    //LINE NO.3,4,5,6,7,8
    for(unsigned r=0; r<6; ++r)
    {
        allLines.at(r+3).push_back('|');
        for(int i=0; i<(int)(m_handWidth-2); ++i)
            allLines.at(r+3).push_back(',');
        allLines.at(r+3).push_back('|');
    }
    //LINE NO.7

    //LINE NO.8

    //LINE NO.9
    allLines.at(9).append(m_handLine);
    return allLines;
}

void AsciiPrinter::drawPrize(std::array<unsigned,6> _prize) const
{
    for(int i=0; i<3; ++i)
    {
        for(int y=0; y<6; ++y)
        {
            if(_prize.at(y)==1)
            {
                if(i==1)
                {
                    std::cout<<m_prizeCardLine2;
                }
                else
                {
                    std::cout<<m_prizeCardLine1;
                }
            }
            else
            {
                std::string tmp;
                for(unsigned u=0; u<m_handWidth; ++u)
                    tmp.push_back(m_emptyChar);
                std::cout<<tmp;
            }
            if(y<5) std::cout<<m_emptyChar;
        }
        std::cout<<std::endl;
    }
}

void AsciiPrinter::drawSlots(std::array<unsigned,6> _slots) const
{
    std::cout<<"TODO: SLOT PRINTOUT"<<std::endl;
}

void AsciiPrinter::drawHand(Hand& _hand) const
{
    std::cout<<"TODO: HAND PRINTOUT"<<std::endl;
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

std::array<unsigned,6> AsciiPrinter::getSlots(Board* _board)
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
