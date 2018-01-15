#ifndef GAMEINL_H
#define GAMEINL_H

#include "game.h" //Does nothing except give syntax highlighting

// Use this namespace prevent polluting the public namespace and to hide implementation details
namespace _PTCG_DETAIL
{
// Alias to simplify template declarations, simply checks two events for equality
template<Game::Event k_eventA, Game::Event k_eventB>
using MatchEvent = typename std::enable_if_t<k_eventA == k_eventB>;

// guiSwitch can be thought of like a switch statement. Every overload is a different case.
// The defaulted template arg is used to enable and disable the overloads based on the passed event.
// First arg is the Event enum, second is a list of args to be forwarded to the guimodule call.
// This case is compiled when the passed Event was INSPECT_SLOT
template<Game::Event k_event, typename... Args, MatchEvent<k_event, Game::Event::INSPECT_SLOT>* = nullptr>
void observerCase(GuiModule*io_observer, Args&&...args)
{
  io_observer->inspectSlot(std::forward<Args>(args)...);
}

// This currently acts like a deafult case, when they didn't wan't to inspect a slot
template<Game::Event k_event, typename... Args,  typename std::enable_if_t<k_event != Game::Event::INSPECT_SLOT>* = nullptr>
void observerCase(GuiModule*io_observer, Args&&...args)
{
  io_observer->drawBoard(std::forward<Args>(args)...);
}
}


// Uses a compile time "switch" to select the correct function from guimodules interface
template<Game::Event k_event, typename... Args>
void Game::notify(Args&&... args)
{
  // For all gui-observers, we forward the args
  for (const auto observer : m_observers)
  {
    // call the inspect slot function
    _PTCG_DETAIL::observerCase<k_event>(observer, std::forward<Args>(args)...);
  }
}


#endif // GAMEINL_H
