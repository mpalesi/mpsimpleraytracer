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

#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

/*
interface for something that can draw 2d graphics
*/

#include "vec2.h"
#include "vec3.h"
#include <string>



class Graphics2d
{
public:
	virtual ~Graphics2d(){}

	virtual void startDrawing(){}

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;


	virtual void drawPixel(const Vec2& pos, const Vec3& colour) = 0;
	virtual void drawPixel(int xpos, int ypos, const Vec3& colour)
	{
		drawPixel(Vec2(xpos, ypos), colour);
	}
	virtual void drawPixel(int xpos, int ypos, unsigned char r, unsigned char g, unsigned char b)
	{
		drawPixel(Vec2(xpos, ypos), Vec3((float)r / 255, (float)g / 255, (float)b / 255));
	}

	virtual void clear(){}//NOTE: FIXME
};



#endif //__GRAPHICS2D_H__
