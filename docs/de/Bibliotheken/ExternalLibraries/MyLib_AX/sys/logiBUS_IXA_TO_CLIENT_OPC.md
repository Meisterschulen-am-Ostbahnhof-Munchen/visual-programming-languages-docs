# logiBUS_IXA_TO_CLIENT_OPC

![logiBUS_IXA_TO_CLIENT_OPC_network](./logiBUS_IXA_TO_CLIENT_OPC_network.svg)

* * * * * * * * * *

## Einleitung

`logiBUS_IXA_TO_CLIENT_OPC` liest einen digitalen Eingang (`logiBUS_IXA`) und schreibt den Wert aktiv per `AX_CLIENT_1_0` auf ein ANDERES Geraet via OPC-UA - "Krauternter-Stil" (laut Quellcode-Kommentar): das Protokoll (`AX_CLIENT_1_0`) steckt IM Baustein selbst, nicht in der Resource des Geraets, im Gegensatz zum "SUB style" der PC_A/PC_B-Bausteine, wo Trigger/Server-Instanzen extra im Composite verkabelt sind.

## Verwendete Funktionsbausteine (FBs)

- **logiBUS_IXA** (`logiBUS::io::DI::logiBUS_IXA`): physischer digitaler Eingang, identifiziert ueber `Input_I1..I8`.
- **AX_CLIENT_1_0** (`adapter::net::AX_CLIENT_1_0`): schreibt den Adapterwert aktiv auf die Remote-Zieladresse `ID` (inkl. `opc.tcp://`-Endpoint des Zielgeraets).

## Zusammenfassung

Ein-Baustein-Bruecke von einem physischen digitalen Eingang zu einem aktiven Remote-Write auf ein anderes Geraet - Gegenstueck zu [`logiBUS_QXA_FROM_SUBSCRIBE_OPC`](./logiBUS_QXA_FROM_SUBSCRIBE_OPC.md) auf der Empfaengerseite.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
