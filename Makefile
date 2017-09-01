CC=g++

simpleraytracer: graphics2d.o material.o rayplane.o savebmp.o world.o main.o object.o raysphere.o simplewin2d.o
	$(CC) -lm graphics2d.o material.o rayplane.o savebmp.o world.o main.o object.o raysphere.o simplewin2d.o -o simpleraytracer

graphics2d.o: graphics2d.cpp graphics2d.h vec2.h vec3.h plane2.h
	$(CC) -c graphics2d.cpp

material.o: material.cpp material.h colour.h
	$(CC) -c material.cpp

rayplane.o: rayplane.cpp rayplane.h ray.h geometry.h plane.h
	$(CC) -c rayplane.cpp

savebmp.o: savebmp.cpp savebmp.h
	$(CC) -c savebmp.cpp

world.o: world.cpp world.h object.h colour.h ray.h light.h geometry.h vec3.h
	$(CC) -c world.cpp

main.o: main.cpp object.h light.h world.h ray.h colour.h material.h rayplane.h raysphere.h
	$(CC) -c main.cpp

object.o: object.cpp object.h material.h geometry.h vec3.h world.h
	$(CC) -c object.cpp

raysphere.o: raysphere.cpp raysphere.h ray.h geometry.h vec3.h
	$(CC) -c raysphere.cpp

simplewin2d.o: simplewin2d.cpp simplewin2d.h savebmp.h graphics2d.h
	$(CC) -c simplewin2d.cpp

clean:
	rm *.o simpleraytracer
