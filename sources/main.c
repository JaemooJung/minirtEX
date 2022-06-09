#include "minirt.h"
#include <stdio.h>

static int terminate(void *info)
{	
	t_info *tmp = (t_info *)info;

	mlx_destroy_window(tmp->mlx_ptr, tmp->win_ptr);
	exit(0);
}

void ex03(t_info info)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;

	//Scene setting;
	canv = canvas(400, 300);
	cam = camera(&canv, point3(0, 0, 0));

	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray);
			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, j, encode_color(pixel_color));
			++i;
		}
		--j;
	}
}

void ex04(t_info info)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	t_sphere	*sp;

	//Scene setting;
	canv = canvas(400, 300);
	cam = camera(&canv, point3(0, 0, 0));
	sp = sphere(point3(0, 0, -5), 2);

	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color_sph(&ray, sp);
			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, j, encode_color(pixel_color));
			++i;
		}
		--j;
	}
}

void ex07(t_info info)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	t_object	*objs;

	canv = canvas(info.win_w, info.win_h);
	cam = camera(&canv, point3(0, 0, 0));
	objs = object(SP, sphere(point3(-2, 0, -5), 2));
	obj_add(&objs, object(SP, sphere(point3(2, 0, -5), 2)));
	//obj_add(&objs, object(SP, sphere(point3(0, -1000, 0), 999)));

	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color_obj(&ray, objs);
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
	ex07(info);
	mlx_hook(info.win_ptr, X_EVENT_KEY_EXIT, 0, terminate, &info);
	mlx_loop(info.mlx_ptr);
}