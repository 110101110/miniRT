/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:37:13 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 19:00:38 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_tool.h"

t_vec3	vec_init(double x, double y, double z)
{
	t_vec3	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;

	return (new_vec);
}

t_vec3	vec_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;

	return (res);
}

t_vec3 vec_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;

	return (res);
}

t_vec3	vec_scale(t_vec3 v, double s)
{
	t_vec3 res;

	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;

	return (res);
}
