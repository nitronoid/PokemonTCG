#include "aiplayerbt.h"
#include <chrono>
#include <thread>

Player* AIPlayerBT::clone() const
{
    return new AIPlayerBT(*this);
}
//--------------------------------------------------------------------------
std::string AIPlayerBT::deckName() const
{
    return "bright_tide_deck.json";
}
//--------------------------------------------------------------------------
std::vector<size_t> AIPlayerBT::chooseCards(const PTCG::PLAYER _player, const PTCG::PILE _origin, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{
    setTime(3000);
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}
//--------------------------------------------------------------------------
std::vector<size_t> AIPlayerBT::chooseSlot(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<BoardSlot> &_options, const unsigned _amount)
{
    setTime(3000);
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}
//--------------------------------------------------------------------------
void AIPlayerBT::learnCards(const PTCG::PLAYER _owner, const PTCG::PILE _origin, const std::vector<size_t> &_indices, const std::vector<std::unique_ptr<Card> > &_revealed)
{
    /// OPTIONAL
}
//--------------------------------------------------------------------------
std::vector<size_t> AIPlayerBT::chooseEnergy(const PTCG::PLAYER _owner, const PTCG::PILE _destination, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{
    setTime(3000);
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}
//--------------------------------------------------------------------------
std::vector<size_t> AIPlayerBT::chooseConditions(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<PTCG::CONDITION> &_options, const unsigned _amount)
{
    setTime(3000);
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;

}
//--------------------------------------------------------------------------
bool AIPlayerBT::agree(const PTCG::ACTION _action)
{
    // when do we agree to an action
    // different type of actions are
    // DRAW DISCARD PLAY VIEW MOVE HEAL ATTACK
    return true;
}
//--------------------------------------------------------------------------
std::pair<bool, unsigned> AIPlayerBT::turn()
{
    // variables
    m_attack = false;
    m_chooseAttack = 0;

    // you can only play one energy at a time
    setTime(3000);
    // required energies for attack 1
    // the number energy attached on card
    setTime(3000);
    playEvolutionCard();

//    if(checkIfCardIsEvolution())
//        playEvolutionCard();
//    setTime(3000);


    if(viewBench()[0].active()->attacks()[1].requirements().size() <= viewBench()[0].numEnergy())
    {
        m_chooseAttack = 0;
        m_attack = true;
    }


        return std::pair<bool, unsigned> {m_attack, m_chooseAttack};

}

//--------------------------------------------------------------------------
void AIPlayerBT::putPokemonOnBench()
{
    int positionOfHighestHP = 0;
    auto hand = viewHand();
    for(unsigned int i=0; i<hand.size(); ++i)
    {
        // checks if the card in your hand is an energy card
        if(hand[i]->cardType() == PTCG::CARD::POKEMON)
        {
            auto pokemon = static_cast<PokemonCard*>(hand[i].get());
            auto currentHighestPoke = static_cast<PokemonCard*>(hand[positionOfHighestHP].get());
            if (pokemon->hp() > currentHighestPoke->hp())
                positionOfHighestHP = i;
        }
    }
    if(canPlay(positionOfHighestHP))
        playCard(positionOfHighestHP);
}

//--------------------------------------------------------------------------
bool AIPlayerBT::checkIfCardIsEnergy()
{
    // the iterator goes through the hand
    for(unsigned int i=0; i<viewHand().size(); ++i)
    {
        // checks if the card in your hand is an energy card
        if(viewHand()[i]->cardType() == PTCG::CARD::ENERGY)
        {
            std::cout<<"THERE IS ENERGY IN THE HAND"<<std::endl;
            return true;
        }
        std::cout<<"THERE IS NO ENERGY IN HAND"<<std::endl;
        return false;
    }
}
//--------------------------------------------------------------------------
void AIPlayerBT::playEvolutionCard()
{
    int evolved = 0;
    auto hand = viewHand();
    auto bench = viewBench();
    for(unsigned int i=0; i<hand.size(); ++i)
    {
        if(hand[i]->cardType() == PTCG::CARD::POKEMON)
        {

            auto pokemon = static_cast<PokemonCard*>(hand[i].get());
            //evolved = pokemon->preEvolution();
            evolved = i;

            for(unsigned int i=0; i<bench.size(); ++i)
            {
                if(bench[0].active()->getName() == pokemon->preEvolution())
                {
                    //evolved = pokemon->preEvolution();
                    //evolved = i;
                    if(canPlay(evolved))
                        playCard(evolved);

                }
            }
        }

    }

}
//--------------------------------------------------------------------------
/*bool AIPlayerBT::checkIfCardIsEvolution()
{
//DO WE NEED THIS FUNCTION?
//probably not
    auto hand = viewHand();
    auto bench = viewBench();
    for(unsigned int i=0; i<hand.size(); ++i)
    {
        if(hand[i]->cardType() == PTCG::CARD::POKEMON)
        {
            auto pokemon = static_cast<PokemonCard*>(hand[i].get());
            if(bench[0].active()->getName() == pokemon->preEvolution())
            {
                std::cout<<"THERE IS EVOLUTION CARD IN THE HAND"<<std::endl;
                return true;
            }
            std::cout<<"THERE IS NO EVOLUTION CARD IN THE HAND"<<std::endl;
            return false;
        }
    }
}*/

//--------------------------------------------------------------------------
void AIPlayerBT::setTime(int _amountMilliSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(_amountMilliSeconds));
}
//--------------------------------------------------------------------------
std::vector<PTCG::TYPE> AIPlayerBT::sortEnergies()
{
    std::vector<PTCG::TYPE> _listOfSpecificEnergies;
    for(int i = 0 ; i < biggestAttack().size(); ++i)
    {
        if(biggestAttack()[i] != PTCG::TYPE::COLOURLESS)
        {
            _listOfSpecificEnergies.push_back(biggestAttack()[i]);
        }
    }
    return _listOfSpecificEnergies;
}

std::vector<PTCG::TYPE> AIPlayerBT::biggestAttack()
{
    auto bench = viewBench();
    std::vector<PTCG::TYPE> _biggestAttack;
    for(int i = 0 ; i < bench[0].active()->attacks().size(); ++i)
    {
        std::vector<PTCG::TYPE> _currentAttack = bench[0].active()->attacks()[i].requirements();
        if(_biggestAttack.size() <= _currentAttack.size())
        {
            _biggestAttack = _currentAttack;
        }
    }
    return _biggestAttack;
}

void AIPlayerBT::attachEnergy()
{
    /// ONLY ATTATCH ENERGIES
    auto bench = viewBench();
    auto hand = viewHand();

    // checks if the amount of energy is less than required,
    // also needs to check if I already have that energy, if not attach the energy needed
    int _pos;
    if(bench[0].numEnergy() < biggestAttack().size())
    {
        std::cout<<"NEED ENERGY"<<std::endl;
        for(int z = 0 ; z < biggestAttack().size(); ++z)
        {
            for(int q = 0 ; q < hand.size(); ++q)
            {
                if(hand[q]->cardType() == PTCG::CARD::ENERGY)
                {
                    EnergyCard* energyCard = static_cast<EnergyCard*>(hand[q].get());
                    std::cout<<"FIND ENERGY CARD"<<std::endl;
                    // check if it matches
                    if(energyCard->type() == biggestAttack()[z] || biggestAttack()[z] == PTCG::TYPE::COLOURLESS)
                    {
                        std::cout<<"IT MATCHES OR IS COLOURLESS"<<std::endl;
                        _pos = q;

                     }
                 }
              }
           }
        if(canPlay(_pos))
            playCard(_pos);
       }

}

bool AIPlayerBT::attackPokemon()
{
    /// NEED THE MULTI SET OF ACTIVE POKEMON
    /// COMPARE IF IT IS THE REQUIREMENT OF ATTACK 1
    /// multisets check if they are equal (convert to a vector)
    /// check for attack 1 requirements, add a to a vector
    /// check if there is a requirement in the multi set
    /// add it to a multi set
    /// loop through and check if they are equal
    bool _attack;

    // when to attack an pokemon
    // check if I have enough energy for attack 1

    if(viewBench()[0].active()->attacks()[0].requirements().size() <= viewBench()[0].numEnergy())
    {
        // check if I am nearly dead ..
        // at the moment just use 10
        if(viewBench()[0].active()->hp() - 10 < 0)
        {
            _attack = false;
        }
        _attack = true;
    }
    return _attack;
}























//--------------------------------------------------------------------------
bool AIPlayerBT::checkIfEnergyNeeded()
{
    auto activeCard = viewBench();
    // checks if the requirement vector size is bigger than the number energy attatched to the card
    // if it is bigger the card needs energy
    if(activeCard[0].active()->attacks()[0].requirements().size() +
            activeCard[0].active()->attacks()[1].requirements().size()
            > activeCard[0].numEnergy())
    {
        std::cout<<"CARD NEEDS ENERGY"<<std::endl;
        return true;
    }
    std::cout<<"CARD DOES NOT NEED ENERGY"<<std::endl;
    return false;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::checkTwoAttacks()
{
    // iterate through the attacks
    if(viewBench()[0].active()->attacks().size() > 1)
    {
        std::cout<<"MULTIPLE ATTACKS"<<std::endl;
        return true;
    }
    std::cout<<"ONE ATTACK"<<std::endl;
    return false;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::checkAttackBigger()
{
    auto bench = viewBench();
    if(bench[0].active()->attacks()[0].requirements().size() >= bench[0].active()->attacks()[1].requirements().size())
    {
        std::cout<<"ATTACK ONE IS BIGGER"<<std::endl;
        return true;
    }
    std::cout<<"ATTACK TWO IS BIGGER"<<std::endl;
    return false;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::needEnergy(int _index)
{
    auto bench = viewBench();
    bool result = false;
    if(bench[0].active()->attacks()[_index].requirements().size() > bench[0].numEnergy())
    {
        std::cout<<"NEED ENERGY"<<std::endl;
        result = true;
    }
    std::cout<<"DONT NEED ENERGY"<<std::endl;
    return result;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::checkVectorSize(int _i)
{
    if(viewBench()[0].active()->attacks()[0].requirements().size() > 1)
    {
        std::cout<<"NEED MULTIPLE REQUIREMENT ENERGIES  "<<viewBench()[0].active()->attacks()[0].requirements().size()<<std::endl;
        return true;
    }
    std::cout<<"NEED ONE REQUIREMENT ENERGIE"<<std::endl;
    return false;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::playEnergies(int _indexx)
{
    /// NOTES THERE IS A PROBLEM WITH THE PLAY ENERGIES FUNCTION
    /// ALSO YOU NEED TO FIND A FUNCTION FOR THE COLOURLESS ENERGIES
    int _index;
    auto hand = viewHand();
    auto bench = viewBench();
    for(size_t i = 0 ; i < bench[0].active()->attacks()[_indexx].requirements().size(); ++i)
    {
        for(size_t j = 0 ; j < hand.size(); ++j)
        {
            if(hand[j]->cardType() == PTCG::CARD::ENERGY)
            {
                EnergyCard* energyCard = static_cast<EnergyCard*>(hand[j].get());
                if(bench[0].active()->attacks()[_indexx].requirements().size() > bench[0].numEnergy())
                {
                    if(bench[0].active()->attacks()[_indexx].requirements()[i] == energyCard->type()
                            || bench[0].active()->attacks()[_indexx].requirements()[i] == PTCG::TYPE::COLOURLESS)
                    {
                        _index = j;
                    }
                }
            }
        }
    }
    if(canPlay(_index))
    {
        std::cout<<"PLAY ENERGY"<<std::endl;
        playCard(_index);
    }

    return true;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::energyInHand()
{
    auto hand = viewHand();
    for(int i = 0; i < hand.size(); ++i)
    {
        if(hand[i]->cardType() == PTCG::CARD::ENERGY)
        {
            std::cout<<"YOU HAVE ENERGY IN HAND"<<std::endl;
            return true;
        }
        std::cout<<"YOU HAVE NO ENERGY IN HAND"<<std::endl;
        return false;
    }
}
//--------------------------------------------------------------------------
void AIPlayerBT::buildTree()
{
    Selector* selectsAttacks = new Selector;
    // selector / sequence nodes
    Selector* selectsWhichAttackBiggest = new Selector;
    Sequence* ifTwoAttacks = new Sequence;
    Sequence* ifOnlyOneAttack = new Sequence;
    Sequence* ifAttackOneBigger = new Sequence;
    Sequence* ifAttackTwoBigger = new Sequence;
    // attach the children
    /// SELECTS IF YOU HAVE TWO ATTACKS OR ONE
    selectsAttacks->addChild(new Condition(energyInHand()));
    selectsAttacks->addChild(ifTwoAttacks);
    selectsAttacks->addChild(ifOnlyOneAttack);
    /// IF THERE IS TWO ATTACKS
    ifTwoAttacks->addChild(new Condition(checkTwoAttacks()));
    ifTwoAttacks->addChild(selectsWhichAttackBiggest);
    /// IF THERE IS ONLY ONE ATTACK
    ifOnlyOneAttack->addChild(new Condition(!checkTwoAttacks()));
    ifOnlyOneAttack->addChild(new Condition(needEnergy(0)));
    ifOnlyOneAttack->addChild(new Action(playEnergies(0)));
    /// SELECTS THE BIGGER ATTACK
    selectsWhichAttackBiggest->addChild(ifAttackOneBigger);
    selectsWhichAttackBiggest->addChild(ifAttackTwoBigger);
    /// IF ATTACK ONE IS BIGGER
    ifAttackOneBigger->addChild(new Condition(checkAttackBigger()));
    ifAttackOneBigger->addChild(new Condition(needEnergy(0)));
    ifAttackOneBigger->addChild(new Action(playEnergies(0)));
    /// IF ATTACK TWO IS BIGGER
    ifAttackTwoBigger->addChild(new Condition(!checkAttackBigger()));
    ifAttackTwoBigger->addChild(new Condition(needEnergy(1)));
    ifAttackTwoBigger->addChild(new Action(playEnergies(1)));

}
