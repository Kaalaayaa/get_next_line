#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>


char	*get_next_line(int fd);

void	*ft_calloc(size_t count, size_t size);

#endif