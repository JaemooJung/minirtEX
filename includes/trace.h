/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:13:46 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/16 18:28:36 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"
# include "minirt.h"

t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);

t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);

t_bool		hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_sphere(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);

t_color3	phong_lighting(t_scene *scene);
t_color3	point_light_get(t_scene *scene, t_light *light);

#endif
