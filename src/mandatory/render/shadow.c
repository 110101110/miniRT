/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:17:15 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 18:19:16 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	in_shadow(t_data *data, t_vec3 hit_p, t_vec3 normal)
{
	t_ray	shadow_ray;
	t_vec3	light_dir;
	double	light_t;
	double	t;

	light_dir = vec_sub(data->light.origin, hit_p);
	light_t = vec_len(light_dir);
	shadow_ray.origin = vec_add(hit_p, vec_scale(normal, EPSILON));
	shadow_ray.dir = vec_normalize(light_dir);
	t = hit_sphere(shadow_ray, data->sp);
	if (t > EPSILON && t < light_t)
		return (true);
	t = hit_plane(shadow_ray, data->pl);
	if (t > EPSILON && t < light_t)
		return (true);
	t = hit_cylinder(shadow_ray, data->cy, NULL);
	if (t > EPSILON && t < light_t)
		return (true);
	return (false);
}
