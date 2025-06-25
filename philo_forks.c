/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:12:11 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/25 21:07:46 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(int right, int left, t_philos *philos)
{
	(void)philos;
	if (philos->seat + 1 == g_thread()->numbers - 1)
	{
		pthread_mutex_lock(&g_thread()->forks[left]);
		pthread_mutex_lock(&g_thread()->forks[right]);
		print_action(philos, "take left fork");
		print_action(philos, "take right fork");
	}
	else
	{
		pthread_mutex_lock(&g_thread()->forks[right]);
		pthread_mutex_lock(&g_thread()->forks[left]);
		print_action(philos, "take right fork");
		print_action(philos, "take left fork");
	}
}

void	unlock_forks(int right, int left, t_philos *philos)
{
	if (philos->seat == g_thread()->numbers - 1)
	{
		pthread_mutex_unlock(&g_thread()->forks[left]);
		pthread_mutex_unlock(&g_thread()->forks[right]); 
	}
	else
	{
		pthread_mutex_unlock(&g_thread()->forks[right]);
		pthread_mutex_unlock(&g_thread()->forks[left]);
	}
}

void	take_the_forks(t_philos *philos)
{
	int	left;
	int	right;

	left = philos->seat;
	right = (philos->seat + 1) % g_thread()->numbers;
	lock_forks(right, left, philos);
}

void	clean_up(void)
{
	int	i;

	i = 0;
	while (i < g_thread()->numbers)
		pthread_mutex_destroy(&g_thread()->forks[i++]);
	pthread_mutex_destroy(&g_thread()->printing);
	pthread_mutex_destroy(&g_thread()->eating_count);
	pthread_mutex_destroy(&g_thread()->death);
	pthread_mutex_destroy(&g_thread()->last_meal);
	pthread_mutex_destroy(&g_thread()->table);
	free(g_thread()->philos);
	free(g_thread()->forks);
}
