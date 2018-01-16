#include "game.h"
#include <iostream>
#include <algorithm>
#include "blankcard.h"

Game::Game(const Game &_original) :
  m_playableCards(_original.m_playableCards),
  m_turnCount(_original.m_turnCount)
{}

void Game::init(const CardFactory &_factory, Player*const io_playerA, Player*const io_playerB)
{
  m_boards[0].deck()->init(_factory.loadDeck(io_playerA->deckName()));
  m_boards[0].deck()->shuffle();
  m_boards[1].deck()->init(_factory.loadDeck(io_playerB->deckName()));
  m_boards[1].deck()->shuffle();
  m_players[0] = io_playerA;
  m_players[1] = io_playerB;
}

void Game::start()
{
  setupGame();
  while(!m_gameFinished)
  {
    nextTurn();
  }
}

void Game::registerObserver(GameObserver*const _observer)
{
  _observer->setGame(this);
  m_observers.push_back(_observer);
}

void Game::inspectSlot(const PTCG::PLAYER _owner, const size_t _index)
{
  notify<Event::INSPECT_SLOT>(_owner, _index);
}

void Game::inspectCard(const PTCG::PLAYER _owner, const PTCG::PILE _pile,  const size_t _index)
{
  notify<Event::INSPECT_CARD>(_owner, _pile, _index);
}

Board* Game::getBoard(const PTCG::PLAYER _owner)
{
  return &m_boards[playerIndex(_owner)];
}

void Game::playPokemon(PokemonCard* const _pokemon, const size_t _index)
{
  // Not basic
  if (_pokemon->stage())
  {
    // Choose from slots with pokemon, that match the pre-evolution
    const auto filter = [name = _pokemon->preEvolution()](auto const _slot)
    {
      return _slot->active() && _slot->active()->getName() == name;
    };
    auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
    if (!slotChoice.empty())
      evolve(_pokemon, _index, slotChoice[0]);
  }
  // Basic Pokemon
  else
  {
    // Use default filter to find empty slots
    static constexpr auto filter = [](BoardSlot*const _slot){return !_slot->active();};
    auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
    // Check a choice was available
    if (!slotChoice.empty())
    {
      // Move the pokemon into the slot
      pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_index}, slotChoice);
      // Set the turn played for this slot
      m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench.slotAt(slotChoice[0])->setTurnPlayed(m_turnCount);
    }
  }
}

void Game::playItem(TrainerCard* const _item, const size_t _index)
{
  // Need to move first as the ability could invalidate _index
  moveCards({_index}, PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::PILE::DISCARD);
  _item->activateAbility(*this);
}

void Game::playTool(TrainerCard* const, const size_t _index)
{
  // Slots with a pokemon that has no tool attached
  static constexpr auto filter = [](BoardSlot*const _slot){ return _slot->active() && !_slot->viewTool();};
  auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
  if (!slotChoice.empty())
    pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_index}, slotChoice);
}

void Game::playEnergy(EnergyCard* const, const size_t _index)
{
  // Choose from slots with pokemon
  static constexpr auto filter = [](BoardSlot*const _slot){return _slot->active();};
  auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
  if (!slotChoice.empty())
  {
    //_energy->activateAbility(*this);
    pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_index}, slotChoice);
    m_playableCards.erase(PTCG::CARD::ENERGY);
  }
}

void Game::playSupport(TrainerCard* const _support, const size_t _index)
{
  _support->activateAbility(*this);
  moveCards({_index}, PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::PILE::DISCARD);
  m_playableCards.erase(PTCG::CARD::SUPPORT);
}

bool Game::canPlay(const size_t _index)
{
  auto card = m_boards[playerIndex(PTCG::PLAYER::SELF)].hand()->cardAt(_index);
  return canPlay(card);
}

bool Game::canPlay(Card*const _card)
{
  return _card->canPlay(*this) && m_playableCards.count(_card->cardType());
}


bool Game::canAttack(const size_t _index)
{
  auto slot = m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench.slotAt(0);
  return slot->active() && slot->active()->canAttack(*this, _index, slot->energyMSet());
}

void Game::playCard(const size_t _index)
{
  auto chosenCard = m_boards[playerIndex(PTCG::PLAYER::SELF)].hand()->cardAt(_index);
  if (canPlay(chosenCard))
  {
    chosenCard->playCard(*this, _index);
    notify<Event::PLAY_CARD>(_index, chosenCard);
  }
}

