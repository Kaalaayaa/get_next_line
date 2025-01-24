#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	*cup_buffer;

	cup_buffer = ft_calloc ((3 + 1), sizeof(char));

	return (NULL);
}

int	main()
{
	int fd = open("text.txt", O_RDWR);
	if (fd = -1)
	{
		printf("Error when opening file");
		return 1;
	}
	char *line = get_next_line(fd);

	if (line = NULL)
	{
		printf("Nothing else to read or error has occured");
	}
	close(fd);
	return 0;
}