#ifndef GAMEINL_H
#define GAMEINL_H

template<Game::Event k_event, typename... Args,
         typename std::enable_if_t<k_event == Game::Event::INSPECT_SLOT>*>
void Game::notifyGui(Args&&... args)
{
  for (const auto gui : m_guiObservers)
  {
    gui->inspectSlot(std::forward<Args>(args)...);
  }
}

template<Game::Event k_event, typename... Args,
         typename std::enable_if_t<k_event != Game::Event::INSPECT_SLOT>*>
void Game::notifyGui(Args&&... args)
{
  for (const auto gui : m_guiObservers)
  {
    gui->drawBoard(std::forward<Args>(args)...);
  }
}

#endif // GAMEINL_H
