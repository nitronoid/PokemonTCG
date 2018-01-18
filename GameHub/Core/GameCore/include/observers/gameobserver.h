#ifndef GUIMODULE_H
#define GUIMODULE_H

#include "board/board.h"

class Game;

class GameObserver
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  GameObserver() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default virtual dtor
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~GameObserver();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing at the start a turn
  //----------------------------------------------------------------------------------------------------------------------
  virtual void startTurn() = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when an attack is used
  //----------------------------------------------------------------------------------------------------------------------
  virtual void attackUsed(PokemonCard*const _pokemon, const unsigned _index) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when an effect is used
  //----------------------------------------------------------------------------------------------------------------------
  virtual void effectUsed(const Ability*const _ability, const PTCG::TRIGGER _trigger) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when a card is played
  //----------------------------------------------------------------------------------------------------------------------
  virtual void playCard(const size_t _index, Card*const _card) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when the active slot is swapped
  //----------------------------------------------------------------------------------------------------------------------
  virtual void swapSlot(const PTCG::PLAYER _origin, const size_t _index) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when a card is moved
  //----------------------------------------------------------------------------------------------------------------------
  virtual void moveCard(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination,
      const size_t _index,
      Card*const _card
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when a pokemon is knocked out
  //----------------------------------------------------------------------------------------------------------------------
  virtual void knockOut(const PTCG::PLAYER _owner, const size_t _index) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for inspecting a board slot
  //----------------------------------------------------------------------------------------------------------------------
  virtual void inspectSlot(const PTCG::PLAYER _player, const size_t _index) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for inspecting a card
  //----------------------------------------------------------------------------------------------------------------------
  virtual void inspectCard(const PTCG::PLAYER _player, const PTCG::PILE _pile, const size_t _index) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for sourcing the game to be observed
  /// @param [in] _subject source game to observe
  //----------------------------------------------------------------------------------------------------------------------
  void setGame(Game*const _subject);

protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pointer to the source game to observe
  //----------------------------------------------------------------------------------------------------------------------
  Game* m_subject = nullptr;
};

#endif // GUIMODULE_H