void Game::drawHand(const PTCG::PLAYER _player)
{
  for (int j = 0; j < 6; ++j) drawCard(_player);
}

void Game::setBoard(Board& io_board, const size_t _active)
{
  io_board.m_bench.put(io_board.hand()->take(_active), 0);
  for (int i = 0; i < 6; ++i)
    io_board.prizeCards()->put(io_board.deck()->takeTop());
}

std::vector<size_t> Game::chooseActive(const PTCG::PLAYER _player, const PTCG::PILE _origin)
{
  static constexpr auto basicFilter = [](auto _card)
  {
    if (_card->cardType() == PTCG::CARD::POKEMON)
      return !static_cast<PokemonCard*>(_card)->stage();
    return false;
  };
  return playerCardChoice(
        _player,
        _player,
        _origin,
        PTCG::ACTION::PLAY,
        basicFilter,
        1
        );
}

std::vector<size_t> Game::chooseReplacement(const PTCG::PLAYER _player)
{
  static constexpr auto basicFilter = [](auto _slot) -> bool
  {
    return _slot->active();
  };
  return playerSlotChoice(
        _player,
        _player,
        PTCG::ACTION::PLAY,
        1,
        basicFilter
        );
}

bool Game::playerAgree(const PTCG::PLAYER _thinker, const PTCG::ACTION _action)
{
  return m_players[playerIndex(_thinker)]->agree(_action);
}

void Game::setupGame()
{
  std::vector<size_t> mulligans;
  for (const auto p : {PTCG::PLAYER::SELF, PTCG::PLAYER::ENEMY})
  {
    Board& board = m_boards[playerIndex(p)];
    drawHand(p);
    auto active = chooseActive(p);
    if (!active.empty()) setBoard(board, active[0]);
    else mulligans.push_back(playerIndex(p));
  }
  doMulligans(mulligans);
}

void Game::doMulligans(std::vector<size_t> &io_mulligans)
{
  // Keep track of the size of the vector
  size_t size = io_mulligans.size();
  for (size_t i = 0; i < size; ++i)
  {
    // get the player index at this point
    const size_t index = io_mulligans[i];
    // use the index to get the board and player flags
    Board& currentPlayerBoard = m_boards[index];
    auto currentPlayer = static_cast<PTCG::PLAYER>(index);
    auto enemyPlayer = static_cast<PTCG::PLAYER>((index+1)%2);
    // Generate consecutive integers for range of hand
    std::vector<size_t> indices(currentPlayerBoard.hand()->numCards());
    std::iota (std::begin(indices), std::end(indices), 0);
    // Reveal the Hand
    revealCards(enemyPlayer, currentPlayer, PTCG::PILE::HAND, indices);
    // Move the hand back to the deck
    moveCards(indices, currentPlayer, PTCG::PILE::HAND, PTCG::PILE::DECK);
    // Shuffle and redraw the hand
    shuffleDeck(currentPlayer);
    drawHand(currentPlayer);
    // Ask the player to choose an active pokemon from their hand
    auto active = chooseActive(currentPlayer);
    // If they were able to we set the board up
    if (!active.empty())
      setBoard(currentPlayerBoard, active[0]);
    // Otherwise they will need to mulligan again
    else
    {
      // If this was the last scheduled mulligan, then we are now on a streak
      // We must therefor offer the enemy the choice of drawing a card
      if ((i == size - 1) && playerAgree(enemyPlayer, PTCG::ACTION::DRAW))
        drawCard(enemyPlayer);
      // Then schedule another mulligan for this player
      io_mulligans.push_back(index);
      // Update the size
      size = io_mulligans.size();
    }
  }
}

void Game::clearEffects()
{
  // Remove all effects for this player
  m_effectQueue.erase(std::remove_if(
                        m_effectQueue.begin(),
                        m_effectQueue.end(),
                        [this](auto ability)
  {
    return ability.first == m_turnCount;
  }
  ), m_effectQueue.end());
}

std::vector<Ability> Game::filterEffects(const PTCG::TRIGGER _trigger)
{
  std::vector<Ability> ret;
  for (const auto & effect : m_effectQueue)
  {
    // only get the effects for this turn
    if (effect.first == m_turnCount && effect.second.getTrigger() == _trigger)
      ret.push_back(effect.second);
  }
  return ret;
}

