/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:47:53 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/25 21:31:17 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen2(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr2(int c, const char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] == (char)c)
			return ((char *)&str[pos]);
		pos++;
	}
	if (c == '\0')
		return ((char *)&str[pos]);
	return (0);
}

char	*ft_strdup2(const char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	while (str[i] != '\0')
		i++;
	newstr = (char *)malloc(sizeof(char) * (i + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*strjoined;

	i = ft_strlen2(s1);
	j = ft_strlen2(s2);
	strjoined = (char *)malloc(sizeof(char) * (i + j + 1));
	i = 0;
	j = 0;
	if (strjoined == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
		strjoined[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		strjoined[j++] = s2[i++];
	strjoined[j] = '\0';
	return (strjoined);
}

char	*ft_substr2(char const *str, int start, size_t len)
{
	char	*newstr;
	size_t	i;

	i = 0;
	if (ft_strlen2(str) < start)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	while (i < len)
	{
		newstr[i] = str[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
