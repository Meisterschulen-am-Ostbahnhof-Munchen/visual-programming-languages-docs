# Q_NumericValueAux

* * * * * * * * * *

## Einleitung

Der **Q_NumericValueAux** ist ein standardkonformer Funktionsbaustein zur numerischen Wertänderung in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.22) Spezifikation für numerische VT-Objekte.

![Q_NumericValueAux](Q_NumericValueAux.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Wertänderungs-Anforderung

### **Ereignis-Ausgänge**

- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung

### **Daten-Eingänge**

- `u16ObjId` (UINT): Objekt-ID (16-bit)
- `u32NewValue` (UDINT): Neuer numerischer Wert (32-bit unsigned)

### **Daten-Ausgänge**

- `STATUS` (STRING): Betriebsstatusmeldung
- `u32OldValue` (UDINT): Vorheriger numerischer Wert
- `s16result` (INT): ISO-konformer Ergebniscode

## Gültige Objekt-IDs

**`u16ObjId` — gültige Objekttypen (Annex F.22, Objekte mit numerischem Wert-Attribut):**
Input Boolean Field (7000–7999), Input Number Field (9000–9999), Input List Field (10000–10999), Output Number Field (12000–12999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Number Variable (21000–21999), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999).

ID_NULL (65535) ist kein Befehlsziel, deaktiviert den Baustein aber bei Verwendung mit `INIT`. Jede ID außerhalb dieser Bereiche ist zum Befehlen ungültig.

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Zielobjekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Wertaktualisierung**:
   - `REQ` mit neuem 32-Bit-Wert
   - Aktualisiert das numerische VT-Objekt
   - `CNF` liefert Betriebsstatus und vorherigen Wert

3. **Wertbereich**:
   - 0 bis 4.294.967.295 (32-bit unsigned)

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.22)
✔ **32-Bit-Wertebereich** (UDINT)
✔ **Sofortige Aktualisierung**
✔ **Rückverfolgbarkeit** (Vorheriger Wert)

## Wertebereich

| Parameter    | Typ       | Wertebereich          |
|-------------|-----------|-----------------------|
| u32NewValue | UDINT     | 0 bis 4.294.967.295   |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Änderung             |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Objekt-ID               |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Messwertanzeigen**: Echtzeit-Datenvisualisierung
- **Zählerstände**: Kilometerzähler, Produktionszähler
- **Prozesssteuerung**: Sollwertvorgaben
- **Diagnosesysteme**: Fehlercode-Anzeige

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_NumericValueAux | VtNumericUpdate | VtValueManager |
|---------------|--------------------|-----------------|----------------|
| ISO-Standard  | ✔                  | ✖               | ✖              |
| Wertebereich  | 32-bit             | 16-bit          | 32-bit         |
| Rückmeldung   | ✔                  | ✖               | ✔              |
| Objekttyp     | Numerische Objekte | Alle            | Alle           |

## Fazit

Der Q_NumericValueAux-Baustein bietet präzise numerische Steuerung:

- **Hochauflösend**: 32-Bit-Wertebereich
- **Zuverlässig**: Integrierte Fehlererkennung
- **Flexibel**: Für alle numerischen Objekte

Unverzichtbar für:

- Präzise Messwertdarstellungen
- Hochauflösende Steuerungen
- Professionelle Prozessvisualisierung
