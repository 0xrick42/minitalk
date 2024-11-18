#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

/* Maximum number of bits for Unicode character (32-bit) */
# define MAX_BITS 32

/* Function to handle errors and exit gracefully */
void    error_exit(const char *msg);

/* Function to convert string to integer safely */
int     ft_atoi(const char *str);

/* Function to write a string to standard output */
void    ft_putstr(const char *str);

/* Function to write a number to standard output */
void    ft_putnbr(int n);

/* Signal handler type for client acknowledgment */
typedef void (*sig_handler_t)(int);

#endif
