/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:18:48 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 17:08:56 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

int	ray_to_color(t_vec3 vec)
{
	t_vec3	color;

	color.x = 0.5 * (vec.x + 1.0);
	color.y = 0.5 * (vec.y + 1.0);
	color.z = 0.5 * (vec.z + 1.0);
	return (color_to_int(color));
}

static int	trace_ray(t_ray ray, t_data *data)
{
	double	t;
	t_vec3	hit_p;
	t_vec3	normal;
	t_vec3	rgb;
	t_sphere sp;

	sp.center = vec_init(0, 0, -5);
	sp.diameter = 4.0;
	sp.color = vec_init(255, 0, 0);
	t = hit_sphere(ray, sp.center, sp.diameter / 2.0);
	if (t > 0)
	{
		hit_p = vec_add(ray.origin, vec_scale(ray.dir, t));
		normal = vec_normalize(vec_sub(hit_p, sp.center));
		rgb = apply_lighting(&sp, hit_p, normal, data);
		return (color_to_int(normal));
	}
	return (0xFFFFFF);
}

void	render_scene(t_data *data)
{
	int x;
	int y;
	t_ray ray;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = get_ray(&data->cam, (double)x, (double)y);
			img_pix_put(&data->img, x, y, trace_ray(ray, data));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
