#include "bytebuffer.h"

t_bytebuffer	*bb_new(size_t capacity)
{
	t_bytebuffer *bb;

	if (!(bb = (t_bytebuffer *)malloc(sizeof(t_bytebuffer))))
		return (NULL);
	bb->capacity = capacity;
	if (!(bb->data = (char *)malloc(sizeof(char) * capacity)))
	{
		free(bb);
		return (NULL);
	}
	bb_clear(bb);
	return (bb);
}

void			bb_clear(t_bytebuffer *bb)
{
	size_t i;

	i = -1;
	while(++i < bb->capacity)
		bb->data[i] = 0;
	bb->size = 0;
	bb->index = 0;
}

void			bb_free(t_bytebuffer **bb)
{
	if (!*bb)
		return ;
	if ((*bb)->data)
		free((*bb)->data);
	free(*bb);
	*bb = NULL;
}
