#ifndef __Object3D__
#define __Object3D__
#include "vectors.h"
#include "hit.h"
#include "ray.h"
#include "material.h"
class Object3D
{
public:
	Object3D()
	{
		m_material=NULL;
	}
	~Object3D(){}
	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
protected:
	Material *m_material;

};
#endif