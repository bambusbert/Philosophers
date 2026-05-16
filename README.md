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

All arguments must be **positive integers**.

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

TODO:

./philo 3 600 200 200 DOES NOT WORK bt i think that's OK bc of the tight timings (3 601 200 200 works)

 3 600 200 200 10
 199 600 200 200 10
"args": ["2", "800", "200", "2147483647"],

c2r1p1% ./test.sh ../philo

42 Philosophers Tester  2026/05/16
Iterations: 10

Mandatory tests (eval sheet)            [0]

Normal tests                            [1]
Hardcore tests (a lot)                  [2]

Exit Tester                             [ESC]



Please choose:2

42 Philosophers Tester  2026/05/16
Iterations: 10

All tests                               [0]

Uneven numbers that shouldn't die       [1]
Even numbers that shouldn't die         [2]
All numbers that shouldn't die          [3]

Uneven numbers that should die          [4]
Even numbers that should die            [5]
All numbers that should die             [6]

Own tests                               [7]
Exit Tester                             [ESC]



Please choose:0
Testing uneven numbers - they shouldn't die

        5 800 200 200 10
1       Pass    [✓]     4802 3 has taken a fork
2       Pass    [✓]     4803 3 has taken a fork
3       Pass    [✓]     4802 3 has taken a fork
4       Pass    [✓]     4802 1 is eating
5       Pass    [✓]     4803 3 has taken a fork
6       Pass    [✓]     4803 1 is eating
7       Pass    [✓]     4803 1 is eating
8       Pass    [✓]     4802 3 has taken a fork
9       Pass    [✓]     4802 1 is eating
10      Pass    [✓]     4802 1 is eating
        100 % correct
____________________________________________
        5 610 200 200 10
1       Pass    [✓]     4802 1 is eating
2       Pass    [✓]     4802 1 is eating
3       Pass    [✓]     4803 1 is eating
4       Pass    [✓]     4802 1 is eating
5       Pass    [✓]     4802 1 is eating
6       Pass    [✓]     4802 1 is eating
7       Pass    [✓]     4802 1 is eating
8       Pass    [✓]     4802 3 has taken a fork
9       Pass    [✓]     4802 3 has taken a fork
10      Pass    [✓]     4802 3 has taken a fork
        100 % correct
____________________________________________
        199 610 200 200 10
1       Pass    [✓]     4019 145 is eating
2       Pass    [✓]     4018 61 has taken a fork
3       Pass    [✓]     4018 15 has taken a fork
4       Pass    [✓]     4019 133 is eating
5       Pass    [✓]     4018 160 is sleeping
6       Pass    [✓]     4018 53 is eating
7       Pass    [✓]     4018 112 is sleeping
8       Pass    [✓]     4018 6 is sleeping
9       Pass    [✓]     4018 79 is eating
10      Pass    [✓]     4018 165 is eating
        100 % correct
____________________________________________
Testing uneven numbers (overkill) - they shouldn't die

        5 610 200 100 10
1       Pass    [✓]     4800 4 is eating
2       Pass    [✓]     4800 4 is eating
3       Pass    [✓]     4800 1 is eating
4       Pass    [✓]     4800 4 is eating
5       Pass    [✓]     4801 4 is eating
6       Pass    [✓]     4800 3 has taken a fork
7       Pass    [✓]     4800 4 is eating
8       Pass    [✓]     4800 1 is eating
9       Pass    [✓]     4801 4 is eating
10      Pass    [✓]     4800 4 is eating
        100 % correct
____________________________________________
        5 601 200 200 10
1       Pass    [✓]     4803 1 is eating
2       Pass    [✓]     4802 1 is eating
3       Pass    [✓]     4802 1 is eating
4       Pass    [✓]     4802 3 has taken a fork
5       Pass    [✓]     4802 1 is eating
6       Pass    [✓]     4802 1 is eating
7       Pass    [✓]     4802 1 is eating
8       Pass    [✓]     4802 1 is eating
9       Pass    [✓]     4803 1 is eating
10      Pass    [✓]     4802 1 has taken a fork
        100 % correct
____________________________________________
        31 610 200 100 10
