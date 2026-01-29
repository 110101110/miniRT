/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:29:40 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 18:49:25 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_tool.h"

typedef struct s_ambient
{
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_light
{
	t_vec3			origin;
	double			ratio;
	// t_vec3		color; not needed in mandatory
}					t_light;

typedef struct s_sphere
{
	t_vec3			center;
	t_color			color;
	double			diameter;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	double			diamter;
	double			height;
	t_color			color;
}					t_cylinder;

typedef struct s_cy_data
{
	double			a;
	double			b;
	double			c;
	double			disc;
}					t_cy_data;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}					t_type;

typedef struct s_object
{
	char			**content;
	t_type			type;
	void			*data;
	t_vec3			color;
	struct s_object	*next;
}					t_object;

typedef struct s_hit
{
	double			t;
	t_vec3			p;
	t_vec3			n;
	t_color			rgb;
}					t_hit;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			dir;
}					t_ray;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	dir;
	double	fov;

	t_vec3	up;
	t_vec3	right;
	double	viewport_w;
	double	viewport_h;
}					t_camera;

typedef struct s_img
{
	void			*img_ptr;
	char			*pxl_ptr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_parser
{
	char			**ambient;
	char			**camera;
	char			**light;
	t_object		*lst;
}					t_parser;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_camera		cam;
	t_ray			ray;
	t_object		*obj;
	t_light			light;
	t_ambient		ambient;
}					t_data;
