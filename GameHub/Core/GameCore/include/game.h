#ifndef GAME_H
#define GAME_H

#include <memory>
#include <unordered_set>
#include "pokemoncard.h"
#include "humanplayer.h"
#include "cardfactory.h"
#include "board.h"
#include "damagehandler.h"

class Game
{
public:
  Game() = default;
  Game(Game&&_original) = default;

  Game clone() const;
  void init(const CardFactory &_factory, const std::string &_deckA, const std::string &_deckB);

  void dealDamage(const unsigned _damage = 0,const unsigned _id = 0);
  unsigned flipCoin(const unsigned _num);

  void start();
  bool canPlay(const std::unique_ptr<Card>& _card);
  bool playCard(const unsigned _index);
  bool drawCard(Board& _board);
  void moveCards(
      const std::vector<int> _cardIndices,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination,
      const bool _reveal
      );
  std::vector<int> playerChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::CARD _cardType,
      const PTCG::ACTION _action,
      const int _amount,
      const int _range
      );

  std::vector<std::unique_ptr<Card>> viewBoard(const PTCG::PLAYER &_player, const PTCG::PILE &_target) const;
  std::array<std::unique_ptr<Card>,6> viewPrize(const PTCG::PLAYER &_player) const;
  std::vector<std::unique_ptr<Card>> viewDeck(const PTCG::PLAYER &_player) const;
  std::vector<std::unique_ptr<Card>> viewDiscard(const PTCG::PLAYER &_player) const;
  std::array<std::unique_ptr<BoardSlot>,6> viewBench(const PTCG::PLAYER &_player) const;
  std::vector<std::unique_ptr<Card>> viewHand(const PTCG::PLAYER &_player) const;
  void applyCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  inline unsigned getTurnCount()const{return m_turnCount;}

    std::unique_ptr<Card> viewTool(const PTCG::PLAYER &_player, const unsigned _slot) const;
    std::vector<std::unique_ptr<Card>> viewTool(const PTCG::PLAYER &_player, const PTCG::PILE &_target) const;
    std::unique_ptr<Card> viewPokemon(const PTCG::PLAYER &_player, const unsigned _slot) const;
    std::vector<std::unique_ptr<Card>> viewPokemon(const PTCG::PLAYER &_player, const PTCG::PILE &_target) const;
    std::vector<std::unique_ptr<Card>> viewEnergy(const PTCG::PLAYER &_player, const unsigned _slot) const;
    std::vector<std::unique_ptr<Card>> viewEnergy(const PTCG::PLAYER &_player, const PTCG::PILE &_target) const;

    unsigned searchCountByName(std::string _name, const PTCG::PLAYER &_player, const PTCG::PILE &_target) const;
    bool matchPokemonType(const PTCG::TYPE &_type, const std::unique_ptr<PokemonCard> &&_card) const;
private:

  Game(const Game &_original);

  void nextTurn();
  void setupGame();
  void attack(PokemonCard* _pokemon, const unsigned _index);
  void poison();
  void burn();
  void paralysis();
  void confuse();
  void sleep();

private:


  std::array<std::unique_ptr<Player>, 2> m_players;
  std::array<Board, 2> m_boards;
  DamageHandler m_damageHandler;
  std::unordered_set<PTCG::CARD> m_playableCards;
  PTCG::PHASE m_turnPhase = PTCG::PHASE::NONE;
  unsigned m_turnCount = 0;
  bool m_turnFinished = false;
  bool m_rulesBroken = false;
  bool m_gameFinished = false;


};

#endif // GAME_H
