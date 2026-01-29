/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Validates a vec3 string and checks that each component is in [min, max].
int	check_vec3_values(char *vec, double min, double max)
{
	char	**parts;
	int		idx;

	parts = ft_split(vec, ',');
	if (!parts)
		return (0);
	if (nb_of_elements(parts) != 3)
	{
		free_tab(parts);
		return (0);
	}
	idx = 0;
	while (idx < 3)
	{
		if (!is_double(parts[idx]) || !check_float_overflows(parts[idx])
			|| !check_range_double(ft_atof(parts[idx]), min, max))
		{
			free_tab(parts);
			return (0);
		}
		idx++;
	}
	free_tab(parts);
	return (1);
}

// Returns 1 if vec3 is not (0,0,0), else 0.
int	vec3_is_not_zero(char *vec)
{
	char	**parts;
	double	x;
	double	y;
	double	z;

	parts = ft_split(vec, ',');
	if (!parts)
		return (0);
	if (nb_of_elements(parts) != 3)
	{
		free_tab(parts);
		return (0);
	}
	x = ft_atof(parts[0]);
	y = ft_atof(parts[1]);
	z = ft_atof(parts[2]);
	free_tab(parts);
	if (x == 0.0 && y == 0.0 && z == 0.0)
		return (0);
	return (1);
}

// Check ambient lighting ratio [0.0 - 1.0]
int	check_ambient_light_values(t_parser *parser)
{
	if (!check_float_overflows(parser->ambient[1])
		|| !check_range_double(ft_atof(parser->ambient[1]), 0.0, 1.0))
		return (ft_putstr_fd("Error\n\
A: ambient lighting ratio out of range\n",
								2),
				0);
	return (1);
}

// Check camera vector [-1.0 - 1.0]
// Check FOV [0 - 180]
int	check_camera_values(t_parser *parser)
{
	if (!check_vec3_values(parser->camera[2], -1.0, 1.0))
		return (ft_putstr_fd("Error\n\
C: camera orientation vector out of range\n",
								2),
				0);
	if (!vec3_is_not_zero(parser->camera[2]))
		return (ft_putstr_fd("Error\nC: orientation vector is null\n", 2), 0);
	if (!check_int_overflows(parser->camera[3])
		|| !check_range_int(ft_atoi(parser->camera[3]), 0, 180))
		return (ft_putstr_fd("Error\nC: FOV out of range\n", 2), 0);
	return (1);
}

// Check light brightness ratio [0.0 - 1.0]
int	check_light_values(t_parser *parser)
{
	if (!check_float_overflows(parser->light[2])
		|| !check_range_double(ft_atof(parser->light[2]), 0.0, 1.0))
		return (ft_putstr_fd("Error\n\
L: light brightness ratio out of range\n",
								2),
				0);
	return (1);
}
