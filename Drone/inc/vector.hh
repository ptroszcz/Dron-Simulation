#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>

#define EPSILON 0.000001

using namespace std;

/*!
 * \file
 * \brief Ten plik zawiera definicję szablonu Vector<>
 *
 * Ten plik zawiera definicję szablonu Vector<> pozwalającego
 * na wybór typu liczbowego wymiarów oraz określenia wymiarów
 */


/*!
 * \brief Szablon definiuje pojecie wektora
 * 
 * Szablon definiuje pojęcie vector<Type,Dimension>, gdzie:\n
 *  - Type oznacza typ liczbowy jakim są wyrażone współrzednę wektora\n
 *  - Dimension określa wymiary wektora
 */
template <typename Type, int Dimension>
class Vector {
  Type elem[Dimension];
  static int existed;     
  static int created;
  public:

 /*!
 * \brief Konstruktor szablonu vector<> ustawiająca domyslne wartości wektora na zera
 * 
 * Konstruktor pozwala na ustawienie wartości wszystkich współrzędnych wektora szablonu
 * vector<> na '0' co pozwala na uniknięcie błędów operowania na niezainicjowanych
 * wartościach
 */
  Vector();

/*!
 * \brief Konstruktor szablonu vector<> ustawiająca zadane 3 wartosci dla wektora co najmniej o
 *        trzech wspolrzednych
 * 
 * Konstruktor szablonu vector<> ustawiająca pierwsze 3 wartosci wspolrzednych na zadane 
 * 3 wartosci dla wektora co najmniej o trzech wspolrzednych. Reszte wspolrzenych ustawia na zero.
 * Jezeli zostanie podany wektor o mniej niz 3 wspolrzednych to wszystkie jego wspolrzedne 
 * zostana ustawione na zera.
 * \param[in] x - pierwsza współrzędna wektora
 * \param[in] y - druga współrzędna wektora
 * \param[in] z - trzecia współrzędna wektora
 */
  Vector(Type x, Type y, Type z);

/*!
 * \brief Destruktor wywoływane przy zniszczenie obiektu klasy vector
 *
 * Destruktor wywołuje się przy zniszczeniu obiektu klasy vector.
 */
  ~Vector() {--existed;}

/*!
 * \brief Konstruktor kopiujący klasy vector
 *
 * Konstruktor kopiujący wywoływany podczas przekazywania wektora np. przy
 * przekazywaniu go do funkcji
 */
  Vector(const Vector &vect) {
    vect.existed++;
    vect.created++;
    for (int i=0;i<Dimension;++i)
      elem[i]=vect[i]; }
    
