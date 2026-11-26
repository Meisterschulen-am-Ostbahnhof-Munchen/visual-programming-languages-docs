# ETP reception in LOGIBUS

!!! warning "State: not pushed, not tested"
    This state is committed in the firmware (LOGIBUS `24534469` "ETP-Empfang mit PSRAM-Puffer aktivieren", forte `8d02d14f7` "AlPgnRxNew_TP: ETP-Empfang bis 65535 Byte"), but **not pushed and not tested on hardware yet**. The statements come from the firmware development, I have not checked the commits myself. There are no hardware results yet, testing is done with the ETP exercises in the training project.

The Extended Transport Protocol (ETP) transfers messages of more than 1785 bytes. LOGIBUS can send ETP and, with this state, also receive it.

## What changes

- **Before:** LOGIBUS could not receive ETP. The default TP filter of the CCI driver discarded every ETP, and `iso_BaseInit` got no memory for ETP. Sending via ETP already worked.
- **New:** LOGIBUS sets its own TP filter (`iso_CoreInit`, `CoreTask.cpp`). It accepts TP and ETP up to `LOGIBUS_ETP_IN_SIZE_MAX` = 128 KiB (`IsoConf.h`). The stack aborts larger ETPs with "System resources".
- **Receive buffer:** It comes from PSRAM (ETP memory callback in `BaseTask.cpp`, `heap_caps_malloc` with `MALLOC_CAP_SPIRAM`). The stack releases it after the data has been distributed, also after an abort.
- **Configuration:** The deprecated route via `ISO_ETP_IN` is not used. From driver V12 on, an own filter plus callback is the intended way.

## In FORTE

- [`AlPgnRxNew_TP`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/en/latest/Bibliotheken/ExternalLibraries/isobus/pgn/rx/AlPgnRxNew_TP/) accepts up to 65535 bytes (before 1785), `u16DaSize` is valid from 0 to 65535. `OVERFLOW` indicates that `Data` was too small.
- [`AlPgnTxNew_TP`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/en/latest/Bibliotheken/ExternalLibraries/isobus/pgn/tx/AlPgnTxNew_TP/) sends automatically via ETP when `u16DaSize` is above 1785, up to 65535 bytes.
- [`DlPgnSend`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/en/latest/Bibliotheken/ExternalLibraries/isobus/pgn/tx/DlPgnSend/) stays at 1785 bytes.

## Restrictions

- ETP only exists addressed (destination specific), a broadcast is not possible.
- PGNs from `0x1F000` to `0x1FFFF` with more than 8 bytes go as [NMEA Fast Packet](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/isobus-other-docs/en/latest/NMEA2000-Fast-Packet/) (at most 223 bytes), not as ETP. For ETP use Proprietary A2 (`0x1EF00`) or Proprietary A (`0xEF00`).
