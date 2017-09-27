#ifndef FNL_H
# define FNL_H

# ifndef READ_SIZE
# define READ_SIZE	512
# endif

typedef struct	s_fnl
{
	int		fd;
	char	*buf;
}				t_fnl;

t_fnl			*fnl_new(const char *path);
void			fnl_free(t_fnl **file);
int				fnl_next_line(t_fnl *file);

#endif
