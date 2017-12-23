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

void Game::init(const CardFactory &_factory, const std::string &_deckA, const std::string &_deckB)
{
  m_boards[0].m_deck.init(_factory.loadDeck(_deckA));
  m_boards[1].m_deck.init(_factory.loadDeck(_deckB));
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
  for (size_t i = 0; i < 2; ++i)
  {
    auto& player = m_players[i];
    Board& board = m_boards[i];
    for (int j = 0; j < 6; ++j)
      if(!drawCard(board))
        {
          std::cout<<"Could not draw cards from deck of Player "<<i+1<<", deck file might be empty or corrupted."<<'\n';
          return;
        }
    auto choice = player->chooseCard(PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::ACTION::PLAY, board.m_hand.view(), 1);
    board.m_bench.put(board.m_hand.take(choice[0]), 0);
  }
}

bool Game::drawCard(Board& _board)
{
  if (_board.m_deck.empty()) return false;
  auto topCard = _board.m_deck.takeTop();
  _board.m_hand.put(std::move(topCard));
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

void Game::dealDamage(const unsigned _damage, const unsigned _id)
{
  std::cout<<"Attack did: "<<_damage<<" damage!\n";
}

unsigned Game::flipCoin(const unsigned _num)
{
  static unsigned ret = 0;
  static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
  for(unsigned i  = 0; i<_num;++i)
  {
      if(gen())
      {
          ++ret;
      }
  }
  std::cout<<"Flipping coin...."<<ret<<" heads, "<<_num-ret<<" tails."<<'\n';
  return ret;
}

Game Game::clone() const
{
  return *this;
}

std::array<std::unique_ptr<Card>,6> Game::viewPrize(const PTCG::PLAYER &_player) const
{
  int player = (m_turnCount+static_cast<int>(_player))%2;
  return m_boards[player].m_prizeCards.view();
}

std::vector<std::unique_ptr<Card>> Game::viewDeck(const PTCG::PLAYER &_player) const
{
  int player = (m_turnCount+static_cast<int>(_player))%2;
  return m_boards[player].m_deck.view();
}

std::vector<std::unique_ptr<Card>> Game::viewDiscard(const PTCG::PLAYER &_player) const
{
  int player = (m_turnCount+static_cast<int>(_player))%2;
  return m_boards[player].m_discardPile.view();
}

std::array<std::unique_ptr<BoardSlot>, 6> Game::viewBench(const PTCG::PLAYER &_player) const
{

  int player = (m_turnCount+static_cast<int>(_player))%2;
  return m_boards[player].m_bench.view();
}

std::vector<std::unique_ptr<Card>> Game::viewHand(const PTCG::PLAYER &_player) const
{
  int player = (m_turnCount+static_cast<int>(_player))%2;
  return m_boards[player].m_hand.view();
}



