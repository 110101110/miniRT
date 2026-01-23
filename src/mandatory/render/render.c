/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:18:48 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/23 18:20:54 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static int	trace_ray(t_ray ray, t_data *data)
{
	double	t2;
	t_vec3	hit_p;
	t_vec3	rgb;
	double	t1;
	t_vec3	normal;

	t1 = hit_sphere(ray, data->sp);
	t2 = hit_plane(ray, data->pl);
	if (t1 > 0 && (t1 < t2 || t2 < 0))
	{
		hit_p = vec_add(ray.origin, vec_scale(ray.dir, t1));
		normal = vec_normalize(vec_sub(hit_p, data->sp.center));
		rgb = apply_lighting(data->sp.color, hit_p, normal, data);
		return (color_to_int(rgb));
	}
	if (t2 > 0)
	{
		hit_p = vec_add(ray.origin, vec_scale(ray.dir, t2));
		rgb = apply_lighting(data->pl.color, hit_p, data->pl.normal, data);
		return (color_to_int(rgb));
	}
	return (0xf4dc22);
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
