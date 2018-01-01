#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "pokemoncard.h"
#include "game.h"

namespace py = pybind11;

PYBIND11_MODULE(poke, m)
{
// ENUMS
  py::enum_<PTCG::TYPE>(m, "TYPE")
      .value("COLOURLESS", PTCG::TYPE::COLOURLESS)
      .value("FIGHTING",   PTCG::TYPE::FIGHTING)
      .value("LIGHTNING",  PTCG::TYPE::LIGHTNING)
      .value("GRASS",      PTCG::TYPE::GRASS)
      .value("PSYCHIC",    PTCG::TYPE::PSYCHIC)
      .value("METAL",      PTCG::TYPE::METAL)
      .value("WATER",      PTCG::TYPE::WATER)
      .value("DARKNESS",   PTCG::TYPE::DARKNESS)
      .value("FIRE",       PTCG::TYPE::FIRE)
      .value("DRAGON",     PTCG::TYPE::DRAGON)
      .value("FAIRY",      PTCG::TYPE::FAIRY)
      .value("ERROR",      PTCG::TYPE::ERROR);

  py::enum_<PTCG::CONDITION>(m, "CONDITION")
      .value("ASLEEP",    PTCG::CONDITION::ASLEEP)
      .value("BURNED",    PTCG::CONDITION::BURNED)
      .value("POISONED",  PTCG::CONDITION::POISONED)
      .value("CONFUSED",  PTCG::CONDITION::CONFUSED)
      .value("PARALYZED", PTCG::CONDITION::PARALYZED);

  py::enum_<PTCG::PHASE>(m, "PHASE")
      .value("DRAW",    PTCG::PHASE::DRAW)
      .value("MAIN",    PTCG::PHASE::MAIN)
      .value("ATTACK",  PTCG::PHASE::ATTACK)
      .value("NONE",    PTCG::PHASE::NONE);

  py::enum_<PTCG::DURATION>(m, "DURATION")
      .value("SINGLE",    PTCG::DURATION::SINGLE)
      .value("MULTIPLE",  PTCG::DURATION::MULTIPLE)
      .value("PERMANENT", PTCG::DURATION::PERMANENT);

  py::enum_<PTCG::CARD>(m, "CARD")
      .value("ENERGY",    PTCG::CARD::ENERGY)
      .value("POKEMON",   PTCG::CARD::POKEMON)
      .value("ITEM",      PTCG::CARD::ITEM)
      .value("TOOL",      PTCG::CARD::TOOL)
      .value("SUPPORT",   PTCG::CARD::SUPPORT)
      .value("STADIUM",   PTCG::CARD::STADIUM);

  py::enum_<PTCG::PLAYER>(m, "PLAYER")
      .value("SELF",  PTCG::PLAYER::SELF)
      .value("ENEMY", PTCG::PLAYER::ENEMY);

  py::enum_<PTCG::PILE>(m, "PILE")
      .value("DECK",    PTCG::PILE::DECK)
      .value("HAND",    PTCG::PILE::HAND)
      .value("DISCARD", PTCG::PILE::DISCARD)
      .value("PRIZE",   PTCG::PILE::PRIZE);

  py::enum_<PTCG::ACTION>(m, "ACTION")
      .value("DRAW",    PTCG::ACTION::DRAW)
      .value("DISCARD", PTCG::ACTION::DISCARD)
      .value("PLAY",    PTCG::ACTION::PLAY)
      .value("VIEW",    PTCG::ACTION::VIEW)
      .value("MOVE",    PTCG::ACTION::MOVE);

  py::enum_<PTCG::ORDER>(m, "ORDER")
        .value("BEFORE",  PTCG::ORDER::BEFORE)
        .value("AFTER",   PTCG::ORDER::AFTER);

  py::class_<Card>(m, "Card")
      //.def(py::init<const unsigned, const std::string&, const Ability&>())
      .def("canPlay", &Card::canPlay)
      .def("cardType", &Card::cardType)
      .def("getName", &Card::getName)
      .def("getID", &Card::getID);

  py::class_<PokemonCard, Card>(m, "PokemonCard")
      .def(py::init<
           const unsigned,
           const std::string&,
           const Ability&,
           std::vector<Attack>&&,
           const PTCG::TYPE,
           const PTCG::TYPE,
           const PTCG::TYPE,
           const int,
           const unsigned,
           const unsigned
           >())
      .def("preEvolution", &PokemonCard::preEvolution)
      .def("type", &PokemonCard::type)
      .def("weakness", &PokemonCard::weakness)
      .def("resistance", &PokemonCard::resistance)
      .def("hp", &PokemonCard::hp)
      .def("retreatCost", &PokemonCard::retreatCost)
      .def("stage", &PokemonCard::stage);

  py::class_<BoardSlot>(m, "BoardSlot")
      .def(py::init<>())
      .def("getDamage", &BoardSlot::getDamage)
      .def("getBonusBefore", &BoardSlot::getBonusBefore)
      .def("getBonusAfter", &BoardSlot::getBonusAfter)
      .def("getReductionBefore", &BoardSlot::getReductionBefore)
      .def("getReductionAfter", &BoardSlot::getReductionAfter)
      .def("getTurnPlayed", &BoardSlot::getTurnPlayed)
      .def("numPokemon", &BoardSlot::numPokemon)
      .def("numEnergy", &BoardSlot::numEnergy)
      .def("numTool", &BoardSlot::numTool)
      .def("numCards", &BoardSlot::numCards)
      .def("active", &BoardSlot::active, py::return_value_policy::reference_internal);


  py::class_<Game>(m, "Game")
      .def(py::init<>())
      .def("dealDamage", &Game::dealDamage, py::arg("_damage"), py::arg("_id") = 0u)
      .def("healDamage", &Game::healDamage, py::arg("_heal"), py::arg("_id") = 0u)
      .def("applyCondition", &Game::applyCondition)
      .def("freeSlots", &Game::freeSlots)
      .def("playerCardChoice", &Game::playerCardChoice,
           py::arg("_thinker"),
           py::arg("_owner"),
           py::arg("_origin"),
           py::arg("_action"),
           py::arg("_match"),
           py::arg("_amount"),
           py::arg("_range") = 0)
      .def("viewDeck", &Game::viewDeck)
      .def("viewDiscard", &Game::viewDiscard)
      .def("viewHand", &Game::viewHand)
      .def("viewPrize", &Game::viewPrize)
      .def("viewBench", &Game::viewBench)
      .def("pileToBench", &Game::pileToBench)
      .def("moveCards", &Game::moveCards,
           py::arg("_cardIndices"),
           py::arg("_owner"),
           py::arg("_origin"),
           py::arg("_destination"),
           py::arg("_reveal") = false,
           py::arg("_destIndex") = std::vector<unsigned>{})
      .def("shuffleDeck", &Game::shuffleDeck)
      .def("flipCoin", &Game::flipCoin);

}
