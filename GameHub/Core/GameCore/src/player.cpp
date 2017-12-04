#include "player.h"
#include "game.h"

void Player::playCard(const unsigned _index)
{

}

void Player::attack(const std::string &_name)
{
  m_activePokemon.pokemon()->attack(_name, m_parentGame);
  endTurn();
}

void Player::endTurn() const
{
  m_parentGame.endTurn();
}

void Player::retreat(const unsigned _replacement)
{
  // Bench is empty?
  if (!m_bench.numBenched())
  {
    // Can't retreat with an empty bench
  }
  // Player has enough energy to retreat?
  else if (m_activePokemon.energy().size() > m_activePokemon.pokemon()->retreatCost())
  {
    // We want to keep all the slot information anyway so we just swap them

    // TODO: Implement a non-copying swap
    //std::swap(m_activePokemon, m_bench.slotAt(_replacement));
  }
  else
  {
    // Need more energy
  }
}

Hand& Player::hand() const
{
    return m_hand;
}

Bench& Player::bench() const
{
    return m_bench;
}

Game Player::getDummyGame() const
{
  return m_parentGame.clone();
}
