/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:39:21 by jaemjung          #+#    #+#             */
/*   Updated: 2022/06/22 19:28:08 by jaemjung         ###   ########.fr       */
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
	else if (obj->type == CY)
		did_hit = hit_cylinder(obj, ray, rec);
	else if (obj->type == PL)
		did_hit = hit_plane(obj, ray, rec);
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

int	cy_boundary(t_cylinder *cy, t_vec3 at_point)
{
	double	hit_height;

	hit_height = vdot(vminus(at_point, cy->center), cy->dir);
	if (hit_height > cy->height || hit_height < 0)
		return (0);
	return (1);
}

t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
	t_point3 hit_center;
	t_vec3 normal;

	hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
	normal = vminus(at_point, hit_center);
	return (vunit(normal));
}

int	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder *cy;

	//a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
	double	a;
	double	half_b;
	double	c;
	t_vec3	u;
	t_vec3	o;
	t_vec3	delta_P;
	double	r;

	double discriminant; // 판별식
	double sqrtd;
	double root;
	double hit_height;
	
	//공식 : a * t^2 + b * t + c = 0
	cy = cy_obj->element;
	u = ray->dir;
	o = cy->dir;
	r = cy->radius;
	delta_P = vminus(ray->orig, cy->center);
	a = vlength2(vcross(u, o));
	half_b = vdot(vcross(u, o), vcross(delta_P, o));
	c = vlength2(vcross(delta_P, o)) - pow(r, 2);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
    // 이 시점에서 판별식이 참이 나왔기에 근이 존재한다고 판단한다.
	sqrtd = sqrt(discriminant); 
	root = (-half_b - sqrtd) / a;  // 근의 공식 해, 작은 근부터 고려.
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	if (!(hit_height = cy_boundary(cy, ray_at(ray, root))))
		return (0);
	rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
	rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

// t_bool	hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_cylinder *cy;
// 	t_vec3	oc;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;
	
// 	cy = (t_cylinder *)obj->element;
// 	oc = vminus(ray->orig, cy->center);
// 	a = pow(vdot(ray->dir, cy->dir), 2) - 1;
// 	b = vdot(ray->dir, cy->dir) * vdot(oc, cy->dir) - vdot(oc, ray->dir);
// 	c = pow(cy->radius, 2) - vdot(oc, oc) + pow(vdot(oc, cy->dir), 2);
// 	discriminant = pow(b, 2) - (a * c);
// 	if (discriminant < 0)
// 		return (FALSE);
// 	double t = (sqrt(discriminant) - b) / a;
// 	if (t < rec->tmin || t > rec->tmax)
// 	{
// 		t = - (b + sqrt(discriminant)) / a;
// 		if (t < rec->tmin || t > rec->tmax)
// 			return (FALSE);
// 	}
// 	rec->t = t;
// 	rec->p = ray_at(ray, t);
// 	rec->normal = vunit(vminus(oc, vmult(cy->dir, vdot(oc, cy->dir))));
// 	set_face_normal(ray, rec);
// 	oc = vminus(rec->p, cy->center);
// 	rec->albedo = obj->albedo;
// 	if (vdot(oc, cy->dir) > cy->height || vdot(oc, cy->dir) < 0)
// 		return (FALSE);
// 	return (TRUE);
// }

t_bool	hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	float	numrator;
	float	denominator;
	float	root;

	pl = obj->element;
	denominator = vdot(ray->dir, pl->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numrator = vdot(vminus(pl->center, ray->orig), pl->dir);
	root = numrator / denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	if (pl->radius != INFINITY)
		if (vlength(vminus(pl->center, rec->p)) > pl->radius)
			return (FALSE);
	rec->normal = pl->dir;
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return (TRUE);
}

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < EPSILON;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vmult(rec->normal, -1);
}
