/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:07:19 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 19:06:54 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

double	hit_plane(t_ray ray, t_plane pl, t_vec3 *normal)
{
	double	t;
	double	denom;
	t_vec3	oc;

	denom = vec_dot(pl.normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	oc = vec_sub(pl.point, ray.origin);
	t = vec_dot(oc, pl.normal) / denom;
	if (normal)
		*normal = pl.normal;
	return (t);
}
