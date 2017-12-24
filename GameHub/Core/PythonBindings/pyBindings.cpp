#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "pokemoncard.h"
#include "game.h"

namespace py = pybind11;

PYBIND11_MODULE(poke, m) {

    py::class_<Game>(m, "Game")
        .def(py::init<>())
        .def("dealDamage", &Game::dealDamage, py::arg("_damage"), py::arg("_id") = 0u)
        .def("flipCoin", &Game::flipCoin);

}
