/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:13:40 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/27 02:34:39 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef int	t_object_type;

# define SP 0
# define CY 1
# define PL 2
# define LIGHT_POINT 10

# define EPSILON 1e-6
# define PI 3.14159265359

typedef int	t_bool;

# define FALSE 0
# define TRUE 1

# define LUMEN 2

typedef struct s_mlx_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx_info;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color3;

typedef struct s_disc
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
}	t_disc;

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

typedef struct s_camera
{
	t_point3	orig;  // 카메라 원점(위치)
	t_vec3		dir;   // 카메라 방향(방향)
	double		focal_len; // focal length
	double		viewport_h;
	double		viewport_w;
	t_vec3		horizontal; // 수평길이 벡터
	t_vec3		vertical; // 수직길이 벡터
	t_point3	left_bottom; // 왼쪽 아래 코너점
}	t_camera;

typedef struct s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
}	t_canvas;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
}	t_hit_record;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo;
}	t_object;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
}	t_sphere;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		dir;
	double		radius;
	double		radius2;
	double		height;
}	t_cylinder;

typedef struct s_plane
{
	t_point3	center;
	t_vec3		dir;
	double		radius;
}	t_plane;

typedef struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
}	t_light;

typedef struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;

#endif