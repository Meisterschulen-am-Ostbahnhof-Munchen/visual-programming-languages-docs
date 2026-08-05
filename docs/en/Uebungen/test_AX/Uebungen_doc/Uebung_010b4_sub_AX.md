Here is the documentation for exercise `Uebung_010b4_sub_AX`, based on the provided XML data.

# Exercise_010b4_sub_AX: IX to QX (generic)

* * * * * * * * * *

## Introduction

This exercise covers the creation of a **sub-application** (SubApp) that establishes a generic link between an ISOBUS input element (softkey) and a logiBUS output. The goal is to map a softkey input (`IX`) directly to a digital output (`QX`). By using interface variables, this function block is reusable for different object IDs and outputs.


## Function Blocks (FBs) Used

This exercise defines a sub-application that internally uses two specialized communication blocks to implement signal processing between ISOBUS and logiBUS.


### Sub-Blocks: Exercise_010b4_sub_AX

- **Type**: SubAppType

- **Description**: IX to QX (generic)

- **Internal Function Blocks Used**:

- **IXA**: `isobus::UT::io::Softkey::Softkey_IXA`

- **Parameters**:

- `QI` = `TRUE` (Block is active)

- **Data Input**:

- `u16ObjId` (Connected to interface `u16ObjId`)

- **Adapter Output**:

- `IN` (Connected to `QXA.OUT`)

- **QXA**: `logiBUS::io::DQ::logiBUS_QXA`

- **Parameters**:

- `QI` = `TRUE` (Block is active)

- **Data Input**:

- `Output` (Connected to interface `Output`)

- **Adapter Input**:

- `OUT` (Connected to `IXA.IN`)

- **Functionality**:

This sub-block acts as a bridge. It receives an object ID (`u16ObjId`) that identifies a softkey on an ISOBUS Universal Terminal (UT). Simultaneously, it receives an output configuration (`Output`, type `logiBUS_DO_S`) that determines which physical output should be switched.

Within the network, the softkey status is captured via the `IXA` block. Instead of wiring discrete events and Booleans, this implementation uses an adapter connection. The adapter port `IN` of the softkey block (`IXA`) is directly connected to the adapter port `OUT` of the output block (`QXA`). This allows the state (e.g., key press) to be directly passed through to the hardware output.


## Program Flow and Connections

The network within the sub-application is kept minimal and relies on abstraction through adapters.

1. **Interface Inputs**:

* **u16ObjId (UINT)**: The ID of the softkey is passed here (initial value: `ID_NULL`). This variable is passed internally to `IXA.u16ObjId`.

* **Output (logiBUS_DO_S)**: The target output is defined here (e.g., Output_Q1..Q8). This variable is passed internally to `QXA.Output`.

2. **Internal Logic**:

* The function block `IXA` initializes communication with the softkey under the specified ID.

* The function block `QXA` initializes the control of the selected digital output.

* The connection between input and output is not made via classic `AND`/`OR` logic or event triggers (`INIT`, `REQ`, `CNF`), but via the **adapter connection** (`Connection Source="IXA.IN" Destination="QXA.OUT"`). This abstracts the signal flow and ensures that the output follows the logical state of the input adapter.

**Application Notes:**

* This function block is intended as a generic module. It can be instantiated multiple times in the main program to assign different buttons to different outputs without having to reprogram the internal logic.

* No explicit events are passed externally; Control is handled entirely internally via the bus drivers.

## Summary

The `Uebung_010b4_sub_AX` is a compact module for directly connecting an ISOBUS softkey to a digital logiBUS output. By encapsulating it in a sub-application and using adapters, the complexity of the underlying protocols is hidden, enabling simple and quick assignment of keys to outputs in higher-level applications.