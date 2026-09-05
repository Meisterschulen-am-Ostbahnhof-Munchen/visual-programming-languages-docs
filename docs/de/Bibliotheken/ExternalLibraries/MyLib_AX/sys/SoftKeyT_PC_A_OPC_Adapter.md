# SoftKeyT_PC_A_OPC_Adapter

![SoftKeyT_PC_A_OPC_Adapter_network](./SoftKeyT_PC_A_OPC_Adapter_network.svg)

* * * * * * * * * *

## Einleitung

`SoftKeyT_PC_A_OPC_Adapter` ist die adapter-gebuendelte Variante von [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC.md) (Geraet A, Station 11): HMI (SoftKey + `GreenWhiteBackground`) und OPC-UA-Trigger sind getrennt. [`SoftKeyT_AE_AX`](./SoftKeyT_AE_AX.md) buendelt die HMI hinter einem `AE_AX`-Plug; `AE_AX_CLIENT_0_SUBSCRIBE_1` buendelt `CLIENT_0` + `AX_SUBSCRIBE_1` hinter einem `AE_AX`-Socket. "SUB style": das Protokoll steckt weiterhin im `MyLib::sys`-Composite. Gegenstueck: [`SoftKeyT_PC_B_OPC_Adapter`](./SoftKeyT_PC_B_OPC_Adapter.md).

## Verwendete Funktionsbausteine (FBs)

- **SoftKeyT_AE_AX** (SubApp, Typ `MyLib::sys::SoftKeyT_AE_AX`): SoftKey + Statusanzeige, gebuendelt hinter einem `AE_AX`-Plug.
- **TRIGGER** (`adapter::net::AE_AX_CLIENT_0_SUBSCRIBE_1`): buendelt Methodenaufruf (`ID_TRIGGER_CALL`) und Zustands-Abo (`ID_STATE_READ`) hinter einem einzigen `AE_AX`-Socket.

## Programmablauf und Verbindungen

`SoftKeyT_AE_AX.OUT` -> `TRIGGER.TRIGGER` (bidirektional: Trigger raus, Zustand zurueck an die HMI-SubApp).

## Zusammenfassung

Adapter-gebuendelte Variante von `Uebung_010d_PC_A_OPC`: dieselbe Funktion, aber HMI und Netzwerkprotokoll sind sauber in 2 wiederverwendbare Bausteine getrennt statt in einem einzigen Composite verdrahtet.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
