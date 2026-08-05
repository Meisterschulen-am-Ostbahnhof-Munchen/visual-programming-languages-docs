# 🧩 Function Blocks in IEC 61499
The IEC 61499 standard defines a model for distributed industrial control systems. The central component of this model is the function block (FB). Unlike IEC 61131-3, an FB in IEC 61499 encapsulates not only data and algorithms, but also the **control of its execution**.
## Structure of a Function Block
A function block always consists of two parts:

1. **Interface:** The "shell" of the block.
2. **Body:** The interior of the block (the implementation).

### Interface

The interface is divided into two areas:

* **Head:** This contains the **event inputs** and **event outputs**.
* **Body Interface:** This is where the **Data Inputs** and **Data Outputs** are located.

**Important:** Data is always synchronized with events. The connection between an event and its associated data is defined by the **WITH Qualifier**. This means: "When event X occurs, data A and B are valid/updated."

---

## Types of Function Blocks

There are three main types of function blocks in IEC 61499:

### 1. Basic Function Block

This is the elementary block in which **algorithms** (code in ST, C, etc.) are executed.

* A **state machine**, the so-called **ECC** (see below), controls *when* which algorithm is executed.
* It has no internal parallel execution; it is always in exactly one state.

### 2. Composite Function Block

This block does not contain any algorithms or ECCs. Instead, its core consists of a **network** of other function blocks (basic or composite FBs) that are interconnected. It serves to structure and encapsulate complex logic.

### 3. Service Interface Function Block (SIFB)

This block provides the interface to the hardware or the operating system.

* Examples: Reading/writing digital I/Os, network communication (UDP/TCP), accessing system time.
* The internal implementation is usually not visible in IEC 61499 (black box).

---

## ⚙️ ECC (Execution Control Chart)

The **ECC (Execution Control Chart)**, or execution control plan, is the core of every **basic function block**. It is a state machine that controls how the component reacts to incoming events.

The ECC consists of three elements:

### 1. EC States

A state represents a situation in which the component is located (e.g., `START`, `INIT`, `RUN`, `ERROR`).

* The component is always active in exactly one state.
* Each state can have one or more **EC actions** assigned to it.

### 2. EC Transitions

Transitions are the connections between states. They define when the component changes from one state to the next.

A transition triggers (fires) when:

* The associated **event** (e.g., `REQ`) occurs.
* AND** an optional **guard condition** is true (e.g., `x > 10`).

*Example:* `REQ [x > 10]` -> Only change the state if event `REQ` occurs AND `x` is greater than 10.

### 3. EC Actions
Actions are executed as soon as a state becomes active. An action consists of two parts (both optional):

1. **Algorithm:** A piece of program code (e.g., in structured text) that performs calculations.

2. **Output Event:** An event (event output) that is sent externally after the algorithm has finished executing (e.g., `CNF`).

### Process in the ECC

1. The function block is in a state (e.g., `START`) and waits.

2. An event arrives at the input.

3. The ECC checks all transitions originating from the current state.

4. If a transition is valid (event matches + condition is true), the ECC changes to the new state.

5. In the new state, all assigned **algorithms** are executed sequentially.

6. Afterward, the assigned **output events** are triggered.

7. The ECC waits in the new state for the next event.

---

> 💡 **Tip:** Can't remember the standard number **61499**?

> Then the **[mnemonic: IEC 61499](Eselsbruecke_IEC61499.md)** will help.