void Game::executeTurnEffects(const PTCG::TRIGGER _trigger)
{
  for (const auto & effect : filterEffects(_trigger))
  {
    effect.use(*this);
    notify<Event::EFFECT_USED>(&effect, _trigger);
  }
}

void Game::addEffect(const PTCG::PLAYER _affected, const unsigned _wait, const Ability &_effect)
{
  // Calculate the turn that this effect should be executed
  // Flag of enemy will offset the turn by 1
  // We multiply wait by 2 as it is the amount of turns that the affected player should wait
  auto executionTurn = m_turnCount + static_cast<unsigned>(_affected) + _wait * 2;
  m_effectQueue.push_back({executionTurn, _effect});
}

bool Game::checkForKnockouts()
{
  bool gameOver = false;
  for (const auto p : {PTCG::PLAYER::SELF, PTCG::PLAYER::ENEMY})
  {
    auto& board = m_boards[playerIndex(p)];
    for (size_t j = 0; j < 6; ++j)
    {
      auto slot = board.m_bench.slotAt(j);
      if (slot->active())
        gameOver = gameOver || handleKnockOut(p, j);
    }
  }
  m_gameFinished = gameOver;
  return gameOver;
}

void Game::resetPlayable()
{
  using crd = PTCG::CARD;
  m_playableCards.insert({crd::ENERGY, crd::ITEM, crd::POKEMON, crd::STADIUM, crd::SUPPORT, crd::TOOL});
}


void Game::nextTurn()
{
  // Get the current player
  size_t playerId = playerIndex(PTCG::PLAYER::SELF);
  auto currentPlayer = m_players[playerId];
  Board& currentBoard = m_boards[playerId];
  resetPlayable();
  // Ascii print the board
  notify<Event::START_TURN>();
  // Apply all effects that are triggered by the start of a turn
  executeTurnEffects(PTCG::TRIGGER::START);
  // The effects could have knocked out a pokemon so we check
  // Attempt to draw a card
  if (!checkForKnockouts() && drawCard(PTCG::PLAYER::SELF))
  {
    // Execute the players turn function
    auto attackDecision = currentPlayer->turn();
    if (attackDecision.first && canAttack(attackDecision.second))
    {
      // Apply all attack triggered effects
      executeTurnEffects(PTCG::TRIGGER::ATTACK);
      attack(currentBoard.m_bench.active(), attackDecision.second);
      // The effects/attack could have knocked out a pokemon so we check
      checkForKnockouts();
    }
    if (!m_gameFinished)
    {
      // Now that damage calc is over, we remove any damage/defense bonuses
      currentBoard.m_bench.activeStatus()->resetForNextTurn();
      //Resolve all between-turn status conditions
      resolveAllEndConditions(PTCG::PLAYER::SELF);
      // Apply all effects triggered by the end of a turn
      executeTurnEffects(PTCG::TRIGGER::END);
      // The effects could have knocked out a pokemon so we check
      checkForKnockouts();
      // Remove all the effects for this turn from the queue, now that we executed them all
      clearEffects();
    }
    ++m_turnCount;
  }
  // Draw failed
  else m_gameFinished = true;
}

void Game::addBonusDamage(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player)
{
  m_boards[playerIndex(_player)].m_bench.activeStatus()->addBonusDamage(_order, _value);
}

void Game::addBonusDefense(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player)
{
  m_boards[playerIndex(_player)].m_bench.activeStatus()->addBonusDefense(_order,_value);
}
bool Game::drawCard(const PTCG::PLAYER _player)
{
  Board& board = m_boards[playerIndex(_player)];
  auto deck = board.deck();
  if (deck->empty()) return false;
  auto topCard = deck->takeTop();
  auto rawCard = topCard.get();
  board.hand()->put(std::move(topCard));
  notify<Event::MOVE_CARD>(_player, PTCG::PILE::DECK, PTCG::PILE::HAND, deck->numCards(), rawCard);
  return true;
}

void Game::putToPile(const PTCG::PLAYER _owner, PTCG::PILE _dest, std::unique_ptr<Card> &&_card)
{
  auto& board = m_boards[playerIndex(_owner)];
  board.pile(_dest)->put(std::move(_card));
}

