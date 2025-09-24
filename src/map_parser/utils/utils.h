#ifndef UTILS_H
# define UTILS_H

#include <string.h>

size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
int		ft_atoi(const char *s);
void	freedom(void **ptr);
char	*ft_strdup(const char *s);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
