#include "player.h"
#include "game.h"

Player::~Player() {}

void Player::playCard(const size_t &_index)
{
  m_parentGame.playCard(_index);
}

void Player::retreat()
{
  if(m_canRetreat)
  {
    constexpr auto filter = [](BoardSlot*const _slot){return !_slot->active();};
    auto switchChoice = m_parentGame.playerSlotChoice(PTCG::PLAYER::SELF,PTCG::PLAYER::SELF,PTCG::ACTION::MOVE,1, filter);
    auto bench = m_parentGame.viewBench(PTCG::PLAYER::SELF);
    if(bench.at(0).numEnergy() >= bench.at(0).active()->retreatCost() &&
       switchChoice[0] < 6 && switchChoice[0] != 0 &&
      bench.at(switchChoice[0]).numPokemon()>0)
    {
      // passing a lambda to return any energy card types
      std::function<bool(Card*const)> match = [](Card* const){return true;};
      //we need to choose our energy to discard
      auto choice = m_parentGame.playerEnergyChoice(
            PTCG::PLAYER::SELF,
            PTCG::PLAYER::SELF,
            PTCG::PILE::DISCARD,
            PTCG::ACTION::DISCARD,
            0,
            match,
            bench.at(0).active()->retreatCost());
      m_parentGame.removeEnergy(PTCG::PLAYER::SELF, PTCG::PILE::DISCARD,0,choice);
      m_parentGame.switchActive(PTCG::PLAYER::SELF, switchChoice[0]);
    }
  }
}


Game Player::getDummyGame() const
{
  return m_parentGame.clone();
}


std::vector<std::unique_ptr<Card>> Player::viewHand() const
{
  return m_parentGame.viewHand(PTCG::PLAYER::SELF);
}

std::vector<std::unique_ptr<Card>> Player::viewDiscard(const PTCG::PLAYER &_owner) const
{
  return m_parentGame.viewDiscard(_owner);
}

std::array<BoardSlot, 6> Player::viewBench(const PTCG::PLAYER &_owner) const
{
  return m_parentGame.viewBench(_owner);
}
