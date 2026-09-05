# NVS_IN_AND_STORE_AR2

![NVS_IN_AND_STORE_AR2_network](./NVS_IN_AND_STORE_AR2_network.svg)

* * * * * * * * * *

## Introduction

`NVS_IN_AND_STORE_AR2` is the AR2-adapter variant of `NVS_IN_AND_STORE_AR` (ESP32 flash storage instead of an INI file): a physically scaled REAL value entered via the VT is persistently stored in NVS flash via `logiBUS::storage::esp32_nvs::NVS_AR2`. Since `NVS_AR2` (unlike the INI variant) has no `SECTION` concept either, that parameter is absent compared to `INI_IN_AND_STORE_AR2`. As there, `AR_TO_AR2.AR_OUT` is duplicated via `AR_SPLIT_2`: VT display (`Q_NumericValue_PHYSA`) + `VALUEO` for a further consumer.

For the general pattern, see [INI_IN_AND_STORE / NVS_IN_AND_STORE (shared pattern)](./INI-NVS-Storage-Blocks.md).

## Technical notes

- `SETM=TRUE`, same reasoning as [`INI_IN_AND_STORE_AR2`](./INI_IN_AND_STORE_AR2.md): live changes are confirmed immediately, not only at the next boot.
- No `SECTION` parameter, since NVS keys are flat (no INI-section concept).

## Summary

AR2-adapter variant of the NVS storage family (ESP32 flash instead of an INI file), with an additional `VALUEO` output.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
