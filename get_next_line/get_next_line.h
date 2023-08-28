/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:48:41 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/25 21:30:52 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_strlen2(const char *str);
char	*ft_strchr2(int c, const char *str);
char	*ft_strdup2(const char *str);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_substr2(const char *str, int start, size_t len);
char	*get_next_line(int fd);

#endif
