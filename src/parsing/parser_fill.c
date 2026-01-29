/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Go to the line where 'A' is located and split its content in parser->ambient
int	fill_ambient_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'A');
	if (line == -1)
		return (0);
	parser->ambient = split_rt_fields(file[line]);
	if (!parser->ambient)
		return (0);
	return (1);
}

// Same for 'C'
int	fill_camera_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'C');
	if (line == -1)
		return (0);
	parser->camera = split_rt_fields(file[line]);
	if (!parser->camera)
		return (0);
	return (1);
}

// Same for 'L'
int	fill_light_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'L');
	if (line == -1)
		return (0);
	parser->light = split_rt_fields(file[line]);
	if (!parser->light)
		return (0);
	return (1);
}

// Fill the parser struct with all its content
int	fill_parser_struct(char **file, t_parser *parser)
{
	if (!fill_ambient_content(file, parser))
		return (0);
	if (!fill_camera_content(file, parser))
		return (0);
	if (!fill_light_content(file, parser))
		return (0);
	if (!fill_obj(file, parser))
		return (0);
	return (1);
}
