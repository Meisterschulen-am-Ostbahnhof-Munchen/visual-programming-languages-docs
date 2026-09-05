# Training_09_OPC_UA_RES: Toggle-Flipflop über OPC-UA — Adapter-Variante von Training_08

![Training_09_OPC_UA_RES_network](./Training_09_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_09_OPC_UA_RES` ist die Adapter-Variante von
`Training_08_OPC_UA_RES` (und damit auch von `Training_03_OPC_UA_RES`) —
komplettiert die Serie der drei Vorher/Nachher-Adapter-Paare:

| Aktionsmenge | Manuell | Adapter |
|---|---|---|
| Toggle-only | Training_03 / **Training_08** | **Training_09** |
| Set/Reset | Training_05 | Training_07 |
| Set/Reset/Toggle | Training_04 | Training_06 |

Statt der `ASRT_AX_*`/`ASR_AX_*`-Kombis aus Training_06/07 kommen hier die
**einwertigen** `AE_AX_*`-Adapterbausteine zum Einsatz (`AE` = Adapter-
Event, ein einzelner Trigger ohne Set/Reset-Unterscheidung). Gleiche
OPC-UA-Adressen wie Training_03/08 (`FF1_*`).

## Verwendete Composites

| Composite | Gerät | Zweck |
|---|---|---|
| [`SoftKeyT_PC_A_OPC_Adapter`](./SoftKeyT_PC_A_OPC_Adapter_network.svg) | A (`192.168.1.11`) | HMI (SoftKey + `GreenWhiteBackground`) hinter `SoftKeyT_AE_AX`, OPC-UA-Trigger hinter `AE_AX_CLIENT_0_SUBSCRIBE_1` |
| [`SoftKeyT_PC_B_OPC_Adapter`](./SoftKeyT_PC_B_OPC_Adapter_network.svg) | B (`192.168.1.12`) | `AE_AX_SERVER_0_CLIENT_1_0` bündelt `SERVER_0` + `AX_CLIENT_1_0`; `AE_AX_AX_SPLIT` verteilt an `DigitalOutput_Q1` und `AE_AX_T_FF` |

## OPC-UA-Adressraum

Identisch zu Training_03/08 (`FF1_TRIGGER_*`, `FF1_STATE_*`) — siehe
[Training_03_OPC_UA_RES](../Training_03_OPC_UA_RES/Training_03_OPC_UA_RES.md#opc-ua-adressraum).

## Programmablauf und Verbindungen

1. **`SoftKeyT_PC_A_OPC_Adapter`** (Gerät A): `SoftKeyT_AE_AX` bündelt
   SoftKey + `GreenWhiteBackground` hinter einem `AE_AX`-Plug; eine
   Adapterverbindung (`SoftKeyT_AE_AX.OUT` → `TRIGGER.TRIGGER`) übergibt
   Trigger/Zustand an `AE_AX_CLIENT_0_SUBSCRIBE_1` (`TRIGGER`).
2. **`SoftKeyT_PC_B_OPC_Adapter`** (Gerät B): `TRIGGER`
   (`AE_AX_SERVER_0_CLIENT_1_0`) liefert das Trigger/Zustand-Bündel über
   `TRIGGER.TRIGGER` an `SPLIT` (`AE_AX_AX_SPLIT`), das an
   `FLIPFLOP.CLK` (`AE_AX_T_FF`) weiterreicht; `SPLIT.AX_OUT` schaltet
   parallel `DigitalOutput_Q1`.

## Technische Besonderheiten

- **`AE_AX_*` als einwertige Basis-Kombi**: Die einfachste der drei
  Kombi-Familien in dieser Serie — ein einzelner `TRIGGER`-Pin statt
  `S_R` (Training_07) oder `S_R_T` (Training_06), da ein reiner
  Toggle-Trigger keine Aktionsunterscheidung braucht.
- **Vollständiger Adapter-Baukasten sichtbar**: Zusammen mit Training_06/07
  zeigt Training_09 alle drei Stufen der adapter-3.0.0-Kombi-Familie
  (`AE_AX_*`/`ASR_AX_*`/`ASRT_AX_*`) im direkten Funktionsvergleich zu
  ihren manuell verdrahteten Gegenstücken.

## Lernziele

- Einwertige Adapter-Kombi-Bausteine (`AE_AX_CLIENT_0_SUBSCRIBE_1`,
  `AE_AX_SERVER_0_CLIENT_1_0`) als einfachste Stufe der Serie.
- Vollständiger Überblick: alle drei Adapter-Kombi-Stufen (`AE`/`ASR`/
  `ASRT`) im Vergleich zu ihren manuellen Gegenstücken.

**Schwierigkeitsgrad**: Fortgeschritten
**Vorkenntnisse**: `Training_08_OPC_UA_RES`, `Training_06_OPC_UA_RES`/
`Training_07_OPC_UA_RES` (gleiches Adapter-Muster, andere Aktionsmengen).

## Zusammenfassung

`Training_09_OPC_UA_RES` schließt die Serie ab: die einwertige
`AE_AX_*`-Adapter-Variante des Toggle-only-Musters, funktional identisch zu
Training_03/08, mit derselben Bündelungslogik wie Training_06/07.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
