#include "player.h"
#include "game.h"

Player::~Player() = default;

void Player::playCard(const size_t &_index)
{
  m_parentGame.playCard(_index);
}

void Player::retreat()
{
  if(m_parentGame.canRetreat(PTCG::PLAYER::SELF))
  {
    m_parentGame.retreat();
    m_canRetreat = false;
  }
}

bool Player::canPlay(const size_t &_index)
{
  return m_parentGame.canPlay(_index);
}

Game Player::getDummyGame() const
{
  return m_parentGame.clone();
}

std::vector<std::unique_ptr<Card>> Player::viewHand() const
{
  return m_parentGame.viewHand(PTCG::PLAYER::SELF);
}

size_t Player::numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const
{
  return m_parentGame.viewPile(_owner, _pile).size();
}

std::vector<std::unique_ptr<Card>> Player::viewDiscard(const PTCG::PLAYER &_owner) const
{
  return m_parentGame.viewDiscard(_owner);
}

std::array<BoardSlot, 6> Player::viewBench(const PTCG::PLAYER &_owner) const
{
  return m_parentGame.viewBench(_owner);
}

bool Player::canRetreat() const
{
  return m_canRetreat;
}
