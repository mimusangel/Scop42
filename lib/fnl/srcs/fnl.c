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
	file->read = 0;
	if (file->fd > 0)
		return (file);
	fnl_free(&file);
	return (NULL);
}

void			fnl_offset(t_fnl *file, ssize_t offset)
{
	if (offset < 0)
		file->read = 0;
	else
		file->read = offset;
}

void			fnl_free(t_fnl **file)
{
	if (!file || !*file)
		return ;
	if ((*file)->fd > 0)
		close((*file)->fd);
	free((*file)->buf);
	free(*file);
	*file = NULL;
}
