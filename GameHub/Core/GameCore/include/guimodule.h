#ifndef GUIMODULE_H
#define GUIMODULE_H
#include "board.h"

class GuiModule
{
public :
    virtual ~GuiModule(){}
    virtual void drawBoard(Board* _board)=0;
};

#endif // GUIMODULE_H
