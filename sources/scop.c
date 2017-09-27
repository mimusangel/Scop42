#include <unistd.h>
#include <stdlib.h>
#include <fnl.h>

int		main(int ac, char **av)
{
	t_fnl	*file;
	char	*str;

	file = fnl_new("README.md");
	if (file)
	{
		while (fnl_next_line(file, &str) > 0)
		{
			write(1, str, fnl_strlen(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		fnl_offset(file, 0);
		while (fnl_next_line(file, &str) > 0)
		{
			write(1, str, fnl_strlen(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		fnl_free(&file);
	}
	return (0);
}
