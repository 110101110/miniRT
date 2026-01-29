/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Must have 3 elements :
// 1. Identifier 'A'
// 2. Ambient lighting ratio [0.0 - 1.0] (double)
// 3. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_ambient_content(char **ambient)
{
	if (nb_of_elements(ambient) != 3)
		return (ft_putstr_fd("Error\nA: invalid number of elements\n", 2), 0);
	if (!is_identifier(ambient[0], "A"))
		return (ft_putstr_fd("Error\nA: invalid identifier\n", 2), 0);
	if (!is_double(ambient[1]))
		return (ft_putstr_fd("Error\nA: invalid lightning ratio\n", 2), 0);
	if (!is_rgb(ambient[2]))
		return (ft_putstr_fd("Error\nA: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 4 elements :
// 1. Identifier 'C'
// 2. Viewpoint coordinates x,y,z (doubles)
// 3. Orientation vector x,y,z (doubles) [-1.0 - 1.0]
// 4. FOV (integer) [0 - 180]
int	parse_camera_content(char **camera)
{
	if (nb_of_elements(camera) != 4)
		return (ft_putstr_fd("Error\nC: invalid number of elements\n", 2), 0);
	if (!is_identifier(camera[0], "C"))
		return (ft_putstr_fd("Error\nC: invalid identifier\n", 2), 0);
	if (!is_vec3(camera[1]))
		return (ft_putstr_fd("Error\nC: invalid coordinates\n", 2), 0);
	if (!is_vec3(camera[2]))
		return (ft_putstr_fd("Error\nC: invalid orientation vector\n", 2), 0);
	if (!is_int(camera[3]))
		return (ft_putstr_fd("Error\nC: invalid FOV\n", 2), 0);
	return (1);
}

// Must have 3 or 4 elements :
// 1. Identifier 'L'
// 2. Light position x,y,z (doubles)
// 3. Brightness ratio [0.0 - 1.0] (double)
// 4. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_light_content(char **light)
{
	if (nb_of_elements(light) != 3 && nb_of_elements(light) != 4)
		return (ft_putstr_fd("Error\nL: invalid number of elements\n", 2), 0);
	if (!is_identifier(light[0], "L"))
		return (ft_putstr_fd("Error\nL: invalid identifier\n", 2), 0);
	if (!is_vec3(light[1]))
		return (ft_putstr_fd("Error\nL: invalid light position\n", 2), 0);
	if (!is_double(light[2]))
		return (ft_putstr_fd("Error\nL: invalid brightness ratio\n", 2), 0);
	if (nb_of_elements(light) == 4 && !is_rgb(light[3]))
		return (ft_putstr_fd("Error\nL: invalid RGB\n", 2), 0);
	return (1);
}

// Parse each content of the parser struct
int	parse_struct_content(t_parser *parser)
{
	if (!parse_ambient_content(parser->ambient))
		return (0);
	if (!parse_camera_content(parser->camera))
		return (0);
	if (!parse_light_content(parser->light))
		return (0);
	if (!parse_object_content(parser))
		return (0);
	return (1);
}
