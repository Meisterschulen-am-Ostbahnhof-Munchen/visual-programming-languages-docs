# GET_LREAL

![GET_LREAL](./GET_LREAL.svg)

* * * * * * * * * *

## Introduction

The function block `GET_LREAL` provides read access to a `LREAL` variable (64-bit floating-point number) which is passed as an InOut parameter. The read value is buffered internally and made available at the output `OUT`. Execution is triggered by an event.

## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Normal Execution Trigger; Reads the value of `IN` |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Confirmation of execution; sent after reading |

### **Data Inputs**

This function block does not have its own data inputs. The source data is provided via the InOut parameter `IN`.

### **Data Outputs**

| Output | Data Type | Initial Value | Comment |
|---------|-----------|--------------|----------------------------|
| OUT | LREAL | 0.0 | Buffered Output Value |

### **Adapter**

No adapters available.

## Functionality

1. An event at input `REQ` triggers processing.
2. The function block executes the ST instruction `OUT := IN;`. The current value of the InOut variable `IN` is read and temporarily stored in the local output variable `OUT`.
3. After successful reading, the event `CNF` is output. The value of `OUT` is retained until the next execution.

## Technical Features

- The source `IN` is declared as an **InOut variable**. It must be linked to an actual variable (e.g., a global or hardware resource) by the calling environment.
- The function block buffers the read value: as long as no new `REQ` pulse is received, `OUT` returns the last read state.
- Both parameters (`IN` and `OUT`) are initialized with the value `0.0`.

## State Overview

Since this is a simple function block (SimpleFB), there is only one ECC state:

| State | Action | Output Event |
|---------|--------|-----------------|
| REQ | `OUT := IN;` | CNF |

## Application Scenarios

- **Buffered reading of a high-frequency process variable** (e.g., temperature or pressure) to keep the value constant during the control cycle.
- **Accessing a shared memory variable** in a multitasking environment where decoupled read speed is desired.
- **Preparing data for downstream calculations** that rely on a stable, buffered floating-point value.

## Comparison with Similar Components

Components such as `GET_REAL` or `GET_INT` operate on the same principle, but with shorter data types. `GET_LREAL` is specifically designed for applications requiring high numerical accuracy (64-bit). Unlike pure read blocks without buffering (e.g., direct variable linking), the buffered output guarantees deterministic delivery that is independent of the time of the read.

## Conclusion

GET_LREAL` is a simple, reliable block for buffered reading of a `LREAL` source. It is particularly suitable for decoupling read and processing logic and ensures that the provided value remains constant throughout a complete execution cycle.
