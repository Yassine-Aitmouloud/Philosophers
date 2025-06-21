/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:19:35 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/20 20:21:25 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	check_avs(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_int(av[i]) || atoi(av[i]) <= 0)
		{
			printf("Invalid argument: %s\n", av[i]);
			exit(1);
		}
		i++;
	}
	g_thread()->numbers = atoi(av[1]);
	g_thread()->time_die = atoi(av[2]);
	g_thread()->eating = atoi(av[3]);
	g_thread()->sleeping = atoi(av[4]);
	if (av[5] == NULL)
		g_thread()->must_eat = -1;
	else
		g_thread()->must_eat = atoi(av[5]);
}

t_threads	*g_thread(void)
{
	static t_threads	infos;

	return (&infos);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
