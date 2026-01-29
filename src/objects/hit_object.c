/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:32:21 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 15:36:42 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3	get_hit_p(t_ray r, double t)
{
	return (vec_add(r.origin, vec_scale(r.dir, t)));
}

double	hit_disk(t_ray r, t_vec3 center, t_vec3 normal, double radius)
{
	double	t;
	double	denom;
	t_vec3	v;

	denom = vec_dot(normal, r.dir);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vec_dot(vec_sub(center, r.origin), normal) / denom;
	if (t < EPSILON)
		return (-1.0);
	v = vec_sub(get_hit_p(r, t), center);
	if (vec_dot(v, v) <= radius * radius)
		return (t);
	return (-1.0);
}

double	hit_object(t_ray r, t_object *obj, t_vec3 *normal)
{
	if (obj->type == SPHERE)
		return (hit_sphere(r, *(t_sphere *)obj->data, normal));
	if (obj->type == PLANE)
		return (hit_plane(r, *(t_plane *)obj->data, normal));
	if (obj->type == CYLINDER)
		return (hit_cylinder(r, *(t_cylinder *)obj->data, normal));
	return (-1.0);
}
