#include "RoaringFluke.h"
#include "player/playercommand.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <functional>
unsigned found;
bool unplayedevo = false;
bool unplayeddevo = false;
unsigned evoloc;
unsigned devoloc;
Player* RoaringFluke::clone() const
{
    return new RoaringFluke(*this);
}


std::string RoaringFluke::deckName() const
{
    return "roaring_heat_deck.json";
}

std::vector<size_t> RoaringFluke::chooseCards(
        const PTCG::PLAYER _player,
        const PTCG::PILE _origin,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card>> &_options,
        const unsigned _amount
        )
{
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

std::vector<size_t> RoaringFluke::chooseSlot(
        const PTCG::PLAYER _owner,
        const PTCG::ACTION _action,
        const std::vector<BoardSlot> &_options,
        const unsigned _amount
        )
{
    for (auto& opt : _options)
    {

    }
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);

    return badChoice;

}

void RoaringFluke::learnCards(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _origin,
        const std::vector<size_t> &_indices,
        const std::vector<std::unique_ptr<Card>> &_revealed
        )
{}

std::vector<size_t> RoaringFluke::chooseEnergy(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _destination,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card> > &_options,
        const unsigned _amount
        )
{
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

bool randomishBool()
{
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
    return gen();
}

bool RoaringFluke::agree(const PTCG::ACTION _action)
{
    return randomishBool();
}

std::vector<size_t> RoaringFluke::chooseConditions(
        const PTCG::PLAYER _owner,
        const PTCG::ACTION _action,
        const std::vector<PTCG::CONDITION> &_options,
        const unsigned _amount)

{
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

std::pair<bool, unsigned> RoaringFluke::turn()
{
    auto initHand = viewHand();
    // Random engine
    static std::random_device seed;
    static std::mt19937_64 eng(seed());

    using cardRefList = std::vector<std::reference_wrapper<std::unique_ptr<Card>>>;
    cardRefList curEnergyList, curPokemonList, curTrainerList;
    std::cout<<"\nRoaring flukes Pokemon:\n\n";

    //------------------------------------------------we create lists based on card type in our deck to simplify AI access to cards---------------------------------------------
    std::vector<int>currentPokeIndexList;
    std::vector<int>currentEnergyIndexList;
    std::vector<int>currentTrainerIndexList;


    for (int i = 0 ; i < initHand.size(); ++i)
    {
        auto& currentCard = initHand[i];
        std::cout<<i+1<<" "<<currentCard->getName()<<" - "<<currentCard->getID()<<"\n";

        if (currentCard->cardType() == PTCG::CARD::ENERGY)
        {
            curEnergyList.push_back(currentCard);
            currentEnergyIndexList.push_back(i);
        }else if(currentCard->cardType() == PTCG::CARD::POKEMON)
        {
            curPokemonList.push_back(currentCard);
            currentPokeIndexList.push_back(i);
        }else if(currentCard->cardType() == PTCG::CARD::ITEM || currentCard->cardType() == PTCG::CARD::SUPPORT)
        {
            curTrainerList.push_back(currentCard);
            currentTrainerIndexList.push_back(i);
        }
    }
    //**************************************************************************************************************************************************************************

    std::cout<<"\nNumber of Pokemon - "<<curPokemonList.size()<<".\n";
    std::cout<<"Number of Energy - "<<curEnergyList.size()<<".\n";
    std::cout<<"Number of Trainers - "<<curTrainerList.size()<<".\n\n";

    //------------------------------------------------gets our's & enemy's current active pokemon and stores them---------------------------------------------------------------
    auto bench = viewBench();
    PokemonCard* currentPoke = bench[0].active();
    PokemonCard* enCurrentPoke = viewBench(PTCG::PLAYER::ENEMY)[0].active();
    auto slot = viewBench()[0];
    auto enslot  = viewBench(PTCG::PLAYER::ENEMY)[0];
    //**************************************************************************************************************************************************************************

    std::cout<<"Current Active: "<<currentPoke->getName()<<" - "<<currentPoke->hp()<<"hp.\n\n";
    bool needswitch = false;
    bool change = false;
    size_t bestPos = 0;
    unsigned evoPoke = 0;

    int i = 0;

    //------------------------------------------------pokemon brain really starts here------------------------------------------------------------------------------------------

    //------------------------------------------------pokemon card managment starts here------------------------------------------------------------------------------------
    if (curPokemonList.size())
    {
        for (auto& card : curPokemonList)
        {
            PokemonCard* pokemon = static_cast<PokemonCard*>(card.get().get());
            PokemonCard* currentBest = static_cast<PokemonCard*>(curPokemonList[bestPos].get().get());
            if (pokemon->hp() > currentBest->hp())
            {
                bestPos = i;
                change = true;
            }
            std::string preEv = pokemon->preEvolution();
            if (preEv.empty() != true)
            {
                std::cout<<pokemon->getName()<<" Has pre evoltion: '"<<preEv<<"'.\n";
                evoPoke = 0;
                for (auto& card : curPokemonList)
                {
                    PokemonCard* currentEv = static_cast<PokemonCard*>(card.get().get());
                    if (preEv == currentEv->getName())
                    {
                        std::cout<<preEv<<" is in your hand.\n";


                        for (int k = 0 ; k < 6; ++k)
                        {
                            if(bench[k].active() && bench[k].active()->getName() == currentEv->getName())
                            {
                                std::cout<<"OH DAMN "<<currentEv->getName()<<" is on your bench E.\n";
                                found = k;
                            }else if (bench[k].active())
                            {
                                std::cout<<bench[k].active()->getName()<<" is on your bench NE.\n";
                            }
                        }

                        if (found)
                        {
                            unplayedevo = true;
                            evoloc = i;

                            std::cout<<"Playing "<<pokemon->getName()<<".\n";
                            found = 0;
                        } else
                        {
                            unplayeddevo = true;
                            devoloc = evoPoke;

                            std::cout<<"Playing "<<currentEv->getName()<<" and its evoltion "<<pokemon->getName()<<" next turn.\n";

                        }


                    }else
                    {

                        std::cout<<preEv<<" is NOT in ph"<<evoPoke<<".\n";
                    }
                ++evoPoke;
                }
            }
            ++i;
        }
       if (unplayedevo)
       {
           if (evoloc)playCard(currentPokeIndexList[evoloc]);
           unplayedevo = false;
           initHand = viewHand();
       }
       if (unplayeddevo)
       {
           if (devoloc)playCard(currentPokeIndexList[devoloc]);
           unplayeddevo = false;
           initHand = viewHand();
       }


    PokemonCard* bestHealth = static_cast<PokemonCard*>(curPokemonList[bestPos].get().get());
    initHand = viewHand();
    if (slot.getRemainingHP() <= 30) needswitch = true;
    if (canPlay(currentPokeIndexList[bestPos]))
    {
        std::cout<<"\n\nBest Health on Pokemon:\n"<<bestHealth->getName()<<" - "<<bestHealth->hp()<<"hp - Playable.\n\n";

        if (currentPoke->hp() < bestHealth->hp())
        {
            //if active has energy we need to hold horses
            playCard(currentPokeIndexList[bestPos]);
            std::cout<<"Switched out active for best Health\n";

        }else
        {
            std::cout<<"can't switch due to active pokemon having better health\n";
        }
    }
    else
    {
        std::cout<<"Best Health on Pokemon:\n"<<bestHealth->getName()<<" - "<<bestHealth->hp()<<"hp - NOT Playable.\n\n";
        if (needswitch)
        {

            for (int j = 0 ; j < curPokemonList.size(); ++j)
            {
                PokemonCard* pokemon = static_cast<PokemonCard*>(curPokemonList[j].get().get());

                if (canPlay(j))
                {
                    if (pokemon->weakness() != enCurrentPoke->type())
                    {
                        if (bestHealth->weakness() == enCurrentPoke->type())
                        {
                            bestPos = j;
                            if (pokemon->hp() > enCurrentPoke->hp())
                            {
                                if (pokemon->hp() > bestHealth->hp())
                                {
                                    bestPos = j;
                                }
                            }
                        }else
                        {
                            if (pokemon->hp() > bestHealth->hp())
                            {
                                bestPos = j;
                            }
                            if (pokemon->hp() > enCurrentPoke->hp())
                            {
                                bestPos = j;
                            }
                        }
                    }

                } else
                {
                    curPokemonList.erase(curPokemonList.begin() + j);
                    --j;
                    if (curPokemonList.size() == 0)
                    {
                        std::cout<<"No Playable Pokemon\n";
                        needswitch = false;
                    }
                }
            }
            if (needswitch)playCard(bestPos);
        }
        needswitch = false;
    }

} else
{
std::cout<<"there were no pokemon in your hand\n";
}

//**************************************************************************************************************************************************************************

//------------------------------------------------energy card managment starts here-----------------------------------------------------------------------------------------
if (curEnergyList.size())
{

    std::cout<<"Calculating Energy\n";
    currentPoke = bench[0].active();
    slot = viewBench()[0];
    signed target = 0;
    for (auto& attack : slot.active()->attacks())
    {
        int curr = attack.requirements().size();
        if (curr > target)
        {
            target = curr;
        }
    }
    std::cout<<"number of energy on main - "<<slot.numEnergy()<<"\nnumber of energy needed for best attack - "<<target<<".\n";
    if (slot.numEnergy() <= target)
    {
        std::vector<Attack> attacks = currentPoke->attacks();
        auto requirements = attacks[attacks.size() - 1].requirements();
        bool played = false;
        unsigned bestAtt;
        std::cout<<"about to match energy\n";
        for (int j = 0 ; j < requirements.size(); ++j)
        {
            for (int t = 0 ; (t < curEnergyList.size()-1) && !played; ++t)
            {
                EnergyCard* energy = static_cast<EnergyCard*>(curEnergyList[t].get().get());
                if (requirements[j] == energy->type())
                {
                    bestAtt = t;
                    played = true;
                } else if  (requirements[j] == PTCG::TYPE::COLOURLESS)
                {
                    bestAtt = t;
                    played = true;
                }
            }

        }
        if (canPlay(currentEnergyIndexList[bestAtt]))
        {
            playCard(currentEnergyIndexList[bestAtt]);
            std::cout<<"pe\n";
        }
    }

} else
{
std::cout<<"there is no Energy in your hand\n";
}

//**************************************************************************************************************************************************************************

//------------------------------------------------trainer cards managment starts here---------------------------------------------------------------------------------------

if (curTrainerList.size())
{
    /*int i;
        TrainerCard* curtrainer = static_cast<TrainerCard*>(curTrainerList[i].get().get());
        for(i; i < currentTrainerIndexList.size()-1; i++ )
        {
            if(canPlay(currentTrainerIndexList[i]))
            {
                int healthLost=currentPoke->hp()-slot.getRemainingHP();
                //if(healthLost >= 20 && healthLost <30 )
                //{
                if(curtrainer->getName()=="Big Malasada")
                {
                    playCard(currentTrainerIndexList[i]);
                    std::cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                }
                //                }else if(healthLost >=30)
                //                {
                if(curtrainer->getName()=="Potion")
                {
                    playCard(currentTrainerIndexList[i]);
                    std::cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

                }
            }
            //playCard(currentTrainerIndexList[i]);
        }*/

} else

{/*15 feb 7.30 b32 */
std::cout<<"there are no Trainers in your hand\n";
}
//**************************************************************************************************************************************************************************

//START ATTACKING
std::cout<<"\n\nCalculating Attack\n";
currentPoke = bench[0].active();
unsigned bestAttack;
bool shouldAttack = false;
for (int j = 0 ; j < slot.active()->attacks().size(); ++j)
{
    std::cout<<"Attact no - "<<j;
    if (canAttack(j))
    {
        bestAttack = j;
        shouldAttack = true;
    }else
    {
        std::cout<<" - FAIL\n";
    }
}
if (shouldAttack)
{
    std::cout<<" - SUCCESS\n";
    std::cout<<"pokemon will attack with attack no "<<bestAttack<<".\n\n";
}

return std::pair<bool, unsigned> {shouldAttack, bestAttack};
//******************************************************************************************************************************************************************************
}


