#include "get_next_line.h"

// Allocates memory and initialize all bytes to 0;
void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*result;

	i = 0;
	result = malloc(count * size);
	if (!result)
	{
		return (NULL);
	}
	while (i < count * size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

