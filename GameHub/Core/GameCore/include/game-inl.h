#ifndef GAMEINL_H
#define GAMEINL_H

#include "game.h" //Does nothing except give syntax highlighting

// Use this namespace to prevent polluting the public namespace and to hide implementation details
namespace _PTCG_DETAIL
{
using event = Game::Event;
// Alias to simplify template declarations, simply checks two events for equality
template<event k_eventA, event k_eventB>
using MatchEvent = typename std::enable_if_t<k_eventA == k_eventB>;

// observerCase can be thought of like a case in a switch statement. Every overload is a different case.
// The defaulted template arg is used to enable and disable the overloads based on the passed event.
// First arg is the Event enum, second is a list of args to be forwarded to the guimodule call.

// This case is compiled when the passed Event was START_TURN
template<event k_event, typename... Args, MatchEvent<k_event, event::START_TURN>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->startTurn(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was EFFECT_USED
template<event k_event, typename... Args, MatchEvent<k_event, event::EFFECT_USED>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->effectUsed(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was ATTACK
template<event k_event, typename... Args, MatchEvent<k_event, event::ATTACK>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->attackUsed(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was PLAY_CARD
template<event k_event, typename... Args, MatchEvent<k_event, event::PLAY_CARD>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->playCard(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was SWAP_SLOT
template<event k_event, typename... Args, MatchEvent<k_event, event::SWAP_SLOT>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->swapSlot(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was MOVE_CARD
template<event k_event, typename... Args, MatchEvent<k_event, event::MOVE_CARD>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->moveCard(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was KNOCK_OUT
template<Game::Event k_event, typename... Args, MatchEvent<k_event, Game::Event::KNOCK_OUT>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->knockOut(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was INSPECT_SLOT
template<Game::Event k_event, typename... Args, MatchEvent<k_event, Game::Event::INSPECT_SLOT>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->inspectSlot(std::forward<Args>(args)...);
}

// This case is compiled when the passed Event was INSPECT_CARD
template<event k_event, typename... Args, MatchEvent<k_event, event::INSPECT_CARD>* = nullptr>
void observerCase(GameObserver*io_observer, Args&&...args)
{
  io_observer->inspectCard(std::forward<Args>(args)...);
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
