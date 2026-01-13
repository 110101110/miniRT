/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:37:35 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/13 00:05:31 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_tool.h"

double	vec_dot(t_vec3 v1, t_vec3 v2)
{
	double	res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vec3	vec_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	//xyz
	res.x = v1.y * v2.z - v1.z * v2.y;
	// yzx
	res.y = v1.z * v2.x - v1.x * v2.z;
	// zxy
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

double	vec_len(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}

//convert vector to unit vector
t_vec3	vec_normalize(t_vec3 v)
{
	double	len;
	t_vec3	res;

	len = vec_len(v);
	if (len == 0)
	{
		res.x = 0;
		res.y = 0;
		res.z = 0;
		return (res);
	}
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}

