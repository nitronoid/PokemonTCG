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
    // when play card, choose the pokemon with the biggest hp
    setTime(m_time);
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}
//--------------------------------------------------------------------------
std::vector<size_t> AIPlayerBT::chooseSlot(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<BoardSlot> &_options, const unsigned _amount)
{
    setTime(m_time);
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
    setTime(m_time);
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}
//--------------------------------------------------------------------------
std::vector<size_t> AIPlayerBT::chooseConditions(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<PTCG::CONDITION> &_options, const unsigned _amount)
{
    setTime(m_time);
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
    // play baic pokemon on bench
    setTime(m_time);
    playBasicPokemonOnBench();
    // play evolution card on bench
    //setTime(m_time);
    //playEvolutionCard();
    // attach energy (should be last thing)
    setTime(m_time);
    attachEnergy();
    // should we atttack or not ?
    // and which attack?

    return std::pair<bool, unsigned> {false,0};

}

//--------------------------------------------------------------------------
void AIPlayerBT::playBasicPokemonOnBench()
{
    // basic pokemon
    auto hand = viewHand();
    for(int i = 0 ; i < hand.size(); ++i)
    {
        // check if the card is a pokemon
        if(hand[i]->cardType() == PTCG::CARD::POKEMON)
        {   // check if it is stage 0
            PokemonCard* pokemonCard = static_cast<PokemonCard*>(hand[i].get());
            if(pokemonCard->stage() == 0)
            {
                if(canPlay(i))
                {
                    playCard(i);
                }
            }
        }
    }
}
//--------------------------------------------------------------------------
void AIPlayerBT::playEvolutionCard()
{
    auto bench = viewBench();
    std::vector<std::string> _listOfPokemons;
    auto hand = viewHand();
    // iterate through your bench and store all the pokemons into a list
    for(int i = 0 ; i < bench.size(); ++i)
    {
        if(bench[i].numPokemon()!=0)
        {
            _listOfPokemons.push_back(bench[i].active()->getName());
        }
    }

    // iterate through your hand and check if there is a evolution card
    for(int j = 0; j < hand.size(); ++j)
    {   // check if your card is a pokemon
        if(hand[j]->cardType() == PTCG::CARD::POKEMON)
        {
            PokemonCard* evolveCard = static_cast<PokemonCard*>(hand[j].get());
            // iterate through the list of pokemon names
            for(int card = 0 ; card < _listOfPokemons.size(); ++card)
            {   // check if the card is equal to the pre-evolution name if it is play card
                if(_listOfPokemons[card] == evolveCard->preEvolution())
                {
                    if(canPlay(j))
                    {
                        playCard(j);
                    }
                }
            }
        }
    }

}
//--------------------------------------------------------------------------
void AIPlayerBT::attachEnergy()
{

    /// need help for this, because this wont work while there are multiple cards
    auto hand = viewHand();
    auto bench = viewBench();
    int _pos;
    for(int i = 0 ; i < bench.size(); ++i)
    {
        if(bench[i].numPokemon() != 0)
        {
            if(biggestAttack(i).size() > bench[i].numEnergy())
            {
                std::cout<<"NEED ENERGY"<<std::endl;
                for(size_t z = 0 ; z < biggestAttack(i).size(); ++z)
                {
                    for(size_t q = 0 ; q < hand.size(); ++q)
                    {
                        if(hand[q]->cardType() == PTCG::CARD::ENERGY)
                        {
                            EnergyCard* energyCard = static_cast<EnergyCard*>(hand[q].get());
                            std::cout<<"FIND ENERGY CARD"<<std::endl;
                            // check if it matches
                            if(energyCard->type() == biggestAttack(i)[z] || biggestAttack(i)[z] == PTCG::TYPE::COLOURLESS)
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
    }
}
//--------------------------------------------------------------------------
bool AIPlayerBT::doAttack()
{
    // return if i want to attack or not
}
//--------------------------------------------------------------------------
int AIPlayerBT::whichAttack()
{
    // return which attack
}
//--------------------------------------------------------------------------
void AIPlayerBT::setTime(int _amountMilliSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(_amountMilliSeconds));
}




//--------------------------------------------------------------------------
std::vector<PTCG::TYPE> AIPlayerBT::sortEnergies()
{
//    // biggestAttack - listOfSpecificEnergies = colourless
//    std::vector<PTCG::TYPE> _listOfSpecificEnergies;
//    for(int i = 0 ; i < biggestAttack().size(); ++i)
//    {
//        if(biggestAttack()[i] != PTCG::TYPE::COLOURLESS)
//        {
//            _listOfSpecificEnergies.push_back(biggestAttack()[i]);
//        }
//    }
//    return _listOfSpecificEnergies;
}
//--------------------------------------------------------------------------
std::vector<PTCG::TYPE> AIPlayerBT::biggestAttack(int _index)
{
    auto bench = viewBench();
    std::vector<PTCG::TYPE> _biggestAttack;
    for(int i = 0 ; i < bench[_index].active()->attacks().size(); ++i)
    {
        std::vector<PTCG::TYPE> _currentAttack = bench[_index].active()->attacks()[i].requirements();
        if(_biggestAttack.size() <= _currentAttack.size())
        {
            _biggestAttack = _currentAttack;
        }
    }
    return _biggestAttack;
}
//--------------------------------------------------------------------------
void AIPlayerBT::willRetreat()
{
    auto bench = viewBench()[0].active();
    int _healthLimit = bench->hp() / 2;
    if(bench->hp() <= _healthLimit)
    {
        std::cout<<"WILL RETREAT"<<std::endl;
        retreat();
    }
    std::cout<<"WILL NOT RETREAT"<<std::endl;
}
//--------------------------------------------------------------------------
void AIPlayerBT::playTrainerCard()
{
    auto hand = viewHand();
    for(int i = 0 ; i < hand.size(); ++i)
    {
        if(hand[i]->cardType() == PTCG::CARD::SUPPORT)
        {
            std::cout<<"SUPPORT CARD FIND"<<std::endl;
        }
        if(hand[i]->cardType() == PTCG::CARD::ITEM)
        {
            std::cout<<"ITEM CARD FIND"<<std::endl;
        }
        if(hand[i]->cardType() == PTCG::CARD::STADIUM)
        {
            std::cout<<"STADIUM CARD FIND"<<std::endl;
        }
    }
}





////--------------------------------------------------------------------------
//bool AIPlayerBT::checkIfEnergyNeeded()
//{
//    auto activeCard = viewBench();
//    // checks if the requirement vector size is bigger than the number energy attatched to the card
//    // if it is bigger the card needs energy
//    if(activeCard[0].active()->attacks()[0].requirements().size() +
//            activeCard[0].active()->attacks()[1].requirements().size()
//            > activeCard[0].numEnergy())
//    {
//        std::cout<<"CARD NEEDS ENERGY"<<std::endl;
//        return true;
//    }
//    std::cout<<"CARD DOES NOT NEED ENERGY"<<std::endl;
//    return false;
//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::checkTwoAttacks()
//{
//    // iterate through the attacks
//    if(viewBench()[0].active()->attacks().size() > 1)
//    {
//        std::cout<<"MULTIPLE ATTACKS"<<std::endl;
//        return true;
//    }
//    std::cout<<"ONE ATTACK"<<std::endl;
//    return false;
//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::checkAttackBigger()
//{
//    auto bench = viewBench();
//    if(bench[0].active()->attacks()[0].requirements().size() >= bench[0].active()->attacks()[1].requirements().size())
//    {
//        std::cout<<"ATTACK ONE IS BIGGER"<<std::endl;
//        return true;
//    }
//    std::cout<<"ATTACK TWO IS BIGGER"<<std::endl;
//    return false;
//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::needEnergy(int _index)
//{
//    auto bench = viewBench();
//    bool result = false;
//    if(bench[0].active()->attacks()[_index].requirements().size() > bench[0].numEnergy())
//    {
//        std::cout<<"NEED ENERGY"<<std::endl;
//        result = true;
//    }
//    std::cout<<"DONT NEED ENERGY"<<std::endl;
//    return result;
//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::checkVectorSize(int _i)
//{
//    if(viewBench()[0].active()->attacks()[0].requirements().size() > 1)
//    {
//        std::cout<<"NEED MULTIPLE REQUIREMENT ENERGIES  "<<viewBench()[0].active()->attacks()[0].requirements().size()<<std::endl;
//        return true;
//    }
//    std::cout<<"NEED ONE REQUIREMENT ENERGIE"<<std::endl;
//    return false;
//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::playEnergies(int _indexx)
//{
//    /// NOTES THERE IS A PROBLEM WITH THE PLAY ENERGIES FUNCTION
//    /// ALSO YOU NEED TO FIND A FUNCTION FOR THE COLOURLESS ENERGIES
//    int _index;
//    auto hand = viewHand();
//    auto bench = viewBench();
//    for(size_t i = 0 ; i < bench[0].active()->attacks()[_indexx].requirements().size(); ++i)
//    {
//        for(size_t j = 0 ; j < hand.size(); ++j)
//        {
//            if(hand[j]->cardType() == PTCG::CARD::ENERGY)
//            {
//                EnergyCard* energyCard = static_cast<EnergyCard*>(hand[j].get());
//                if(bench[0].active()->attacks()[_indexx].requirements().size() > bench[0].numEnergy())
//                {
//                    if(bench[0].active()->attacks()[_indexx].requirements()[i] == energyCard->type()
//                            || bench[0].active()->attacks()[_indexx].requirements()[i] == PTCG::TYPE::COLOURLESS)
//                    {
//                        _index = j;
//                    }
//                }
//            }
//        }
//    }
//    if(canPlay(_index))
//    {
//        std::cout<<"PLAY ENERGY"<<std::endl;
//        playCard(_index);
//    }

//    return true;
//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::energyInHand()
//{
//    auto hand = viewHand();
//    for(int i = 0; i < hand.size(); ++i)
//    {
//        if(hand[i]->cardType() == PTCG::CARD::ENERGY)
//        {
//            std::cout<<"YOU HAVE ENERGY IN HAND"<<std::endl;
//            return true;
//        }
//        std::cout<<"YOU HAVE NO ENERGY IN HAND"<<std::endl;
//        return false;
//    }
//}
////--------------------------------------------------------------------------
//void AIPlayerBT::buildTree()
//{
//    Selector* selectsAttacks = new Selector;
//    // selector / sequence nodes
//    Selector* selectsWhichAttackBiggest = new Selector;
//    Sequence* ifTwoAttacks = new Sequence;
//    Sequence* ifOnlyOneAttack = new Sequence;
//    Sequence* ifAttackOneBigger = new Sequence;
//    Sequence* ifAttackTwoBigger = new Sequence;
//    // attach the children
//    /// SELECTS IF YOU HAVE TWO ATTACKS OR ONE
//    selectsAttacks->addChild(new Condition(energyInHand()));
//    selectsAttacks->addChild(ifTwoAttacks);
//    selectsAttacks->addChild(ifOnlyOneAttack);
//    /// IF THERE IS TWO ATTACKS
//    ifTwoAttacks->addChild(new Condition(checkTwoAttacks()));
//    ifTwoAttacks->addChild(selectsWhichAttackBiggest);
//    /// IF THERE IS ONLY ONE ATTACK
//    ifOnlyOneAttack->addChild(new Condition(!checkTwoAttacks()));
//    ifOnlyOneAttack->addChild(new Condition(needEnergy(0)));
//    ifOnlyOneAttack->addChild(new Action(playEnergies(0)));
//    /// SELECTS THE BIGGER ATTACK
//    selectsWhichAttackBiggest->addChild(ifAttackOneBigger);
//    selectsWhichAttackBiggest->addChild(ifAttackTwoBigger);
//    /// IF ATTACK ONE IS BIGGER
//    ifAttackOneBigger->addChild(new Condition(checkAttackBigger()));
//    ifAttackOneBigger->addChild(new Condition(needEnergy(0)));
//    ifAttackOneBigger->addChild(new Action(playEnergies(0)));
//    /// IF ATTACK TWO IS BIGGER
//    ifAttackTwoBigger->addChild(new Condition(!checkAttackBigger()));
//    ifAttackTwoBigger->addChild(new Condition(needEnergy(1)));
//    ifAttackTwoBigger->addChild(new Action(playEnergies(1)));

//}
////--------------------------------------------------------------------------
//bool AIPlayerBT::checkIfCardIsEnergy()
//{
//    // the iterator goes through the hand
//    for(unsigned int i=0; i<viewHand().size(); ++i)
//    {
//        // checks if the card in your hand is an energy card
//        if(viewHand()[i]->cardType() == PTCG::CARD::ENERGY)
//        {
//            std::cout<<"THERE IS ENERGY IN THE HAND"<<std::endl;
//            return true;
//        }
//        std::cout<<"THERE IS NO ENERGY IN HAND"<<std::endl;
//        return false;
//    }
//}
