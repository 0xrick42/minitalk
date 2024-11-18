#include "minitalk_bonus.h"

/* Global variable to store the current Unicode character being received */
static unsigned int g_current_char = 0;
static pid_t g_client_pid = 0;

/* Function implementations from the mandatory part */
void    error_exit(const char *msg)
{
    while (*msg)
        write(2, msg++, 1);
    exit(1);
}

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

void    ft_putstr(const char *str)
{
    while (*str)
        write(1, str++, 1);
}

/* Function to send acknowledgment to client */
void    send_acknowledgment(void)
{
    if (g_client_pid > 0)
    {
        if (kill(g_client_pid, SIGUSR1) == -1)
            error_exit("Error: Failed to send acknowledgment\n");
    }
}

/* Signal handler function with Unicode support */
void    handle_signal(int signum)
{
    static int  bit_count = 0;
    static int  bits_for_char = 0;

    /* Store client PID for acknowledgment */
    if (g_client_pid == 0)
        g_client_pid = signum;

    /* Determine number of bits needed for the character */
    if (bit_count == 0)
    {
        if ((g_current_char & 0x80) == 0)
            bits_for_char = 8;
        else if ((g_current_char & 0xE0) == 0xC0)
            bits_for_char = 16;
        else if ((g_current_char & 0xF0) == 0xE0)
            bits_for_char = 24;
        else if ((g_current_char & 0xF8) == 0xF0)
            bits_for_char = 32;
    }

    /* Build the character bit by bit */
    if (signum == SIGUSR1)
        g_current_char |= (1U << bit_count);
    bit_count++;

    /* When we have received all bits for the character */
    if (bit_count == bits_for_char)
    {
        write(1, &g_current_char, bits_for_char / 8);
        send_acknowledgment();
        bit_count = 0;
        g_current_char = 0;
        bits_for_char = 8;
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
