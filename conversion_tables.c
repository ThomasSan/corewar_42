#include "assembleur.h"

int		index_in_2d_array(char const **array, char *str)
{
	int i = 0;

	while (array[i])
	{
		if (ft_strcmp(array[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		label_sizes(char *str)
{
	const char	size_of_two = ["zjmp", "ldi", "sti", "fork", "lldi", "lfork"];
	const char	size_of_four = ["live", "ld", "and", "or", "xor", "lld"];

	if (index_in_2d_array(size_of_two, str))
		return (2);
	if (index_in_2d_array(size_of_four, str))
		return (4);
}

int		params_types(char *str)
{
	const char no_encoding = ["live", "zjmp", "fork", "lfork"];

	if (index_in_2d_array(no_encoding, str))
		return (0);
	return (1);
}