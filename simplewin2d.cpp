/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/

// ***
// *** Port to GNU g++ by Maurizio Palesi <maurizio.palesi@dieei.unict.it>
// ***

#include "simplewin2d.h"
#include "savebmp.h"

//#include "../maths/maths.h"


// COTD Entry submitted by Joshua Carmody [paladinoftheweb@hotmail.com]
//modified by me (nick c)

const float MAX_UBYTE_VAL = 255.0f;



/*************************************************************************/
// drawingSurface constructor. Creates a "drawing surface" (DIB) for the
// application to draw to. Takes two parameters, width, and height.
/*************************************************************************/
drawingSurface::drawingSurface(int width, int height) {
  windowWidth = width; // Store the width
  windowHeight = height; // Store the height

  windowContents = (unsigned long*)malloc(width * height * sizeof(unsigned long));

}



/*************************************************************************/
// Destructor for drawingSurface, cleans up vairables and frees memory.
/*************************************************************************/
drawingSurface::~drawingSurface() {
  free(windowContents);
}




/*************************************************************************/
// Erases the entire bitmap (fills with the specifier color)
/*************************************************************************/
void drawingSurface::erase(unsigned long color) {
  int i, j;
  for(i=0;i<windowWidth;i++) {
    for(j=0;j<windowHeight;j++) {
      *(windowContents + i + (j * windowWidth)) = color;
    }
  }
}





/*************************************************************************/
// Return the DIB's width
/*************************************************************************/
int drawingSurface::getWidth() {
  return windowWidth;
}




/*************************************************************************/
// Return the DIB's height
/*************************************************************************/
int drawingSurface::getHeight() {
  return windowHeight;
}


void bitmapWindow::advanceToNextRow(int currentx)
{
	writeindex += windowContents->getWidth() - currentx;
}


void bitmapWindow::clear()
{
	erase(0);
}

int bitmapWindow::saveBMP(char *fname)
{
  return SaveBMP(fname, 
		 windowContents->getSurface(), 
		 windowContents->getWidth(),
		 windowContents->getHeight());
}


void bitmapWindow::startDrawing()
{
	//erase(0);
	writeindex = windowContents->getSurface();
}


int bitmapWindow::getWidth() const
{
	return windowContents->getWidth();
}

int bitmapWindow::getHeight() const
{
	return windowContents->getHeight();
}



void bitmapWindow::drawPixel(const Vec2& pos, const Vec3& colour)
{
	setPixel(pos.x, pos.y, RGB(colour.x*MAX_UBYTE_VAL, colour.y*MAX_UBYTE_VAL, colour.z*MAX_UBYTE_VAL));
}


void bitmapWindow::drawPixel(int xpos, int ypos, const Vec3& colour)
{
	setPixel(xpos, ypos, RGB(colour.x*MAX_UBYTE_VAL, colour.y*MAX_UBYTE_VAL, colour.z*MAX_UBYTE_VAL));
}






/*************************************************************************/
// constructor for bitmapWindow. Takes 5 parameters. An X coordinate for
// the window to appear, a Y coordinate for the window to appear, the
// width of the window, the height of the window, and the handle to this
// program's instance.
/*************************************************************************/
bitmapWindow::bitmapWindow(int x, int y, int width, int height) 
{
  windowWidth = width + 7; // Store the width
  windowHeight = height + 25; // Store the height


  windowContents = new drawingSurface(width, height); // Create the drawing surface, this class is defined above
}


/*************************************************************************/
// Destructor, cleans up allocated memory and updates the number of
// these windows
/*************************************************************************/
bitmapWindow::~bitmapWindow() {
}




/*************************************************************************/
// Passes a request to change pixel data on to the drawing surface.
/*************************************************************************/
void bitmapWindow::setPixel(int x, int y, unsigned long color) {
  windowContents->setPixel(x, y, color);
}



/*************************************************************************/
// Passes a request to erase a line on to the drawingSurface.
/*************************************************************************/
void bitmapWindow::erase(unsigned long color) {
  windowContents->erase(color);
}