std::unique_ptr<Card> Game::takeFromPile(const PTCG::PLAYER _owner, PTCG::PILE _dest, const size_t _index)
{
  auto& board = m_boards[playerIndex(_owner)];
  return board.pile(_dest)->take(_index);
}
void Game::benchToPile(
    const PTCG::PLAYER &_owner,
    const PTCG::PILE &_dest,
    std::function<bool(Card*const)> _match,
    const size_t &_index
    )
{
  // Get the slot that we are moving from
  auto slot = m_boards[playerIndex(_owner)].m_bench.slotAt(_index);
  // Check the slot has a pokemon before filtering
  auto rawPokemon = slot->active();
  if(rawPokemon && _match(rawPokemon))
  {
    // Move all the attached pokemon
    for (auto& poke : slot->detachPokemon())
      putToPile(_owner,_dest, std::unique_ptr<Card>{poke.release()});
  }
  // Check the slot has a tool before filtering
  auto rawTool = slot->viewTool().get();
  if (rawTool && _match(rawTool))
  {
    // Detatch and move the tool card
    auto tool = slot->detachTool();
    putToPile(_owner, _dest, std::unique_ptr<Card>{tool.release()});
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
    putToPile(_owner, _dest, std::unique_ptr<Card>{energy.release()});
  }
}

void Game::shuffleDeck(const PTCG::PLAYER _owner)
{
  m_boards[playerIndex(_owner)].deck()->shuffle();
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
    std::vector<size_t> _pileIndex,
    std::vector<size_t> _benchIndex
    )
{
  if ((_benchIndex.size() == _pileIndex.size()) && !_pileIndex.empty())
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
    std::cout<<"Missmatched destination and card indices.\n"<<
               "Amount of card indices: "<<_pileIndex.size()<<"\n"<<
               "Amount of destination indices: "<<_benchIndex.size()<<"\n";
  }
}

std::vector<size_t> Game::filterSlots(const PTCG::PLAYER _owner, std::function<bool(BoardSlot*const)> _match) const
{
  std::vector<size_t> ret;
  auto benchSlots = viewBench(_owner);
  for (size_t i = 0; i < benchSlots.size(); ++i)
  {
    if (_match(&benchSlots[i])) ret.push_back(i);
  }
  return ret;
}


std::vector<size_t> Game::freeSlots(const PTCG::PLAYER _owner) const
{
  return filterSlots(_owner, [](BoardSlot*const _slot){return !_slot->active();});
}

std::vector<size_t> Game::nonFreeSlots(const PTCG::PLAYER _owner) const
{
  return filterSlots(_owner, [](BoardSlot*const _slot){return _slot->active();});
}

void Game::retreat()
{
  static constexpr auto self = PTCG::PLAYER::SELF;
  const auto filter = [](BoardSlot*const _slot){return _slot->active();};
  auto replacement = playerSlotChoice(self, self, PTCG::ACTION::MOVE, 1, filter, true);
  if (!replacement.empty())
  {
    auto& bench = m_boards[playerIndex(self)].m_bench;
    auto slot = bench.slotAt(0);
    static constexpr auto  match = [](Card* const){return true;};
    auto choice = playerEnergyChoice(
          self,
          self,
          PTCG::PILE::DISCARD,
          PTCG::ACTION::DISCARD,
          0,
          match,
          slot->active()->retreatCost()
          );
    if (!choice.empty())
    {
      removeEnergy(self, PTCG::PILE::DISCARD, 0, choice);
      switchActive(self, replacement[0]);
      bench.activeStatus()->setCanRetreat(false);
      notify<Event::SWAP_SLOT>(self, replacement[0]);
    }
  }
}

void Game::switchActive(const PTCG::PLAYER &_player, const size_t &_subIndex)
{
  auto& board = m_boards[playerIndex(_player)];
  board.m_bench.switchActive(_subIndex);
}

