# Training_08_OPC_UA_RES: Toggle-Flipflop über OPC-UA — Vergleichsbasis für Training_09

![Training_08_OPC_UA_RES_network](./Training_08_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_08_OPC_UA_RES` verwendet exakt dieselben Composites wie
`Training_03_OPC_UA_RES` (`Uebung_010d_PC_A_OPC`/`Uebung_010d_PC_B_OPC`) und
dieselben OPC-UA-Adressen (`FF1_*`) — funktional identisch zu Training_03.

Der Grund für die eigenständige `.sys`-Datei: Training_08 dient als direkte
**Vergleichsbasis (manuelle Verdrahtung)** unmittelbar neben
`Training_09_OPC_UA_RES` (Adapter-Variante), analog zum Paar
Training_04/Training_06 und Training_05/Training_07. Ohne Training_08 müsste
man für den Vorher/Nachher-Vergleich der Adapter-Bündelung bei der
Toggle-only-Variante wieder auf Training_03 zurückgreifen, das an anderer
Stelle in der Serie steht.

## Verwendete Composites

Identisch zu Training_03 — siehe
[Training_03_OPC_UA_RES](../Training_03_OPC_UA_RES/Training_03_OPC_UA_RES.md)
für die vollständige Beschreibung von `Uebung_010d_PC_A_OPC` und
`Uebung_010d_PC_B_OPC`.

| Composite | Gerät |
|---|---|
| [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC_network.svg) | A (`192.168.1.11`) |
| [`Uebung_010d_PC_B_OPC`](./Uebung_010d_PC_B_OPC_network.svg) | B (`192.168.1.12`) |

## OPC-UA-Adressraum

Identisch zu Training_03 (`FF1_TRIGGER_*`, `FF1_STATE_*`) — siehe
[Training_03_OPC_UA_RES](../Training_03_OPC_UA_RES/Training_03_OPC_UA_RES.md#opc-ua-adressraum).

## Programmablauf und Verbindungen

Identisch zu Training_03 — Ablauf und Verbindungen sind dort im Detail
beschrieben.

## Technische Besonderheiten

- **Bewusste Wiederverwendung, keine neue Logik**: Training_08 führt keine
  neue Funktion ein. Es stellt sicher, dass die "Vorher"-Seite des
  Toggle-only-Adapter-Vergleichs (siehe `Training_09_OPC_UA_RES`) direkt
  neben ihrer "Nachher"-Seite in der Trainingsserie steht — genau wie
  Training_04/06 und Training_05/07 bereits als Paare nebeneinander stehen.

## Lernziele

- Direkter, unmittelbar benachbarter Vorher/Nachher-Vergleich (manuell vs.
  Adapter) für alle drei Aktionsmengen der Serie (Toggle-only, SR-only,
  SR+Toggle).

**Schwierigkeitsgrad**: Mittel
**Vorkenntnisse**: `Training_03_OPC_UA_RES` (identisches Muster).

## Zusammenfassung

`Training_08_OPC_UA_RES` ist funktional identisch zu Training_03 und dient
ausschließlich als unmittelbare Vergleichsbasis für die Adapter-Variante
`Training_09_OPC_UA_RES`.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
