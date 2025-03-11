/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:56:34 by kchatela          #+#    #+#             */
/*   Updated: 2025/03/11 17:19:22 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char	*obtain_remaining(char *basin_buffer);
char	*extract_line(char *basin_buffer);
char	*append_buffer(char *basin_buffer, char *read_buffer);
/* -------------------------------------------------------------------------- */
/* Function to read data from the file and append it to partial content.      */
/* -------------------------------------------------------------------------- */

static char	*read_from_file(char *basin_buffer, int fd)
{
	int		bytes_read;
	char	*cup_buffer;

	cup_buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (cup_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(cup_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (ft_strchr(basin_buffer, '\n'))
			break ;
	}
	free(cup_buffer);
	return (basin_buffer);
}

/* -------------------------------------------------------------------------- */
/* The get_next_line function to get the next line from the file descriptor.  */
/* -------------------------------------------------------------------------- */
char	*get_next_line(int fd)
{
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = ft_calloc(1, sizeof (char));
	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);
	if (!basin_buffer)
		return (free(basin_buffer), NULL);
	line = extract_line(basin_buffer);
	basin_buffer = obtain_remaining(basin_buffer);
	return (line);
}

//takes everything up to and including the first \n
char	*extract_line(char *basin_buffer)
{
	char	*line;
	char	*nwline_pos;
	int		len;
	int		i;

	i = 0;
	if (!basin_buffer || !*basin_buffer)
		return (NULL);
	nwline_pos = ft_strchr(basin_buffer, '\n');
	if (nwline_pos)
		len = nwline_pos - basin_buffer + 1;
	else
		len = ft_strlen(basin_buffer);
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = basin_buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

//keeps everything after the first \n
char	*obtain_remaining(char *basin_buffer)
{
	char	*remaining_pos;
	char	*remaining_buffer;
	int		len;
	int		i;

	i = 0;
	if (!basin_buffer || !*basin_buffer)
		return (NULL);
	remaining_pos = ft_strchr(basin_buffer, '\n');
	if (!remaining_pos)
		return (NULL);
	remaining_pos++;
	len = ft_strlen(remaining_pos);
	remaining_buffer = ft_calloc(len + 1, sizeof(char));
	if (!remaining_buffer)
		return (NULL);
	i = 0;
	while (remaining_pos[i])
	{
		remaining_buffer[i] = remaining_pos[i];
		i++;
	}
	remaining_buffer[i] = '\0';
	free(basin_buffer);
	return (remaining_buffer);
}

char	*append_buffer(char *basin_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(basin_buffer, read_buffer);
	if (!temp)
	{
		free(basin_buffer);
		return (NULL);
	}
	free(basin_buffer);
	return (temp);
}

int main(void)
{
 int  fd;
 char *line;
 int  count;

 count = 0;
 fd = open("example.txt", O_RDONLY);
 if (fd == -1)
 {
   printf("Error opening file");
  return (1);
 } 
 while (1)
 {
  line = get_next_line(fd);
  if (line == NULL)
   break ;
  count++;
  printf("[%d]:%s\n", count, line);
  free(line);
  line = NULL;
 }
 close(fd);
 return (0);
}