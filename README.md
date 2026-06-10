*This project has been created as part of the 42 curriculum by fda-cruz*

## Description

Codexion is a concurrency simulation where multiple coders compete for a limited number of USB dongles to compile their code.

Each coder runs as an independent thread and cycles through four phases: requesting dongles, compiling, debugging, and refactoring.
Compiling requires holding two adjacent dongles simultaneously.
The simulation ends either when all coders complete the required number of compilations, or when a coder burns out due to waiting too long without compiling.

The program implements two scheduling policies to determine which coder receives the dongles when multiple coders request them at the same time:
- **FIFO** - First In First Out
- **EDF** - Earliest Deadline First

## Requirements

Make sure `make` is installed on your system:

```bash
sudo apt install make
```

## Instructions

### Compilation

To compile the program, simply write "make" in the terminal. The **codexion** program will be available for usage.

```bash
make
```

### Execution

To run the program, eight parameters need to be passed:
1. *number_of_coders*: Number of coders and dongles
2. *time_to_burnout*: Max milliseconds a coder can go without starting to compile
3. *time_to_compile*: Time in milliseconds a coder spends compiling
4. *time_to_debug*: Time in milliseconds a coder spends debugging
5. *time_to_refactor*: Time in milliseconds a coder spends refactoring
6. *number_of_compiles_required*: Compilations each coder must complete
7. *dongle_cooldown*: Milliseconds a dongle is unavailable after being released
8. *scheduler*: scheduling policy `fifo` or `edf`

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

**Example:**

```bash
./codexion 3 800 200 100 100 5 60 edf
```

## Technical Overview

### Simulation Flow

The simulation starts by creating all coder threads and the monitor thread.

To guarantee a synchronized start, every thread enters a startup barrier and waits until all threads are ready. Once the barrier is released, a global simulation timestamp is recorded and all threads begin simultaneously.

Each coder then enters the following cycle:

1. Request dongles
2. Wait until both required dongles are assigned
3. Compile
4. Debug
5. Refactor

The monitor thread runs independently and continuously:

1. Checks burnout conditions
2. Checks completion conditions
3. Processes dongle requests
4. Updates dongle cooldowns
5. Assigns available dongles according to the selected scheduler

The monitor is responsible for tracking dongle ownership and releasing them once a coder leaves the compilation phase.

### Startup Barrier

A startup barrier ensures that no thread begins the simulation before all threads have been successfully created.

Each thread increments a shared `ready_count` value and waits on a condition variable.

The main thread waits until all threads are ready.
At that point, the simulation timestamp is stored and a broadcast wakes every waiting thread simultaneously.

### Scheduler

When a coder finishes refactoring, it requests its two adjacent dongles.
The monitor collects pending requests and inserts them into a scheduler queue.

As previously stated, the scheduler determines which waiting coder should receive the dongles according to the `fifo` or `edf` policy.

`fifo` Requests are processed in arrival order.

`edf` Requests are ordered by burnout deadline:

```text
deadline = last_compile_start + time_to_burnout
```

Coders with the earliest deadline receive priority.

### Dongle Lifecycle

Each dongle tracks its availability, occupancy state and cooldown timer.
When assigned to a coder, the dongle becomes occupied and cannot be assigned again.

Once the monitor detects that a coder has left the compilation phase, it releases the corresponding dongles.

The dongle remains unavailable until its cooldown period expires. The monitor periodically updates all dongles and marks them as ready once the cooldown completes.

### Burnout Detection

Every coder stores the timestamp of its last compilation start.

The monitor periodically compares the current simulation time against that timestamp. If the elapsed time exceeds `time_to_burnout`, the coder burns out and the simulation stops immediately.

This check is performed continuously throughout the simulation, ensuring accurate burnout detection regardless of the coder's current activity.

### Completion Detection

Each coder tracks the number of completed compilations.

The monitor periodically checks whether every coder has reached `number_of_compiles_required`.
Once all coders satisfy this condition, the simulation terminates successfully.

### Blocking Cases Handled

The simulation was designed with concurrency safety as a core requirement, addressing several classical issues that arise in multithreaded coordination of shared resources.

`Deadlock` is prevented by ensuring that a coder never holds a partial allocation of resources. Dongles are assigned atomically by the monitor: a coder only receives permission to proceed when both required dongles are available at the same time.
This removes any possibility of circular waiting between threads and avoids violating Coffman’s necessary conditions for deadlock.

`Starvation` is handled through the `edf` scheduling strategy.
The monitor always prioritizes coders closest to their burnout threshold, ensuring that threads with more urgent deadlines are served first.
In practical terms, this guarantees fairness as long as the system remains in a feasible state where all deadlines can be satisfied.

`Dongle cooldown` introduces an additional constraint to resource availability.

After a dongle is released, it enters a temporary unavailable state for a fixed cooldown period. The monitor tracks the last release timestamp per dongle and only marks it as ready after the cooldown expires.

