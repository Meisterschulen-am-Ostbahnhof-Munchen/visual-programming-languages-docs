# Training_05_OPC_UA_RES: reines SR-Flipflop über 2 OPC-UA-Methoden ("SUB style")

![Training_05_OPC_UA_RES_network](./Training_05_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_05_OPC_UA_RES` ist die Set/Reset-**ohne**-Toggle-Variante von
`Training_04_OPC_UA_RES`: 2 SoftKeys (Set, Reset) statt 3, ein reines
`AX_SR`-Flipflop statt `AX_T_FF_SR`. Gleiches "SUB style"-Muster, gleiche
Option-A-Methodenaufteilung (eigene Methode pro Aktion), aber ohne die
Toggle-Aktion und ohne den dritten SoftKey/Server.

## Verwendete Composites

| Composite | Gerät | Zweck |
|---|---|---|
| [`SoftKeySR_PC_A_OPC`](./SoftKeySR_PC_A_OPC_network.svg) | A (`192.168.1.11`) | 2 SoftKeys (Set/Reset) rufen je einen eigenen `CLIENT_0`-Methodenaufruf auf Gerät B auf; `GreenWhiteBackground` am Set-SoftKey zeigt den überwachten Zustand |
| [`SoftKeySR_PC_B_OPC`](./SoftKeySR_PC_B_OPC_network.svg) | B (`192.168.1.12`) | 2 `SERVER_0`-Instanzen empfangen Set/Reset, treiben `AX_SR`, schalten `Output_Q1` und schreiben den Zustand per `AX_CLIENT_1_0` zurück |

## OPC-UA-Adressraum

| Konstante (lokal/remote) | Wert (Auszug) | Zweck |
|---|---|---|
| `SR2_SET_LOCAL_METHOD` / `SR2_SET_REMOTE_CALL` | `.../SRFlipflop/SR2_Set` | Set-Methode |
| `SR2_RESET_LOCAL_METHOD` / `SR2_RESET_REMOTE_CALL` | `.../SRFlipflop/SR2_Reset` | Reset-Methode |
| `SR2_STATE_LOCAL_READ` / `SR2_STATE_REMOTE_WRITE` | `.../SRFlipflop/SR2_State` | Zustands-Rückkanal |

Eigener Adress-Namensraum (`SR2_*`) getrennt von `SR1_*` aus Training_04 —
beide Übungen können unverändert gleichzeitig auf denselben zwei Geräten
laufen, ohne OPC-UA-Adresskollision.

## Programmablauf und Verbindungen

1. **`SoftKeySR_PC_A_OPC`** (Gerät A): `SoftKey_SET.IND` →
   `TRIGGER_SET_CLIENT.REQ`, `SoftKey_RESET.IND` →
   `TRIGGER_RESET_CLIENT.REQ` — zwei unabhängige `CLIENT_0`-Aufrufe.
   `STATE_SUBSCRIBE` speist `GreenWhiteBackground_AX.DI1` am Set-SoftKey.
2. **`SoftKeySR_PC_B_OPC`** (Gerät B): `TRIGGER_SET_SERVER.IND` →
   `AX_SR.S`, `TRIGGER_RESET_SERVER.IND` → `AX_SR.R`; der neue Zustand
   geht wie in Training_04 über `AX_SPLIT_2` an `Output_Q1` und
   `STATE_CLIENT` (Rückschreiben nach Gerät A).

## Technische Besonderheiten

- **Reduzierte Aktionsmenge**: `AX_SR` hat nur `S`/`R`/`Q` — kein `CLK` für
  Toggle. Wer nur Set/Reset braucht, spart sich Composite-Komplexität und
  eine dritte Methode/Server-Instanz gegenüber Training_04.
- **Gleiches Grundmuster wie Training_04**: Bis auf die fehlende
  Toggle-Aktion sind Verdrahtung, Rückschreibe-Mechanismus und
  Adressstruktur identisch — eine gute Vorlage, um Option A auf beliebig
  viele/wenige unabhängige Aktionen zu skalieren.

## Lernziele

- Reines SR-Flipflop (`AX_SR`) ferngesteuert über zwei getrennte
  OPC-UA-Methoden, als reduzierte Variante von Training_04.
- Eigenständiger OPC-UA-Adress-Namensraum pro Übung, um Kollisionen bei
  gleichzeitigem Betrieb mehrerer Trainings-Systeme zu vermeiden.

**Schwierigkeitsgrad**: Mittel
**Vorkenntnisse**: `Training_04_OPC_UA_RES` (gleiches Muster mit Toggle).

## Zusammenfassung

`Training_05_OPC_UA_RES` reduziert Training_04 auf reines Set/Reset ohne
Toggle — gleiches "SUB style"/Option-A-Muster, zwei statt drei OPC-UA-
Methoden, eigener Adress-Namensraum.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
