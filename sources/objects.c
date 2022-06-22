/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:23:22 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/18 01:31:28 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "error.h"
#include "utils.h"
#include <stdlib.h>

t_object	*object(t_object_type type, void *element, t_color3 albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->radius = radius;
	sphere->radius2 = radius * radius;
	return (sphere);
}

t_cylinder	*cylinder(t_point3 center, double radius, t_vec3 dir, double height)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		error("cylinder malloc failed");
	cylinder->center = center;
	cylinder->dir = vunit(dir);
	cylinder->radius = radius;
	cylinder->height = height;
	return (cylinder);
}

void	attach_cy_cap(t_object **objs, t_object *cy_)
{
	t_cylinder	*cy;
	t_plane	*top;
	t_plane	*bottom;

	cy = (t_cylinder *)cy_->element;
	top = (t_plane *)malloc(sizeof(t_plane));
	bottom = (t_plane *)malloc(sizeof(t_plane));
	if (top == NULL || bottom == NULL)
		error("attach_cy_cap malloc failed");
	bottom->center = cy->center;
	bottom->dir = cy->dir;
	bottom->radius = cy->radius;
	obj_add(objs, object(PL, bottom, cy_->albedo));
	top->dir = cy->dir;
	top->radius = cy->radius;
	top->center = vplus(cy->center, vmult(cy->dir, cy->height));
	obj_add(objs, object(PL, top, cy_->albedo));
}

t_plane	*plane(t_point3 center, t_vec3 dir, double radius)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->center = center;
	plane->dir = vunit(dir);
	plane->radius = radius;
	return (plane);
}

t_light		*light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

void	obj_add(t_object **objects, t_object *new)
{
	t_object	*curr;

	if (*objects == NULL)
	{
		*objects = new;
		return ;
	}
	curr = *objects;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

t_object	*obj_last(t_object *objects)
{
	if (objects == NULL)
		return (NULL);
	while (objects->next)
		objects = objects->next;
	return (objects);
}

