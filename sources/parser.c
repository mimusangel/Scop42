/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:56:36 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 07:35:30 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	scop_obj_tri2(t_scop *scop, int it, int *vali, int offset)
{
	int				i;
	int				index;

	i = -1;
	while (++i < 9)
	{
		index = (i / 3 + offset) % 4;
		if ((vali[index] * 3 + i % 3) >= scop->obj.vcount * 3)
			return (ft_putlog("Vertex index not found!", ""));
		if ((it * 9 + i) >= (scop->obj.tcount * 9))
			return (ft_putlog("Buffer index not found!", ""));
		scop->obj.buff[it * 9 + i] = scop->obj.v[vali[index] * 3 + i % 3];
	}
	return (1);
}

static int	scop_obj_tri(t_scop *scop, char *line)
{
	static size_t	it = 0;
	int				vali[4];
	t_array			*arr;

	arr = array_bystr(line, ' ', 1);
	if (arr && (arr->len == 4 || arr->len == 5))
	{
		vali[0] = ft_atoi(arr->data[1]) - 1;
		vali[1] = ft_atoi(arr->data[2]) - 1;
		vali[2] = ft_atoi(arr->data[3]) - 1;
		if (!scop_obj_tri2(scop, it, vali, 0))
			return (ft_putlog("Line: ", line));
		it++;
		if (arr->len == 5)
		{
			vali[3] = ft_atoi(arr->data[4]) - 1;
			if (!scop_obj_tri2(scop, it, vali, 2))
				return (ft_putlog("Vertex index not found! Line: ", line));
			it++;
		}
		// scop->obj.tcount = it;
		array_free(&arr);
	}
	return (1);
}

static void	scop_obj_center(t_scop *scop)
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

static int	scop_obj_line(t_scop *scop, char *line)
{
	static size_t	iv = 0;
	t_array			*arr;

	arr = NULL;
	if (ft_strstart(line, "v "))
	{
		arr = array_bystr(line, ' ', 1);
		if (arr)
		{
			if (arr->len <= 4)
			{
				scop->obj.v[iv * 3] = (GLfloat)ft_atof(arr->data[1]);
				scop->obj.v[iv * 3 + 1] = (GLfloat)ft_atof(arr->data[2]);
				scop->obj.v[iv * 3 + 2] = (GLfloat)ft_atof(arr->data[3]);
			}
			iv++;
			array_free(&arr);
		}
	}
 	if (ft_strstart(line, "f "))
	{
		if (!scop_obj_tri(scop, line))
			return (0);
	}
	return (1);
}

int			scop_obj_parser(t_scop *scop, t_array *arr)
{
	size_t	i;
	char	*line;

	i = -1;
	while (++i < arr->len)
	{
		line = arr->data[i];
		if (!scop_obj_line(scop, line))
			return (0);
		free(arr->data[i]);
		arr->data[i] = NULL;
	}
	free(arr->data);
	scop_obj_center(scop);
	return (1);
}
