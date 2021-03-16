#include "Obstacle.hh"

/*!
 * \file
 * \brief Ten plik zawiera metody klasy Obstacle
 *
 * Ten plik zawiera metody klasy Obstacle z ich pełnym sposobem działania
 */

bool Obstacle::IsCollision(const SceneObject& object) const{
  Vector3D center,min,max;
    center=object.Center();
    min=(this->ObjectContour).vertice_min;
    max=(this->ObjectContour).vertice_max;
    if (center[0]<=max[0]&&center[0]>=min[0]) {
      if(center[1]<=max[1]&&center[1]>=min[1]) {
	if (center[2]<=max[2]&&(center[2]+100)>=min[2])
	  return true;
      }
    }
    return false;
}

Vector3D Obstacle::Center() const {
  Vector3D result;
  result=(this->vertice[2])-(this->vertice[0]);
  result=result/2;
  result+=(this->vertice[2]);
  return result;
}
