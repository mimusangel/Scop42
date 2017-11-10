/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:06:17 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 09:28:10 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		scop_obj_count_check(t_scop *scop, t_array *arr)
{
	size_t	i;
	char	*line;
	t_array	*check;

	i = -1;
	while (++i < arr->len)
	{
		line = arr->data[i];
		check = array_bystr(line, ' ', 1);
		if (ft_strstart(line, "v ") && check->len == 4)
			scop->obj.vcount += 1;
		else if (ft_strstart(line, "f ")
			&& (check->len == 4 || check->len == 5))
			scop->obj.tcount += check->len - 3;
		if (ft_strstart(line, "f ") && (check->len < 4 || check->len > 5))
			ft_putlog("Invalid line! Line: ", line);
		if (ft_strstart(line, "v ") && check->len != 4)
			return (ft_putlog("Invalid line! Line: ", line));
		array_free(&check);
	}
	return (1);
}

void			scop_init_obj(t_scop *scop)
{
	scop->obj.vcount = 0;
	scop->obj.tcount = 0;
	scop->obj.v = NULL;
	scop->obj.buff = NULL;
	scop->obj.cx = 0.f;
	scop->obj.cy = 0.f;
	scop->obj.cz = 0.f;
	scop->obj.pos.x = 0.f;
	scop->obj.pos.y = 0.f;
	scop->obj.pos.z = 6.f;
	scop->obj.rot.x = 0.f;
	scop->obj.rot.y = 0.f;
	scop->obj.rot.z = 0.f;
}

int				scop_load_obj(t_scop *scop, char *path)
{
	char	*file_content;
	t_array	*array_file;

	file_content = scop_file_content(path);
	if (ft_strlen(file_content) <= 0)
		return (ft_putlog("Empty file!\n", path));
	array_file = array_bystr(file_content, '\n', 1);
	if (file_content)
		free(file_content);
	if (array_file->len <= 1)
		return (ft_putlog("Not valid file!\n", path));
	if (!scop_obj_count_check(scop, array_file))
		return (0);
	scop->obj.v = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.vcount * 3);
	if (!scop->obj.v)
		return (ft_putlog("Error malloc: ", "vertex array"));
	scop->obj.buff = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	if (!scop->obj.buff)
		return (ft_putlog("Error malloc: ", "buffer"));
	if (!scop_obj_parser(scop, array_file))
		return (0);
	free(array_file);
	if (scop->obj.v)
		free(scop->obj.v);
	return (1);
}

void			scop_unload_obj(t_scop *scop)
{
	scop->obj.vcount = 0;
	scop->obj.tcount = 0;
	if (scop->obj.buff)
		free(scop->obj.buff);
}

void			scop_obj_color(t_scop *scop)
{
	size_t	i;
	size_t	j;
	float	color;

	i = -1;
	while (++i < scop->obj.tcount)
	{
		color = 0.1f + ((float)rand() / (float)(RAND_MAX)) * 0.8f;
		j = -1;
		while (++j < 9)
			scop->obj.buff[i * 9 + j] = color;
	}
}
