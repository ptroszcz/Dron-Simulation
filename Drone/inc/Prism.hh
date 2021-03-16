#pragma once


#include <iostream>
#include "vector3D.hh"
#include "matrix3x3.hh"
#include <vector>

using namespace std;


/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Prism
 *
 * Ten plik zawiera definicję klasy Prism
 */


/*!
 * \brief Klasa definiuje pojęcie Graniastosłupa
 * 
 * Klasa definiuje graniastosłup przechowując informacje o współrzędnych
 * jego wierzchołków oraz o jego pierwotnych współrzędnych wierzchołków
 * czyli takich przed zastosowanie dowolnej z metod, które obsługuje 
 * takich jak obrót czy translacja
 */
class Prism {
  
  public:

  std::vector<Vector3D> vertice;
  std::vector<Vector3D> original_vertice; /*tablica przechowujaca oryginalne
					    wymiary danej bryly*/

/*!
 * \brief Przeciążenie operatora odczytu '[]' dla klasy Prism
 * 
 * Metoda przeciąża operator '[]' dla klasy Prism , 
 * pozwalający na odczyt wartości współrzędnych poszczególnych wierzchołków.
 * \param[in] lnd - indeks pozwalajacy na wybór numeru wierzchołka figury, 
 *                 który ma zostać wczytany.
 *                 Jej wartość musi być mniejsza od wymiarów figury, ale nie 
 *                 mniejsza niż 0
 * \return Zwraca wektor reprezentujący wybrany wierzchołek
 */  
  Vector3D operator[] (unsigned int  lnd) const;

/*!
 * \brief Przeciążenie operatora zapisu '[]' dla klasy Prism
 * 
 * Metoda przeciąża operator '[]' dla klasy Prism , 
 * pozwalający na zapis wpółrzędnych wybranego wierzchołka figury
 * \param[in] lnd - indeks pozwalajacy na wybór numeru wierzchołka, 
 *                  do którego ma zostać zapisana wartość współrzędnych
 *                  Jej wartość musi być mniejsza od wymiarów figury,
 *                  ale nie mniejsza niż 0
 * \return Zwraca referencję do wektora reprezentującego wybrany wierzchołek
 */  
  Vector3D& operator[] (unsigned int lnd);

/*!
 * \brief Metoda translacji figury
 *
 * Metoda przeciąża operator '+=' co pozwala na przesunięcie każdego 
 * wierzchołka figury o ten sam zadany wektor, czyli na dokonanie operacji
 * translacji o wektor
 * \param[in] vect - wektor o jaki ma zostac przesunięty każdy wierzchołek
 *                   figury, musi mieć takie same wymiary jak wektory, które
 *                   reprezentują wierzchołki figury
 */
  void operator += (Vector3D vect);

/*!
 * \brief Metoda obrotu figury
 *
 * Metoda pozwalająca na obrót figury czyli każdego jej wierzchołka o zadaną
 * macierz obrotu i powtórzenie tej operacji zadaną liczbę razy
 * \param[in] matrix - macierz obrotu, czyli macierz, która bedzie przemnożona
 *                     przez każdy wierzchołek figury dając wspolrzędne nowych
 *                     wierzchołków
 * \param[in] times - liczba typu int określająca ilość powtórzeń operacji
 *                    obrotu
 */  
  void Rotate (Matrix3x3 matrix, int times);
  

/*!
 * \brief Metoda obracająca bryłę wokół własnej osi o zadany kąt
 *
 * Metoda obraca bryłę wokoł jej własnej osi o kąt zadany przez użytkownika
 * \param[in] angle - kąt obrotu
 * \return Zwraca wektor określający środek obracanej figury
 */     
  Vector3D Rotate_own_axis(double angle);

/*!
 * \brief Metoda przeciążenia operatora równości
 *
 * Metoda przeciąża operator '=' co pozwala na przypisanie jednej z figur
 * wszystkich współrzędnych drugiej figury. Operacja zabezpieczona przez
 * metode ideksowania nie pozwalającą przekroczyć zakresu indeksów
 * \param[in] prism - graniastosłup, którego współrzędne mają zostać skopiowane
 *                    do wybranego graniastosłupa
 */
  void operator = (Prism prism);

};
