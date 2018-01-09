#ifndef HAND_H
#define HAND_H
#include "cardpile.h"
#include <vector>

class Hand : public CardPile
{
public:
    Hand() = default;
    Hand (const Hand &_original);
    Hand& operator=(const Hand &);
    Hand(std::vector<std::unique_ptr<Card>>&& _cards) :
      m_cards(std::move(_cards))
    {}

    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const size_t _index) override;
    virtual Card* cardAt(const size_t _index) override;
    std::vector<std::unique_ptr<Card>> view() const;
    virtual size_t numCards() const override;
private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // HAND_H
