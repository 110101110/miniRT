/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:14:03 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 15:33:24 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Handle the "Edge Case": If camera points exactly Up or Down,
// vec_cross returns (0,0,0). We'll add a fix for this during parsing.

void	init_camera(t_camera *cam, double aspect_ratio)
{
	double	theta;
	t_vec3	world_up;

	theta = (cam->fov * M_PI) / 180.0;
	cam->viewport_w = 2.0 * tan(theta / 2.0);
	cam->viewport_h = cam->viewport_w / aspect_ratio;
	world_up = vec_init(0, 1, 0);
	cam->right = vec_cross(cam->dir, world_up);
	cam->right = vec_normalize(cam->right);
	cam->up = vec_cross(cam->right, cam->dir);
	cam->up = vec_normalize(cam->up);
}
