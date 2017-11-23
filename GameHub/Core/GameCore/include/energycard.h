#ifndef ENERGYCARD_H
#define ENERGYCARD_H

#include "card.h"

class EnergyCard:Card
{
public:
    EnergyCard(const EnergyCard&) = default;
    EnergyCard(
            const unsigned _id,
            const unsigned _amount,
            const PTCG::TYPE& _type
            );
private:
    const unsigned m_amount;
    const PTCG::TYPE m_type;
};

#endif // ENERGYCARD_H
