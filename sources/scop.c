/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 11:34:13 by mgallo            #+#    #+#             */
/*   Updated: 2017/09/29 13:09:19 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fnl.h>
#include "scop.h"

# include <stdio.h>

static void 	parse_obj(t_fnl *file)
{
	char	*line;
	int		end;
	int		count[4];

	line = NULL;
	count[0] = count[1] = count[2] = count[3] = 0;
	while ((end = file_next_line(file, &line)) > 0)
	{
		if (fnl_strstartwith(line, "v "))
			count[0]++;
		if (fnl_strstartwith(line, "vt "))
			count[1]++;
		if (fnl_strstartwith(line, "vn "))
			count[2]++;
		if (fnl_strstartwith(line, "f "))
			count[3]++;
		free(line);
		line = NULL;
	}
	printf("Vertex Position number: %d\n", count[0]);
	printf("Vertex Texture number: %d\n", count[1]);
	printf("Vertex Normal number: %d\n", count[2]);
	printf("Face number: %d\n", count[3]);
}

int		main(int ac, char **av)
{
	t_fnl	*file;
	if (ac > 1)
	{
		file = fnl_new(av[1]);
		if (file)
		{
			parse_obj(file);
			fnl_free(&file);
		}
		else
			write(1, "Impossible d'ouvrir le fichier\n.", 32);
	}
	else
		write(1, "Argument non valide!\n", 21);
	return (0);
}
