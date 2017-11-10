/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:00:35 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 01:46:22 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# ifndef O_BINARY
#  define O_BINARY 0
# endif

typedef struct s_bmp_infoheader	t_bmp_infoheader;
typedef struct s_bmp_header		t_bmp_header;

# pragma pack(push, 1)

/*
** s_bmp_header : 14oct
*/

struct					s_bmp_header
{
	unsigned short int	type;
	unsigned int		size;
	unsigned short int	reserved1;
	unsigned short int	reserved2;
	unsigned int		offset;
};

/*
** s_bmp_infoheader : 40oct
*/

struct					s_bmp_infoheader
{
	unsigned int		size;
	int					width;
	int					height;
	unsigned short int	planes;
	unsigned short int	bits;
	unsigned int		compression;
	unsigned int		imagesize;
	int					xresolution;
	int					yresolution;
	unsigned int		ncolours;
	unsigned int		importantcolours;
};

# pragma pack(pop)

typedef struct			s_bmp
{
	t_bmp_header		header;
	t_bmp_infoheader	info;
	char				*data;
}						t_bmp;

int						bmp_load(t_bmp *bmp, char *path);

#endif
