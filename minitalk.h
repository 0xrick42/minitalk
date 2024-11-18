#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

/* Function to handle errors and exit gracefully */
void    error_exit(const char *msg);

/* Function to convert string to integer safely */
int     ft_atoi(const char *str);

/* Function to write a string to standard output */
void    ft_putstr(const char *str);

/* Function to write a number to standard output */
void    ft_putnbr(int n);

#endif
