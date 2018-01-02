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

void Game::drawHand(Board& io_board)
{
  for (int j = 0; j < 6; ++j) drawCard(io_board);
}

void Game::setBoard(Board& io_board, const size_t _active)
{
  io_board.m_bench.put(io_board.m_hand.take(_active), 0);
}

std::vector<size_t> Game::chooseActive(const PTCG::PLAYER _player)
{
  return playerCardChoice(
        _player,
        _player,
        PTCG::PILE::HAND,
        PTCG::ACTION::PLAY,
        [](auto _card)
  {
    if (_card->cardType() == PTCG::CARD::POKEMON)
    {
      return !static_cast<PokemonCard*>(_card)->stage();
    }
    return false;
  },
        1
  );
}

void Game::setupGame()
{
  std::vector<size_t> mulligans;
  for (size_t i = 0; i < 2; ++i)
  {
    Board& board = m_boards[i];
    drawHand(board);
    auto active = chooseActive(static_cast<PTCG::PLAYER>(i));
    if (!active.empty()) setBoard(board, active[0]);
    else mulligans.push_back(i);
  }
  doMulligans(mulligans);
}

void Game::doMulligans(const std::vector<size_t> &_mulligans)
{
  for (const auto i : _mulligans)
  {
    Board& board = m_boards[i];
    std::vector<size_t> active;
    while (active.empty())
    {
      PTCG::PLAYER currentPlayer = static_cast<PTCG::PLAYER>(i);
      // Generate consecutive integers for range of hand
      std::vector<size_t> indices(board.m_hand.view().size());
      std::iota (std::begin(indices), std::end(indices), 0);
      // Reveal the Hand
      revealCards(static_cast<PTCG::PLAYER>((i+1)%2), currentPlayer, PTCG::PILE::HAND, indices);
      // Move the hand back to the deck
      moveCards(indices, currentPlayer, PTCG::PILE::HAND, PTCG::PILE::DECK);
      shuffleDeck(currentPlayer);
      drawHand(board);
      active = chooseActive(currentPlayer);
    }
    setBoard(board, active[0]);
  }
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

std::unique_ptr<Card> Game::takeFromPile(const PTCG::PLAYER _owner, PTCG::PILE _dest, const size_t _index)
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
void Game::benchToPile(
    const PTCG::PLAYER &_player,
    const PTCG::PILE &_dest,
    std::function<bool(Card*const)> _match,
    const unsigned &_index
    )
{
  // Get the slot that we are moving from
  auto slot = m_boards[playerIndex(_player)].m_bench.slotAt(_index);
  // Check the slot has a pokemon before filtering
  auto rawPokemon = slot->active();
  if(rawPokemon && _match(rawPokemon))
  {
    // Move all the attached pokemon
    for (auto& poke : slot->detachPokemon())
      putToPile(_player,_dest, std::unique_ptr<Card>{poke.release()});
  }
  // Check the slot has a tool before filtering
  auto rawTool = slot->viewTool().get();
  if (rawTool && _match(rawTool))
  {
    // Detatch and move the tool card
    auto tool = slot->detachTool();
    putToPile(_player, _dest, std::unique_ptr<Card>{tool.release()});
  }
  // Get the card energy
  auto unfilteredEnergy = slot->viewEnergy();
  // Declare arrays to store our filtered results
  decltype(unfilteredEnergy) filteredEnergy;
  std::vector<size_t> positions;
  // Filter the energy cards
  filterCards(unfilteredEnergy, filteredEnergy, positions, _match);
  //sort to avoid index invalidation
  std::sort(positions.begin(), positions.end(),std::greater<size_t>());
  for (const auto pos : positions)
  {
    // Move all the energy
    auto energy = slot->detachEnergy(pos);
    putToPile(_player, _dest, std::unique_ptr<Card>{energy.release()});
  }
}

void Game::shuffleDeck(const PTCG::PLAYER _owner)
{
  m_boards[playerIndex(_owner)].m_deck.shuffle();
}

template<typename T>
void doubleVecSort(std::vector<T>&io_sorter, std::vector<T>&io_second)
{
  // Construct and fill a vector of consecutive indices
  std::vector<size_t> indices(io_sorter.size());
  std::iota (std::begin(indices), std::end(indices), 0);
  // Sort the indices based on the passed vector
  std::sort(indices.begin(), indices.end(), [&io_sorter](const T _a, const T _b)
  {
    return io_sorter[_a] > io_sorter[_b];
  }
  );

  // Reorder the two vectors based on the sorted indices
  // for all elements to put in place
  for(size_t i = 0; i < io_sorter.size() - 1; ++i)
  {
    // while the element i is not yet in place
    while(i != indices[i])
    {
      // swap it with the element at its final place
      size_t alt = indices[i];
      std::swap(io_sorter[i], io_sorter[alt]);
      std::swap(io_second[i], io_second[alt]);
      std::swap(indices[i], indices[alt]);
    }
  }
}

void Game::pileToBench(
    const PTCG::PLAYER &_player,
    const PTCG::PILE &_origin,
    std::vector<unsigned> &_pileIndex,
    std::vector<unsigned> &_benchIndex)
{
  if (_benchIndex.size() == _pileIndex.size() && !_pileIndex.empty())
  {
    doubleVecSort(_pileIndex, _benchIndex);
    auto& board = m_boards[playerIndex(_player)];
    for(size_t i = 0; i < _benchIndex.size(); ++i)
    {
      board.m_bench.slotAt(_benchIndex[i])->attachCard(takeFromPile(_player, _origin, _pileIndex[i]));
    }
  }
  else
  {
    std::cout<<"Missmatched destination and card indices.\n"
               "Amount of card indices: "<<_pileIndex.size()<<"\n"
                                                              "Amount of destination indices: "<<_benchIndex.size()<<"\n";
  }
}

std::vector<size_t> Game::freeSlots(const PTCG::PLAYER _owner)
{
  std::vector<size_t> ret;
  auto benchSlots = m_boards[playerIndex(_owner)].m_bench.view();
  for (size_t i = 0; i < benchSlots.size(); ++i)
  {
    if (!benchSlots[i].active()) ret.push_back(i);
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
bool Game::moveCards(
    std::vector<size_t> _cardIndices,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::PILE _destination,
    const bool _reveal,
    const std::vector<unsigned> _destIndex
    )
{
  //sort the input indices to avoid affecting take order in a vector
  std::sort(_cardIndices.begin(), _cardIndices.end(),std::greater<size_t>());

  //if no particular index is specified in destination, do these
  if(_destIndex.empty())
  {
    for(size_t i = 0; i<_cardIndices.size();++i)
    {
      putToPile(_owner,_destination, takeFromPile(_owner, _origin, _cardIndices[i]));
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

void Game::filterCards(
    std::vector<std::unique_ptr<Card>>& io_unfiltered,
    std::vector<std::unique_ptr<Card>>& io_filtered,
    std::vector<size_t>& io_originalPositions,
    std::function<bool(Card*const)> _match
    ) const
{
  if(!io_unfiltered.empty())
  {
    // Filter the cards based on the provided function
    for(size_t k = 0; k < io_unfiltered.size(); ++k)
    {
      auto& card = io_unfiltered[k];
      if(_match(card.get()))
      {
        // Move to our filtered vec
        io_filtered.push_back(std::move(card));
        // Save its original position
        io_originalPositions.push_back(k);
      }
    }
  }
}

void Game::filterPile(
    std::vector<std::unique_ptr<Card>>& io_filtered,
    std::vector<size_t>& io_originalPositions,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _pile,
    std::function<bool(Card*const)> _match
    ) const
{
  // Retrieve the unfiltered cards
  auto unfiltered = viewPile(_owner, _pile);
  filterCards(unfiltered, io_filtered, io_originalPositions, _match);
}

std::vector<size_t> Game::playerCardChoice(
    const PTCG::PLAYER _thinker,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    std::function<bool (Card * const)> _match,
    const unsigned _amount,
    const size_t _range
    )
{
  // Declare vectors to hold
  std::vector<size_t> choice;
  std::vector<size_t> positions;
  std::vector<std::unique_ptr<Card>> options;
  // Filter the origin pile based on the match functions
  filterPile(options, positions, _owner, _origin, _match);
  // Resize based on the choice given, if one was given
  if(options.size() > _range && _range)
    options.resize(_range);
  // Get the players choice from our filtered options
  choice = m_players[playerIndex(_thinker)]->chooseCards(_owner, _origin, _action, options, _amount);
  // Convert the player choice to the original pile indexes
  for (auto& pick : choice) pick = positions[pick];
  return choice;
}

std::vector<size_t> Game::playerSlotChoice(
    const PTCG::PLAYER _thinker,
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const unsigned _amount
    )
{
  std::vector<size_t> choice;
  std::vector<size_t> positions;
  std::vector<BoardSlot> options;
  auto benchArr = viewBench(_owner);
  for (size_t i = 0; i < benchArr.size(); ++i)
  {
    auto& slot = benchArr[i];
    if(slot.active())
    {
      options.push_back(std::move(slot));
      positions.push_back(i);
    }
  }

  choice = m_players[playerIndex(_thinker)]->chooseSlot(_owner, _action, options, _amount);
  // Convert the player choice to the original pile indexes
  for (auto& pick : choice) pick = positions[pick];
  return choice;
}

std::vector<std::unique_ptr<Card>> Game::viewPile(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const
{
  std::vector<std::unique_ptr<Card>> ret;
  // Get the owners board
  auto& board = m_boards[playerIndex(_owner)];
  using pile = PTCG::PILE;
  switch (_pile)
  {
    case pile::DECK :    {ret = board.m_deck.view(); break;}
    case pile::HAND :    {ret = board.m_hand.view(); break;}
    case pile::DISCARD : {ret = board.m_discardPile.view(); break;}
    case pile::PRIZE :
    {
      // Prize needs to be converted from an array to a vector
      for (auto& card : board.m_deck.view()) ret.push_back(std::move(card));
      break;
    }
    default: break;
  }
  return ret;
}

void Game::revealCards(
    const PTCG::PLAYER _learner,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const std::vector<size_t> &_indices
    )
{
  // Retrieve the specified origin pile
  auto pile = viewPile(_owner, _origin);
  // Prepare a vector to store the requested cards
  std::vector<std::unique_ptr<Card>> revealed;
  revealed.reserve(_indices.size());
  // Place the requested cards in our vector
  for (const auto i : _indices) revealed.push_back(std::move(pile[i]));
  // Triger the players callback for learning cards
  m_players[playerIndex(_learner)]->learnCards(
        _owner,
        _origin,
        _indices,
        revealed
        );
}

void Game::attack(PokemonCard* _pokemon, const unsigned _index)
{
  _pokemon->attack(_index, *this);
}

void Game::dealDamage(const int _damage, const unsigned _id)
{
  m_boards[playerIndex(PTCG::PLAYER::ENEMY)].m_bench.slotAt(_id)->takeDamage(_damage);
  std::cout<<"Attack did: "<<_damage<<" damage!\n";
}

void Game::healDamage(const int _heal, const unsigned _id)
{
  m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench.slotAt(_id)->removeDamage(_heal);
  std::cout<<"Healed: "<<_heal<<" damage!\n";
}

void Game::evolve(std::unique_ptr<PokemonCard> &_postEvo, const unsigned &_handIndex, const unsigned &_index)
{
  Board& board = m_boards[playerIndex(PTCG::PLAYER::SELF)];
  //if indexed bench is empty or out of bound
  if(_index>5)
  {
    std::cout<<"selected pokemon is out of bound."<<'\n';
  }
  //check if chosen card is the correct pokemon to evolve to
  else if(board.m_bench.slotAt(_index)->canEvolve(_postEvo,m_turnCount))
  {
    std::vector<unsigned> hand = std::vector<unsigned>(_handIndex);
    std::vector<unsigned> bench = std::vector<unsigned>(_index);
    //moving post evolution card from hand to chosen slot, need pileToBench
    pileToBench(PTCG::PLAYER::SELF,PTCG::PILE::HAND,hand,bench);
    //remove conditions if evolved pokemon is an active
    if(!_index) board.m_bench.slotAt(0)->removeAllConditions();
  }
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
  auto devolvedPokemon = std::unique_ptr<Card>(static_cast<Card*>(board.m_bench.slotAt(_index)->devolvePokemon().release()));
  board.m_hand.put(std::move(devolvedPokemon));
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
  unsigned ret = 0;
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


