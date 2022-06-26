/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:13:43 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/26 17:19:34 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"
# include "minirt.h"
# include "trace.h"

t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 orig, t_vec3 dir, double fov);

t_sphere	*sphere(t_point3 center, double radius);
t_cylinder	*cylinder(t_point3 center, double radius, t_vec3 dir, double height);
void		attach_cy_cap(t_object **objs, t_object *cy_);
t_plane		*plane(t_point3 center, t_vec3 dir, double radius);
t_object	*object(t_object_type type, void *element, t_color3 albedo);

t_light		*light_point(t_point3 light_origin,
				t_color3 light_color, double bright_ratio);

t_scene		*scene_init(void);
void		draw_scene(t_mlx_info *info);

#endif