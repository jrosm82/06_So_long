/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:14:43 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/06 14:28:03 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putpct(char c)
{
	ft_putchar('%');
	ft_putchar(c);
	return (2);
}

static int	pnt_decide(char c, va_list ap, int prn_cnt)
{
	if (c == 'c')
		prn_cnt += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		prn_cnt += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		prn_cnt += ft_putstr(print_p(va_arg(ap, uintptr_t)));
	else if (c == 'i' || c == 'd')
		prn_cnt += ft_putint(va_arg(ap, int));
	else if (c == 'u')
		prn_cnt += ft_putuint(va_arg(ap, unsigned int));
	else if (c == 'x')
		prn_cnt += ft_putstr(print_hex(va_arg(ap, unsigned int), 'x'));
	else if (c == 'X')
		prn_cnt += ft_putstr(print_hex(va_arg(ap, unsigned int), 'X'));
	else if (c == '%')
		prn_cnt += ft_putchar('%');
	else
		prn_cnt += ft_putpct(c);
	return (prn_cnt);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		prn_cnt;

	prn_cnt = 0;
	i = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			prn_cnt += pnt_decide(str[i], ap, 0);
		}
		else
		{
			prn_cnt += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(ap);
	return (prn_cnt);
}
/*
int	main(void)
{
	int	pnt = -2147483648;
	int	*ptr = &pnt;
	int	a = 0;
	unsigned long long b = 0;
	char *p = NULL;
	unsigned int u = 4294967295;

	printf("%d",printf("   PRINTF->*[u-%u]**[u-%u]* =", u, 0));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->*[u-%u]**[u-%u]* =", u, 0));
	printf("\n\n");

	   printf("%d",printf("   PRINTF->*[c-%c]**[d-%d]* =",'A',pnt));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->*[c-%c]**[d-%d]* =",'A',pnt));
	printf("\n\n");

	   printf("%d",printf("   PRINTF->**[i-%i]**[s-%s] =", pnt, "aa"));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->**[i-%i]**[s-%s] =", pnt, "aa"));
	printf("\n\n");

	   printf("%d",printf("   PRINTF->* **[pct-%%]***[p-%p]***=", ptr));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->* **[pct-%%]***[p-%p]***=", ptr));
	printf("\n\n");
	
	   printf("%d",printf("   PRINTF->* **[x-%x]**[X-%X]*=", 2147483647, 150378));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->* **[x-%x]**[X-%X]*=", 2147483647, 150378));
	printf("\n\n");

	   printf("%d", printf("   PRINTF->****[c-%c]****[s-%s]*****=", '\0', p));
	printf("\n");
	printf("%d", ft_printf("FT_PRINTF->****[c-%c]****[s-%s]*****=", '\0', p));	
	printf("\n\n");

	   printf("%d", printf("   PRINTF->******[s-%s]*****[s-%s]***=", "", " "));
	printf("\n");
	printf("%d", ft_printf("FT_PRINTF->******[s-%s]*****[s-%s]***=", "", " "));	
	printf("\n\n");

	   printf("%d", printf("   PRINTF-> [p-%p] [p-%p]  =", &a, b));
	printf("\n");
	printf("%d", ft_printf("FT_PRINTF-> [p-%p] [p-%p]  =", &a, b));
	printf("\n\n");
	return(0);
}




#include <stdio.h>

int	main(void)
{
	int	pnt = -2147483648;
	int	*ptr = &pnt;
	int	a = 0;
	unsigned long long b = 0;
	char *p = NULL;

	   printf("%d",printf("   PRINTF->*[%c]**[%d]* =",'A',pnt));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->*[%c]**[%d]* =",'A',pnt));
	printf("\n\n");

	   printf("%d",printf("   PRINTF->**[%i]**[%s] =", pnt, "aa"));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->**[%i]**[%s] =", pnt, "aa"));
	printf("\n\n");

	   printf("%d",printf("   PRINTF->* **[%%]***[%p]***=", ptr));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->* **[%%]***[%p]***=", ptr));
	printf("\n\n");
	
	   printf("%d",printf("   PRINTF->* **[%x]**[%X]*=", 2147483647, 150378));
	printf("\n");
	printf("%d",ft_printf("FT_PRINTF->* **[%x]**[%X]*=", 2147483647, 150378));
	printf("\n\n");

	   printf("%d", printf("   PRINTF->****[%c]****[%s]*****=", '\0', p));
	printf("\n");
	printf("%d", ft_printf("FT_PRINTF->****[%c]****[%s]*****=", '\0', p));	
	printf("\n\n");

	   printf("%d", printf("   PRINTF->******[%s]*****[%s]***=", "", " "));
	printf("\n");
	printf("%d", ft_printf("FT_PRINTF->******[%s]*****[%s]***=", "", " "));	
	printf("\n\n");

	   printf("%d", printf("   PRINTF-> [%p] [%p]  =", &a, b));
	printf("\n");
	printf("%d", ft_printf("FT_PRINTF-> [%p] [%p]  =", &a, b));
	printf("\n\n");
	return(0);
}*/
