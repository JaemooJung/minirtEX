#include "minirt.h"
#include <stdio.h>

int	main()
{
	t_mlx_info	info;

	init_mlx(&info);
	draw_scene(&info);
	mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.img_ptr, 0, 0);
	mlx_hook(info.win_ptr, X_EVENT_KEY_EXIT, 0, terminate, &info);
	mlx_key_hook(info.win_ptr, key_hook, &info);
	mlx_loop(info.mlx_ptr);
}
