# FB_RANDOM

![FB_RANDOM](https://user-images.githubusercontent.com/116869307/214155024-ae39eff3-e6bb-427b-a02b-83e3f91fd564.png)

* * * * * * * * * *

## Einleitung
Der **FB_RANDOM**-Funktionsbaustein ist ein standardkonformer Zufallszahlengenerator nach IEC 61499-1, entwickelt unter EPL-2.0 Lizenz.
Der Baustein generiert gleichverteilte Pseudozufallszahlen im Bereich [0,1).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisiert den Zufallszahlengenerator (optional)
- `REQ`: Löst die Berechnung einer neuen Zufallszahl aus

### **Ereignis-Ausgänge**
- `INITO`: Bestätigt die Initialisierung
- `CNF`: Liefert die berechnete Zufallszahl

### **Daten-Eingänge**
| Parameter | Typ | Beschreibung | Initialwert |
|-----------|-----|--------------|-------------|
| `SEED` | UINT | Seed-Wert (0 = Systemzeit) | 0 |

### **Daten-Ausgänge**
| Parameter | Typ | Beschreibung | Wertebereich |
|-----------|-----|--------------|-------------|
| `VAL` | REAL | Generierte Zufallszahl | [0.0, 1.0) |

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit `SEED`=0 verwendet Systemzeit
   - `INIT` mit `SEED`<>0 verwendet festen Startwert
   - Ohne Initialisierung wiederholbare Sequenz

2. **Zahlengenerierung**:
   - `REQ` triggert Berechnung
   - `CNF` liefert Ergebnis in `VAL`

3. **Wiederholbarkeit**:
   - Gleicher Seed = gleiche Zahlenfolge
   - Systemzeit-Seed = nicht reproduzierbar

## Technische Besonderheiten

✔ **IEC 61499-1 konform** (Mathematische Funktion)  
✔ **Basiert auf C-Standard rand()** (Mindestbereich 0-32767)  
✔ **Eclipse 4diac Integration**  
✔ **Zwei Betriebsmodi** (Reproduzierbar/Nicht-reproduzierbar)  

## Anwendungsszenarien

- **Simulationen**: Zufällige Prozessparameter
- **Spiele**: Nicht-deterministisches Verhalten
- **Tests**: Zufällige Testfälle generieren
- **Statistik**: Monte-Carlo-Simulationen

## Beispielwerte

| Seed | Erste 3 Werte (Beispiel) |
|------|--------------------------|
| 0 | 0.12345, 0.65432, 0.98765 |
| 42 | 0.16234, 0.79456, 0.32891 |
| Kein INIT | 0.00000, 0.00001, 0.00002 |

## Vergleich mit ähnlichen Bausteinen

| Feature | FB_RANDOM | Standard-RNG | Kryptografisch sicher |
|---------|-----------|--------------|-----------------------|
| Geschwindigkeit | Hoch | Mittel | Niedrig |
| Sicherheit | Niedrig | Niedrig | Hoch |
| Reproduzierbarkeit | Ja | Ja | Nein |
| Wertebereich | [0,1) | Systemabhängig | Groß |

## Fazit

Der FB_RANDOM-Baustein bietet einfache Zufallszahlengenerierung:

- **Einfach**: Intuitive Bedienung
- **Flexibel**: Reproduzierbar oder nicht-reproduzierbar
- **Leichtgewichtig**: Geringer Ressourcenbedarf

Idealer Einsatz bei:
- Prototypenentwicklung
- Simulationen
- Testautomatisierung
- Nicht-kritischen Zufallsanwendungen

*Der praktische Helfer für zufällige Anforderungen in Steuerungssystemen*
