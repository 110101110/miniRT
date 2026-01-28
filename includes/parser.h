/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:42 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/28 16:56:59 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "float.h"
# include "structs.h"

/* parser_args.c */
int		check_file_exists(char *filename);
int		parse_arguments(int ac, char **av);

/* parser_debug.c */
void	print_tab(char **tab);

/* parser.c */
int		ft_isspace(int c);
double	ft_atof(const char *str);
char	**copy_file_to_array(char *filename);

int		count_mandatory_identifiers(char **file);
int		is_legal(char c);
int		detect_illegal_characters(char **file);
int		one_identifier_per_line(char **file);
int		where_is(char **file, char identifier);

int		fill_ambient_content(char **file, t_parser *parser);
int		fill_camera_content(char **file, t_parser *parser);
int		fill_light_content(char **file, t_parser *parser);
int		fill_obj(char **file, t_parser *parser);
int		fill_parser_struct(char **file, t_parser *parser);

int		detect_illegal_object(char **file);

int		nb_of_elements(char **tab);
int		is_identifier(char *str, char *identifier);
int		is_double(char *str);
int		is_rgb(char *str);
int		is_vec3(char *str);

int		parse_ambient_content(char **ambient);
int		parse_camera_content(char **camera);
int		parse_light_content(char **light);
int		parse_sphere_content(char **content);
int		parse_plane_content(char **content);
int		parse_cylinder_content(char **content);
int		parse_object_content(t_parser *parser);
int		parse_struct_content(t_parser *parser);

int		check_range_double(double value, double min, double max);
int		check_range_int(int value, int min, int max);
int		check_float_overflows(char *str);
int		check_int_overflows(char *str);

int		check_ambient_light_values(t_parser *parser);
int		check_camera_values(t_parser *parser);
int		check_light_values(t_parser *parser);
int		check_values_ranges(t_parser *parser);

int		parse_file(char **file, t_parser *parser);
void	free_parser(t_parser *parser);


/* Provided by libft */
char	*get_next_line(int fd);
void	free_tab(char **str);

#endif
