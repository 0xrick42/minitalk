#include "minitalk.h"

/* Global variable to store the current character being received */
static unsigned char g_current_char = 0;

/* Function to handle errors and exit */
void    error_exit(const char *msg)
{
    while (*msg)
        write(2, msg++, 1);
    exit(1);
}

/* Function to write a number */
void    ft_putnbr(int n)
{
    char    c;

    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10);
    c = '0' + (n % 10);
    write(1, &c, 1);
}

/* Function to write a string */
void    ft_putstr(const char *str)
{
    while (*str)
        write(1, str++, 1);
}

/* Signal handler function */
void    handle_signal(int signum)
{
    static int  bit_count = 0;

    /* Build the character bit by bit */
    if (signum == SIGUSR1)
        g_current_char |= (1 << bit_count);
    bit_count++;

    /* When we have received all 8 bits */
    if (bit_count == 8)
    {
        write(1, &g_current_char, 1);
        bit_count = 0;
        g_current_char = 0;
    }
}

int main(void)
{
    struct sigaction    sa;

    /* Print server PID */
    ft_putstr("Server PID: ");
    ft_putnbr(getpid());
    ft_putstr("\n");

    /* Setup signal handling */
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    /* Register signal handlers */
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
        error_exit("Error: Failed to setup signal handlers\n");

    /* Wait for signals indefinitely */
    while (1)
        pause();
    return (0);
}
