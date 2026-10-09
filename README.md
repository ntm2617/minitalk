# 📡 Minitalk
*This project has been created as part of the 42 curriculum*
> A lightweight client-server inter-process communication (IPC) system using UNIX signals.

## 📖 Description

### 🎯 Goal
The objective of **Minitalk** is to code a small data exchange program between two separate processes using only **UNIX signals**. The communication takes place exclusively via `SIGUSR1` and `SIGUSR2`.

### 🔍 Overview
The project consists of two distinct programs:
- **`server`**: Starts first, displays its Process ID (PID), and waits for incoming signals. It reassembles received signals bit-by-bit into characters and prints them to `stdout`.
- **`client`**: Takes the server PID and a string as arguments. It translates each character into its 8-bit binary representation and transmits them sequentially to the server using `SIGUSR1` and `SIGUSR2`.

---

## 🕹️ Technical Breakdown

### 1. Bitwise Transmission Protocol ⚙️
Because UNIX signals only convey an event without payload data, characters are broken down into **8 individual bits**:
- **Bit `0`** $\rightarrow$ Sent as **`SIGUSR1`**
- **Bit `1`** $\rightarrow$ Sent as **`SIGUSR2`**

```text
Character 'A' (ASCII 65): 01000001
Client  ──► [SIGUSR1] [SIGUSR2] [SIGUSR1] [SIGUSR1] [SIGUSR1] [SIGUSR1] [SIGUSR1] [SIGUSR2] ──► Server
                                                                                   Reconstructed: 'A'
```

To prevent the Linux operating system from dropping signals due to signal queue limitations, the client uses a microsecond delay (`usleep(200)`). 
This also ensures 100 characters transmit within the 1-second limit required by the 42 subject.

### 2. Server Architecture 🔄
- Operates in a continuous `while (1) pause();` loop, saving CPU cycles until an interrupt arrives.
- Tracks bit count and bit shifting with `static` variables.
- Detects the null-terminator (`\0`) sent at the end of every message and appends a newline (`\n`) for clean formatting.

---

## 🛠️ Instructions

### 📦 Compilation

The repository includes a standard `Makefile`:

```bash
make        # Compiles both 'server' and 'client' executables
make clean  # Removes object (.o) files
make fclean # Removes object files and executables
make re     # Cleans and recompiles from scratch
```

### 🚀 Execution

#### 1. Start the Server
Open a terminal and start the server:
```bash
./server
```
*The server will print its Process ID (PID) and wait for messages:*
```text
42424
```

#### 2. Run the Client
Open a second terminal and send a message using the server's PID:
```bash
./client <SERVER_PID> "<STRING_TO_SEND>"
```

**Example:**
```bash
./client 42424 "Hello!!"
```

---

**Error Handling:**
  ```bash
  ./client              # Wrong argument count -> prints error
  ./client 999999 "hi"  # Non-existent PID -> prints error
  ./client -1 "hi"      # Invalid PID -> prints error
  ```

---

### 🎞️ Video


https://github.com/user-attachments/assets/ce1c44e5-646f-4dfc-9a5b-9446459587eb

