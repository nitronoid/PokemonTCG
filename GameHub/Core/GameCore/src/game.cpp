#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game(const Game &_original) :
  m_playableCards(_original.m_playableCards),
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

  m_drawer = _drawer;
}

void Game::start()
{
  setupGame();
  while(!m_gameFinished)
  {
    nextTurn();
  }
}

void Game::playPokemon(PokemonCard* const _pokemon, const size_t _index)
{
  // Not basic
  if (_pokemon->stage())
  {
    // Choose from slots with pokemon
    constexpr auto filter = [](BoardSlot*const _slot){return _slot->active();};
    auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
    if (!slotChoice.empty())
      evolve(_pokemon, _index, slotChoice[0]);
  }
  // Basic Pokemon
  else
  {
    // Use default filter to find empty slots
    constexpr auto filter = [](BoardSlot*const _slot){return !_slot->active();};
    auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
    if (!slotChoice.empty())
    {
      pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_index}, slotChoice);
      m_boards[playerIndex(PTCG::PLAYER::SELF)].m_bench.slotAt(_index)->setTurnPlayed(m_turnCount);
    }
  }
}

void Game::playItem(TrainerCard* const _item, const size_t _index)
{
  _item->activateAbility(*this);
  moveCards({_index}, PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::PILE::DISCARD);
}

void Game::playTool(TrainerCard* const _tool, const size_t _index)
{
  // Slots with a pokemon that has no tool attached
  auto filter = [](BoardSlot*const _slot){ return _slot->active() && !_slot->viewTool();};
  auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
  if (!slotChoice.empty())
    pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_index}, slotChoice);
}

void Game::playEnergy(EnergyCard* const _energy, const size_t _index)
{
  // Choose from slots with pokemon
  constexpr auto filter = [](BoardSlot*const _slot){return _slot->active();};
  auto slotChoice = playerSlotChoice(PTCG::PLAYER::SELF, PTCG::PLAYER::SELF, PTCG::ACTION::PLAY, 1, filter);
  if (!slotChoice.empty())
  {
    //_energy->activateAbility(*this);
    pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, {_index}, slotChoice);
  }
}

void Game::playSupport(TrainerCard* const _support, const size_t _index)
{
  //need to check if a supporter card has already been played this turn
  if (!m_supportPlayed)
  {
    _support->activateAbility(*this);
    moveCards({_index}, PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::PILE::DISCARD);
    m_supportPlayed = true;
  }
}

bool Game::canPlay(const size_t _index)
{
  return viewHand(PTCG::PLAYER::SELF)[_index]->canPlay(*this);
}

void Game::playCard(const size_t _index)
{
  // MUST store the COPY of the hand here, rather than retrieve the card in one line
  // Otherwise the copy is temp and gets destructed, which null's our card
  auto hand = viewHand(PTCG::PLAYER::SELF);
  auto chosenCard = hand[_index].get();
  using card = PTCG::CARD;
  if (chosenCard->canPlay(*this))
  {
    switch (chosenCard->cardType())
    {
      case card::ENERGY:
      {
        //attach energy to occupied slots
        playEnergy(static_cast<EnergyCard*>(chosenCard), _index);
        break;
      }
      case card::POKEMON:
      {
        playPokemon(static_cast<PokemonCard*>(chosenCard), _index);
        break;
      }
      case card::ITEM:
      {
        playItem(static_cast<TrainerCard*>(chosenCard), _index);
        break;
      }
      case card::TOOL:
      {
        playTool(static_cast<TrainerCard*>(chosenCard), _index);
        break;
      }
      case card::SUPPORT:
      {
        playSupport(static_cast<TrainerCard*>(chosenCard), _index);
        break;
      }
      case card::STADIUM:
      {
        //WILL IMPLEMENT STADIUM LATER WHEN IT IS INCLUDED IN OUR SET
        break;
      }
      default: break;
    }
  }
}

void Game::drawHand(Board& io_board)
{
  for (int j = 0; j < 6; ++j) drawCard(io_board);
}

