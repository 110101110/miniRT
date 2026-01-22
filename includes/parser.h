/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:42 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/22 21:23:28 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# include "minirt.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
#include <limits.h>

typedef struct s_parser
{
	char		**ambient;
	char		**camera;
	char		**light;
	t_list		*obj;
}	t_parser;

int		parse(int ac, char **av, t_data *data);
char	*get_next_line(int fd);
int		parse_arguments(int ac, char **av);
void	print_tab(char **tab);

#endif