# Q_EndPoint

```{index} single: Q_EndPoint
```

![Q_EndPoint](https://user-images.githubusercontent.com/116869307/214147340-866900ae-dc9c-4cbd-a9e8-c8755d833674.png)

* * * * * * * * * *

## Einleitung
Der **Q_EndPoint** ist ein standardkonformer Funktionsbaustein zur Steuerung von Linienendpunkten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.26) Spezifikation für landwirtschaftliche Steuersysteme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Endpunktänderungs-Anforderung (mit Position/Richtung)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung (mit Ergebnisdaten)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Linienobjekt-ID
- `u16Width` (UINT): Neue X-Endposition (0-65535 Pixel)
- `u16Height` (UINT): Neue Y-Endposition (0-65535 Pixel)
- `u8LineDirection` (USINT): Linienrichtung (ISO 11783-6 B.27)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u16OldWidth` (UINT): Vorherige X-Endposition
- `u16OldHeight` (UINT): Vorherige Y-Endposition
- `u8OldLineDirection` (USINT): Vorherige Linienrichtung
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Linienobjekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Endpunktänderung**:
   - `REQ` mit neuen Positions- und Richtungsparametern
   - Ändert Endpunkt und Ausrichtung der Linie
   - `CNF` liefert Ergebnis und alte Werte

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.26 + B.27)  
✔ **16-bit Positionsauflösung** (0-65535 Pixel)  
✔ **Vollständige Liniensteuerung** (Position + Richtung)  
✔ **Echtzeitfähige** Verarbeitung  

## Linienrichtungen (B.27)

| Wert | Richtung          | Beschreibung            |
|------|-------------------|-------------------------|
| 0    | Horizontal        | Von links nach rechts   |
| 1    | Vertikal          | Von oben nach unten     |
| 2    | Diagonal rechts   | Links oben → rechts unten |
| 3    | Diagonal links    | Rechts oben → links unten |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreich                       |
| -6   | VT_E_OVERFLOW           | Ungültige Positionswerte          |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Linienobjekt-ID         |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige Instanz                |

## Anwendungsszenarien

- **Maschinenvisualisierung**: Dynamische Verbindungslinien
- **Diagramme**: Anpassbare Datenanzeigen
- **Technische Zeichnungen**: Konfigurierbare Hilfslinien
- **UI-Design**: Adaptive Trennlinien

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_EndPoint   | VtLineEditor | VtDynamicLine |
|---------------|--------------|--------------|---------------|
| ISO-Standard  | ✔            | ✖            | ✖             |
| Steuerung     | Endpunkt     | Vollständig  | Nur Position  |
| Richtungen    | 4 Optionen   | 8 Optionen   | Keine         |

## Fazit

Der Q_EndPoint-Baustein bietet die Referenzimplementierung für Linienendpunkt-Steuerung:

- **Präzise**: Pixelgenaue Positionierung
- **Flexibel**: Kombinierte Positions- und Richtungssteuerung
- **Standardkonform**: Volle ISO 11783-6 Kompatibilität

Idealer Einsatz bei:
- Dynamischen technischen Zeichnungen
- Adaptiven Diagrammanzeigen
- Konfigurierbaren Benutzeroberflächen
