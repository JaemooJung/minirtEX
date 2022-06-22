/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:23:29 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/22 19:22:01 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_canvas	canvas(int	width, int height)
{
	t_canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_camera	camera(t_canvas *canvas, t_point3 orig)
{
	t_camera	cam;
	double		focal_len;
	double		viewport_height;

	viewport_height = 2.0;
	focal_len = 1.0;
	cam.orig = orig;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = vec3(cam.viewport_w, 0, 0);
	cam.vertical = vec3(0, cam.viewport_h, 0);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
								vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
	return (cam);
}

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;
	
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		error("scene malloc failed");
	scene->canvas = canvas(WIN_W, WIN_H);
	scene->camera = camera(&scene->canvas, point3(0, 0, 7));
	world = NULL;
	obj_add(&world, object(SP, sphere(point3(-2, 0, -5), 2), color3(0, 0.5, 0.5))); // world 에 구1 추가
	t_object *cy = object(CY, cylinder(point3(4, -2, -5), 1, vec3(EPSILON, 1, EPSILON), 4), color3(0.7, 0, 0));
	t_cylinder *c = cy->element;
	obj_add(&world, cy);
	obj_add(&world, object(PL, plane(c->center, c->dir, c->radius), cy->albedo));
	obj_add(&world, object(PL, plane(vplus(c->center, vmult(c->dir, c->height)), c->dir, c->radius), cy->albedo));
	obj_add(&world, object(PL, plane(point3(0, -3, 0), vec3(EPSILON, 1, EPSILON), INF), color3(0, 0.7, 0)));
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(4, 0, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	scene->light = lights;
	ka = 0.2; // 8.4 에서 설명
	scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
	return (scene);
}

