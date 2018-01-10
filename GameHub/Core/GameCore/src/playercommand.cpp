#include "playercommand.h"
#include "game.h"

void PlayCardCMD::execute(HumanPlayer &_player)
{
    // Play cards
    auto card = _player.chooseCards(PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::ACTION::PLAY, _player.viewHand(), 1);
    if (!card.empty()) _player.playCard(card[0]);
    else std::cout<<"Hand is empty."<<std::endl;

}

void AttackCMD::execute(HumanPlayer &_player)
{
    unsigned attack = _player.viewBench()[0].active()->attackNum();
    unsigned len = attack;
    do
    {
        std::cout<<"Pick an attack from 1 - "<<len<<std::endl;
        std::cin>>attack;
    } while (!std::cin.fail() && attack > len);
    _player.setAttack(attack);

}

void RetreatCMD::execute(HumanPlayer &_player)
{

}
