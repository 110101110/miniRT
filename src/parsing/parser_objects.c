/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Must have 4 elements :
// 1. Identifier 'sp'
// 2. Sphere center x,y,z (doubles)
// 3. Sphere diameter (double)
// 4. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_sphere_content(char **content)
{
	if (nb_of_elements(content) != 4)
		return (ft_putstr_fd("Error\nsp: invalid number of elements\n", 2), 0);
	if (!is_identifier(content[0], "sp"))
		return (ft_putstr_fd("Error\nsp: invalid identifier\n", 2), 0);
	if (!is_vec3(content[1]))
		return (ft_putstr_fd("Error\nsp: invalid center\n", 2), 0);
	if (!is_double(content[2]))
		return (ft_putstr_fd("Error\nsp: invalid diameter\n", 2), 0);
	if (!is_rgb(content[3]))
		return (ft_putstr_fd("Error\nsp: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 4 elements :
// 1. Identifier 'pl'
// 2. Plane point x,y,z (doubles)
// 3. Plane normal vector x,y,z (doubles) [-1.0 - 1.0]
// 4. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_plane_content(char **content)
{
	if (nb_of_elements(content) != 4)
		return (ft_putstr_fd("Error\npl: invalid number of elements\n", 2), 0);
	if (!is_identifier(content[0], "pl"))
		return (ft_putstr_fd("Error\npl: invalid identifier\n", 2), 0);
	if (!is_vec3(content[1]))
		return (ft_putstr_fd("Error\npl: invalid point\n", 2), 0);
	if (!is_vec3(content[2]))
		return (ft_putstr_fd("Error\npl: invalid orientation vector\n", 2), 0);
	if (!is_rgb(content[3]))
		return (ft_putstr_fd("Error\npl: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 6 elements :
// 1. Identifier 'cy'
// 2. Cylinder base point x,y,z (doubles)
// 3. Cylinder orientation vector x,y,z (doubles) [-1.0 - 1.0]
// 4. Cylinder diameter (double)
// 5. Cylinder height (double)
// 6. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_cylinder_content(char **content)
{
	if (nb_of_elements(content) != 6)
		return (ft_putstr_fd("Error\ncy: invalid number of elements\n", 2), 0);
	if (!is_identifier(content[0], "cy"))
		return (ft_putstr_fd("Error\ncy: invalid identifier\n", 2), 0);
	if (!is_vec3(content[1]))
		return (ft_putstr_fd("Error\ncy: invalid base point\n", 2), 0);
	if (!is_vec3(content[2]))
		return (ft_putstr_fd("Error\ncy: invalid orientation vector\n", 2), 0);
	if (!is_double(content[3]))
		return (ft_putstr_fd("Error\ncy: invalid diameter\n", 2), 0);
	if (!is_double(content[4]))
		return (ft_putstr_fd("Error\ncy: invalid height\n", 2), 0);
	if (!is_rgb(content[5]))
		return (ft_putstr_fd("Error\ncy: invalid RGB\n", 2), 0);
	return (1);
}

// Dispatches parsing based on object identifier.
static int	parse_single_object(char **content)
{
	if (is_identifier(content[0], "sp"))
		return (parse_sphere_content(content));
	if (is_identifier(content[0], "pl"))
		return (parse_plane_content(content));
	if (is_identifier(content[0], "cy"))
		return (parse_cylinder_content(content));
	return (0);
}

// Parses each object entry in parser->obj.
int	parse_object_content(t_parser *parser)
{
	t_object	*current;

	current = parser->lst;
	while (current)
	{
		if (!current->content || !parse_single_object(current->content))
			return (0);
		current = current->next;
	}
	return (1);
}
