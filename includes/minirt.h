/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:46 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 16:01:40 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_macos/mlx.h"
# include "math_tool.h"
# include "structs.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

// # define KEY_ESC 65307 for linux
# define KEY_ESC 53

// init win
void	init_mlx(t_data *data);
int		close_window(t_data *data);
// init cam
void	init_camera(t_camera *cam, double aspect_ratio);

// rendering
void	render_scene(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
t_ray	get_ray(t_camera *cam, double x, double y);

// objects
t_vec3	get_hit_p(t_ray r, double t);
double	hit_sphere(t_ray ray, t_sphere sp);
double	hit_plane(t_ray ray, t_plane pl);
double	hit_cylinder(t_ray ray, t_cylinder cy, t_vec3 *normal);
t_vec3	get_cy_normal(t_vec3 hit_p, t_cylinder cy);

// light
t_vec3	apply_lighting(t_color color, t_vec3 hit_p, t_vec3 normal,
			t_data *data);
bool	in_shadow(t_data *data, t_vec3 hit_p, t_vec3 normal);
#endif