 /*!
  * \brief Metoda zwracająca ilość stworzonych do tej pory obiektów klasy vector
  *
  * Metoda statyczna która zwraca wartość liczby stworzonych przez całe działanie
  * programu obiektów klasy vector
  */
  static int TakeCreated() {return created;}

/*!
  * \brief Metoda zwracająca ilość istniejących w danym momencie obiektów klasy vector
  *
  * Metoda statyczna, która zwraca wartość liczby istniejących w danym momencie 
  * obiektów klasy vector
  */  
  static int TakeExisted() {return existed;}
  
  
/*!
 * \brief Przeciążenie operatora odczytu '[]' dla szablonu vector<>
 * 
 * Metoda przeciąża operator '[]' dla szablonu vector<> , 
 * pozwalający na odczyt wartości wybranej współrzędnej
 * \param[in] lnd - indeks pozwalajacy na wybór numeru współrzędnej wektora, 
 *                 która ma zostać wczytana np. dla lnd=0 współrzędna x. Jej
 *                 wartość musi być mniejsza od wymiarów wektora, ale nie 
 *                 mniejsza niż 0
 * \return Zwraca wartość wybranej przez lnd współrzędnej
 */
  Type operator [] (unsigned int lnd) const {
    if (lnd>=0 && lnd<Dimension)
    return elem[lnd];
  else {
    cerr<<"Przekroczono zakres indeksów klasy Vector3D"<<endl;
    return 0; }
  }


/*!
 * \brief Przeciążenie operatora zapisu '[]' dla szablonu vector<>
 * 
 * Metoda przeciąża operator '[]' dla szablonu vector<> , 
 * pozwalający na zapis wybranej wartości do wybranej współrzędnej wektora
 * \param[in] lnd - indeks pozwalajacy na wybór numeru współrzędnej wektora, 
 *                  do którego ma zostać zapisana wartość np. dla lnd=0
 *                  do  współrzędna x. Jej wartość musi być mniejsza od 
 *                  wymiarów wektora, ale nie mniejsza niż 0
 * \return Zwraca referencję do wybranej przez lnd współrzędnej
 */
  Type& operator [] (unsigned int lnd) {
    if (lnd>=0 && lnd<Dimension)
    return elem[lnd];
  else {
    cerr<<"Przekroczono zakres indeksów klasy Vector3D"<<endl;
    cerr<<"Dokonana zmiana zastosowana dla pierwszego elementu klasy"<<endl;
    return elem[0];
  }
}

/*!
 * \brief Przeciazenie operatora '+=' dla szablonu vector<>
 *
 * Przeciążenie operatora '+=' dla szablonu vector<> pozwalające na zwiększenie
 * wartości jednego wektora o wartość drugiego wektora
 * \param[in] Vec2 - drugi wektor o jaki zostanie powiekszony pierwszy wektor
 */
  void operator += (Vector<Type,Dimension> Vec2);

/*!
 * \brief Przeciazenie operatora '+=' dla szablonu vector<>
 *
 * Przeciążenie operatora '+=' dla szablonu vector<> pozwalające na zwiększenie
 * wartości jednego wektora o wartość liczby czyli zwiększenie jego każdej
 * współrzędnej o daną liczbę
 * \param[in] number - liczba a jaką mają zostać zwiększone wszystkie 
 *                     współrzędne wektora
 */
  void operator += (Type number);

/*!
 * \brief Przeciazenie operatora *= dla szablonu vector<>
 *
 * Przeciążenie operatora '*=' dla szablonu vector<> pozwalające na pomnożenie
 * wartości każdej jego współrzędnej o zadaną liczbę
 * \param[in] number - liczba, przez którą będzie mnożona każda współrzędna
 *                     wektora
 */
  void operator *= (Type number);

 /*!
 * \brief Przeciążenie operatora mnożenia wektora przez skalar
 * 
 * Przeciąża operator '*' pozwalający mnożyć wektor przez skalar, co powoduje
 * otrzymanie nowego wektora o współrzędnych równych poprzeprzeniemu 
 * pomnożonych przez wybrany skalar
 * \param[in] number - liczba, przez którą będzie mnożona każda współrzędna
 *                     wektora
 * \return Zwraca nowo powstały wektor szablonu vector<>, którego współrzędne
 *         są iloczynem współrzędnych pierwszego wektora oraz skalaru
 */
  Vector<Type,Dimension> operator * (Type number) const;

/*!
 * \brief Przeciazenie operatora '=' dla szablonu vector<>
 *
 * Przeciążenie operatora '=' dla szablonu vector<> pozwalające na przypisanie
 * jednemu wektorowi wszystkich współrzędnych innego wektora o ile oba
 * wektory mają tyle samo współrzędnych
 * \param[in] Vec2 - wektor, którego współrzędne mają zostać przekopiowane
 *                   do współrzędnych drugiego wektora
 */