//_cardIndices - target cards on board/hand... to move
void Game::moveCards(
    std::vector<size_t> _cardIndices,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::PILE _destination
    )
{
  //sort the input indices to avoid affecting take order in a vector
  std::sort(_cardIndices.begin(), _cardIndices.end(),std::greater<size_t>());
  for(const auto i : _cardIndices)
  {
    auto taken = takeFromPile(_owner, _origin, i);
    auto rawCard = taken.get();
    putToPile(_owner,_destination, std::move(taken));
    notify<Event::MOVE_CARD>(_owner, _origin, _destination, i, rawCard);
  }
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

std::vector<size_t> Game::playerConditionChoice(
    const PTCG::PLAYER _thinker,
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<PTCG::CONDITION> _options,
    const unsigned _amount
    )
{
  auto relOwner = relativeOwner(_thinker, _owner);
  return m_players[playerIndex(_thinker)]->chooseConditions(relOwner, _action, _options, _amount);
}

std::vector<size_t> Game::playerCardChoice(
    const PTCG::PLAYER _thinker,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    std::function<bool (Card * const)> _match,
    const unsigned _amount,
    const bool _known,
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
  // If the options are not public knowledge to the thinker we replace them with blanks
  if (!_known)
    std::generate(
          options.begin(),
          options.end(),
          [](){ return std::unique_ptr<Card>(new BlankCard); }
    );
  auto relOwner = relativeOwner(_thinker, _owner);
  // Get the players choice from our filtered options
  choice = m_players[playerIndex(_thinker)]->chooseCards(relOwner, _origin, _action, options, _amount);
  // Convert the player choice to the original pile indexes
  for (auto& pick : choice) pick = positions[pick];
  return choice;
}

PTCG::PLAYER Game::relativeOwner(const PTCG::PLAYER _thinker, const PTCG::PLAYER _owner)
{
  size_t thinker = static_cast<size_t>(_thinker);
  size_t owner = static_cast<size_t>(_owner);
  return static_cast<PTCG::PLAYER>(thinker ^ owner);
}

std::vector<size_t> Game::playerSlotChoice(
    const PTCG::PLAYER _thinker,
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const unsigned _amount,
    std::function<bool(BoardSlot*const)> _match,
    const bool _filterActive
    )
{
  std::vector<size_t> choice;
  std::vector<size_t> positions;
  std::vector<BoardSlot> options;
  auto benchArr = viewBench(_owner);
  for (size_t i = static_cast<size_t>(_filterActive); i < benchArr.size(); ++i)
  {
    auto& slot = benchArr[i];
    if(_match(&slot))
    {
      options.push_back(std::move(slot));
      positions.push_back(i);
    }
  }
  auto relOwner = relativeOwner(_thinker, _owner);
  choice = m_players[playerIndex(_thinker)]->chooseSlot(relOwner, _action, options, _amount);
  // Convert the player choice to the original pile indexes
  for (auto& pick : choice) pick = positions[pick];
  return choice;
}

size_t Game::numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const
{
  auto& board = m_boards[playerIndex(_owner)];
  return board.pile(_pile)->numCards();
}

std::vector<std::unique_ptr<Card>> Game::viewPile(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const
{
  auto& board = m_boards[playerIndex(_owner)];
  return board.pile(_pile)->view();
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
  auto relOwner = relativeOwner(_learner, _owner);
  // Triger the players callback for learning cards
  m_players[playerIndex(_learner)]->learnCards(
        relOwner,
        _origin,
        _indices,
        revealed
        );
}

void Game::attack(PokemonCard* _pokemon, const unsigned _index)
{
  if(resolveAttackConditions(PTCG::PLAYER::SELF))
  {
    _pokemon->attack(_index, *this);
    notify<Event::ATTACK>(_pokemon, _index);
  }
}

void Game::dealDamage(const int _damage, const size_t _id, const bool &_applyWeak)
{
  if(_id<6)
  {
    m_damageHandler.generalDamage(
          &m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench,
        &m_boards[playerIndex(PTCG::PLAYER::ENEMY)].m_bench,
        _id,
        _damage,
        _applyWeak);
    std::cout<<"Attack did: "<<_damage<<" damage!\n";
  }
}

void Game::addDamageCounter(const int _damage, const PTCG::PLAYER _player, const unsigned _id)
{
  m_damageHandler.rawDamage(m_boards[playerIndex(_player)].m_bench.slotAt(_id),_damage);
}

void Game::healDamage(const int _heal, const unsigned _id)
{

  m_damageHandler.heal(m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench.slotAt(_id),_heal);
  std::cout<<"Healed: "<<_heal<<" damage!\n";
}

bool Game::evolve(PokemonCard*const _postEvo, const size_t &_handIndex, const size_t &_index)
{
  Board& board = m_boards[playerIndex(PTCG::PLAYER::SELF)];
  //check if chosen card is the correct pokemon to evolve to
  if(board.m_bench.slotAt(_index)->canEvolve(_postEvo,m_turnCount))
  {
    //moving post evolution card from hand to chosen slot, need pileToBench
    pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_handIndex}, {_index});
    board.m_bench.slotAt(_index)->setTurnPlayed(m_turnCount);
    //remove conditions if evolved pokemon is an active
    if(!_index) board.m_bench.activeStatus()->removeAllConditions();
    return true;
  }
  std::cout<<"evolution failed."<<'\n';
  return false;
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
  board.hand()->put(std::unique_ptr<Card>(board.m_bench.slotAt(_index)->devolvePokemon().release()));
  return true;
}

