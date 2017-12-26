#include "game.h"
#include <iostream>
#include <algorithm>

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

void Game::init(const CardFactory &_factory, GuiModule * const _drawer, const std::string &_deckA, const std::string &_deckB)
{
  m_boards[0].m_deck.init(_factory.loadDeck(_deckA));
  m_boards[0].m_deck.shuffle();
  m_boards[1].m_deck.init(_factory.loadDeck(_deckB));
  m_boards[1].m_deck.shuffle();
  m_players[0].reset(new HumanPlayer(*this));
  m_players[1].reset(new HumanPlayer(*this));

  if(_drawer) m_drawer = _drawer;
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
    {
      if(!drawCard(board))
      {
        std::cout<<"Could not draw cards from deck of Player "<<i+1<<", deck file might be empty or corrupted."<<'\n';
        return;
      }
    }
    auto hand = board.m_hand.view();
    decltype (hand) pokemon;
    std::vector<size_t> indexes;
    for(size_t k = 0; k < hand.size(); ++k)
    {
      auto& card = hand[k];
      if(card->cardType() == PTCG::CARD::POKEMON)
      {
        pokemon.push_back(std::move(card));
        indexes.push_back(k);
      }
    }
    auto choice = player->chooseCards(PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::ACTION::PLAY, pokemon, 1);
    board.m_bench.put(board.m_hand.take(indexes[choice[0]]), 0);
  }
}

bool Game::drawCard(Board& _board)
{
  if (_board.m_deck.empty()) return false;
  auto topCard = _board.m_deck.takeTop();
  _board.m_hand.put(std::move(topCard));
  return true;
}

void Game::putToPile(const PTCG::PLAYER _owner, PTCG::PILE _dest, std::unique_ptr<Card> &&_card)
{
  auto& board = m_boards[playerIndex(_owner)];
  switch (_dest)
  {
    case PTCG::PILE::DECK:
      board.m_deck.put(std::move(_card));
      break;
    case PTCG::PILE::DISCARD:
      board.m_discardPile.put(std::move(_card));
      break;
    case PTCG::PILE::HAND:
      board.m_hand.put(std::move(_card));
      break;
    case PTCG::PILE::PRIZE:
      board.m_prizeCards.put(std::move(_card));
      break;
    default: break;
  }
}

std::unique_ptr<Card> Game::takeFromPile(const PTCG::PLAYER _owner, PTCG::PILE _dest, const unsigned _index)
{
  auto& board = m_boards[playerIndex(_owner)];
  std::unique_ptr<Card> ret;
  switch (_dest)
  {
    case PTCG::PILE::DECK:
      ret = board.m_deck.take(_index);
      break;
    case PTCG::PILE::DISCARD:
      ret = board.m_discardPile.take(_index);
      break;
    case PTCG::PILE::HAND:
      ret = board.m_hand.take(_index);
      break;
    case PTCG::PILE::PRIZE:
      ret = board.m_prizeCards.take(_index);
      break;
    default: break;
  }
  return ret;
}

void Game::switchActive(const PTCG::PLAYER &_player, const unsigned &_subIndex)
{
  if(_subIndex>5)
  {
    std::cout<<"Inex out of bench range when switching"<<'\n';
    return;
  }
  auto& board = m_boards[playerIndex(_player)];
  board.m_bench.switchActive(_subIndex);

}


//_cardIndices - target cards on board/hand... to move
bool Game::moveCards(std::vector<unsigned> _cardIndices,
                     const PTCG::PLAYER _owner,
                     const PTCG::PILE _origin,
                     const PTCG::PILE _destination,
                     const bool _reveal,
                     const std::vector<unsigned> _destIndex)
{
  //sort the input indices to avoid affecting take order in a vector
  std::sort(_cardIndices.begin(), _cardIndices.end(),std::greater<unsigned>());

  //if no particular index is specified in destination, do these
  if(_destIndex.empty())
  {
    for(unsigned i = 0; i<_cardIndices.size();++i)
    {
      putToPile(_owner,_destination, std::move(takeFromPile(_owner,_origin,_cardIndices.at(i))));
    }
    return true;

  }
  else
  {
    //for now, will implement later.
    return false;
  }
  return false;
}



