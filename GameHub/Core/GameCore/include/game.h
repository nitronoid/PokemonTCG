#ifndef GAME_H
#define GAME_H
#include <memory>
#include <unordered_set>
#include "pokemoncard.h"
#include "humanplayer.h"
#include "cardfactory.h"
#include "board.h"
#include "damagehandler.h"
#include "gameobserver.h"

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
  void start();
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
      std::function<bool(Card*const)> _match,
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
      std::function<bool(BoardSlot*const)> _match,
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
      std::function<bool(Card*const)> _match,
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
  /// index is zero, the player will be asked to choose a replacement pokemon.
  /// @param [in] _owner is the player who owns the slot
  /// @param [in] _dest is the pile to move the cards to
  /// @param [in] _match is the function used to filter cards on the slot
  /// @param [in] _index is the slot to move cards from
  //----------------------------------------------------------------------------------------------------------------------
  void benchToPile(
      const PTCG::PLAYER &_owner,
      const PTCG::PILE &_dest,
      std::function<bool(Card*const)> _match,
      const size_t &_index=0
      );
  void pileToBench(
      const PTCG::PLAYER &_player,
      const PTCG::PILE &_origin,
      std::vector<size_t> _pileIndex,
      std::vector<size_t> _benchIndex
      );
  void switchActive(const PTCG::PLAYER &_player, const size_t &_subIndex);
  size_t numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const;
  //Slots
  std::vector<size_t> filterSlots(const PTCG::PLAYER _owner, std::function<bool(BoardSlot*const)>) const;
  std::vector<size_t> freeSlots(const PTCG::PLAYER _owner) const;
  std::vector<size_t> nonFreeSlots(const PTCG::PLAYER _owner) const;

  //Card playing
  void inspectSlot(const PTCG::PLAYER _owner, const size_t _index);
  void inspectCard(const PTCG::PLAYER _owner, const PTCG::PILE _pile,  const size_t _index);
  void playCard(const size_t _index);
  bool canPlay(const size_t _index);
  bool canPlay(Card*const _card);
  void playPokemon(PokemonCard* const _pokemon, const size_t _index);
  void playItem(TrainerCard* const _item, const size_t _index);
  void playTool(TrainerCard* const, const size_t _index);
  void playSupport(TrainerCard* const _support, const size_t _index);
  void playEnergy(EnergyCard* const, const size_t _index);
  //actions
  bool evolve(PokemonCard * const _postEvo, const size_t &_handIndex, const size_t &_index);
  bool devolve(const PTCG::PLAYER &_player, const unsigned &_index);
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

  void addBonusDamage(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  void addBonusDefense(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  bool hasCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition);
  void applyCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  void removeCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  void removeAllCondition(const PTCG::PLAYER &_target);
  bool canAttack(const size_t _index);
  bool canRetreat(const PTCG::PLAYER &_player);
  void setCanRetreat(const PTCG::PLAYER &_affected, const bool _val = false);
  void setProtected(const PTCG::PLAYER &_affected, const bool _val = true);
  //Effectors
  void addEffect(const PTCG::PLAYER _affected, const unsigned _wait, const Ability &_effect);

  inline unsigned turnCount() const {return m_turnCount;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to simulate the outcome of flipping one or more coins
  /// @param [in] _num is the amount of coin flips to be simulated
  /// @return the amount of heads
  //----------------------------------------------------------------------------------------------------------------------
  unsigned flipCoin(const unsigned _num);
  void shuffleDeck(const PTCG::PLAYER _owner);


  void registerPlayer(Player*const _newPlayer, size_t _index);

  Board* getBoard(const PTCG::PLAYER _owner);
  void registerObserver(GameObserver*const _observer);
  void nextTurn();


private:
  Game(const Game &_original);

  template<Game::Event k_event, typename... Args>
  void notify(Args&&... args);

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief resets the m_playable card member when a new turn starts
  //----------------------------------------------------------------------------------------------------------------------
  void resetPlayable();
  bool checkForKnockouts();
  std::vector<size_t> chooseActive(const PTCG::PLAYER _player, const PTCG::PILE _origin = PTCG::PILE::HAND);
  std::vector<size_t> chooseReplacement(const PTCG::PLAYER _player);
  void executeTurnEffects(const PTCG::TRIGGER _trigger);
  std::vector<Ability> filterEffects(const PTCG::TRIGGER _trigger);
  void clearEffects();
  void filterPile(std::vector<std::unique_ptr<Card>>& io_filtered,
                  std::vector<size_t> &io_originalPositions,
                  const PTCG::PLAYER _owner,
                  const PTCG::PILE _pile,
                  std::function<bool(Card*const)> _match
                  ) const;
  void filterCards(
      std::vector<std::unique_ptr<Card>>& io_unfiltered,
      std::vector<std::unique_ptr<Card>>& io_filtered,
      std::vector<size_t>& io_originalPositions,
      std::function<bool(Card*const)> _match
      ) const;
  void putToPile(const PTCG::PLAYER _owner, PTCG::PILE _dest , std::unique_ptr<Card> &&_card);
  std::unique_ptr<Card> takeFromPile(const PTCG::PLAYER _owner, PTCG::PILE _dest, const size_t _index);
  size_t playerIndex(const PTCG::PLAYER &_player) const;
  void doMulligans(std::vector<size_t> &io_mulligans);
  void drawHand(const PTCG::PLAYER _player);
  void setBoard(Board& io_board, const size_t _active);

  void setupGame();
  void attack(PokemonCard* _pokemon, const unsigned _index);
  bool handleKnockOut(const PTCG::PLAYER &_player, const size_t &_index);
  void resolveAllEndConditions(const PTCG::PLAYER _player);
  bool resolveAttackConditions(const PTCG::PLAYER _player);
  void resolveEndCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition);
  PTCG::PLAYER relativeOwner(const PTCG::PLAYER _thinker, const PTCG::PLAYER _owner);

private:
  std::vector<GameObserver*> m_observers;
  std::array<Player*, 2> m_players{{nullptr, nullptr}};
  std::array<Board, 2> m_boards;
  DamageHandler m_damageHandler;
  std::unordered_set<PTCG::CARD> m_playableCards;
  std::vector<std::pair<unsigned, Ability>> m_effectQueue;
  unsigned m_turnCount = 0;
  bool m_gameFinished  = false;

};

#include "game-inl.h" //Template implementations

#endif // GAME_H
