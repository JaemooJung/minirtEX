/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:39:21 by jaemjung          #+#    #+#             */
/*   Updated: 2022/06/14 12:42:21 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool	hit(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool		did_hit;
	t_hit_record	tmp;

	tmp = *rec;
	did_hit = FALSE;
	while (obj != NULL)
	{
		if (hit_obj(obj, ray, &tmp))
		{
			did_hit = TRUE;
			tmp.tmax = tmp.t;
			*rec = tmp;
		}
		obj = obj->next;
	}
	return (did_hit);
}

t_bool	hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool	did_hit;

	did_hit = FALSE;
	if (obj->type == SP)
		did_hit = hit_sphere(obj, ray, rec);
	return (did_hit);
}

t_bool	hit_sphere(t_object *object, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc; //방향벡터로 나타낸 구의 중심.
	t_sphere	*sp;
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double	a; 
	double	half_b;
	double	c;
	double	discriminant; //판별식
	double	sqrtd;
	double	root;

	sp = (t_sphere *)object->element;
	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
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

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vmult(rec->normal, -1);
}