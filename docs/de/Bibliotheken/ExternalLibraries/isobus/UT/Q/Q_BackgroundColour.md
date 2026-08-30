# Q_BackgroundColour

![Q_BackgroundColour](https://user-images.githubusercontent.com/113907471/204320542-f628c868-03d7-4d81-9ebb-5cf63d9ce541.png)

![Beispiel](https://user-images.githubusercontent.com/113907471/204320176-773a1f69-281c-4d83-873a-671f1680081a.png)

* * * * * * * * * *

## Einleitung

Der **Q_BackgroundColour** ist ein standardkonformer Funktionsbaustein zur Steuerung von Hintergrundfarben in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.20) Spezifikation für landwirtschaftliche Steuersysteme.

![Q_BackgroundColour](Q_BackgroundColour.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Farbänderungs-Anforderung (mit Farbcode)

### **Ereignis-Ausgänge**

- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung (mit Ergebnisdaten)

### **Daten-Eingänge**

- `u16ObjId` (UINT): Objektkennung
- `u8Colour` (USINT): Neuer Farbwert (ISO 11783-6 Palette)

### **Daten-Ausgänge**

- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldColour` (USINT): Vorheriger Farbwert
- `s16result` (INT): ISO-konformer Ergebniscode

## Gültige Objekt-IDs

**`u16ObjId` — gültige Objekttypen (Anhang F.20, Objekte mit Hintergrundfarben-Attribut):**
WorkingSet (0), Data Mask (1000–1999), Alarm Mask (2000–2999), Soft Key Mask (4000–4999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Output String Field (11000–11999), Output Number Field (12000–12999), Window Mask (34000–34999), Graphics Context (36000–36999), Auxiliary Function (29000–29999), Auxiliary Function Type2 (31000–31999), Auxiliary Input Type2 (32000–32999).

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Farbänderung**:
   - `REQ` mit neuem Farbcode (0-255) auslösen
   - `CNF` liefert Ergebnis und alten Farbwert

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.20 + A.3 Farbpalette)
✔ **8-bit Farbunterstützung** (256 Werte)
✔ **Echtzeitfähige** Verarbeitung
✔ **Zustandserhaltung** (u8OldColour)

## Standardfarbpalette (Auszug)

| Code | Farbe       | RGB-Äquivalent |
|------|-------------|----------------|
| 0    | Schwarz     | #000000        |
| 1    | Rot         | #FF0000        |
| 2    | Grün        | #00FF00        |
| 3    | Gelb        | #FFFF00        |
| 4    | Blau        | #0000FF        |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreich                       |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                    |
| -8   | VT_E_NOACT              | Ungültiger Zustand                |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Objekt-ID               |

## Anwendungsszenarien

- **Maschinenstatus**: Farbliche Alarmanzeige
- **Nachtmodus**: Dunkle Farbpaletten
- **Markierungen**: Hervorhebung von Objekten
- **Branding**: Hersteller-spezifische Farben

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_BackgroundColour | VtColourManager | VtDynamicStyle |
|---------------|--------------------|-----------------|----------------|
| ISO-Standard  | ✔                  | ✖               | ✖              |
| Farbpalette   | Standard           | Erweitert       | Benutzerdef.   |
| Objektbindung | Explizit           | Implizit        | Stylesheet     |

## 🛠️ Zugehörige Übungen

- [Uebung_016](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_016.md)
- [Uebung_016a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_016a.md)

## Fazit

Der Q_BackgroundColour-Baustein bietet die Referenzimplementierung für ISOBUS-Farbsteuerung:

- **Standardkonform**: Volle ISO 11783-6 Kompatibilität
- **Einfache Integration**: Klare Farbpalettendefinition
- **Robust**: Bewährte Feldtauglichkeit

Essentiell für:

- Farbliche Statusanzeigen
- Benutzeroberflächen-Design
- Dynamische Visualisierungen
