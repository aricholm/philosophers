/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:40:07 by aricholm          #+#    #+#             */
/*   Updated: 2021/11/10 17:06:01 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_queue	*add_queue(unsigned int philosopher)
{
	t_queue	*queue;

	queue = malloc(sizeof (t_queue));
	if (!queue)
		return (NULL);
	queue->philosopher = philosopher;
	queue->next = NULL;
	return (queue);
}

void	destroy_queue(t_queue *queue)
{
	t_queue	*tmp;

	while (queue)
	{
		tmp = queue->next;
		free (queue);
		queue = tmp;
	}
}

void	push_to_back(t_queue **queue)
{
	t_queue	*first;
	t_queue	*tmp;

	first = *queue;
	tmp = *queue;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = first;
	*queue = (*queue)->next;
	first->next = NULL;
}

t_queue	*init_queue(unsigned int philosophers)
{
	t_queue	*out;
	t_queue	*tmp;
	size_t	i;

	if (!philosophers)
		return (NULL);
	i = 1;
	out = add_queue(i);
	tmp = out;
	while (i < philosophers)
	{
		tmp->next = add_queue(i++);
		tmp = tmp->next;
	}
	return (out);
}
