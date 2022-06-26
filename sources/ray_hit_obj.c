/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:39:21 by jaemjung          #+#    #+#             */
/*   Updated: 2022/06/26 13:28:55 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool	hit(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool			did_hit;
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
	else if (obj->type == CY)
		did_hit = hit_cylinder(obj, ray, rec);
	else if (obj->type == PL)
		did_hit = hit_plane(obj, ray, rec);
	return (did_hit);
}

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < EPSILON;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vmult(rec->normal, -1);
}
