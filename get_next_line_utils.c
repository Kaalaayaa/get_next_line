#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

// Allocates memory and initialize all bytes to 0
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

//Finds the first occurrence of a character in a string
char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	while (*s)
	{
		if (*s == char_c)
			return ((char *)s);
		s++;
	}
	if (char_c == '\0')
		return ((char*)s);
	return (NULL);
}

// char *ft_strdup(const char *str)
// {
// 	char	*result;

// 	result = malloc(ft_strlen(str) + 1 * sizeof(char));
// 	if (!result)
// 	{
// 		return (NULL);
// 	}
// 	ft_strlcpy(result, str, ft_strlen(str) + 1);
// 	return (result);
// }

