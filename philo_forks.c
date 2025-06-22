/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:12:11 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/22 10:00:09 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(int right, int left, t_philos *philos)
{
	if (left < right)
	{
		pthread_mutex_lock(&g_thread()->forks[left]);
		print_action(philos, "take left fork");
		pthread_mutex_lock(&g_thread()->forks[right]);
		print_action(philos, "take right fork");
	}
	else
	{
		pthread_mutex_lock(&g_thread()->forks[right]);
		print_action(philos, "take right fork");
		pthread_mutex_lock(&g_thread()->forks[left]);
		print_action(philos, "take left fork");
	}
}

void	unlock_forks(int right, int left)
{
	if (left < right)
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
	// unlock_forks(right, left);
}
