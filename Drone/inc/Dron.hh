#pragma once

#include "Rotor.hh"
#include "Body.hh"
#include "SceneObject.hh"


#define NUMBER_OF_ROTORS 4

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Dron
 *
 * Ten plik zawiera definicję klasy Dron
 */


/*!
 * \brief Klasa definiuje pojęcie drona
 * 
 * Klasa definiuje drona jako obiekt składający się z 5 figur: jednego 
 * prostopadłościanu oraz czterech graniastosłupów prostych, prawidłowych
 * sześciokątnych
 */
class Dron: public SceneObject {

  std::string _DronName;          /*pole przechowujące nazwę drona*/
  Rotor rotor[NUMBER_OF_ROTORS];  /*pole przechowujące wirniki drona*/

  public:

/*!
 * \brief Metoda zwracająca 'D'
 *
 * Metoda wirtualna pozwalająca na rozpoznanie że dany obiekt jest dronem
 * \return Zwraca 'D' co oznacza że jest to obiekt klast Dron
 */
  char ID() const {return 'D';}

  double radius; /*pole przechowujące promień drona*/

/*!
 * \brief Konstruktor nadający dronowi domyslną nazwę
 *
 * Konstruktor nadaje dronowi nazwę "Dron 0."przy jego inicjalizacji
 */
  Dron(): _DronName("Dron_0") {}

/*!
 * \brief Konstruktor nadający dronowi nazwę określoną przez użytkownika
 *
 * Konstruktor nadaje dronowi nazwę taką jaka zostanie podana jako parametr
 * tego konstruktora będąca typem const char*
 * \param[in] Name - nazwa jaką otrzyma inijowany drona
 */
  Dron(const char* Name): _DronName(Name) {}

/*!
 * \brief Metoda uzyskania nazwy drona
 *
 * Metoda pozwala na uzyskanie nazwy wybranego drona. Nazwa ta jest domyślna
 * jeżeli przy inicjacji drona nie została podana inna nazwa
 * \return Zwraca nazwę wybranego drona
 */  
  const std::string &TakeName() const {return _DronName;}


/*!
 * \brief Metoda zmiany nazwy drona
 *
 * Metoda pozwala na zmianę nazwy wybranego drona na podaną nową nazwę
 * \param[in] _name - nowa nazwa dla Drona
 */  
  void ChangeName(string _name) {_DronName=_name;};
  
  Body body;      /*pole przechowujące korpus drona*/

/*!
 * \brief Metoda ruchu drona o zadany wektor
 *
 * Metoda pozwalająca ruch całego drona czyli każdej figury z jakiej sie 
 * składa o zadany wektor klast Vector3D
 * \param[in] vect - wektor klast Vector3D o jaki ma zostać przesunięty
 *                   cały dron
 */  
  void Move_Dron(Vector3D vect);


/*!
 * \brief Metoda obrotu drona wokół właśnej osi o zadany kąt
 *
 * Metoda pozwalająca na obracanie się całego drona czyli wszystkich jego
 * figur o zadany kąt wokół osi drona
 * \param[in] angle - kąt o jaki ma się obrócić dron
 */  
  void Rotate_Dron(double angle);

  /*!
 * \brief Przeciążenie operatora odczytu '[]' dla klasy Dron
 * 
 * Metoda przeciąża operator '[]' dla klasy Dron , 
 * pozwalający na odczyt poszczególnych wirników drona
 * \param[in] lnd - indeks pozwalajacy na wybór wirnika
 *                 Jej wartość musi być mniejsza od ilości wirników, ale nie 
 *                 mniejsza niż 0
 * \return Zwraca wybrany wirnik czyli obiekt klasy Rotor
 */  
  Rotor operator [] (unsigned int lnd) const {
    if (lnd>=0 && lnd<NUMBER_OF_ROTORS)
    return rotor[lnd];
  else {
    cerr<<"Przekroczono zakres indeksów klasy Dron"<<endl;
    cerr<<"Wczytano wartosc pierwszego rotora"<<endl;
    return rotor[0]; }
  }

/*!
 * \brief Przeciążenie operatora zapisu '[]' dla klasy Dron
 * 
 * Metoda przeciąża operator '[]' dla klasy Dron , 
 * pozwalający na zapis wirników klasy Rotor w klasie Dron
 * \param[in] lnd - indeks pozwalajacy na wirnika drona
 *                  Jej wartość musi być mniejsza od wymiarów figury,
 *                  ale nie mniejsza niż 0
 * \return Zwraca referencję wybranego wirnika czyli obiektu klasy Rotor
 */  
  Rotor& operator [] (unsigned int lnd) {
    if (lnd>=0 && lnd<NUMBER_OF_ROTORS)
    return rotor[lnd];
  else {
    cerr<<"Przekroczono zakres indeksów klasy Dron"<<endl;
    cerr<<"Dokonana zmiana zastosowana dla pierwszego rotora"<<endl;
    return rotor[0];
  }
  }

/*!
 * \brief Metoda obliczająca środek drona
 *
 * Metoda oblicze współrzędne środka drona czyli środka podstawy jego korpusu
 * i zwraca je w postaci obiektu klasy Vector3D
 * \return Zwraca wektor reprezentujący środek drona
 */  
  Vector3D Center() const;


/*!
 * \brief Metoda sprawdzająca czy występuje kolizja dwóch dronów
 *
 * Metoda sprawdza czy podane drony kolidują ze sobą. Ponieważ drugi z dronów
 * jest typu SceneObject& należy jako argument wywołania podać wskaźnik typu
 * SceneObject na element typu Dron, aby funkcja zwróciła poprawny wynik
 * \param[in] dron - wskaźnik typu SceneObject na obiekt klasy Dron
 * \return true - gdy następuje kolizja
 * \return false - gdy nie następuje kolizja
 */  
  bool IsCollision(const SceneObject& dron) const;

};

/*!
 * \brief Przeciążenie operatora '<<' dla klasy Dron
 *
 * Przeciąża operator przesunięcia bitowego w lewo '<<' pozwalający na 
 * wyświetlenie wartości charakterystycznych drona w formacie: nazwa drona,
 * wpółrzędne jego środka  w nawiasie oddzielone przecinkiem podane z dokładnością
 *do jednego miejsca po przecinku
 * \param[in] stream - strumień, na który mają zostać wyświetlone informacje o dronie
 * \param[in] dron - dron, którego nazwa i współrzędne środka mają zostać wyświetlone
 */
std::ostream& operator <<(std::ostream &stream, const Dron dron);
