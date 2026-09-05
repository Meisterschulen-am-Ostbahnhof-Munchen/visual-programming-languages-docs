# logiBUS_IXA_BG

![logiBUS_IXA_BG_network](./logiBUS_IXA_BG_network.svg)

* * * * * * * * * *

## Einleitung

`logiBUS_IXA_BG` verbindet einen physischen digitalen Eingang (`logiBUS_IXA`) mit einer VT-Statusanzeige über die Hintergrundfarbfamilie `GreenWhiteBackground1_AX` (siehe [Background-Farbbausteine (gemeinsames Muster)](./Background-Farbbausteine.md)) — der aktuelle Zustand des Eingangs wird als grün/weißer Hintergrund auf dem VT sichtbar gemacht, ohne OPC-UA-Anbindung. Für die Variante mit zusätzlicher OPC-UA-Rückmeldung siehe [`logiBUS_IXA_BG_OPC`](./logiBUS_IXA_BG_OPC.md).

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: logiBUS_IXA_BG

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **logiBUS_IXA**: `logiBUS::io::DI::logiBUS_IXA` — physischer digitaler Eingang, Adapter-Ausgang `IN`, `QI=TRUE`.
    - **GreenWhiteBackground1_AX** (SubApp): `MyLib::sys::GreenWhiteBackground1_AX` — Ein-Objekt-Hintergrundfarbbaustein aus der Background-Farbbaustein-Familie, steuert die VT-Objekthintergrundfarbe anhand von `DI1`.
- **Funktionsweise**: Der Adapter-Ausgang des physischen Eingangs wird direkt auf den `DI1`-Adaptereingang des Hintergrundfarbbausteins geführt, der die Farbumschaltung eines VT-Objekts übernimmt.

## Programmablauf und Verbindungen

1. `Input` → `logiBUS_IXA.Input`; `u16ObjId` → `GreenWhiteBackground1_AX.u16ObjId`.
2. `logiBUS_IXA.IN` (Adapter) → `GreenWhiteBackground1_AX.DI1` (Adapter).

## Anwendungsszenarien

- Rein visuelle Statusanzeige eines physischen digitalen Eingangs auf dem VT (z. B. Endschalter-Zustand), ohne dass der Wert per OPC-UA nach außen gemeldet werden muss.

## Zusammenfassung

Kombiniert einen physischen digitalen Eingang mit der Standard-Hintergrundfarbfamilie zu einer einfachen VT-Statusanzeige.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
