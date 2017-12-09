#include "game.h"
#include <iostream>

Game::Game(const Game &_original) :
  m_playableCards(_original.m_playableCards),
  m_turnPhase(_original.m_turnPhase),
  m_turnCount(_original.m_turnCount)
{
  for (size_t i = 0; i < m_players.size(); ++i)
  {
    if (_original.m_players[i]) m_players[i].reset( _original.m_players[i]->clone());
  }
}

void Game::start()
{
  setupGame();
  while(!m_gameFinished)
  {
    nextTurn();
  }
}

void Game::setupGame()
{

}

bool Game::drawCard(Board& _board)
{
  if (_board.m_deck.empty()) return false;
  auto topCard = _board.m_deck.takeTop();
  _board.m_hand.putLast(std::move(topCard));
  return true;
}

void Game::nextTurn()
{
  // Get the current player
  auto& currentPlayer = m_players[m_turnCount % 2];
  Board& currentBoard = m_boards[m_turnCount % 2];

  // Attempt to draw a card
  if (drawCard(currentBoard))
  {
    // Execute the players turn function
    auto attackDecision = currentPlayer->turn();
    if (attackDecision.first)
        attack(currentBoard.m_bench.active(), attackDecision.second);
    std::cout<<m_turnCount<<'\n';
    ++m_turnCount;
  }
  // Draw failed
  else m_gameFinished = true;
}

void Game::attack(PokemonCard* _pokemon, const unsigned _index)
{
  _pokemon->attack(_index, *this);
}

void Game::dealDamage(const int _damage)
{
  std::cout<<"Attack did: "<<_damage<<" damage!\n";
}

Game Game::clone() const
{
  return *this;
}

