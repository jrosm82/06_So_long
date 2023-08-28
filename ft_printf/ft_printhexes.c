/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:40:27 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/04 17:12:08 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_hexdigits(uintptr_t value)
{
	int	count;

	count = 0;
	while (value > 0)
	{
		value = value / 16;
		count++;
	}
	return (count);
}

char	*print_p(uintptr_t value)
{
	static char	ptr[25];
	int			i;
	char		*hexlower;

	hexlower = "0123456789abcdef";
	if (value == 0)
		return ("(nil)");
	i = count_hexdigits(value);
	ptr[0] = '0';
	ptr[1] = 'x';
	ptr[i + 2] = '\0';
	i--;
	while (i >= 0)
	{
		ptr[i + 2] = hexlower[value % 16];
		value = value / 16;
		i--;
	}
	return (ptr);
}

char	*hex_dec(char c)
{
	if (c == 'x')
		return ("0123456789abcdef");
	else
		return ("0123456789ABCDEF");
}

char	*print_hex(unsigned int a, char hexchar)
{
	static char	ptr[25];
	char		*hexalph;	
	int			i;

	hexalph = hex_dec(hexchar);
	if (a == 0)
		return ("0");
	i = count_hexdigits(a);
	if (i > 0)
	{
		ptr[i] = '\0';
		i--;
		while (i >= 0)
		{
			ptr[i] = hexalph[a % 16];
			a = a / 16;
			i--;
		}	
		return (ptr);
	}
	else
		return (NULL);
}
