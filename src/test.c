#include "header.h"
#include <unistd.h>

char **get_test_map(int fd)
{
	char *str;
	char **map = NULL;

	str = get_next_line(fd);
	if (str)
		str[str_len(str) - 1] = '\0';
	while (str)
	{
		map = add_str_to_str_tab(map, str);
		str = get_next_line(fd);
		if (str)
			str[str_len(str) - 1] = '\0';
	}
	return (map);
}