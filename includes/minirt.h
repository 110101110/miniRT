/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:04:46 by qizhang           #+#    #+#             */
/*   Updated: 2026/02/07 15:27:11 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_macos/mlx.h"
// # include "../mlx_linux/mlx.h"
# include "math_tool.h"
# include "parser.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

//for linux
// # define KEY_ESC 65307
//for mac
# define KEY_ESC 53

// init win
void		init_mlx(t_data *data);
int			close_window(t_data *data);
// init cam
void		init_camera(t_camera *cam, double aspect_ratio);
// parsing
t_color		store_rgb(char *str);
t_vec3		store_vec3(char *str);
int			store_ambient_lightning_data(char **ambient, t_ambient *data);
int			store_camera_data(char **camera, t_camera *data);
int			store_light_data(char **light, t_light *data);
int			store_sphere_data(char **content, t_object *obj);
int			store_plane_data(char **content, t_object *obj);
int			store_cylinder_data(char **content, t_object *obj);
int			store_objects_data(t_object **lst, t_data *data);
int			store_data(t_parser *parser, t_data *data);
int			parse(int ac, char **av, t_data *data);
// rendering
void		render_scene(t_data *data);
void		img_pix_put(t_img *img, int x, int y, int color);
t_ray		get_ray(t_camera *cam, double x, double y);
// objects
double		hit_object(t_ray r, t_object *obj, t_vec3 *normal);
t_vec3		get_hit_p(t_ray r, double t);
double		hit_sphere(t_ray ray, t_sphere sp, t_vec3 *normal);
double		hit_plane(t_ray ray, t_plane pl, t_vec3 *normal);
double		hit_cylinder(t_ray ray, t_cylinder cy, t_vec3 *normal);
double		hit_disk(t_ray r, t_vec3 center, t_vec3 normal, double radius);
t_vec3		get_cy_normal(t_vec3 hit_p, t_cylinder cy);
// obj struct related
t_object	*obj_new(char **content);
void		fill_node(t_object *node, t_type type, void *data, t_vec3 color);
void		add_obj_back(t_object **lst, t_object *node);
void		free_obj(t_object *lst);
// light
t_vec3		apply_lighting(t_color color, t_vec3 hit_p, t_vec3 normal,
				t_data *data);
bool		in_shadow(t_data *data, t_vec3 hit_p, t_vec3 normal);
//free and clean exit
int			clean_exit(t_data *data);
// debug prints
void		print_parser(t_parser *parse);
void		print_data(t_data *data);

#endif
