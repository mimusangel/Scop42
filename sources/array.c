/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:22:38 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 06:20:57 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t	array_count_work(char *str, char sep)
{
	size_t	i;
	size_t	work;

	i = 0;
	work = 0;
	while (*str)
	{
		if (*str == sep || *str == '\r')
			work = 0;
		if (*str != sep && !work && *str != '\r')
		{
			i++;
			work = 1;
		}
		str++;
	}
	return (i);
}

static size_t	array_count_row(char *str, char sep)
{
	size_t	i;

	i = 1;
	while (*str)
	{
		if (*str == sep)
			i++;
		str++;
	}
	return (i);
}

t_array			*array_bystr(char *str, char sep, int trim)
{
	t_array	*arr;
	size_t	i;
	size_t	next;

	if (!(arr = (t_array *)malloc(sizeof(t_array))))
		return (NULL);
	arr->len = trim ? array_count_work(str, sep) : array_count_row(str, sep);
	if (!(arr->data = (char **)malloc(sizeof(char *) * arr->len)))
	{
		free(arr);
		return (NULL);
	}
	i = -1;
	while (++i < arr->len)
	{
		while (trim && *str && *str == sep)
			str++;
		next = ft_strchr(str, sep);
		if (!trim)
			arr->data[i] = (next > 0) ? ft_strsub(str, 0, next) : NULL;
		else if (next > 0)
			arr->data[i] = ft_strsub(str, 0, next);
		str += next + 1;
	}
	return (arr);
}

void			array_free(t_array **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = -1;
	while (++i < (*arr)->len)
		if ((*arr)->data[i])
		{
			free((*arr)->data[i]);
			(*arr)->data[i] = NULL;
		}
	free((*arr)->data);
	(*arr)->data = NULL;
	free(*arr);
	*arr = NULL;
}
