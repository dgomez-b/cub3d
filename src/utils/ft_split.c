/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-b <dgomez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:28:51 by dgomez-b          #+#    #+#             */
/*   Updated: 2023/07/26 15:52:04 by dgomez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ********************************LIBRARIES********************************* */

#include <stdlib.h>

/* ********************************FUNCTIONS********************************* */

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);

static size_t	ft_cantword(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i])
	{
		while ((s[i] == c) && (i < len))
			i++;
		if (i != len)
		{
			while ((s[i] != c) && (i < len))
				i++;
			j++;
		}
	}
	if (j == 0)
		j++;
	return (j);
}

static void	ft_freemat(char **mat)
{
	size_t	i;

	i = 0;
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

static size_t	ft_cantchar(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
		if (s[i++] == c)
			j++;
	return (j);
}

static char	*ft_substr2(const char *s, size_t ini, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s || ini >= ft_strlen(s))
		return (0);
	i = 0;
	while (s[ini + i] && s[ini + i] != c)
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	j = -1;
	while (++j < i)
		str[j] = s[ini + j];
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**mat;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	mat = ft_calloc(ft_cantword(s, c) + 1, sizeof(char *));
	if (!mat || ft_cantchar(s, c) == ft_strlen(s))
		return (mat);
	i = 0;
	j = 0;
	while (j < ft_cantword(s, c))
	{
		while (i < ft_strlen(s) && s[i] == c)
			i++;
		mat[j] = ft_substr2(s, i, c);
		if (!mat[j])
		{
			ft_freemat(mat);
			return (0);
		}
		i += ft_strlen(mat[j++]);
	}
	return (mat);
}
