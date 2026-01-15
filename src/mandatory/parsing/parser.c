/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/15 13:45:01 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"
#include <fcntl.h>
#include <unistd.h>

int check_file_exists(char *filename)
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

int parse_arguments(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Error: Invalid number of arguments.\n");
        return (0);
    }
    if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 4) != 0)
    {
        printf("Error: Invalid file extension. Expected a .rt file.\n");
        return (0);
    }
    if (ft_strlen(av[1]) < 4)
    {
        printf("Error: Invalid filename.\n");
        return (0);
    }
    if (!check_file_exists(av[1]))
    {
        printf("Error: File does not exist or cannot be opened.\n");
        return (0);
    }
    return (1);
}

int parse(int ac, char **av)
{
    if(!parse_arguments(ac, av))
        return (0);
    printf("Parsing successful.\n");
    return (1);
}
