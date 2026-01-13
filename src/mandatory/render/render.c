/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:18:48 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/13 15:05:56 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

void	render_scene(t_data *data)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// Simple math to make a color gradient based on position
			// r = varies with X, g = varies with Y, b = constant
			int r = (int)((double)x / WIDTH * 255.0);
			int g = (int)((double)y / HEIGHT * 255.0);
			int b = 100;

			// Re-use your math library if you want, or manual shift:
			color = (r << 16) | (g << 8) | b;

			img_pix_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}

	// Push the whole image to the window at oncem
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
