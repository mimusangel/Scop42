/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 03:23:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 17:43:59 by mgallo           ###   ########.fr       */
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
	while (*s && *s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - '0');
		s++;
	}
	return (nb * sign);
}

double		ft_atof(const char *s)
{
	double	nb[2];
	int		sign;

	nb[0] = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s && *s >= '0' && *s <= '9')
	{
		nb[0] = nb[0] * 10 + (*s - '0');
		s++;
	}
	if (*s != '.')
		return (nb[0] * sign);
	s++;
	nb[1] = 10.0;
	while (*s && *s >= '0' && *s <= '9')
	{
		nb[0] = nb[0] + ((*s - '0') / nb[1]);
		nb[1] *= 10.0;
		s++;
	}
	return (nb[0] * sign);
}

void		ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = '0' + (n % 10);
	write(1, &c, 1);
}

void		ft_putfloat(float n)
{
	int		i;
	char	c;

	i = (int)n;
	ft_putnbr(i);
	write(1, ".", 1);
	n = n - i;
	while (n != 0)
	{
		n = n * 10;
		i = (int)n;
		c = '0' + (i % 10);
		write(1, &c, 1);
		n = n - i;
	}
}

void		ft_putfloat_nb(float n, int size)
{
	int		i;
	char	c;

	i = (int)n;
	ft_putnbr(i);
	write(1, ".", 1);
	n = n - i;
	if (n < 0)
		n = -n;
	while (n != 0 && size > 0)
	{
		size--;
		n = n * 10;
		i = (int)n;
		n = n - i;
		if (size <= 0 && n > 0.5f)
			i++;
		c = '0' + (i % 10);
		write(1, &c, 1);
	}
	while (size-- > 0)
		write(1, "0", 1);
}
