#include "structures.h"
#include <stdlib.h>

t_object	*object(t_object_type type, void *element)
{
	t_object *new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->radius = radius;
	sphere->radius2 = radius * radius;
	return (sphere);
}

void	obj_add(t_object **objects, t_object *new)
{
	t_object *curr;

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

