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

#endif
