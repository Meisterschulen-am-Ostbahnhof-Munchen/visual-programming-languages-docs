# Q_Size

![Q_Size](https://user-images.githubusercontent.com/116869307/214153095-72c9e230-b193-4843-be85-33038f6bd44d.png)

* * * * * * * * * *

## Einleitung

Der **Q_Size** ist ein standardkonformer Funktionsbaustein zur Größenänderung von Objekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.18) Spezifikation für VT-Objekte.

![Q_Size](Q_Size.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Größenänderungs-Anforderung

### **Ereignis-Ausgänge**

- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung

### **Daten-Eingänge**

- `u16ObjId` (UINT): Objekt-ID (16-bit)
- `u16Width` (UINT): Neue Breite in Pixeln
- `u16Height` (UINT): Neue Höhe in Pixeln

### **Daten-Ausgänge**

- `STATUS` (STRING): Betriebsstatusmeldung
- `u16OldWidth` (UINT): Vorherige Breite
- `u16OldHeight` (UINT): Vorherige Höhe
- `s16result` (INT): ISO-konformer Ergebniscode

## Gültige Objekt-IDs

**`u16ObjId` — gültige Objekttypen (Anhang F.18, Objekte mit Größen-Attribut):**
Container (3000–3999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Input List Field (10000–10999), Output String Field (11000–11999), Output Number Field (12000–12999), Output Line (13000–13999), Output Rectangle (14000–14999), Output Ellipse (15000–15999), Output Polygon (16000–16999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Output List Object (37000–37999), Animation Object (44000–44999).

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Zielobjekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Größenänderung**:
   - `REQ` mit neuen Abmessungen
   - Passt die Objektgeometrie dynamisch an
   - `CNF` liefert Betriebsstatus und vorherige Maße

3. **Maßeinheit**:
   - Alle Werte in Bildschirmpixeln

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.18)
✔ **Dynamische Größenanpassung** (Echtzeit-Update)
✔ **Umfassende Objektunterstützung**
✔ **Rückverfolgbarkeit** (Vorherige Abmessungen)

## Größenreferenz

| Parameter | Wertebereich   | Beschreibung       |
|-----------|---------------|--------------------|
| Width     | 1-65535 Pixel | Horizontale Ausdehnung |
| Height    | 1-65535 Pixel | Vertikale Ausdehnung |

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

- **Responsive Designs**: Anpassung an Displaygrößen
- **Zoom-Funktionen**: Dynamische Skalierung
- **Layoutmanager**: Automatische Größenoptimierung
- **Animationssteuerung**: Größenänderungseffekte

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_Size | VtResizeObject | VtGeometryManager |
|---------------|--------|----------------|-------------------|
| ISO-Standard  | ✔      | ✖              | ✖                 |
| Echtzeit-Update | ✔    | ✔              | ✖                 |
| 2D-Steuerung  | ✔      | ✔              | ✔                 |
| Rückmeldung   | ✔      | ✖              | ✔                 |

## Fazit

Der Q_Size-Baustein bietet präzise Größensteuerung:

- **Flexibel**: Pixelgenaue Anpassung
- **Performant**: Sofortige Darstellungsaktualisierung
- **Zuverlässig**: ISO-konforme Implementierung

Unverzichtbar für:

- Adaptive Benutzeroberflächen
- Dynamische Visualisierungen
- Professionelle VT-Anwendungen
