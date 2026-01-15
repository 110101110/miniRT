/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:29:40 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 16:27:50 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "math_tool.h"

typedef struct	s_ambient
{
	double		ratio;
	t_color		color;
}				t_ambient;

typedef struct	s_light
{
	t_vec3		origin;
	double		ratio;
	t_vec3		color;
}				t_light;

typedef	enum	e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_type;

typedef	struct s_object
{
	t_type	type;
	void	*data;
	struct s_object *next;
}	t_object;

typedef struct	s_sphere
{
	t_vec3		center;
	t_color		color;
	double		diameter;
}				t_sphere;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		dir;
}				t_ray;

typedef struct s_camera
{
	t_vec3 origin; // x, y, z coordinates of the viewpoint
	t_vec3 dir;    // orientation vector
	double fov;    // horizontal field of view (angle: 0 - 180)

	t_vec3		up;
	t_vec3		right;
	double		viewport_w;
	double		viewport_h;
}				t_camera;

typedef struct s_img
{
	void		*img_ptr;
	char		*pxl_ptr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_camera	cam;
	t_ray		ray;
	t_object	object;
	t_light		light;
	t_ambient	ambient;
}				t_data;
