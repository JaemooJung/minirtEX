#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_h;
	int		win_w;
}	t_info;


typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

typedef struct s_camera
{
	t_point3	orig;  // 카메라 원점(위치)
	double		viewport_h; // 뷰포트 세로길이
	double		viewport_w; // 뷰포트 가로길이
	t_vec3		horizontal; // 수평길이 벡터
	t_vec3		vertical; // 수직길이 벡터
	double		focal_len; // focal length
	t_point3	left_bottom; // 왼쪽 아래 코너점
} t_camera;

typedef struct s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
} t_canvas;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
} t_sphere;

typedef int	t_bool;

# define FALSE 0
# define TRUE 1

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
} t_hit_record;

typedef int t_object_type;

# define SP 0

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
} t_object;

#endif