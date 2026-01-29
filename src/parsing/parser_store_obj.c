/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Allocates and stores a sphere object into the runtime objects list.
int	store_sphere_data(char **content, t_object *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->center = store_vec3(content[1]);
	sphere->diameter = ft_atof(content[2]);
	sphere->color = store_rgb(content[3]);
	fill_node(obj, SPHERE, sphere, sphere->color);
	return (1);
}

// Allocates and stores a plane object into the runtime objects list.
int	store_plane_data(char **content, t_object *obj)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->point = store_vec3(content[1]);
	plane->normal = store_vec3(content[2]);
	plane->normal = vec_normalize(plane->normal);
	plane->color = store_rgb(content[3]);
	fill_node(obj, PLANE, plane, plane->color);
	return (1);
}

// Allocates and stores a cylinder object into the runtime objects list.
int	store_cylinder_data(char **content, t_object *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->center = store_vec3(content[1]);
	cylinder->axis = store_vec3(content[2]);
	cylinder->axis = vec_normalize(cylinder->axis);
	cylinder->diamter = ft_atof(content[3]);
	cylinder->height = ft_atof(content[4]);
	cylinder->color = store_rgb(content[5]);
	fill_node(obj, CYLINDER, cylinder, cylinder->color);
	return (1);
}

// Helper function to store single object data based on identifier.
static int	store_single_object(char **content, t_object *current)
{
	if (is_identifier(content[0], "sp"))
		return (store_sphere_data(content, current));
	else if (is_identifier(content[0], "pl"))
		return (store_plane_data(content, current));
	else if (is_identifier(content[0], "cy"))
		return (store_cylinder_data(content, current));
	return (1);
}

int	store_objects_data(t_object **lst, t_data *data)
{
	t_object	*current;
	char		**content;

	current = *lst;
	while (current)
	{
		content = current->content;
		if (!store_single_object(content, current))
			return (0);
		current = current->next;
	}
	data->obj = *lst;
	return (1);
}
