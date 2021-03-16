#pragma once


#include <iostream>
#include "vector.hh"
using namespace std;

/*!
 * \file
 * \brief Ten plik zawiera definicję szablonu Matrix<>
 *
 * Ten plik zawiera definicję szablonu Matrix<> pozwalającego
 * na wybór typu liczbowego wymiarów oraz określenia wymiarów macierzy 
 * kwadratowej
 */




/*!
 * \brief Szablon definiuje pojecie macierzy kwadratowej
 * 
 * Szablon definiuje pojęcie Matrix<Type,Dimension>, gdzie:\n
 *  - Type oznacza typ liczbowy jaki przechowuje macierz\n
 *  - Dimension określa wymiary macierzy kwadratowej
 */
template <typename Type, int Dimension>
class Matrix{
  Type Tab[Dimension][Dimension];
  public:

/*!
 * \brief Przeciążenie operatora odczytu '()' dla szablonu Matrix<>
 * 
 * Metoda przeciąża operator '()' dla szablonu Matrix<> , 
 * pozwalający na odczyt wartości z wybranej kolumny i wiersza macierzy
 * \param[in] poems - numer wiersza, z którego odczytujemy wartość. Jego
 *                 wartość musi być mniejsza od wymiarów macierzy, ale nie 
 *                 mniejsza niż 0
 * \param[in] columns - numer kolumny, z której odczytujemy wartość. Jego
 *                 wartość musi być mniejsza od wymiarów macierzy, ale nie 
 *                 mniejsza niż 0
 * \return Zwraca wartość znajdującą się w wybranej kolumnie i wierszu
 */  
  Type operator () (int poems, int columns) const {
     if (poems>=0 && poems<Dimension && columns>=0 && columns <Dimension)
    return Tab[poems][columns];
  else {
    cerr<<"Przekroczono zakres indeksow klasy Matrix2x2"<<endl;
    return 0; }
  }

/*!
 * \brief Przeciążenie operatora zapisu '()' dla szablonu Matrix<>
 * 
 * Metoda przeciąża operator '()' dla szablonu Matrix<> , 
 * pozwalający na zapis wartości do wybranej kolumny i wiersza macierzy
 * \param[in] poems - numer wiersza, do którego zapisujemy wartość. Jego
 *                 wartość musi być mniejsza od wymiarów macierzy, ale nie 
 *                 mniejsza niż 0
 * \param[in] columns - numer kolumny, do której zapisujemy wartość. Jego
 *                 wartość musi być mniejsza od wymiarów macierzy, ale nie 
 *                 mniejsza niż 0
 * \return Zwraca referencję do wybranej komórki macierzy
 */    
  Type& operator () (int poems, int columns) {
    if (poems>=0 && poems<Dimension && columns>=0 && columns <Dimension)
    return Tab[poems][columns];
  else {
    cerr<<"Przekroczono zakres indeksow klasy Matrix2x2"<<endl;
    cerr<<"Dokonana zmiana zastosowana dla pierwszego elementu klasy"<<endl;
    return Tab[0][0]; }
}

/*!
 * \brief Metoda szablonu Matrix<> tworząca macierz obrotu dla 2 wymiarów
 * 
 * Metoda szablonu Matrix<> tworząca macierz obrotu dla 2 wymiarów, czyli
 * tworząca taką macierz, która po przemnożeniu przez obiekt dwuwymiarowy
 * obróci go o zadany kąt
 * \param[in] angle - kąt o jaki ma zostać obrócony wektor, musi być
 *                    wyrażony w radianach
 */
  void Create2D (double angle);



/*!
 * \brief Przeciazenie mnozenia macierzy przez wektor
 *
 * Przeciąża operator '*' dla mnożenia macierzy przez wektor, co pozwala na
 * obliczenie iloczynu macierzy i wektora
 * \param[in] vect - wektor ktory bedzie mnozyl macierz, jego wymiary
 *                    muszą być takie same jak macierzy
 * \return  Zwraca wektor bedacy wynikiem mnozenia macierzy przez wektor
 */    
  Vector<Type,Dimension> operator * (Vector<Type,Dimension> vect) const;

/*!
 * \brief Metoda inicjująca macierz
 *
 * Metoda, która wstawia w każdą komórkę macierzy wartość '0'
 */  
  void Init();

/*!
 * \brief Przeciążenie operatora '=' dla szablonu Matrix<>
 *
 * Przeciążenie operatora '=' dla szablonu Matrix<> pozwalające na przypisanie
 * jednej macierzy wartości wszystkich komórek jak w drugiej macierzy
 * \param[in] matrix - macierz, której wartości komórek  mają zostać
 *                     przekopiowane do komórek drugiej macierzy z zachowaniem
 *                     zgodności wierszy i kolumn, macierz musi mieć takie
 *                     same wymiary jak pierwsza macierz
 */  
  void operator = (Matrix<Type,Dimension> matrix);

/*!
 * \brief Przeciazenie mnozenia macierzy przez macierz
 *
 * Przeciąża operator '*' dla mnożenia macierzy przez macierz, co pozwala
 * na uzyskanie nowej macierzy będącej wynikiem iloczynu dwóch zadanych
 * \param[in] matrix - macierz, przez którą będzie mnożona pierwsza z macierzy
 *                     musi być tych sanych wymiarów co macierz mnożona
 * \return  Zwraca macierz będąca wynikiem iloczynu dwóch zadanych macierzy
 */      
  Matrix<Type,Dimension> operator * (Matrix<Type,Dimension> matrix) const;

/*!
 * \brief Metoda szablonu Matrix<> tworząca macierz obrotu dla 3 wymiarów
 * 
 * Metoda szablonu Matrix<> tworząca macierz obrotu dla 3 wymiarów, czyli
 * tworząca taką macierz, która po przemnożeniu przez obiekt trójwymiarowy
 * obróci go o zadany kąt wokół wybranej osi obrotu
 * \param[in] angle - kąt o jaki ma zostać obrócony wektor, musi być
 *                    wyrażony w radianach
 * \param[in] axis - oś względem, której ma zostać dokonany obrót, musi byc
 *                   wyrażona jako 'x', 'y' lub 'z'
 */  
  void Create3D(char axis, double angle);
   
};




