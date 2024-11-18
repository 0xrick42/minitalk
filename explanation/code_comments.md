# Detailed Code Comments

## Client (client.c)

```c
// ft_atoi: String to integer conversion
// Handles whitespace, signs, and numeric characters
// Returns the converted number with appropriate sign
static int ft_atoi(const char *str)

// send_char: Sends a character as binary signals
// Uses bitwise operations to extract each bit
// Sends SIGUSR1 for 1 and SIGUSR2 for 0
// Includes delay to ensure signal reception
void send_char(int server_pid, char character)

// Main function:
// 1. Validates command line arguments
// 2. Converts server PID to integer
// 3. Sends message character by character
int main(int argc, char **argv)
```

## Server (server.c)

```c
// handle_signal: Processes incoming signals
// Uses static variables to maintain state between calls
// Reconstructs character bit by bit
// Prints character when all 8 bits are received
void handle_signal(int signal)

// Main function:
// 1. Validates no arguments were provided
// 2. Displays server PID
// 3. Sets up signal handlers
// 4. Enters infinite loop waiting for signals
int main(int argc, char **argv)
```

## Client Bonus (client_bonus.c)

```c
// handle_confirmation: Processes server acknowledgment
// Prints success message when server confirms receipt
void handle_confirmation(int signal)

// ft_atoi: Same as regular client
// Enhanced error checking for bonus version
static int ft_atoi(const char *str)

// send_char: Similar to regular client
// Added reliability with signal synchronization
void send_char(int server_pid, char character)

// Main function:
// Additional features:
// - Sets up confirmation handler
// - Sends null terminator
// - Waits for server confirmation
int main(int argc, char **argv)
```

## Server Bonus (server_bonus.c)

```c
// handle_signal: Enhanced signal handler
// Additional features:
// - Uses sigaction structure for better signal handling
// - Tracks client PID for confirmation
// - Handles message termination
// - Adds formatting (newlines)
void handle_signal(int signal, siginfo_t *client_info, void *context)

// Main function:
// Enhanced features:
// - Uses sigaction for advanced signal handling
// - Better error messages
// - Improved signal handler setup
int main(int argc, char **argv)
```

## Key Implementation Details

### Signal Handling
- SIGUSR1 represents binary 1
- SIGUSR2 represents binary 0
- 500 microsecond delay between signals prevents loss
- Static variables maintain state between signal handler calls

### Character Transmission
1. Character is broken into 8 bits
2. Each bit sent as a signal (SIGUSR1/SIGUSR2)
3. Server reconstructs bits into character
4. Character printed when complete

### Bonus Features
1. Two-way communication
2. Message completion detection
3. Client notification
4. Better signal handling with sigaction
5. Support for longer messages

### Error Handling
- Input validation
- PID verification
- Signal handling errors
- Memory management
- Process synchronization
