# ALI_TO_AI

![ALI_TO_AI](./ALI_TO_AI.svg)

* * * * * * * * * *
## Introduction

The **ALI_TO_AI** function block is a composite function block (FB) that converts an **ALI adapter** (input of a LINT value interface) into an **AI adapter** (output of an INT value interface). It serves to convert data from a LINT-based adapter to the INT-based adapter type without requiring the user to implement the conversion themselves.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |
|----------|----------|-----------------------------------------------------|
| ALI_IN | Event | Control signal of the ALI adapter, triggers the conversion |

### **Event Outputs**

| Name | Data Type | Description |
|----------|----------|-------------------------------------------------------|
| AI_OUT | Event | Confirmation signal from the AI adapter after successful conversion |

### **Data Inputs**

| Name | Data Type | Description |
|----------|----------|------------------------------------|
| ALI_IN.D1| LINT | The LINT value to be converted |

### **Data Outputs**

| Name | Data Type | Description |
|----------|----------|------------------------------------|
| AI_OUT.D1| INT | The converted INT value |

### **Adapter**

| Direction | Name | Type | Description |
|----------|---------|--------------|---------------------------------------------|
| Socket | ALI_IN | ALI (unidirectional) | Returns LINT values and control events |
| Plug | AI_OUT | AI (unidirectional) | Outputs converted INT values and events |

## Functionality

This function block operates as a simple coupling of an ALI socket to an AI plug. Internally, the available conversion function block **F_LINT_TO_INT** is used.

1. An incoming event at **ALI_IN.E1** triggers the conversion function block.
2. Simultaneously, the current value of **ALI_IN.D1** is passed to the input of the converter. 3. After the conversion is complete, the result is forwarded to **AI_OUT.D1**.
4. An acknowledgment event is output via **AI_OUT.E1**.

The entire process is atomic within a single cycle – delays only occur due to the runtime of the conversion block.

## Technical Features

- **Pure Adapter Coupling**: The block does not contain its own state logic or timing.
- **Use of IEC 61131 Conversion**: The actual type conversion is performed by the standardized block `F_LINT_TO_INT`.
- **Simple Composition**: All connections are direct and without intermediate logic.
- **Type- and Event-Driven**: The conversion is only executed when an event occurs at the ALI input.

## State Overview

As a composite function block without its own state diagram, **ALI_TO_AI** does not have its own state machine. The internal conversion function block `F_LINT_TO_INT` operates according to the simple pattern:

- **IDLE**: Waiting for an event.
- **CONVERT**: Executing the conversion and outputting the result.

## Application Scenarios

- **System Coupling**: When a sensor module provides LINT values via an ALI adapter, but the control system expects INT values via an AI adapter.
- **Protocol or Interface Adaptation**: Integration of components from different manufacturers that use different adapter types.
- **Data Path Cleanup**: Simplifying the signal flow through defined conversion at a central location.

## Comparison with Similar Function Blocks

| Function Block | Function | Difference |
|-----------------|------------------------------------------|------------------------------------------------------------------|
| ALI_TO_AI | LINT → INT via adapter | Specifically for unidirectional ALI/AI interfaces |
| LINT_TO_INT | Direct conversion LINT → INT | No adapter integration – pure data conversion |
| AI_TO_ALI | INT → LINT (reverse direction) | Same structure, but opposite data direction |

## Conclusion

**ALI_TO_AI** is a small but useful compound block that bridges the gap between two common IEC 61499 adapter types. Encapsulating the conversion logic simplifies reuse and accelerates system integration. The block is robust because it uses a standardized IEC 61131 converter and requires no configuration.
