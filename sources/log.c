/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 22:44:47 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 07:38:16 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void		ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

void		ft_putlog(const char *str, const char *strlog)
{
	ft_putstr(str);
	ft_putstr(strlog);
	write(1, "\n", 1);
}

void		scop_putmat4(GLfloat *mat)
{
	int i;

	i = 0;
	while (i < 16)
	{
		ft_putfloat_nb(mat[i], 2);
		if (i % 4 == 3)
			write(1, "\n", 1);
		else
			write(1, ", ", 2);
		i++;
	}
}

void		scop_obj_log(t_scop *scop)
{
	ft_putstr("Vertex Count: ");
	ft_putnbr(scop->obj.vcount);
	ft_putstr("\nVertex Texture Count: ");
	ft_putnbr(scop->obj.vtcount);
	ft_putstr("\nVertex Normal Count: ");
	ft_putnbr(scop->obj.vncount);
	ft_putstr("\nTriangle Count: ");
	ft_putnbr(scop->obj.tcount);
	ft_putstr("\n");
}
