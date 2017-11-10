/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:33:22 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 10:07:36 by mgallo           ###   ########.fr       */
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
	ft_putstr("Arguments:\n");
	ft_putstr("\t-sphere: calcul des textures par sphere(par defaut)\n");
	ft_putstr("\t-flat: calcul des textures par les axe y et z\n");
	ft_putstr("Utilisation:\n");
	ft_putstr("\tFleche + wasd: deplacement.\n");
	ft_putstr("\tPN 7 + PN 9: activer/desactiver rotation auto.\n");
	ft_putstr("\tPN 1 a PN 6: rotation predefini.\n");
	ft_putstr("\t1 et 2: mode de rendu.\n");
	ft_putstr("\t8, 9 et 0: mode de cullface.\n");
	ft_putstr("\tt: transition texture.\n");
	ft_putstr("\tu: transition couleur uniforme.\n");
}

void		scop_args(t_scop *scop, int ac, char **av)
{
	size_t i;

	scop->calc_normal_type = 0;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequal(av[i], "-sphere"))
			scop->calc_normal_type = 0;
		else if (ft_strequal(av[i], "-flat"))
			scop->calc_normal_type = 1;
	}
	scop_command();
}
