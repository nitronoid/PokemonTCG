#include "player.h"
#include "game.h"

Player::~Player() {}

void Player::playCard(const unsigned _index)
{

}

void Player::retreat(const unsigned _replacement)
{
  if(m_canRetreat)
  {
    auto bench = m_parentGame.viewBench(PTCG::PLAYER::SELF);
    if(bench.at(0).numEnergy() >= bench.at(0).active()->retreatCost() &&
       _replacement < 6 && _replacement != 0 &&
      bench.at(_replacement).numPokemon()>0)
    {
      std::function<bool(Card*const)> match;
      //we need to choose our energy to discard
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
