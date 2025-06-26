/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:16:38 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/26 15:41:58 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watcher(void *arg)
{
	int		i;
	long	last;

	(void)arg;
	while (1)
	{
		i = 0;
		while (i < g_thread()->numbers)
		{
			pthread_mutex_lock(&g_thread()->last_meal);
			last = g_thread()->philos[i].last_eat;
			pthread_mutex_unlock(&g_thread()->last_meal);
			if (get_time_ms() - last > g_thread()->time_die)
			{
				print_action(&g_thread()->philos[i], "died");
				pthread_mutex_lock(&g_thread()->death);
				g_thread()->someone_died = 1;
				pthread_mutex_unlock(&g_thread()->death);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	int			i;

	(void)arg;
	while (1)
	{
		i = 0;
		while (i < g_thread()->numbers)
		{
			if (check_for_death())
				return (NULL);
			if (g_thread()->must_eat > 0)
			{
				if (check_the_philos())
				{
					pthread_mutex_lock(&g_thread()->death);
					g_thread()->someone_died = 1;
					pthread_mutex_unlock(&g_thread()->death);
					return (NULL);
				}
			}
			i++;
		}
	}
	return (NULL);
}

long	get_last_meal(int i)
{
	long	last_meal;

	pthread_mutex_lock(&g_thread()->last_meal);
	last_meal = g_thread()->philos[i].last_eat;
	pthread_mutex_unlock(&g_thread()->last_meal);
	return (last_meal);
}

int	check_for_checked(int i)
{
	pthread_mutex_lock(&g_thread()->eating_count);
	if (g_thread()->philos[i].checked)
		return (pthread_mutex_unlock(&g_thread()->eating_count), 1);
	return (pthread_mutex_unlock(&g_thread()->eating_count), 0);
}

int	check_the_philos(void)
{
	int	i;

	i = 0;
	while (i < g_thread()->numbers)
	{
		if (!check_for_checked(i))
			return (0);
		i++;
	}
	return (1);
}
