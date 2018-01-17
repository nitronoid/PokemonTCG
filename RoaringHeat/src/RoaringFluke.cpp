#include "RoaringFluke.h"
#include "playercommand.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <functional>

Player* RoaringFluke::clone() const
{
    return new RoaringFluke(*this);
}


std::string RoaringFluke::deckName() const
{
    return "test_deck.json";
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
        const unsigned _amount
        )
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
        }else
        {
            curTrainerList.push_back(currentCard);
            currentTrainerIndexList.push_back(i);
        }
    }


    std::cout<<"\nNumber of Pokemon - "<<curPokemonList.size()<<".\n";
    std::cout<<"Number of Energy - "<<curEnergyList.size()<<".\n";
    std::cout<<"Number of Trainers - "<<curTrainerList.size()<<".\n\n";
    //gets our & enemys current active pokemon and stores them
    //[
    PokemonCard* currentPoke = viewBench()[0].active();
    PokemonCard* enCurrentPoke = viewBench(PTCG::PLAYER::ENEMY)[0].active();
    auto slot = viewBench()[0];
    auto enslot  = viewBench(PTCG::PLAYER::ENEMY)[0];
    //]
    std::cout<<"Current Active: "<<currentPoke->getName()<<" - "<<currentPoke->hp()<<"hp.\n\n";
    bool needswitch = false;
    bool switchfound = false;
    size_t bestPos = 0;
    int i = 0;

    for (auto& card : curPokemonList)
    {
        PokemonCard* pokemon = static_cast<PokemonCard*>(card.get().get());
        PokemonCard* currentBest = static_cast<PokemonCard*>(curPokemonList[bestPos].get().get());
        if (pokemon->hp() > currentBest->hp())
        {
            bestPos = i;
        }
        ++i;
    }

    PokemonCard* bestHealth = static_cast<PokemonCard*>(curPokemonList[bestPos].get().get());

    if (slot.getRemainingHP() <= 30) needswitch = true;
    if (canPlay(currentPokeIndexList[bestPos]))
    {
        std::cout<<"Best Health on Pokemon:\n"<<bestHealth->getName()<<" - "<<bestHealth->hp()<<"hp - Playable.\n\n";

        if (currentPoke->hp() < bestHealth->hp())
        {

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




    //energy
    currentPoke = viewBench()[0].active();
    signed target = 0;
    for (auto& attack : slot.active()->attacks())
    {
        int curr = attack.requirements().size();
        if (curr > target)
            target = curr;
    }
    std::cout<<"number of energy on main - "<<slot.numEnergy()<<"\nnumber of energy needed for best attack - "<<target<<".\n";
    if (slot.numEnergy() <= target)
    {
        std::vector<Attack> attacks = currentPoke->attacks();
        auto requirements = attacks[attacks.size() - 1].requirements();
        bool played = false;
        for (int j = 0 ; j < requirements.size(); ++j)
        {
            for (int t = 0 ; (t < curEnergyList.size()) && !played; ++t)
            {
                EnergyCard* energy = static_cast<EnergyCard*>(curEnergyList[t].get().get());
                if ((requirements[j] == energy->type()) || (requirements[j] == PTCG::TYPE::COLOURLESS))
                {
                    playCard(currentEnergyIndexList[t]);
                    played = true;
                }
            }
        }
    }




    // Should we attack?
    bool doAttack = randomishBool();
    unsigned attackNum = viewBench().at(0).active()->attackNum();
    std::uniform_int_distribution<unsigned> agen(0, attackNum - 1);

    // Return the decision
    return std::pair<bool, unsigned> {doAttack, agen(eng)};
}


