# CLIENT_9

![CLIENT_9](CLIENT_9.svg)

* * * * * * * * * *

## Introduction

The `CLIENT_9` function block is the generic client variant with 9 send and 9 receive data fields for communicating with a matching [SERVER_9](SERVER_9.md) block. It transmits 9 data values (`SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` `SD_8` `SD_9`) to the server and receives 9 data values (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`) back. Like all `CLIENT_*` blocks, it is based on the generic `GEN_CLIENT` implementation — the same C++ base as [CLIENT_1](CLIENT_1.md)/[SERVER_1](SERVER_1.md); only the number of send/receive fields differs per instantiation.

## Interface Structure

### **Event Inputs**

- **INIT**: Opens a new connection (QI = TRUE) or closes an existing connection (QI = FALSE), carries `QI` and `ID`.
- **REQ**: Sends data to the server and requests data from the server, carries `QI` and `SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` `SD_8` `SD_9`.

### **Event Outputs**

- **INITO**: Confirms connection setup/teardown, carries `QO` and `STATUS`.
- **CNF**: Signals that new data is available from the server, carries `QO`, `STATUS` and `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`.

### **Data Inputs**

- **QI** (BOOL): Controls the connection state (`TRUE` = open connection, `FALSE` = close connection).
- **ID** (WSTRING): Connection identifier (e.g. target address/port).
- **SD_1** (ANY): Send value 1, transmitted to the server with `REQ`.
- **SD_2** (ANY): Send value 2, transmitted to the server with `REQ`.
- **SD_3** (ANY): Send value 3, transmitted to the server with `REQ`.
- **SD_4** (ANY): Send value 4, transmitted to the server with `REQ`.
- **SD_5** (ANY): Send value 5, transmitted to the server with `REQ`.
- **SD_6** (ANY): Send value 6, transmitted to the server with `REQ`.
- **SD_7** (ANY): Send value 7, transmitted to the server with `REQ`.
- **SD_8** (ANY): Send value 8, transmitted to the server with `REQ`.
- **SD_9** (ANY): Send value 9, transmitted to the server with `REQ`.

### **Data Outputs**

- **QO** (BOOL): Current connection status.
- **STATUS** (WSTRING): Status information about the connection.
- **RD_1** (ANY): Receive value 1, delivered by the server with `CNF`.
- **RD_2** (ANY): Receive value 2, delivered by the server with `CNF`.
- **RD_3** (ANY): Receive value 3, delivered by the server with `CNF`.
- **RD_4** (ANY): Receive value 4, delivered by the server with `CNF`.
- **RD_5** (ANY): Receive value 5, delivered by the server with `CNF`.
- **RD_6** (ANY): Receive value 6, delivered by the server with `CNF`.
- **RD_7** (ANY): Receive value 7, delivered by the server with `CNF`.
- **RD_8** (ANY): Receive value 8, delivered by the server with `CNF`.
- **RD_9** (ANY): Receive value 9, delivered by the server with `CNF`.

## Functionality

`CLIENT_9` initializes a connection to the matching `SERVER_9` block via `INIT` (when `QI = TRUE`) or closes it (when `QI = FALSE`); completion is confirmed via `INITO`. Via `REQ`, the values `SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` `SD_8` `SD_9` are transmitted to the server. Once response data (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`) is available, the block triggers `CNF` and provides `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` `RD_9`.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_CLIENT'`, the same C++ base as all other `CLIENT_*` variants; the number and type (`ANY`) of send/receive fields are fixed per instantiation via the type definition.
- **`ANY` data fields**: All `SD_i`/`RD_i` are generically (`ANY`) typed and adapt to whichever data type is wired to them.
- **Counterpart `SERVER_9`**: `CLIENT_9` is only functionally compatible with a `SERVER_9` block on the server side — the number of send fields on one side must match the number of receive fields on the other.

## State Overview

1. **Disconnected**: Initial state, `QO = FALSE`.
2. **Connecting**: `INIT` with `QI = TRUE` is processed.
3. **Connected**: `INITO` with `QO = TRUE` confirms the connection.
4. **Data exchange**: `REQ`/`CNF` cycle for send/receive data.
5. **Disconnecting**: `INIT` with `QI = FALSE` is processed.

## Application Scenarios

- **Communication between distributed control systems** that need to send exactly 9 values and receive exactly 9 values, without carrying unused surplus data fields.
- **Client-side connection** to a communication partner already laid out as a `SERVER_9` with the matching field count.

## Comparison with similar function blocks

- **[SERVER_9](SERVER_9.md)**: the direct counterpart on the server side, with send/receive field counts swapped.
- **[CLIENT_1](CLIENT_1.md) / [SERVER_1](SERVER_1.md)**: the same generic implementation with one send and one receive field each.

## Conclusion

`CLIENT_9` provides the generic client variant of the `GEN_CLIENT` family tailored to 9 send and 9 receive fields, suiting network connections whose payload count differs from the standard single-field variant.
