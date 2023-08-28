/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:11:51 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/04 17:11:29 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>

int		ft_putchar(int c);
int		ft_putstr(char *s);

int		int_len(int nbr);
int		uint_len(unsigned int nbr);
int		ft_putuint(unsigned int n);
int		ft_putint(int n);

int		count_hexdigits(uintptr_t value);
char	*print_p(uintptr_t value);
char	*hex_dec(char c);
char	*print_hex(unsigned int a, char hexchar);

int		ft_printf(const char *str, ...);

#endif
