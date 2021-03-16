#include "Prism.hh"


/*!
 * \file
 * \brief Ten plik zawiera metody klasy Prism
 *
 * Ten plik zawiera metody klasy Prism z ich pełnym sposobem działania
 */

Vector3D Prism::operator[] (unsigned int lnd) const {
  if (lnd>=0 && lnd<vertice.size())
    return vertice[lnd];
  else {
    cerr<<"Przekroczono zakres indeksów klasy Prism"<<endl;
    return vertice[0];  }
  }


Vector3D& Prism::operator[] (unsigned int lnd) {
   if (lnd>=0 && lnd<vertice.size())
     return vertice[lnd];
  else {
    cerr<<"Przekroczono zakres indeksów klasy Prism"<<endl;
    cerr<<"Dokonana zmiana zastosowana dla pierwszego elementu klasy"<<endl;
    return vertice[0];
  }
}

  
void Prism::operator += (Vector3D vect) {
  for (unsigned int i=0;i<vertice.size();++i)
    this->vertice[i]+=vect;
}

void Prism::Rotate (Matrix3x3 matrix, int times) {
  while (times>0) {
    for (unsigned int i=0;i<vertice.size();++i) 
      this->vertice[i]=matrix*this->vertice[i];
    times--;
  }
}

  
Vector3D Prism::Rotate_own_axis(double angle) {
  Vector3D help;
  Matrix3x3 Rotate;
  help=this->vertice[0]-this->vertice[vertice.size()/4];
  help*=0.5;
  help-=this->vertice[0];
  (*this)+=help;
  Rotate.Create3D('z',angle);
  (*this).Rotate(Rotate,1);
  help*=(-1);
  (*this)+=help;
  return help;
}

void Prism::operator = (Prism prism) {
  for (unsigned int i=0;i<vertice.size();++i)
    this->vertice[i]=prism[i];
}
