/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:52:20 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/28 19:08:28 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_parser(t_parser *parse)
{
	t_object	*current;
	int			i;

	printf("--- PARSER DEBUG ---\n");
	printf("Ambient: %s, %s\n", parse->ambient[0], parse->ambient[1]);
	printf("Camera:  %s, %s, %s\n", parse->camera[0], parse->camera[1],
		parse->camera[2]);
	printf("Light:   %s, %s, %s\n", parse->light[0], parse->light[1],
		parse->light[2]);
	printf("\n--- OBJECT LIST ---\n");
	current = parse->lst;
	i = 0;
	while (current)
	{
		printf("Object [%d]: ", i++);
		if (current->content)
			print_tab(current->content);
		current = current->next;
	}
	printf("--------------------\n");
}

void	print_data(t_data *data)
{
	t_object	*obj;
	t_sphere	*s;
	t_plane		*p;
	t_cylinder	*c;

	printf("--- STORAGE DEBUG ---\n");
	printf("Ambient ratio: %f, color: (%f, %f, %f)\n", data->ambient.ratio,
		data->ambient.color.x, data->ambient.color.y, data->ambient.color.z);
	printf("Camera: origin:(%f, %f, %f), dir:(%f, %f, %f), fov: %f\n",
		data->cam.origin.x, data->cam.origin.y, data->cam.origin.z,
		data->cam.dir.x, data->cam.dir.y, data->cam.dir.z, data->cam.fov);
	printf("Light: ratio: %f, origin: (%f, %f, %f)\n", data->ambient.ratio,
		data->light.origin.x, data->light.origin.y, data->light.origin.z);
	printf("\n--- OBJECT LIST ---\n");
	obj = data->obj;
	int i = 0;
	while (obj)
	{
		printf("Object [%d]: ", i++);
		if (obj->type == SPHERE)
		{
			s = (t_sphere *)obj->data;
			printf("Sphere\n\tCenter: (%f, %f, %f)\n\tDiameter: %f\n",
				s->center.x, s->center.y, s->center.z, s->diameter);
		}
		else if (obj->type == PLANE)
		{
			p = (t_plane *)obj->data;
			printf("Plane\n\tPoint: (%f, %f, %f)\n\tNormal: (%f, %f, %f)\n",
				p->point.x, p->point.y, p->point.z, p->normal.x, p->normal.y,
				p->normal.z);
		}
		else if (obj->type == CYLINDER)
		{
			c = (t_cylinder *)obj->data;
			printf("Cylinder\n\tCenter: (%f, %f, %f)\n\tAxis: (%f, %f,%f)\n\tDia: %f, Height: %f\n", c->center.x, c->center.y,
				c->center.z, c->axis.x, c->axis.y, c->axis.z, c->diamter,
				c->height);
		}
		printf("\tColor: (%f, %f, %f)\n\n", obj->color.x, obj->color.y,
			obj->color.z);
		obj = obj->next;
	}
	printf("--------------------\n");
}
