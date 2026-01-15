/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:24 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 16:25:32 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

double	hit_sphere(t_ray ray, t_vec3 center, double radius)
{
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		disc;

	oc = vec_sub(ray.origin, center);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0 * vec_dot(oc, ray.dir);
	c = vec_dot(oc, oc) - radius * radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1.0);
	return ((-b - sqrt(disc)) / (2.0 * a));
}
