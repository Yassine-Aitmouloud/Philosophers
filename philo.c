/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniki <aniki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/26 01:39:45 by aniki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mute;
int a = 0;

void *printfker(void *str)
{
    // char *copy = (char *)str;
    int j = 0;
    while(j < 1)
    {   
        pthread_mutex_lock(&mute);
        printf("%s\n","fker");
        j++;
        pthread_mutex_unlock(&mute);
    }
    return NULL;
}

void *printnaam(void *str)
{
    // char *copy = (char *)str;
    int j = 0;
    while(j < 1)
    {   
        pthread_mutex_lock(&mute);
        printf("%s\n","n3es");
        j++;
        pthread_mutex_unlock(&mute);
    }
    return NULL;
}

void *printkol(void *str)
{
    // char *copy = (char *)str;
    int j = 0;
    while(j < 1)
    {   
        pthread_mutex_lock(&mute);
        printf("%s\n","kol");
        j++;
        pthread_mutex_unlock(&mute);
    }
    return NULL;
}
int main(int ac, char **av)
{
    int i = 0;
    int philos = atoi(av[1]);
    // int time_die = atoi(av[2]);
    // int eating = atoi(av[3]);
    // int sleeping = atoi(av[4]);
    pthread_t threads[philos];
    while(i < philos)
    {
        pthread_create(&threads[i],NULL,printnaam, "hello");
        while(usleep(1000000));
        pthread_create(&threads[i],NULL,printkol, "hello");
        while(usleep(1000000));      
        pthread_create(&threads[i],NULL,printfker, "hello");
        while(usleep(1000000));
        i++;
    }
    i = 0;
    while(i < philos)
    {
        pthread_join(threads[i],NULL);
        i++;
    }
    return 0;
}