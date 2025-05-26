/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/26 16:22:27 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mute;
int a = 0;

t_status	*g_status(void)
{
	static t_status	status = {0};

	return (&status);
}
void *printfker(t_philos *philos)
{
	pthread_mutex_lock(&mute);
	printf("philo%d %s\n",philos->seat,"fker");
	pthread_mutex_unlock(&mute);
    return NULL;
}

void *printnaam(t_philos *philos)
{
	pthread_mutex_lock(&mute);
	printf("philo%d %s\n",philos->seat,"n3es");
	pthread_mutex_unlock(&mute);
	usleep(10000000);
    return NULL;
}

void *printkol(t_philos *philos)
{
	pthread_mutex_lock(&mute);
	printf("philo%d %s\n",philos->seat,"kol");
	pthread_mutex_unlock(&mute);
	usleep(10000000);
    return NULL;
}
void *routine (void *something)
{
	printnaam();
    printkol();
    printfker();
	return (NULL);
}
void setup_philos (int philo)
{
	int i = 0;
	g_status()->philos = malloc(sizeof(t_philos) * philo);
	g_status()->original = g_status()->philos;
	while(i < philo)
    {
		
		pthread_create(&g_status()->philos->phi_id,NULL,&routine, &philos);
		philos->seat = i;
        i++;
		g_status->philos++;
    }
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
	pthread_mutex_init(&mute,0);
    i = 0;
    while(i < philos)
    {
        pthread_join(g_status()->original->phi_id,NULL);
        i++;
    }
    return 0;
}