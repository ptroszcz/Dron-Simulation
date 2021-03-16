#pragma once

#include "Prism.hh"



/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Body
 *
 * Ten plik zawiera definicję klasy Body będącą pochodną klasy Prism
 */


/*!
 * \brief Klasa definiuje pojęcie kadłuba dla drona
 * 
 * Klasa definiuje kadłub dla drona jako prostopadłościan, przechowując 
 * informacje o jego wierzchołkach i dodatkowo pozwalająca mu o ruch
 * do przodu
 */


class Body: public Prism {

  public:

/*!
 * \brief Konstruktor powodujący ustalenie poprawnej ilości wierzchołków
 *
 * Konstruktor powodujący ustalenie ośmiu wierzchołków dla każdego zainicjowanego
 * obiektu klasy Body, czyli ustanowienie go prostopadłościanem
 */
  Body() {vertice.resize(8);original_vertice.resize(8);}

  

/*!
 * \brief Metoda dająca wektor przesunięcia korpusu do przodu 
 *
 * Metoda dająca wektor przesunięcia korpusu do przodu o zadaną odległość
 * z zadanym kątem wznoszenia lub opadania
 * \param[in] distance - odleglosc drogi bryly
 * \param[in] angle:
 *                   - jeżeli dodatni to kąt wznoszenia
 *                   - jeżeli ujemny to kąt opadania
 * \return Zwraca wektor pozwalający przesunac bryle o zadana odleglosc
 *         oraz zadany kat unoszenia lub wznoszenia w strone w jaka jest
 *         zwrocona figura
 */   
  Vector3D Move(double distance, double angle);

};
