/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:42 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/22 19:37:52 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# include "minirt.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>

// typedef struct s_obj
// {
// 	t_type		type;
// 	char		**content;
// 	struct s_obj *next;
// }	t_obj;

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