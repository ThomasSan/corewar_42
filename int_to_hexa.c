#include "assembleur.h"
#include <stdio.h>

int		length_in_base(int nb, int base)
{
	int	i;

	i = 0;
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char	*str_itobase(int nb, int base)
{
	const char	*symbols = "0123456789abcdef";
	char		*str;
	char		*tmp;
	int			len;

	len = length_in_base(nb, base);
	str = (char*)malloc(sizeof(char) * len + 1);
	// printf("len %d\n", len);
	str[len] = '\0';
	len--;
	while (nb > 0)
	{
		// printf("modulo/16 %d, divised/16 %d\n", nb%base, nb/base);
		str[len] = symbols[nb % base];
		nb /= base;
		len--;
	}
	if (ft_strlen(str) == 1)
	{
		tmp = str;
		str = ft_strjoin("0", str);
		free(tmp);
	}
	// printf("str (%s)\n", str);
	return (str);
}