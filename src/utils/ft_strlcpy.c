/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:38:30 by dgomez-b          #+#    #+#             */
/*   Updated: 2025/11/03 19:55:18 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ********************************LIBRARIES********************************* */

#include "./utils.h"
#include <string.h>

/* ********************************FUNCTIONS********************************* */

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	return (ft_strlen(src));
}
