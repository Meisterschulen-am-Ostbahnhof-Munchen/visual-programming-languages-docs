# SERVER_0_9

![SERVER_0_9](SERVER_0_9.svg)

* * * * * * * * * *
## Introduction

The `SERVER_0_9` function block is the generic server variant with 0 send and 9 receive data fields for communicating with a matching [CLIENT_9_0](CLIENT_9_0.md) block. It receives 9 data values (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`) from the client without sending any payload itself. Like all `SERVER_*` blocks, it is based on the generic `GEN_SERVER` implementation — the same C++ base as [CLIENT_1](CLIENT_1.md)/[SERVER_1](SERVER_1.md); only the number of send/receive fields differs per instantiation.

## Interface Structure

### **Event Inputs**

- **INIT**: Enables the server for a client connection (QI = TRUE) or closes it (QI = FALSE), carries `QI` and `ID`.
- **RSP**: Sends data to the client, carries `QI`.

### **Event Outputs**

- **INITO**: Confirms connection setup/teardown, carries `QO` and `STATUS`.
- **IND**: Signals that new data is available from the client, carries `QO`, `STATUS` and `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`.

### **Data Inputs**

- **QI** (BOOL): Controls the connection state (`TRUE` = open connection, `FALSE` = close connection).
- **ID** (WSTRING): Connection identifier (e.g. target address/port).
- No send fields (`SERVER_0_9` transmits no payload data with `RSP`, only connection control).

### **Data Outputs**

- **QO** (BOOL): Current connection status.
- **STATUS** (WSTRING): Status information about the connection.
- **RD_1** (ANY): Receive value 1, delivered by the client with `IND`.
- **RD_2** (ANY): Receive value 2, delivered by the client with `IND`.
- **RD_3** (ANY): Receive value 3, delivered by the client with `IND`.
- **RD_4** (ANY): Receive value 4, delivered by the client with `IND`.
- **RD_5** (ANY): Receive value 5, delivered by the client with `IND`.
- **RD_6** (ANY): Receive value 6, delivered by the client with `IND`.
- **RD_7** (ANY): Receive value 7, delivered by the client with `IND`.
- **RD_8** (ANY): Receive value 8, delivered by the client with `IND`.
- **RD_9** (ANY): Receive value 9, delivered by the client with `IND`.

## Functionality

`SERVER_0_9` initializes a connection to the matching `CLIENT_9_0` block via `INIT` (when `QI = TRUE`) or closes it (when `QI = FALSE`); completion is confirmed via `INITO`. Via `RSP`, a request without payload is sent. Once response data (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`) is available, the block triggers `IND` and provides `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_SERVER'`, the same C++ base as all other `SERVER_*` variants; the number and type (`ANY`) of send/receive fields are fixed per instantiation via the type definition.
- **`ANY` data fields**: All `SD_i`/`RD_i` are generically (`ANY`) typed and adapt to whichever data type is wired to them.
- **Counterpart `CLIENT_9_0`**: `SERVER_0_9` is only functionally compatible with a `CLIENT_9_0` block on the client side — the number of send fields on one side must match the number of receive fields on the other.

## State Overview

1. **Disconnected**: Initial state, `QO = FALSE`.
2. **Connecting**: `INIT` with `QI = TRUE` is processed.
3. **Connected**: `INITO` with `QO = TRUE` confirms the connection.
4. **Data exchange**: `RSP`/`IND` cycle for send/receive data.
5. **Disconnecting**: `INIT` with `QI = FALSE` is processed.

## Application Scenarios

- **Communication between distributed control systems** that need to send exactly 0 values and receive exactly 9 values, without carrying unused surplus data fields.
- **Server-side connection** to a communication partner already laid out as a `CLIENT_9_0` with the matching field count.

## Comparison with similar function blocks

- **[CLIENT_9_0](CLIENT_9_0.md)**: the direct counterpart on the client side, with send/receive field counts swapped.
- **[CLIENT_1](CLIENT_1.md) / [SERVER_1](SERVER_1.md)**: the same generic implementation with one send and one receive field each.

## Conclusion

`SERVER_0_9` provides the generic server variant of the `GEN_SERVER` family tailored to 0 send and 9 receive fields, suiting network connections whose payload count differs from the standard single-field variant.
