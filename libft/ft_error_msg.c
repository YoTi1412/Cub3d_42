/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:59:09 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/07 22:58:12 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_error_msg(char *msg)
{
	ft_printf(RED "ERROR • %s\n" RESET, msg);
	exit(EXIT_FAILURE);
}
