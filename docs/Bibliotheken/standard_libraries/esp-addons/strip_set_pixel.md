# strip_set_pixel

![strip_set_pixel](https://user-images.githubusercontent.com/116869307/214141844-ddb96db7-341d-496e-b4cb-f277d1f6fb39.png)

* * * * * * * * * *

## Einleitung
Der **STRIP_SET_PIXEL** ist ein spezialisierter Service-Interface-Baustein nach IEC 61499-2 zur Ansteuerung von LED-Streifen. Entwickelt unter EPL-2.0 Lizenz ermöglicht Version 1.0 die individuelle Ansteuerung einzelner LEDs in RGB-Streifen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierung des LED-Controllers
- `set_pixel`: Setzt Farbe für einzelne LED (mit Index und RGB-Werten)
- `clear`: Löscht den gesamten LED-Streifen

### **Ereignis-Ausgänge**
- `INITO`: Bestätigung der Initialisierung
- `set_pixel_CNF`: Bestätigung der Pixel-Setzung
- `clear_CNF`: Bestätigung des Löschvorgangs

#### **Daten-Eingänge**
- `index` (UDINT): LED-Position im Streifen
- `red` (UDINT): Rotwert (0-255)
- `green` (UDINT): Grünwert (0-255)
- `blue` (UDINT): Blauwert (0-255)

#### **Daten-Ausgänge**
- `set_pixel_return` (DINT): Fehlercode der Pixeloperation
- `clear_return` (DINT): Fehlercode des Löschvorgangs

## Funktionsweise

1. **Initialisierung**:
   - `INIT` startet den LED-Controller
   - `INITO` bestätigt erfolgreichen Start

2. **Pixelsteuerung**:
   - `set_pixel` mit Index und RGB-Werten
   - `set_pixel_CNF` mit Rückgabecode

3. **Streifenreset**:
   - `clear` deaktiviert alle LEDs
   - `clear_CNF` bestätigt Operation

## Technische Besonderheiten

✔ **Individuelle LED-Ansteuerung**  
✔ **24-bit RGB-Farbtiefe** pro LED  
✔ **Fehlerrückmeldung** für alle Operationen  
✔ **Echtzeitfähige** Steuerung  

## Anwendungsszenarien

- **Industrielle Beleuchtung**: Statusanzeigen
- **Landmaschinen**: Arbeitszustandsvisualisierung
- **Werbetechnik**: Dynamische Lichteffekte
- **Architekturbeleuchtung**: Gebäudeillumination

## Befehlstabelle

| Befehl         | Parameter               | Rückgabewert          |
|----------------|-------------------------|-----------------------|
| INIT           | -                       | INITO                 |
| set_pixel      | index, red, green, blue | set_pixel_return      |
| clear          | -                       | clear_return          |

## Fazit

Der STRIP_SET_PIXEL-Baustein bietet eine professionelle Schnittstelle für LED-Streifen:

- Präzise Einzel-LED-Steuerung
- Volle RGB-Farbkontrolle
- Robuste Fehlerrückmeldung

Besonders geeignet für industrielle Anwendungen, die zuverlässige und flexible LED-Visualisierung erfordern. Die standardkonforme IEC 61499-2-Implementierung ermöglicht einfache Integration in Automatisierungssysteme.