#include "Factory.hh"


wFactory Factory::_wFactory;

void wFactory::CreateFactory() {
  if (!*this)
    reset(new Factory()); }


shared_ptr<SceneObject> Factory::CreateObject(ObjectType ObjType) const {

  Vector3D V1,V2;
  switch (ObjType) {
  case OT_Dron: {
    shared_ptr<Dron> wDron(new Dron(_Name.c_str()));
    Body Korpus;
    Rotor rotor1,rotor2, rotor3,rotor4;
    V1=this->Center;
    V1[0]-=50;
    V1[1]-=50;
    Korpus[0]=V1;
    V1[0]+=100;
    Korpus[1]=V1;
    V1[1]+=100;
    Korpus[2]=V1;
    V1[0]-=100;
    Korpus[3]=V1;
    V1[1]-=100;
    V1[2]+=50;
    Korpus[4]=V1;
    V1[0]+=100;
    Korpus[5]=V1;
    V1[1]+=100;
    Korpus[6]=V1;
    V1[0]-=100;
    Korpus[7]=V1;
    wDron->body=Korpus;
    V1[1]-=100;
    V1[0]-=50;
    V2[1]=V1[1];
    rotor1[0]=V1;
    V1[0]+=25;
    V1[1]+=50*sin(M_PI/3);
    rotor1[1]=V1;
    V1[0]+=50;
    rotor1[2]=V1;
    V1[0]+=25;
    V1[1]=V2[1];
    rotor1[3]=V1;
    V1[0]-=25;
    V1[1]+=(-1)*50*sin(M_PI/3);
    rotor1[4]=V1;
    V1[0]-=50;
    rotor1[5]=V1;
    V1[0]=0;
    V1[1]=0;
    V1[2]=50;
    for (int i=0;i<6;++i)
      rotor1[i+6]=rotor1[i]+V1;
    rotor2=rotor1;
    rotor3=rotor1;
    rotor4=rotor1;
    V1[0]=100;
    V1[1]=0;
    V1[2]=0;
    rotor2+=V1;
    V1[1]=100;
    rotor3+=V1;
    V1[0]=0;
    rotor4+=V1;
    (*wDron)[0]=rotor1;
    (*wDron)[1]=rotor2;
    (*wDron)[2]=rotor3;
    (*wDron)[3]=rotor4;
    V1=(*wDron).Center();
    V1[2]=0;
    V2=((*wDron)[0])[5];
    V2[2]=0;
    (wDron->radius)=V1.length(V2);
    return wDron; }
  case OT_CuboidObstacle: {
    shared_ptr<CuboidObstacle> wCubObst(new CuboidObstacle(_Name.c_str()));
    V1=this->Center;
    V2=this->Dimensions;
    V1[0]-=(V2[0]/2);
    V1[1]-=(V2[1]/2);
    (*wCubObst)[0]=V1;
    V1[0]+=V2[0];
    (*wCubObst)[1]=V1;
    V1[1]+=V2[1];
    (*wCubObst)[2]=V1;
    V1[0]-=V2[0];
    (*wCubObst)[3]=V1;
    V1[1]-=V2[1];
    V1[2]+=V2[2];
    (*wCubObst)[4]=V1;
    V1[0]+=V2[0];
    (*wCubObst)[5]=V1;
    V1[1]+=V2[1];
    (*wCubObst)[6]=V1;
    V1[0]-=V2[0];
    (*wCubObst)[7]=V1;
    V1[0]=119.709;     /*dlugosc promienia dronow*/
    V1[1]=119.709;
    V1[2]=0;
    (wCubObst->ObjectContour).vertice_min=(*wCubObst)[0]-V1;
    (wCubObst->ObjectContour).vertice_max=(*wCubObst)[6]+V1;
    return wCubObst; }

  }
  return make_shared<CuboidObstacle>();
}
