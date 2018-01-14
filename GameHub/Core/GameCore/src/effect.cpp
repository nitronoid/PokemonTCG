#include "effect.h"

Effect::~Effect() = default;

PTCG::TRIGGER Effect::getTrigger() const { return  m_trigger; }

PTCG::DURATION Effect::getDuration() const { return m_duration; }

std::string Effect::name() const { return m_name; }

void Effect::activate(Game& _game) const { m_ability(&_game); }

bool Effect::canActivate(Game&_game) const { return m_canUse(&_game);}

