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



void RoaringFluke::refreshFilteredHand(
        std::vector<std::unique_ptr<Card>>& io_hand,
        cardRefList& io_pokeList,
        cardRefList& io_energyList,
        cardRefList& io_trainerList,
        std::vector<int>& io_pokeIndexList,
        std::vector<int>& io_energyIndexList,
        std::vector<int>& io_trainerIndexList)
{
    io_hand=viewHand();
    io_pokeList.clear();
    io_pokeIndexList.clear();
    io_energyList.clear();
    io_energyIndexList.clear();
    io_trainerList.clear();
    io_trainerIndexList.clear();
    for (int i = 0 ; i < io_hand.size(); ++i)
    {
        auto& currentCard = io_hand[i];
        std::cout<<i+1<<" "<<currentCard->getName()<<" - "<<currentCard->getID()<<"\n";

        if (currentCard->cardType() == PTCG::CARD::ENERGY)
        {
            io_energyList.push_back(currentCard.get());
            io_energyIndexList.push_back(i);
        }else if(currentCard->cardType() == PTCG::CARD::POKEMON)
        {
            io_pokeList.push_back(currentCard.get());
            io_pokeIndexList.push_back(i);
        }else if(currentCard->cardType() == PTCG::CARD::ITEM || currentCard->cardType() == PTCG::CARD::SUPPORT)
        {
            io_trainerList.push_back(currentCard.get());
            io_trainerIndexList.push_back(i);
        }
    }
}

std::pair<bool, unsigned> RoaringFluke::turn()
{
    auto initHand = viewHand();
    // Random engine
    static std::random_device seed;
    static std::mt19937_64 eng(seed());


    cardRefList curEnergyList, curPokemonList, curTrainerList;
    std::cout<<"\nRoaring flukes Pokemon:\n\n";

    //------------------------------------------------we create lists based on card type in our deck to simplify AI access to cards---------------------------------------------
    std::vector<int>currentPokeIndexList;
    std::vector<int>currentEnergyIndexList;
    std::vector<int>currentTrainerIndexList;

    refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);

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
    size_t bestPos = 0;
    unsigned evoPoke = 0;


    //------------------------------------------------pokemon brain really starts here------------------------------------------------------------------------------------------

    //------------------------------------------------pokemon card managment starts here------------------------------------------------------------------------------------
    if (curPokemonList.size())
    {
        int w = 0;
        for (auto& card : curPokemonList)
        {
            PokemonCard* pokemon = static_cast<PokemonCard*>(card);
            PokemonCard* currentBest = static_cast<PokemonCard*>(curPokemonList[bestPos]);
            std::string preEv = pokemon->preEvolution();
            if (preEv.empty() != true)
            {
                std::cout<<pokemon->getName()<<" Has pre evoltion: '"<<preEv<<"'.\n";
                evoPoke = 0;
                for (auto& card : curPokemonList)
                {
                    PokemonCard* currentEv = static_cast<PokemonCard*>(card);
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
                            evoloc = w;

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
            ++w;
        }
        if (unplayedevo)
        {
            if (evoloc)playCard(currentPokeIndexList[evoloc]);
            unplayedevo = false;
            refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);
        }
        if (unplayeddevo)
        {
            if (devoloc)playCard(currentPokeIndexList[devoloc]);
            unplayeddevo = false;
            refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);
        }



        refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);
        int i = 0;
        for (auto& card : curPokemonList)
        {
            PokemonCard* pokemon = static_cast<PokemonCard*>(card);
            PokemonCard* currentBest = static_cast<PokemonCard*>(curPokemonList[bestPos]);
            if (pokemon->hp() > currentBest->hp())
            {
                bestPos = i;
            }
            ++i;
        }
        PokemonCard* bestHealth = static_cast<PokemonCard*>(curPokemonList[bestPos]);
        if (slot.getRemainingHP() <= 30) needswitch = true;
        if (canPlay(currentPokeIndexList[bestPos]))
        {
            std::cout<<"\n\nBest Health on Pokemon:\n"<<bestHealth->getName()<<" - "<<bestHealth->hp()<<"hp - Playable.\n\n";

            if (currentPoke->hp() < bestHealth->hp())
            {
                //if active has energy we need to hold horses
                playCard(currentPokeIndexList[bestPos]);
                refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);
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
                    PokemonCard* pokemon = static_cast<PokemonCard*>(curPokemonList[j]);

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
                if (needswitch)
                {
                    playCard(bestPos);
                    refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);
                }
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
            unsigned bestToAttach = 0;
            std::cout<<"about to match energy\n";
            for (int j = 0 ; j < requirements.size(); ++j)
            {
                for (int t = 0 ; (t < curEnergyList.size()) && !played; ++t)
                {
                    EnergyCard* energy = static_cast<EnergyCard*>(curEnergyList[t]);
                    if (requirements[j] == energy->type() || requirements[j] == PTCG::TYPE::COLOURLESS)
                    {
                        bestToAttach = t;
                        played = true;
                    }
                }

            }
            if (canPlay(!currentEnergyIndexList.empty() && currentEnergyIndexList[bestToAttach]))
            {
                playCard(currentEnergyIndexList[bestToAttach]);
                refreshFilteredHand(initHand, curPokemonList, curEnergyList, curTrainerList,currentPokeIndexList, currentEnergyIndexList, currentTrainerIndexList);
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


