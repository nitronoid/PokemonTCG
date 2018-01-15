#ifndef SIMPLEPRINTER_H
#define SIMPLEPRINTER_H
#include "guimodule.h"

class SimplePrinter : public GuiModule
{
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  SimplePrinter() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~SimplePrinter() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief main draw method, draws entire thing
  //----------------------------------------------------------------------------------------------------------------------
  virtual void drawBoard() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief interface for inspecting a board slot
  //----------------------------------------------------------------------------------------------------------------------
  virtual void inspectSlot(const PTCG::PLAYER _player, const size_t _index) override;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw one side of board, self and opponent are handled differently
  /// @param [in] board to draw
  /// @param [in] a switch for self/opponent
  //----------------------------------------------------------------------------------------------------------------------
  void drawSide(Board* _board, const bool _isOp);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute pokemon card string fields with information
  /// @param [io] the card string
  /// @param [in] a reference card
  //----------------------------------------------------------------------------------------------------------------------
  void pokemonStr(std::string &_str, PokemonCard * const _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute big sentinel slot fields with information
  /// @param [in] reference slot
  /// @param [in] the status of the active pokemon in slot
  /// @return final slot string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string bigSlotStr(BoardSlot* const _slot, Status *const _activeStatus) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute big sentinel card fields with information
  /// @param [in] reference card
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string bigCardStr(Card* const _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute big sentinel PokemonCard fields with information
  /// @param [in] reference card
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string bigPCStr(PokemonCard* _card, std::string _ret="") const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute big sentinel EnergyCard fields with information
  /// @param [in] reference card
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string bigECStr(EnergyCard* _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute big sentinel TrainerCard fields with information
  /// @param [in] reference card
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string bigTCStr(TrainerCard* _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute sentinel slot fields with information
  /// @param [in] reference slot
  /// @return final slot string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string slotStr(BoardSlot* const _slot) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute sentinel slot fields with information
  /// @param [in] reference active slot
  /// @param [in] the status of the active pokemon in slot
  /// @return final active slot string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string activeStr(BoardSlot* const _activeSlot, Status * const _activeStatus) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief construct bench string using bench cards information
  /// @param [in] reference bench
  /// @return final bench string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string benchStr(Bench * const _bench) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief construct hand string using hand cards information
  /// @param [in] reference hand
  /// @return final hand string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string handStr(Hand * const _hand) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute sentinel hand card fields with information
  /// @param [in] reference card from hand
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string cardStr(Card * const _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute sentinel energy card (hand) fields with information
  /// @param [in] reference card from hand
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string energyCardStr(EnergyCard * const _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute sentinel pokemon card (hand) fields with information
  /// @param [in] reference card from hand
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string pokemonCardStr(PokemonCard * const _card) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief substitute sentinel trainer card (hand) fields with information
  /// @param [in] reference card from hand
  /// @param [in] type of the trainer card
  /// @return final card string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string trainerCardStr(TrainerCard * const _card, const std::string &_type) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief make a prize card string based on card presence
  /// @param [in] reference prize card pile
  /// @return final pile string for printout
  //----------------------------------------------------------------------------------------------------------------------
  std::string prizeStr(PrizeCards * const _prize) const;
};

#endif // SIMPLEPRINTER_H
