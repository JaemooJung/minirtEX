/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:13:04 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/26 13:35:33 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static t_disc	calc_sp_disc(t_sphere *sp, t_ray *ray)
{
	t_disc	disc; //a, b, c는 각각 t에 관한 2차 방정식의 계수
	t_vec3	oc; //방향벡터로 나타낸 구의 중심.

	oc = vminus(ray->orig, sp->center);
	disc.a = vlength2(ray->dir);
	disc.half_b = vdot(oc, ray->dir);
	disc.c = vlength2(oc) - sp->radius2;
	disc.discriminant = disc.half_b * disc.half_b - disc.a * disc.c;
	return (disc);
}

t_bool	hit_sphere(t_object *object, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_disc		disc;
	double		sqrtd;
	double		root;

	sp = (t_sphere *)object->element;
	disc = calc_sp_disc(sp, ray);
	if (disc.discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(disc.discriminant);
	root = (-(disc.half_b) - sqrtd) / disc.a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-(disc.half_b) + sqrtd) / disc.a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = object->albedo;
	return (TRUE);
}
