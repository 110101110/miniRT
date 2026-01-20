/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:06 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/20 16:18:01 by qizhang          ###   ########.fr       */
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
	data.light.origin = vec_init(0,10,-10);
	data.light.ratio = 0.9;
	data.ambient.ratio = 0.3;
	data.ambient.color = color_init(255, 255, 255);
	// hardcode sphere
	data.sp.center = vec_init(0, -2, -10);
	data.sp.diameter = 2.0;
	data.sp.color = color_init(0,0, 255);
	// hardcode plane
	data.pl.point = vec_init(0, -4, 0);
	data.pl.normal = vec_init(0, 1, 0);
	data.pl.color = color_init(200,200,200);
	init_camera(&data.cam, aspect_ratio);
	render_scene(&data);
	mlx_loop(data.mlx);
	return (0);
}
