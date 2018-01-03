#ifndef GAME_H
#define GAME_H

#include <memory>
#include <unordered_set>
#include "pokemoncard.h"
#include "humanplayer.h"
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
  void init(const CardFactory &_factory, GuiModule *const _drawer, const std::string &_deckA, const std::string &_deckB);

  void dealDamage(const int _damage, const unsigned _id = 0);
  void addDamageCounter(const int _damage, const PTCG::PLAYER _player = PTCG::PLAYER::ENEMY, const unsigned _id = 0);
  void healDamage(const int _heal, const unsigned _id = 0);
  unsigned flipCoin(const unsigned _num);

  void start();
  bool canPlay(const std::unique_ptr<Card>& _card);
  bool playCard(const unsigned _index);
  bool drawCard(Board& _board);
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
      const unsigned _amount
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
  void applyCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  void removeCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  void removeAllCondition(const PTCG::PLAYER &_target);
  inline unsigned getTurnCount() const {return m_turnCount;}
  void switchActive(const PTCG::PLAYER &_player, const unsigned &_subIndex);
  //player needs to choose what to move into active if _index = 0
  void benchToPile(const PTCG::PLAYER &_player, const PTCG::PILE &_dest, std::function<bool(Card*const)> _match, const unsigned &_index=0);
  void pileToBench(const PTCG::PLAYER &_player, const PTCG::PILE &_origin, std::vector<unsigned> &_pileIndex, std::vector<unsigned> &_benchIndex);
  void evolve(std::unique_ptr<PokemonCard> &_postEvo, const unsigned &_handIndex, const unsigned &_index);
  bool devolve(const PTCG::PLAYER &_player, const unsigned &_index);
  std::vector<size_t> freeSlots(const PTCG::PLAYER _owner);
  void shuffleDeck(const PTCG::PLAYER _owner);
  void addEffect(const PTCG::PLAYER _affected, const Ability &_effect);

private:
  Game(const Game &_original);
  std::vector<size_t> chooseActive(const PTCG::PLAYER _player);
  void splitEffects(std::vector<Ability>&io_attackTriggered, std::vector<Ability>&io_endTriggered);
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
  void drawHand(Board& io_board);
  void setBoard(Board& io_board, const size_t _active);
  void nextTurn();
  void setupGame();
  void attack(PokemonCard* _pokemon, const unsigned _index);
  void poison();
  void burn();
  void paralysis();
  void confuse();
  void sleep();

private:
  GuiModule* m_drawer;
  std::array<std::unique_ptr<Player>, 2> m_players;
  std::array<Board, 2> m_boards;
  DamageHandler m_damageHandler;
  std::unordered_set<PTCG::CARD> m_playableCards;
  std::vector<std::pair<unsigned, Ability>> m_effectQueue;
  unsigned m_turnCount = 0;
  bool m_turnFinished  = false;
  bool m_rulesBroken   = false;
  bool m_gameFinished  = false;

};

#endif // GAME_H
