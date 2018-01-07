#ifndef ENERGYCARD_H
#define ENERGYCARD_H

#include "card.h"

class EnergyCard : public Card
{
public:
    EnergyCard(const EnergyCard&) = default;
    EnergyCard(const unsigned _id, const std::string &_name, const Ability &_ability, const unsigned _amount, const PTCG::TYPE _type) :
      Card(_id, _name, _ability),
      m_amount(_amount),
      m_type(_type)
    {}

    virtual bool canPlay() const override;

    virtual Card* clone() override;

    PTCG::TYPE type() const;
    unsigned amount() const;
    virtual PTCG::CARD cardType() const override;
private:
    unsigned m_amount;
    PTCG::TYPE m_type;
};

#endif // ENERGYCARD_H
