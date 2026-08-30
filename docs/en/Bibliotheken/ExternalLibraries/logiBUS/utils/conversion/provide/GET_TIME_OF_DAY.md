# GET_TIME_OF_DAY

![GET_TIME_OF_DAY](./GET_TIME_OF_DAY.svg)

* * * * * * * * * *

## Introduction

The function block `GET_TIME_OF_DAY` is used to read a time of day value (type `TIME_OF_DAY`) from an InOut variable. The read value is buffered internally and made available via a data output. In this way, a consistent, uniquely read time of day is passed on – even if the source variable changes in the meantime.

## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Execution Request; reads the current value of IN |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Confirmation after successful read and buffering |

### **Data Inputs**

There are no pure inputs. The source data is provided via the InOut input `IN`.

### **Data Outputs**

| Output | Data Type | Comment |
|---------|------------|-------------------------------|
| OUT | TIME_OF_DAY| Buffered time of day value |

### **Adapters**

No adapters are available.

## Functionality

A call to the event `REQ` triggers the internal associated action: The current value of the InOut variable `IN` is read and copied to the output variable `OUT`. The event `CNF` is then sent. The time of day is then consistently available at the output `OUT` until the next `REQ` – regardless of any interim changes to `IN`.

## Technical Features

- **InOut variable as source:** The function block uses an InOut parameter that is directly linked to an external variable in the IEC 61499 model. This allows the function block to read the value "from the outside" without having to define a data input itself.
- **Buffering:** The read value is temporarily stored in the output variable `OUT`, so that subsequent queries always return the same value until `REQ` is triggered again.
- **Simple State Machine:** The function block consists of only one state, which executes the action and immediately outputs the confirmation event.

## State Overview

The simple function block has only the state `REQ`. As soon as the event `REQ` is received, the action `REQ` is executed (OUT := IN) and the event `CNF` is sent. There are no further states or branches.

## Application Scenarios

- **Timestamping in Controllers:** A one-time capture of a time value from a higher-level clock, for example, to document operating hours or switching times.
- **Buffering for Asynchronous Evaluation:** An external timer (e.g., a system clock) changes continuously; the function block freezes its value at the time of the call and makes it available to a slower consumer or logic.
- **Communication Across Boundaries:** In distributed systems, the current time of day can be retrieved from a component and cached locally for consistent output later.

## Comparison with Similar Function Blocks

- **Unlike a pure data connector** (e.g., MOVE or simple data copy), `GET_TIME_OF_DAY` uses an InOut parameter, which allows direct coupling to the source variable and thus cleanly separates the signal paths in the IEC 61499 model.
- **Unlike time function blocks**, which independently generate ticks or real-time values, this function block only accesses an externally provided value – it is purely read and buffer logic.
- **Similar function blocks** exist for other data types (e.g., `GET_BOOL`, `GET_REAL`) and follow the same design pattern.

## Conclusion

GET_TIME_OF_DAY` is a compact yet useful function block that reads a time of day from an InOut variable, buffers it, and passes it on as a controlled output value. Its clear, low-state logic and buffering make it particularly suitable for tasks where a recorded time must be available in the same format at a later time.
