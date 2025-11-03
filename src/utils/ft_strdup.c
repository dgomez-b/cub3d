/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:15:12 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/09/26 18:15:12 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*rs;
	size_t	len;

	len = ft_strlen(s);
	rs = malloc(sizeof(char) * len + 1);
	if (!rs)
		return (0);
	rs[len] = 0;
	while (len-- > 0)
		rs[len] = s[len];
	return (rs);
}
