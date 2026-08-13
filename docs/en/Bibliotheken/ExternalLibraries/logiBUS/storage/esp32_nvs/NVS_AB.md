# NVS_AB

![NVS_AB](NVS_AB.svg)

* * * * * * * * * *
## Introduction

`NVS_AB` loads and stores a `BYTE` value under a key (`KEY`) in the ESP32's non-volatile storage (NVS). Unlike the bidirectional [NVS_AB2](NVS_AB2.md), it uses two separate unidirectional `AB` adapters: a socket for writing (`AB_IN`) and a plug for reading/confirming (`AB_OUT`).

## Interface Structure

### **Event Inputs**

- **INIT**: initializes the block and reads the value stored under `KEY` (or `DEFAULT_VALUE` if none exists yet). Carries `QI`, `SETM`, `KEY`, `DEFAULT_VALUE`.

### **Event Outputs**

- **INITO**: confirms initialization and the initial read, carries `QO` and `STATUS`.

### **Data Inputs**

- **QI** (BOOL): qualifier for the `INIT` event.
- **SETM** (BOOL): enables mirroring (confirmation) on write (`SET`).
- **KEY** (STRING): name of the key in the NVS.
- **DEFAULT_VALUE** (BYTE): value returned when nothing is stored under `KEY` yet.

### **Data Outputs**

- **QO** (BOOL): success qualifier, carried with `INITO` and the internal adapter confirmations.
- **STATUS** (STRING): status message of the NVS access.

### **Adapters**

- **AB_IN** (Socket, type `AB`): new value to store -- an adapter event on `AB_IN.E1` triggers a `SET` on the internal NVS block, `AB_IN.D1` carries the value to write.
- **AB_OUT** (Plug, type `AB`): outputs the most recently read value -- both after the automatic initial read on `INIT` and after each confirmed write (`AB_OUT.D1`/`AB_OUT.E1`).

## Functionality

`NVS_AB` wraps an internal instance of `logiBUS::storage::esp32_nvs::NVS` plus an `E_PERMIT` gate (`SET_PERMIT`). On `INIT`, the internal NVS instance is initialized (`NVS.INIT`) and a `GET` is triggered automatically, returning the value stored under `KEY` (or `DEFAULT_VALUE`); the result is output via `AB_OUT`, and `INITO` confirms completion.

To write, the block connected to `AB_IN` fires an adapter event (`AB_IN.E1`) carrying the new value (`AB_IN.D1`), which triggers `NVS.SET`. Whether the successful write is additionally reported back via `AB_OUT` is controlled by `SETM`: if `SETM` is set, `SET_PERMIT` releases the `AB_OUT.E1` event after a successful `SET` ("mirroring").

## Technical Details

- Pure composite FB with no ECC of its own -- the actual flash logic lives in the internal `NVS` instance; `NVS_AB` only wires events and data between it and the two `AB` adapters.
- Two separate unidirectional adapters (`AB_IN`/`AB_OUT`) instead of a single bidirectional one -- this lets the read and write paths connect to different peers, which [NVS_AB2](NVS_AB2.md) (a single shared `AB2` socket) cannot do.
- `SETM` only controls whether a write is additionally mirrored back via an `AB_OUT` adapter event -- the value is stored either way.

## State Overview

The block is stateless in terms of its own ECC: on `INIT` it runs through initialization plus an initial read once, then reacts to every `AB_IN` adapter event with an NVS write and, optionally, a confirmation via `AB_OUT`.

## Application Scenarios

- Persisting individual `BYTE` configuration values (e.g. operating mode, channel selection) on the ESP32
- Building a read/write pair where the read and write sides need to connect to different blocks
- Restoring a last-stored `BYTE` value after a restart via `AB_OUT`

## ⚖️ Comparison with Similar Blocks

Compare with [NVS_AB2](NVS_AB2.md), which serves the same purpose through a single bidirectional `AB2` adapter instead of two unidirectional `AB` adapters, and with [INI_AB](../ini/INI_AB.md), which provides the same interface for the text-based `settings.ini` instead of the NVS flash storage.

## Conclusion

`NVS_AB` provides simple, unidirectionally wired access to a persistent `BYTE` value in the ESP32's NVS, and fits anywhere the read and write paths need to be kept separate.
