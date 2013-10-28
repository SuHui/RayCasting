#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "ray.h"
#include "vectors.h"

class Camera
{
public:
	Camera(){}
	~Camera(){}
	virtual Ray generateRay(Vec2f point)=0;
	virtual float getTMin()const=0;
protected:
	float m_tMin;
};
class OrthographicCamera:public Camera
{
public:
	OrthographicCamera(){}
	~OrthographicCamera(){}
	OrthographicCamera(Vec3f center,Vec3f direction,Vec3f up,float size)//构造函数初始化
	{
		m_center=center; 

		direction.Normalize();                     //输入的单位向量单位化
		m_direction=direction;   
		Vec3f t_up=up-up.Dot3(direction)/direction.Dot3(direction)*direction;
		t_up.Normalize();
		m_up=t_up;
		Vec3f::Cross3(m_horiziontal,up,direction); 
		m_horiziontal.Normalize(); 
		m_size=size;  
		m_tMin=-FLT_MAX;                      
	}
	Ray generateRay(Vec2f point)                   
	{                                            
		Vec3f origin=m_center+(point.x()-0.5)*m_size*m_horiziontal+(point.y()-0.5)*m_up*m_size;
		Ray newRay(origin,m_direction);
		return newRay;
	}
	float getTMin()const
	{
		return m_tMin;
	}

private:
	Vec3f m_center;
	Vec3f m_direction;
	Vec3f m_up;
	float m_size;
	Vec3f m_horiziontal;

};

#endif