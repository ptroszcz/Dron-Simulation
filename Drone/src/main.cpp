#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "vector3D.hh"
#include "matrix3x3.hh"
#include "gnuplot_link.hh"
#include "Scene.hh"
#include "Prism.hh"
#include "Body.hh"
#include "Rotor.hh"
#include "Dron.hh"
#include "CuboidObstacle.hh"
#include "Factory.hh"

using namespace std;

#define FPS 30



/*!
 * \file
 * \brief To jest główny plik programu
 *
 * To jest główny plik programu, zajmujący się obsługą użytkownika oraz 
 * zawierający funkcję main.
 */


/*!
 * \mainpage Fabryka obiektów
 *
 * Program jednego drona i dwie przeszkody na początku programu. Pozwala na
 * dodawanie kolejnych dronów oraz przeszkód, z warunkiem że nie można stworzyć
 * obiektu takiego, który zablokował by możliwośc ruchu dowolnego z dronów.
 * Program pozwala na wybór drona do sterowania oraz sterowanie jego ruchem.
 * Program pozwala także usuwać aktualnie wybranego drona jednak tylko jeśli
 * nie jest to jedyny dron.
 *
 * \section label Najważniejsze cechy
 *
 * Program pozwala na operacje:
 * - dodawania nowych dronów w wybranym miejscu
 * - dodawania nowych prostopadłościennych przeszkodó w wybranym miejscu
 *   oraz o zadanych rozmiarach
 * - usuwanie aktualnie wybranego drona, jendak liczba dronów nie może być
 *   mniejsza niż 1 
 * - ruchu dronów o zadaną odległość oraz o zadany kąt unoszenia('+')
 *    lub opadania('-')
 * - obrót dronów wokół własnej osi o zadany kąt
 * - program zlicza także ilośc istniejących jak i stworzonych przez całe
 * działanie programu obiektów klasy Vector3D
 * - program zlicza także ilośc istniejących jak i stworzonych przez całe
 * działanie programu obiektów klasy SceneObject
 * - wizualizacje działania dronów zapewnia program gnuplot 
 * - zarówno ruch jak i obrót drona są animowane wraz z animacją obrotu
 * wirników
 * - wybór jednego z trzech dronów do przemieszczania w dowolnym momencie
 * programu, w którym wszystkie drony nie poruszają się
 * - wykrywanie kolizji dronów ze soba jak i drona z przeszkodą oraz
 * zatrzymywanie poruszającego się drona w razie wystąpienie tej też kolizji
 */

const int kEdgeSize = 50;


template<>
int Vector3D::existed=0;

template<>
int Vector3D::created=0;


int SceneObject::existed=0;
int SceneObject::created=0;




/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] stream - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] rotor - wirnik klasy Rotor, którego współrzędne mają
 *                    zostać zapisane do wybranego strumienia
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */

