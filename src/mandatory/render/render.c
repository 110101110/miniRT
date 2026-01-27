/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:18:48 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 17:38:05 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"
#include <math.h>

static int	trace_ray(t_ray ray, t_data *data)
{
	double	t;
	double	t_tmp;
	t_vec3	rgb;
	t_vec3	normal;
	t_vec3	normal_cy;

	t = INFINITY;
	//sphere
	t_tmp = hit_sphere(ray, data->sp);
	if (t_tmp > EPSILON && t_tmp < t)
	{
		t = t_tmp;
		normal = vec_normalize(vec_sub(get_hit_p(ray, t), data->sp.center));
		rgb = data->sp.color;
	}
	//plane
	t_tmp = hit_plane(ray, data->pl);
	if (t_tmp > EPSILON && t_tmp < t)
	{
		t = t_tmp;
		normal = data->pl.normal;
		rgb = data->pl.color;
	}
	//cylinder
	t_tmp = hit_cylinder(ray, data->cy, &normal_cy);
	if (t_tmp > EPSILON && t_tmp < t)
	{
		t = t_tmp;
		rgb = data->cy.color;
		normal = normal_cy;
	}
	if (t < INFINITY)
		return (color_to_int(apply_lighting(rgb, get_hit_p(ray, t), normal, data)));
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
