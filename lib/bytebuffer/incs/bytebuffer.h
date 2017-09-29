#ifndef BYTEBUFFER_H
# define BYTEBUFFER_H

# include <stdlib.h>


typedef struct	s_bytebuffer
{
	char	*data;
	size_t	capacity;
	size_t	index;
	size_t	size;
}				t_bytebuffer;

t_bytebuffer	*bb_new(size_t capacity);
void			bb_clear(t_bytebuffer *bb);
void			bb_free(t_bytebuffer **bb);
void			bb_setindex(t_bytebuffer *bb, size_t index);

void			bb_putchar(t_bytebuffer *bb, char c);
void			bb_putint(t_bytebuffer *bb, int i);
void			bb_putfloat(t_bytebuffer *bb, float f);

char			bb_getchar(t_bytebuffer *bb);
int				bb_getint(t_bytebuffer *bb);
float			bb_getfloat(t_bytebuffer *bb);

#endif
