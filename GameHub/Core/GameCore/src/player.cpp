#include "player.h"
#include "game.h"

void Player::playCard(const unsigned _index)
{

}

void Player::attack(const unsigned _index)
{

}

void Player::endTurn() const
{

}

void Player::retreat(const unsigned _replacement)
{

}

void Player::viewHand() const
{

}

void Player::viewBench() const
{

}

Game Player::getDummyGame() const
{
  return m_parentGame.clone();
}