void WriteToStreamExample(ostream& stream, Rotor rotor) {
  Vector3D center1, center2, help1, help2;
  help1=rotor[3];
  help2=rotor[0];
  center1[0]=(help1[0]+help2[0])/2;
  center1[1]=(help1[1]+help2[1])/2;
  center1[2]=(help1[2]+help2[2])/2;
  center2=center1;
  center2[2]+=50;

  for (int i=0;i<6;++i) {
    stream << center1 <<endl;
    stream << rotor[i]<<endl;
    stream << rotor[i+6]<<endl;
    stream << center2 <<endl;
    stream << endl; }
  stream << center1 <<endl;
    stream << rotor[0]<<endl;
    stream << rotor[6]<<endl;
    stream << center2 <<endl;
    stream <<endl;
}
  

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] stream - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Korp - korpus klasy Body, którego współrzędne mają
 *                   zostać zapisane do wybranego strumienia
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void WriteToStreamExample(ostream& stream, Body Korp)
{
  

  Vector3D V1,V2,V3,V4,V5,V6,V7,V8;
  V1=Korp[0];
  V2=Korp[1];
  V3=Korp[2];
  V4=Korp[3];
  V5=Korp[4];
  V6=Korp[5];
  V7=Korp[6];
  V8=Korp[7];

  stream << setw(16) << fixed << setprecision(10) << V1[0]
         << setw(16) << fixed << setprecision(10) << V1[1]
         << setw(16) << fixed << setprecision(10) << V1[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V2[0]
         << setw(16) << fixed << setprecision(10) << V2[1]
         << setw(16) << fixed << setprecision(10) << V2[2]
         << endl;

  stream << endl;

  stream << setw(16) << fixed << setprecision(10) << V4[0]
         << setw(16) << fixed << setprecision(10) << V4[1]
         << setw(16) << fixed << setprecision(10) << V4[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V3[0]
         << setw(16) << fixed << setprecision(10) << V3[1]
         << setw(16) << fixed << setprecision(10) << V3[2]
         << endl;

  stream << endl;

  stream << setw(16) << fixed << setprecision(10) << V8[0]
         << setw(16) << fixed << setprecision(10) << V8[1]
         << setw(16) << fixed << setprecision(10) << V8[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V7[0]
         << setw(16) << fixed << setprecision(10) << V7[1]
         << setw(16) << fixed << setprecision(10) << V7[2]
         << endl;

  stream << endl;

  stream << setw(16) << fixed << setprecision(10) << V5[0]
         << setw(16) << fixed << setprecision(10) << V5[1]
         << setw(16) << fixed << setprecision(10) << V5[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V6[0]
         << setw(16) << fixed << setprecision(10) << V6[1]
         << setw(16) << fixed << setprecision(10) << V6[2]
         << endl;

  stream << endl;
 
  stream << setw(16) << fixed << setprecision(10) << V1[0]
         << setw(16) << fixed << setprecision(10) << V1[1]
         << setw(16) << fixed << setprecision(10) << V1[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V2[0]
         << setw(16) << fixed << setprecision(10) << V2[1]
         << setw(16) << fixed << setprecision(10) << V2[2]
         << endl;
                             // Jeszcze raz zapisujemy pierwsze dwa wierzcholki,
                             // aby gnuplot narysowal zamkniętą powierzchnie.
}



/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] stream - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 *\param[in] CubObst - przeszkoda klasy CuboidObstacle, której współrzędne mają
 *                   zostać zapisane do wybranego strumienia
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */

void WriteToStreamExample(ostream& stream, CuboidObstacle CubObst)
{
  

  Vector3D V1,V2,V3,V4,V5,V6,V7,V8;
  V1=CubObst[0];
  V2=CubObst[1];
  V3=CubObst[2];
  V4=CubObst[3];
  V5=CubObst[4];
  V6=CubObst[5];
  V7=CubObst[6];
  V8=CubObst[7];

  stream << setw(16) << fixed << setprecision(10) << V1[0]
         << setw(16) << fixed << setprecision(10) << V1[1]
         << setw(16) << fixed << setprecision(10) << V1[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V2[0]
         << setw(16) << fixed << setprecision(10) << V2[1]
         << setw(16) << fixed << setprecision(10) << V2[2]
         << endl;

  stream << endl;

  stream << setw(16) << fixed << setprecision(10) << V4[0]
         << setw(16) << fixed << setprecision(10) << V4[1]
         << setw(16) << fixed << setprecision(10) << V4[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V3[0]
         << setw(16) << fixed << setprecision(10) << V3[1]
         << setw(16) << fixed << setprecision(10) << V3[2]
         << endl;

  stream << endl;

  stream << setw(16) << fixed << setprecision(10) << V8[0]
         << setw(16) << fixed << setprecision(10) << V8[1]
         << setw(16) << fixed << setprecision(10) << V8[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V7[0]
         << setw(16) << fixed << setprecision(10) << V7[1]
         << setw(16) << fixed << setprecision(10) << V7[2]
         << endl;

  stream << endl;

  stream << setw(16) << fixed << setprecision(10) << V5[0]
         << setw(16) << fixed << setprecision(10) << V5[1]
         << setw(16) << fixed << setprecision(10) << V5[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V6[0]
         << setw(16) << fixed << setprecision(10) << V6[1]
         << setw(16) << fixed << setprecision(10) << V6[2]
         << endl;

  stream << endl;
 
  stream << setw(16) << fixed << setprecision(10) << V1[0]
         << setw(16) << fixed << setprecision(10) << V1[1]
         << setw(16) << fixed << setprecision(10) << V1[2]
         << endl;

  stream << setw(16) << fixed << setprecision(10) << V2[0]
         << setw(16) << fixed << setprecision(10) << V2[1]
         << setw(16) << fixed << setprecision(10) << V2[2]
         << endl;
                             // Jeszcze raz zapisujemy pierwsze dwa wierzcholki,
                             // aby gnuplot narysowal zamkniętą powierzchnie.
}

bool WriteToFileExample(const char  *filename, Body Korp)
{
  ofstream  file_stream;

  file_stream.open(filename);
  if (!file_stream.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  WriteToStreamExample(file_stream,Korp);

  file_stream.close();
  return !file_stream.fail();
}

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] filename - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] rotor - wirnik klasy Rotor, którego współrzędne mają
 *                    zostać zapisane do wybranego pliku
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool WriteToFileExample(const char  *filename, Rotor rotor)
{
  ofstream  file_stream;

  file_stream.open(filename);
  if (!file_stream.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  WriteToStreamExample(file_stream,rotor);

  file_stream.close();
  return !file_stream.fail();
}



/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] filename - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 *\param[in] CubObst - przeszkoda klasy CuboidObstacle, której współrzędne mają
 *                   zostać zapisane do wybranego pliku
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool WriteToFileExample(const char  *filename, CuboidObstacle CubObst)
{
  ofstream  file_stream;

  file_stream.open(filename);
  if (!file_stream.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  WriteToStreamExample(file_stream,CubObst);

  file_stream.close();
  return !file_stream.fail();
}


/*!
 * \brief Funkcja zapisu współrzędnych drona do plików
 *
 * Zapisuje współrzędne drona do 5 osobnych plików. W każdym pliku jedna
 * figura składająca się na drona.
 * \param[in] dron - dron, którego współrzędne mają zostać zapisane do pliku
 * \return Zwraca: - 1,gdy operacja zapisu do dowolnego z pięciu plików
 *                   nie powiodła się
 *                 - 0, gdy operacja się w pełni powiodła
 */
int Save_Dron_To_File(Dron dron) {
  std::string _name;
  _name=(dron.TakeName()+"body");
  if (!WriteToFileExample(_name.c_str(),dron.body)) return 1;
  _name=(dron.TakeName()+"rotor1");
  if (!WriteToFileExample(_name.c_str(),dron[0])) return 1;
  _name=(dron.TakeName()+"rotor2");
  if (!WriteToFileExample(_name.c_str(),dron[1])) return 1;
  _name=(dron.TakeName()+"rotor3");
  if (!WriteToFileExample(_name.c_str(),dron[2])) return 1;
  _name=(dron.TakeName()+"rotor4");
  if (!WriteToFileExample(_name.c_str(),dron[3])) return 1;
  return 0;
}



/*!
 * \brief Funkcja wyświetlania treści menu
 *
 * Funkcja wyswietla na standardowy strumień wyjściowy treść menu, jednak nie
 * jest odpowiedzialna za obługiwanie wyświetlanych opcji
 */
void Display_Menu() {
  cout<<endl;
  cout<<"D - dodaj drona"<<endl;
  cout<<"P - dodaj przeszkode"<<endl;
  cout<<"U - usun wyselekcjowanego drona"<<endl;
  cout<<"j - przesuniecie bryly do przodu o zadany kat wznoszenia i zadana odleglosc"<<endl;
  cout<<"o - obrot bryly wokol wlasnej osi o zadany kat"<<endl;
  cout<<"s - selekcja drona"<<endl;
  cout<<"m - wyswietl menu"<<endl;
  cout<<"k - koniec dzialania programu"<<endl;
  
  cout<<endl;
}

/*!
 * \brief Główna funkcja programu
 *
 * Główna funkcja programu definiująca figurę, na której użytkownik bedzie
 * wykonywał operacje oraz zajmująca się odczytywaniem wprowadzanych danych
 * przez użytkownika, interpretacją ich oraz wykonaniem wybranych przez 
 * użytkownika działań
 */
int main() { 
{

  Factory::CreateFactory();

  shared_ptr<SceneObject> wScObj;
  Vector3D Trans, help;
  double angle,angle2;
  int Droncount=1, Obstaclecount=1;
  std::string name;
  double distance=0;
  unsigned int chosen_dron=0;
  int kolizja=0;
  char choice='m', choice2='n';
  Scene scene;
  PzG::LaczeDoGNUPlota  link;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   
   //  Ustawienie trybu rysowania 3D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy x,y,z.
   //
  link.SetDrawingMode(PzG::DM_3D);

   // Ustawienie zakresow poszczegolnych osi
  link.SetRangeY(-400,600);
  link.SetRangeX(-400,400);
  link.SetRangeZ(-300,600);

  Vector3D V1,V2;

  V1[0]=50;
  V1[1]=50;
  V1[2]=0;
  Factory::UseFactory()->ChangeCenter(V1);
  name=("Dron_"+to_string(Droncount));
  Factory::UseFactory()->ChangeName(name.c_str());
  wScObj = Factory::UseFactory()->CreateObject(OT_Dron);
  name+="body";
  link.AddFilename(name.c_str(),8);
  name=("Dron_"+to_string(Droncount));
  name+="rotor1";
  link.AddFilename(name.c_str(),3);
  name=("Dron_"+to_string(Droncount));
  name+="rotor2";
  link.AddFilename(name.c_str(),4);
  name=("Dron_"+to_string(Droncount));
  name+="rotor3";
  link.AddFilename(name.c_str(),3);
  name=("Dron_"+to_string(Droncount));
  name+="rotor4";
  link.AddFilename(name.c_str(),4);
  (scene.ScObj).push_back(wScObj);
  (scene.Robot).push_back(static_pointer_cast<Dron>(wScObj));
  Droncount++;

  V1[0]=-200;
  V1[1]=-100;
  V1[2]=-300;
  V2[0]=200;
  V2[1]=200;
  V2[2]=500;
  Factory::UseFactory()->ChangeCenter(V1);
  Factory::UseFactory()->ChangeDimensions(V2);
  name="Obstacle_";
  name+=(to_string(Obstaclecount));
  Factory::UseFactory()->ChangeName(name.c_str());
  wScObj = Factory::UseFactory()->CreateObject(OT_CuboidObstacle);
  link.AddFilename(name.c_str());
  (scene.ScObj).push_back(wScObj);
  if (!WriteToFileExample(name.c_str(),(*(static_pointer_cast<CuboidObstacle>(wScObj))))) return 1;
  Obstaclecount++;

  V1[0]=300;
  V1[1]=250;
  V1[2]=-300;
  V2[0]=200;
  V2[1]=100;
  V2[2]=600;
  Factory::UseFactory()->ChangeCenter(V1);
  Factory::UseFactory()->ChangeDimensions(V2);
  name="Obstacle_";
  name+=(to_string(Obstaclecount));
  Factory::UseFactory()->ChangeName(name.c_str());
  wScObj = Factory::UseFactory()->CreateObject(OT_CuboidObstacle);
  link.AddFilename(name.c_str());
  (scene.ScObj).push_back(wScObj);
  if (!WriteToFileExample(name.c_str(),(*(static_pointer_cast<CuboidObstacle>(wScObj))))) return 1;
  Obstaclecount++;
 
  std::list<std::shared_ptr<Dron>>::iterator iter = (scene.Robot).begin();
  std::list<std::shared_ptr<Dron>>::iterator iter_help = (scene.Robot).begin();
  std::list<std::shared_ptr<SceneObject>>::iterator iterScObj = (scene.ScObj).begin();
  std::list<std::shared_ptr<SceneObject>>::iterator iterScObj2 = (scene.ScObj).begin();

  Save_Dron_To_File(**iter);
  iter = (scene.Robot).begin();
  for(unsigned int i=0;i<(scene.ScObj).size();++i) {
    if ((*iter)==(*iterScObj2))
      break;
    ++iterScObj2;}
  link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  Display_Menu();
  while (choice!='k') {
    cout<<endl;
    cout<<"Laczna ilosc stworzonych obiektow klasy SceneObject: "<<SceneObject::TakeCreated()<<endl;
    cout<<"      Ilosc istniejacych obiektow klasy SceneObject: "<<SceneObject::TakeExisted()<<endl;
    cout<<endl;
    cout<<"Laczna ilosc stworzonych obiektow klasy Vector3D: "<<Vector3D::TakeCreated()<<endl;
    cout<<"      Ilosc istniejacych obiektow klasy Vector3D: "<<Vector3D::TakeExisted()<<endl;
    cout<<endl;
    cout<<"Aktualnie wyselekcjonowanym dronem jest:"<<endl;
    cout<<(**iter);
    cout<<endl;
    cout<<" Twoj wybor? (m-menu) > ";
    cin >> choice;
    cin.ignore(10000,'\n'); /*pobierz tylko jeden znak, reszte zignoruj*/
    iter_help = (scene.Robot).begin();
    switch(choice) {
    case 'm':
      Display_Menu();
      break;
    case 'k':
       Factory::DestroyFactory();
      cout<<endl;
      cout<<"Koniec dzialania programu"<<endl;
      break;
    case 'D': {
      cout<<endl;
      cout << "Podaj docelowe wspolrzedne drona: x y z > ";
      cin >> V1;
      if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	cerr <<" Blad formatu wspolrzednych drona";
	cout <<" Operacja nie zostala wykonana"<<endl;
	cout <<endl;
	cin.clear();
	cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
      else{
	 Factory::UseFactory()->ChangeCenter(V1);
	 name="Dron_";
	 name+=(to_string(Droncount));
	 Factory::UseFactory()->ChangeName(name.c_str());
	 wScObj = Factory::UseFactory()->CreateObject(OT_Dron);
	 iterScObj = (scene.ScObj).begin();
	 kolizja=0;
	 for (unsigned int i=0;i<(scene.ScObj).size();++i) {
	   if ((**iterScObj).IsCollision(*wScObj)) {
	     cout<<"Wykryta zostala kolizja. Nie mozna utworzyc drona w wybranym miejscu."<<endl;
	     kolizja=1;
	     break;
	    }
	    ++iterScObj; 
	 }
	 if (kolizja==1) 
	   wScObj=(scene.ScObj).front();
	 else {
	   name+="body";
	   link.AddFilename(name.c_str(),8);
	   name=("Dron_"+to_string(Droncount));
	   name+="rotor1";
	   link.AddFilename(name.c_str(),3);
	   name=("Dron_"+to_string(Droncount));
	   name+="rotor2";
	   link.AddFilename(name.c_str(),4);
	   name=("Dron_"+to_string(Droncount));
	   name+="rotor3";
	   link.AddFilename(name.c_str(),3);
	   name=("Dron_"+to_string(Droncount));
	   name+="rotor4";
	   link.AddFilename(name.c_str(),4);
	   (scene.ScObj).push_back(wScObj);
	   (scene.Robot).push_back(static_pointer_cast<Dron>(wScObj));
	   Save_Dron_To_File(*(static_pointer_cast<Dron>(wScObj)));
	   link.Draw();
	   Droncount++; }
      }
      break;
    }
    case 'P': {
      cout<<endl;
      cout << "Podaj docelowe wspolrzedne srodka przeszkody: x y z > ";
      cin >> V1;
      if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	cerr <<" Blad formatu wspolrzednych przeszkody";
	cout <<" Operacja nie zostala wykonana"<<endl;
	cout <<endl;
	cin.clear();
	cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
      else{
	cout<<endl;
	cout<< "Podaj wymiary przeszkody wzdluz osi OX, OY, OZ: "<<endl;
	cout<<"wymiar_x wymiar_y wymiar_z > ";
	cin >> V2;
	if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	  cerr <<" Blad formatu wspolrzednych przeszkody";
	  cout <<" Operacja nie zostala wykonana"<<endl;
	  cout <<endl;
	  cin.clear();
	  cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
	else{
	  Factory::UseFactory()->ChangeCenter(V1);
	  Factory::UseFactory()->ChangeDimensions(V2);
	  name="Obstacle_";
	  name+=(to_string(Obstaclecount));
	  Factory::UseFactory()->ChangeName(name.c_str());
	  wScObj = Factory::UseFactory()->CreateObject(OT_CuboidObstacle);
	  iterScObj = (scene.ScObj).begin();
	  kolizja=0;
	  for (unsigned int i=0;i<(scene.ScObj).size();++i) {
	    if ((**iterScObj).ID() == 'D') {
	      if ((*wScObj).IsCollision(**iterScObj)) {
	      cout<<"Wykryta zostala kolizja z dronem. Nie mozna utworzyc przeszkody w wybranym miejscu."<<endl;
	      kolizja=1;
	      break;
	      }
	    }
	    ++iterScObj; 
	 }
	  if (kolizja == 1)
	    wScObj=(scene.ScObj).front();
	  else {
	    link.AddFilename(name.c_str());
	    (scene.ScObj).push_back(wScObj);
	    if (!WriteToFileExample(name.c_str(),(*(static_pointer_cast<CuboidObstacle>(wScObj))))) return 1;
	    link.Draw();
	    Obstaclecount++;}
	}
      }
      break;
    }
    case 'U': {
      if ((scene.Robot).size()<=1) 
	cout<<"Nie mozna usunac drona, gdy pozostal tylko jeden"<<endl;
      else {
	cout<<endl;
	cout<<"Aktualnie wyselekcjonowanym dronem jest:"<<endl;
	cout<<(**iter);
	cout<<endl;
	cout<<"Czy napewno usunąć tego drona? (t/n)> ";
	cin>>choice2;
	if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	  cerr <<" Blad formatu odpowiedzi";
	  cout <<" Operacja nie zostala wykonana"<<endl;
	  cout <<endl;
	  cin.clear();
	  cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
	else{
	  if (choice2=='t') {
	    iter_help=(scene.Robot).end();
	    --iter_help;
	    name=(**iter_help).TakeName()+"body";
	    link.DeleteFileName(name.c_str());
	    name=(**iter_help).TakeName()+"rotor1";
	    link.DeleteFileName(name.c_str());
	    name=(**iter_help).TakeName()+"rotor2";
	    link.DeleteFileName(name.c_str());
	    name=(**iter_help).TakeName()+"rotor3";
	    link.DeleteFileName(name.c_str());
	    name=(**iter_help).TakeName()+"rotor4";
	    link.DeleteFileName(name.c_str());
	    (scene.Robot).remove(*iter);
	    (scene.ScObj).remove(*iterScObj2);
	    wScObj=(scene.ScObj).front();
	    iter = (scene.Robot).begin();
	    iter_help = (scene.Robot).begin();
	    iterScObj = (scene.ScObj).begin();
	    iterScObj2 = (scene.ScObj).begin();
	    for(unsigned int i=0;i<(scene.ScObj).size();++i) {
	      if ((*iter)==(*iterScObj2))
		break;
	      ++iterScObj2;}
	    for (unsigned int i=1;i<=(scene.Robot).size();++i) {
	      name=("Dron_"+to_string(i));
	      (**iter).ChangeName(name);
	      Save_Dron_To_File(**iter);
	      ++iter; }
	    iter = (scene.Robot).begin();
	    Droncount--;
	    link.Draw();
	    cout<<endl;
	    cout<<"Drona usunieto."<<endl; }
	  else if (choice2=='n') {
	    cout<<endl;
	    cout<<"Zrezygnowano z usuniecia Drona"<<endl; }
	  else {
	    cout<<endl;
	    cout<<"Wpisano niepoprawna decyzje. Operacja usuniecia uznana za odrzucona"<<endl;}
	}
      }
      break;
    }
    case 'j':
      cout << "Podaj dlugosc drogi przelotu"<<endl;
      cin >> distance;
      if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	cerr <<" Blad formatu dlugosci drogi przelotu.";
	cout <<" Operacja nie zostala wykonana"<<endl;
	cout <<endl;
	cin.clear();
	cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
      else{
	cout<<"Podaj kat wznoszenia(+) lub opadania(-) w stopniach"<<endl;
	cin >> angle;
	if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	  cerr <<" Blad formatu kata w stopniach.";
	  cout <<" Operacja nie zostala wykonana"<<endl;
	  cout <<endl;
	  cin.clear();
	  cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
      else{
	cin.ignore(10000,'\n');
	angle=((angle*M_PI)/180);
	Trans=((*iter)->body).Move(distance,angle);
	help=Trans/FPS;
	kolizja=0;
	for (int i=0;i<FPS;++i) {
	  iterScObj = (scene.ScObj).begin();
	  (**iter).Move_Dron(help);
	  ((**iter)[0]).Rotate_own_axis(M_PI/5);
	  ((**iter)[2]).Rotate_own_axis(M_PI/5);
	  ((**iter)[1]).Rotate_own_axis((9*M_PI)/5);
	  ((**iter)[3]).Rotate_own_axis((9*M_PI)/5);
	  for (unsigned int i=0;i<(scene.ScObj).size();++i) {
	    if ((*iterScObj)!=(*iterScObj2)) {
	      if ((**iterScObj).IsCollision(**iterScObj2)) {
		cout<<"Wykryta zostala kolizja. Ruch zostal zatrzymany."<<endl;
		cout<<endl;
		kolizja=1;
		break; }
	    }
	    ++iterScObj; 
	    }
	  if (kolizja==1) {
	    (**iter).Move_Dron(help*(-1));
	    break;}
	  Save_Dron_To_File(**iter);
	  link.Draw();
	  usleep(200000);
	}
      }
      }
      Save_Dron_To_File(**iter);
      link.Draw();
      break;
    case 'o':
      cout <<"Podaj kat obrotu bryly wokol wlasnej osi w stopniach"<<endl;
      cin >> angle;
      if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	cerr <<" Blad formatu kata w stopniach.";
	cout <<" Operacja nie zostala wykonana"<<endl;
	cout <<endl;
	cin.clear();
	cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
      else{
	cin.ignore(10000,'\n');
	angle=((angle*M_PI)/180);
	angle2=angle/30;
	for (int i=0;i<FPS;++i) {
	  (**iter).Rotate_Dron(angle2);
	  ((**iter)[0]).Rotate_own_axis(M_PI/5);
	  ((**iter)[2]).Rotate_own_axis(M_PI/5);
	  ((**iter)[1]).Rotate_own_axis((9*M_PI)/5);
	  ((**iter)[3]).Rotate_own_axis((9*M_PI)/5);
	  Save_Dron_To_File(**iter);
	  link.Draw();
	  usleep(150000);
	}
      }
      break;
    case 's':
      cout<<"Aktualnie wyselekcjonowanym dronem jest:"<<endl;
      cout<<(**iter);
      cout<<endl;
      cout<<"       0. - zaniechaj zmiany selekcji"<<endl;
      cout<<endl;
      iter_help = (scene.Robot).begin();
      cout<<(**iter_help);
      for (unsigned int i=1;i<(scene.Robot).size();++i)
        cout<<(**(++iter_help));
      cout<<endl;
      cout<<"Podaj numer drona, dla ktorego maja byc wykonywane operacje sterowania"<<endl;
      cout<<endl;
      cout<<"Wprowadz numer drona lub 0 > ";
      cin >> chosen_dron;
      if (cin.fail() ) {    /*sprawdzenie czy udalo sie wczytac poprawnie*/
	cerr <<" Blad formatu numeru drona.";
	cout <<" Operacja nie zostala wykonana."<<endl;
	cout <<endl;
	cin.clear();
	cin.ignore(10000,'\n'); } /*pomin znaki az do znaku konca lini*/
      else{
	cin.ignore(10000,'\n');
	if (chosen_dron < 0 || chosen_dron>(scene.Robot).size() ) {
	  cerr<<" Wybrano niestniejącego drona.";
	  cout <<" Operacja nie została wykonana."<<endl;}
	else if (chosen_dron == 0)
	  break;
	else {
	  iter = (scene.Robot).begin();
	  for(unsigned int i=1;i<chosen_dron;++i)
	    iter++;
	}
      }
      chosen_dron=0;
      iterScObj2 = (scene.ScObj).begin();
      for(unsigned int i=0;i<(scene.ScObj).size();++i) {
	if ((*iter)==(*iterScObj2))
	  break;
	++iterScObj2;}
      break;      
    default:
      cout<<"Niepoprawny wybor opcji. Sprobuj ponownie."<<endl;
      break;
    }
    if (choice=='k')
      break;
  }
  cin.ignore(100000,'\n');
 }
  cout<<"Laczna ilosc stworzonych obiektow klasy SceneObject: "<<SceneObject::TakeCreated()<<endl;
    cout<<"      Ilosc istniejacych obiektow klasy SceneObject: "<<SceneObject::TakeExisted()<<endl;
    cout<<endl;
    cout<<"Laczna ilosc stworzonych obiektow klasy Vector3D: "<<Vector3D::TakeCreated()<<endl;
    cout<<"      Ilosc istniejacych obiektow klasy Vector3D: "<<Vector3D::TakeExisted()<<endl;
    cout<<endl;
}

