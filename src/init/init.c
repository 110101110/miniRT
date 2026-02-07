/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:12:07 by qizhang           #+#    #+#             */
/*   Updated: 2026/02/07 15:29:21 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}

int	close_window(t_data *data)
{
	clean_exit(data);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	// mlx_destroy_display is only available on linux
	// mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
	{
		free(data->mlx);
		exit(1);
	}
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.pxl_ptr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, key_hook, data);
}
