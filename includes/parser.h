/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:42 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/17 13:30:49 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define BUFFER_SIZE 32

typedef struct ambient_light
{
	float	ratio;
	int		r;
	int		g;
	int		b;
}           t_ambient_light;

typedef struct cam
{
	t_vec3	origin;
	t_vec3	direction;
	float	fov;
}           t_cam;

typedef struct light
{
	t_vec3	position;
	float	ratio;
	int		r;
	int		g;
	int		b;
}		   t_light;

typedef struct s_parse
{
	t_ambient_light	ambient;
	t_cam			camera;
	t_light			light;
	int		sphere_count;
	int		plane_count;
	int		cylinder_count;
}				t_parse;

int parse(int ac, char **av);
char	*get_next_line(int fd);