#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3 // Default value if not defined externally
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>


char	*get_next_line(int fd);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);

#endif