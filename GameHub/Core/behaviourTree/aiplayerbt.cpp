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
    //    if(viewBench()[0].active()->attacks().size()<2)
    //    {
    //        std::cout<<"ONE ATTACK"<<std::endl;
    //    }
    //    else
    //    {
    //         std::cout<<"TWO ATTACKS"<<std::endl;
    //         if(viewBench()[0].active()->attacks()[0].requirements().size() >
    //                 viewBench()[0].active()->attacks()[1].requirements().size())
    //         {
    //             std::cout<<"FIRST ATTACK HAS MORE ENERGY"<<std::endl;
    //         }
    //         else
    //         {
    //             std::cout<<"SECOND ATTACK HAS MORE ENERGY"<<std::endl;
    //             if(viewBench()[0].active()->attacks()[1].requirements().size() > viewBench()[0].numEnergy())
    //             {
    //                 std::cout<<"ATTACH ENERGY"<<std::endl;
    //             }
    //         }
    //    }
    if(checkIfEnergyNeeded())
        // check if the string is not empty , or has a +/x ]
        // cast it to an int
        //if(viewBench()[0].active()->hp() - viewBench(PTCG::PLAYER::ENEMY)[0].active()->attacks)
        playEnergy();

    // required energies for attack 1
    // the number energy attached on card
    setTime(3000);

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
void AIPlayerBT::playEnergy()
{
    auto hand = viewHand();
    for(unsigned int i=0; i<hand.size(); ++i)
    {
        // checks if the card in your hand is an energy card
        if(hand[i]->cardType() == PTCG::CARD::ENERGY)
        {   // make a card energy from your hand
            EnergyCard* typeOfEnergyHand = static_cast<EnergyCard*>(hand[i].get());
            // if that card energy == requirements
            if(typeOfEnergyHand->type() == typeReturnofActiveCard()
                    // this is wrong need the amount of colourless
                    || typeReturnofActiveCard() == PTCG::TYPE::COLOURLESS)
            {
                if(canPlay(i))
                    playCard(i);
            }

        }
    }
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
PTCG::TYPE AIPlayerBT::typeReturnofActiveCard()
{
    // goes through the requirement energies in attack 1
    for(int i = 0; i < viewBench()[0].active()->attacks()[0].requirements().size(); ++i)
    {
        // return the energy needed for attack one
        return viewBench()[0].active()->attacks()[0].requirements()[0];
    }
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
bool AIPlayerBT::checkIfEnergyNeeded()
{
    // checks if the requirement vector size is bigger than the number energy attatched to the card
    // if it is bigger the card needs energy
    if(viewBench()[0].active()->attacks()[0].requirements().size()
            + viewBench()[0].active()->attacks()[1].requirements().size()
            > viewBench()[0].numEnergy() + 1)
    {
        std::cout<<"CARD NEEDS ENERGY"<<std::endl;
        return true;
    }
    std::cout<<"CARD DOES NOT NEED ENERGY"<<std::endl;
    return false;
}
//--------------------------------------------------------------------------
bool AIPlayerBT::playEvolutionCard()
{
    int evolved = 0;
    auto hand = viewHand();
    auto bench = viewBench();
    for(unsigned int i=0; i<hand.size(); ++i)
    {
        if(hand[i]->cardType() == PTCG::CARD::POKEMON)
        {
            auto pokemon = static_cast<PokemonCard*>(hand[i].get());
            if(bench[0].active()->getName() == pokemon->preEvolution())
            {
                // put evolution on basic pokemon
                //pokemon->preEvolution() = pokemon->stage();
                //pokemon->stage() = pokemon->preEvolution();
                evolved = i;

            }
        }
        if(canPlay(evolved))
            playCard(evolved);
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
bool AIPlayerBT::temp()
{
    std::cout<<"TRUE NODE TEMP"<<std::endl;
    return true;
}
//--------------------------------------------------------------------------
void AIPlayerBT::setTime(int _amountMilliSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(_amountMilliSeconds));
}
//--------------------------------------------------------------------------
