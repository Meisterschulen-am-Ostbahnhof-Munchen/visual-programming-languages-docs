# INI_AX

![INI_AX](INI_AX.svg)

* * * * * * * * * *
## Introduction

`INI_AX` loads and stores a `BOOL` value in the `settings.ini` file, addressed by section (`SECTION`) and key (`KEY`). It is the Boolean counterpart to [INI_AB](INI_AB.md) and the `settings.ini` counterpart to [NVS_AX](../esp32_nvs/NVS_AX.md).

## Interface Structure

### **Event Inputs**

- **INIT**: initializes the block and reads the value stored under `SECTION`/`KEY` (or `DEFAULT_VALUE` if none exists yet). Carries `QI`, `SETM`, `SECTION`, `KEY`, `DEFAULT_VALUE`.

### **Event Outputs**

- **INITO**: confirms initialization and the initial read, carries `QO` and `STATUS`.

### **Data Inputs**

- **QI** (BOOL): qualifier for the `INIT` event.
- **SETM** (BOOL): enables mirroring (confirmation) on write (`SET`).
- **SECTION** (STRING): name of the section in `settings.ini`.
- **KEY** (STRING): name of the key within the section.
- **DEFAULT_VALUE** (BOOL): value returned when nothing is stored under `SECTION`/`KEY` yet.

### **Data Outputs**

- **QO** (BOOL): success qualifier, carried with `INITO` and the internal adapter confirmations.
- **STATUS** (STRING): status message of the file access.

### **Adapters**

- **AX_IN** (Socket, type `AX`): new value to store -- an adapter event on `AX_IN.E1` triggers a `SET` on the internal INI block, `AX_IN.D1` carries the value to write.
- **AX_OUT** (Plug, type `AX`): outputs the most recently read value -- both after the automatic initial read on `INIT` and after each confirmed write (`AX_OUT.D1`/`AX_OUT.E1`).

## Functionality

`INI_AX` wraps an internal instance of `eclipse4diac::storage::INI` plus an `E_PERMIT` gate (`SET_PERMIT`). On `INIT`, the internal INI instance is initialized (`INI.INIT`) and a `GET` is triggered automatically, returning the value stored under `SECTION`/`KEY` (or `DEFAULT_VALUE`); the result is output via `AX_OUT`, and `INITO` confirms completion.

To write, the block connected to `AX_IN` fires an adapter event (`AX_IN.E1`) carrying the new value (`AX_IN.D1`), which triggers `INI.SET`. Whether the successful write is additionally reported back via `AX_OUT` is controlled by `SETM`: if `SETM` is set, `SET_PERMIT` releases the `AX_OUT.E1` event after a successful `SET` ("mirroring").

## Technical Details

- Pure composite FB with no ECC of its own -- the actual file access logic lives in the internal `INI` instance; `INI_AX` only wires events and data between it and the two `AX` adapters.
- Two separate unidirectional adapters (`AX_IN`/`AX_OUT`) -- this lets the read and write paths connect to different peers.
- Addressing via `SECTION` **and** `KEY` (rather than just `KEY` for the `NVS_*` blocks) matches the classic INI file format.

## State Overview

The block is stateless in terms of its own ECC: on `INIT` it runs through initialization plus an initial read once, then reacts to every `AX_IN` adapter event with an INI write and, optionally, a confirmation via `AX_OUT`.

## Application Scenarios

- Persisting individual `BOOL` configuration values (e.g. enable flags, operating-mode switches) in a human-readable `settings.ini`
- Building a read/write pair where the read and write sides need to connect to different blocks
- Configuration files that also need to be viewable/editable outside the controller (e.g. with a text editor)

## ⚖️ Comparison with Similar Blocks

Compare with [INI_AB](INI_AB.md), which uses the same architecture for `BYTE` instead of `BOOL` values, and with [NVS_AX](../esp32_nvs/NVS_AX.md), which provides the same interface for the ESP32 NVS flash storage instead of `settings.ini`.

## Conclusion

`INI_AX` provides simple, unidirectionally wired access to a persistent `BOOL` value in `settings.ini`, and fits anywhere the read and write paths need to be kept separate.