1       Pass    [✓]     4001 26 is eating
2       Pass    [✓]     4000 3 is eating
3       Pass    [✓]     4000 18 is eating
4       Pass    [✓]     4001 13 has taken a fork
5       Pass    [✓]     4000 22 is eating
6       Pass    [✓]     4000 1 is eating
7       Pass    [✓]     4001 1 is eating
8       Pass    [✓]     4001 12 is sleeping
9       Pass    [✓]     4000 2 is sleeping
10      Pass    [✓]     4001 30 is eating
        100 % correct
____________________________________________
        31 610 200 200 10
1       Pass    [✓]     4018 9 is eating
2       Pass    [✓]     4018 1 is eating
3       Pass    [✓]     4018 3 is eating
4       Pass    [✓]     4018 2 is sleeping
5       Pass    [✓]     4018 5 is eating
6       Pass    [✓]     4018 7 is eating
7       Pass    [✓]     4018 3 is eating
8       Pass    [✓]     4018 3 is eating
9       Pass    [✓]     4018 1 is eating
10      Pass    [✓]     4018 7 is eating
        100 % correct
____________________________________________
        31 605 200 200 10
1       Pass    [✓]     4018 5 is eating
2       Pass    [✓]     4018 3 is eating
3       Pass    [✓]     4018 6 is sleeping
4       Pass    [✓]     4018 9 is eating
5       Pass    [✓]     4018 3 is eating
6       Pass    [✓]     4018 3 is eating
7       Pass    [✓]     4018 3 is eating
8       Pass    [✓]     4018 8 is sleeping
9       Pass    [✓]     4018 9 is eating
10      Pass    [✓]     4019 7 is eating
        100 % correct
____________________________________________
        31 601 200 200 10
1       Pass    [✓]     4018 7 is eating
2       Pass    [✓]     4018 11 is eating
3       Pass    [✓]     4018 5 is eating
4       Pass    [✓]     4019 11 has taken a fork
5       Pass    [✓]     4018 11 has taken a fork
6       Pass    [✓]     4018 6 is sleeping
7       Pass    [✓]     4018 9 is eating
8       Pass    [✓]     4018 3 is eating
9       Pass    [✓]     4018 3 is eating
10      Pass    [✓]     4018 3 has taken a fork
        100 % correct
____________________________________________
        131 610 200 100 10
1       Pass    [✓]     4001 67 is eating
2       Pass    [✓]     4000 71 is eating
3       Pass    [✓]     4001 39 is eating
4       Pass    [✓]     4000 73 is eating
5       Pass    [✓]     4000 120 is eating
6       Pass    [✓]     4000 71 is eating
7       Pass    [✓]     4000 13 is eating
8       Pass    [✓]     4001 101 is eating
9       Pass    [✓]     4001 40 is sleeping
10      Pass    [✓]     4001 95 is eating
        100 % correct
____________________________________________
        131 610 200 200 10
1       Pass    [✓]     4018 15 is eating
2       Pass    [✓]     4019 28 is sleeping
3       Pass    [✓]     4018 7 is eating
4       Pass    [✓]     4019 47 has taken a fork
5       Pass    [✓]     4018 63 is eating
6       Pass    [✓]     4018 57 is eating
7       Pass    [✓]     4019 37 has taken a fork
8       Pass    [✓]     4018 130 is eating
9       Pass    [✓]     4019 45 has taken a fork
10      Pass    [✓]     4018 86 is sleeping
        100 % correct
____________________________________________
        131 605 200 200 10
1       Pass    [✓]     4018 91 is eating
2       Pass    [✓]     4018 73 is eating
3       Pass    [✓]     4019 95 is eating
4       Pass    [✓]     4019 3 is eating
5       Pass    [✓]     4019 77 is eating
6       Pass    [✓]     4018 45 is eating
7       Pass    [✓]     4019 49 is eating
8       Pass    [✓]     4020 27 is eating
9       Pass    [✓]     4019 71 is eating
10      Pass    [✓]     4018 78 is sleeping
        100 % correct
____________________________________________
        131 601 200 200 10
