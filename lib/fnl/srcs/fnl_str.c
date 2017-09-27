#include <stdlib.h>
#include "fnl.h"

ssize_t			fnl_strlen(const char *str)
{
	ssize_t i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

char			*fnl_strcpy(const char *str)
{
	ssize_t i;
	char 	*nstr;

	nstr = (char *)malloc(sizeof(char) * (fnl_strlen(str) + 1));
	i = -1;
	while (str[++i])
		nstr[i] = str[i];
	nstr[i] = '\0';
	return (nstr);
}


char			*fnl_strcat(const char *s0, const char *s1)
{
	ssize_t i;
	ssize_t len0;
	char 	*nstr;

	len0 = fnl_strlen(s0);
	nstr = (char *)malloc(sizeof(char) * (len0 + fnl_strlen(s1) + 1));
	i = -1;
	while (s0[++i])
		nstr[i] = s0[i];
	i = -1;
	while (s1[++i])
		nstr[len0 + i] = s1[i];
	nstr[len0 + i] = '\0';
	return (nstr);
}

ssize_t			fnl_getchar(const char *str, const char c, ssize_t start)
{
	ssize_t i;

	i = 0;
	while (str[start + i])
	{
		if (str[start + i] == c)
			return (start + i);
		i++;
	}
	return (i);
}

char			*fnl_strsub(const char *str, ssize_t start, ssize_t end)
{
	ssize_t i;
	char	*nstr;

	nstr = (char *)malloc(sizeof(char) * (end - start + 1));
	i = -1;
	while (++i < (end - start))
		nstr[i] = str[start + i];
	nstr[i] = '\0';
	return (nstr);
}
