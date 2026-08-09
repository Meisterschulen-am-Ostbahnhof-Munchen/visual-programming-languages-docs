# Q_SetAudioVolume_AUS

![Q_SetAudioVolume_AUS](./Q_SetAudioVolume_AUS.svg)

* * * * * * * * * *
## Introduction

The Q_SetAudioVolume_AUS function block is a composite function block (FB) that executes the "SetAudioVolume" command according to ISO 11783-6 on a Virtual Terminal (VT). It encapsulates the base function block Q_SetAudioVolume and provides an adapter-based interface for setting the volume and reading back the previous value. The FB initializes itself via the INIT event input and acknowledges this with INITO. A new volume value can then be passed via the u8Volume adapter, whereupon the command is triggered and the result is output via CNF with STATUS and s16result.
## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Service initialization. Triggers the initialization of the internal function block.

### **Event Outputs**

- **INITO** (EInit): Confirmation of successful initialization.
- **CNF** (Event): Confirmation of the requested service. Outputted after setting the volume. Contains the output data STATUS and s16result.

### **Data Inputs**

The FB has no direct data inputs. Volume input is via the u8Volume adapter.

### **Data Outputs**

- **STATUS** (STRING): Service status message.
- **s16result** (INT): Command return value. Possible values:
- 0 (VT_E_NO_ERR): Success.
- -6 (VT_E_OVERFLOW): Buffer overflow.
- -8 (VT_E_NOACT): Command not possible in the current state.
- -21 (VT_E_NO_INSTANCE): No VT client available.
- -129 (VT_E_ISO_INSTANCE_INVALID): Connection instance invalid.
- -128 (VT_E_HANDLE_INVALID): Handle invalid.
- -130 (VT_E_NOT_ALIVE): VT not active.

### **Adapters**

- **u8Volume** (Socket): Unidirectional adapter of type OFF. Receives the desired volume as a value between 0 and 100%.
- **u8OldVolume** (Plug): Unidirectional adapter of type OFF. Outputs the volume level (0–100%) valid before the command.

## Functionality

After startup, the FB is initialized via the INIT input. The internal block Q_SetAudioVolume is prepared, and INITO signals its readiness. As soon as a new volume value is received via the u8Volume adapter (event E1 of the adapter), the command to change the volume is sent to the VT. Upon completion of the process, CNF is triggered, and the output variables STATUS and s16result contain the result. Simultaneously, the previous volume value is output via the u8OldVolume adapter, allowing external logic to read the old value.

The possible error codes correspond to the ISO11783-6 definitions and cover typical VT error situations.

## Technical Features

- The function block is implemented as a composite block that uses the basic function block Q_SetAudioVolume from the isobus library.
- The interface uses only adapters for data transmission, resulting in loose coupling and flexible wiring.
- The adapters are of type "unidirectional::OFF" and enable event-driven data transmission.

`` - The function block (FB) is designed for use in ISOBUS systems according to ISO 11783-6.

## State Overview

Since this is a composite block with an internal FB, there is no explicit top-level state machine. The FB goes through the following phases:

1. Initialization (INIT received → INITO sent)
2. Ready (waits for volume change via u8Volume adapter)
3. Processing (internal command is executed)
4. Result output (CNF with STATUS/s16result)

A detailed state machine is implemented in the internal block Q_SetAudioVolume.

## Application Scenarios

- Agricultural machine control: Adjusting the volume of voice outputs or warning tones from the virtual terminal.
- Integration into ISOBUS-compliant applications that change audio settings via the operator terminal.
- Combination with other VT command blocks such as Q_SelectAudioOutput, Q_Beep, etc.

## Comparison with similar blocks

The Q_SetAudioVolume_AUS block differs from a direct Q_SetAudioVolume block in its use of adapters for data transmission. While Q_SetAudioVolume may have direct data inputs (e.g., u8Volume as VarDeclaration), the adapter variant allows for decoupled, event-driven communication. Similar adapter blocks exist for other VT commands, resulting in a consistent design pattern.

## Conclusion

Q_SetAudioVolume_AUS is a specialized function block for volume control of an ISOBUS VT. The adapter-based interface ensures a clear separation between the control and data layers. The block provides complete feedback on the success of the command and is suitable for reliable use in agricultural control systems.
