/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:24 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 19:06:50 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

double	hit_sphere(t_ray ray, t_sphere sp, t_vec3 *normal)
{
	t_vec3	oc;
	double	abc[3];
	double	disc;
	double	t;

	oc = vec_sub(ray.origin, sp.center);
	abc[0] = vec_dot(ray.dir, ray.dir);
	abc[1] = 2.0 * vec_dot(oc, ray.dir);
	abc[2] = vec_dot(oc, oc) - (sp.diameter * sp.diameter / 4);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (-1.0);
	t = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		return (-1.0);
	if (normal)
		*normal = vec_normalize(vec_sub(get_hit_p(ray, t), sp.center));
	return (t);
}
