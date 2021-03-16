#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: rotations_3D
	./rotations_3D

rotations_3D: obj obj/main.o obj/Prism.o obj/Body.o obj/matrix3x3.o obj/vector3D.o\
           obj/gnuplot_link.o obj/Dron.o obj/Obstacle.o obj/Factory.o
	g++ -Wall -pedantic -std=c++0x -o rotations_3D obj/main.o obj/vector3D.o\
                        obj/matrix3x3.o obj/Prism.o obj/gnuplot_link.o obj/Body.o obj/Dron.o obj/Obstacle.o obj/Factory.o

obj:
	mkdir obj

obj/gnuplot_link.o: inc/gnuplot_link.hh src/gnuplot_link.cpp
	g++ -c ${CXXFLAGS} -o obj/gnuplot_link.o src/gnuplot_link.cpp

obj/main.o: src/main.cpp inc/Prism.hh inc/Body.hh inc/matrix3x3.hh inc/matrix.hh	inc/Rotor.hh	inc/vector3D.hh inc/vector.hh inc/Scene.hh inc/Dron.hh inc/CuboidObstacle.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Prism.o: src/Prism.cpp inc/Prism.hh\
         inc/vector3D.hh inc/vector.hh inc/matrix.hh inc/matrix3x3.hh
	g++ -c ${CXXFLAGS} -o obj/Prism.o src/Prism.cpp

obj/matrix3x3.o: src/matrix3x3.cpp inc/matrix3x3.hh inc/matrix.hh inc/vector3D.hh inc/vector.hh
	g++ -c ${CXXFLAGS} -o obj/matrix3x3.o src/matrix3x3.cpp

obj/vector3D.o: src/vector3D.cpp inc/vector3D.hh inc/vector.hh
	g++ -c ${CXXFLAGS} -o obj/vector3D.o src/vector3D.cpp

obj/Body.o: src/Body.cpp inc/Body.hh\
         inc/vector3D.hh inc/vector.hh inc/matrix.hh inc/matrix3x3.hh
	g++ -c ${CXXFLAGS} -o obj/Body.o src/Body.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/Body.hh inc/Rotor.hh
	g++ -c ${CXXFLAGS} -o obj/Dron.o src/Dron.cpp

obj/Obstacle.o: src/Obstacle.cpp inc/Obstacle.hh inc/Dron.hh inc/Prism.hh
	g++ -c ${CXXFLAGS} -o obj/Obstacle.o src/Obstacle.cpp

obj/Factory.o: src/Factory.cpp inc/Factory.hh inc/Dron.hh inc/CuboidObstacle.hh inc/vector3D.hh
	g++ -c ${CXXFLAGS} -o obj/Factory.o src/Factory.cpp


clean:
	rm -f obj/*.o rotations_3D
