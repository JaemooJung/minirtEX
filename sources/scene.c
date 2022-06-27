/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:23:29 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/27 14:17:23 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_canvas	canvas(int width, int height)
{
	t_canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_vec3	cam_set_vup(t_vec3 dir)
{
	if (dir.x == 0 && dir.y != 0 && dir.z == 0)
		return (vec3(0, dir.y, EPSILON));
	else
		return (vec3(0, 1, 0));
}

t_camera	camera(t_canvas *canvas, t_point3 orig, t_vec3 dir, double fov)
{
	t_camera	cam;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;

	cam.orig = orig;
	cam.focal_len = tan((fov * PI / 180.0) / 2.0);
	cam.viewport_h = cam.focal_len * 2;
	cam.viewport_w = cam.viewport_h * canvas->aspect_ratio;
	w = vunit(vmult(dir, -1));
	u = vunit(vcross(cam_set_vup(cam.dir), w));
	v = vcross(w, u);
	cam.horizontal = vmult(u, cam.viewport_w);
	cam.vertical = vmult(v, cam.viewport_h);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)), w);
	return (cam);
}

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*light;
	double		ka;
	
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		error("scene malloc failed");
	scene->canvas = canvas(WIN_W, WIN_H);
	scene->camera = camera(&scene->canvas, point3(0, -10, 7), vec3(0, 0.6, -0.3), 120);
	world = NULL;
	obj_add(&world, object(PL, plane(point3(0, 0, -5), vec3(0, 0, 1), INFINITY), color3(155/255, 255/255, 150/255)));
	obj_add(&world, object(SP, sphere(point3(0, 0, 3), 4), color3(0.3, 0.7, 1)));
	obj_add(&world, object(CY, cylinder(point3(0, 0, 0), 2.2, vec3(1, 1, 1), 21.42), color3(10/255, 0, 255/255)));
	obj_add(&world, object(CY, cylinder(point3(0, 0, 0), 30, vec3(0, 0, -1), 1.42), color3(0.7, 0.1, 0)));
	scene->world = world;
	light = object(LIGHT_POINT, light_point(point3(0, 0, 30), color3(1, 1, 1), 0.7), color3(0, 0, 0));
	scene->light = light;
	ka = 0.1;
	scene->ambient = vmult(color3(1,1,1), ka);
	return (scene);
}
