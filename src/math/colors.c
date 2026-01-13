/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:37:43 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/13 00:05:11 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_tool.h"

t_color	color_init(int r, int g, int b)
{
	t_color	c;

	c.x = (double)r / 255.0;
	c.y = (double)g / 255.0;
	c.z = (double)b / 255.0;
	return (c);
}

t_color	color_mult(t_color c1, t_color c2)
{
	t_color	res;

	res.x = c1.x * c2.x;
	res.y = c1.y * c2.y;
	res.z = c1.z * c2.z;
	return (res);
}

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(c.x * 255.0);
	g = (int)(c.y * 255.0);
	b = (int)(c.z * 255.0);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((0 << 24) | (r << 16) | (g << 8) | b);
}
