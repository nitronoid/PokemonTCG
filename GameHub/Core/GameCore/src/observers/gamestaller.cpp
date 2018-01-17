#include "observers/gamestaller.h"
#include <chrono>
#include <thread>

void GameStaller::startTurn()
{
  stall();
}

void GameStaller::attackUsed(PokemonCard*const, const unsigned)
{
  stall();
}

void GameStaller::effectUsed(const Ability * const, const PTCG::TRIGGER)
{
  stall();
}

void GameStaller::playCard(const size_t, Card*const)
{
  stall();
}

void GameStaller::moveCard(const PTCG::PLAYER, const PTCG::PILE, const PTCG::PILE, const size_t, Card * const)
{
  stall();
}

void GameStaller::knockOut(const PTCG::PLAYER, const size_t)
{
  stall();
}

void GameStaller::swapSlot(const PTCG::PLAYER, const size_t)
{
  stall();
}

void GameStaller::inspectSlot(const PTCG::PLAYER, const size_t)
{
  stall();
}

void GameStaller::inspectCard(const PTCG::PLAYER, const PTCG::PILE, const size_t)
{
  stall();
}


void GameStaller::stall() const
{
  std::this_thread::sleep_for(std::chrono::milliseconds(m_wait));
}
