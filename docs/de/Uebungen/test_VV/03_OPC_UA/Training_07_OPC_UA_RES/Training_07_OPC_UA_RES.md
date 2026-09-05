# Training_07_OPC_UA_RES: reines SR-Flipflop über OPC-UA — Adapter-Variante von Training_05

![Training_07_OPC_UA_RES_network](./Training_07_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_07_OPC_UA_RES` verhält sich zu `Training_05_OPC_UA_RES` genauso
wie `Training_06_OPC_UA_RES` zu `Training_04_OPC_UA_RES`: dieselbe
Set/Reset-Funktion, aber mit den kombinierten `ASR_AX`-Adapterbausteinen
statt einzeln verdrahteter `CLIENT_0`/`SERVER_0`/`AX_CLIENT_1_0`-Instanzen.
Gleiche OPC-UA-Adressen wie Training_05 (`SR2_*`).

## Verwendete Composites

| Composite | Gerät | Zweck |
|---|---|---|
| [`SoftKeySR_PC_A_OPC_Adapter`](./SoftKeySR_PC_A_OPC_Adapter_network.svg) | A (`192.168.1.11`) | HMI (2 SoftKeys + `GreenWhiteBackground`) hinter `SoftKeySR_ASR_AX`, OPC-UA-Trigger hinter `ASR_AX_CLIENT_0_SUBSCRIBE_1` — über eine bidirektionale Adapterverbindung gekoppelt |
| [`SoftKeySR_PC_B_OPC_Adapter`](./SoftKeySR_PC_B_OPC_Adapter_network.svg) | B (`192.168.1.12`) | `ASR_AX_SERVER_0_CLIENT_1_0` bündelt die 2 `SERVER_0` + `AX_CLIENT_1_0` hinter einem Adapter; `ASR_AX_AX_SPLIT` verteilt an `DigitalOutput_Q1` und `ASR_AX_SR_2` |

## OPC-UA-Adressraum

Identisch zu Training_05 (`SR2_SET_*`, `SR2_RESET_*`, `SR2_STATE_*`) —
siehe
[Training_05_OPC_UA_RES](../Training_05_OPC_UA_RES/Training_05_OPC_UA_RES.md#opc-ua-adressraum).

## Programmablauf und Verbindungen

1. **`SoftKeySR_PC_A_OPC_Adapter`** (Gerät A): `SoftKeySR_ASR_AX` bündelt
   die 2 SoftKeys + `GreenWhiteBackground` hinter einem `ASR_AX`-Plug; eine
   Adapterverbindung übergibt Set/Reset/Zustand an
   `ASR_AX_CLIENT_0_SUBSCRIBE_1` (`TRIGGER`), das die `ID_SET_CALL`/
   `ID_RESET_CALL`/`ID_STATE_READ`-Adressen trägt.
2. **`SoftKeySR_PC_B_OPC_Adapter`** (Gerät B): `TRIGGER`
   (`ASR_AX_SERVER_0_CLIENT_1_0`) trägt die 3 `ID_*`-Adressen und liefert
   das Set/Reset/Zustand-Bündel über `TRIGGER.S_R` an `SPLIT`
   (`ASR_AX_AX_SPLIT`), das es an `FLIPFLOP` (`ASR_AX_SR_2`) weiterreicht;
   `SPLIT.AX_OUT` schaltet parallel `DigitalOutput_Q1`.

## Technische Besonderheiten

- **`ASR_AX_*`-Kombis statt `ASRT_AX_*`**: Dieselbe Bündelungslogik wie in
  Training_06, aber die zweiwertige (Set/Reset) statt dreiwertige
  (Set/Reset/Toggle) Adapter-Variante — ein Pin (`S_R` statt `S_R_T`)
  weniger, sonst strukturell identisch.
- **Direkter Vergleich mit Training_05**: Gleicher Adressraum, gleiche
  Funktion, aber deutlich weniger Einzelverbindungen im Composite.

## Lernziele

- Adapter-3.0.0-Kombi-Bausteine für die reduzierte Set/Reset-ohne-Toggle-
  Variante (`ASR_AX_CLIENT_0_SUBSCRIBE_1`, `ASR_AX_SERVER_0_CLIENT_1_0`).
- Direkter Vergleich Training_05 (manuell) vs. Training_07 (Adapter) bei
  identischer Funktion.

**Schwierigkeitsgrad**: Fortgeschritten
**Vorkenntnisse**: `Training_05_OPC_UA_RES`, `Training_06_OPC_UA_RES`
(gleiches Adapter-Muster mit Toggle).

## Zusammenfassung

`Training_07_OPC_UA_RES` überträgt das Adapter-Bündelungsmuster aus
Training_06 auf die reduzierte Set/Reset-Variante aus Training_05.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
