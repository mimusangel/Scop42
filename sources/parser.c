/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:56:36 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 17:16:33 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scop_obj_tri(t_scop *scop, char *line)
{
	static size_t	it = 0;
	int				vali[4];
	int				i;
	t_array			*arr;
	float			color;

	arr = array_bystr(line, ' ', 1);
	if (arr)
	{
		vali[0] = ft_atoi(arr->data[1]) - 1;
		vali[1] = ft_atoi(arr->data[2]) - 1;
		vali[2] = ft_atoi(arr->data[3]) - 1;
		i = -1;
		color = 0.25f + ((float)rand()/(float)(RAND_MAX)) * 0.5f;
		while (++i < 9)
		{
			scop->obj.vpos[it * 9 + i] = scop->obj.v[vali[i / 3] * 3 + i % 3];
			scop->obj.color[it * 9 + i] = color;
		}
		it++;
		if (arr->len > 4)
		{
			color = 0.1f + ((float)rand()/(float)(RAND_MAX)) * 0.8f;
			vali[3] = ft_atoi(arr->data[4]) - 1;
			i = -1;
			while (++i < 9)
			{
				scop->obj.vpos[it * 9 + i] = scop->obj.v[vali[(i / 3 + 2) % 4] * 3 + i % 3];
				scop->obj.color[it * 9 + i] = color;
			}
			it++;
		}
		/*
			u = X/texture_width
			v = 1 - Y/texture_height
		*/
		scop->obj.tcount = it;
		array_free(&arr);
	}
}

static void scop_obj_center(t_scop *scop)
{
	size_t	i;

	scop->obj.cx = 0;
	scop->obj.cy = 0;
	scop->obj.cz = 0;
	i = -1;
	while (++i < scop->obj.vcount)
	{
		scop->obj.cx += scop->obj.v[i * 3];
		scop->obj.cy += scop->obj.v[i * 3 + 1];
		scop->obj.cz += scop->obj.v[i * 3 + 2];
	}
	scop->obj.cx /= (GLfloat)scop->obj.vcount;
	scop->obj.cy /= (GLfloat)scop->obj.vcount;
	scop->obj.cz /= (GLfloat)scop->obj.vcount;
}

static void	scop_obj_line(t_scop *scop, char *line)
{
	static size_t	iv = 0;
	t_array			*arr;

	arr = NULL;
	if (!line || !*line)
		return ;
	if (ft_strstart(line, "v "))
	{
		arr = array_bystr(line, ' ', 1);
		scop->obj.v[iv * 3] = (GLfloat)ft_atof(arr->data[1]);
		scop->obj.v[iv * 3 + 1] = (GLfloat)ft_atof(arr->data[2]);
		scop->obj.v[iv * 3 + 2] = (GLfloat)ft_atof(arr->data[3]);
		iv++;
	}
	if (ft_strstart(line, "f "))
		scop_obj_tri(scop, line);
	if (arr)
		array_free(&arr);
}

void		scop_obj_parser(t_scop *scop, t_array *arr)
{
	size_t	i;
	char	*line;

	i = -1;
	while (++i < arr->len)
	{
		line = arr->data[i];
		scop_obj_line(scop, line);
	}
	scop_obj_center(scop);
}