1       Pass    [✓]     4019 29 is eating
2       Pass    [✓]     4018 61 has taken a fork
3       Pass    [✓]     4018 5 is eating
4       Pass    [✓]     4018 58 is sleeping
5       Pass    [✓]     4018 3 is eating
6       Pass    [✓]     4018 95 is eating
7       Pass    [✓]     4018 43 is eating
8       Pass    [✓]     4019 100 is sleeping
9       Pass    [✓]     4018 10 is sleeping
10      Pass    [✓]     4019 102 is sleeping
        100 % correct
____________________________________________
        199 610 200 100 10
1       Pass    [✓]     4001 91 is eating
2       Pass    [✓]     4003 77 is eating
3       Pass    [✓]     4001 129 has taken a fork
4       Pass    [✓]     4002 85 is eating
5       Pass    [✓]     4002 23 is eating
6       Pass    [✓]     4002 113 is eating
7       Pass    [✓]     4001 129 is eating
8       Pass    [✓]     4000 13 is eating
9       Pass    [✓]     4001 182 is eating
10      Pass    [✓]     4001 61 is eating
        100 % correct
____________________________________________
        199 610 200 200 10
1       Pass    [✓]     4021 165 is eating
2       Pass    [✓]     4019 79 is eating
3       Pass    [✓]     4018 133 is eating
4       Pass    [✓]     4018 137 is eating
5       Pass    [✓]     4019 125 is eating
6       Pass    [✓]     4019 93 has taken a fork
7       Pass    [✓]     4019 13 is eating
8       Pass    [✓]     4018 3 is eating
9       Pass    [✓]     4018 109 is eating
10      Pass    [✓]     4018 128 is sleeping
        100 % correct
____________________________________________
        199 605 200 200 10
1       Pass    [✓]     4018 153 is eating
2       Pass    [✓]     4019 105 has taken a fork
3       Pass    [✓]     4019 103 is eating
4       Pass    [✓]     4019 109 is eating
5       Pass    [✓]     4018 29 is eating
6       Pass    [✓]     4018 37 is eating
7       Pass    [✓]     4018 67 is eating
8       Pass    [✓]     4018 39 is eating
9       Pass    [✓]     4018 150 is sleeping
10      Pass    [✓]     4019 5 is eating
        100 % correct
____________________________________________
        199 601 200 200 10
1       Pass    [✓]     4018 70 is sleeping
2       Pass    [✓]     4019 152 is sleeping
3       Pass    [✓]     4018 45 is eating
4       Pass    [✓]     4018 133 is eating
5       Pass    [✓]     4018 119 is eating
6       Pass    [✓]     4018 53 is eating
7       Pass    [✓]     4019 75 is eating
8       Pass    [✓]     4018 49 is eating
9       Pass    [✓]     4018 143 is eating
10      Pass    [✓]     4018 21 is eating
        100 % correct
____________________________________________
Testing even numbers - they shouldn't die
        4 410 200 100 10
1       Pass    [✓]     3801 2 is eating
2       Pass    [✓]     3800 4 is eating
3       Pass    [✓]     3800 4 is eating
4       Pass    [✓]     3800 4 is eating
5       Pass    [✓]     3800 4 is eating
6       Pass    [✓]     3800 2 is eating
7       Pass    [✓]     3800 4 is eating
8       Pass    [✓]     3801 2 is eating
9       Pass    [✓]     3800 4 is eating
10      Pass    [✓]     3800 4 is eating
        100 % correct
____________________________________________
        4 410 200 200 10
1       Pass    [✓]     3818 2 is eating
2       Pass    [✓]     3818 4 is eating
3       Pass    [✓]     3818 4 is eating
4       Pass    [✓]     3819 4 is eating
5       Pass    [✓]     3819 4 is eating
6       Pass    [✓]     3818 4 is eating
7       Pass    [✓]     3818 4 is eating
8       Pass    [✓]     3819 4 is eating
9       Pass    [✓]     3819 4 is eating
10      Pass    [✓]     3818 4 is eating
        100 % correct
____________________________________________
        198 610 200 200 10
1       Pass    [✓]     3819 134 is eating
2       Pass    [✓]     3820 82 is eating
3       Pass    [✓]     3821 126 is eating
4       Pass    [✓]     3819 152 is eating
5       Pass    [✓]     3819 188 is eating
6       Pass    [✓]     3819 48 is eating
7       Pass    [✓]     3819 132 is eating
8       Pass    [✓]     3819 162 is eating
9       Pass    [✓]     3824 56 is eating
10      Pass    [✓]     3819 96 is eating
        100 % correct
