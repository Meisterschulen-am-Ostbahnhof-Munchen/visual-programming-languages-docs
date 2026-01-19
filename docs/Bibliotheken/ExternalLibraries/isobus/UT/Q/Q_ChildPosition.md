# Q_ChildPosition

```{index} single: Q_ChildPosition
```

![Q_ChildPosition](https://user-images.githubusercontent.com/116869307/214147176-8b27f37a-4898-406a-98a0-e5f5701abc58.png)

* * * * * * * * * *

## Einleitung
Der **Q_ChildPosition** ist ein standardkonformer Funktionsbaustein zur absoluten Positionsänderung von Child-Objekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.16) Spezifikation für landwirtschaftliche Steuersysteme.

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

## Vergleich mit ähnlichen Bausteinen

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