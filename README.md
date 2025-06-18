# 🧠 42_Philosophers

> A multithreaded simulation of the classic Dining Philosophers problem, implemented in C using POSIX threads.

## 📚 Project Overview

This project is part of the 42 Beirut curriculum. It simulates a scenario in which philosophers alternately think, eat, and sleep while avoiding deadlocks and starvation.

All logic is implemented inside the `philo/` directory.

## 🗂 Project Structure

```
42_Philosophers/
├── philo/
│   ├── Makefile
│   ├── philo.c
│   ├── init.c
│   ├── monitor.c
│   ├── routine.c
│   ├── threads.c
│   ├── utils.c
│   ├── single_philo.c
│   ├── utils.h
│   └── philo.h
└── README.md
```


## ⚙️ Installation

```bash
# Clone the repo
git clone https://github.com/MarioMakhlouta/42_Philosophers.git

# Go into the project folder
cd 42_Philosophers/philo

# Compile the project
make
````

To clean compiled files:

```bash
make clean     # Removes object files
make fclean    # Removes object files and the binary
make re        # Recompiles from scratch
```

---

## 🚀 How to Run

The compiled program expects **the following arguments**:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```

* `number_of_philosophers` (int > 0)
* `time_to_die` (in ms)
* `time_to_eat` (in ms)
* `time_to_sleep` (in ms)
* `number_of_times_each_philosopher_must_eat` (optional, int > 0)

### 🧪 Example

```bash
./philo 5 800 200 200
```

* 5 philosophers
* Each dies if they don't eat within 800ms
* Eating takes 200ms
* Sleeping takes 200ms

---

## 🧪 Tester

A tester is available to validate your project output and behavior under various conditions:

### 🔗 GitHub Repo:

[42\_Philosophers\_tester](https://github.com/MarioMakhlouta/42_Philosophers_tester)

### 📥 Clone & Run

```bash
git clone https://github.com/MarioMakhlouta/42_Philosophers_tester.git
cd 42_Philosophers_tester
./test.sh
```

---

## 👨‍💻 Author

* **Mario Makhlouta - mmakhlou**
* GitHub: [MarioMakhlouta](https://github.com/MarioMakhlouta)

