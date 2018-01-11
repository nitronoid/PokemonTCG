#include "player.h"
#include "game.h"

Player::~Player() {}

void Player::playCard(const size_t &_index)
{
  m_parentGame.playCard(_index);
}

void Player::retreat()
{
    constexpr auto self = PTCG::PLAYER::SELF;
    if(m_parentGame.activeCanRetreat(self))
    {
        constexpr auto filter = [](BoardSlot*const _slot){return !_slot->active();};
        auto switchChoice = m_parentGame.playerSlotChoice(self, self, PTCG::ACTION::MOVE, 1, filter);
        auto bench = viewBench(self);
        // passing a lambda to return any energy card types
        std::function<bool(Card*const)> match = [](Card* const){return true;};
        //we need to choose our energy to discard
        auto choice = m_parentGame.playerEnergyChoice(
            self,
            self,
            PTCG::PILE::DISCARD,
            PTCG::ACTION::DISCARD,
            0,
            match,
            bench.at(0).active()->retreatCost());
        m_parentGame.removeEnergy(self, PTCG::PILE::DISCARD,0,choice);
        m_parentGame.switchActive(self, switchChoice[0]);
        m_canRetreat = false;
    }
}

bool Player::canPlay(const size_t &_index)
{
  return m_parentGame.canPlay(_index);
}

Game Player::getDummyGame() const
{
  return m_parentGame.clone();
}

std::vector<std::unique_ptr<Card>> Player::viewHand() const
{
  return m_parentGame.viewHand(PTCG::PLAYER::SELF);
}

std::vector<std::unique_ptr<Card>> Player::viewDiscard(const PTCG::PLAYER &_owner) const
{
  return m_parentGame.viewDiscard(_owner);
}

std::array<BoardSlot, 6> Player::viewBench(const PTCG::PLAYER &_owner) const
{
  return m_parentGame.viewBench(_owner);
}

bool Player::canRetreat()
{
  return m_canRetreat;
}
