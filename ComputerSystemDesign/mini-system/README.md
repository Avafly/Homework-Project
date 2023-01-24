# 📕 Mini ARM operating system

## Goal of this work

Writing a mini system using ARM language on Xilinx Zynq-7000 device. 3 tasks (written in C) will be provided, and they have to run on the system continuously in a round-robin fashion. Each application runs forever (i.e., never exits).

The following is a brief description of 3 tasks.

* Tasks1: Selection-sorting. Its outcome is displayed on LEDs.
* Tasks2: DhryStone Benchmark. It is used to measure the CPU performance. The benchmark is composed of several functions. Each function name is printed via UART after execution. After the execution of the whole benchmark, a message **'Task2 finished'** will be printed on UART console.
* Tasks3: Simply send ‘Hello World’ to UART console.

### The assignment requirements are as follows.

* System Initializations (in **Supervisor mode**)
  * Stack setup for each mode
  * GIC configuration
  * Private Timer configuration
  * UART configuration
  * TCB (Task-Control Block) setup for each user program (See  [[here](https://github.com/Avafly/Homework-Project/tree/master/ComputerSystemDesign/mini-system/TCB.pdf)])
  * Stack setup for each user program
* Task Scheduling (in **IRQ mode**)
  * Set the timer interval to 1ms for task scheduling
    * Some people refer to it (periodic timer interrupt) as **tick**
  * Context switch in ISR upon private timer interrupt
  * Task priorities are the same for 3 tasks
  * Use the round-robin mechanism for the task scheduling (task1 → task2 → task3→ task1→ task2 ...)

The application programs run in **User mode**.



## What did I do

[[Demo](https://trustylin.com/s/wXF9)] (Click <u>Preview</u> to watch it online)

The procedure has two parts: 1. starting tasks, 2. All tasks have been started.

When there are still tasks that have not been started, system will start them in sequence. The `openTask` parameter is used to count the started tasks and record the program counter (PC) of the next task to be opened for the next branching. Note that interrupt occurs 1 ms once, thus the data in the registers are saved to the stack in `csd_IRQ_ISR` part to avoid data loss.

Once all tasks are started, the system switches between each program by interrupt, and the process is to save the current task's data from the register to the stack and load the next task's data from the stack into the register.

As the result, Tera Term displays the results of tasks 2 and 3, and the outcome of task 1 is displayed on LED lights.

You can find the description [[here](https://trustylin.com/s/42id)] (in Korean language).
