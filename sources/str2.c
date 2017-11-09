/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 07:01:51 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 18:41:29 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				ft_strstart(char *str, char *start)
{
	size_t	i;

	if (!*str || !*start)
		return (0);
	i = 0;
	while (str[i] && start[i] && str[i] == start[i])
		i++;
	return (start[i] == '\0');
}

int				ft_strend(char *str, char *end)
{
	size_t	i;
	size_t	len[2];

	if (!*str || !*end)
		return (0);
	len[0] = ft_strlen(str);
	len[1] = ft_strlen(end);
	if (len[1] > len[0])
		return (0);
	i = -1;
	while (++i < len[1])
	{
		if (str[len[0] - len[1] + i] != end[i])
			return (0);
	}
	return (1);
}
