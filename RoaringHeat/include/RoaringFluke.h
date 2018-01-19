#ifndef ROARINGFLUKE_H
#define ROARINGFLUKE_H

#include "player/player.h"

class RoaringFluke : public Player
{
public:
  RoaringFluke(const RoaringFluke&) = default;
  RoaringFluke(Game* _parentGame) :
    Player(_parentGame)
  {}

  virtual Player* clone() const override;

  virtual std::string deckName() const override;

  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;

  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) override;

  virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) override;

  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;

  virtual std::vector<size_t> chooseConditions(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<PTCG::CONDITION> &_options,
      const unsigned _amount
      ) override;

  virtual bool agree(const PTCG::ACTION _action) override;
  virtual std::pair<bool, unsigned> turn() override;

private:
  using cardRefList = std::vector<Card*>;
  void refreshFilteredHand(
          std::vector<std::unique_ptr<Card>>& io_hand,
          cardRefList& io_pokeList,
          cardRefList& io_energyList,
          cardRefList& io_trainerList,
          std::vector<int>& io_pokeIndexList,
          std::vector<int>& io_energyIndexList,
          std::vector<int>& io_trainerIndexList);
  unsigned m_found;

};


#endif // ROARINGFLUKE_H
