#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "fnl.h"

t_fnl			*fnl_new(const char *path)
{
	t_fnl *file;

	if (!(file = (t_fnl *)malloc(sizeof(t_fnl))))
		return (NULL);
	file->fd = open(path, O_RDONLY);
	file->buf = NULL;
	if (file->fd > 0)
		return (file);
	fnl_free(&file);
	return (NULL);
}

void			fnl_free(t_fnl **file)
{
	if (!file || !*file)
		return ;
	if ((*file)->fd > 0)
		close((*file)->fd);
	free(*file);
	*file = NULL;
}

int				fnl_next_line(t_fnl *file)
{
	return (0);
}
