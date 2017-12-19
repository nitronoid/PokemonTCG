#include "player.h"
#include "game.h"

Player::~Player() {}

void Player::playCard(const unsigned _index)
{

}

void Player::retreat(const unsigned _replacement)
{

}

Game Player::getDummyGame() const
{
  return m_parentGame.clone();
}


std::vector<std::unique_ptr<Card>> Player::viewHand() const
{

  //TODO FOR ERIC
  return std::vector<std::unique_ptr<Card>>{};
}

std::vector<std::unique_ptr<Card>> Player::viewDiscard(const PTCG::PLAYER _owner) const
{
  //TODO FOR ERIC
  return std::vector<std::unique_ptr<Card>>{};
}

std::array<std::unique_ptr<BoardSlot>, 6> Player::viewBench(const PTCG::PLAYER _owner) const
{
  //TODO FOR ERIC
  return std::array<std::unique_ptr<BoardSlot>, 6>{};
}
