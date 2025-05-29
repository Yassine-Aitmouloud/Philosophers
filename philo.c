/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniki <aniki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/29 17:28:01 by aniki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mute;
int a = 0;

t_status	*g_thread(void)
{
	static t_status	infos = {0};

	return (&infos);
}

void printfker(t_philos *philos)
{
	printf("philo%d %s\n",philos->seat,"fker");
}

void printnaam(t_philos *philos)
{
	pthread_mutex_init(&philos->fork,0);
	printf("philo%d %s\n",philos->seat,"n3es");
	usleep(100);
}

void printkol(t_philos *philos)
{
	pthread_mutex_lock(&philos->fork);
	printf("philo%d %s\n",philos->seat,"kol");
	pthread_mutex_unlock(&philos->fork);
	usleep(100);
}

void *routine (void *something)
{
	printnaam(something);
    printkol(something);
    printfker(something);
	return (NULL);
}

void *garder (void *philo)
{
    int i = 0;
	g_thread()->philos = malloc(sizeof(t_philos) * (*(int *)philo));
	g_thread()->original = g_thread()->philos;
    while(i < (*(int *)philo))
    {
		pthread_create(&g_thread()->philos[i].phi_id, NULL, &routine, &philo);
		g_thread()->philos[i].seat = i;
        i++;
    }
    return (NULL);
}

void setup_philos (int philo)
{
    pthread_t mod;
	pthread_create(&mod, NULL, &garder, &philo);
}
int main(int ac, char **av)
{
	int i = 0;
	if (!av[1])
	return 1;
    int philos = atoi(av[1]);
    // int time_die = atoi(av[2]);
    // int eating = atoi(av[3]);
    // int sleeping = atoi(av[4]);
    i = 0;
	setup_philos(philos);
    while(i < philos)
    {
        pthread_join(g_thread()->original[i].phi_id,NULL);
		i++;
    }
    return 0;
}