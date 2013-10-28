#include "stdafx.h"
#include "image.h"
#include "scene_parser.h"
#include "material.h"
#include "ray.h"
#include "camera.h"
#include "hit.h"
#include "group.h"
#include "object3d.h"
#include "vectors.h"
int main(int argc, char *argv[])
{
	const char *input_file = NULL;
	int width = 100;
	int height = 100;
	const char *output_file = NULL;
	float depth_min = 0;
	float depth_max = 1;
	const char *depth_file = NULL;
	for (int i = 1; i < argc; i++) 
	{
		if (!strcmp(argv[i],"-input")) 
		{   i++; assert (i < argc); 
			input_file = argv[i];
		} else if (!strcmp(argv[i],"-size")) {
			i++; assert (i < argc); 
			width = atoi(argv[i]);
			i++; assert (i < argc);
			height = atoi(argv[i]);
		}else if (!strcmp(argv[i],"-output")) {   
			i++; assert (i < argc); 
			output_file = argv[i];
		} else if (!strcmp(argv[i],"-depth")) {
			i++; assert (i < argc); 
			depth_min = atof(argv[i]);
			i++; assert (i < argc); 
			depth_max = atof(argv[i]);
			i++; assert (i < argc); 
			depth_file = argv[i];
		} else {
			printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
			assert(0);
		}
 
	}
    SceneParser *scene=new SceneParser(input_file);
	Image       *outputimage=new Image(width,height);
	outputimage->SetAllPixels(scene->getBackgroundColor());
	Image  *depthimage=new Image(width,height);     
    Camera *camera=scene->getCamera();   
	Material *meterial = new Material(scene->getBackgroundColor());
	Group  *group=scene->getGroup();
	for(int y=0;y<height;y++)                 
	{
		for(int x=0;x<width;x++)
		{
			Vec2f point(x,y);
			point/=float(width);
			Ray r=camera->generateRay(point);
			Hit hit(FLT_MAX, meterial);
			bool intersected=group->intersect(r,hit,camera->getTMin());
			outputimage->SetPixel(x,y,hit.getMaterial()->getDiffuseColor());
		    float deap = hit.getT();
			float length=depth_max-depth_min;
			float co=1.0f-(deap-depth_min)/length;
			Vec3f color(co,co,co);
			depthimage->SetPixel(x,y,color);
		}
	}
	delete meterial;
    outputimage->SaveTGA(output_file);
	depthimage->SaveTGA(depth_file);
	return 0;     
}