  void operator = (Vector<Type,Dimension> Vec2);
   
/*!
 * \brief Przeciążenie operatora dodawania wektorów dla szablonu vector<>
 * 
 * Przeciąża operator '+' pozwalający dodać współrzędne dwóch wektorów o tych
 * samych wymiarach co w rezultacie daje nowy wektor, którego współrzędne
 * są sumą wspołrzędnych dwóch danych wektorów
 * \param[in] Vec2 - wektor będący drugim składnikiem dodawania, musi być
 *                   tego samego wymiaru co wektor pierwszy
 * \return Zwraca nowo powstały wektor szablonu vector<>, którego współrzędne
 *         są sumą współrzędnych pierwszego wektora oraz drugiego wektora
 */
  Vector<Type,Dimension> operator + (Vector<Type,Dimension> Vec2) const;

/*!
 * \brief Przeciazenie operatora '-=' dla szablonu vector<>
 *
 * Przeciążenie operatora '+=' dla szablonu vector<> pozwalające na zmniejszenie
 * wartości jednego wektora o wartość drugiego wektora
 * \param[in] Vec2 - drugi wektor o jaki zostanie pomniejszony pierwszy wektor
 */
  void operator -= (Vector<Type,Dimension> Vec2);

/*!
 * \brief Przeciążenie operatora odejmowania wektorów
 * 
 * Przeciąża operator '-' pozwalający odejmować współrzędne dwóch danych
 * wektorów i w rezultacie otrzymać trzeci wektor, którego współrzędne
 * są różnica współrzędnych dwóch danych wektorów
 * \param[in] Vec2 - wektor, którego wpółrzędne stanowią odjemnik działania,
 *                   musi mieć takie same wymiary jak pierwszy wektor
 * \return Zwraca nowo powstały wektor szablonu vector<>, którego współrzędne
 *         są różnicą współrzędnych pierwszego wektora oraz drugiego wektora
 */
  Vector<Type,Dimension> operator - (Vector<Type,Dimension> Vec2) const;

/*!
 * \brief Przeciążenie operatora dzielenia wektora przez liczbę
 * 
 * Przeciąża operator '/' pozwalający dzielić wektor przez liczbę tego samego
 * typu co współrzędne wektora dzielonego
 * \param[in] number - liczba przez którą dzielony jest wektor
 * \return Zwraca nowo powstały wektor szablonu vector<>, którego współrzędne
 *         są ilorazem każdej wpółrzędnej przez podaną liczbę
 */
  Vector<Type,Dimension> operator / (Type number) const;

/*!
 * \brief Metoda szablonu vector<> obliczająca odległość dwóch wektorów od siebie
 * 
 * Metoda oblicza odległość dwóch wektorów od siebie, czyli oblicza w tych samych
 * typach liczbowych co współrzędne wektorów długość najkrótszej prostej łączącej
 * wskazywane przez wektory punkty
 * \param[in] Vec2 - wektor wskazujący drugi punkt do obliczenia długości
 * \return Zwraca liczbę tego samego typu co wpółrzędne równą odległości
 *         dwóch wektorów od siebie
 */
  Type length(Vector<Type,Dimension> Vec2) const;


/*!
 * \brief Metoda obliczajaca wektor przemieszczenia dla wybranego odcinka do przodu o zadaną odleglość
 * 
 * Metoda wylicza wektor kierunkowy dla podanego odcinka danego dwoma wektorami
 * i na tej podstawie oblicza nowy wektor
 * przesunięcia tak, aby odcinek przemieścił się do przodu o wartość odległości
 * zadaną przez użytkownika
 * \param[in] vec - wektor stanowiący koniec odcinka
 * \parami[in] *this - wektor stanowiący początek odcinka
 * \return Zwraca nowo powstały wektor szablonu vector<>, który określe
 *         przesunięcie odcinka w kierunku jego wektora kierunkowego o zadana odleglosc
 */  
  Vector<Type,Dimension> Direct(Vector<Type,Dimension> vec,Type distance) const;


  
};




template <typename Type, int Dimension>
Vector<Type,Dimension>::Vector() {
  this->existed++;
  this->created++;
  for (int lnd=0;lnd<Dimension;++lnd)
    elem[lnd]=0;
  }

template <typename Type, int Dimension>
Vector<Type,Dimension>::Vector(Type x, Type y, Type z) {
  this->existed++;
  this->created++;
  if (Dimension >= 3) {
    elem[0]=x;
    elem[1]=y;
    elem[2]=z;
    for (int lnd=3;lnd<Dimension;++lnd)
      elem[lnd]=0; }
  else {
    cerr<<"Wywolanie kontruktora parametrycznego mozliwe tylko dla wektorow co najmniej o 3 wspolrzednych."<<endl;
    cout<<"Stworzono wektor bez uwzgledniania podanych parametrow"<<endl;
    for (int lnd=0;lnd<Dimension;++lnd)
      elem[lnd]=0;
  }
}
    

/*!
 * \brief Przeciążenie operatora '>>' dla szablonu vector<>
 *
 * Przeciąża operator przesunięcia bitowego w prawo '>>' pozwalający na 
 * zapisanie wspołrzędnych do wektora szablonu vector<> z dowolnego strumienia typu std::istream
 * \param[in] stream - strumień, z którego mają zostać wczytane wartośći współrzędnych
 *                     musi być typu std::istream
 * \param[in] vector - wektor, do którego zostaną zapisane współrzędne odczytane
 *                     ze wskazanego strumienia
 * \return Zwraca referencję do strumienia, z którego były odczytywane wartości
 *         współrzędnych
 */
template <typename Type, int Dimension>
inline
std::istream& operator >> (std::istream &stream, Vector<Type,Dimension> &vector)
{
  for (int i=0;i<Dimension;++i) {
    stream >> vector[i];
    if (stream.fail() )
      return stream; }
  return stream;  
}

