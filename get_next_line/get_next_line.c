/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:12:22 by jrosmari          #+#    #+#             */
/*   Updated: 2023/07/01 17:42:18 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	

static char	*split_ln(char *ln_final)
{
	size_t	cnt;
	char	*str_rest;

	cnt = 0;
	while (ln_final[cnt] != '\0' && ln_final[cnt] != '\n')
		cnt++;
	if (ln_final[cnt] == '\0' || ln_final[1] == '\0')
		return (0);
	str_rest = ft_substr2(ln_final, cnt + 1, ft_strlen2(ln_final) - cnt);
	if (*str_rest == '\0')
	{
		free(str_rest);
		str_rest = NULL;
	}
	ln_final[cnt + 1] = '\0';
	return (str_rest);
}

static char	*read_func(int fd, char *buffer, char *ln_carry)
{
	int		ln_read;
	char	*str;

	ln_read = 1;
	while (ln_read != '\0')
	{
		ln_read = read(fd, buffer, BUFFER_SIZE);
		if (ln_read == -1)
			return (0);
		else if (ln_read == 0)
			return (ln_carry);
		buffer[ln_read] = '\0';
		if (!ln_carry)
			ln_carry = ft_strdup2("");
		str = ln_carry;
		ln_carry = ft_strjoin2(str, buffer);
		free(str);
		str = NULL;
		if (ft_strchr2('\n', buffer))
			return (ln_carry);
	}
	return (ln_carry);
}

char	*get_next_line(int fd)
{
	static char	*ln_carry;
	char		*ln_final;
	char		*buffer;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	ln_final = read_func(fd, buffer, ln_carry);
	free(buffer);
	buffer = NULL;
	if (!ln_final)
		return (NULL);
	ln_carry = split_ln(ln_final);
	return (ln_final);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	
	char	*toprint;
	
	int fd = open("big_line_with_nl", O_RDONLY | O_CREAT);
		
	while ((toprint = get_next_line(fd)) != NULL )
	{
		printf("%s", toprint);
		free(toprint);
	}	
	close(fd);
	return (0);
}*/