void Game::nextTurn()
{
  // Get the current player
  auto& currentPlayer = m_players[m_turnCount % 2];
  Board& currentBoard = m_boards[m_turnCount % 2];
  if (m_drawer)
  {
    m_drawer->drawBoard(&m_boards[(m_turnCount + 1) % 2],false);
    m_drawer->drawBoard(&currentBoard, true);
  }
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

bool Game::evolve(const unsigned &_index)
{
  Board& board = m_boards[playerIndex(PTCG::PLAYER::SELF)];
  if(_index>5||board.m_bench.view().at(_index).numPokemon()==0)
  {
    std::cout<<"selected pokemon is out of bound or does not exist."<<'\n';
    return false;
  }
  if(board.m_bench.slotAt(_index)->getTurnPlayed()==0)
  {
    std::cout<<"This mon cannot evolve yet."<<'\n';
    return false;
  }
  //chooseCard here for valid Pokemon and return the card to attach to the evolving pokemon

  if(_index==0)
  {
    board.m_bench.slotAt(0)->removeAllConditions();
  }

  return true;
}
// Need to implement take single pokemon card from m_pokemon in Board Slot
bool Game::devolve(const PTCG::PLAYER &_player, const unsigned &_index)
{
  Board& board = m_boards[playerIndex(_player)];
  if(_index>5||board.m_bench.view().at(_index).numPokemon()==0)
  {
    std::cout<<"selected pokemon is out of bound or does not exist."<<'\n';
    return false;
  }

  return true;
}

void Game::applyCondition(const PTCG::PLAYER &_target, const PTCG::CONDITION &_condition)
{
  Board& board = m_boards[playerIndex(_target)];
  switch (_condition) {
    case PTCG::CONDITION::ASLEEP:
    {
      board.m_bench.slotAt(0)->addCondition(_condition);
      break;
    }
    case PTCG::CONDITION::BURNED:
    {
      board.m_bench.slotAt(0)->addCondition(_condition);
      break;
    }
    case PTCG::CONDITION::CONFUSED:
    {
      board.m_bench.slotAt(0)->addCondition(_condition);
      break;
    }
    case PTCG::CONDITION::PARALYZED:
    {
      board.m_bench.slotAt(0)->addCondition(_condition);
      break;
    }
    case PTCG::CONDITION::POISONED:
    {
      board.m_bench.slotAt(0)->addCondition(_condition);
      break;
    }
    default: break;
  }
}

void Game::removeCondition(const PTCG::PLAYER &_target, const PTCG::CONDITION &_condition)
{
  m_boards[playerIndex(_target)].m_bench.slotAt(0)->removeCondition(_condition);
}

void Game::removeAllCondition(const PTCG::PLAYER &_target)
{
  m_boards[playerIndex(_target)].m_bench.slotAt(0)->removeAllConditions();
}

void Game::poison()
{
  m_damageHandler.rawDamage(m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench,0,m_damageHandler.getPoison());

}

void Game::burn()
{
  m_damageHandler.rawDamage(m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench,0,m_damageHandler.getBurn());
  if(flipCoin(1))
  {
    m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench.slotAt(0)->removeCondition(PTCG::CONDITION::BURNED);
  }
}

void Game::paralysis()
{
  //TODO AFTER GAME LOOP
}

void Game::confuse()
{
  //TODO AFTER GAMELOOP
}
void Game::sleep()
{
  //TODO AFTER LOOP
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

size_t Game::playerIndex(const PTCG::PLAYER &_player) const
{
  return (m_turnCount+static_cast<size_t>(_player)) % 2;
}

std::array<std::unique_ptr<Card>,6> Game::viewPrize(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].m_prizeCards.view();
}

std::vector<std::unique_ptr<Card>> Game::viewDeck(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].m_deck.view();
}

std::vector<std::unique_ptr<Card>> Game::viewDiscard(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].m_discardPile.view();
}

std::array<BoardSlot, 6> Game::viewBench(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].m_bench.view();
}

std::vector<std::unique_ptr<Card>> Game::viewHand(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].m_hand.view();
}

unsigned Game::searchCountByName(std::string _name, const PTCG::PLAYER &_player, const PTCG::PILE &_target) const
{
  const Board& board = m_boards[playerIndex(_player)];
  std::vector<std::unique_ptr<Card>> temp;
  switch(_target)
  {
    case PTCG::PILE::DECK :
    {
      temp = board.m_deck.view();
      break;

    }
    case PTCG::PILE::DISCARD :
    {
      temp = board.m_discardPile.view();
      break;

    }
    case PTCG::PILE::HAND :
    {
      temp = board.m_hand.view();
      break;
    }
    default : break;
  }
  unsigned matchCount=0;
  for(unsigned m=0; m<temp.size(); ++m)
  {
    if(temp.at(m)->getName() == _name)
    {
      ++matchCount;
    }
  }
  return matchCount;
}

