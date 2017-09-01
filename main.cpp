/*=====================================================================
  Code By Nicholas Chapman.

  nickamy@paradise.net.nz

  You may use this code for any non-commercial project,
  as long as you do not remove this description.

  You may *not* use this code for any commercial project.
  =====================================================================*/

#include <math.h>
#include <time.h>
//MAU: #include "../simplewin2d/simwin_framework.h"
#include "simplewin2d.h"
// #include "../utils/timer.h"
#include "world.h"
#include "ray.h"
#include "colour.h"
#include "material.h"
#include "rayplane.h"
#include "raysphere.h"
#include "object.h"
#include "light.h"

//------------------------------------------------------------------------
//forwards declarations
//------------------------------------------------------------------------
const Vec3 getUnitDirForImageCoords(int x, int y);

//------------------------------------------------------------------------
//some global objects
//------------------------------------------------------------------------
World* world = NULL;

Light* light1 = NULL;

Object* sphere1 = NULL;


//dimensions of the window
const int width = 400;
const int height = 400;

//position of the camera
const Vec3 campos(-3,0,1);

/* MAU:
   void getWindowDims(int& width_, int& height_)
   {
   width_ = width;
   height_ = height;
   }
*/

void doInit(/* MAU: HINSTANCE hinstance, HWND windowhandle,*/ bitmapWindow& graphics)
{
  //------------------------------------------------------------------------
  //create the world
  //------------------------------------------------------------------------
  world = new World();


  //------------------------------------------------------------------------
  //insert some objects into the world
  //------------------------------------------------------------------------
  {
    Material planemat(Colour(1,1,1), 0.5, 20, 0.6); 
		
    RayPlane* planegeom = new RayPlane(Plane(Vec3(0,0,1), 0));

    Object* groundplane = new Object(planemat, planegeom);

    world->insertObject(groundplane);
  }

	
  {
    Material mat(Colour(1,1,1), 0.5, 20, 0); 
		
    RayPlane* geom = new RayPlane(Plane(Vec3(0,1,0), -6));

    Object* theplane = new Object(mat, geom);

    world->insertObject(theplane);
  }

  {

    Material mat(Colour(0,1,0), 0.4, 20, 0.7); 
		
    RaySphere* geom = new RaySphere(Vec3(4,0,2), 0.7);

    sphere1 = new Object(mat, geom);

    world->insertObject(sphere1);
  }

  {

    Material mat(Colour(1,0,0), 0.4, 10, 0.5); 
		
    RaySphere* geom = new RaySphere(Vec3(4,0,2), 0.7);

    Object* thesphere = new Object(mat, geom);

    world->insertObject(thesphere);
  }



  //world->insertLight(new Light(Vec3(0,0,10), Colour(1, 0, 0) * 100));

  light1 = new Light(Vec3(15,0,5), Colour(1, 1, 1) * 100);
	
  world->insertLight(light1);
}


void doMain(bitmapWindow& graphics, float rad)
{
  //------------------------------------------------------------------------
  //animate the movements of some of the entities
  //------------------------------------------------------------------------	

  if(light1)
    light1->pos = Vec3(0 + cos(rad) * 5, sin(rad) * 5, 5);
	

  if(sphere1)
    static_cast<RaySphere&>(sphere1->getGeometry()).centerpos = 
      Vec3(3 + cos(rad * 0.2) * 2, sin(rad * 0.2) * 2, 1);


  //------------------------------------------------------------------------
  //draw the scene
  //------------------------------------------------------------------------
  for(int x=0; x<width; ++x)
    for(int y=0; y<height; ++y)
    {
      //------------------------------------------------------------------------
      //calculate the ray from the camera to trace thru the world
      //------------------------------------------------------------------------
      const Ray ray(campos, getUnitDirForImageCoords(x, y));

      Colour colour;
      world->getColourForRay(ray, colour);

      //------------------------------------------------------------------------
      //do some gamma correction
      //------------------------------------------------------------------------
      /*const float exponent = 0.6;
	colour.r = pow(colour.r, exponent);
	colour.g = pow(colour.g, exponent);
	colour.b = pow(colour.b, exponent);

	colour *= 0.5;*/

      //------------------------------------------------------------------------
      //make sure no components exceed 1
      //------------------------------------------------------------------------
      colour.positiveClipComponents();

      //------------------------------------------------------------------------
      //draw the pixel
      //------------------------------------------------------------------------
      graphics.drawPixel(x, y, Vec3(colour.b, colour.g, colour.r));
    }


}

void doShutdown()
{
  delete world;
  world = NULL;
}


//the below is for a camera pointing in the x direction, with y off to the left and z up.
const Vec3 getUnitDirForImageCoords(int x, int y)
{
  const float xfrac = (float)x / (float)width;
  const float yfrac = (float)y / (float)height;

  return normalise(Vec3(1.0f, -(xfrac - 0.5f), -(yfrac - 0.5f)));
}


// MAU:
int main()
{
  bitmapWindow *graphics = new bitmapWindow(30, 30, width, height);

  doInit(*graphics);

  graphics->startDrawing();

  /*
  char fname[16];
  for (int g=0; g<360; g+=10)
  {
    doMain(*graphics, (float)g*M_PI/360);
    sprintf(fname, "img_%03d.bmp", g);
    graphics->saveBMP(fname);
  }
  */

  doMain(*graphics, 0);
  graphics->saveBMP((char *)"img.bmp");

  doShutdown();


  delete graphics;

  return 0;
}
