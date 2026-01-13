/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:46 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/13 01:50:59 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "math_tool.h"
# include "../mlx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

// # define KEY_ESC 65307 for linux
#  define KEY_ESC 53

typedef struct	s_img{
	void	*img_ptr;
	char	*pxl_ptr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_data{
	void	*mlx;
	void	*win;
	t_img	img;
} t_data;

//init
void	init_mlx(t_data *data);
int		close_window(t_data *data);
//rendering
void	render_scene(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);

#endif
