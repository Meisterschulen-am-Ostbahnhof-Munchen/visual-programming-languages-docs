# Uebung_010d_PC_B_OPC

![Uebung_010d_PC_B_OPC_network](./Uebung_010d_PC_B_OPC_network.svg)

* * * * * * * * * *

## Einleitung

`Uebung_010d_PC_B_OPC` ist die Geraet-B-Seite (Station 12, 192.168.1.12) der PC-zu-PC-OPC-UA-Variante von Uebung 010d: empfaengt den Trigger-Methodenaufruf von Geraet A per `SERVER_0` (reiner RPC-Trigger, kein Wertwechsel-Trick, keine Bridge noetig), taktet die echte Toggle-Flipflop-Logik (`AX_T_FF`), schaltet `DigitalOutput_Q1` und schreibt den neuen Zustand aktiv per `AX_CLIENT_1_0` zurueck auf Geraet A. Gegenstueck: [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC.md).

## Verwendete Funktionsbausteine (FBs)

- **TRIGGER_SERVER** (`iec61499::net::SERVER_0`): empfaengt den Methodenaufruf unter `ID_TRIGGER_METHOD`.
- **AX_T_FF** (`adapter::events::unidirectional::AX_T_FF`): Toggle-Flipflop, getaktet von `TRIGGER_SERVER.IND`.
- **AX_SPLIT_2** (`adapter::events::unidirectional::AX_SPLIT_2`): verzweigt den Flipflop-Zustand auf physischen Ausgang + Rueckmeldung.
- **DigitalOutput_Q1** (`logiBUS::io::DQ::logiBUS_QXA`): physischer Ausgang (`Output` waehlt `Output_Q1..Q8`).
- **STATE_CLIENT** (`adapter::net::AX_CLIENT_1_0`): schreibt den neuen Zustand aktiv auf Geraet A unter `ID_STATE_WRITE`.

## Zusammenfassung

Geraet-B-Seite: empfaengt den Trigger per RPC, haelt die tatsaechliche Toggle-Logik und meldet den Zustand aktiv an Geraet A zurueck.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
