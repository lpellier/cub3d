/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:56:30 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 15:53:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# define CONVERTER "ciduxXps%"
# include <stdarg.h>
# include "cub3d.h"

/*
** Infos padding : if 1 -> '0' && if 2 -> '-'
*/

typedef struct		s_printf
{
	int				width;
	int				number;
	int				precision;
	int				padding;
	int				outputlen;
	int				plus;
	int				minus;
	int				space;
	int				perc;
	int				count;
	int				len;
	int				orig;
	char			type;
}					t_printf;

/*
**----------------- Libft functions -------------------
*/

void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnstr_fd(char *s, int size, int fd);
int					ft_intlen(long n);
char				*ft_int_hexmax(long n, char *tab);
char				*ft_int_hexmin(long n, char *tab);
int					ft_uintlen(unsigned long n);
void				ft_putunbr_fd(unsigned int n, int fd);
size_t				digit_count(long value, int base);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);

/*
**----------------- Filling information -------------------
*/

const char			*checkwidth(const char *format, t_printf *info, va_list ap);
const char			*checkprecision(const char *format, t_printf *info, \
					va_list ap);
const char			*checktype(const char *format, t_printf *info);
const char			*ft_fill_struct(const char *format, t_printf *info, \
					va_list ap);

/*
**--------------------------------------------------------------**
**-------------------------- Output ----------------------------**
**--------------------------------------------------------------**
*/

int					count_format(const char *format);
void				output_flags(t_printf *info);
int					output_sign(t_printf *info, int res);
void				put_zeros(t_printf *info);
void				output_string(t_printf *info, va_list ap);
void				output_int(t_printf *info, va_list ap);
void				output_uint(t_printf *info, va_list ap);
void				output_char(t_printf *info, va_list ap);
void				output_adress(t_printf *info, va_list ap);
void				output_hexmin(t_printf *info, va_list ap);
void				output_hexmax(t_printf *info, va_list ap);
const char			*print_before(const char *format, t_printf *info);
const char			*print_aoutsider(const char *format, t_printf *info);
const char			*init_perc(t_printf *info, const char *format);
void				check_padding_case_int(t_printf *info, int res);
void				check_padding_case_adress(t_printf *info, void *res, \
					char *str);
void				check_padding_case_hex(t_printf *info, void *ret);
void				check_padding_case(t_printf *info);
void				ft_output(t_printf *info, va_list ap);

int					ft_printf(const char *format, ...);

#endif
