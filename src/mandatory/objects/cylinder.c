/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:30:07 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 18:19:39 by qizhang          ###   ########.fr       */
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

double	hit_tube(t_ray ray, t_cylinder cy)
{
	double	t1;
	double	t2;
	double	t_res;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	m1;
	double	m2;
	t_vec3	oc;
	t_vec3	d_v;
	t_vec3	oc_v;

	oc = vec_sub(ray.origin, cy.center);
	d_v = vec_sub(ray.dir, vec_scale(cy.axis, vec_dot(ray.dir, cy.axis)));
	oc_v = vec_sub(oc, vec_scale(cy.axis, vec_dot(oc, cy.axis)));
	a = vec_dot(d_v, d_v);
	b = 2 * vec_dot(d_v, oc_v);
	c = vec_dot(oc_v, oc_v) - (cy.diamter * cy.diamter / 4);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1.0);
	t1 = (-b - sqrt(disc)) / (2.0 * a);
	t2 = (-b + sqrt(disc)) / (2.0 * a);
	t_res = -1.0;
	m1 = vec_dot(vec_sub(get_hit_p(ray, t1), cy.center), cy.axis);
	if (t1 > EPSILON && m1 >= -cy.height / 2 && m1 <= cy.height / 2)
		t_res = t1;
	else
	{
		m2 = vec_dot(vec_sub(get_hit_p(ray, t2), cy.center), cy.axis);
		if (t2 > EPSILON && m2 >= -cy.height / 2 && m2 <= cy.height / 2)
			t_res = t2;
	}
	return (t_res);
}

double	hit_cylinder(t_ray ray, t_cylinder cy, t_vec3 *normal)
{
	double	min_t;
	double	t_tube;
	double	t_top;
	double	t_bot;
	t_vec3	c_top;
	t_vec3	c_bot;

	c_top = vec_add(cy.center, vec_scale(cy.axis, cy.height / 2));
	c_bot = vec_sub(cy.center, vec_scale(cy.axis, cy.height / 2));
	t_tube = hit_tube(ray, cy);
	t_top = hit_disk(ray, c_top, cy.axis, cy.diamter / 2);
	t_bot = hit_disk(ray, c_bot, vec_scale(cy.axis, -1), cy.diamter / 2);
	min_t = find_min_t(t_tube, t_top, t_bot);
	if (min_t < 0)
		return (-1.0);
	if (normal)
		*normal = get_cy_normal(get_hit_p(ray, min_t), cy);
	return (min_t);
}
