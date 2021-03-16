#pragma once

#include <list>
#include <memory>
#include "CuboidObstacle.hh"
#include "Dron.hh"


#define NUMBER_OF_DRONS 3
#define NUMBER_OF_OBSTACLE 3
/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Scene
 *
 * Ten plik zawiera definicję klasy Scene 
 */


/*!
 * \brief Klasa definiuje pojęcie sceny
 * 
 * Klasa definiuje scene czyli klase przetrzymującą informację o obiektach,
 * znajdujących się w niej. Dokładniej mówiąc:
 * - listę wskażników na obiekty klasy Dron
 * - liste wskaźników na obiekty klasy SceneObject
 */

class Scene {

  public:
  std::list<std::shared_ptr<Dron>> Robot;
  std::list<std::shared_ptr<SceneObject>> ScObj;
};
  
