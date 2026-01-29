/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:06 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 16:23:40 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int ac, char **av)
{
	t_data	data;
	double	aspect_ratio;

	if (parse(ac, av, &data) == 0)
		return (1);
	// print_data(&data);
	init_mlx(&data);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	init_camera(&data.cam, aspect_ratio);
	render_scene(&data);
	mlx_loop(data.mlx);
	return (0);
}
