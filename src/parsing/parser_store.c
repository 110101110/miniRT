/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Parses an RGB string and stores it as a t_color.
t_color	store_rgb(char *str)
{
	int		value[3];
	char	**rgb_values;
	t_color	color;

	rgb_values = ft_split(str, ',');
	if (!rgb_values)
		return (color_init(0, 0, 0));
	value[0] = (unsigned char)ft_atoi(rgb_values[0]);
	value[1] = (unsigned char)ft_atoi(rgb_values[1]);
	value[2] = (unsigned char)ft_atoi(rgb_values[2]);
	color = color_init(value[0], value[1], value[2]);
	free_tab(rgb_values);
	return (color);
}

// Stores ambient lighting data into the runtime scene struct.
int	store_ambient_lightning_data(char **ambient, t_ambient *data)
{
	data->ratio = ft_atof(ambient[1]);
	data->color = store_rgb(ambient[2]);
	return (1);
}

// Parses a vec3 string and stores it into a t_vec3.
t_vec3	store_vec3(char *str)
{
	double	value[3];
	t_vec3	vec;
	char	**vec_values;

	vec_values = ft_split(str, ',');
	if (!vec_values)
		return (vec_init(0, 0, 0));
	value[0] = ft_atof(vec_values[0]);
	value[1] = ft_atof(vec_values[1]);
	value[2] = ft_atof(vec_values[2]);
	vec = vec_init(value[0], value[1], value[2]);
	free_tab(vec_values);
	return (vec);
}

// Stores camera data into the runtime scene struct.
int	store_camera_data(char **camera, t_camera *data)
{
	data->origin = store_vec3(camera[1]);
	data->dir = store_vec3(camera[2]);
	data->fov = ft_atoi(camera[3]);
	return (1);
}

// Add this for bonus :
// if (nb_of_elements(light) == 4)
// 	data->color = store_rgb(light[3]);
// Stores light data into the runtime scene struct.
int	store_light_data(char **light, t_light *data)
{
	data->origin = store_vec3(light[1]);
	data->ratio = ft_atof(light[2]);
	return (1);
}
