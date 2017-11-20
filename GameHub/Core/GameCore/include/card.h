#ifndef CARD_H
#define CARD_H

#include <string>

class Game;
class Card
{
protected:
  Card(const int _id, const std::string &_name) :
    m_id(_id),
    m_name(_name)
  {}

private:
  const int m_id;
  const std::string m_name;
};

#endif // CARD_H
