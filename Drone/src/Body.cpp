#include "Body.hh"

/*!
 * \file
 * \brief Ten plik zawiera metody klasy Body
 *
 * Ten plik zawiera metody klasy Body z ich pełnym sposobem działania
 */

Vector3D Body::Move(double distance, double angle) {
  Vector3D Trans;
  Trans=(this->vertice[1]).Direct((this->vertice[2]),(distance*cos(angle)));
  Trans[2]=distance*sin(angle);
  return Trans;
}