/*!
 * \brief Przeciążenie operatora '<<' dla szablonu vector<>
 *
 * Przeciąża operator przesunięcia bitowego w lewo '<<' pozwalający na 
 * wyświetlenie wartości wspołrzędnych wektora szablonu vector<> na dowolny strumień std::ostream
 * \param[in] stream - strumień, na który mają zostać wyświetlone wartośći współrzędnych,
 *                     musi być typu std::ostream
 * \param[in] vector - wektor, którego wartośći współrzędnych zostaną wyświetlone
 * \return Zwraca referencję do strumienia, na który były wyświetlane współrzędne wektora
 */
template <typename Type,int Dimension>
inline
std::ostream& operator << (std::ostream &stream, const Vector<Type,Dimension> &vector)
{
 for (int i=0;i<Dimension;++i)
    stream << setw(16) << fixed << setprecision(10) << vector[i];
  return stream;
}


template <typename Type,int Dimension>
inline
void Vector<Type,Dimension>::operator += (Vector<Type,Dimension> Vec2) {
  for (int i=0;i<Dimension;++i)
    this->elem[i]+=Vec2[i];
}

template <typename Type,int Dimension>
inline
void Vector<Type,Dimension>::operator += (Type number) {
  for (int i=0;i<Dimension;i++)
    this->elem[i]+=number;
}

template <typename Type,int Dimension>
inline
void Vector<Type,Dimension>::operator *= (Type number) {
  for (int i=0;i<Dimension;++i)
    this->elem[i]*=number;
}

template <typename Type,int Dimension>
inline
Vector<Type,Dimension> Vector<Type,Dimension>::operator * (Type number) const {
  Vector<Type,Dimension> result;
  for (int i=0;i<Dimension;++i)
    result[i]=this->elem[i]*number;
  return result;
}

template <typename Type,int Dimension>
inline
void Vector<Type,Dimension>::operator = (Vector<Type,Dimension> Vec2) {
  for (int i=0;i<Dimension;++i)
    this->elem[i]=Vec2[i];
    }

template <typename Type,int Dimension>
inline
Vector<Type,Dimension> Vector<Type,Dimension>::operator + (Vector<Type,Dimension> Vec2) const {
  Vector<Type,Dimension> sum;
  for (int i=0;i<Dimension;++i)
    sum[i]=this->elem[i]+Vec2[i];
  return sum;
}

template <typename Type,int Dimension>
inline
void Vector<Type,Dimension>::operator -= (Vector<Type,Dimension> Vec2) {
  for (int i=0;i<Dimension;++i)
    this->elem[i]-=Vec2[i];
}

template <typename Type,int Dimension>
inline
Vector<Type,Dimension> Vector<Type,Dimension>::operator - (Vector<Type,Dimension> Vec2) const {
  Vector<Type,Dimension> diff;
  for (int i=0;i<Dimension;++i)
    diff[i]=this->elem[i]-Vec2[i];
  return diff;
}

template <typename Type,int Dimension>
inline
Vector<Type,Dimension> Vector<Type,Dimension>::operator / (Type number) const {
  Vector<Type,Dimension> result;
  for (int i=0;i<Dimension;++i)
    result[i]=this->elem[i]/number;
  return result;
}


template <typename Type,int Dimension>
inline
Type Vector<Type,Dimension>::length(Vector<Type,Dimension> Vec2) const {
  Vector<Type,Dimension> help;
  double result=0;
  for (int i=0;i<Dimension;++i)
  help[i]=Vec2[i]-this->elem[i];
  for (int i=0;i<Dimension;++i)
    result=result+(help[i]*help[i]);
  result = sqrt(result);
  return result;
}


template <typename Type,int Dimension>
inline
Vector<Type,Dimension> Vector<Type,Dimension>::Direct(Vector<Type,Dimension> vec,Type distance) const {
  if (Dimension!=3) {
    cerr<<"Metoda dostępna tylko dla wektora o 3 wspólrzednych. Operacja nie zostala wykonana"<<endl;
    return vec; }
  Vector<Type,Dimension> help;
  double angle;
  help=vec-(*this);
  if (help[0]>-EPSILON && help[0]<EPSILON) {
    angle = (M_PI)/2;
    if (help[1]<0)
      angle *=(-1);
  }
  else {
    angle = atan((help[1]/help[0]));
    if (help[0]<0)
      angle+=M_PI; }
  help[0]=cos(angle)*distance;
  help[1]=sin(angle)*distance;
  help[2]=0;
  return help;
}


