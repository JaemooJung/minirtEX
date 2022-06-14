/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:13:43 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/14 17:35:38 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"
# include "minirt.h"
# include "trace.h"

t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 origin);

t_sphere	*sphere(t_point3 center, double radius);
t_cylinder	*cylinder(t_point3 center, double radius, t_vec3 dir, double height);
t_object	*object(t_object_type type, void *element, t_color3 albedo);

t_light		*light_point(t_point3 light_origin,
				t_color3 light_color, double bright_ratio);

t_scene		*scene_init(void);
void		draw_scene(t_mlx_info *info);

#endif