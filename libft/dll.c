/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:52:30 by yrafai            #+#    #+#             */
/*   Updated: 2025/04/07 17:53:35 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_dll	*ft_dbl_lstlast(t_dll *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_dbl_lstadd_back(t_dll **lst, t_dll *new_list)
{
	t_dll	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new_list;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	new_list->prev = tmp;
	tmp->next = new_list;
}

t_dll	*ft_dbl_lstnew(char *content)
{
	t_dll	*new_node;

	new_node = malloc(sizeof(t_dll));
	if (!new_node)
		return (NULL);
	new_node->string = ft_strdup(content);
	if (!new_node->string)
	{
		free(new_node);
		return (NULL);
	}
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	ft_dbl_lstsize(t_dll *start, t_dll *end, int *cols)
{
	int	i;
	int	tmp;

	i = 0;
	while (start != end->next)
	{
		tmp = ft_strlen(start->string) - 1;
		if (*cols < tmp)
			*cols = tmp;
		start = start->next;
		i++;
	}
	return (i);
}
