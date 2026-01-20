/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/20 13:17:43 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"
#include <fcntl.h>
#include <unistd.h>

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
}

int	check_file_exists(char *filename)
{
	int		fd;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		read(fd, buffer, 1);
		close(fd);
		return (1);
	}
	return (0);
}

int	parse_arguments(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 4) != 0)
		return (0);
	if (ft_strlen(av[1]) < 4)
		return (0);
	if (!check_file_exists(av[1]))
		return (0);
	return (1);
}

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
	char	**file;

	file = copy_file_to_array(filename);
	if (!file)
		return (0);
	return (1);
}

int	parse(int ac, char **av)
{
	if (!parse_arguments(ac, av))
		return (0);
	if (!parse_file(av[1]))
		return (0);
	printf("Parsing successful.\n");
	return (1);
}
