#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "pokemoncard.h"
#include "game.h"

//void dealDamage(int _ammount)
//{
//  std::cout<<"Player dealt: "<<_ammount<<" damage!\n";
//}

namespace py = pybind11;

PYBIND11_MODULE(poke, m) {

    py::class_<Game>(m, "Game")
        .def(py::init<>())
        .def("dealDamage", &Game::dealDamage);

//    m.def("dealDamage", &dealDamage, "A function which deals damage");
}
