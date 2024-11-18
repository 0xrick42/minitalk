#include "minitalk.h"

/* Function to handle errors and exit */
void    error_exit(const char *msg)
{
    while (*msg)
        write(2, msg++, 1);
    exit(1);
}

/* Function to convert string to integer */
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

/* Function to send a character bit by bit */
void    send_char(pid_t pid, unsigned char c)
{
    int bit;

    /* Send each bit of the character */
    for (bit = 0; bit < 8; bit++)
    {
        /* Send SIGUSR1 for 1, SIGUSR2 for 0 */
        if (c & (1 << bit))
        {
            if (kill(pid, SIGUSR1) == -1)
                error_exit("Error: Failed to send signal\n");
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
                error_exit("Error: Failed to send signal\n");
        }
        usleep(100); /* Small delay to prevent signal loss */
    }
}

int main(int argc, char **argv)
{
    pid_t   server_pid;
    char    *message;

    /* Check arguments */
    if (argc != 3)
        error_exit("Error: Wrong number of arguments\nUsage: ./client [server_pid] [message]\n");

    /* Get server PID and message */
    server_pid = ft_atoi(argv[1]);
    message = argv[2];

    /* Check if PID is valid */
    if (server_pid <= 0)
        error_exit("Error: Invalid server PID\n");

    /* Send each character */
    while (*message)
    {
        send_char(server_pid, *message);
        message++;
    }

    /* Send null terminator */
    send_char(server_pid, '\n');

    return (0);
}
