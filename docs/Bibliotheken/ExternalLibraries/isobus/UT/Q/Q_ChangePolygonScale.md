# Q_ChangePolygonScale

```{index} single: Q_ChangePolygonScale
```

![Q_ChangePolygonScale](https://user-images.githubusercontent.com/116869307/214147096-01ad8095-df5d-4cab-82ee-7f97a5758ea0.png)

* * * * * * * * * *

## Einleitung
Der **Q_ChangePolygonScale** ist ein standardkonformer Funktionsbaustein zur Skalierung von Polygonobjekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.54) Spezifikation für landwirtschaftliche Steuersysteme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Polygon-Objekt-ID)
- `REQ`: Skalierungsanforderung (mit neuen Abmessungen)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Skalierungsbestätigung (mit Ergebnisdaten)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Polygon-Objekt-ID
- `u16NewWidth` (UINT): Neue Breite in Pixeln
- `u16NewHeight` (UINT): Neue Höhe in Pixeln

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u16OldWidth` (UINT): Vorherige Breite
- `u16OldHeight` (UINT): Vorherige Höhe
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Polygon-Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Skalierung**:
   - `REQ` mit neuen Abmessungen auslösen
   - Proportionale Skalierung aller Polygonpunkte
   - `CNF` liefert Ergebnis und alte Werte

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.54)
✔ **Proportionale Skalierung** (Breite/Höhe)
✔ **16-bit Auflösung** (0-65535 Pixel)
✔ **Echtzeitfähige** Verarbeitung

## Skalierungsverhalten

| Parameter  | Wirkung                     |
|------------|-----------------------------|
| Breite     | Horizontale Skalierung      |
| Höhe       | Vertikale Skalierung        |
| 0xFFFF     | Ursprungsgröße beibehalten  |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreich                       |
| -6   | VT_E_OVERFLOW           | Ungültige Abmessungen             |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Polygon-ID              |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige Instanz                |

## Anwendungsszenarien

- **Maschinendarstellung**: Dynamische Größenanpassung
- **Zoomfunktionen**: Detailvergrößerungen
- **Responsive Designs**: Anpassung an Displaygrößen
- **Animierte Übergänge**: Fließende Größenänderungen

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ChangePolygonScale | VtGeometryScaler | VtDynamicResize |
|---------------|----------------------|------------------|-----------------|
| ISO-Standard  | ✔                    | ✖                | ✖               |
| Skalierung    | Proportional         | Frei             | Nur Breite      |
| Auflösung     | 16-bit               | 8-bit            | 16-bit          |

## Fazit

Der Q_ChangePolygonScale-Baustein bietet die Referenzimplementierung für Polygon-Skalierungen:

- **Präzise**: Pixelgenaue Größenkontrolle
- **Proportional**: Erhalt der Originalform
- **Standardkonform**: Volle ISO 11783-6 Kompatibilität

Idealer Einsatz bei:
- Adaptiven Visualisierungen
- Dynamischen Kartenansichten
- Größenveränderbaren Bedienelementen