/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:06 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 16:33:47 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	main(void)
{
	t_data	data;
	double	aspect_ratio;
	t_light	light;

	init_mlx(&data);
	data.cam.origin = vec_init(0, 0, 0);
	data.cam.dir = vec_init(0, 0, -1);
	data.cam.fov = 100.0;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;

	//hardcode for testing ambient and diffuse light
	data.light = light;
	data.light.origin = vec_init(5.0, 5.0, 5.0);
	data.light.ratio = 0.7;
	data.light.color = vec_init(255, 255, 255);
	data.ambient.color = vec_init(0, 0, 200);
	data.ambient.ratio = 0.3;

	init_camera(&data.cam, aspect_ratio);
	render_scene(&data);
	mlx_loop(data.mlx);
	return (0);
}
