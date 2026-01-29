/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:21:46 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 15:38:50 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	dst = img->pxl_ptr + offset;
	*(unsigned int *)dst = color;
}
