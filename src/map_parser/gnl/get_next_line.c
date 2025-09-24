/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidgomez <davidgomez@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:01:07 by davidgomez        #+#    #+#             */
/*   Updated: 2023/01/29 00:33:54 by davidgomez       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* ************************************************************************** */

int		ft_strcpy(char *dst, char *src);
char	*ft_strchr(char *s, char c);
void	*ft_memcpy2(void *dst, const void *src, size_t len);

static int	ft_buffprocesor(int fd, char *str)
{
	static char	aux[BUFFER_SIZE + 1];
	char		*nl;
	int			i;

	if (*aux != 0)
	{
		i = ft_strcpy(str, aux);
		*aux = 0;
	}
	else
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i >= 0)
			str[i] = 0;
		else
			*str = 0;
	}
	nl = ft_strchr(str, '\n');
	if (!nl)
		return (i);
	i -= ft_strcpy(aux, ++nl);
	*nl = 0;
	return (i);
}

static char	*ft_createstr(int len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (len >= 0)
		str[len--] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	static int	i;
	int			j;
	char		*str;
	char		buff[BUFFER_SIZE + 1];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!i)
		i = 0;
	j = ft_buffprocesor(fd, buff);
	if (!*buff)
		return (0);
	i += j;
	str = 0;
	if (!ft_strchr(buff, '\n'))
		str = get_next_line(fd);
	i -= j;
	if (!str)
		str = ft_createstr(i + j);
	if (!str)
		return (0);
	ft_memcpy2(str + i, buff, j);
	return (str);
}