/*!
 * \brief Przeciążenie operatora '<<' dla szablonu Matrix<>
 *
 * Przeciąża operator przesunięcia bitowego w lewo '<<' pozwalający na 
 * wyświetlenie wartości wszystkich komórek macierzy nad dowolny strumień
 * typu std::ostream
 * \param[in] stream - strumień, na który mają zostać wyświetlone
 *                     wartośći komórek macierzy musi być typu std::ostream
 * \param[in] matrix - macierz, której wartośći komórek zostaną wyświetlone
 * \return Zwraca referencję do strumienia, na który były wyświetlane
 *         wartości komórek macierzy
 */
template <typename Type,int Dimension>
inline
std::ostream& operator << (std::ostream &stream, const Matrix<Type,Dimension> &matrix) {
  for (int i=0;i<Dimension;++i) {
    stream <<endl;
    for (int j=0;j<Dimension;++j) {
      stream << setw(16) << fixed << setprecision(10) << matrix(i,j);}
  }
  return stream;  
}


template <typename Type,int Dimension>
inline
Vector<Type,Dimension> Matrix<Type,Dimension>::operator * (Vector<Type,Dimension> vect) const {
  Vector<Type,Dimension> result;
  for (int i=0;i<Dimension;++i) {
    for (int j=0;j<Dimension;++j) {
      result[i]+=(this->Tab[i][j]*vect[j]); 
    }
  }
  return result;
}




template <typename Type,int Dimension>
inline
void Matrix<Type,Dimension>::Create2D (double angle) {
  if (Dimension==2){
    for (int i=0;i<Dimension;++i) {
      for (int j=0;j<Dimension;++j)
	this->Tab[i][j]=0; }
    this->Tab[0][0]=cos(angle);
    this->Tab[0][1]=-sin(angle);
    this->Tab[1][0]=sin(angle);
    this->Tab[1][1]=cos(angle); }
  else {
    cerr << "Nie mozna stworzyc macierzy obrotu 2D";
    cerr << "dla macierzy innej niz 2x2"<<endl; }
}

template <typename Type,int Dimension>
inline
void Matrix<Type,Dimension>::Init() {
  for (int i=0;i<Dimension;++i) {
    for (int j=0;j<Dimension;++j)
      this->Tab[i][j]=0;
  }
}

template <typename Type,int Dimension>
inline
void Matrix<Type,Dimension>::operator = (Matrix<Type,Dimension> matrix) {
  for (int i=0;i<Dimension;++i) {
    for (int j=0;j<Dimension;++j)
      this->Tab[i][j]=matrix(i,j); }
}



template <typename Type,int Dimension>
inline
Matrix<Type,Dimension> Matrix<Type,Dimension>::operator * (Matrix<Type,Dimension> matrix) const {
  Matrix<Type,Dimension> result;
  result.Init();
  for (int i=0;i<Dimension;++i) {
    for (int j=0;j<Dimension;++j) {
      for (int k=0;k<Dimension;++k) 
	result(i,j)+=(this->Tab[i][k]*matrix(k,j));
    }
  }
  return result;
}

template <typename Type,int Dimension>
inline
void Matrix<Type,Dimension>::Create3D(char axis, double angle) {
  if (Dimension==3) {
    (*this).Init();
    switch(axis) {
    case 'x':
      this->Tab[0][0]=1;
      this->Tab[1][1]=cos(angle);
      this->Tab[1][2]=-sin(angle);
      this->Tab[2][1]=sin(angle);
      this->Tab[2][2]=cos(angle);
      break;
    case 'y':
      this->Tab[1][1]=1;
      this->Tab[0][0]=cos(angle);
      this->Tab[2][0]=-sin(angle);
      this->Tab[0][2]=sin(angle);
      this->Tab[2][2]=cos(angle);
      break;
    case 'z':
      this->Tab[2][2]=1;
      this->Tab[0][0]=cos(angle);
      this->Tab[0][1]=-sin(angle);
      this->Tab[1][0]=sin(angle);
      this->Tab[1][1]=cos(angle);
      break;
    default:
      cerr<<"Wybrano niepoprawna os obrotu. Operacja nie zostala wykonana."<<endl;
    }
  }
  else
    cerr<<"Nie mozna stworzyc macierzy obrotu 3D dla macierzy innej niz 3x3"<<endl;
}
    
