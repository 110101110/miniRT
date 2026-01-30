/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/30 00:35:17 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Validates sphere diameter constraints.
static int	check_sphere_values(char **content)
{
	double	val;

	val = ft_atof(content[2]);
	if (!check_float_overflows(content[2]) || val <= 0.0)
		return (ft_putstr_fd("Error\nsp: invalid diameter\n", 2), 0);
	return (1);
}

// Validates plane normal vector constraints.
static int	check_plane_values(char **content)
{
	if (!check_vec3_values(content[2], -1.0, 1.0))
		return (ft_putstr_fd("Error\npl: invalid normal vector value\n", 2), 0);
	return (1);
}

// Validates cylinder axis/diameter/height constraints.
static int	check_cylinder_values(char **content)
{
	double	val;

	if (!check_vec3_values(content[2], -1.0, 1.0))
		return (ft_putstr_fd("Error\ncy: invalid axis vector value\n", 2), 0);
	val = ft_atof(content[3]);
	if (!check_float_overflows(content[3]) || val <= 0.0)
		return (ft_putstr_fd("Error\ncy: invalid diameter\n", 2), 0);
	val = ft_atof(content[4]);
	if (!check_float_overflows(content[4]) || val <= 0.0)
		return (ft_putstr_fd("Error\ncy: invalid height\n", 2), 0);
	return (1);
}

// Validates object-specific numeric constraints after parsing.
static int	check_object_values(t_parser *parser)
{
	t_object	*current;
	char		**content;

	current = parser->lst;
	while (current)
	{
		content = current->content;
		if (!content)
			return (0);
		if (is_identifier(content[0], "sp") && !check_sphere_values(content))
			return (0);
		else if (is_identifier(content[0], "pl")
			&& !check_plane_values(content))
			return (0);
		else if (is_identifier(content[0], "cy")
			&& !check_cylinder_values(content))
			return (0);
		current = current->next;
	}
	return (1);
}

// Check if the values are within their specified ranges
int	check_values_ranges(t_parser *parser)
{
	if (!check_ambient_light_values(parser))
		return (0);
	if (!check_camera_values(parser))
		return (0);
	if (!check_light_values(parser))
		return (0);
	if (!check_object_values(parser))
		return (0);
	return (1);
}