____________________________________________
        198 800 200 200 10
1       Pass    [✓]     3825 72 is eating
2       Pass    [✓]     3819 34 is eating
3       Pass    [✓]     3819 52 is eating
4       Pass    [✓]     3819 70 is eating
5       Pass    [✓]     3819 86 is eating
6       Pass    [✓]     3820 64 is eating
7       Pass    [✓]     3820 178 is eating
8       Pass    [✓]     3819 112 is eating
9       Pass    [✓]     3819 196 is eating
10      Pass    [✓]     3818 114 is eating
        100 % correct
____________________________________________
Testing even numbers (overkill) - they shouldn't die
        50 410 200 100 10
1       Pass    [✓]     3801 14 is eating
2       Pass    [✓]     3801 12 is eating
3       Pass    [✓]     3800 28 is eating
4       Pass    [✓]     3801 2 is eating
5       Pass    [✓]     3801 42 is eating
6       Pass    [✓]     3801 50 is eating
7       Pass    [✓]     3801 34 is eating
8       Pass    [✓]     3801 26 is eating
9       Pass    [✓]     3801 10 is eating
10      Pass    [✓]     3800 4 is eating
        100 % correct
____________________________________________
        50 410 200 200 10
1       Pass    [✓]     3819 46 is eating
2       Pass    [✓]     3818 16 is eating
3       Pass    [✓]     3819 50 is eating
4       Pass    [✓]     3818 34 is eating
5       Pass    [✓]     3818 44 is eating
6       Pass    [✓]     3819 48 is eating
7       Pass    [✓]     3819 38 is eating
8       Pass    [✓]     3819 4 is eating
9       Pass    [✓]     3819 26 is eating
10      Pass    [✓]     3818 24 is eating
        100 % correct
____________________________________________
        50 405 200 200 10
1       Pass    [✓]     3818 28 is eating
2       Pass    [✓]     3819 46 is eating
3       Pass    [✓]     3818 12 is eating
4       Pass    [✓]     3818 50 is eating
5       Pass    [✓]     3819 12 is eating
6       Pass    [✓]     3819 2 is eating
7       Pass    [✓]     3819 24 is eating
8       Pass    [✓]     3818 2 is eating
9       Pass    [✓]     3818 42 is eating
10      Pass    [✓]     3818 42 is eating
        100 % correct
____________________________________________
        50 401 200 200 10
1       Fail    [x]     602 2 died
2       Fail    [x]     602 44 died
3       Fail    [x]     602 22 died
4       Fail    [x]     602 34 died
5       Fail    [x]     602 4 died
6       Fail    [x]     603 46 died
7       Fail    [x]     602 42 died
8       Fail    [x]     602 6 died
9       Fail    [x]     602 44 died
10      Fail    [x]     602 8 died
        0 % correct
____________________________________________
        130 410 200 100 10
1       Pass    [✓]     3801 120 is eating
2       Pass    [✓]     3801 68 is eating
3       Pass    [✓]     3800 118 is eating
4       Pass    [✓]     3801 60 is eating
5       Pass    [✓]     3800 46 is eating
6       Pass    [✓]     3801 46 is eating
7       Pass    [✓]     3801 8 is eating
8       Pass    [✓]     3801 48 is eating
9       Pass    [✓]     3801 94 is eating
10      Pass    [✓]     3801 70 is eating
        100 % correct
____________________________________________
        130 410 200 200 10
1       Pass    [✓]     3818 18 is eating
2       Pass    [✓]     3818 4 is eating
3       Pass    [✓]     3818 24 is eating
4       Pass    [✓]     3820 124 is eating
5       Pass    [✓]     3819 80 is eating
6       Pass    [✓]     3822 8 is eating
7       Pass    [✓]     3818 34 is eating
8       Pass    [✓]     3818 28 is eating
9       Pass    [✓]     3822 40 is eating
10      Pass    [✓]     3819 56 is eating
        100 % correct
____________________________________________
        130 405 200 200 10
