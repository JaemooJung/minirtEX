/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:23:29 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/17 20:01:39 by jaemung          ###   ########.fr       */
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
	double		ka; // 8.4 에서 설명

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		error("scene malloc failed");
	scene->canvas = canvas(WIN_W, WIN_H);
	scene->camera = camera(&scene->canvas, point3(0, 0, 7));
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0, 0.5, 0.5)); // world 에 구1 추가
	obj_add(&world, object(CY, cylinder(point3(0, 0, -10), 2.2, vec3(1, 1, EPSILON), 8), color3(0.3, 0, 0)));
	obj_add(&world, object(PL, plane(point3(100, -100, -100), vec3(EPSILON, EPSILON, EPSILON), 10), color3(0, 0.7, 0)));
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(0, 0, 0), color3(1, 1, 1), 0.7), color3(0, 0, 0));
	scene->light = lights;
	ka = 0.1; // 8.4 에서 설명
	scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
	return (scene);
}

