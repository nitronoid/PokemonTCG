#ifndef POKEMONCARD_H
#define POKEMONCARD_H

#include "card/card.h"
#include "effect/attack.h"
#include <vector>
#include <unordered_set>

class PokemonCard : public Card
{
public:
  PokemonCard(const PokemonCard&) = default;
  PokemonCard& operator=(const PokemonCard&) = delete;
  PokemonCard(
      const unsigned _id,
      const std::string &_name,
      const Ability & _ability,
      std::vector<Attack> && _attacks,
      const PTCG::TYPE _type,
      const PTCG::TYPE _weakness,
      const PTCG::TYPE _resistance,
      const int _hp,
      const unsigned _retreatCost,
      const unsigned _stage,
      const std::string _preEvo = ""
      ) :
    Card(_id, _name, _ability),
    m_type(_type),
    m_weakness(_weakness),
    m_resistance(_resistance),
    m_attacks(_attacks),
    m_preEvolution(_preEvo),
    m_hp(_hp),
    m_retreatCost(_retreatCost),
    m_stage(_stage)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~PokemonCard() = default;

  virtual bool canPlay(Game&io_game) const override;

  virtual void playCard(Game&_game, const size_t _index) override;

  bool canAttack(Game &_game, const size_t _attackID, std::unordered_multiset<PTCG::TYPE> _attachedEnergy);

  virtual Card* clone() override;

  void attack(const unsigned &_attackIndex, Game& _game);

  virtual PTCG::CARD cardType() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get pokemon type
  /// @return pokemon type enum
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TYPE type() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get weakness type
  /// @return pokemon type enum (weakness)
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TYPE weakness() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get resistance type
  /// @return pokemon type enum (resistance)
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TYPE resistance() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get hp
  /// @return an int number
  //----------------------------------------------------------------------------------------------------------------------
  int hp() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get retreat cost
  /// @return an unsigned integer value
  //----------------------------------------------------------------------------------------------------------------------
  unsigned retreatCost() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get stage of current pokemon
  /// @return an unsigned integer value
  //----------------------------------------------------------------------------------------------------------------------
  unsigned stage() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get attacks of this pokemon
  /// @return vector of attacks
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Attack> attacks() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the number of attacks
  /// @return the number of attacks
  //----------------------------------------------------------------------------------------------------------------------
  unsigned attackNum() const;
  
private:
  PTCG::TYPE  m_type;
  PTCG::TYPE  m_weakness;
  PTCG::TYPE  m_resistance;
  std::vector<Attack> m_attacks;
  std::string m_preEvolution;  //ADD TO CONSTRUCTOR
  int         m_hp;
  unsigned    m_retreatCost;
  unsigned    m_stage;

};

#endif // POKEMONCARD_H