1       Pass    [✓]     3819 18 is eating
2       Pass    [✓]     3819 130 is eating
3       Pass    [✓]     3818 104 is eating
4       Pass    [✓]     3819 42 is eating
5       Pass    [✓]     3822 110 is eating
6       Pass    [✓]     3818 128 is eating
7       Pass    [✓]     3820 126 is eating
8       Pass    [✓]     3821 102 is eating
9       Pass    [✓]     3819 84 is eating
10      Pass    [✓]     3818 96 is eating
        100 % correct
____________________________________________
        130 401 200 200 10
1       Fail    [x]     602 58 died
2       Fail    [x]     602 68 died
3       Fail    [x]     602 70 died
4       Fail    [x]     602 16 died
5       Fail    [x]     402 11 died
6       Fail    [x]     602 110 died
7       Fail    [x]     602 96 died
8       Fail    [x]     602 114 died
9       Fail    [x]     602 94 died
10      Fail    [x]     602 128 died
        0 % correct
____________________________________________
        198 410 200 100 10
1       Pass    [✓]     3802 46 is eating
2       Pass    [✓]     3802 157 is sleeping
3       Pass    [✓]     3803 80 is eating
4       Pass    [✓]     3802 166 is eating
5       Pass    [✓]     3801 6 is eating
6       Pass    [✓]     3800 22 is eating
7       Pass    [✓]     3801 46 is eating
8       Pass    [✓]     3802 76 is eating
9       Pass    [✓]     3802 174 is eating
10      Pass    [✓]     3801 147 is sleeping
        100 % correct
____________________________________________
        198 410 200 200 10
1       Pass    [✓]     3819 192 is eating
2       Pass    [✓]     3819 124 is eating
3       Pass    [✓]     3818 114 is eating
4       Pass    [✓]     3818 48 is eating
5       Pass    [✓]     3819 150 is eating
6       Pass    [✓]     3819 2 is eating
7       Pass    [✓]     3818 26 is eating
8       Pass    [✓]     3819 192 is eating
9       Pass    [✓]     3819 20 is eating
10      Pass    [✓]     3818 8 is eating
        100 % correct
____________________________________________
        198 405 200 200 10
1       Pass    [✓]     3821 192 is eating
2       Pass    [✓]     3819 84 is eating
3       Pass    [✓]     3819 190 is eating
4       Pass    [✓]     3820 112 is eating
5       Pass    [✓]     3819 28 is eating
6       Pass    [✓]     3819 106 is eating
7       Pass    [✓]     3818 18 is eating
8       Pass    [✓]     3818 10 is eating
9       Pass    [✓]     3819 148 is eating
10      Pass    [✓]     3820 166 is eating
        100 % correct
____________________________________________
        198 401 200 200 10
1       Fail    [x]     602 182 died
2       Fail    [x]     602 102 died
3       Fail    [x]     602 26 died
4       Fail    [x]     602 50 died
5       Fail    [x]     602 76 died
6       Fail    [x]     602 36 died
7       Fail    [x]     402 177 died
8       Fail    [x]     602 32 died
9       Fail    [x]     602 162 died
10      Fail    [x]     602 150 died
        0 % correct
____________________________________________
Testing uneven numbers - one should die
        4 310 200 100 10
1       Pass    [✓]     312 1 died
2       Pass    [✓]     311 1 died
3       Pass    [✓]     311 1 died
4       Pass    [✓]     312 1 died
5       Pass    [✓]     311 1 died
6       Pass    [✓]     312 1 died
7       Pass    [✓]     311 1 died
8       Pass    [✓]     311 1 died
9       Pass    [✓]     311 1 died
10      Pass    [✓]     311 3 died
        100 % correct
____________________________________________
        1 800 200 100 10
1       Pass    [✓]     800 1 died
2       Pass    [✓]     800 1 died
3       Pass    [✓]     800 1 died
4       Pass    [✓]     800 1 died
5       Pass    [✓]     800 1 died
6       Pass    [✓]     800 1 died
7       Pass    [✓]     800 1 died
8       Pass    [✓]     800 1 died
9       Pass    [✓]     800 1 died
10      Pass    [✓]     800 1 died
        100 % correct
____________________________________________
Testing uneven numbers - one should die
        3 596 200 200 10
