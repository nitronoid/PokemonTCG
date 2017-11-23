#include "energycard.h"

EnergyCard::EnergyCard(
        const unsigned _id,
        const unsigned _amount,
        const PTCG::TYPE& _type
        )
{
    EnergyCard.m_type = _type;
    EnergyCard.m_amount = _amount;
    EnergyCard.m_id = _id;
}
