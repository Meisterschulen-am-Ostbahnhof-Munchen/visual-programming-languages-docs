# Uebung_010e_PC_B_OPC

![Uebung_010e_PC_B_OPC_network](./Uebung_010e_PC_B_OPC_network.svg)

* * * * * * * * * *

## Einleitung

`Uebung_010e_PC_B_OPC` ist die Geraet-B-Seite (Station 12, 192.168.1.12): empfaengt Set/Reset/Toggle je per eigenem `SERVER_0`-Methodenaufruf (reiner RPC-Trigger, kein Wertwechsel-Trick, keine Bridge noetig), taktet die echte SR/Toggle-Flipflop-Logik (`AX_T_FF_SR`), schaltet `DigitalOutput_Q1` und schreibt den neuen Zustand aktiv per `AX_CLIENT_1_0` zurueck auf Geraet A. Gegenstueck: [`Uebung_010e_PC_A_OPC`](./Uebung_010e_PC_A_OPC.md).

## Verwendete Funktionsbausteine (FBs)

- **TRIGGER_SET_SERVER / TRIGGER_RESET_SERVER / TRIGGER_TOGGLE_SERVER** (`iec61499::net::SERVER_0`): empfangen je einen eigenen Methodenaufruf.
- **AX_T_FF_SR** (`adapter::events::unidirectional::AX_T_FF_SR`): kombinierte Set/Reset/Toggle-Flipflop-Logik.
- **AX_SPLIT_2** (`adapter::events::unidirectional::AX_SPLIT_2`): verzweigt den Zustand auf physischen Ausgang + Rueckmeldung.
- **DigitalOutput_Q1** (`logiBUS::io::DQ::logiBUS_QXA`): physischer Ausgang.
- **STATE_CLIENT** (`adapter::net::AX_CLIENT_1_0`): schreibt den Zustand aktiv auf Geraet A unter `ID_STATE_WRITE`.

## Zusammenfassung

Geraet-B-Seite: empfaengt Set/Reset/Toggle per RPC, haelt die kombinierte SR/Toggle-Flipflop-Logik und meldet den Zustand aktiv zurueck.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
