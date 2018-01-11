#ifndef GUIMODULE_H
#define GUIMODULE_H
#include "board.h"

class Game;

class GuiModule
{
public :
  GuiModule() = default;
  virtual ~GuiModule();
  virtual void drawBoard() = 0;
  void setGame(Game*const _subject);

protected:
  Game* m_subject = nullptr;
};

#endif // GUIMODULE_H