`Burnout detection` dedicated monitor thread continuously checks each coder's `last_compile_time`.
If `get_current_time() - last_compile_time >= time_to_burnout`, the burnout is logged and the simulation stops.

Detection occurs within 10ms of the actual burnout time.

`Log serialization` is enforced through a dedicated `mutex_print` mutex protecting all output operations.
This guarantees that log messages generated by concurrent threads are written atomically, preventing mixed logs and preserving the readability and ordering of events even under high contention.

### Thread Synchronization Mechanisms

The system relies on a combination of mutexes and a condition variable to coordinate coders and the central monitor while maintaining strict separation of concerns between shared state and thread-local state.

Each coder owns a dedicated mutex that protects its internal state.
`t_coder's pthread_mutex_t mutex` protects coder state fields written by the coder thread: `current_operation`, `number_of_compiles_done`, `last_compile_time`, `request_time`.

The monitor acquires this mutex when reading these fields.
This ensures that the monitor can safely inspect or evaluate a coder’s status without risking race conditions while the coder is simultaneously updating its own state.

On the control side, `t_control` is shared by all threads and acts as the central coordination structure of the simulation.

The monitor is the only thread that writes the global control state, including `is_running`, and it also updates the per-coder dongle flags `has_left_dongle` and `has_right_dongle` under the same mutex. Coders only read this state to decide whether they can continue waiting or must exit.

`t_control's pthread_mutex_t mutex` protects these shared values and is also used together with `t_control's pthread_cond_t condition`, because coders must wait and wake under the same lock that guards the condition predicate.
This guarantees that dongle assignments and shutdown signals are observed consistently by every coder thread.

As previously mentioned, a single condition variable, `t_control's pthread_cond_t condition`, is used to suspend coders while they wait for resource allocation. Coders block inside their request routine, `coder_request`, until either dongles are assigned by the monitor or `is_running` becomes 0.

The monitor uses `pthread_cond_broadcast` to wake all waiting coder threads after each scheduling decision or during shutdown, ensuring no thread remains stuck waiting indefinitely.

`t_control's pthread_mutex_t mutex_print` is used to serialize all logging operations.
It protects `print_message`, ensuring log serialization.

As a result, race conditions are prevented by clearly separating ownership of data: coder-specific fields are always accessed under the `t_coder’s pthread_mutex_t mutex`, while shared scheduling state is accessed under the `t_control's pthread_mutex_t mutex`.

This separation avoids overlapping lock domains and reduces contention while preserving consistency across threads and ensuring a race-free synchronization model.

Shutdown is handled in a thread-safe and deterministic manner. When the monitor detects burnout or the program completion requirements are met, it sets `is_running = 0` under `t_control's pthread_mutex_t mutex` and broadcasts the condition variable.

All coder threads wake up, check `is_running`, and exit cleanly.

### Output Message Format

Each state change is outputted as:

`timestamp in milliseconds` `coder_id` `action`

Where action is one of: `has taken a dongle`, `is compiling`, `is debugging`, `is refactoring`, `burned out`.

**Example:**
```
0 1 has taken a dongle
```

### Project Structure

```text
.
├── include
│   └── codexion.h
├── Makefile
├── README.md
└── src
    ├── codexion.c
    ├── heap
    │   └── heap.c
    ├── parser
    │   ├── parser.c
    │   └── parser_utils.c
    ├── simulation
    │   ├── simulation.c
    │   ├── simulation_frees.c
    │   ├── simulation_threads.c
    │   ├── simulation_utils2.c
    │   └── simulation_utils.c
    └── threads
        ├── coder.c
        ├── coder_utils.c
        ├── monitor.c
        ├── monitor_utils2.c
        └── monitor_utils.c
```

## Resources

### Concurrency and POSIX Threads

- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/) — Comprehensive guide to pthreads
- [Complementary Explanation on Threads](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) - Video series explaining core threading and synchronization concepts
- [Starting Threads](https://man7.org/linux/man-pages/man3/pthread_create.3.html) - Manual page for pthread_create
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — The classic resource-sharing problem this project is based on

### Scheduling

- [Earliest Deadline First Scheduling](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling) — EDF scheduling algorithm
- [FIFO Scheduling](https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)) — First In First Out scheduling algorithm

### Synchronization Mechanisms

- [Mutex](https://www.ibm.com/docs/en/zos/3.2.0?topic=functions-pthread-mutex-init-initialize-mutex-object)

- [Condition Variables](https://www.ibm.com/docs/en/zos/3.2.0?topic=functions-pthread-cond-init-initialize-condition-variable)

### Use of AI

ChatGPT was used initially to clarify doubts and, later on, to help organize the README.

Claude was introduced midway to assist with the organization as well.

The overall flow and structure of the project were already planned by the student, but AI was used to double-check that nothing important was being left out, such as mutexes and condition variables.