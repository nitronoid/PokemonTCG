#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include "observers/gameobserver.h"

class GameLogger : public GameObserver
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for GameLogger
  //----------------------------------------------------------------------------------------------------------------------
  GameLogger();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default virtual dtor for GameLogger
  //----------------------------------------------------------------------------------------------------------------------
  ~GameLogger() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing at the start a turn
  //----------------------------------------------------------------------------------------------------------------------
  virtual void startTurn() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when an attack is used
  //----------------------------------------------------------------------------------------------------------------------
  virtual void attackUsed(PokemonCard*const _pokemon, const unsigned _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when an effect is used
  //----------------------------------------------------------------------------------------------------------------------
  virtual void effectUsed(const Ability * const _ability, const PTCG::TRIGGER _trigger) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when a card is played
  //----------------------------------------------------------------------------------------------------------------------
  virtual void playCard(const size_t _handIndex, Card*const _card) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when the active slot is swapped
  //----------------------------------------------------------------------------------------------------------------------
  virtual void swapSlot(const PTCG::PLAYER _player, const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when a card is moved
  //----------------------------------------------------------------------------------------------------------------------
  virtual void moveCard(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination,
      const size_t _index, Card*const _card
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for executing when a pokemon is knocked out
  //----------------------------------------------------------------------------------------------------------------------
  virtual void knockOut(const PTCG::PLAYER _player, const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for inspecting a board slot
  //----------------------------------------------------------------------------------------------------------------------
  virtual void inspectSlot(const PTCG::PLAYER _player, const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for inspecting a card
  //----------------------------------------------------------------------------------------------------------------------
  virtual void inspectCard(const PTCG::PLAYER _player, const PTCG::PILE _pile, const size_t _index) override;

private:
  std::string m_logPath = "../gamelogs/log.txt";
  std::string playerStr(const PTCG::PLAYER _player);
  std::string currentPlayerStr();
  std::string pileStr(const PTCG::PILE _origin);
  std::string triggerStr(const PTCG::TRIGGER _origin);
  void logToFile(const std::string &_msg);

};

#endif // GAMELOGGER_H
