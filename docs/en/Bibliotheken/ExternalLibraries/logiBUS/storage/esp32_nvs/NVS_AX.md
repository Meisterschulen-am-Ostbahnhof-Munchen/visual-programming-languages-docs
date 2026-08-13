# NVS_AX

![NVS_AX](NVS_AX.svg)

* * * * * * * * * *
## Introduction

`NVS_AX` loads and stores a `BOOL` value under a key (`KEY`) in the ESP32's non-volatile storage (NVS). It is the Boolean counterpart to [NVS_AB](NVS_AB.md) and uses the same two-adapter architecture, but with unidirectional `AX` adapters instead of `AB`.

## Interface Structure

### **Event Inputs**

- **INIT**: initializes the block and reads the value stored under `KEY` (or `DEFAULT_VALUE` if none exists yet). Carries `QI`, `SETM`, `KEY`, `DEFAULT_VALUE`.

### **Event Outputs**

- **INITO**: confirms initialization and the initial read, carries `QO` and `STATUS`.

### **Data Inputs**

- **QI** (BOOL): qualifier for the `INIT` event.
- **SETM** (BOOL): enables mirroring (confirmation) on write (`SET`).
- **KEY** (STRING): name of the key in the NVS.
- **DEFAULT_VALUE** (BOOL): value returned when nothing is stored under `KEY` yet.

### **Data Outputs**

- **QO** (BOOL): success qualifier, carried with `INITO` and the internal adapter confirmations.
- **STATUS** (STRING): status message of the NVS access.

### **Adapters**

- **AX_IN** (Socket, type `AX`): new value to store -- an adapter event on `AX_IN.E1` triggers a `SET` on the internal NVS block, `AX_IN.D1` carries the value to write.
- **AX_OUT** (Plug, type `AX`): outputs the most recently read value -- both after the automatic initial read on `INIT` and after each confirmed write (`AX_OUT.D1`/`AX_OUT.E1`).

## Functionality

`NVS_AX` wraps an internal instance of `logiBUS::storage::esp32_nvs::NVS` plus an `E_PERMIT` gate (`SET_PERMIT`). On `INIT`, the internal NVS instance is initialized (`NVS.INIT`) and a `GET` is triggered automatically, returning the value stored under `KEY` (or `DEFAULT_VALUE`); the result is output via `AX_OUT`, and `INITO` confirms completion.

To write, the block connected to `AX_IN` fires an adapter event (`AX_IN.E1`) carrying the new value (`AX_IN.D1`), which triggers `NVS.SET`. Whether the successful write is additionally reported back via `AX_OUT` is controlled by `SETM`: if `SETM` is set, `SET_PERMIT` releases the `AX_OUT.E1` event after a successful `SET` ("mirroring").

## Technical Details

- Pure composite FB with no ECC of its own -- the actual flash logic lives in the internal `NVS` instance; `NVS_AX` only wires events and data between it and the two `AX` adapters.
- Two separate unidirectional adapters (`AX_IN`/`AX_OUT`) -- this lets the read and write paths connect to different peers.
- `SETM` only controls whether a write is additionally mirrored back via an `AX_OUT` adapter event -- the value is stored either way.

## State Overview

The block is stateless in terms of its own ECC: on `INIT` it runs through initialization plus an initial read once, then reacts to every `AX_IN` adapter event with an NVS write and, optionally, a confirmation via `AX_OUT`.

## Application Scenarios

- Persisting individual `BOOL` configuration values (e.g. enable flags, operating-mode switches) on the ESP32
- Building a read/write pair where the read and write sides need to connect to different blocks
- Restoring a last-stored `BOOL` value after a restart via `AX_OUT`

## ⚖️ Comparison with Similar Blocks

Compare with [NVS_AB](NVS_AB.md), which uses the same architecture for `BYTE` instead of `BOOL` values, and with [INI_AX](../ini/INI_AX.md), which provides the same interface for the text-based `settings.ini` instead of the NVS flash storage.

## Conclusion

`NVS_AX` provides simple, unidirectionally wired access to a persistent `BOOL` value in the ESP32's NVS, and fits anywhere the read and write paths need to be kept separate.
