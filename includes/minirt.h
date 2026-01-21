/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:46 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 01:10:50 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_macos/mlx.h"
# include "math_tool.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
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
double	hit_sphere(t_ray ray, t_vec3 center, double raduis);

// light
t_vec3	apply_lighting(t_sphere *sp, t_vec3 hit_p, t_vec3 normal, t_data *data);
#endif
