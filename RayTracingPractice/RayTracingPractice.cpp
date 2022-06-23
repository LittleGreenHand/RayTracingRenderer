// RayTracingPractice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<fstream>
#include <iostream>

#include"color.h"
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
using namespace std;

//实现渐变色
color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	//线性插值
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
int main()
{
	//Image,投影屏幕宽高比
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	//World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
	//Camera
	camera cam;


	ofstream outPPM;
	outPPM.open("RayTracingOutPPM.ppm", ios::out | ios::trunc);
	outPPM << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for (int j = image_height - 1; j >= 0; --j) 
	{
		for (int i = 0; i < image_width; ++i) 
		{
			color pixel_color(0, 0, 0);
			for (int m = 0; m < samples_per_pixel; m++)
			{
				double u = (i + random_double()) / (image_width - 1);
				double v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			
			write_color(outPPM, pixel_color,samples_per_pixel);
		}
		outPPM << endl;
	}
	outPPM.close();
	cout << "Success!" << endl;
}
