#include "guimodule.h"

GuiModule::~GuiModule() = default;

void GuiModule::setGame(Game*const _subject)
{
  m_subject = _subject;
}
