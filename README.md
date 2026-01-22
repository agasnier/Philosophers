*This project has been created as part of the 42 curriculum by algasnie.*

# Philosophers

## Description
The **Philosophers** project intends to learn the basis of threading a process and using mutexes. 
This notion is worked with the dining philosophers problem: a table of X philosophers, each philosophers had his own fork, they must take on other fork from the philosphers a his right in order to eat. Each philosophers had time to eat, time to sleep and time to think. The goals is to make philosophers eat the maximum meals without dying of starve. When a phillosphers die of starving, all philosophers must stop eat, so a monitoring fonction verify in a loop during all the time of the process if a philosophers is dead.

## Instruction
Run the progam with a list of arguments that represent the number of philosophers and time of each action:

```./philo numbers_of_philosopers time_to_die time_to_eat time_to_sleep [number_of_meals_for_each (optional)]```

### Compilation
To compile the mandatory part:
```make```

To clean all object files (.o) for both parts:
```make clean```

To clean all object files and executables:
```make fclean```

## Resources
* Subject: 42 Philosophers
* Peer-Learning: Asking student that already finish the program, they deeply helped me to understand the subject.

## How it work

To share the reading and the modifying of a variable between each process we need to use mutexes.
A mutex is like a padlock, before reading or modifying a variable we need to ensure the padlock associated is unlocked. 

In this project we need three mutexes: one that protect each fork, one that protect the "died" state and the "last_meal" state in each philosophers.

Each philos has his own thread, to ensure all philo can eat we need to feed even ids brefore odd ids.
In this way we ensure that the maximum philosophers are eating at the same time.

At the launch of thread, the routine() represent these following action in a while(1) loop: eat(), sleep(), think(). 

eat() ensure each philo can take two forks, update the time of the last_meal and wait the time needed.
sleep() ensure each philo is sleeping the time needed.
thinking() ensure that the order of philos is respected, without a waiting time before eating one more time the philo that just finish his nap can overtake the philo that is waiting before him making him die.

Each situation a timer is need, the program use is_dead_timer() that cut the timer in small loop to check if the philo philo is dead while waiting.

Because each philosophers canno't talk between them we need to use a monitor(), a while(1) parse the tab of philo to check if they must die of starving. (difference between last_meal and the time_to_die). If a philo must die the monitor set the variable. This is this variable that is checked by the is_dead_timer(). So each philo kwows when there is a die.

If one philo is dead or all philos has eaten the numbers_must_eat of meal, if precised, the program stop.