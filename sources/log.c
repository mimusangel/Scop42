/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 22:44:47 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 04:10:38 by mgallo           ###   ########.fr       */
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
