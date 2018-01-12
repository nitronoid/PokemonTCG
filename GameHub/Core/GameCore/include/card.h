#ifndef CARD_H
#define CARD_H

#include "ability.h"
#include <string>
#include <iostream>

class Card
{
public:
  /// @brief default copy ctor
  Card(const Card&) = default;
  /// @brief default assignement operator
  Card& operator=(const Card&) = default;
  /// @brief ctor to construct a Card
  /// @param [in] _id Set ID of the card
  /// @param [in] _name name of the card
  /// @param [in] _ability effects of a card
  Card(const unsigned _id, const std::string &_name, const Ability & _ability) :
    m_ability(_ability),
    m_name(_name),
    m_id(_id)
  {}
  /// @brief virtual dtor
  virtual ~Card();
  /// @brief a check if the card can be played
  virtual bool canPlay(Game&_game) const = 0;
  /// @brief returns the clone of the card
  virtual Card* clone() = 0;
  /// @brief returns the type of card this card is
  virtual PTCG::CARD cardType() const = 0;
  /// @brief use the ability of the card
  void activateAbility(Game &_game) const;
  /// @brief return name of a card
  inline std::string getName() const{return m_name;}
  /// @brief returns set ID of a card
  inline unsigned getID()const{return m_id;}

protected:
  /// @brief effect object of the card
  Ability m_ability;
private:
  /// @brief name of the card
  std::string m_name;
  /// @brief ID of the card in the card set
  unsigned m_id;
};

#endif // CARD_H
