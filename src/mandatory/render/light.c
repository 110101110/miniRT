/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 01:01:30 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 19:28:34 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// t_vec3	ambient_light();

t_vec3	diffuse_light(t_sphere *sp, t_vec3 hit_p, t_vec3 normal, t_light *light)
{
	t_vec3	light_dir;
	double	dot;
	double intensity;
	t_vec3	res;

	light_dir = vec_normalize(vec_sub(light->origin, hit_p));
	dot = vec_dot(normal, light_dir);
	if (dot < 0)
		return (vec_init(0, 0, 0));
	intensity = dot * light->ratio;
	res = vec_scale(sp->color, intensity);
	return (res);
}

t_vec3	ambient_light(t_sphere *sp, t_ambient *ambient)
{
	t_color	res;
	res = color_mult(sp->color, ambient->color);
	res = vec_scale(res, ambient->ratio);
	return (res);
}

t_vec3	apply_lighting(t_sphere *sp, t_vec3 hit_p, t_vec3 normal, t_data *data)
{
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	final;

	diffuse = diffuse_light(sp, hit_p, normal, &data->light);
	ambient = ambient_light(sp, &data->ambient);
	final = vec_add(ambient, diffuse);
	return (final);
}
