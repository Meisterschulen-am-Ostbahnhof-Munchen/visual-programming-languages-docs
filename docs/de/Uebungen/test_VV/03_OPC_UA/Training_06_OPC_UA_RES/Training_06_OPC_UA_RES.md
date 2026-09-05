# Training_06_OPC_UA_RES: SR+Toggle über OPC-UA — Adapter-Variante von Training_04

![Training_06_OPC_UA_RES_network](./Training_06_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_06_OPC_UA_RES` ist die **Adapter-Variante** von
`Training_04_OPC_UA_RES` — dieselbe Funktion (3 SoftKeys, SR+Toggle-
Flipflop, OPC-UA-Rückschreiben), aber statt einzelner `CLIENT_0`/`SERVER_0`/
`AX_CLIENT_1_0`-Instanzen mit manueller Datenverdrahtung kommen die
kombinierten Adapter-Bausteine aus der `adapter-3.0.0`-Bibliothek zum
Einsatz (siehe die adapter-3.0.0-FB-Familie, dokumentiert unter
[`Bibliotheken/ExternalLibraries/adapter`](../../../../Bibliotheken/ExternalLibraries/adapter/index.md)).
Gleiche OPC-UA-Adressen wie Training_04 (`SR1_*`).

## Verwendete Composites

| Composite | Gerät | Zweck |
|---|---|---|
| [`Uebung_010e_PC_A_OPC_Adapter`](./Uebung_010e_PC_A_OPC_Adapter_network.svg) | A (`192.168.1.11`) | HMI (3 SoftKeys + `GreenWhiteBackground`) hinter `SoftKeySRT_ASRT_AX`, OPC-UA-Trigger hinter `ASRT_AX_CLIENT_0_SUBSCRIBE_1` — beide über **eine** bidirektionale Adapterverbindung gekoppelt |
| [`Uebung_010e_PC_B_OPC_Adapter`](./Uebung_010e_PC_B_OPC_Adapter_network.svg) | B (`192.168.1.12`) | `ASRT_AX_SERVER_0_CLIENT_1_0` bündelt die 3 `SERVER_0` + `AX_CLIENT_1_0` hinter einem Adapter; `ASRT_AX_AX_SPLIT` verteilt an `DigitalOutput_Q1` und `ASRT_AX_T_FF_SR_2` |

## OPC-UA-Adressraum

Identisch zu Training_04 (`SR1_SET_*`, `SR1_RESET_*`, `SR1_TOGGLE_*`,
`SR1_STATE_*`) — siehe
[Training_04_OPC_UA_RES](../Training_04_OPC_UA_RES/Training_04_OPC_UA_RES.md#opc-ua-adressraum).
Nur die Verdrahtung im Composite ändert sich, nicht der Adressraum.

## Programmablauf und Verbindungen

1. **`Uebung_010e_PC_A_OPC_Adapter`** (Gerät A): `SoftKeySRT_ASRT_AX`
   bündelt die 3 SoftKeys + `GreenWhiteBackground` hinter einem
   `ASRT_AX`-Plug; eine einzige Adapterverbindung
   (`SoftKeySRT_ASRT_AX.OUT` → `TRIGGER.S_R_T`) übergibt Set/Reset/Toggle/
   Zustand an `ASRT_AX_CLIENT_0_SUBSCRIBE_1` (`TRIGGER`), das die 3
   `ID_*_CALL`- und `ID_STATE_READ`-Adressen als Datenpins trägt.
2. **`Uebung_010e_PC_B_OPC_Adapter`** (Gerät B): `TRIGGER`
   (`ASRT_AX_SERVER_0_CLIENT_1_0`) trägt die 4 `ID_*`-Adressen als
   Datenpins und liefert das gebündelte Set/Reset/Toggle/Zustand-Signal
   über `TRIGGER.S_R_T` an `SPLIT` (`ASRT_AX_AX_SPLIT`), das es an
   `FLIPFLOP` (`ASRT_AX_T_FF_SR_2`) weiterreicht; `SPLIT.AX_OUT` schaltet
   parallel `DigitalOutput_Q1`.

## Technische Besonderheiten

- **Ein Adapter statt vier Einzelbausteine**: `ASRT_AX_SERVER_0_CLIENT_1_0`
  bündelt 3× `SERVER_0` + 1× `AX_CLIENT_1_0` hinter einem einzigen
  bidirektionalen Adapter-Anschluss — die vier `ID_*`-Adresspins bleiben
  als Datenpins direkt am Composite-Interface sichtbar (siehe
  [PR #158](https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/visual-programming-languages-docs/pull/158)
  für die vollständige adapter-3.0.0-FB-Dokumentation dieser Kombi-Typen).
- **Durchgängige Adapterkette statt Event/BOOL-Wechsel**: Anders als in
  Training_04 (`AX_T_FF_SR` mit separaten `S`/`R`/`CLK`-Eventpins und
  BOOL-`Q`) läuft hier das gesamte Set/Reset/Toggle/Zustand-Bündel als
  **eine** Adapterverbindung durch `TRIGGER` → `SPLIT` → `FLIPFLOP` — die
  eigentliche Flipflop-Logik (`ASRT_AX_T_FF_SR_2`) ist selbst
  adapterbasiert, nicht mehr auf Einzel-Events verdrahtet.
- **Weniger Verdrahtungsaufwand, gleiche Semantik**: Funktional identisch zu
  Training_04, aber deutlich weniger Verbindungen im Composite — der Preis
  ist, dass die einzelnen Aktionen (Set/Reset/Toggle) nicht mehr als
  separate Pins im Netzplan sichtbar sind, sondern im Adapterbündel
  verschwinden (nur noch an den `ID_*`-Datenpins ablesbar).

## Lernziele

- Adapter-3.0.0-Kombi-Bausteine (`ASRT_AX_CLIENT_0_SUBSCRIBE_1`,
  `ASRT_AX_SERVER_0_CLIENT_1_0`) als Ersatz für mehrere einzeln verdrahtete
  Netzwerk-FBs.
- Durchgängige bidirektionale Adapterketten (`ASRT_AX_AX_SPLIT`,
  `ASRT_AX_T_FF_SR_2`) statt Einzel-Event-/BOOL-Verdrahtung.
- Direkter Vergleich Training_04 (manuell) vs. Training_06 (Adapter) bei
  identischer Funktion und identischem OPC-UA-Adressraum.

**Schwierigkeitsgrad**: Fortgeschritten
**Vorkenntnisse**: `Training_04_OPC_UA_RES`, adapter-3.0.0-FB-Familie
(`Bibliotheken/ExternalLibraries/adapter`).

## Zusammenfassung

`Training_06_OPC_UA_RES` zeigt dieselbe SR+Toggle-über-OPC-UA-Funktion wie
Training_04, jetzt mit den kombinierten adapter-3.0.0-Bausteinen
(`ASRT_AX_CLIENT_0_SUBSCRIBE_1`, `ASRT_AX_SERVER_0_CLIENT_1_0`) statt
manuell verdrahteter Einzel-FBs — weniger Verbindungen, gleicher
Adressraum, gleiches Verhalten.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
