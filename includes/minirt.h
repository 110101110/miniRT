/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:46 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 13:25:40 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_macos/mlx.h"
# include "math_tool.h"
# include "parser.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

// # define KEY_ESC 65307 for linux
# define KEY_ESC 53
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
}				t_data;

// init win
void			init_mlx(t_data *data);
int				close_window(t_data *data);
// init cam
void			init_camera(t_camera *cam, double aspect_ratio);

// rendering
void			render_scene(t_data *data);
void			img_pix_put(t_img *img, int x, int y, int color);
t_ray			get_ray(t_camera *cam, double x, double y);

#endif
