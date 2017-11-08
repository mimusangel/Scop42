/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 07:01:51 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 07:04:35 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			ft_strstart(char *str, char *start)
{
	size_t	i;

	if (!*str || !*start)
		return (0);
	i = 0;
	while (str[i] && start[i] && str[i] == start[i])
		i++;
	return (start[i] == '\0');
}
