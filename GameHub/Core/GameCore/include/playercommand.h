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
  virtual void execute(HumanPlayer&_player) override;
};

struct AttackCMD : public Command
{
  AttackCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

struct RetreatCMD : public Command
{
  RetreatCMD() = default;
  virtual void execute(HumanPlayer&_player) override;
};

#endif // PLAYERCOMMAND_H
