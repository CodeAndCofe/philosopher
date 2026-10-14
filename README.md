# Philosophers 🍝

I built this project in 2025 at **1337 / 42**. It was my first serious concurrency project, and it taught me how small timing differences can break a program.

## The problem in one minute

The Dining Philosophers problem models resource sharing:

- Philosophers sit in a circle.
- One fork is between each pair.
- To eat, a philosopher must hold both left and right forks.
- Philosophers cycle through thinking, eating, and sleeping.

![Dining Philosophers diagram](assets/dining-philosophers.svg)

The challenge is not printing states — it is coordinating shared resources safely.

## Why this is hard

| Risk | What it means here |
|---|---|
| **Deadlock** | Everyone holds one fork and waits forever for the second fork. |
| **Data race** | Shared values (last meal time, stop flag, counters) are read/written without safe synchronization. |
| **Starvation** | One philosopher keeps missing chances to eat while others continue. |

A correct solution needs to handle all three.

## Project model: circular linked list

In this project, philosophers are represented as a **circular linked list**:

- each node = one philosopher
- each node points to the next philosopher
- the last node points back to the first

This matches the round table naturally and makes neighbor relations explicit. The data structure helps model the table, but synchronization logic is still required to avoid deadlock/races.

## Processes vs threads (quick view)

| Process | Thread |
|---|---|
| Separate address space | Shares process memory with sibling threads |
| Uses IPC to share data | Shares variables directly (needs mutexes/locks) |
| Stronger isolation | Easier sharing, higher race risk |

In the usual `philo` version, philosophers run as **threads** and forks are protected with mutexes.

## Program arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks). |
| `time_to_die` | Max time without eating before death is reported. |
| `time_to_eat` | Eating duration while holding two forks. |
| `time_to_sleep` | Sleeping duration after eating. |
| optional meal count | Stop when each philosopher has eaten enough times. |

## What I learned

- Correct concurrent code is about **coordination**, not just syntax.
- Preventing deadlock alone is not enough; race safety and fairness matter too.
- Modeling the table clearly (circular list) made the concurrency rules easier to reason about.

## Image credit

- Wikimedia Commons source page for the diagram used here:  
  https://commons.wikimedia.org/wiki/File:Dining_philosophers.svg

## References

- GeeksforGeeks style/reference article:  
  https://www.geeksforgeeks.org/operating-systems/dining-philosophers-problem/
- Wikimedia Commons image page:  
  https://commons.wikimedia.org/wiki/File:Dining_philosophers.svg
- Optional illustrated variant (CC BY-SA, Wikimedia Commons):  
  https://commons.wikimedia.org/wiki/File:An_illustration_of_the_dining_philosophers_problem.png
