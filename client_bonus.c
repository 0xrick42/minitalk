#include "minitalk_bonus.h"

/* Global variable to track if acknowledgment was received */
static volatile sig_atomic_t g_ack_received = 0;

/* Function implementations from the mandatory part */
int ft_atoi(const char *str)
{
    int result;
    int sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (sign * result);
}

void    error_exit(const char *msg)
{
    while (*msg)
        write(2, msg++, 1);
    exit(1);
}

/* Acknowledgment signal handler */
void    handle_acknowledgment(int signum)
{
    (void)signum;
    g_ack_received = 1;
}

/* Function to send a Unicode character bit by bit */
void    send_unicode_char(pid_t pid, unsigned int c)
{
    int     bit;
    int     bits_to_send;

    /* Determine number of bits needed for the character */
    if (c < 0x80)
        bits_to_send = 8;
    else if (c < 0x800)
        bits_to_send = 16;
    else if (c < 0x10000)
        bits_to_send = 24;
    else
        bits_to_send = 32;

    /* Reset acknowledgment flag */
    g_ack_received = 0;

    /* Send each bit of the character */
    for (bit = 0; bit < bits_to_send; bit++)
    {
        /* Send SIGUSR1 for 1, SIGUSR2 for 0 */
        if (c & (1U << bit))
        {
            if (kill(pid, SIGUSR1) == -1)
                error_exit("Error: Failed to send signal\n");
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
                error_exit("Error: Failed to send signal\n");
        }

        /* Wait for acknowledgment with timeout */
        int timeout = 1000; /* 100ms timeout */
        while (!g_ack_received && timeout > 0)
        {
            usleep(100);
            timeout--;
        }
        if (timeout == 0)
            error_exit("Error: Server not responding\n");
    }
}

int main(int argc, char **argv)
{
    pid_t               server_pid;
    char                *message;
    struct sigaction    sa;

    /* Check arguments */
    if (argc != 3)
        error_exit("Error: Wrong number of arguments\nUsage: ./client_bonus [server_pid] [message]\n");

    /* Setup acknowledgment signal handler */
    sa.sa_handler = handle_acknowledgment;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        error_exit("Error: Failed to setup signal handler\n");

    /* Get server PID and message */
    server_pid = ft_atoi(argv[1]);
    message = argv[2];

    /* Check if PID is valid */
    if (server_pid <= 0)
        error_exit("Error: Invalid server PID\n");

    /* Send each character */
    while (*message)
    {
        send_unicode_char(server_pid, (unsigned char)*message);
        message++;
    }

    /* Send newline */
    send_unicode_char(server_pid, '\n');

    return (0);
}
