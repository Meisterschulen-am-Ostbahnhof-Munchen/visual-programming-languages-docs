# AQ_AX_SEL_AQ

![AQ_AX_SEL_AQ](./AQ_AX_SEL_AQ.svg)

* * * * * * * * * *
## Introduction

The function block `AQ_AX_SEL_AQ` is used for binary selection between two analog or value-based input signals provided via adapters. A selector adapter controls which of the two inputs is passed through to the output. The block encapsulates the classic selection logic and prepares it for event-driven execution in IEC 61499 environments.

## Interface Structure

The function block communicates exclusively via standardized adapter interfaces. This simplifies modeling in the application network, as related data and event lines are transmitted together.

## **Event Inputs**
The block does not have direct event inputs. Event processing is handled implicitly via the events of the connected input adapters (`IN0`, `IN1`, `G`).

### **Event Outputs**
The function block does not have direct event outputs. Events are forwarded via the output adapter (`OUT`).

### **Data Inputs**
There are no direct data inputs on the function block interface. Data is transmitted encapsulated via the sockets.

### **Data Outputs**
There are no direct data outputs. Data is provided encapsulated via the plug.


### ### **Adapter**

#### **Sockets (Input Interfaces)**

* **G** (Type: `adapter::types::unidirectional::AX`):

* **Description**: Selector (selection signal).

* **Data**: `D1` (Selector state).

* **Event**: `E1` (Trigger on selector value change).

* **IN0** (Type: `adapter::types::unidirectional::AQ`):

* **Description**: First selectable input channel (selected at `G = FALSE`).

* **Data**: `D1` (Input value).

* **Event**: `E1` (Trigger on value change at IN0).

* **IN1** (Type: `adapter::types::unidirectional::AQ`):

* **Description**: Second selectable input channel (selected with `G = TRUE`).

* **Data**: `D1` (Input value).

* **Event**: `E1` (Trigger on value change at IN1).

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AQ`):

* **Description**: The selected output channel.

* **Data**: `D1` (Output value of the selected input).

* **Event**: `E1` (Output event for signaling a new valid value).

## Functionality

The function block is implemented internally as a function block network and operates according to the following sequence:

1. **Event Acquisition**: As soon as an event `E1` arrives at one of the inputs (`IN0`, `IN1`) or the selector (`G`), it is intercepted and synchronized via edge- or value-triggered auxiliary function blocks (`E_D_FF` and `E_D_FF_ANY`).


 2. **Data Buffering**: The current values of the adapter inputs are buffered in the internal network using function blocks `F_MOVE` and formatted according to the specified type.

3. **Selection Logic**: The internal core function block `F_SEL` (based on the standardized selection function according to IEC 61131-3) evaluates the state of the selector:

* If `G.D1` is set to `FALSE`, the value of `IN0` is passed through.

* If `G.D1` is set to `TRUE`, the value of `IN1` is passed through.

4. **Output**: The selected value is passed to the output plug `OUT.D1`. Simultaneously, the output event `OUT.E1` is triggered to inform subsequent program components in the control network about the value change.

## Technical Features

* **Event-Data Consistency**: The use of internal D flip-flops ensures that the data values are read and processed at the exact moment the corresponding change event occurs.

* **Typing**: The function block internally uses `F_MOVE` with the data type `BYTE` to encapsulate and assign the adapter data. This means that the `AQ` interfaces used transmit binary- or byte-compatible data structures.


* ## State Overview

Since `AQ_AX_SEL_AQ` is a purely data- and event-driven combination block without its own internal state machine (ECC), its behavior can be described using the following logical table:

| Selector (`G.D1`) | Value `IN0.D1` | Value `IN1.D1` | Output (`OUT.D1`) | Behavior of the Output Event (`OUT.E1`) |

| :---: | :---: | :---: | :---: | :--- |

| **FALSE** | `Wert_A` | `Wert_B` | **`Wert_A`** | Fires as soon as an event occurs at `IN0.E1`, `IN1.E1`, or `G.E1`. |

**TRUE** | `Wert_A` | `Wert_B` | **`Wert_B`** | Fires as soon as an event occurs at `IN0.E1`, `IN1.E1`, or `G.E1`. |


## Application Scenarios

* **Sensor Redundancy / Switchover**: Automatic or manual switching between a primary sensor (`IN0`) and a secondary/backup sensor (`IN1`) in case of a fault via the control signal `G`.

* **Manual/Automatic Operation**: Selection of setpoints for actuators. In automatic mode (`G = TRUE`), the calculated controller value (`IN1`) is used; in manual mode (`G = FALSE`), a predefined fixed value or a manually specified parameter (`IN0`) is used.

* **Recipe-Controlled Parameterization**: Dynamic switching of process limits during operation.


* ## Comparison with Similar Components

* **Standard `SEL` (IEC 61131-3)**: The classic `SEL` component has no event control and reacts purely cyclically to incoming data. `AQ_AX_SEL_AQ` extends this functionality with the event-based paradigm of IEC 61499.

* **Classic Multiplexers (MUX)**: While a multiplexer usually selects from a large number of inputs, this component is specifically limited to efficient 1-out-of-2 selection (binary selection), which minimizes parameterization and wiring effort.

## Conclusion

The `AQ_AX_SEL_AQ` is a useful infrastructure component for modular 4diac applications. By completely encapsulating the signals in adapter connections, it significantly contributes to clarity in the application window and ensures robust, event-driven signal forwarding.