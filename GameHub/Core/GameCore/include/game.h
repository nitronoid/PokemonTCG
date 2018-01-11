#ifndef GAME_H
#define GAME_H
#include <memory>
#include <unordered_set>
#include "pokemoncard.h"
#include "humanplayer.h"
#include "aiplayerbt.h"
#include "cardfactory.h"
#include "board.h"
#include "damagehandler.h"
#include "guimodule.h"

class Game
{
public:
  Game() = default;
  Game(Game&&_original) = default;

  Game clone() const;
  void init(const CardFactory &_factory, Player * const _playerA, Player * const _playerB);

  void dealDamage(const int _damage, const size_t _id = 0, const bool &_applyWeak = true);
  void addDamageCounter(const int _damage, const PTCG::PLAYER _player = PTCG::PLAYER::ENEMY, const unsigned _id = 0);
  void healDamage(const int _heal, const unsigned _id = 0);
  unsigned flipCoin(const unsigned _num);

  void start();
  void playCard(const size_t _index);
  bool canPlay(const size_t _index);
  bool drawCard(const PTCG::PLAYER _player);
  void moveCards(
      std::vector<size_t> _cardIndices,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination
      );

  std::vector<size_t> playerCardChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      std::function<bool(Card*const)> _match,
      const unsigned _amount,
      const size_t _range = 0
      );

  std::vector<size_t> playerSlotChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const unsigned _amount,
      std::function<bool(BoardSlot*const)> _match
      );

  void revealCards(
      const PTCG::PLAYER _learner,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices
      );

  std::vector<size_t> playerEnergyChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const size_t _slotIndex,
      std::function<bool(Card*const)> _match,
      const unsigned _amount
      );

  void removeEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const size_t _slotIndex,
      std::vector<size_t> _indices
      );

  bool playerAgree(const PTCG::PLAYER _player, const PTCG::ACTION _action);

  // View card pile functions
  // std::vector<std::unique_ptr<Card>>  viewBoard(const PTCG::PLAYER &_player, const PTCG::PILE &_target) const;
  std::vector<std::unique_ptr<Card>>  viewDeck(const PTCG::PLAYER &_player)    const;
  std::vector<std::unique_ptr<Card>>  viewDiscard(const PTCG::PLAYER &_player) const;
  std::vector<std::unique_ptr<Card>>  viewHand(const PTCG::PLAYER &_player)    const;
  std::array<std::unique_ptr<Card>,6> viewPrize(const PTCG::PLAYER &_player)   const;
  std::array<BoardSlot, 6>            viewBench(const PTCG::PLAYER &_player)   const;

  void addBonusDamage(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  void addBonusDefense(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  bool hasCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition);
  void applyCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  void removeCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  void removeAllCondition(const PTCG::PLAYER &_target);
  inline unsigned turnCount() const {return m_turnCount;}
  void switchActive(const PTCG::PLAYER &_player, const unsigned &_subIndex);
  //player needs to choose what to move into active if _index = 0
  void benchToPile(const PTCG::PLAYER &_player, const PTCG::PILE &_dest, std::function<bool(Card*const)> _match, const size_t &_index=0);
  void pileToBench(const PTCG::PLAYER &_player, const PTCG::PILE &_origin, std::vector<size_t> _pileIndex, std::vector<size_t> _benchIndex);
  bool evolve(PokemonCard * const _postEvo, const size_t &_handIndex, const size_t &_index);
  bool devolve(const PTCG::PLAYER &_player, const unsigned &_index);
  std::vector<size_t> filterSlots(const PTCG::PLAYER _owner, std::function<bool(BoardSlot*const)>) const;
  std::vector<size_t> freeSlots(const PTCG::PLAYER _owner) const;
  std::vector<size_t> nonFreeSlots(const PTCG::PLAYER _owner) const;
  void shuffleDeck(const PTCG::PLAYER _owner);
  void addEffect(const PTCG::PLAYER _affected, const unsigned _wait, const Ability &_effect);
  bool activeCanRetreat(const PTCG::PLAYER &_player);
  void setActiveCanRetreat(const PTCG::PLAYER &_player,const bool &_val = false);
  Board* getBoard(const PTCG::PLAYER _owner);
  void registerGui(GuiModule*const _gui);
  void retreat();
private:
  Game(const Game &_original);
  void notifyGui();
  bool checkForKnockouts();
  std::vector<size_t> chooseActive(const PTCG::PLAYER _player, const PTCG::PILE _origin = PTCG::PILE::HAND);
  std::vector<size_t> chooseReplacement(const PTCG::PLAYER _player);
  void executeTurnEffects(const PTCG::TRIGGER _trigger);
  std::vector<Ability> filterEffects(const PTCG::TRIGGER _trigger);
  void clearEffects();
  std::vector<std::unique_ptr<Card>> viewPile(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const;
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
  void nextTurn();
  void setupGame();
  void attack(PokemonCard* _pokemon, const unsigned _index);
  bool handleKnockOut(const PTCG::PLAYER &_player, const size_t &_index);
  void playPokemon(PokemonCard* const _pokemon, const size_t _index);
  void playItem(TrainerCard* const _item, const size_t _index);
  void playTool(TrainerCard* const _tool, const size_t _index);
  void playSupport(TrainerCard* const _support, const size_t _index);
  void playEnergy(EnergyCard* const _energy, const size_t _index);
  void resolveAllEndConditions(const PTCG::PLAYER _player);
  bool resolveAttackConditions(const PTCG::PLAYER _player);
  void resolveEndCondition(const PTCG::PLAYER _player, const PTCG::CONDITION _condition);

private:
  std::vector<GuiModule*> m_guiObservers;
  std::array<Player*, 2> m_players{{nullptr, nullptr}};
  std::array<Board, 2> m_boards;
  DamageHandler m_damageHandler;
  std::unordered_set<PTCG::CARD> m_playableCards;
  std::vector<std::pair<unsigned, Ability>> m_effectQueue;
  unsigned m_turnCount = 0;
  bool m_turnFinished  = false;
  bool m_rulesBroken   = false;
  bool m_gameFinished  = false;
  bool m_supportPlayed = false;


};

#endif // GAME_H
