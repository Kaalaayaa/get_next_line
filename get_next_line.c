#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	*cup_buffer;

	cup_buffer = ft_calloc ((3 + 1), sizeof(char));
	if(cup_buffer == NULL)
		return (NULL);
	bytes_read = read(fd, cup_buffer, 3);
	if (bytes_read <= 0)
		return (NULL);
	return (cup_buffer);
}

int	main()
{
	int		fd;
	int		count;
	char 	*next_line;

	count = 0;
	fd = open("example.txt", O_RDWR);
	if (fd == -1)
	{
		printf("Error when opening file");
		return 1;
	}
	while(1)
	{
		next_line = get_next_line(fd);
		if(next_line == NULL)
			break;
		count ++;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
		next_line = NULL; // ??
	}
	

	close(fd);
	return 0;
}

// if (fd = -1)
// 	{
// 		printf("Error when opening file");
// 		return 1;
// 	}
// 	next_line = get_next_line(fd);
// 	if (next_line = NULL)
// 	{
// 		printf("Nothing else to read or error has occured");
// 	}