# INI_IN_AND_STORE / NVS_IN_AND_STORE: Shared Pattern

* * * * * * * * * *
## Introduction

`MyLib::sys` contains a family of blocks that **persistently store** a value entered via the VT and automatically reload it on deployment — either in an INI file (`INI_IN_AND_STORE_*`) or in ESP32 flash (NVS, `NVS_IN_AND_STORE_*`). This page explains the shared pattern.

## Naming Scheme

`{INI|NVS}_IN_AND_STORE_<type>`, where `<type>` determines the data type: `AIS` (string adapter), `AR` (REAL adapter, with physical scaling `NumericObjectPool_S`), `AUDI` (UDINT adapter) in test_AX; `UDINT` (classic, no adapter) in test_B.

## Functionality (test_AX, adapter-based)

1. A VT input field (`StringValue_AIS`/`NumericValue_PHYSA`/…) delivers the user-entered value as an adapter.
2. `INI_<type>`/`NVS_<type>` (`eclipse4diac::storage::INI_*` or `logiBUS::storage::esp32_nvs::NVS_*`) stores this value persistently under `KEY`/`SECTION` (INI only) and returns the last stored value on `INIT` (`SETM=TRUE`: storing active, `DEFAULT_VALUE`: initial value if nothing has been stored yet).
3. The (newly loaded or newly entered) value is split via `<type>_SPLIT_2`: once as plug `VALUEO` outward (for reuse in the calling network) and once to `Q_StringValue_AIS`/`Q_NumericValue_PHYSA` (writing back to the VT display field, so the input field and display stay in sync).

## Functionality (test_B, classic)

The `test_B` variant (`INI_IN_AND_STORE_UDINT`/`NVS_IN_AND_STORE_UDINT`) is older and uses classic event/data connections instead of adapters: a `NumericValue_ID` input field delivers a DWORD value, converted to UDINT via `F_DWORD_TO_UDINT` and passed to `INI`/`NVS` (generic, non-type-specific blocks). The stored value goes out as `VALUEO` and back to `Q_NumericValue` for display.

## Summary

Both variants solve the same problem — "remember a user-entered value across restarts" — with the same basic pattern (input field → storage FB with KEY/SECTION → split into output + display write-back), differing only in storage location (INI file vs. NVS flash) and wiring style (adapters in test_AX, classic in test_B).

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