std::vector<size_t> Game::playerEnergyChoice(
    const PTCG::PLAYER _thinker,
    const PTCG::PLAYER _owner,
    const PTCG::PILE _destination,
    const PTCG::ACTION _action,
    const size_t _slotIndex,
    std::function<bool(Card*const)> _match,
    const unsigned _amount
    )
{
  // Player and players board
  auto player = m_players[playerIndex(_thinker)];
  auto& board = m_boards[playerIndex(_thinker)];
  // Get the unfiltered energy cards on the requested slot
  auto energy = board.m_bench.slotAt(_slotIndex)->viewEnergy();
  decltype (energy) filteredEnergy;
  std::vector<size_t> positions;
  // Filter the energies
  filterCards(energy, filteredEnergy, positions, _match);
  auto relOwner = relativeOwner(_thinker, _owner);
  // Ask for the players pick of those filtered energies
  auto choice = player->chooseEnergy(relOwner, _destination, _action, filteredEnergy, _amount);
  // Convert the choices to their original index
  for (auto& pick : choice) pick = positions[pick];
  return choice;
}

void Game::removeEnergy(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _destination,
    const size_t _slotIndex,
    std::vector<size_t> _indices
    )
{
  // Get the required slot
  auto slot = m_boards[playerIndex(_owner)].m_bench.slotAt(_slotIndex);
  // Sort the indices to avoid invalidation
  std::sort(_indices.begin(), _indices.end(), std::greater<size_t>());
  // Move the energies
  for (const auto i : _indices)
    putToPile(_owner, _destination, slot->detachEnergy(i));
}


bool Game::handleKnockOut(const PTCG::PLAYER &_player, const size_t &_index)
{
  bool gameOver = false;
  auto & board = m_boards[playerIndex(_player)];
  auto& bench = board.m_bench;
  auto slot = bench.slotAt(_index);
  if(slot->active() && slot->isDefeated())
  {
    notify<Event::KNOCK_OUT>(_player, _index);
    // Match all cards
    static constexpr auto match = [](Card* const){return true;};
    // Discard and reset all state on that slot
    benchToPile(_player,PTCG::PILE::DISCARD,match,_index);
    slot->setDamage(0);
    // If it was the active we need to reset the active condition
    if(!_index)
    {
      bench.activeStatus()->resetAll();
      // Force the opponent to choose a new active pokemon
      auto active = chooseReplacement(_player);
      if (!active.empty())
        switchActive(_player, active[0]);
      else
        gameOver = true;
    }
    size_t opponentIndex = (static_cast<unsigned>(_player) + 1) % 2;
    auto opponent = static_cast<PTCG::PLAYER>(opponentIndex);
    //Taking a prize card in prize card.
    static constexpr auto prizes = [](Card* const card) -> bool {return card;};
    auto choice = playerCardChoice(opponent, opponent, PTCG::PILE::PRIZE, PTCG::ACTION::DRAW, prizes, 1);
    moveCards(choice, opponent, PTCG::PILE::PRIZE, PTCG::PILE::HAND);
    if (!m_boards[opponentIndex].prizeCards()->numCards())
      gameOver = true;
  }
  return gameOver;
}

void Game::resolveAllEndConditions(const PTCG::PLAYER _player)
{
  auto conditions = m_boards[playerIndex(_player)].m_bench.activeStatus()->conditions();
  for (const auto& condition : conditions)
  {
    resolveEndCondition(_player, condition);
  }
}

bool Game::hasCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition)
{
  // Return if the active has this condition
  return m_boards[playerIndex(_player)].m_bench.activeStatus()->hasCondition(_condition);
}

bool Game::resolveAttackConditions(const PTCG::PLAYER _player)
{
  using cond = PTCG::CONDITION;
  bool confused;
  if((confused =  hasCondition(_player, cond::CONFUSED) && !flipCoin(1)))
  {
    std::cout<<"Confused and failed to flip heads, taking confusion damage."<<'\n';
    addDamageCounter(m_damageHandler.getConfuse(), _player);
  }
  // if you flipped heads and you're not alseep or paralyzed
  return !(confused || hasCondition(_player, cond::ASLEEP) || hasCondition(_player, cond::PARALYZED));
}

