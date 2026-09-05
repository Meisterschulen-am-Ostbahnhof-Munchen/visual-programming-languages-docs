# Uebung_010e_PC_B_OPC_Adapter

![Uebung_010e_PC_B_OPC_Adapter_network](./Uebung_010e_PC_B_OPC_Adapter_network.svg)

* * * * * * * * * *

## Einleitung

`Uebung_010e_PC_B_OPC_Adapter` ist die adapter-gebuendelte Variante von [`Uebung_010e_PC_B_OPC`](./Uebung_010e_PC_B_OPC.md) (Geraet B, Station 12): die 3 `SERVER_0`-Instanzen + `AX_CLIENT_1_0` sind hinter EINEM `ASRT_AX_SERVER_0_CLIENT_1_0`-Baustein hinter einem einzigen bidirektionalen Adapter-Anschluss gebuendelt; `ASRT_AX_AX_SPLIT` speist sowohl `DigitalOutput_Q1` als auch die SR/Toggle-Flipflop-Logik (`ASRT_AX_T_FF_SR_2`). Gegenstueck: [`Uebung_010e_PC_A_OPC_Adapter`](./Uebung_010e_PC_A_OPC_Adapter.md).

## Verwendete Funktionsbausteine (FBs)

- **TRIGGER** (`adapter::net::ASRT_AX_SERVER_0_CLIENT_1_0`): buendelt Server-Empfang (`ID_SET_METHOD`/`ID_RESET_METHOD`/`ID_TOGGLE_METHOD`) und Zustands-Rueckmeldung (`ID_STATE_WRITE`).
- **SPLIT** (`adapter::events::bidirectional::ASRT_AX_AX_SPLIT`): verzweigt auf physischen Ausgang + Flipflop-Logik.
- **FLIPFLOP** (`adapter::events::bidirectional::ASRT_AX_T_FF_SR_2`): kombinierte SR/Toggle-Flipflop-Logik als Adapter-Baustein.
- **DigitalOutput_Q1** (`logiBUS::io::DQ::logiBUS_QXA`): physischer Ausgang.

## Zusammenfassung

Adapter-gebuendelte Variante von `Uebung_010e_PC_B_OPC`: Netzwerkprotokoll und SR/Toggle-Flipflop-Logik als wiederverwendbare Adapter-Bausteine.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
