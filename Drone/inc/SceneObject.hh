#pragma once

#include <iostream>
#include "vector3D.hh"

using namespace std;
/*!
 * \file
 * \brief Ten plik zawiera definicję klasy SceneObject
 *
 * Ten plik zawiera definicję klasy SceneObject
 */


/*!
 * \brief Klasa definiuje pojęcie objektu sceny
 * 
 * Klasa definiuje objekt sceny jako wspólną klase przechowującą wszystkie 
 * elementy znajdujące się w scenie
 */
class SceneObject {

  static int existed;
  static int created;

  public:

/*!
 * \brief Metoda zwracająca 'S'
 *
 * Metoda wirtualna pozwalająca na rozpoznanie że dany obiekt jest obiektem 
 * sceny
 * \return Zwraca 'S' co oznacza że jest to obiekt klast SceneObject
 */
  virtual char ID() const {return 'S';}




/*!
  * \brief Metoda zwracająca ilość stworzonych do tej pory obiektów klasy SceneObject
  *
  * Metoda statyczna która zwraca wartość liczby stworzonych przez całe działanie
  * programu obiektów klasy SceneObject
  */
  static int TakeCreated() {return created;}

/*!
  * \brief Metoda zwracająca ilość istniejących w danym momencie obiektów klasy SceneObject
  *
  * Metoda statyczna, która zwraca wartość liczby istniejących w danym momencie 
  * obiektów klasy SceneObject
  */  
  static int TakeExisted() {return existed;}


  
/*!
 * \brief Konstruktor klasy SceneObject
 * 
 * Konstruktor nalicza liczbę stworzonych i istniejących objektów klasy SceneObject
 */
  SceneObject() {++existed;++created;}

  /*!
 * \brief Destruktor klasy SceneObject
 * 
 * Destruktor przy wywołaniu odejmuje liczbę stworzonych objektów klasy SceneObject
 */
  virtual ~SceneObject() {--existed;}

/*!
 * \brief Konstruktor kopiujący klasy SceneObject
 *
 * Konstruktor kopiujący wywoływany podczas przekazywania objektu sceny np. przy
 * przekazywaniu go do funkcji
 */
  SceneObject(const SceneObject& SceneObj) {
    ++(SceneObj.existed);
    ++(SceneObj.created);
  }

/*!
 * \brief Metoda wirtualna sprawdzająca wystąpienie kolizji
 *
 * Metoda wirtualna sprawdzająca czy występuje kolizja między dwoma obiektami
 * klasy SceneObject. Ponieważ jest to metoda wirtualna zwraca zawsze false
 * zaś jej pełne implementacje znajdują się w klasach pochodnych od klasy
 * SceneObject
 * \param[in] - referencja do obiektu klasy SceneObject
 * \return false - zawsze, gdy nie zostaje przysłonięta przez metody klas 
 *                 pochodnych
 */  
  virtual bool IsCollision(const SceneObject&) const {return false;}


/*!
 * \brief Metoda wirtualna sprawdzająca środek obiektu sceny
 *
 * Metoda wirtualna sprawdzająca współrzędne środka obiektu klasy SceneObject
 * Ponieważ jest to metoda wirtualna zwraca zawsze wektor zerowy
 * zaś jej pełne implementacje znajdują się w klasach pochodnych od klasy
 * SceneObject
 * \return Vector3D - Zwraca wektor klasy Vector3D o wszystkich współrzędnych
 *                    równych zeru
 */  
  virtual Vector3D Center() const{Vector3D V1;return V1;}




};
