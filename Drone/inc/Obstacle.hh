#pragma once

#include "Prism.hh"
#include "RectangleContour.hh"
#include "SceneObject.hh"
#include "Dron.hh"

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Obstacle
 *
 * Ten plik zawiera definicję klasy Obstacle będącą pochodną klasy Prism oraz
 * SceneObject
 */


/*!
 * \brief Klasa definiuje pojęcie przeszkody
 * 
 * Klasa definiuje przeszkodę jako granistosłup
 */


class Obstacle: public SceneObject, public Prism {

  public:


  
  RectangleContour ObjectContour; /*pole przechowujące obrys przeszkody 
                                           powiększony o promień drona*/

/*!
 * \brief Metoda zwracająca 'O'
 *
 * Metoda wirtualna pozwalająca na rozpoznanie że dany obiekt jest przeszkodą
 * \return Zwraca 'O' co oznacza że jest to obiekt klasy Obstacle
 */
  char ID() const {return 'O';}

/*!
 * \brief Metoda sprawdzająca czy występuje kolizja drona z przeszkodą
 *
 * Metoda sprawdza czy podana przeszkoda koliduje z podanym dronem.
 * Ponieważ dron jest typu SceneObject& należy jako argument wywołania
 * podać wskaźnik typu SceneObject na element typu Dron, aby funkcja
 * zwróciła poprawny wynik
 * \param[in] dron - wskaźnik typu SceneObject na obiekt klasy Dron
 * \return true - gdy następuje kolizja
 * \return false - gdy nie następuje kolizja
 */  
  bool IsCollision(const SceneObject& dron) const;

/*!
 * \brief Metoda obliczająca środek przeszkody
 *
 * Metoda oblicze współrzędne środka przeszkody czyli środka podstawy
 * i zwraca je w postaci obiektu klasy Vector3D
 * \return Zwraca wektor reprezentujący środek podstawy przeszkody
 */  
  Vector3D Center() const;

  

};
