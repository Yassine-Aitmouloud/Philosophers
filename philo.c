/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/21 16:59:15 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	use_usleep(long duration)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration)
		usleep(50);
}

int	is_died(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&g_thread()->death);
	i = g_thread()->someone_died;
	pthread_mutex_unlock(&g_thread()->death);
	return (i);
}

void	create_philos(void)
{
	int	i;

	i = 0;
	while (i < g_thread()->numbers)
	{
		g_thread()->philos[i].checked = 0;
		g_thread()->philos[i].seat = i;
		g_thread()->philos[i].last_eat = get_time_ms();
		g_thread()->philos[i].meals_eaten = 0;
		pthread_create(&g_thread()->philos[i].phi_id, NULL, &routine,
			&g_thread()->philos[i]);
		i++;
	}
}

void	get_start(void)
{
	int	i;

	i = 0;
	g_thread()->someone_died = 0;
	pthread_mutex_init(&g_thread()->mute, NULL);
	pthread_mutex_init(&g_thread()->printing, NULL);
	pthread_mutex_init(&g_thread()->eating_count, NULL);
	pthread_mutex_init(&g_thread()->death, NULL);
	pthread_mutex_init(&g_thread()->last_meal, NULL);
	g_thread()->philos = malloc(sizeof(t_philos) * g_thread()->numbers);
	g_thread()->forks = malloc(sizeof(pthread_mutex_t) * g_thread()->numbers);
	while (i < g_thread()->numbers)
		pthread_mutex_init(&g_thread()->forks[i++], NULL);
}

int	main(int ac, char **av)
{
	pthread_t	mon = 0;
	int			i;

	i = 0;
	if (ac != 6 && ac != 5)
		return (1);
	check_avs(av);
	g_thread()->start = get_time_ms();
	get_start();
	create_philos();
	if (g_thread()->numbers > 1)
		pthread_create(&mon, NULL, &monitor, NULL);
	pthread_join(mon, NULL);
	while (i < g_thread()->numbers)
	{
		pthread_join(g_thread()->philos[i].phi_id, NULL);
		i++;
	}
	free(g_thread()->philos);
	free(g_thread()->forks);
	return (0);
}
