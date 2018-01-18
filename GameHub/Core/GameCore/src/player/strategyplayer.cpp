#include "player/strategyplayer.h"
#include "game.h"

StrategyPlayer::StrategyPlayer(const StrategyPlayer& _original):
  Player(_original),
  m_userClone(_original.m_userClone->clone()),
  m_turn(_original.m_turn)
{}

StrategyPlayer::StrategyPlayer(Game*const _dummyGame, Player* _user) :
  Player(_dummyGame),
  m_userClone(_user)
{
  m_userClone->attachToGame(_dummyGame);
}

Player* StrategyPlayer::clone() const
{
  return new StrategyPlayer(*this);
}

std::string StrategyPlayer::deckName() const
{
  return m_userClone->deckName();
}

std::vector<size_t> StrategyPlayer::chooseCards(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  return m_userClone->chooseCards(_owner, _origin, _action, _options, _amount);
}

std::vector<size_t> StrategyPlayer::chooseSlot(
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<BoardSlot> &_options,
    const unsigned _amount
    )
{
  return m_userClone->chooseSlot(_owner, _action, _options, _amount);
}

void StrategyPlayer::learnCards(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const std::vector<size_t> &_indices,
    const std::vector<std::unique_ptr<Card>> &_revealed
    )
{
  m_userClone->learnCards(_owner, _origin, _indices, _revealed);
}

std::vector<size_t> StrategyPlayer::chooseEnergy(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _destination,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card> > &_options,
    const unsigned _amount
    )
{
  return m_userClone->chooseEnergy(_owner, _destination, _action, _options, _amount);
}

bool StrategyPlayer::agree(const PTCG::ACTION _action)
{
  return m_userClone->agree(_action);
}

std::vector<size_t> StrategyPlayer::chooseConditions(
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<PTCG::CONDITION> &_options,
    const unsigned _amount
    )
{
  return m_userClone->chooseConditions(_owner, _action, _options, _amount);
}

std::pair<bool, unsigned> StrategyPlayer::turn()
{
  // Return the decision
  return m_turn(m_userClone.get());
}

void StrategyPlayer::setTurn(const std::function<std::pair<bool, unsigned>(Player*)> _newTurnFunc)
{
  m_turn = _newTurnFunc;
}





