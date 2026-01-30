/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:42 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/30 01:11:46 by kevisout         ###   ########.fr       */
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
int		parse_file(char **file, t_parser *parser);
int		store_data(t_parser *parser, t_data *data);
int		parse(int ac, char **av, t_data *data);

/* parser_utils.c */
int		ft_isspace(int c);
double	ft_atof(const char *str);
int		nb_of_elements(char **tab);
int		is_identifier(char *str, char *identifier);
int		is_double(char *str);

/* parser_file.c */
char	**copy_file_to_array(char *filename);

/* parser_split.c */
char	**split_rt_fields(const char *line);

/* parser_validate.c */
int		count_mandatory_identifiers(char **file);
int		is_legal(char c);
int		detect_illegal_characters(char **file);
int		where_is(char **file, char identifier);

/* parser_validate2.c */
int		one_identifier_per_line(char **file);
int		detect_illegal_object(char **file);

/* parser_fill.c */
int		fill_ambient_content(char **file, t_parser *parser);
int		fill_camera_content(char **file, t_parser *parser);
int		fill_light_content(char **file, t_parser *parser);
int		fill_parser_struct(char **file, t_parser *parser);

/* parser_fill_obj.c */
int		fill_obj(char **file, t_parser *parser);

/* parser_types.c */
int		is_rgb(char *str);
int		is_vec3(char *str);
int		is_int(char *str);

/* parser_content.c */
int		parse_ambient_content(char **ambient);
int		parse_camera_content(char **camera);
int		parse_light_content(char **light);
int		parse_struct_content(t_parser *parser);

/* parser_objects.c */
int		parse_sphere_content(char **content);
int		parse_plane_content(char **content);
int		parse_cylinder_content(char **content);
int		parse_object_content(t_parser *parser);

/* parser_range.c */
int		check_range_double(double value, double min, double max);
int		check_range_int(int value, int min, int max);
int		check_float_overflows(char *str);
int		check_int_overflows(char *str);

/* parser_check.c */
int		check_vec3_values(char *vec, double min, double max);
int		check_ambient_light_values(t_parser *parser);
int		check_camera_values(t_parser *parser);
int		check_light_values(t_parser *parser);

/* parser_check_obj.c */
int		check_values_ranges(t_parser *parser);

/* parser_store.c */
t_color	store_rgb(char *str);
int		store_ambient_lightning_data(char **ambient, t_ambient *data);
t_vec3	store_vec3(char *str);
int		store_camera_data(char **camera, t_camera *data);
int		store_light_data(char **light, t_light *data);

/* parser_store_obj.c */
int		store_sphere_data(char **content, t_object *obj);
int		store_plane_data(char **content, t_object *obj);
int		store_cylinder_data(char **content, t_object *obj);
int		store_objects_data(t_object **lst, t_data *data);

/* parser_free.c */
void	free_tab(char **tab);
void	free_parser(t_parser *parser);

#endif
