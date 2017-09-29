#include "fnl.h"

int				fnl_strtoint(const char *str)
{
	int 	nb;
	int		neg;

	nb = 0;
	while (*str == '\n' || *str == '\v' || *str == ' ' || *str == '\t'
		|| *str == '\r' || *str == '\f')
		str++;
	neg = 0;
	if (*str == '-')
		neg = 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (neg ? -nb : nb);
}

double			fnl_strtodouble(const char *str)
{
	double	nb;
	double	mul;

	nb = (double)fnl_strtoint(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	mul = 10.0;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb + ((*str - '0') / mul);
		mul = mul * 10;
		str++;
	}
	return (nb);
}

int				fnl_strstartwith(const char *str, const char *start)
{
	while (*start)
	{
		if (*start != *str)
			return (0);
		start++;
		str++;
	}
	return (1);
}

ssize_t			fnl_strcountchar(const char *str, const char c)
{
	ssize_t count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

ssize_t			fnl_strstr(const char *str, const char *search)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	if (!*str || !*search)
		return (0);
	while (str[++i])
	{
		j = -1;
		while (search[++j])
			if (str[i + j] != search[j])
				break ;
		if (!search[j])
			return (i);
	}
	return (0);
}
