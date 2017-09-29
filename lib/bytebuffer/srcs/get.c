#include "bytebuffer.h"

char			bb_getchar(t_bytebuffer *bb)
{
	char c;

	c = 0;
	if (bb->index < bb->capacity)
	{
		c = bb->data[bb->index];
		bb->index++;
	}
	return (c);
}

int				bb_getint(t_bytebuffer *bb)
{
	int ret;

	ret = (bb_getchar(bb) << 24) | (bb_getchar(bb) << 16)
		| (bb_getchar(bb) << 8) | bb_getchar(bb);
	return (ret);
}

float			bb_getfloat(t_bytebuffer *bb)
{
	char	f[sizeof(float)];
	size_t	i;

	i = -1;
	while (++i < sizeof(float))
		f[i] = bb_getchar(bb);
	return (*((float *)f));
}
