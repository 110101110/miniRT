/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/21 18:05:27 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

char	**copy_file_to_array(char *filename)
{
	int		fd;
	char	*line;
	char	**file;
	int		line_count;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_count = 0;
	while (get_next_line(fd))
		line_count++;
	close(fd);
	file = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!file)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file[i++] = line;
	}
	file[i] = NULL;
	close(fd);
	return (file);
}

int	parse_file(char *filename)
{
	(void)filename;
	return (1);
}

int	parse(int ac, char **av, t_data *data)
{
	char	**file;

	if (!parse_arguments(ac, av))
		return (0);
	file = copy_file_to_array(av[1]);
	if (!file)
		return (0);
	if (!parse_file(av[1]))
		return (0);
	printf("Parsing successful.\n");
	print_tab(file);
	return (1);
	(void)data;
}
