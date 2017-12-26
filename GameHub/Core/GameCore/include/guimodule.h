#ifndef GUIMODULE_H
#define GUIMODULE_H
#include "board.h"

class GuiModule
{
public :
    virtual ~GuiModule(){}
    virtual void drawBoard(Board* _board)=0; //standard method
    virtual void drawBoard(Board* _board, const bool _isOp=false)=0; //differentiate between opponent board draw and current player
    //_drawType == f -> current; _drawType == t -> opponent
};

#endif // GUIMODULE_H
