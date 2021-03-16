#pragma once

#include <memory>
#include <list>
#include "Dron.hh"
#include "CuboidObstacle.hh"
#include "vector3D.hh"
#include <string>

using namespace std;


/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Factory
 *
 * Ten plik zawiera definicję klasy Factory oraz wFactory(czyli klasy która
 * sprawi, że klasa Factory będzie singletonem).
 */


enum ObjectType {OT_Dron, OT_CuboidObstacle};

class Factory;   /*krotka definicja, aby moc uzyc przy implemenatcji wskaznika*/


/*!
 * \brief Klasa definiuje pojęcie wskażnika na obiekt klasy Factory
 * 
 * Klasa definiuje pojęcie wskażnika na obiekt klasy Factory, co pozwala uczynić
 * z klast Factory singleton
 */
class wFactory: private shared_ptr<Factory> {

  friend class Factory;

/*!
 * \brief Metoda tworząca wskażnik na fabrykę
 *
 * Metoda tworzy wskaźnik na obiekt klasy Factory. Jest to jedyna metoda
 * pozwalająca zainicjować fabrykę
 */
  void CreateFactory();

/*!
 * \brief Metoda niszczy wskażnik na fabrykę
 *
 * Metoda niszczy wskaźnik na obiekt klasy Factory. Oznacza to że, ustawia go
 * jako nullptr.
 */
  void DestroyFactory() {this->reset(static_cast<Factory*>(nullptr));}
  
  public:

/*!
 * \brief Przeciążenie operatora "->" dla klasy wFactory
 *
 * Przeciążenie operatora "->" dla klasy wFactory. Ma na celu ułatwienie zapisu
 * dla piszącego program.
 * \return Zwraca odpowiedni wskażnik na klasę wFactory, odpowiadający takiemu
 *         wywołanemu przy klasie nie będącej wskaźnikiem  przy użyciu operatora "->"
 */
    Factory* operator -> () {return &**this;}

};
  

/*!
 * \brief Klasa definiuje pojęcie fabryki objektów
 * 
 * Klasa definiuje pojęcie fabryki objektów realizującej wzorzec projektowy 
 * fabryki obiektów oraz singletonu
 */
class Factory {
  
  static wFactory _wFactory;

  string _Name;

  Vector3D Center;
  Vector3D Dimensions={100,100,100};

 public:

/*!
 * \brief Metoda pozwalająca na użycie fabryki
 *
 * Metoda ta jest jedynym możliwym sposobem na wykorzystanie klasy Factory i jej
 * metod
 * \return Zwraca wskaźnik na fabrykę
 */
  static wFactory& UseFactory() {return _wFactory;}

/*!
 * \brief Metoda tworząca fabrykę
 *
 * Metoda tworzy obiekt klasy Factory inicjując wskaźnik na nią
 */
  static void CreateFactory(){ _wFactory.CreateFactory();}

/*!
 * \brief Metoda niszcząca fabrykę
 *
 * Metoda niszczy obiekt klasy Factory resetując wartość wskaźnika na nią na nullptr
 */
  static void DestroyFactory() { _wFactory.DestroyFactory();}

/*!
 * \brief Metoda zmieniajaca nazwę tworzonego obiektu
 *
 * Metoda pozwala na zmianę nazwy obiektu, który zostanie stworzony przez metodę
 * CreateObject
 * \param[in] sName - nowa nazwa dla następnego utworzonego obiektu przez fabrykę
 */
  void ChangeName(const char* sName) { _Name = sName; }

/*!
 * \brief Metoda zmieniajaca środek tworzonego obiektu
 *
 * Metoda pozwala na zmianę środka obiektu, który zostanie stworzony przez metodę
 * CreateObject
 * \param[in] center - wektor zawiejący współrzędne środka następnego stworzonego obiektu
 */
  void ChangeCenter(Vector3D center) {this->Center=center;}

/*!
 * \brief Metoda zmieniajaca wymiary tworzonej przeszkody
 *
 * Metoda pozwala na zmianę wymiarów przeszkody, która zostanie stworzona
 * przez metodę CreateObject
 * \param[in] dim - wektor zawierający wymiary następnej stworzonej przeszkody
 */
  void ChangeDimensions(Vector3D dim) {this->Dimensions=dim;}

/*!
 * \brief Metoda tworząca obiekt klasy Dron lub CuboidObstacle
 *
 * Metoda tworząca obiekt klasy Dron(o zadanym środku)  lub CuboidObstacle(o zadanym
 * środku oraz wymiarach
 * \param[in] Nazwa typu tworzonego obiektu:
 *            - OT_Dron: jeżeli ma zostać stworzony obiekt klasy Dron
 *            - OT_CuboidObstacle: jeżeli ma zostać stworzony obiekt klasy CuboidObstacle
 * \return Zwraca wskażnik współdzielony shared_ptr<> na obiekt klasy SceneObject
 */
  shared_ptr<SceneObject> CreateObject(ObjectType ObjType) const;


 private:

  friend class wFactory;


/*!
 * \brief Konstruktor klasy Factory
 *
 * Konstruktor klasy Factory bez dodatkowej definicji. Umieszczony w polu prywatnym
 * dzięki czemu nie można go zainicjować inaczej niż metodą CreateFactory
 */
  Factory() {}
  
/*!
 * \brief Konstruktor kopiujący klasy Factory
 *
 * Konstruktor kopiujący klasy Factory. Definicja nie pozwala na używanie tego 
 * konstruktora w żadnym miejscu programu
 */
  Factory(const Factory&) =delete;
};


  

  
  
