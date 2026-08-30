# Q_ChildPosition

![Q_ChildPosition](https://user-images.githubusercontent.com/116869307/214147176-8b27f37a-4898-406a-98a0-e5f5701abc58.png)

* * * * * * * * * *

## Einleitung

Der **Q_ChildPosition** ist ein standardkonformer Funktionsbaustein zur absoluten Positionsänderung von Child-Objekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.16) Spezifikation für landwirtschaftliche Steuersysteme.

![Q_ChildPosition](Q_ChildPosition.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Initialisierungsanforderung (mit Objekt- und Parent-ID)
- `REQ`: Positionsänderungs-Anforderung (mit absoluten Koordinaten)

### **Ereignis-Ausgänge**

- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung (mit Ergebnisdaten)

### **Daten-Eingänge**

- `u16ObjId` (UINT): Child-Objekt-ID
- `u16ObjIdParent` (UINT): Parent-Objekt-ID
- `s16Xposition` (INT): Absolute X-Position relativ zum Parent
- `s16Yposition` (INT): Absolute Y-Position relativ zum Parent

### **Daten-Ausgänge**

- `STATUS` (STRING): Betriebsstatusmeldung
- `s16OldXposition` (INT): Vorherige X-Position
- `s16OldYposition` (INT): Vorherige Y-Position
- `s16result` (INT): ISO-konformer Ergebniscode

## Gültige Objekt-IDs

`u16ObjId` (das zu bewegende Child-Objekt) und `u16ObjIdParent` (das Parent-Objekt) unterliegen **unterschiedlichen** Gültigkeitsregeln. Annex F der ISO 11783-6 definiert nur, welche Objekttypen als Child gültig sind — welche Objekttypen als Parent zulässig sind, steht separat in Annex B, jeweils unter „Allowed commands" des Objekttyps.

**`u16ObjId` — gültige Child-Objekttypen (Annex F.16):**
Container (3000–3999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Input List Field (10000–10999), Output String Field (11000–11999), Output Number Field (12000–12999), Output Line (13000–13999), Output Rectangle (14000–14999), Output Ellipse (15000–15999), Output Polygon (16000–16999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Picture Graphic (20000–20499), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999), Auxiliary Function/Type2 (29000–29999 / 31000–31999), Auxiliary Input/Type2 (30000–30999 / 32000–32999), Auxiliary Control Designator (33000–33999).

**`u16ObjIdParent` — gültige Parent-Objekttypen (Annex B, "Allowed commands"):**
WorkingSet (B.1), Data Mask (B.2), Alarm Mask (B.3), **Container (B.4)**, Key (B.6), Window Mask, Button, Auxiliary Function (Type 1/2), Auxiliary Input (Type 1/2).

**Nicht zulässig als Parent:** Soft Key Mask (B.5 listet das Kommando nicht als erlaubt) und Animation Object (dessen Kinder sind indexbasiert, nicht X/Y-positioniert).

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Child- und Parent-Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Positionsänderung**:
   - `REQ` mit absoluten Koordinaten relativ zum Parent
   - Wertebereich: -32768 bis +32767 Pixel
   - `CNF` liefert Ergebnis und alte Position

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.16)
✔ **Absolute Positionsänderung** (relativ zum Parent)
✔ **16-bit Wertebereich** (±32768 Pixel)
✔ **Echtzeitfähige** Verarbeitung

## Positionsbereich

| Parameter | Bereich        | Beschreibung               |
|-----------|---------------|----------------------------|
| X-Position| -32768 - +32767| Horizontale Position       |
| Y-Position| -32768 - +32767| Vertikale Position         |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreich                       |
| -6   | VT_E_OVERFLOW           | Position außerhalb des gültigen Bereichs |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Objekt-ID               |

## Anwendungsszenarien

- **Präzise Objektplatzierung**: Exakte Positionierung von UI-Elementen
- **Dynamische Layouts**: Neuausrichtung von Bedienelementen
- **Komplexe Anordnungen**: Mehrschichtige Oberflächen
- **Maschinenvisualisierung**: Technische Zeichnungen

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ChildPosition | Q_ChildLocation | VtAbsoluteMove |
|---------------|-----------------|-----------------|----------------|
| ISO-Standard  | ✔               | ✔               | ✖              |
| Positionstyp  | Absolut         | Relativ         | Absolut        |
| Wertebereich  | ±32767 Pixel    | ±127 Pixel      | ±32767 Pixel   |

## Fazit

Der Q_ChildPosition-Baustein bietet die Referenzimplementierung für absolute Positionsänderungen:

- **Präzise**: Pixelgenaue Positionierung
- **Flexibel**: Großer Wertebereich
- **Standardkonform**: Volle ISO 11783-6 Kompatibilität

Idealer Einsatz bei:

- Komplexen Benutzeroberflächen
- Technischen Zeichnungen
- Präzisen Layoutanforderungen
