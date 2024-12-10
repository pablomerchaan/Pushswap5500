/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:58:04 by paperez-          #+#    #+#             */
/*   Updated: 2024/05/29 12:47:24 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_printp(va_list args, char c);
int	ft_putnbr(int nb);
int	ft_puthexa(unsigned int h, const char c, int count);
int	ft_putpointer(void *p);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putuint(unsigned int n);
int	ft_puthexaux(unsigned long long h, char c, int count);
#endif
