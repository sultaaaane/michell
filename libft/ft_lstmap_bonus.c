/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:00:14 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:54:55 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*head;
	void	*content;

	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		l = ft_lstnew(content);
		if (!l)
		{
			ft_lstclear(&head, del);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&head, l);
		lst = lst->next;
	}
	return (head);
}
