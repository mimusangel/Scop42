#include <unistd.h>
#include <stdlib.h>
#include <fnl.h>

# include <stdio.h>
int		main(int ac, char **av)
{
	char *s0 = "v 0.21 0.42 0.69";
	char *s1 = "vn test";
	int a = fnl_strstartwith(s0, "v ");
	int b = fnl_strstartwith(s1, "v ");
	printf("%d\n", a);
	printf("%d\n", b);
	ssize_t count = fnl_strcountchar(s0, ' ');
	printf("%zd\n", count);

	int i = fnl_getchar(s0, ' ', 0) + 1;
	double val = fnl_strtodouble(s0 + i);
	printf("%s\n", s0 + i);
	printf("val: %f\n", val);

	i = i + fnl_getchar(s0 + i, ' ', 0) + 1;
	val = fnl_strtodouble(s0 + i);
	printf("%s\n", s0 + i);
	printf("val: %f\n", val);

	i = i + fnl_getchar(s0 + i, ' ', 0) + 1;
	val = fnl_strtodouble(s0 + i);
	printf("%s\n", s0 + i);
	printf("val: %f\n", val);

	char *s2 = "f 1//2 3//4 5//6";
	char *s3 = "f 1/2/3 4/5/6 7/8/9";
	printf("s2: %s\n", s2 + fnl_strstr(s2, "//"));
	printf("s3: %s\n", s3 + fnl_strstr(s3, "//"));
	return (0);
}
