#ifndef FNL_H
# define FNL_H

# ifndef READ_SIZE
# define READ_SIZE	512
# endif

# include <unistd.h>

typedef struct	s_fnl
{
	int		fd;
	char	*buf;
	ssize_t read;

}				t_fnl;

t_fnl			*fnl_new(const char *path);
void			fnl_offset(t_fnl *file, ssize_t offset);
void			fnl_free(t_fnl **file);

ssize_t			fnl_strlen(const char *str);
char			*fnl_strcpy(const char *str);
char			*fnl_strcat(const char *s0, const char *s1);
ssize_t			fnl_getchar(const char *str, const char c, ssize_t start);
char			*fnl_strsub(const char *str, ssize_t start, ssize_t end);

int				fnl_next_line(t_fnl *file, char **str);

int				fnl_strtoint(const char *str);
double			fnl_strtodouble(const char *str);
int				fnl_strstartwith(const char *str, const char *start);
ssize_t			fnl_strcountchar(const char *str, const char c);
ssize_t			fnl_strstr(const char *str, const char *search);

#endif
