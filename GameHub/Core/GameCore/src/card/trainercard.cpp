#include "card/trainercard.h"
#include "game.h"

Card* TrainerCard::clone()
{
  return new TrainerCard(*this);
}

bool TrainerCard::canPlay(Game &_game) const
{
  return m_ability.canUse(_game);
}

void TrainerCard::playCard(Game&_game, const size_t _index)
{
  using card = PTCG::CARD;
  switch (m_type)
  {
    case card::ITEM:
    {
      _game.playItem(static_cast<TrainerCard*>(this), _index);
      break;
    }
    case card::TOOL:
    {
      _game.playTool(static_cast<TrainerCard*>(this), _index);
      break;
    }
    case card::SUPPORT:
    {
      _game.playSupport(static_cast<TrainerCard*>(this), _index);
      break;
    }
    case card::STADIUM:
    {
      //WILL IMPLEMENT STADIUM LATER WHEN IT IS INCLUDED IN OUR SET
      break;
    }
    default: break;
  }
}

PTCG::CARD TrainerCard::cardType() const
{
  return m_type;
}
