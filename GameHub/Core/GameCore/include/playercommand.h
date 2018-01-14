#ifndef PLAYERCOMMAND_H
#define PLAYERCOMMAND_H

class HumanPlayer;

struct Command
{
  Command() = default;
  virtual ~Command() = default;
  virtual void execute(HumanPlayer&_player) = 0;
};

struct PlayCardCMD : public Command
{
  PlayCardCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~PlayCardCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct AttackCMD : public Command
{
  AttackCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~AttackCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct RetreatCMD : public Command
{
  RetreatCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~RetreatCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct RestartCMD : public Command
{
  RestartCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~RestartCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct ExitCMD : public Command
{
  ExitCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~ExitCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct SkipCMD : public Command
{
  SkipCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~SkipCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct InspectSlotCMD : public Command
{
  InspectSlotCMD() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~InspectSlotCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

#endif // PLAYERCOMMAND_H
