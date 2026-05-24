*This project has been created as part of the 42 curriculum by slambert.*

# Philosophers

## Description

Philosophers is a project exploring the classic **Dining Philosophers Problem** — a fundamental concurrency problem originally formulated by Edsger Dijkstra. The goal is to simulate a group of philosophers sitting around a table with a bowl of spaghetti, where each philosopher alternates between eating, thinking, and sleeping.

The core challenge is to prevent **deadlocks** and **starvation** while managing shared resources (forks) safely using **threads** and **mutexes**.

Key learning objectives:
- Creating and managing POSIX threads with `pthread_create`, `pthread_join`, and `pthread_detach`
- Protecting shared state using mutexes (`pthread_mutex_lock`, `pthread_mutex_unlock`)
- Precise time management with `gettimeofday` and `usleep`
- Avoiding data races in a concurrent environment

### Rules

- One or more philosophers sit at a round table with a large bowl of spaghetti in the middle.
- There is one fork between each pair of adjacent philosophers (as many forks as philosophers).
- To eat, a philosopher must hold **both** the left and right fork simultaneously.
- Philosophers cycle through three states: **eating → sleeping → thinking**.
- The simulation ends when a philosopher dies of starvation, or when all philosophers have eaten the required number of times (if specified).
- Philosophers do not communicate with each other.
- A death message must be displayed within **10ms** of the actual death.
- No data races are allowed.

---

## Instructions

### Compilation

```bash
make
```

This produces the `philo` binary. To clean up:

```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full rebuild
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

All arguments must be **positive integers**. Whitespace is **NOT** allowed.

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers at the table |
| `time_to_die` (ms) | Time before a philosopher dies if they haven't started eating since their last meal or the start of the simulation |
| `time_to_eat` (ms) | Time it takes to eat (requires holding two forks) |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops once all philosophers have eaten at least this many times |

### Examples

```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same, but stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher (only one fork available, will die)
./philo 1 800 200 200
```

### Output Format

Each state change is logged as:

timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died

Where `timestamp_in_ms` is the time elapsed since the simulation started (in milliseconds) and `X` is the philosopher's number (starting at 1).

---

## Resources

### Documentation & References

- [`pthread` manual — `man 7 pthreads`](https://man7.org/linux/man-pages/man7/pthreads.7.html) — comprehensive overview of POSIX threads
- [`gettimeofday` manual — `man 2 gettimeofday`](https://man7.org/linux/man-pages/man2/gettimeofday.2.html) — used for millisecond-precision timing
- [`usleep` manual — `man 3 usleep`](https://man7.org/linux/man-pages/man3/usleep.3.html) — microsecond sleep
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — original problem description and classic solutions
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/) — in-depth tutorial on pthreads

### AI Usage

AI was used during this project for the following tasks:
- Checking the header file for duplicate declarations
- Verifying chronological ordering of simulation log output
- Generating this README based on the subject PDF
- further conceptional explanations on the theoretical concepts