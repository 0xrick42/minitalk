# Minitalk Project Explanation

## Overview
Minitalk is a communication program that implements a small data exchange protocol using UNIX signals (SIGUSR1 and SIGUSR2). It consists of a server and a client that communicate with each other using only these signals.

## How It Works
The program uses binary communication where:
- SIGUSR1 represents binary 1
- SIGUSR2 represents binary 0

Each character is sent bit by bit (8 bits) from the client to the server.

## Components Explanation

### Client (client.c)
#### Functions:

1. `ft_atoi(const char *str)`
   - Purpose: Converts a string representation of a number into an integer
   - Used for: Converting the server PID from string to integer
   - Parameters: String containing the number
   - Returns: The converted integer value

2. `send_char(int server_pid, char character)`
   - Purpose: Sends a single character to the server bit by bit
   - Process: 
     - Breaks down each character into 8 bits
     - Sends SIGUSR1 for 1s and SIGUSR2 for 0s
     - Uses 500 microseconds delay between signals to prevent signal loss
   - Parameters:
     - server_pid: The PID of the server to send signals to
     - character: The character to be sent

3. `main(int argc, char **argv)`
   - Purpose: Entry point, handles command line arguments and initiates communication
   - Process:
     - Validates input (requires server PID and message)
     - Converts server PID from string to integer
     - Sends each character of the message to the server

### Server (server.c)
#### Functions:

1. `handle_signal(int signal)`
   - Purpose: Processes received signals and reconstructs characters
   - Process:
     - Accumulates bits using static variables
     - After receiving 8 bits, reconstructs and prints the character
     - Resets counters for the next character
   - Parameters:
     - signal: The received signal (SIGUSR1 or SIGUSR2)

2. `main(int argc, char **argv)`
   - Purpose: Sets up the server and signal handlers
   - Process:
     - Prints server PID for client use
     - Sets up signal handlers
     - Enters infinite loop waiting for signals

## Bonus Features (client_bonus.c & server_bonus.c)

### Additional Features:

1. `handle_confirmation(int signal)` (client_bonus.c)
   - Purpose: Handles receipt confirmation from server
   - Process: Prints confirmation message when server acknowledges receipt

2. `handle_signal(int signal, siginfo_t *client_info, void *context)` (server_bonus.c)
   - Purpose: Enhanced signal handler with client information
   - Additional features:
     - Sends confirmation back to client
     - Supports Unicode characters
     - Adds newline after complete messages
     - Uses sigaction for better signal handling

## Key Differences Between Regular and Bonus Versions:

1. Regular Version:
   - Basic one-way communication
   - No receipt confirmation
   - Simple signal handling

2. Bonus Version:
   - Two-way communication (confirmation signals)
   - Enhanced error handling
   - Support for longer messages
   - Better signal handling with sigaction
   - Message completion notification

## Technical Details:
- Uses POSIX signals for communication
- Implements binary data transfer using only two signals
- Handles process synchronization
- Uses static variables for maintaining state between signal handler calls
- Implements proper error handling and input validation

## Usage:
1. Compile both server and client
2. Start the server first (it will display its PID)
3. Run the client with server PID and message as arguments
4. For bonus version, wait for confirmation message
