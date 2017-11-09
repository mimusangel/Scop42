/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:06:17 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 17:19:26 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t	scop_obj_count_arg(char *line)
{
	size_t i;

	i = 0;
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	while (*line)
	{
		while (*line && *line != ' ' && *line != '\t' && *line != '\n')
			line++;
		i++;
		while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
			line++;
	}
	return (i);
}

static void		scop_obj_count(t_scop *scop, t_array *arr)
{
	size_t	i;
	size_t	f;
	char	*line;

	i = -1;
	while (++i < arr->len)
	{
		line = arr->data[i];
		if (ft_strstart(line, "v "))
			scop->obj.vcount += 1;
		if (ft_strstart(line, "vt "))
			scop->obj.vtcount += 1;
		if (ft_strstart(line, "vn "))
			scop->obj.vncount += 1;
		if (ft_strstart(line, "f "))
		{
			f = scop_obj_count_arg(line + 2);
			if (f == 3 || f == 4)
				scop->obj.tcount += f - 2;
		}
	}
}

static void		scop_init_obj(t_scop *scop)
{
	scop->obj.vcount = 0;
	scop->obj.vtcount = 0;
	scop->obj.vncount = 0;
	scop->obj.tcount = 0;
	scop->obj.v = NULL;
	scop->obj.vt = NULL;
	scop->obj.vn = NULL;
	scop->obj.cx = 0.f;
	scop->obj.cy = 0.f;
	scop->obj.cz = 0.f;
	scop->obj.pos.x = 0.f;
	scop->obj.pos.y = 0.f;
	scop->obj.pos.z = 6.f;
}

int				scop_load_obj(t_scop *scop, char *path)
{
	char	*file_content;
	t_array	*array_file;

	scop_init_obj(scop);
	file_content = scop_file_content(path);
	array_file = array_bystr(file_content, '\n', 1);
	if (file_content)
		free(file_content);
	scop_obj_count(scop, array_file);
	scop->obj.v = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.vcount * 3);
	scop->obj.vpos = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	scop->obj.color = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	scop_obj_parser(scop, array_file);
	scop_obj_log(scop);
	if (array_file)
		array_free(&array_file);
	return (0);
}

void			scop_unload_obj(t_scop *scop)
{
	scop->obj.vcount = 0;
	scop->obj.vtcount = 0;
	scop->obj.vncount = 0;
	scop->obj.tcount = 0;
	if (scop->obj.v)
		free(scop->obj.v);
	if (scop->obj.vt)
		free(scop->obj.vt);
	if (scop->obj.vn)
		free(scop->obj.vn);
	if (scop->obj.vpos)
		free(scop->obj.vpos);
	if (scop->obj.color)
		free(scop->obj.color);
}
