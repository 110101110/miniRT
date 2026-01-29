/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:17:41 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 15:32:45 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_TOOL_H
#define MATH_TOOL_H

# include <math.h>

# define EPSILON 1e-6

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef t_vec3 t_color;

// vector math functions
t_vec3	vec_init(double x, double y, double z);
t_vec3	vec_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec_scale(t_vec3 v, double s);

double	vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec_cross(t_vec3 v1, t_vec3 v2);
t_vec3	vec_normalize(t_vec3 v);
double	vec_len(t_vec3 v);

// color related functions
t_color	color_init(int r, int g, int b);
t_color	color_mult(t_color c1, t_color c2);
int		color_to_int(t_color c);

#endif
