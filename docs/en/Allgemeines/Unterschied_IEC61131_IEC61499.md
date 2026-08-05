# ⚖️ Difference between IEC 61131-3 and IEC 61499

The standards **IEC 61131-3** and **IEC 61499** both define standards for programming industrial control systems, but they follow different approaches regarding architecture and implementation.

## 1. Architectural Model

### IEC 61131-3: Centralized Control
IEC 61131-3 was primarily developed for **programmable logic controllers (PLCs)**. The model assumes a central processing unit that executes a program.

* **Structure:** Configuration -> Resource -> Task -> Program -> Function blocks/functions.

* **Focus:** A single device controls a process.

### IEC 61499: Distributed Systems
IEC 61499 extends the concepts of IEC 61131-3 for **distributed systems**. An application can be distributed across multiple devices and resources without requiring reprogramming of its functionality.

* **Structure:** System -> Device -> Resource -> Application -> Function Blocks.

* **Focus:** Functional units (software blocks) communicate via events and data, regardless of the hardware on which they run.

## 2. Execution Model

Perhaps the most important difference lies in how code is executed.

### IEC 61131-3: Cyclic (Scan-based)
In the classic PLC world, execution usually follows a rigid cycle:

1. **Read inputs:** All physical inputs are read into the process image.

2. **Execute program:** The code is processed from top to bottom (or according to task priority).

3. **Write outputs:** The calculated values are written to the physical outputs.

This cycle repeats continuously (e.g., every 10 ms). A function block is called in every cycle, regardless of whether its input data has changed.

### IEC 61499: Event-driven
Execution in IEC 61499 is based on **events**.

* A function block does **nothing** as long as no event arrives at one of its event inputs.

* When an event arrives (e.g., `REQ` for Request), the block is "woken up."

* The **Execution Control (ECC)** then decides which algorithms are executed and which output events (e.g., `CNF` for Confirmation) are fired.

* There is no global cycle; the execution chain is determined by the flow of events.

## 3. Function Blocks in Comparison

| Feature | IEC 61131-3 FB | IEC 61499 FB |

| :--- | :--- | :--- |

| **Interface** | Data only (VAR_INPUT, VAR_OUTPUT) | Events and data |

| **Execution** | Triggered by the call in the program (cycle) | Triggered by incoming events |

| **Internal Logic** | Code body (in ST, LAD, FBD, etc.) | Explicit state machine (**ECC**) or interconnected network |

| **Data Synchronization** | Implicit (on call) | Explicit via **WITH qualifier** (connects data with events) |

## Summary

* Use **IEC 61131-3** when programming a single PLC and requiring cyclic, deterministic execution.

Use **IEC 61499** when designing distributed systems, requiring component-based software encapsulation, or mapping event-driven processes.


Use IEC 61499 when designing distributed systems, implementing component-based software encapsulation, or mapping event-driven processes.