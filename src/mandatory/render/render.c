/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:18:48 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/14 13:17:36 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

//debug function
int	ray_to_color(t_ray ray)
{
	t_vec3	color;

	// Map -1..1 range to 0..1 range
	color.x = 0.5 * (ray.dir.x + 1.0);
	color.y = 0.5 * (ray.dir.y + 1.0);
	color.z = 0.5 * (ray.dir.z + 1.0);
	return (color_to_int(color));
}

void	render_scene(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_ray(&data->cam, x, y);
			color = ray_to_color(ray);
			img_pix_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
