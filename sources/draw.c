/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:27:18 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/26 13:35:08 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	draw_pixel(t_mlx_info *info, int x, int y, int color)
{
	char	*dst;

	dst = info->addr + (y * info->line_len + x * (info->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_scene(t_mlx_info *info)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_scene		*scene;
	
	scene = scene_init();
	j = -1;
	while (++j < scene->canvas.height)
	{
		i = -1;
		while (++i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene); 
			draw_pixel(info, i, scene->canvas.height - j - 1, encode_color(pixel_color));
		}
	}
}
