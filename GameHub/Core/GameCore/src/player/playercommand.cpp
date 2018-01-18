#include "player/playercommand.h"
#include "player/humanplayer.h"
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
  _player.setTurnEnd();
}

void RetreatCMD::execute(HumanPlayer &_player)
{
  _player.retreat();
}

void SkipCMD::execute(HumanPlayer &_player)
{
  _player.setTurnEnd();
}

void ExitCMD::execute(HumanPlayer &_player)
{
  _player.setTurnEnd();
}

void RestartCMD::execute(HumanPlayer &_player)
{
  _player.setTurnEnd();
}

void InspectSlotCMD::execute(HumanPlayer &_player)
{
  static constexpr auto self = PTCG::PLAYER::SELF;
  auto optionArr = _player.viewBench(self);
  // Copy across the slots into option if they are occupied
  std::vector<BoardSlot> options;
  std::copy_if(
        optionArr.begin(),
        optionArr.end(),
        std::back_inserter(options),
        [](auto& slot){ return slot.active(); }
  );
  auto choice = _player.chooseSlot(self, PTCG::ACTION::VIEW, options, 1);
  _player.inspectSlot(self, choice[0]);
}

void InspectCardCMD::execute(HumanPlayer &_player)
{
  static constexpr auto self = PTCG::PLAYER::SELF;
  static constexpr auto pile = PTCG::PILE::HAND;
  auto options = _player.viewHand();
  auto choice = _player.chooseCards(self, pile, PTCG::ACTION::VIEW, options, 1);
  _player.inspectCard(self, pile, choice[0]);
}
