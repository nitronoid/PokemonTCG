#include "game.h"

void Game::dealDamage(const int _damage)
{
  std::cout<<"Attack did: "<<_damage<<" damage!\n";
}

Game Game::clone() const
{
  return *this;
}

void Game::play()
{

}

void Game::endTurn()
{
  ++m_turnCount;
  m_turnFinished = true;
}
