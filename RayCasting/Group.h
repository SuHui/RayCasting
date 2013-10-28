#ifndef __GROUP_H_
#define __GROUP_H_

#include "Object3D.h"

class Group:public Object3D
{
public:
	Group()
	{
		m_num_objects=0;
		m_object3D=NULL;
	}
	Group(int num_objects)
	{
		m_num_objects=num_objects;
		m_object3D=new Object3D *[m_num_objects];
	}
	~Group()
	{
		for(int i=0;i<m_num_objects;i++)
		{
			delete m_object3D[i];
		}
		if(m_object3D!=NULL)
			delete m_object3D;
	}
	void addObject(int count,Object3D *object)
	{
		m_object3D[count]=object;
	}
	bool intersect(const Ray &r, Hit &h, float tmin)
	{
		bool temp=false;
		for(int i=0;i<m_num_objects;i++)
		{
			temp=(m_object3D[i]->intersect(r,h,tmin)?true:temp);
		}
		return temp;
	}
private:
	int m_num_objects;
	Object3D **m_object3D;
};

#endif 