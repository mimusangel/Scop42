/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:02:35 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 08:37:20 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "bmp.h"
#include "scop.h"

static int	bmp_load2(t_bmp *bmp, int fd)
{
	size_t	s;

	bmp->info.imagesize = bmp->info.width * bmp->info.height
		* (bmp->info.bits / 8);
	if (!(bmp->data = (char *)malloc(sizeof(char) * bmp->info.imagesize)))
	{
		close(fd);
		return (ft_putlog("Error malloc.\nFile: ", "path"));
	}
	printf("size: %u\n", bmp->info.imagesize);
	if ((s = read(fd, bmp->data, bmp->info.imagesize)) != bmp->info.imagesize)
	{
		free(bmp->data);
		close(fd);
		return (ft_putlog("Error size image.\nFile: ", "path"));
	}
	close(fd);
	printf("%d, %d, %d(%d)\n", bmp->info.width, bmp->info.height, bmp->info.bits, (bmp->info.bits / 8));
	printf("%u\n", bmp->data[(200 * bmp->info.width + 500) * 3]);
	printf("%u\n", bmp->data[(200 * bmp->info.width + 500) * 3 + 1]);
	printf("%u\n", bmp->data[(200 * bmp->info.width + 500) * 3 + 2]);
	return (1);
}

int			bmp_load(t_bmp *bmp, char *path)
{
	int		fd;

	if((fd = open(path, O_RDONLY | O_BINARY)) <= 2)
		return (ft_putlog("File not found!\nFile: ", path));
	if (read(fd, (char *)&(bmp->header), 14) != 14
		|| read(fd, (char *)&(bmp->info), 40) != 40)
	{
		close(fd);
		return (ft_putlog("Error file format is incorrect.\nFile: ", "path"));
	}
	if (bmp->header.type != 19778)
	{
		close(fd);
		return (ft_putlog("Error header type.\nFile: ", "path"));
	}
	return (bmp_load2(bmp, fd));
}
