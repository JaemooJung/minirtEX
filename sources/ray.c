/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:23:18 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/27 02:32:59 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

//ray 생성자(정규화 된 ray)
t_ray		ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3	ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

//primary_ray 생성자
t_ray		ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	// left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_record record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3	ray_color(t_scene *scene)
{
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	else
		return (color3(0.2, 0.2, 0.2));
}
