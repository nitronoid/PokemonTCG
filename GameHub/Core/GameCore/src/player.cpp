#include "player.h"
#include "game.h"

Player::~Player() = default;

void Player::playCard(const size_t _index)
{
  m_subjectGame->playCard(_index);
}

void Player::inspectSlot(const PTCG::PLAYER _owner, const size_t _index)
{
  m_subjectGame->inspectSlot(_owner, _index);
}

void Player::retreat()
{
  if(m_subjectGame->canRetreat(PTCG::PLAYER::SELF))
  {
    m_subjectGame->retreat();
  }
}

bool Player::canPlay(const size_t &_index)
{
  return m_subjectGame->canPlay(_index);
}

Game Player::getDummyGame() const
{
  return m_subjectGame->dummyClone();
}

void Player::attachToGame(Game*const _newSubject)
{
  m_subjectGame = _newSubject;
}

std::vector<std::unique_ptr<Card>> Player::viewHand() const
{
  return m_subjectGame->viewHand(PTCG::PLAYER::SELF);
}

size_t Player::numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const
{
  return m_subjectGame->numCards(_owner, _pile);
}

std::vector<std::unique_ptr<Card>> Player::viewDiscard(const PTCG::PLAYER &_owner) const
{
  return m_subjectGame->viewDiscard(_owner);
}

std::array<BoardSlot, 6> Player::viewBench(const PTCG::PLAYER &_owner) const
{
  return m_subjectGame->viewBench(_owner);
}