void Game::setBoard(Board& io_board, const size_t _active)
{
  io_board.m_bench.put(io_board.m_hand.take(_active), 0);
  for (int i = 0; i < 6; ++i)
    io_board.m_prizeCards.put(io_board.m_deck.takeTop());
}

std::vector<size_t> Game::chooseActive(const PTCG::PLAYER _player, const PTCG::PILE _origin)
{
  constexpr auto basicFilter = [](auto _card)
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
  constexpr auto basicFilter = [](auto _slot)
  {
    auto card = _slot->active();
    if (card && card->cardType() == PTCG::CARD::POKEMON)
      return !static_cast<PokemonCard*>(card)->stage();
    return false;
  };
  return playerSlotChoice(
        _player,
        _player,
        PTCG::ACTION::PLAY,
        1,
        basicFilter
        );
}

bool Game::playerAgree(const PTCG::PLAYER _player, const PTCG::ACTION _action)
{
  return m_players[playerIndex(_player)]->agree(_action);
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

void Game::doMulligans(std::vector<size_t> &io_mulligans)
{
  // Keep track of the size of the vector
  size_t size = io_mulligans.size();
  for (size_t i = 0; i < size; ++i)
  {
    // get the player index at this point
    const size_t index = io_mulligans[i];
    // use the index to get the board and player flags
    Board& board = m_boards[index];
    auto currentPlayer = static_cast<PTCG::PLAYER>(index);
    auto enemyPlayer = static_cast<PTCG::PLAYER>((index+1)%2);
    // Generate consecutive integers for range of hand
    std::vector<size_t> indices(board.m_hand.view().size());
    std::iota (std::begin(indices), std::end(indices), 0);
    // Reveal the Hand
    revealCards(enemyPlayer, currentPlayer, PTCG::PILE::HAND, indices);
    // Move the hand back to the deck
    moveCards(indices, currentPlayer, PTCG::PILE::HAND, PTCG::PILE::DECK);
    // Shuffle and redraw the hand
    shuffleDeck(currentPlayer);
    drawHand(board);
    // Ask the player to choose an active pokemon from their hand
    auto active = chooseActive(currentPlayer);
    // If they were able to we set the board up
    if (!active.empty())
      setBoard(board, active[0]);
    // Otherwise they will need to mulligan again
    else
    {
      // If this was the last scheduled mulligan, then we are now on a streak
      // We must therefor offer the enemy the choice of drawing a card
      if ((i == size - 1) && playerAgree(enemyPlayer, PTCG::ACTION::DRAW))
        drawCard(m_boards[(index+1)%2]);
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
  for (const auto & effect : filterEffects(_trigger)) effect.use(*this);
}

void Game::addEffect(const PTCG::PLAYER _affected, const unsigned _wait, const Ability &_effect)
{
  // Calculate the turn that this effect should be executed
  // Flag of enemy will offset the turn by 1
  // We multiply wait by 2 as it is the amount of turns that the affected player should wait
  auto executionTurn = m_turnCount + static_cast<unsigned>(_affected) + _wait * 2;
  m_effectQueue.push_back({executionTurn, _effect});
}

void Game::checkForKnockouts()
{
  for (size_t i = 0; i < m_boards.size(); ++i)
  {
    auto& board = m_boards[i];
    for (size_t j = 0; j < 6; ++j)
    {
      auto slot = board.m_bench.slotAt(j);
      if (slot->active())
        handleKnockOut(static_cast<PTCG::PLAYER>(i), j);
    }
  }
}

void Game::nextTurn()
{
  // Get the current player
  auto& currentPlayer = m_players[m_turnCount % 2];
  Board& currentBoard = m_boards[m_turnCount % 2];
  // Ascii print the board
  if (m_drawer)
  {
    m_drawer->drawBoard(&m_boards[(m_turnCount + 1) % 2],false);
    m_drawer->drawBoard(&currentBoard, true);
  }
  // Apply all effects that are triggered by the start of a turn
  executeTurnEffects(PTCG::TRIGGER::START);
  // The effects could have knocked out a pokemon so we check
  checkForKnockouts();
  // Attempt to draw a card
  if (drawCard(currentBoard))
  {
    // Execute the players turn function
    auto attackDecision = currentPlayer->turn();
    if (attackDecision.first)
    {
      // Apply all attack triggered effects
      executeTurnEffects(PTCG::TRIGGER::ATTACK);
      attack(currentBoard.m_bench.active(), attackDecision.second);
      // The effects/attack could have knocked out a pokemon so we check
      checkForKnockouts();
    }
    // Now that damage calc is over, we remove any damage/defense bonuses
    currentBoard.m_bench.activeStatus()->resetDamageEffects();
    //Resolve all between-turn status conditions
    resolveAllEndConditions(PTCG::PLAYER::SELF);
    // Apply all effects triggered by the end of a turn
    executeTurnEffects(PTCG::TRIGGER::END);
    // The effects could have knocked out a pokemon so we check
    checkForKnockouts();
    // Remove all the effects for this turn from the queue, now that we executed them all
    clearEffects();
    std::cout<<m_turnCount<<'\n';
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
    const size_t &_index
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
    putToPile(_owner,_destination, takeFromPile(_owner, _origin, i));
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
    const unsigned _amount,
    std::function<bool(BoardSlot*const)> _match
    )
{
  std::vector<size_t> choice;
  std::vector<size_t> positions;
  std::vector<BoardSlot> options;
  auto benchArr = viewBench(_owner);
  for (size_t i = 0; i < benchArr.size(); ++i)
  {
    auto& slot = benchArr[i];
    if(_match(&slot))
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
      for (auto& card : board.m_prizeCards.view()) ret.push_back(std::move(card));
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
  if(resolveAttackConditions(PTCG::PLAYER::SELF))
  {
    _pokemon->attack(_index, *this);
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
    std::vector<size_t> hand = std::vector<size_t>(_handIndex);
    std::vector<size_t> bench = std::vector<size_t>(_index);
    //moving post evolution card from hand to chosen slot, need pileToBench
    pileToBench(PTCG::PLAYER::SELF, PTCG::PILE::HAND, hand, bench);
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
  board.m_hand.put(std::unique_ptr<Card>(board.m_bench.slotAt(_index)->devolvePokemon().release()));
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
  auto& player = m_players[playerIndex(_thinker)];
  auto& board = m_boards[playerIndex(_thinker)];
  // Get the unfiltered energy cards on the requested slot
  auto energy = board.m_bench.slotAt(_slotIndex)->viewEnergy();
  decltype (energy) filteredEnergy;
  std::vector<size_t> positions;
  // Filter the energies
  filterCards(energy, filteredEnergy, positions, _match);
  // Ask for the players pick of those filtered energies
  auto choice = player->chooseEnergy(_owner, _destination, _action, filteredEnergy, _amount);
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


void Game::handleKnockOut(const PTCG::PLAYER &_player, const size_t &_index)
{
  auto& bench = m_boards[playerIndex(_player)].m_bench;
  if(bench.view()[_index].isDefeated())
  {
    // Match all cards
    constexpr auto match = [](Card* const){return true;};
    // Discard and reset all state on that slot
    benchToPile(_player,PTCG::PILE::DISCARD,match,_index);
    auto opponent = static_cast<PTCG::PLAYER>((static_cast<unsigned>(_player) + 1) % 2);
    bench.slotAt(_index)->setDamage(0);
    // If it was the active we need to reset the active condition
    if(!_index)
    {
      bench.activeStatus()->resetAll();
      // Force the opponent to choose a new active pokemon
      auto active = chooseReplacement(_player);
      if (!active.empty())
        switchActive(_player, active[0]);
      else
        m_gameFinished = true;
    }
    //Taking a prize card in prize card.
    auto choice = playerCardChoice(opponent, opponent, PTCG::PILE::PRIZE, PTCG::ACTION::DRAW, match, 1);
    moveCards(choice, opponent, PTCG::PILE::PRIZE, PTCG::PILE::HAND);
  }
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
    addDamageCounter(m_damageHandler.getConfuse(), _player);
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


