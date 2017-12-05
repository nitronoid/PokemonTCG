#include "player.h"
#include "game.h"

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
