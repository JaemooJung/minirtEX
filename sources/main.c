#include "minirt.h"
#include <stdio.h>

static int terminate(void *info)
{	
	t_info *tmp = (t_info *)info;

	mlx_destroy_window(tmp->mlx_ptr, tmp->win_ptr);
	exit(0);
}

// void ex03(t_info info)
// {
// 	int			i;
// 	int			j;
// 	double		u;
// 	double		v;
// 	t_color3	pixel_color;
// 	t_canvas	canv;
// 	t_camera	cam;
// 	t_ray		ray;

// 	//Scene setting;
// 	canv = canvas(400, 300);
// 	cam = camera(&canv, point3(0, 0, 0));

// 	j = canv.height - 1;
// 	while (j >= 0)
// 	{
// 		i = 0;
// 		while (i < canv.width)
// 		{
// 			u = (double)i / (canv.width - 1);
// 			v = (double)j / (canv.height - 1);
// 			//ray from camera origin to pixel
// 			ray = ray_primary(&cam, u, v);
// 			pixel_color = ray_color(&ray);
// 			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, j, encode_color(pixel_color));
// 			++i;
// 		}
// 		--j;
// 	}
// }

// void ex04(t_info info)
// {
// 	int			i;
// 	int			j;
// 	double		u;
// 	double		v;
// 	t_color3	pixel_color;
// 	t_canvas	canv;
// 	t_camera	cam;
// 	t_ray		ray;
// 	t_sphere	*sp;

// 	//Scene setting;
// 	canv = canvas(400, 300);
// 	cam = camera(&canv, point3(0, 0, 0));
// 	sp = sphere(point3(0, 0, -5), 2);

// 	j = canv.height - 1;
// 	while (j >= 0)
// 	{
// 		i = 0;
// 		while (i < canv.width)
// 		{
// 			u = (double)i / (canv.width - 1);
// 			v = (double)j / (canv.height - 1);
// 			//ray from camera origin to pixel
// 			ray = ray_primary(&cam, u, v);
// 			pixel_color = ray_color_sph(&ray, sp);
// 			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, j, encode_color(pixel_color));
// 			++i;
// 		}
// 		--j;
// 	}
// }

// void ex07(t_info info)
// {
// 	int			i;
// 	int			j;
// 	double		u;
// 	double		v;
// 	t_color3	pixel_color;
// 	t_canvas	canv;
// 	t_camera	cam;
// 	t_ray		ray;
// 	t_object	*objs;

// 	canv = canvas(info.win_w, info.win_h);
// 	cam = camera(&canv, point3(0, 0, 0));
// 	objs = object(SP, sphere(point3(-2, 0, -5), 2));
// 	obj_add(&objs, object(SP, sphere(point3(2, 0, -5), 2)));
// 	obj_add(&objs, object(SP, sphere(point3(0, -1000, 0), 990)));

// 	j = 0;
// 	while (j < canv.height)
// 	{
// 		i = 0;
// 		while (i < canv.width)
// 		{
// 			u = (double)i / (canv.width - 1);
// 			v = (double)j / (canv.height - 1);
// 			//ray from camera origin to pixel
// 			ray = ray_primary(&cam, u, v);
// 			pixel_color = ray_color_obj(&ray, objs);
// 			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, j, encode_color(pixel_color));
// 			++i;
// 		}
// 		++j;
// 	}
// }

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka; // 8.4 에서 설명

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->canvas = canvas(400, 300);
	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
	obj_add(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
	obj_add(&world, object(SP, sphere(point3(0, -1000, 0), 900), color3(1, 1, 1))); // world 에 구3 추가
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
	scene->light = lights;
	ka = 0.1; // 8.4 에서 설명
	scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
	return (scene);
}

void ex08(t_info info)
{
		int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	// 수정
	t_scene		*scene;
	
	scene = scene_init();
	// 랜더링
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene); 
			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, j, encode_color(pixel_color));
			++i;
		}
		--j;
	}
}

int	main()
{
	t_info	info;

	info.mlx_ptr = mlx_init();
	info.win_h = 300;
	info.win_w = 400;
	info.win_ptr = mlx_new_window(info.mlx_ptr, info.win_w, info.win_h, "Minirt");
	//ex03(info);
	//ex04(info);
	//ex07(info);
	ex08(info);
	mlx_hook(info.win_ptr, X_EVENT_KEY_EXIT, 0, terminate, &info);
	mlx_loop(info.mlx_ptr);
}