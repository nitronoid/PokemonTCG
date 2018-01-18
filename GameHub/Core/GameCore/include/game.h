#ifndef GAME_H
#define GAME_H
#include <memory>
#include <unordered_set>
#include "card/pokemoncard.h"
#include "card/cardfactory.h"
#include "board/board.h"
#include "player/player.h"
#include "damagehandler.h"
#include "observers/gameobserver.h"

class Game
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Event enum to communicate what has happened to an observer
  //----------------------------------------------------------------------------------------------------------------------
  enum class Event { START_TURN, EFFECT_USED, ATTACK, PLAY_CARD, SWAP_SLOT, MOVE_CARD, KNOCK_OUT, INSPECT_SLOT, INSPECT_CARD };

public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  Game() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~Game() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default move ctor
  /// @param [in] _original is the game to move
  //----------------------------------------------------------------------------------------------------------------------
  Game(Game&&_original) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy constructor to be used for cloning the game
  /// @param [in] _original is the Game to copy
  //----------------------------------------------------------------------------------------------------------------------
  Game(const Game &_original);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief game cloner, used to make a copy of the game that ommits information that the current player doesn't know.
  /// @return A redacted game
  //----------------------------------------------------------------------------------------------------------------------
  Game dummyClone() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief init function that used a card factory to load in players decks and attach them to the game
  /// @param [in] _factory is the card factory to load the decks
  /// @param [io] io_playerA is a player of the game
  /// @param [io] io_playerB is a player of the game
  //----------------------------------------------------------------------------------------------------------------------
  void init(const CardFactory &_factory, Player * const io_playerA, Player * const io_playerB);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function called to begin the game.
  //----------------------------------------------------------------------------------------------------------------------
  void playGame();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to progress the game to the next turn, public to allow simulations to run
  /// @param [in] _observer is the observer to register for notifications
  //----------------------------------------------------------------------------------------------------------------------
  void nextTurn();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose card(s) from a set of options
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _origin is the pile that contains the cards
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _match is a function that will be used to filter the cards in the _origin down to the options for _thinker
  /// @param [in] _amount is the amount of cards that the _thinker should pick from the options
  /// @param [in] _known tells us whether the options should be revealed to the player, for example prize cards should not
  /// @param [in] _range allows the caller to limit the amount of cards that are possible options. e.g. we could say pick
  /// from the top 7 cards of the deck by setting range to 7.
  /// @return the indices of the picked cards, in _origin
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> playerCardChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::function<bool(Card*const)> _match,
      const unsigned _amount,
      const bool _known = true,
      const size_t _range = 0
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose slot(s) from a set of options
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _amount is the amount of slots that the _thinker should pick from the options
  /// @param [in] _match is a function that will be used to filter the slots down to the options for _thinker
  /// @param [in] _skipActive tells us whether to consider the active pokemon/slot as an option
  /// @return the indices of the picked slots
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> playerSlotChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const unsigned _amount,
      const std::function<bool(BoardSlot*const)> _match,
      const bool _skipActive = false
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that reveals a list of cards to the player
  /// @param [in] _learner is the player to whom the cards are revealed
  /// @param [in] _owner is the player who owns the cards
  /// @param [in] _origin is the pile that contains the cards
  /// @param [in] _indices tells the player the position of each card in _origin
  //----------------------------------------------------------------------------------------------------------------------
  void revealCards(
      const PTCG::PLAYER _learner,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose energ(y/ies) from a slot
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _destination is where the energies will be moved to
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _slotIndex is the slot which the energies are attached to
  /// @param [in] _match is a function that will be used to filter the cards in the _origin down to the options for _thinker
  /// @param [in] _amount is the amount of cards that the _thinker should pick from the options
  /// @return the indices of the picked energy cards
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> playerEnergyChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const size_t _slotIndex,
      const std::function<bool(Card*const)> _match,
      const unsigned _amount
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose condition(s) from their active pokemon
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _options are the conditions to choose from if they are on the active
  /// @param [in] _amount is the amount of conditions that the _thinker should pick from the options
  /// @return the indices of the picked conditons
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> playerConditionChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<PTCG::CONDITION> _options,
      const unsigned _amount
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose condition(s) from their active pokemon
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _action is what the player can choose to accept
  /// @return true for agree and false for disagree
  //----------------------------------------------------------------------------------------------------------------------
  bool playerAgree(const PTCG::PLAYER _thinker, const PTCG::ACTION _action);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in a pile
  /// @param [in] _owner is the player who owns the pile
  /// @param [in] _pile is the pile that contains the cards
  /// @return a copy of all cards in that pile
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewPile(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in the deck
  /// @param [in] _owner is the player who owns the deck
  /// @return a copy of all cards in that deck
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewDeck(const PTCG::PLAYER &_player)    const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in the discard pile
  /// @param [in] _owner is the player who owns the discard pile
  /// @return a copy of all cards in that discard pile
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewDiscard(const PTCG::PLAYER &_player) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in the hand
  /// @param [in] _owner is the player who owns the hand
  /// @return a copy of all cards in that hand
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewHand(const PTCG::PLAYER &_player)    const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that copies and returns all prize cards
  /// @param [in] _owner is the player who owns the prize cards
  /// @return a copy of all prize cards
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card> > viewPrize(const PTCG::PLAYER &_player)   const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that copies and returns all slots on the bench including the active
  /// @param [in] _owner is the player who owns the bench
  /// @return a copy of all slots in the bench
  //----------------------------------------------------------------------------------------------------------------------
  std::array<BoardSlot, 6>            viewBench(const PTCG::PLAYER &_player)   const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief gives access to a players board
  /// @param [in] _owner is the player who owns the board
  /// @return a mutable pointer to the _owner's board
  //----------------------------------------------------------------------------------------------------------------------
  Board* getBoard(const PTCG::PLAYER _owner);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief gets a copy of the active status
  /// @param [in] _owner is the player who owns the status
  /// @return a copy of the _owners active status
  //----------------------------------------------------------------------------------------------------------------------
  Status viewStatus(const PTCG::PLAYER _owner) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function that returns the number of cards in a pile.
  /// @param [in] _owner is the player who owns the pile
  /// @param [in] _pile is the pile to check
  /// @return the number of cards in the pile
  //----------------------------------------------------------------------------------------------------------------------
  size_t numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to filter the card's in a pile
  /// @param [o] o_filtered is where the filtered cards are dumped
  /// @param [o] o_originalPositions stores the indices of the dumped cards, in their pile
  /// @param [in] _owner is the player that owns the pile
  /// @param [in] _pile is the pile that contains the cards to filter
  /// @param [in] _match is the match function which will be used to filter the cards
  //----------------------------------------------------------------------------------------------------------------------
  void filterPile(
      std::vector<std::unique_ptr<Card>>& o_filtered,
      std::vector<size_t> &o_originalPositions,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _pile,
      const std::function<bool(Card*const)> _match
      ) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to filter the card's
  /// @param [io] io_unfiltered are the unfiltered cards, if a card passes the match function it is moved from here
  /// @param [o] o_filtered is used to dump the filtered cards
  /// @param [o] o_originalPositions stores the indices of the dumped cards
  /// @param [in] _match is the match function which will be used to filter the cards
  //----------------------------------------------------------------------------------------------------------------------
  void filterCards(
      std::vector<std::unique_ptr<Card>>& io_unfiltered,
      std::vector<std::unique_ptr<Card>>& o_filtered,
      std::vector<size_t>& o_originalPositions,
      const std::function<bool(Card*const)> _match
      ) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function which filters slots with a match function.
  /// @param [in] _owner is the player who owns the slots
  /// @param [in] _match is the function to filter with
  /// @return the indices of the slots that passed the filter.
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> filterSlots(const PTCG::PLAYER _owner, const std::function<bool(BoardSlot*const)> _match) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function which filters slots by checking whether that they don't contain a pokemon.
  /// @param [in] _owner is the player who owns the slots
  /// @return the indices of the slots that have no pokemon.
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> freeSlots(const PTCG::PLAYER _owner) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function which filters slots by checking that they contain a pokemon.
  /// @param [in] _owner is the player who owns the slots
  /// @return the indices of the slots that have pokemon.
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> nonFreeSlots(const PTCG::PLAYER _owner) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that moves the top card of the players deck to their hand
  /// @param [in] _player is the player who will draw a card
  /// @return whether or not the player could draw a card
  //----------------------------------------------------------------------------------------------------------------------
  bool drawCard(const PTCG::PLAYER _player);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that moves cards from one pile to another
  /// @param [in] _cardIndices are the positions of the cards to move from the _origin pile
  /// @param [in] _owner is the player who owns the cards
  /// @param [in] _origin is the pile that contains the cards prior to this call
  /// @param [in] _destination is the pile to move the cards to
  //----------------------------------------------------------------------------------------------------------------------
  void moveCards(
      std::vector<size_t> _cardIndices,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that removes energy card(s) from a slot and moves them to a card pile
  /// @param [in] _owner is the player who owns the slot and energy
  /// @param [in] _destination is the pile to move the cards to
  /// @param [in] _slotIndex is the index of the slot to remove energies from
  /// @param [in] _indices are the indices of the energy to move from the _origin pile
  //----------------------------------------------------------------------------------------------------------------------
  void removeEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const size_t _slotIndex,
      std::vector<size_t> _indices
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that moves cards from a bench slot to a card pile, using a match function to filter. If the slot
  /// index is zero, the caller should ask for a replacement after this call.
  /// @param [in] _owner is the player who owns the slot
  /// @param [in] _dest is the pile to move the cards to
  /// @param [in] _match is the function used to filter cards on the slot
  /// @param [in] _index is the slot to move cards from
  //----------------------------------------------------------------------------------------------------------------------
  void benchToPile(
      const PTCG::PLAYER &_owner,
      const PTCG::PILE &_dest,
      const std::function<bool(Card*const)> _match,
      const size_t &_index=0
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function that moves cards from a pile to bench slots. There should be exactly one bench index for every card index.
  /// @param [in] _owner is the player who owns the slots
  /// @param [in] _origin is the pile to move the cards from
  /// @param [in] _pileIndex a list of indices, each refers to a card in the _origin pile to move
  /// @param [in] _benchIndex a list of indices, each refers to a slot to move a card into
  //----------------------------------------------------------------------------------------------------------------------
  void pileToBench(
      const PTCG::PLAYER &_owner,
      const PTCG::PILE &_origin,
      std::vector<size_t> _pileIndex,
      std::vector<size_t> _benchIndex
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function that switches the active slot for a benched one and in doing so, clears status effects.
  /// @param [in] _owner is the player who owns the slots
  /// @param [in] _subIndex is the slot to swap with
  //----------------------------------------------------------------------------------------------------------------------
  void switchActive(const PTCG::PLAYER &_owner, const size_t &_subIndex);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function which notifies the observers that a player is inspecting a slot. Used mainly for GUI
  /// @param [in] _owner is the player who owns the slot
  /// @param [in] _index is the index of the slot on the _owners bench.
  //----------------------------------------------------------------------------------------------------------------------
  void inspectSlot(const PTCG::PLAYER _owner, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function which notifies the observers that a player is inspecting a card. Used mainly for GUI
  /// @param [in] _owner is the player who owns the card
  /// @param [in] _pile is the card pile that contains the card.
  /// @param [in] _index is the index of the card in the _owners pile.
  //----------------------------------------------------------------------------------------------------------------------
  void inspectCard(const PTCG::PLAYER _owner, const PTCG::PILE _pile,  const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a function which plays a card from the current players hand
  /// @param [in] _index is the index of the card in current players hand.
  //----------------------------------------------------------------------------------------------------------------------
  void playCard(const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief tells us whether the card at _index in the current players hand can be played.
  /// @param [in]  _index is the index of the card in current players hand.
  /// @return whether the card can be played or not
  //----------------------------------------------------------------------------------------------------------------------
  bool canPlay(const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief tells us whether the card at can be played. Assumes it is in the current players hand.
  /// @param [in]  _card is the card to check.
  /// @return whether the card can be played or not
  //----------------------------------------------------------------------------------------------------------------------
  bool canPlay(Card*const _card);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief plays a pokemon card. Is public to allow the cards themselves to trigger this call.
  /// @param [in]  _pokemon is the pokemon card to play.
  /// @param [in] _index is the index of this pokemon in the current players hand.
  //----------------------------------------------------------------------------------------------------------------------
  void playPokemon(PokemonCard* const _pokemon, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief plays an item card. Is public to allow the cards themselves to trigger this call.
  /// @param [in]  _item is the item card to play.
  /// @param [in] _index is the index of this card in the current players hand.
  //----------------------------------------------------------------------------------------------------------------------
  void playItem(TrainerCard* const _item, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief plays a tool card. Is public to allow the cards themselves to trigger this call.
  /// @param [in]  _tool is the tool card to play.
  /// @param [in] _index is the index of this card in the current players hand.
  //----------------------------------------------------------------------------------------------------------------------
  void playTool(TrainerCard* const _tool, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief plays a support card. Is public to allow the cards themselves to trigger this call.
  /// @param [in]  _support is the support card to play.
  /// @param [in] _index is the index of this card in the current players hand.
  //----------------------------------------------------------------------------------------------------------------------
  void playSupport(TrainerCard* const _support, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief plays an energy card. Is public to allow the cards themselves to trigger this call.
  /// @param [in]  _energy is the energy card to play.
  /// @param [in] _index is the index of this card in the current players hand.
  //----------------------------------------------------------------------------------------------------------------------
  void playEnergy(EnergyCard* const _energy, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief evolves a pokemon by playing another pokemon on top in the same slot.
  /// @param [in]  _postEvo is the pokemon card to play, will be the result of the evolution.
  /// @param [in] _handIndex is the index of this card in the current players hand.
  /// @param [in] _index is the index of the slot to try evolve.
  /// @return whether the pokemon could be evolved.
  //----------------------------------------------------------------------------------------------------------------------
  bool evolve(PokemonCard * const _postEvo, const size_t &_handIndex, const size_t &_index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief devolves a pokemon by moving the top level pokemon back to the owners hand.
  /// @param [in]  _postEvo is the pokemon card to play, will be the result of the evolution.
  /// @param [in] _index is the index of the slot to try devolve.
  /// @return whether the pokemon could be devolved.
  //----------------------------------------------------------------------------------------------------------------------
  bool devolve(const PTCG::PLAYER &_owner, const unsigned &_index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief retreats the active pokemon by switching it for a benched one. The user will be prompted to pick a replacement
  //----------------------------------------------------------------------------------------------------------------------
  void retreat();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function called when a card wants to deal damage through an attack, which takes into account weakeness and
  /// resistance using the damage calculator.
  /// @param [in] _damage is the raw amount of damage to inflict before caclculation.
  /// @param [in] _id is the index in the opponents bench for the damage to be dealt to, 0 is the active pokemon.
  /// @param [in] _applyWeak is a switch that can be used to avoid weakness and resistance calculation.
  //----------------------------------------------------------------------------------------------------------------------
  void dealDamage(const int _damage, const size_t _id = 0, const bool &_applyWeak = true);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to apply damage through an effect such as burn or poison. This can be done to self or opponent.
  /// @param [in] _damage is the raw amount of damage to inflict
  /// @param [in] _player a flag telling us who to inflict the damage on
  /// @param [in] _id is the index of the pokemon in the players board to deal damage to.
  //----------------------------------------------------------------------------------------------------------------------
  void addDamageCounter(const int _damage, const PTCG::PLAYER _player = PTCG::PLAYER::ENEMY, const unsigned _id = 0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this function is used to remove an amount of damage from a pokemon. This can only done to the self
  /// @param [in] _heal is the amount of damage to remove from the pokemon.
  /// @param [in] _id is the index in the current players bench for the damage to removed from, 0 is the active pokemon
  //----------------------------------------------------------------------------------------------------------------------
  void healDamage(const int _heal, const unsigned _id = 0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this function is used to add bonus damage to an attack that happens this turn. Is cleared upon end of turn.
  /// @param [in] _value is the amount of damage to add to the attack.
  /// @param [in] _order refers to whether or not the bonus should be applied before or after damage calculation
  /// @param [in] _player is the player who's attack is given the bonus
  //----------------------------------------------------------------------------------------------------------------------
  void addBonusDamage(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this function is used to lower the damage done by an attack this turn. Is cleared upon end of turn.
  /// @param [in] _value is the amount of damage to lower the attack damage by.
  /// @param [in] _order refers to whether or not the bonus should be applied before or after damage calculation
  /// @param [in] _player is the player who's attack is lowered
  //----------------------------------------------------------------------------------------------------------------------
  void addBonusDefense(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief checks whether the _player's active pokemon is affected by _condition
  /// @param [in] _player is the player, who's active should be checked.
  /// @param [in] _condition is the condition to check for
  /// @return returns whether or not the pokemon is affected by _condtion
  //----------------------------------------------------------------------------------------------------------------------
  bool hasCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief applies a condition to the _target's active pokemon
  /// @param [in] _target is the player, who's active should be affected.
  /// @param [in] _condition is the condition to apply
  //----------------------------------------------------------------------------------------------------------------------
  void applyCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief removes a condition from the _target's active pokemon
  /// @param [in] _target is the player, who's active should be now be unaffected by _condition
  /// @param [in] _condition is the condition to remove
  //----------------------------------------------------------------------------------------------------------------------
  void removeCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief removes all conditions from _target's active pokemon
  /// @param [in] _target is the player, who's active should be now be unaffected by any conditions
  //----------------------------------------------------------------------------------------------------------------------
  void removeAllConditions(const PTCG::PLAYER &_target);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief checks if the current players active pokemon can use the attack stored at _index
  /// @param [in] _index is the index of the attack to check
  /// @return whether or not the attack can be used
  //----------------------------------------------------------------------------------------------------------------------
  bool canAttack(const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief checks if _player's active pokemon can retreat
  /// @param [in] _player is the player who's active should be checked
  /// @return whether or not the pokemon can retreat
  //----------------------------------------------------------------------------------------------------------------------
  bool canRetreat(const PTCG::PLAYER &_player);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the canRetreat value for _affected's active pokemon
  /// @param [in] _affected is the player who's active should be set
  /// @param [in] _val is the value to set
  //----------------------------------------------------------------------------------------------------------------------
  void setCanRetreat(const PTCG::PLAYER &_affected, const bool _val = false);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the isProtected value for _affected's active pokemon
  /// @param [in] _affected is the player who's active should be set
  /// @param [in] _val is the value to set
  //----------------------------------------------------------------------------------------------------------------------
  void setProtected(const PTCG::PLAYER &_affected, const bool _val = true);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief will add an effect to the effect queue so that it will be executed on a future turn.
  /// @param [in] _affected is the player who's turn the effect will be executed on
  /// @param [in] _wait is the ammount of _affected's turns to wait before execution
  /// @param [in] _effect is the effect to be executed
  //----------------------------------------------------------------------------------------------------------------------
  void addEffect(const PTCG::PLAYER _affected, const unsigned _wait, const Ability &_effect);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief gets the current tunr count
  /// @return the current turn count
  //----------------------------------------------------------------------------------------------------------------------
  unsigned turnCount() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to simulate the outcome of flipping one or more coins
  /// @param [in] _num is the amount of coin flips to be simulated
  /// @return the amount of heads
  //----------------------------------------------------------------------------------------------------------------------
  unsigned flipCoin(const unsigned _num);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief shuffles _owner's deck
  /// @param [in] _owner the player who's deck should be shuffled
  //----------------------------------------------------------------------------------------------------------------------
  void shuffleDeck(const PTCG::PLAYER _owner);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to register a new observer to the game
  /// @param [in] _observer is the observer to register for notifications
  //----------------------------------------------------------------------------------------------------------------------
  void registerObserver(GameObserver*const _observer);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to register a new player to the game
  /// @param [in] _newPlayer is the new player to register
  /// @param [in] _who tells the game the role of the new player
  //----------------------------------------------------------------------------------------------------------------------
  void registerPlayer(Player*const _newPlayer, const PTCG::PLAYER _who);

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to progress the game to the next turn, public to allow simulations to run
  /// @param [k] k_event is the event flag used to decide the correct observer interface function to call
  /// @param [...] args are the arguments that should be forwarded to the interface function call
  //----------------------------------------------------------------------------------------------------------------------
  template<Game::Event k_event, typename... Args>
  void notify(Args&&... args);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief resets the m_playable card member when a new turn starts
  //----------------------------------------------------------------------------------------------------------------------
  void resetPlayable();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief checks if any pokemon on the board are knocked out and handles this
  //----------------------------------------------------------------------------------------------------------------------
  bool checkForKnockouts();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief makes _player choose an basic pokemon from _pile
  /// @param [in] _player is the player who should choose
  /// @param [in] _origin is the pile to choose from
  /// @return a vector of indices, refering to the chosen positions in _origin
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> chooseActive(const PTCG::PLAYER _player, const PTCG::PILE _origin = PTCG::PILE::HAND);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief makes _player choose a replacement for their active pokemon from their bench if possible
  /// @param [in] _player is the player who should make the choice
  /// @return is a list of at most one index holding the position of the replacement on the bench. If the return is empty,
  /// then there were no available replacements.
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<size_t> chooseReplacement(const PTCG::PLAYER _player);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to execute all queued effects for the given trigger
  /// @param [in] _trigger is the event that has just happened to trigger effects
  //----------------------------------------------------------------------------------------------------------------------
  void executeTurnEffects(const PTCG::TRIGGER _trigger);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to filter effects by their trigger, copying them from the queue
  /// @param [in] _trigger is the trigger to filter by
  /// @return the abilties in the queue that had the _trigger, and were set to execute on this turn
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Ability> filterEffects(const PTCG::TRIGGER _trigger);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to clear the effect queue, of this turns effects
  //----------------------------------------------------------------------------------------------------------------------
  void clearEffects();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief internal function used put a card in a pile
  /// @param [in] _owner is the owner of the pile
  /// @param [in] _dest is the pile to put the card in
  /// @param [in] _card is the card to put in the pile
  //----------------------------------------------------------------------------------------------------------------------
  void putToPile(const PTCG::PLAYER _owner, PTCG::PILE _dest , std::unique_ptr<Card> &&_card);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief internal function used to take a card from a pile
  /// @param [in] _owner is the owner of the pile
  /// @param [in] _origin is the pile to take the card from
  /// @param [in] _index is the position of the card to take, in the pile
  /// @return the taken card
  //----------------------------------------------------------------------------------------------------------------------
  std::unique_ptr<Card> takeFromPile(const PTCG::PLAYER _owner, PTCG::PILE _origin, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief internal function used convert a player enum into the index of the player
  /// @param [in] _player is the enum to convert
  /// @return the index of the player
  //----------------------------------------------------------------------------------------------------------------------
  size_t playerIndex(const PTCG::PLAYER &_player) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief handle mulligans after hands are drawn
  /// @param [io] io_mulligans holds the indices of the players to perform mulligans for
  //----------------------------------------------------------------------------------------------------------------------
  void doMulligans(std::vector<size_t> &io_mulligans);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draws 6 cards from the players deck and puts them in the hand
  /// @param [in] _player is the player to draw a hand for
  //----------------------------------------------------------------------------------------------------------------------
  void drawHand(const PTCG::PLAYER _player);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief plays the players active pokemon, and sets up their prize cards
  /// @param [in] _player is the player who's board should be set
  /// @param [in] _active is the index in the boards hand, to play as the active pokemon
  //----------------------------------------------------------------------------------------------------------------------
  void setBoard(const PTCG::PLAYER _player, const size_t _active);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prepares the game for the start by setting up the boards, drawing hands, playing active and setting prize cards
  //----------------------------------------------------------------------------------------------------------------------
  void setupGame();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief executes an attack sequence
  /// @param [in] _pokemon is the pokemon thats attacking
  /// @param [in] _index is the index of the attack on the _pokemon
  //----------------------------------------------------------------------------------------------------------------------
  void attack(PokemonCard* _pokemon, const unsigned _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sequence that is executed when a pokemon is knocked out
  /// @param [in] _player is the player who's pokemon has been knocked out
  /// @param [in] _index is the position on the players bench of the pokemon that's been knocked out
  //----------------------------------------------------------------------------------------------------------------------
  bool handleKnockOut(const PTCG::PLAYER &_player, const size_t &_index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief execute effects of conditions such as burn and poison, that are triggered by the end of a turn
  /// @param [in] _player is the player who's  conditions should be resolved
  //----------------------------------------------------------------------------------------------------------------------
  void resolveAllEndConditions(const PTCG::PLAYER _player);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief execute effects of conditions such as sleep and paralysis which would interfere with the attack sequence
  /// @param [in] _player is the player who's  conditions should be resolved
  //----------------------------------------------------------------------------------------------------------------------
  bool resolveAttackConditions(const PTCG::PLAYER _player);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief execute effects of a single end condition
  /// @param [in] _player is the player who's affected by the condtion
  /// @param [in] _condition is the condition to resolve
  //----------------------------------------------------------------------------------------------------------------------
  void resolveEndCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief takes an owner and thinker flag, and works out who the thinker is relative to the owner, for example if both
  /// flags are ENEMY, then the player flag that should be passed to player choice is SELF, as they are choosing from their
  /// owne pile.
  /// @param [in] _thinker is the player who is going to make a choice
  /// @param [in] _owner is the player who owns the options of the choice
  /// @return the relative owner of the options
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::PLAYER relativeOwner(const PTCG::PLAYER _thinker, const PTCG::PLAYER _owner);

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a vector of observers to be notified with events
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<GameObserver*> m_observers;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief an array of two player pointers, used as references to participants
  //----------------------------------------------------------------------------------------------------------------------
  std::array<Player*, 2> m_players{{nullptr, nullptr}};
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief an array of two boards which hold all cards and slots
  //----------------------------------------------------------------------------------------------------------------------
  std::array<Board, 2> m_boards;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief an internal damage handler to seperate out damage calculation for attacks
  //----------------------------------------------------------------------------------------------------------------------
  DamageHandler m_damageHandler;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set of playable cards for this turn, used to prevent multiple energies and supporters being played, but can
  /// also be used for game effects that would prevent another type of card from being played
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_set<PTCG::CARD> m_playableCards;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the effect queue which holds pairs of turn to execute, and effect to execute
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::pair<unsigned, Ability>> m_effectQueue;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the current turn of the game
  //----------------------------------------------------------------------------------------------------------------------
  unsigned m_turnCount = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief has the game ended.
  //----------------------------------------------------------------------------------------------------------------------
  bool m_gameFinished  = false;

};

#include "game-inl.h" //Template implementations

#endif // GAME_H
