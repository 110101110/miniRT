/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:06 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/23 17:33:35 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	main(void)
{
	t_data	data;
	double	aspect_ratio;

	init_mlx(&data);
	data.cam.origin = vec_init(0, 0, 0);
	data.cam.dir = vec_normalize(vec_init(0, 0, -1));
	data.cam.fov = 60;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data.light.origin = vec_init(-5, 0, -5);
	data.light.ratio = 0.9;
	data.ambient.ratio = 0.2;
	data.ambient.color = color_init(255, 255, 255);
	// hardcode sphere
	data.sp.center = vec_init(0, 0, -8);
	data.sp.diameter = 4;
	data.sp.color = color_init(255,255, 255);
	// hardcode plane
	data.pl.point = vec_init(0, -5, 0);
	data.pl.normal = vec_init(0, 1, 0);
	data.pl.color = color_init(100, 100, 255);
	init_camera(&data.cam, aspect_ratio);
	render_scene(&data);
	mlx_loop(data.mlx);
	return (0);
}
