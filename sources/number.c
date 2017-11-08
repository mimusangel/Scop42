/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 03:23:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 03:38:52 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			ft_atoi(const char *s)
{
	int nb;
	int sign;

	nb = 0;
	sign = 1;
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - '0');
		s++;
	}
	return (nb * sign);
}

double		ft_atof(const char *s)
{
	double	nb;
	double	dec;
	double	mult;

	nb = (double)ft_atoi(s);
	while (*s || *s != '.')
		s++;
	dec = 0;
	mult = 1;
	while (*s >= '0' && *s <= '9')
	{
		dec = dec * 10 + (*s - '0');
		mult = mult * 10;
		s++;
	}
	return (nb + (dec / mult));
}
