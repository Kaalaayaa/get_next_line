#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */
/* Function to read data from the file and append it to partial content.      */
/* -------------------------------------------------------------------------- */
static char *read_from_file(char *basin_buffer, int fd)
{
    int		bytes_read;
	char	*cup_buffer;

	cup_buffer = ft_calloc ((BUFFER_SIZE + 1), sizeof(char));
	if(cup_buffer == NULL)
		return (NULL);
	bytes_read = 1;

	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);

		if (bytes_read == -1)
			return (free(cup_buffer), NULL);

		cup_buffer[bytes_read] = '\0';

		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		
		if (ft_strchr(basin_buffer, '\n'));
			break;
	}
	free (cup_buffer);
	return (basin_buffer);
}

/* -------------------------------------------------------------------------- */
/* The get_next_line function to get the next line from the file descriptor.  */
/* -------------------------------------------------------------------------- */
char	*get_next_line(int fd)
{
	static char	*basin_buffer;
	char	*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	if (!basin_buffer)
		basin_buffer = ft_calloc(1, sizeof (char));

	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);

	if (!basin_buffer)
		return (free(basin_buffer), NULL);

	// extract_line(basin_buffer) takes everything up to and including the first \n
	line = extract_line(basin_buffer);

	// obtain_remaining(basin_buffer) keeps everything after the first \n so it can be used in the next call.
	basin_buffer = obtain_remaining(basin_buffer);

	return (line);
}

char	*extract_line(char *basin_buffer)
{
	char *line;
	char *nwline_pos;
	int len;
	int i;

	i = 0;

	if (!basin_buffer || !*basin_buffer)
	{
		return (NULL);
	}
	nwline_pos = ft_strchr(basin_buffer, '\n');

	if (nwline_pos)
	{
		len = nwline_pos - basin_buffer + 1;
	}
	else
	{
		len = ft_strlen(basin_buffer);
	};

	line = ft_calloc(len + 1, sizeof(char));
	if(!line)
		return (NULL);

	while(i < len)
	{
		line[i] = basin_buffer[i];
		i++;
	}

	line[len] = '\0';
	return line;
};

char	*obtain_remaining(char *basin_buffer){

	char *remaining_pos;

	if (!basin_buffer || !*basin_buffer)
	{
		return (NULL);
	}

	remaining_pos = ft_strchr


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