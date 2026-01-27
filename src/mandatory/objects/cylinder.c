/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:30:07 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 19:44:03 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static double	find_min_t(double t1, double t2, double t3)
{
	double	min;

	min = INFINITY;
	if (t1 > EPSILON && t1 < min)
		min = t1;
	if (t2 > EPSILON && t2 < min)
		min = t2;
	if (t3 > EPSILON && t3 < min)
		min = t3;
	if (min == INFINITY)
		return (-1.0);
	return (min);
}

t_vec3	get_cy_normal(t_vec3 hit_p, t_cylinder cy)
{
	t_vec3	normal;
	t_vec3	axis_p;
	double	m;

	m = vec_dot(vec_sub(hit_p, cy.center), cy.axis);
	if (m > cy.height / 2.0 - EPSILON)
		return (cy.axis);
	if (m < -cy.height / 2.0 + EPSILON)
		return (vec_scale(cy.axis, -1));
	axis_p = vec_add(cy.center, vec_scale(cy.axis, m));
	normal = vec_normalize(vec_sub(hit_p, axis_p));
	return (normal);
}

static void	cylinder_calcu(t_ray r, t_cylinder cy, t_cy_data data)
{
	t_vec3	oc;
	t_vec3	d_v;
	t_vec3	oc_v;

	oc = vec_sub(r.origin, cy.center);
	d_v = vec_sub(r.dir, vec_scale(cy.axis, vec_dot(r.dir, cy.axis)));
	oc_v = vec_sub(oc, vec_scale(cy.axis, vec_dot(oc, cy.axis)));
	data.a = vec_dot(d_v, d_v);
	data.b = 2 * vec_dot(d_v, oc_v);
	data.c = vec_dot(oc_v, oc_v) - (cy.diamter * cy.diamter / 4);
	data.disc = data.b * data.b - 4 * data.a * data.c;
}

double	hit_tube(t_ray ray, t_cylinder cy)
{
	double		t1;
	double		t2;
	double		m1;
	double		m2;
	t_cy_data	data;

	cylinder_calcu(ray, cy, data);
	t1 = (-data.b - sqrt(data.disc)) / (2.0 * data.a);
	t2 = (-data.b + sqrt(data.disc)) / (2.0 * data.a);
	m1 = vec_dot(vec_sub(get_hit_p(ray, t1), cy.center), cy.axis);
	if (t1 > EPSILON && m1 >= -cy.height / 2 && m1 <= cy.height / 2)
		return (t1);
	else
	{
		m2 = vec_dot(vec_sub(get_hit_p(ray, t2), cy.center), cy.axis);
		if (t2 > EPSILON && m2 >= -cy.height / 2 && m2 <= cy.height / 2)
			return (t2);
	}
	return (-1.0);
}

double	hit_cylinder(t_ray ray, t_cylinder cy, t_vec3 *normal)
{
	double	min_t;
	double	t_cy[3];
	t_vec3	c_top;
	t_vec3	c_bot;

	c_top = vec_add(cy.center, vec_scale(cy.axis, cy.height / 2));
	c_bot = vec_sub(cy.center, vec_scale(cy.axis, cy.height / 2));
	t_cy[0] = hit_tube(ray, cy);
	t_cy[1] = hit_disk(ray, c_top, cy.axis, cy.diamter / 2);
	t_cy[2] = hit_disk(ray, c_bot, vec_scale(cy.axis, -1), cy.diamter / 2);
	min_t = find_min_t(t_cy[0], t_cy[1], t_cy[2]);
	if (min_t < 0)
		return (-1.0);
	if (normal)
		*normal = get_cy_normal(get_hit_p(ray, min_t), cy);
	return (min_t);
}
