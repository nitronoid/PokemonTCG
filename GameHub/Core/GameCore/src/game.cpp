#include "game.h"

void Game::dealDamage(const int _damage)
{
  std::cout<<"Attack did: "<<_damage<<" damage!\n";
}

Game Game::clone() const
{
  return *this;
}

