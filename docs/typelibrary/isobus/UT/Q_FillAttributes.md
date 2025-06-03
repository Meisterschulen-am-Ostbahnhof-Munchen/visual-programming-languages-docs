# Q_FillAttributes

![Q_FillAttributes](https://user-images.githubusercontent.com/116869307/214147532-6ef11045-1dcb-4c4d-bdf3-84d87ed73257.png)

* * * * * * * * * *

## Einleitung
Der **Q_FillAttributes** ist ein standardkonformer Funktionsbaustein zur Änderung von Füllattributen in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.32) Spezifikation für VT-Systeme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Attributänderungs-Anforderung (mit neuen Füllattributen)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung (mit Status und alten Attributen)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Objekt-ID (16-bit)
- `u8FillType` (USINT): Neuer Fülltyp
- `u8FillColour` (USINT): Neue Füllfarbe
- `u16FillPatternId` (UINT): Neues Füllmuster

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldFillType` (USINT): Alter Fülltyp
- `u8OldFillColour` (USINT): Alte Füllfarbe
- `u16OldFillPatternId` (UINT): Altes Füllmuster
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Attributänderung**:
   - `REQ` mit neuen Füllattributen
   - Ändert Fülleigenschaften des Objekts
   - `CNF` liefert Ergebnisstatus und vorherige Werte

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.32)  
✔ **Umfassende Attributsteuerung** (Typ, Farbe, Muster)  
✔ **Rückmeldung alter Werte** für Reversionsmöglichkeit  
✔ **Transaktionssicher** (Atomare Ausführung)  

## Attribut-Eigenschaften

| Feature        | Beschreibung                     |
|---------------|----------------------------------|
| Fülltypen     | Nach ISO 11783-6 B.14.4          |
| Farbpalette   | 8-bit Farbindex                  |
| Muster        | 16-bit Musterreferenzen          |
| Objektbereich | Alle füllfähigen VT-Objekte      |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Änderung             |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Designanpassungen**: Dynamische Oberflächengestaltung
- **Statusvisualisierung**: Farbliche Hervorhebungen
- **Musterwechsel**: Kontextsensitive Darstellungen
- **Themenwechsel**: Dunkel-/Hellmodus Umschaltung

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_FillAttributes | VtSetColor | VtPatternManager |
|---------------|------------------|------------|------------------|
| ISO-Standard  | ✔                | ✖          | ✖                |
| Farbsteuerung | ✔                | ✔          | ✖                |
| Mustersteuerung | ✔              | ✖          | ✔                |
| Typsteuerung  | ✔                | ✖          | ✖                |

## Fazit

Der Q_FillAttributes-Baustein bietet die Standardimplementierung für Füllattributänderungen:

- **Vielseitig**: Komplette Kontrolle über Fülleigenschaften
- **Rückverfolgbar**: Rückmeldung vorheriger Werte
- **Robust**: ISO-konforme Fehlerbehandlung

Unverzichtbar für:
- Dynamische Benutzeroberflächen
- Zustandsabhängige Visualisierungen
- Designflexible VT-Anwendungen
