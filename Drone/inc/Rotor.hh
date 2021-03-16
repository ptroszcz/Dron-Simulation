#pragma once

#include "Prism.hh"

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Rotor
 *
 * Ten plik zawiera definicję klasy Rotor
 */


/*!
 * \brief Klasa definiuje pojęcie wirnika
 * 
 * Klasa definiuje wirnik, który jest reprezentowany przez graniastosłup
 * prosty, prawidłowy sześciokątny
 */
class Rotor: public Prism {

  public:
  
/*!
 * \brief Konstruktor powodujący ustalenie poprawnej ilości wierchołków
 *
 * Konstruktor powodujący ustalenie dwunastu wierzchołków dla każdego zainicjowanego
 * obiektu klasy Rotor, czyli ustanowienie go graniastosłupem prawidłowym, prostym
 * sześciokątnym
 */
  Rotor() {vertice.resize(12);original_vertice.resize(12);}

};
