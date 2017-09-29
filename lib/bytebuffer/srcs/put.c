#include "bytebuffer.h"

void	bb_putchar(t_bytebuffer *bb, char c)
{
	if (bb->size < bb->capacity)
	{
		bb->data[bb->size] = c;
		bb->size++;
	}
}

void	bb_putint(t_bytebuffer *bb, int i)
{
	bb_putchar(bb, (char)((i >> 24) & 0xff));
	bb_putchar(bb, (char)((i >> 16) & 0xff));
	bb_putchar(bb, (char)((i >> 8) & 0xff));
	bb_putchar(bb, (char)(i & 0xff));
}

void	bb_putfloat(t_bytebuffer *bb, float f)
{
	char	*s;
	size_t	i;

	s = (char *) &f;
	i = -1;
	while (++i < sizeof(float))
		bb_putchar(bb, s[i]);
}
