#include "gameobserver.h"

GameObserver::~GameObserver() = default;

void GameObserver::setGame(Game*const _subject)
{
  m_subject = _subject;
}
