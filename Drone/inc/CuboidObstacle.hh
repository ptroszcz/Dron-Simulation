#pragma once

#include "Obstacle.hh"

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy CuboidObstacle
 *
 * Ten plik zawiera definicję klasy CuboidObstacle będącą pochodną klasy Obstacle
 */


/*!
 * \brief Klasa definiuje pojęcie przeszkody prostopadłościennej
 * 
 * Klasa definiuje przeszkodę jako prostopadłościań przechowując informację o jego 
 * wiechłokach
 */


class CuboidObstacle: public Obstacle {

  std::string _ObstacleName;

  public:
  
/*!
 * \brief Konstruktor powodujący ustalenie poprawnej ilości wierzchołków
 *
 * Konstruktor powodujący ustalenie ośmiu wierzchołków dla każdego zainicjowanego
 * obiektu klasy CuboidObstacle, czyli ustanowienie go prostopadłościanem
 */
  CuboidObstacle(): _ObstacleName("Obstacle_0") {vertice.resize(8);original_vertice.resize(8);}


  /*!
 * \brief Konstruktor powodujący ustalenie poprawnej ilości wierzchołków oraz 
 *       zadanie wybranej nazwy
 *
 * Konstruktor powodujący ustalenie ośmiu wierzchołków dla każdego zainicjowanego
 * obiektu klasy CuboidObstacle, czyli ustanowienie go prostopadłościanem oraz nazywający
 * przeszkodę zadaną nazwą
 *\param[in] Name - nazwa dla tworzonego obiektu klasy CuboidObstacle
 */
  CuboidObstacle(const char* Name): _ObstacleName(Name) {vertice.resize(8);original_vertice.resize(8);}


};
