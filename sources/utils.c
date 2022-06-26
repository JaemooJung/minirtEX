/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:23:37 by jaemung           #+#    #+#             */
/*   Updated: 2022/06/26 13:35:50 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//벡터3 생성자
t_vec3		vec3(double x, double y, double z)
{
	t_vec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

//포인트3 생성자
t_point3	point3(double x, double y, double z)
{
	t_point3 point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

//색상3 생성자
t_point3	color3(double r, double g, double b)
{
	t_color3 color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

int encode_color(t_color3 color)
{
	int r;
	int g;
	int b;

	r = (int)(color.x * 255.999);
	g = (int)(color.y * 255.999);
	b = (int)(color.z * 255.999);
	return ((r << 16) | (g << 8) | b);
}
