/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:17:15 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 15:37:03 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	in_shadow(t_data *data, t_vec3 hit_p, t_vec3 normal)
{
	t_object	*curr;
	t_ray		s_ray;
	t_vec3		light_dir;
	double		light_t;
	double		t;

	light_dir = vec_sub(data->light.origin, hit_p);
	light_t = vec_len(light_dir);
	s_ray.origin = vec_add(hit_p, vec_scale(normal, EPSILON));
	s_ray.dir = vec_normalize(light_dir);
	curr = data->obj;
	while (curr)
	{
		t = hit_object(s_ray, curr, NULL);
		if (t > EPSILON && t < light_t)
			return (true);
		curr = curr->next;
	}
	return (false);
}
