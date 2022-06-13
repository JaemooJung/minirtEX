#include "minirt.h"
#include <stdio.h>

void ex08(t_mlx_info info)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_scene		*scene;
	
	scene = scene_init();
	// 랜더링
	j = 0;
	while (j < scene->canvas.height)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene); 
			mlx_pixel_put(info.mlx_ptr, info.win_ptr, i, 
				scene->canvas.height - j - 1, encode_color(pixel_color));
			++i;
		}
		++j;
	}
}

int	main()
{
	t_mlx_info	info;

	init_mlx(&info);
	//ex08(info);
	draw_scene(&info);
	mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.img_ptr, 0, 0);
	mlx_hook(info.win_ptr, X_EVENT_KEY_EXIT, 0, terminate, &info);
	mlx_key_hook(info.win_ptr, key_hook, &info);
	mlx_loop(info.mlx_ptr);
}