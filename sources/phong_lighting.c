/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:40:39 by jaemjung          #+#    #+#             */
/*   Updated: 2022/06/27 14:02:42 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	//v - 2 * dot(v, n) * n;
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd; // diffuse의 강도
	double		light_len;
	t_ray		light_ray;
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	double		ksn;
	double		ks;
	double		brightness;

	light_dir = vminus(light->origin, scene->rec.p);
	light_len = vlength(light_dir);
	// 그림자 계산 시 자기 자신에 의해 그림자가 지는 것을 방지하기 위해 오차값을 곱해줘야 함.
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, 1e-3)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	// cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
	diffuse = vmult(light->light_color, kd);
	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	ksn = 64; // shininess value
	ks = 0.3; // specular strength
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
	return (vmult(vplus(vplus(scene->ambient, diffuse), specular), brightness));
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*light;

	light_color = color3(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
	light = scene->light;
	if (light->type == LIGHT_POINT)
		light_color = vplus(light_color, point_light_get(scene, light->element));
	light_color = vplus(light_color, scene->ambient);
	//광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}
