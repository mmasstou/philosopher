/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:50:15 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/20 18:50:17 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	add_back(t_philo **lst, t_philo *new)
{
	t_philo	*last_node;

	if (!*lst)
	{
		add_front(lst, new);
		return ;
	}
	last_node = lstlast(*lst);
	last_node->next = new;
}
