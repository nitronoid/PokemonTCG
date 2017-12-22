#include "damagecalculator.h"

int DamageCalculator::CalculateDamage(std::unique_ptr<BoardSlot> _refSlot, const unsigned _id, bool _includeWeakRes)
{
    if(_id > 5)
    {
        std::cout<<"ERROR: CalculateDamage cannot be called because slot index is out of range."<<'\n';
        return 0;
    }
    else
    {
        PTCG::TYPE temp = PTCG::TYPE::ERROR; //!!!DELETE WHEN IMPLEMENTED!!!
        m_initialDamage = _refSlot->GetDamage();
        int currentDmg=m_initialDamage;


        //If this is an active pokemon:
        if(_id == 0)
        {
            //add weakness/resistance effects to the top evo of pokemon
            if(_refSlot->active()->weakness()==temp)currentDmg*=2;
            if(_refSlot->active()->resistance()==temp)currentDmg-=20;
        }
        m_noBonus = currentDmg;
    }
}

int DamageCalculator::CalcDmgWeakRes()
{

}

int DamageCalculator::CalcDmgNoWeakRes()
{

}
