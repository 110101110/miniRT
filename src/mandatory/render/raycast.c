/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:56:03 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 18:29:44 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// get ray through each pixel
// (x,y) pixel coordinate
t_ray	get_ray(t_camera *cam, double x, double y)
{
	t_ray	ray;
	t_vec3	dir;
	double	u;
	double	v;

	u = ((x + 0.5) / (double)WIDTH) * 2.0 - 1.0;
	v = ((y + 0.5) / (double)HEIGHT) * 2.0 - 1.0;
	v *= -1;
	u *= (cam->viewport_w / 2.0);
	v *= (cam->viewport_h / 2.0);
	dir = vec_init(0, 0, 0);
	dir = vec_add(dir, vec_scale(cam->right, u));
	dir = vec_add(dir, vec_scale(cam->up, v));
	dir = vec_add(cam->dir, dir);
	ray.origin = cam->origin;
	ray.dir = vec_normalize(dir);
	return (ray);
}
