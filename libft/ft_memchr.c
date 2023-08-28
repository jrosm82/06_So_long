/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:21:09 by jrosmari          #+#    #+#             */
/*   Updated: 2023/01/22 09:38:47 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	*ptr_c;
	size_t			i;

	ptr_s = (unsigned char *)s;
	ptr_c = (unsigned char *)&c;
	i = 0;
	while (i < n)
	{
		if (ptr_s[i] == *ptr_c)
			return ((void *)(ptr_s + i));
		i++;
	}
	return (NULL);
}