1       Pass    [✓]     597 1 died
2       Pass    [✓]     597 3 died
3       Pass    [✓]     597 1 died
4       Pass    [✓]     597 1 died
5       Pass    [✓]     597 3 died
6       Pass    [✓]     597 1 died
7       Pass    [✓]     597 1 died
8       Pass    [✓]     597 3 died
9       Pass    [✓]     597 3 died
10      Pass    [✓]     597 1 died
        100 % correct
____________________________________________
        3 599 200 200 10
1       Pass    [✓]     600 3 died
2       Pass    [✓]     600 1 died
3       Pass    [✓]     600 3 died
4       Pass    [✓]     600 1 died
5       Pass    [✓]     600 3 died
6       Pass    [✓]     600 1 died
7       Pass    [✓]     600 3 died
8       Pass    [✓]     600 3 died
9       Pass    [✓]     600 3 died
10      Pass    [✓]     600 1 died
        100 % correct
____________________________________________
        3 600 200 200 10
1       Fail    [x]     5800 2 is eating
2       Fail    [x]     5800 1 is eating
3       Fail    [x]     5800 1 is eating
4       Fail    [x]     5800 3 has taken a fork
5       Fail    [x]     5800 1 has taken a fork
6       Fail    [x]     5800 2 is eating
7       Fail    [x]     5800 1 is eating
8       Fail    [x]     5800 2 is eating
9       Fail    [x]     5800 3 has taken a fork
10      Fail    [x]     5800 1 is eating
        0 % correct
____________________________________________
        31 596 200 200 10
1       Pass    [✓]     597 31 died
2       Pass    [✓]     597 31 died
3       Pass    [✓]     597 31 died
4       Pass    [✓]     597 31 died
5       Pass    [✓]     597 31 died
6       Pass    [✓]     597 31 died
7       Pass    [✓]     597 31 died
8       Pass    [✓]     597 31 died
9       Pass    [✓]     597 31 died
10      Pass    [✓]     598 31 died
        100 % correct
____________________________________________
        31 599 200 200 10
1       Pass    [✓]     600 31 died
2       Pass    [✓]     600 31 died
3       Pass    [✓]     600 31 died
4       Pass    [✓]     600 31 died
5       Pass    [✓]     600 31 died
6       Pass    [✓]     600 31 died
7       Pass    [✓]     600 31 died
8       Pass    [✓]     600 31 died
9       Pass    [✓]     600 31 died
10      Pass    [✓]     600 31 died
        100 % correct
____________________________________________
        31 600 200 200 10
1       Fail    [x]     4018 5 is eating
2       Pass    [✓]     601 31 died
3       Fail    [x]     4018 9 has taken a fork
4       Fail    [x]     4018 3 is eating
5       Fail    [x]     4018 9 is eating
6       Fail    [x]     4018 7 is eating
7       Fail    [x]     4018 2 is sleeping
8       Fail    [x]     4019 3 is eating
9       Pass    [✓]     601 31 died
10      Fail    [x]     4018 3 is eating
        20 % correct
____________________________________________
        131 596 200 200 10
1       Pass    [✓]     597 131 died
2       Pass    [✓]     597 131 died
3       Pass    [✓]     597 131 died
4       Pass    [✓]     597 131 died
5       Pass    [✓]     597 131 died
6       Pass    [✓]     597 131 died
7       Pass    [✓]     597 131 died
8       Pass    [✓]     597 131 died
9       Pass    [✓]     597 131 died
10      Pass    [✓]     597 131 died
        100 % correct
____________________________________________
        131 599 200 200 10
1       Pass    [✓]     600 131 died
2       Pass    [✓]     600 131 died
3       Pass    [✓]     600 131 died
4       Pass    [✓]     600 131 died
5       Pass    [✓]     600 131 died
6       Pass    [✓]     600 131 died
7       Pass    [✓]     600 131 died
8       Pass    [✓]     600 131 died
9       Pass    [✓]     600 131 died
10      Pass    [✓]     600 131 died
        100 % correct
____________________________________________
        131 600 200 200 10
