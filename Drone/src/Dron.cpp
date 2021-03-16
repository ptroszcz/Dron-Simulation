#include "Dron.hh"


/*!
 * \file
 * \brief Ten plik zawiera metody klasy Dron
 *
 * Ten plik zawiera metody klasy Dron z ich pełnym sposobem działania
 */


void Dron::Move_Dron(Vector3D vect){
  this->body+=vect;
  for (int i=0;i<NUMBER_OF_ROTORS;++i)
    rotor[i]+=vect;
}


void Dron::Rotate_Dron(double angle) {
  Vector3D vec;
  Matrix3x3 rotate;
  rotate.Create3D('z',angle);
  vec=(this->body).Rotate_own_axis(angle);
  for (int i=0;i<NUMBER_OF_ROTORS;++i) {
    vec*=(-1);
    rotor[i]+=vec;
    rotor[i].Rotate(rotate,1);
    vec*=(-1);
    rotor[i]+=vec; }
}

Vector3D Dron::Center() const{
  Vector3D result;
  result = (this->body)[2]-(this->body)[0];
  result=result/2;
  result+=(this->body)[0];
  return result;
}



bool Dron::IsCollision(const SceneObject& dron) const{
  Vector3D vec1, vec2;
  double distance;
  vec1=(*this).Center();
  vec1[2]=0;
  vec2=dron.Center();
  vec2[2]=0;
  distance=vec1.length(vec2);
  if (distance<(2*(*this).radius)) {
    if ((dron.Center())[2]>((*this).Center())[2]) {
      vec1[2]=((*this).Center())[2];
      vec2[2]=(dron.Center())[2]; }
    else {
      vec2[2]=((*this).Center())[2];
      vec1[2]=(dron.Center())[2]; }
    vec2[2]+=100;
    distance=vec2[2]-vec1[2];
    if (distance <=200.0)
      return true;
  }
  return false;
}
      
  


std::ostream& operator <<(std::ostream &stream, const Dron dron) {
  stream<<"  "<<dron.TakeName()<<"   Wpolrzedne: (";
  for (int i=0;i<3;++i) {
    stream<<fixed<<setprecision(1)<<(dron.Center())[i];
    if (i!=2)
      stream<<", "; }
  stream<<")"<<endl;
  return stream;
}
