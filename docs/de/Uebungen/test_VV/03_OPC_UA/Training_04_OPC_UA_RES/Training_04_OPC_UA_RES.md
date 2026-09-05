# Training_04_OPC_UA_RES: SR+Toggle-Flipflop über 3 OPC-UA-Methoden ("SUB style", Option A)

![Training_04_OPC_UA_RES_network](./Training_04_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_04_OPC_UA_RES` überträgt `Uebung_010e_AX` (SR+Toggle-Flipflop über
3 SoftKeys, siehe
[`Uebung_010e_AX.md`](../../../test_AX/Uebungen_doc/Uebung_010e_AX.md)) nach
demselben "SUB style"-Muster wie `Training_03_OPC_UA_RES` auf zwei Geräte.
Set, Reset und Toggle sind drei **eigenständige** OPC-UA-Methoden
(**Option A**) — Gerät A ruft je nach gedrücktem SoftKey eine von drei
`CLIENT_0`-Instanzen auf, statt eine einzelne Methode mit einem
String-Parameter zu übergeben.

## Verwendete Composites

| Composite | Gerät | Zweck |
|---|---|---|
| [`Uebung_010e_PC_A_OPC`](./Uebung_010e_PC_A_OPC_network.svg) | A (`192.168.1.11`) | 3 SoftKeys (Set/Reset/Toggle) rufen je einen eigenen `CLIENT_0`-Methodenaufruf auf Gerät B auf; `GreenWhiteBackground` am Toggle-SoftKey zeigt den überwachten Zustand |
| [`Uebung_010e_PC_B_OPC`](./Uebung_010e_PC_B_OPC_network.svg) | B (`192.168.1.12`) | 3 `SERVER_0`-Instanzen empfangen Set/Reset/Toggle, treiben `AX_T_FF_SR`, schalten `Output_Q1` und schreiben den Zustand per `AX_CLIENT_1_0` zurück |

## OPC-UA-Adressraum

Drei unabhängige Methoden-Adresspaare plus ein Zustands-Adresspaar, alle in
`VV::const::OPC_UA::myOpcUaAddresses`:

| Konstante (lokal/remote) | Wert (Auszug) | Zweck |
|---|---|---|
| `SR1_SET_LOCAL_METHOD` / `SR1_SET_REMOTE_CALL` | `.../SRFlipflop/SR1_Set` | Set-Methode |
| `SR1_RESET_LOCAL_METHOD` / `SR1_RESET_REMOTE_CALL` | `.../SRFlipflop/SR1_Reset` | Reset-Methode |
| `SR1_TOGGLE_LOCAL_METHOD` / `SR1_TOGGLE_REMOTE_CALL` | `.../SRFlipflop/SR1_Toggle` | Toggle-Methode |
| `SR1_STATE_LOCAL_READ` / `SR1_STATE_REMOTE_WRITE` | `.../SRFlipflop/SR1_State` | Zustands-Rückkanal (`READ`/`WRITE`, wie in Training_03) |

Jede der drei Methoden hat einen eigenen, unabhängigen `CLIENT_0`/`SERVER_0`-
Adresspfad (`SR1_Set`, `SR1_Reset`, `SR1_Toggle`) — keine gemeinsam genutzte
Methode mit Parameter.

## Programmablauf und Verbindungen

1. **`Uebung_010e_PC_A_OPC`** (Gerät A): `SoftKey_SET.IND` →
   `TRIGGER_SET_CLIENT.REQ`, `SoftKey_RESET.IND` →
   `TRIGGER_RESET_CLIENT.REQ`, `SoftKey_TOGGLE.IND` →
   `TRIGGER_TOGGLE_CLIENT.REQ` — drei unabhängige `CLIENT_0`-Aufrufe, je
   einer pro SoftKey. `STATE_SUBSCRIBE` speist wie in Training_03
   `GreenWhiteBackground_AX.DI1` am Toggle-SoftKey.
2. **`Uebung_010e_PC_B_OPC`** (Gerät B): drei `SERVER_0`-Instanzen
   (`TRIGGER_SET_SERVER`, `TRIGGER_RESET_SERVER`, `TRIGGER_TOGGLE_SERVER`)
   takten je den passenden Eingang von `AX_T_FF_SR` (`S`/`R`/`CLK`); der neue Zustand
   geht wie in Training_03 über `AX_SPLIT_2` an `Output_Q1` und
   `STATE_CLIENT` (Rückschreiben nach Gerät A).

## Technische Besonderheiten

- **Option A: eigene Methode pro Aktion** — statt einer gemeinsamen
  Methode mit einem Parameter (der signalisieren würde "welche Aktion")
  bekommt jede Aktion ihren eigenen `CLIENT_0`/`SERVER_0`-Adresspfad. Das
  ist einfacher zu verdrahten (keine Parameterauswertung nötig), verbraucht
  aber drei statt einer Server-Instanz.
- **Set/Reset/Toggle auf einem Flipflop**: `AX_T_FF_SR` ist die
  SR+Toggle-fähige Variante von `AX_T_FF` (siehe `Uebung_010e_AX.md` für
  die lokale ECC-Logik).

## Lernziele

- Mehrere unabhängige OPC-UA-Methoden auf demselben Gerät, je mit eigenem
  Adresspfad statt gemeinsamem Parameter.
- SR+Toggle-Flipflop-Logik (`AX_T_FF_SR`) ferngesteuert über drei getrennte
  RPC-Kanäle.

**Schwierigkeitsgrad**: Mittel bis fortgeschritten
**Vorkenntnisse**: `Uebung_010e_AX.SUB`, `Training_03_OPC_UA_RES` (RPC-Muster,
"SUB style").

## Zusammenfassung

`Training_04_OPC_UA_RES` erweitert das RPC-Muster aus Training_03 auf drei
unabhängige Aktionen (Set/Reset/Toggle), jede mit eigenem OPC-UA-Methoden-
Adresspfad ("Option A") statt eines parametrisierten Einzelaufrufs.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