1       Fail    [x]     4018 91 is eating
2       Fail    [x]     4018 9 is eating
3       Fail    [x]     4018 67 is eating
4       Fail    [x]     4019 43 is eating
5       Fail    [x]     4018 17 is eating
6       Fail    [x]     4018 102 is sleeping
7       Fail    [x]     4018 104 is sleeping
8       Fail    [x]     4018 9 is eating
9       Pass    [✓]     601 131 died
10      Fail    [x]     4019 105 is eating
        10 % correct
____________________________________________
        199 596 200 200 10
1       Pass    [✓]     597 199 died
2       Pass    [✓]     592 126 died
3       Pass    [✓]     597 199 died
4       Pass    [✓]     597 199 died
5       Pass    [✓]     597 199 died
6       Pass    [✓]     597 199 died
7       Pass    [✓]     597 199 died
8       Pass    [✓]     597 199 died
9       Pass    [✓]     597 199 died
10      Pass    [✓]     597 199 died
        100 % correct
____________________________________________
        199 599 200 200 10
1       Pass    [✓]     600 199 died
2       Pass    [✓]     600 199 died
3       Pass    [✓]     600 199 died
4       Pass    [✓]     600 199 died
5       Pass    [✓]     600 199 died
6       Pass    [✓]     600 199 died
7       Pass    [✓]     601 199 died
8       Pass    [✓]     600 199 died
9       Pass    [✓]     600 199 died
10      Pass    [✓]     600 199 died
        100 % correct
____________________________________________
        199 600 200 200 10
1       Fail    [x]     4018 173 is eating
2       Fail    [x]     4018 97 is eating
3       Pass    [✓]     601 199 died
4       Fail    [x]     4018 15 has taken a fork
5       Fail    [x]     4018 111 has taken a fork
6       Fail    [x]     4019 131 is eating
7       Fail    [x]     4018 54 is sleeping
8       Fail    [x]     4018 104 is sleeping
9       Fail    [x]     4019 137 is eating
10      Fail    [x]     4018 119 is eating
        10 % correct
____________________________________________
Testing even numbers - one should die
        3 599 200 200 10
1       Pass    [✓]     600 3 died
2       Pass    [✓]     600 3 died
3       Pass    [✓]     600 1 died
4       Pass    [✓]     600 3 died
5       Pass    [✓]     600 3 died
6       Pass    [✓]     600 3 died
7       Pass    [✓]     600 1 died
8       Pass    [✓]     600 3 died
9       Pass    [✓]     600 3 died
10      Pass    [✓]     600 1 died
        100 % correct
____________________________________________
        31 599 200 200 10
1       Pass    [✓]     600 31 died
2       Pass    [✓]     600 31 died
3       Pass    [✓]     600 31 died
4       Pass    [✓]     600 31 died
5       Pass    [✓]     600 31 died
6       Pass    [✓]     600 31 died
7       Pass    [✓]     600 31 died
8       Pass    [✓]     600 31 died
9       Pass    [✓]     600 31 died
10      Pass    [✓]     600 31 died
        100 % correct
____________________________________________
        131 596 200 200 10
1       Pass    [✓]     597 131 died
2       Pass    [✓]     597 131 died
3       Pass    [✓]     597 131 died
4       Pass    [✓]     597 129 died
5       Pass    [✓]     597 129 died
6       Pass    [✓]     597 131 died
7       Pass    [✓]     597 131 died
8       Pass    [✓]     598 131 died
9       Pass    [✓]     598 131 died
10      Pass    [✓]     597 131 died
        100 % correct
____________________________________________
Testing even numbers - one should die
        4 310 200 100 10
1       Pass    [✓]     312 1 died
2       Pass    [✓]     311 1 died
3       Pass    [✓]     311 1 died
4       Pass    [✓]     311 1 died
5       Pass    [✓]     311 1 died
6       Pass    [✓]     312 1 died
7       Pass    [✓]     311 1 died
8       Pass    [✓]     311 1 died
9       Pass    [✓]     311 1 died
10      Pass    [✓]     311 3 died
        100 % correct
____________________________________________
        50 396 200 200 10
1       Pass    [✓]     398 1 died
2       Pass    [✓]     397 1 died
3       Pass    [✓]     397 1 died
4       Pass    [✓]     397 1 died
5       Pass    [✓]     397 1 died
6       Pass    [✓]     397 1 died
7       Pass    [✓]     397 3 died
8       Pass    [✓]     397 1 died
9       Pass    [✓]     397 1 died
10      Pass    [✓]     397 1 died
        100 % correct
