#include <iostream>
#include "selector.h"
#include "sequence.h"
#include "testaction.h"
#include "conditionenergy.h"
#include "conditiondead.h"
#include "conditionsecondattack.h"
#include "conditionlistempty.h"
#include "cards.h"

int main()
{
    // popplio
    Cards card;
    card.setCurrentEnergy(0);

    // create a list of cards
    std::vector<Cards> m_listOfBenchCards;
    m_listOfBenchCards.push_back(card);
    m_listOfBenchCards.push_back(card);

//-----------------------------------------------------------------------------
    // build tree
    // add children from left to right
    // root Selector for action Decision
    Sequence* actionDecision = new Sequence;
    // selects if ACTION card needs energy or bench card
    Selector* actionOrBenchSelector = new Selector;
    // checks if the card need energy, if it will be dead soon, attach energy to ACTION card
    Sequence* energyNeededSequence = new Sequence;
    // sequence for attack 2
    Selector* attack1ORattack2 = new Selector;
    Sequence* attack2 = new Sequence;
    Sequence* attack1 = new Sequence;
    // checks if the bench is empty, for basic card in hand to bench
    Sequence* drawBasic = new Sequence;

    // root node and tell which action to choose
    actionDecision->addChild(actionOrBenchSelector);
    // draw cards from hand to bench
    actionDecision->addChild(drawBasic);
    // choose attack1 or attack2
    actionDecision->addChild(attack1ORattack2);
    // condition check if the bench is not empty
    drawBasic->addChild(new conditionListEmpty(m_listOfBenchCards));
    drawBasic->addChild(new testAction("BENCH CARDS LIST NOT EMPTY"));

    attack1ORattack2->addChild(attack2);
    attack1ORattack2->addChild(attack1);
    attack1ORattack2->addChild(new testAction("CAN'T ATTACK"));
    // checks for condition
    attack2->addChild(new conditionSecondAttack(card.getCurrentEnergy(), card.getEnergy_1()));
    attack2->addChild(new testAction("ATTACK 2"));
    attack1->addChild(new conditionSecondAttack(card.getCurrentEnergy(), card.getEnergy_0()));
    attack1->addChild(new testAction("ATTACK 1"));
    // ACTION or BENCH card to attach energy
    actionOrBenchSelector->addChild(energyNeededSequence);

    // Sequence for attaching energy
    energyNeededSequence->addChild(new conditionEnergy(card.getCurrentEnergy(),card.getEnergy_0(), card.getEnergy_1()));
    energyNeededSequence->addChild(new conditionDead(card.getHealth()));
    energyNeededSequence->addChild(new testAction("ATTACH ENERGY TO ACTIVE CARD"));

    actionOrBenchSelector->addChild(new testAction("ATTACH ENERGY TO RANDOM BENCH CARD"));
    // while the root is not true then continue running !
    while(!actionDecision->run())
        std::cout<<"running"<<'\n';

    return 0;
}