void Game::resolveEndCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition)
{
  switch (_condition)
  {
    case PTCG::CONDITION::ASLEEP:
    {
      if(flipCoin(1)) removeCondition(_player, _condition);
      break;
    }
    case PTCG::CONDITION::BURNED:
    {
      addDamageCounter(m_damageHandler.getBurn(), _player);
      if(flipCoin(1)) removeCondition(_player, _condition);
      break;
    }
    case PTCG::CONDITION::PARALYZED:
    {
      removeCondition(_player, _condition);
      break;
    }
    case PTCG::CONDITION::POISONED:
    {
      addDamageCounter(m_damageHandler.getPoison(), _player);
      break;
    }
    default: break;
  }
}
void Game::applyCondition(const PTCG::PLAYER &_target, const PTCG::CONDITION &_condition)
{
  m_boards[playerIndex(_target)].m_bench.activeStatus()->addCondition(_condition);
}

void Game::removeCondition(const PTCG::PLAYER &_target, const PTCG::CONDITION &_condition)
{
  m_boards[playerIndex(_target)].m_bench.activeStatus()->removeCondition(_condition);
}

void Game::removeAllCondition(const PTCG::PLAYER &_target)
{
  m_boards[playerIndex(_target)].m_bench.activeStatus()->removeAllConditions();
}

unsigned Game::flipCoin(const unsigned _num)
{
  unsigned ret = 0;
  // Random bool generator
  static auto gen = std::bind(
        std::uniform_int_distribution<unsigned>(0u,1u),
        // Use a random_device to seed
        std::default_random_engine(std::random_device{}())
        );
  for(unsigned i  = 0; i < _num; ++i)
  {
    ret += gen();
  }
  std::cout<<"Flipping coin...."<<ret<<" heads, "<<_num-ret<<" tails."<<'\n';
  return ret;
}

std::vector<std::unique_ptr<Card>> blankCardVector(const size_t _len)
{
  std::vector<std::unique_ptr<Card>> ret(_len);
  for (auto& c : ret) c.reset(new BlankCard);
  return ret;
}

Game Game::dummyClone() const
{
  Game copy = *this;
  auto& copySelfBoard   = copy.m_boards[playerIndex(PTCG::PLAYER::SELF)];
  auto& copyEnemyBoard  = copy.m_boards[playerIndex(PTCG::PLAYER::ENEMY)];
  *copySelfBoard.deck()  = Deck(blankCardVector(copySelfBoard.deck()->numCards()));
  *copyEnemyBoard.hand() = Hand(blankCardVector(copyEnemyBoard.hand()->numCards()));
  *copyEnemyBoard.deck() = Deck(blankCardVector(copyEnemyBoard.deck()->numCards()));
  return copy;
}

size_t Game::playerIndex(const PTCG::PLAYER &_player) const
{
  return (m_turnCount+static_cast<size_t>(_player)) % 2;
}

std::vector<std::unique_ptr<Card>> Game::viewPrize(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].prizeCards()->view();
}

std::vector<std::unique_ptr<Card>> Game::viewDeck(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].deck()->view();
}

std::vector<std::unique_ptr<Card>> Game::viewDiscard(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].discardPile()->view();
}

std::array<BoardSlot, 6> Game::viewBench(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].m_bench.view();
}

std::vector<std::unique_ptr<Card>> Game::viewHand(const PTCG::PLAYER &_player) const
{
  return m_boards[playerIndex(_player)].hand()->view();
}

bool Game::canRetreat(const PTCG::PLAYER &_player)
{
  auto& board = m_boards[playerIndex(_player)];
  auto slot = board.m_bench.slotAt(0);
  return board.m_bench.activeStatus()->canRetreat() &&
      !hasCondition(_player, PTCG::CONDITION::PARALYZED) &&
      !hasCondition(_player, PTCG::CONDITION::ASLEEP) &&
      slot->numEnergy() >= slot->active()->retreatCost();
}

void Game::setCanRetreat(const PTCG::PLAYER &_affected, const bool _val)
{
  m_boards[playerIndex(_affected)].m_bench.activeStatus()->setCanRetreat(_val);
}

void Game::setProtected(const PTCG::PLAYER &_affected, const bool _val)
{
  m_boards[playerIndex(_affected)].m_bench.activeStatus()->setProtected(_val);
}
