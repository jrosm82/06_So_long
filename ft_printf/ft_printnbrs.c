/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:41:42 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/04 16:49:27 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_len(int nbr)
{
	int	pos;

	pos = 0;
	if (nbr == -2147483648)
		return (11);
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		pos++;
		nbr = nbr * -1;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		pos++;
	}
	return (pos);
}

int	uint_len(unsigned int nbr)
{
	int	pos;

	pos = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		pos++;
	}
	return (pos);
}

int	ft_putuint(unsigned int un)
{
	int	i;

	i = uint_len(un);
	if (un >= 10)
	{
		ft_putuint(un / 10);
		ft_putuint(un % 10);
	}
	else
		ft_putchar(un + '0');
	return (i);
}

int	ft_putint(int n)
{
	int	i;

	i = int_len(n);
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putint(n / 10);
		ft_putint(n % 10);
	}
	else
		ft_putchar(n + '0');
	return (i);
}
