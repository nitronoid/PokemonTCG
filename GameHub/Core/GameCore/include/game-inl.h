#ifndef GAMEINL_H
#define GAMEINL_H

#include "game.h" //Does nothing except give syntax highlighting

// If the passed enum was INSPECT_SLOT this function is called
template<Game::Event k_event, typename... Args, Game::MatchEvent<k_event, Game::Event::INSPECT_SLOT>*>
void Game::notifyGui(Args&&... args)
{
  // For all gui-observers, we forward the args
  for (const auto gui : m_guiObservers)
  {
    // call the inspect slot function
    gui->inspectSlot(std::forward<Args>(args)...);
  }
}

template<Game::Event k_event, typename... Args,
         typename std::enable_if_t<k_event != Game::Event::INSPECT_SLOT>*>
void Game::notifyGui(Args&&... args)
{
  // For all gui-observers, we forward the args
  for (const auto gui : m_guiObservers)
  {
    // call the draw board function
    gui->drawBoard(std::forward<Args>(args)...);
  }
}

#endif // GAMEINL_H
