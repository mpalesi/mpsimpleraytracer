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

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "colour.h"
#include "vec3.h"



class Light
{
public:
	Light(const Vec3& pos_, const Colour& c)
	:	pos(pos_),
		colour(c)
	{}

	~Light(){}

	inline const Vec3& getPos() const { return pos; }
	inline const Colour& getColour() const { return colour; }

	Vec3 pos;
	Colour colour;
};


#endif //__LIGHT_H__
