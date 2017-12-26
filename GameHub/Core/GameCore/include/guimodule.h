#ifndef GUIMODULE_H
#define GUIMODULE_H
#include "board.h"

class GuiModule
{
public :
    virtual ~GuiModule(){}
    virtual void drawBoard(Board* _board, const bool _isOp)=0;
    //_drawType == f -> current; _drawType == t -> opponent
};

#endif // GUIMODULE_H
