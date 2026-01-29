/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 18:26:43 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Top-level file parsing pipeline:
// validate format, split, parse, and range-check.
int	parse_file(char **file, t_parser *parser)
{
	if (!count_mandatory_identifiers(file))
		return (ft_putstr_fd("Error\nproblem with identifier count\n", 2), 0);
	if (!detect_illegal_characters(file))
		return (ft_putstr_fd("Error\nillegal character detected\n", 2), 0);
	if (!one_identifier_per_line(file))
		return (ft_putstr_fd("Error\nproblem with identifiers format\n", 2), 0);
	if (!detect_illegal_object(file))
		return (ft_putstr_fd("Error\nillegal identifier detected\n", 2), 0);
	if (!fill_parser_struct(file, parser))
		return (ft_putstr_fd("Error\nfailed to fill parser struct\n", 2), 0);
	if (!parse_struct_content(parser))
		return (0);
	if (!check_values_ranges(parser))
		return (0);
	return (1);
}

// Stores all parsed entities into the runtime scene struct.
int	store_data(t_parser *parser, t_data *data)
{
	if (!store_ambient_lightning_data(parser->ambient, &data->ambient))
		return (0);
	if (!store_camera_data(parser->camera, &data->cam))
		return (0);
	if (!store_light_data(parser->light, &data->light))
		return (0);
	if (!store_objects_data(&parser->lst, data))
		return (0);
	return (1);
}

// Main parse entrypoint:
// validate arguments, parse file, and populate runtime data.
int	parse(int ac, char **av, t_data *data)
{
	char		**file;
	t_parser	parser;

	if (!parse_arguments(ac, av))
		return (0);
	file = copy_file_to_array(av[1]);
	if (!file)
		return (0);
	ft_bzero(&parser, sizeof(t_parser));
	if (!parse_file(file, &parser))
	{
		free_parser(&parser);
		free_tab(file);
		return (0);
	}
	if (!store_data(&parser, data))
	{
		free_parser(&parser);
		free_tab(file);
		return (0);
	}
	free_parser(&parser);
	free_tab(file);
	return (1);
}
