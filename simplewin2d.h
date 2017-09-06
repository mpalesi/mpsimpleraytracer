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

#ifndef __SIMPLEWIN2D_H__
#define __SIMPLEWIN2D_H__


// COTD Entry submitted by Joshua Carmody [paladinoftheweb@hotmail.com]
//modified by me (nick c)

#include <string>
#include "graphics2d.h"
class Vec2;
class Vec3;
class drawingSurface;

// MAU:
inline unsigned long RGB(float r, float g, float b)
{
  return ((unsigned long)r << 16) | ((unsigned long)g << 8) | ((unsigned long)b);
}


/*************************************************************************/
// the bitmapWindow class. This uses the above drawingSurface class to
// easily create a window that we can draw to directly.
/*************************************************************************/
class bitmapWindow : public Graphics2d 
{
public:
  bitmapWindow(int x, int y, int width, int height); // Constructor
  ~bitmapWindow(); // Destructor
  void setPixel(int x, int y, unsigned long color); // Set Pixel data in our pointer to the specified color
  void erase(unsigned long color); // Passes the erase request to the drawingSurface

  int saveBMP(char *fname);




  //-----------------------------------------------------------------
  //NEWCODE: satisfy Graphics2d interface.
  //-----------------------------------------------------------------
  virtual void clear();

  virtual void startDrawing();

  virtual int getWidth() const;
  virtual int getHeight() const;


  virtual void drawPixel(const Vec2& pos, const Vec3& colour);

  virtual void drawPixel(int xpos, int ypos, const Vec3& colour);


  // MAU:  virtual void doDrawLine(const Vec2& startpos, const Vec2& endpos, const Vec3& colour);

  // MAU:  virtual void drawRect(const Vec2& pos, int width, int height, const Vec3& colour);


  // MAU:  virtual void drawText(const Vec2& pos, const std::string& text, const Vec3& colour);

  // MAU: HWND getWindowHandle(){ return windowHandle; } 

  inline void fastDrawPixelAdvance(const Vec3& colour)
  {
    *writeindex++ = RGB(colour.x*255, colour.y*255, colour.z*255);
  }

  void advanceToNextRow(int currentx);


protected:
  /* MAU: HWND windowHandle; // The handle for the window we'll pop up. */
  /* MAU: void registerWindowClass(HINSTANCE currentInstance); // For registering the class of window we'll use */
  /* MAU: static BOOL classIsRegistered; // Have we, or have we not, registered our window class? */
  /* MAU: static int numberOfBitmapWindows; // The number of these classes in use */
  int windowWidth, windowHeight; // Store the window's dimensions
  drawingSurface *windowContents; // easy DIB class defined above

  unsigned long* writeindex;
};






/*************************************************************************/
// drawingSurface class. Allows for very easy drawing to a window.
/*************************************************************************/
class drawingSurface {
public:
  drawingSurface(int width, int height); // Constructor
  ~drawingSurface(); // Destructor
    
  inline void setPixel(int x, int y, unsigned long color); // Set Pixel data in our pointer to the specified color
  void erase(unsigned long color); // Completely fills the bitmap with the specified color
  int getWidth(); // Return the bitmap's width.
  int getHeight(); // Return the bitmap's height.

  unsigned long* getSurface(){ return windowContents; }

protected:
  unsigned long *windowContents; // Pointer to pixel data to display in the window
  int windowWidth, windowHeight; // Store the window's dimensions
};

/*************************************************************************/
// setPixel, sets the pixel at x, y to color inside the DIB
/*************************************************************************/
inline void drawingSurface::setPixel(int x, int y, unsigned long color)
{
  //NEWCODE: clip out pixels off screen
  if(x < 0 || x >= windowWidth || y < 0 || y >= windowHeight)
    return;


  *(windowContents + (x + (y * windowWidth))) = color;
}

#endif //__SIMPLEWIN2D_H__
