/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:41:29 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/10 22:01:05 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	is_number(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ph_atoi(const char *str)
{
	size_t	i;
	int		out;

	i = 0;
	out = 0;
	while (str[i])
		out = out * 10 + (str[i++] - '0');
	return (out);
}

int	get_data(t_setup *setup, int argc, const char *argv[])
{
	if (!is_number(argv[1]) || !is_number(argv[2]) || !is_number(argv[3])
		|| !is_number(argv[4]))
		return (1);
	setup->max_philo = ph_atoi(argv[1]);
	if (!setup->max_philo)
		return (1);
	setup->time_to_die = ph_atoi(argv[2]);
	setup->time_to_eat = ph_atoi(argv[3]);
	setup->time_to_sleep = ph_atoi(argv[4]);
	if (argc == 6)
	{
		if (is_number(argv[5]))
			setup->times_to_eat = ph_atoi(argv[5]);
		else
			return (1);
	}
	else
		setup->times_to_eat = 0;
	return (0);
}
