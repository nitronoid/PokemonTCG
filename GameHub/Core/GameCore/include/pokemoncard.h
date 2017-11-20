#ifndef POKEMONCARD_H
#define POKEMONCARD_H

#include "card.h"
#include "pokemonenums.h"
#include <vector>
#include <functional>

class PokemonCard : public Card
{
public:
  PokemonCard(const PokemonCard &) = default;
  PokemonCard(const int _id, const int _hp, const std::string &_name, const PTCG::TYPE _type) :
    Card(_id, _name),
    m_type(_type),
    m_hp(_hp)
  {}

  inline void addAttack(std::function<void(const Game&)> _attack)
  {
    m_attacks.push_back(_attack);
  }

  inline void attack(int _index, const Game& _game)
  {
    m_attacks[_index](_game);
  }

private:
  std::vector<std::function<void(const Game&)>> m_attacks;
  const PTCG::TYPE m_type;
  const int m_hp;


};

#endif // POKEMONCARD_H
