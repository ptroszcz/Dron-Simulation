#pragma once

#include "vector3D.hh"


/*!
 * \file
 * \brief Ten plik zawiera definicję klasy RectangleContour
 *
 * Ten plik zawiera definicję klasy RectangleContour
 */


/*!
 * \brief Klasa definiuje pojęcie obrysu prostopadłościennego
 * 
 * Klasa definiuje obrys prostopadłościanu, który jest powiększonym obrysem
 * prostopadłościanu od góry o promień drona, w celu ułatwienia wykrywania
 * kolizji. Przechowuje jego dwa wiechołki.
 */


class RectangleContour {

  public:
  
  Vector3D vertice_min;
  Vector3D vertice_max;
};
