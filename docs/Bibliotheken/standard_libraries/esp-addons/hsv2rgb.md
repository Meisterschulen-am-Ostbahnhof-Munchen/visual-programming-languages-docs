# hsv2rgb

![hsv2rgb](https://user-images.githubusercontent.com/116869307/214141778-56fe9e06-d507-4cbd-a0c0-717217a4db83.png)

* * * * * * * * * *

## Einleitung
Der **HSV2RGB** ist ein spezialisierter Funktionsbaustein nach IEC 61499-2 zur Konvertierung von HSV- in RGB-Farbwerte. Entwickelt unter EPL-2.0 Lizenz ermöglicht Version 1.0 die farbtreue Umrechnung für Visualisierungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Konvertierungsanforderung (mit HSV-Werten)

### **Ereignis-Ausgänge**
- `CNF`: Konvertierungsbestätigung (mit RGB-Werten)

### **Daten-Eingänge**
- `hue` (UDINT): Farbton (0-360°)
- `saturation` (UDINT): Sättigung (0-100%)
- `value` (UDINT): Helligkeit (0-100%)

### **Daten-Ausgänge**
- `r` (UDINT): Rot-Anteil (0-255)
- `g` (UDINT): Grün-Anteil (0-255)
- `b` (UDINT): Blau-Anteil (0-255)

## Funktionsprinzip

1. **Anforderung**:
   - `REQ`-Ereignis mit HSV-Parametern startet Konvertierung

2. **Berechnung**:
   - Implementiert standardisierten HSV→RGB-Algorithmus
   - Berücksichtigt zylindrischen HSV-Farbraum

3. **Ausgabe**:
   - `CNF`-Ereignis mit berechneten RGB-Werten
   - Wertebereich für RGB: 0-255 (24-bit Farbe)

## Technische Besonderheiten

✔ **Präzise Farbraumtransformation**  
✔ **Integer-basierte Berechnung** (UDINT)  
✔ **Echtzeitfähige** Konvertierung  
✔ **Standardkonform** nach IEC 61499-2  

## Anwendungsszenarien

- **Visualisierungssysteme**: HMI-Farbdarstellung
- **Landtechnik**: Statusanzeigen
- **Bildverarbeitung**: Farbkorrekturen
- **LED-Steuerungen**: Dynamische Beleuchtung

## Vergleich mit ähnlichen Bausteinen

| Feature        | HSV2RGB | RGB2HSV | GRAYSCALE |
|---------------|---------|---------|-----------|
| Konvertierung | HSV→RGB | RGB→HSV | RGB→Grau  |
| Farbtiefe     | 24-bit  | 24-bit  | 8-bit     |
| Parameter     | 3 Eing. | 3 Eing. | 3 Eing.   |

## Fazit

Der HSV2RGB-Baustein bietet eine professionelle Lösung für Farbraumkonvertierungen:

- Intuitive HSV-Eingabe (Farbton/Sättigung/Helligkeit)
- Standardisierte RGB-Ausgabe
- Optimierte Performance für Echtzeitsysteme

Besonders wertvoll für Anwendungen, die benutzerfreundliche Farbauswahl mit präziser RGB-Darstellung kombinieren müssen. Die IEC 61499-2-Konformität ermöglicht einfache Integration in industrielle Steuerungssysteme.
