# Q_BackgroundColourAux

* * * * * * * * * *

## Einleitung

Der **Q_BackgroundColourAux** ist ein standardkonformer Funktionsbaustein zur Steuerung von sekundären Hintergrundfarben in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.20) Spezifikation für Hilfsfarben in landwirtschaftlichen Steuersystemen.

![Q_BackgroundColourAux](Q_BackgroundColourAux.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Farbänderungs-Anforderung (mit Farbcode)

### **Ereignis-Ausgänge**

- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung (mit Ergebnisdaten)

### **Daten-Eingänge**

- `u16ObjId` (UINT): Objektkennung
- `u8Colour` (USINT): Neuer Hilfsfarbwert (ISO 11783-6 Palette)

### **Daten-Ausgänge**

- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldColour` (USINT): Vorheriger Hilfsfarbwert
- `s16result` (INT): ISO-konformer Ergebniscode

## Gültige Objekt-IDs

**`u16ObjId` — gültige Objekttypen (Anhang F.20, Objekte mit Hintergrundfarben-Attribut):**
WorkingSet (0), Data Mask (1000–1999), Alarm Mask (2000–2999), Soft Key Mask (4000–4999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Output String Field (11000–11999), Output Number Field (12000–12999), Window Mask (34000–34999), Graphics Context (36000–36999), Auxiliary Function (29000–29999), Auxiliary Function Type2 (31000–31999), Auxiliary Input Type2 (32000–32999).

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Objekt-ID für Hilfselement
   - `INITO` bestätigt Betriebsbereitschaft

2. **Farbänderung**:
   - `REQ` mit neuem Hilfsfarbcode (0-255) auslösen
   - `CNF` liefert Ergebnis und alten Farbwert

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.20 für Hilfsfarben)
✔ **8-bit Farbunterstützung** (256 Werte)
✔ **Kompatibel mit Q_BackgroundColour**
✔ **Zustandserhaltung** (u8OldColour)

## Standard-Hilfsfarben (Auszug)

| Code | Anwendungsbereich      | Typische Farbe  |
|------|------------------------|-----------------|
| 16   | Statusbalken           | Blau            |
| 32   | Sekundärbereiche       | Grau            |
| 48   | Hilfslinien            | Hellblau        |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreich                       |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Objekt-ID               |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige Instanz                |

## Anwendungsszenarien

- **Statusanzeigen**: Sekundärfarben für Balken
- **Gruppierungen**: Farbliche Abgrenzung von Bereichen
- **Editor-Modi**: Hilfslinien in Konfiguratoren
- **Diagnose**: Zusatzinformationen

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_BackgroundColourAux | Q_BackgroundColour | VtAuxColour |
|---------------|-----------------------|--------------------|-------------|
| ISO-Standard  | ✔                     | ✔                  | ✖           |
| Farbbereich   | Hilfselemente         | Hauptelemente      | Alle        |
| Verwendung    | Sekundär              | Primär             | Universell  |

## Fazit

Der Q_BackgroundColourAux-Baustein ergänzt die ISOBUS-Farbsteuerung für Hilfselemente:

- **Spezialisiert**: Optimiert für sekundäre Anzeigeelemente
- **Konsistent**: Gleiche API wie Q_BackgroundColour
- **Praxisbewährt**: Eingesetzt in modernen Traktor-Displays

Idealer Einsatz bei:

- Komplexen Anzeigelayouts
- Mehrschichtigen Visualisierungen
- Systemen mit erweitertem Farbmanagement