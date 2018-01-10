#ifndef AIPLAYERBT_H
#define AIPLAYERBT_H

/// BrightTide includes
#include "sequence.h"
#include "selector.h"
#include "action.h"
#include "condition.h"
#include "player.h"

class AIPlayerBT : public Player
{
public:
  AIPlayerBT(const AIPlayerBT&) = default;
  AIPlayerBT(Game& _parentGame) :
    Player(_parentGame)
  {}

  virtual Player* clone() const override;

  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;

  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) override;

  virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) override;

  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;

  virtual bool agree(const PTCG::ACTION _action) override;

  /// @build bool (attack or not), unsigned (which attack)
  virtual std::pair<bool, unsigned> turn() override;

};

#endif // AIPLAYERBT_H
