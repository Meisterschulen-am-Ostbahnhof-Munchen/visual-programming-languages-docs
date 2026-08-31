# A2X2_2X_TO_2AX2

![A2X2_2X_TO_2AX2](A2X2_2X_TO_2AX2.svg)

* * * * * * * * * *

## Introduction

The A2X2_2X_TO_2AX2 function block is the inverse of [A2X2_2AX2_TO_2X](A2X2_2AX2_TO_2X.md): it decomposes an [A2X2](../../../types/bidirectional/BOOL/A2X2.md) socket into two [AX2](../../../types/bidirectional/BOOL/AX2.md) plugs — one for UP, one for DOWN.

## Interface Structure

### **Event Inputs**

The function block has no direct event inputs — communication happens exclusively through the adapters.

### **Event Outputs**

The function block has no direct event outputs.

### **Data Inputs**

The function block has no direct data inputs.

### **Data Outputs**

The function block has no direct data outputs.

### **Adapters**

- **A2X2_IN** (Socket): input to be decomposed, of type `adapter::types::bidirectional::A2X2`
- **UP** (Plug): UP channel, of type `adapter::types::bidirectional::AX2` — TRUE = forward, up, right, clockwise
- **DOWN** (Plug): DOWN channel, of type `adapter::types::bidirectional::AX2` — TRUE = backward, down, left, counter-clockwise

## Functionality

For each channel, the full bidirectional wiring between the A2X2 socket and the corresponding AX2 plug is established: whatever `A2X2_IN` receives on its indication side (`EO_UP`/`DO_UP`) is passed to `UP.EO1`/`UP.DO1`; whatever arrives at the `UP` plug on its request side (`EI1`/`DI1`) is reported back to `A2X2_IN.EI_UP`/`DI_UP`. The same wiring applies to DOWN via the `DOWN` plug. Both channels are fully independent.

## Technical Details

- Directly exploits AX2's bidirectionality — each channel needs only a single adapter, not two
- Pure wiring, no logic or state
- Every destination variable has exactly one writer, no fan-in on data connections

## State Overview

The block is stateless:

- A2X2_IN.EO_UP → UP.EO1, A2X2_IN.DO_UP → UP.DO1
- UP.EI1 → A2X2_IN.EI_UP, UP.DI1 → A2X2_IN.DI_UP
- A2X2_IN.EO_DOWN → DOWN.EO1, A2X2_IN.DO_DOWN → DOWN.DO1
- DOWN.EI1 → A2X2_IN.EI_DOWN, DOWN.DI1 → A2X2_IN.DI_DOWN

## Application Scenarios

- Splitting an A2X2 bus signal into two independently processable AX2 channels
- Connecting existing AX2-based subsystems to a central A2X2
- Test setups that need to observe or control each channel individually

## ⚖️ Comparison with Similar Blocks

The counterpart [A2X2_2AX2_TO_2X](A2X2_2AX2_TO_2X.md) composes instead of decomposing. For the same task, [A2X2_4AX_TO_2X](A2X2_4AX_TO_2X.md) / [A2X2_2X_TO_4AX](A2X2_2X_TO_4AX.md) offer an alternative with four unidirectional [AX](../../../types/unidirectional/BOOL/AX.md) adapters instead of two bidirectional AX2. The unidirectional predecessor [A2X_2X_TO_2AX](../../unidirectional/BOOL/A2X_2X_TO_2AX.md) decomposes analogously into two plain [AX](../../../types/unidirectional/BOOL/AX.md) adapters.

## Conclusion

A2X2_2X_TO_2AX2 is the most efficient way to split an A2X2 signal into two independent AX2 channels, since both adapters are already bidirectional and no extra logic is needed.
