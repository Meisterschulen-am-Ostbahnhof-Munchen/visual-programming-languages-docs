# INI_AB

![INI_AB](INI_AB.svg)

* * * * * * * * * *
## Introduction

`INI_AB` loads and stores a `BYTE` value in the `settings.ini` file, addressed by section (`SECTION`) and key (`KEY`). It is the `settings.ini` counterpart to [NVS_AB](../esp32_nvs/NVS_AB.md) and uses the same two-adapter architecture with unidirectional `AB` adapters.

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
- **DEFAULT_VALUE** (BYTE): value returned when nothing is stored under `SECTION`/`KEY` yet.

### **Data Outputs**

- **QO** (BOOL): success qualifier, carried with `INITO` and the internal adapter confirmations.
- **STATUS** (STRING): status message of the file access.

### **Adapters**

- **AB_IN** (Socket, type `AB`): new value to store -- an adapter event on `AB_IN.E1` triggers a `SET` on the internal INI block, `AB_IN.D1` carries the value to write.
- **AB_OUT** (Plug, type `AB`): outputs the most recently read value -- both after the automatic initial read on `INIT` and after each confirmed write (`AB_OUT.D1`/`AB_OUT.E1`).

## Functionality

`INI_AB` wraps an internal instance of `eclipse4diac::storage::INI` plus an `E_PERMIT` gate (`SET_PERMIT`). On `INIT`, the internal INI instance is initialized (`INI.INIT`) and a `GET` is triggered automatically, returning the value stored under `SECTION`/`KEY` (or `DEFAULT_VALUE`); the result is output via `AB_OUT`, and `INITO` confirms completion.

To write, the block connected to `AB_IN` fires an adapter event (`AB_IN.E1`) carrying the new value (`AB_IN.D1`), which triggers `INI.SET`. Whether the successful write is additionally reported back via `AB_OUT` is controlled by `SETM`: if `SETM` is set, `SET_PERMIT` releases the `AB_OUT.E1` event after a successful `SET` ("mirroring").

## Technical Details

- Pure composite FB with no ECC of its own -- the actual file access logic lives in the internal `INI` instance; `INI_AB` only wires events and data between it and the two `AB` adapters.
- Two separate unidirectional adapters (`AB_IN`/`AB_OUT`) instead of a single bidirectional one -- this lets the read and write paths connect to different peers, which [INI_AB2](INI_AB2.md) (a single shared `AB2` socket) cannot do.
- Addressing via `SECTION` **and** `KEY` (rather than just `KEY` for the `NVS_*` blocks) matches the classic INI file format.

## State Overview

The block is stateless in terms of its own ECC: on `INIT` it runs through initialization plus an initial read once, then reacts to every `AB_IN` adapter event with an INI write and, optionally, a confirmation via `AB_OUT`.

## Application Scenarios

- Persisting individual `BYTE` configuration values (e.g. operating mode, channel selection) in a human-readable `settings.ini`
- Building a read/write pair where the read and write sides need to connect to different blocks
- Configuration files that also need to be viewable/editable outside the controller (e.g. with a text editor)

## ⚖️ Comparison with Similar Blocks

Compare with [INI_AB2](INI_AB2.md), which serves the same purpose through a single bidirectional `AB2` adapter instead of two unidirectional `AB` adapters, and with [NVS_AB](../esp32_nvs/NVS_AB.md), which provides the same interface for the ESP32 NVS flash storage instead of `settings.ini`.

## Conclusion

`INI_AB` provides simple, unidirectionally wired access to a persistent `BYTE` value in `settings.ini`, and fits anywhere the read and write paths need to be kept separate.
