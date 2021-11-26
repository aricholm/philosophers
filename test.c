/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:33:04 by aricholm          #+#    #+#             */
/*   Updated: 2021/11/16 16:40:21 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	struct timeval	tv;

	while (1)
	{
		gettimeofday(&tv, NULL);
		printf("tv: %ld - %ld\n", tv.tv_sec, tv.tv_usec);
		sleep(1);
	}
	return 0;
}

