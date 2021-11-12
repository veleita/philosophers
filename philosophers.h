/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:16:20 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/12 10:05:34 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>	// INT_MAX
# include <stdbool.h>	// bool type
# include <pthread.h>	// threads and mutex
# include <string.h>	// memset
# include <unistd.h>	// write
# include <stdlib.h>	// malloc, free
# include <sys/time.h>	// gettimeofday
# include <stdio.h>	// printf

# define CORRECT 0
# define FAIL 0
# define DONE 1

# define AVAIABLE 0
# define TAKEN 1

# define FORKS		"has taken the forks"
# define FORKSNT	"has left the forks"
# define EAT 		"is eating"
# define SLEEP 		"is sleeping"
# define WAKE 		"woke up!"
# define THINK 		"is thinking"
# define DIE 		"died"

/************ STRUCTS ************/

typedef struct s_fork
{
	pthread_mutex_t		*mutex;
	int					state;
}						t_fork;
/*
** t_config
**  Main features, all threads share this information
** 
**	Program's arguments
**		-number_of_philosophers: Pretty self-explanatory
**		-time_to_die: 			 Ms they can stay alive without eating
**		-time_to_eat: 			 Ms they take to eat
**		-time_to_sleep:			 Ms they take to sleep
**		-number_of_times_each_philosopher_must_eat:
**								 Before the simulation stops (optional)
**
**	Program's internal parameters
**		-on: 		State of simulation, if it turns 0, the simulation stops
**		-start: 	Timestamp of the beginning of the program
**		-printer: 	Mutex that controls message prints
**		-forks: 	Array of pointers to forks, each fork is a mutex
*/
typedef struct s_config
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_meals;
	t_fork			**forks;
	pthread_mutex_t	printer;
	bool			stop_simulation;
	struct timeval	start_time;
}					t_config;

/*
** t_philosopher
**  There is one of these for each philosopher
**
**	-id: 		Philosopher's identifier
**	-meals: 	Number of times the philosopher ate
**	-timestamp: Last time the philosopher ate
** 	-thread: 	Pointer to philosopher's thread
** 	-timelock: 	Mutex that protects access to last_meal_time
**	-p: 		Pointer to the struct above
*/
typedef struct s_philosopher {
	int				id;
	int				number_of_meals;
	struct timeval	last_meal_time;
	pthread_mutex_t	timelock;
	pthread_t		*thread;
	t_config		*common;
}	t_philosopher;

/************ FUNCTION DEFINITIONS *************/

/* init.c */
t_config		get_common(char **argv);
t_fork			**get_forks(int number_of_philos);
t_philosopher	**get_philos(t_config *common);
void			launch_philos(int number_of_philosophers,
					t_philosopher **philos);
int				check_args(char **argv, int argc);

/* utils.c */
unsigned int	ft_atoi(char *str);
bool			ft_str_isdigit(char *str);
int				ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);

/* custom_utils.c */
void			ft_usleep(int ms, bool *stop_simulation);
void			printer(const char *message, int philo_id, t_config *common);
long int		time_struct_to_int(struct timeval s);
long int		get_time_lapse(struct timeval t1, struct timeval t2);
bool			num_correct(unsigned int num);

/* simulation.c */
void			check_stop_conditions(t_config *common, t_philosopher **philos);
void			*start_routine(void *arg);

/* life_cycle.c */
void			take_forks(int philo_id, int last_philo, t_config *common);
void			eat_and_sleep(int philo_id, int last_philo, t_config *common,
					t_philosopher *stats);

/* termination.c */
void			death(int dead_philo_id, t_config *common,
					t_philosopher **philos, bool *have_eaten_n_times);
void			terminate(t_philosopher **philos, t_config *common);
int				one_philo(t_config *common);

#endif
