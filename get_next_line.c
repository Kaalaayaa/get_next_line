#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char *obtain_remaining(char *basin_buffer);
char	*extract_line(char *basin_buffer);
char *append_buffer(char *basin_buffer, char *read_buffer);
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
		
		if (ft_strchr(basin_buffer, '\n'))
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
	char *remaining_buffer;
	int len;
	int i;

	i = 0;

	if (!basin_buffer || !*basin_buffer)
	{
		return (NULL);
	}

	remaining_pos = ft_strchr(basin_buffer, '\n');

	if(!remaining_pos)
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

char *append_buffer(char *basin_buffer, char *read_buffer)
{
	char *temp;

	temp = ft_strjoin(basin_buffer, read_buffer);
	free(basin_buffer);
	return(temp);
}


void test_get_next_line(const char *file_path)
{
    int fd;
    int count;
    char *next_line;

    count = 0;
    fd = open(file_path, O_RDWR);
    if (fd == -1)
    {
        printf("Error when opening file\n");
        return;
    }

    // Test: Read lines and print
    while (1)
    {
        next_line = get_next_line(fd);
        if (next_line == NULL)
            break;  // End of file

        count++;
        printf("[%d]: %s\n", count, next_line);  // Test output
        free(next_line);  // Free allocated memory for the line
    }

    close(fd);  // Close the file after testing
}

// Edge case: Empty file
void test_empty_file()
{
    printf("\n--- Testing Empty File ---\n");
    test_get_next_line("empty.txt");  // Empty file should not print anything
}

// Edge case: File with a single line
void test_single_line_file()
{
    printf("\n--- Testing Single Line File ---\n");
    test_get_next_line("single_line.txt");  // Should print 1 line
}

// Edge case: File with multiple lines
void test_multiple_lines_file()
{
    printf("\n--- Testing Multiple Lines File ---\n");
    test_get_next_line("multiple_lines.txt");  // Should print multiple lines
}

// Edge case: File with a line but no newline character at the end
void test_line_no_newline()
{
    printf("\n--- Testing Line with No Newline ---\n");
    test_get_next_line("line_no_newline.txt");  // Should print the entire line, no newline
}

// Edge case: File with empty lines
void test_empty_lines()
{
    printf("\n--- Testing File with Empty Lines ---\n");
    test_get_next_line("empty_lines.txt");  // Should handle empty lines correctly
}

int main()
{
    // Run all edge case tests
    test_empty_file();
    test_single_line_file();
    test_multiple_lines_file();
    test_line_no_newline();
    test_empty_lines();

    return 0;
}