/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:18:48 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/28 19:01:10 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"
#include <math.h>

static int	trace_ray(t_ray ray, t_data *data)
{
	t_object	*curr;
	t_hit		tmp;
	t_hit		close;

	close.t = INFINITY;
	curr = data->obj;
	while (curr)
	{
		tmp.t = hit_object(ray, curr, &tmp.n);
		if (tmp.t > EPSILON && tmp.t < close.t)
		{
			close.n = tmp.n;
			close.t = tmp.t;
			close.rgb = curr->color;
		}
		curr = curr->next;
	}
	if (close.t == INFINITY)
		return (0xf4dc22);
	close.p = get_hit_p(ray, close.t);
	return (color_to_int(apply_lighting(close.rgb, close.p, close.n, data)));
}

void	render_scene(t_data *data)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = get_ray(&data->cam, (double)x, (double)y);
			color = trace_ray(ray, data);
			img_pix_put(&data->img, x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