____________________________________________
        50 399 200 200 10
1       Pass    [✓]     400 1 died
2       Pass    [✓]     400 33 died
3       Pass    [✓]     400 3 died
4       Pass    [✓]     400 1 died
5       Pass    [✓]     400 29 died
6       Pass    [✓]     400 37 died
7       Pass    [✓]     400 31 died
8       Pass    [✓]     400 15 died
9       Pass    [✓]     400 25 died
10      Pass    [✓]     400 15 died
        100 % correct
____________________________________________
        50 400 200 200 10
1       Pass    [✓]     601 2 died
2       Pass    [✓]     401 5 died
3       Pass    [✓]     601 2 died
4       Pass    [✓]     601 2 died
5       Pass    [✓]     401 1 died
6       Pass    [✓]     601 2 died
7       Pass    [✓]     601 2 died
8       Pass    [✓]     601 2 died
9       Pass    [✓]     601 2 died
10      Pass    [✓]     601 2 died
        100 % correct
____________________________________________
        130 396 200 200 10
1       Pass    [✓]     397 1 died
2       Pass    [✓]     397 1 died
3       Pass    [✓]     397 21 died
4       Pass    [✓]     397 1 died
5       Pass    [✓]     397 1 died
6       Pass    [✓]     397 1 died
7       Pass    [✓]     397 1 died
8       Pass    [✓]     397 19 died
9       Pass    [✓]     398 1 died
10      Pass    [✓]     397 1 died
        100 % correct
____________________________________________
        130 399 200 200 10
1       Pass    [✓]     400 41 died
2       Pass    [✓]     400 77 died
3       Pass    [✓]     400 5 died
4       Pass    [✓]     400 113 died
5       Pass    [✓]     400 99 died
6       Pass    [✓]     400 25 died
7       Pass    [✓]     400 49 died
8       Pass    [✓]     400 123 died
9       Pass    [✓]     400 15 died
10      Pass    [✓]     400 9 died
        100 % correct
____________________________________________
        130 400 200 200 10
1       Pass    [✓]     401 103 died
2       Pass    [✓]     401 3 died
3       Pass    [✓]     601 2 died
4       Pass    [✓]     601 2 died
5       Pass    [✓]     401 63 died
6       Pass    [✓]     401 97 died
7       Pass    [✓]     401 1 died
8       Pass    [✓]     601 2 died
9       Pass    [✓]     601 2 died
10      Pass    [✓]     601 2 died
        100 % correct
____________________________________________
        198 396 200 200 10
1       Pass    [✓]     397 3 died
2       Pass    [✓]     398 1 died
3       Pass    [✓]     397 1 died
4       Pass    [✓]     394 28 died
5       Pass    [✓]     398 1 died
6       Pass    [✓]     397 1 died
7       Pass    [✓]     397 1 died
8       Pass    [✓]     397 1 died
9       Pass    [✓]     397 1 died
10      Pass    [✓]     397 1 died
        100 % correct
____________________________________________
        198 399 200 200 10
1       Pass    [✓]     400 145 died
2       Pass    [✓]     400 135 died
3       Pass    [✓]     400 171 died
4       Pass    [✓]     400 99 died
5       Pass    [✓]     400 47 died
6       Pass    [✓]     400 83 died
7       Pass    [✓]     400 41 died
8       Pass    [✓]     400 23 died
9       Pass    [✓]     400 15 died
10      Pass    [✓]     400 141 died
        100 % correct
____________________________________________
        198 400 200 200 10
1       Pass    [✓]     401 29 died
2       Pass    [✓]     401 81 died
3       Pass    [✓]     601 2 died
4       Pass    [✓]     602 2 died
5       Pass    [✓]     601 2 died
6       Pass    [✓]     401 187 died
7       Pass    [✓]     602 2 died
8       Pass    [✓]     401 17 died
9       Pass    [✓]     401 29 died
10      Pass    [✓]     601 2 died
        100 % correct
____________________________________________

RESULT: passed: 534     failed: 66
        89 % correct