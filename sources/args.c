/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:33:22 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/11 18:13:19 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	ft_strequal(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (!*s1 && !*s2);
}

static void	scop_command(void)
{
	ft_putstr("Utilisation:\n");
	ft_putstr("\tFleche + wasd: deplacement.\n");
	ft_putstr("\tr: rotation automatique on/off.\n");
	ft_putstr("\t1, 2, 3: mode de cullface.\n");
	ft_putstr("\t8: rotation y - 22.5 degres.\n");
	ft_putstr("\t9: rotation y + 22.5 degres.\n");
	ft_putstr("\t0: rotation y = 0 degres.\n");
	ft_putstr("\tf: mode wireframe.\n");
	ft_putstr("\tt: mode texture.\n");
}

void		scop_args(t_scop *scop, int ac, char **av)
{
	size_t i;

	scop->calc_normal_type = 0;
	scop->rand_mod = 0;
	scop->color_mod = 0;
	scop->wireframe = 0;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequal(av[i], "-sphere"))
			scop->calc_normal_type = 0;
		else if (ft_strequal(av[i], "-flat"))
			scop->calc_normal_type = 1;
		else if (ft_strequal(av[i], "-rand"))
			scop->rand_mod = 1;
		else if (ft_strequal(av[i], "-color"))
			scop->color_mod = 1;
	}
	scop_command();
}

int			scop_usage(char *name)
{
	ft_putstr("Usage: ");
	ft_putlog(name, " <file.obj> [image.bmp] [Arguments...]");
	ft_putstr("Arguments:\n");
	ft_putstr("\t-sphere: calcul des textures par sphere(par defaut)\n");
	ft_putstr("\t-flat: calcul des textures par les axe y et z\n");
	ft_putstr("\t-rand: active le srand pour les couleur\n");
	ft_putstr("\t-color: les couleur ne sont plus noir vers blanc\n");
	return (0);
}
