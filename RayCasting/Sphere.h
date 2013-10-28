#ifndef __SPHERE__
#define __SPHERE__
#include "Object3D.h"
#include "material.h"
class Sphere:public Object3D
{
public:
	Sphere(){}
	Sphere(Vec3f center,float radius,Material *current_material)
	{
		m_center=center;
		m_radius=radius;
		m_material=current_material;
	}
	~Sphere(){}
	bool intersect(const Ray &r, Hit &h, float tmin)
	{
		float b=2*r.getDirection().Dot3(r.getOrigin()-m_center);
		float c=(r.getOrigin()-m_center).Dot3(r.getOrigin()-m_center)-m_radius*m_radius;
		float d=b*b-4*c;
		if(d<0)
		{
			return false;
		}
		else
		{
			float f=sqrt(d);
			float t=((-b)-f)/2;
			if(t>tmin && t<h.getT())
			{
				h.set(t,m_material,r);
				return true;
			}
			return false;
		}	
	}
private:
	Vec3f m_center;
	float m_radius;
};

#endif