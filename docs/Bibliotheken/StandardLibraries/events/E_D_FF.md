# E_D_FF

```{index} single: E_D_FF
```

![E_D_FF Diagram](https://user-images.githubusercontent.com/113907528/204898130-f9f31fd9-da42-4b29-a664-add0d91e8890.png)

* * * * * * * * * *

## 📺 Video

* [D-Flip-Flop: E_D_FF aus der IEC 61499 (Übung 002c) als "Eventbremse"](https://www.youtube.com/watch?v=yGSx_0ggveE)
* [D-Flip-Flop: E_D_FF aus der IEC 61499 (Übung 85)](https://www.youtube.com/watch?v=VNaTUOE5izc)

## Einleitung
Die IEC 61499 ist ein internationaler Standard für die Modellierung verteilter industrieller Steuerungssysteme. Der **E_D_FF**-Baustein (Data Flip-Flop) ist ein grundlegendes Speicherelement in dieser Norm, das digitale Signale synchron zu einem Taktsignal speichert. Dieser Funktionsbaustein spielt eine zentrale Rolle in Zustandsmaschinen und Speicheranwendungen industrieller Automatisierungslösungen.

## Struktur des E_D_FF-Bausteins

### Schnittstelle (Interface)

**Ereignis-Eingänge:**
- `CLK` (Clock): Taktereignis, das die Übernahme des Daten-Eingangs `D` auslöst.
    - **Verbundene Daten**: `D`

**Ereignis-Ausgänge:**
- `EO` (Event Output): Wird ausgelöst, wenn der `CLK`-Impuls zu einer Änderung des Ausgangs `Q` führt.
    - **Verbundene Daten**: `Q`

**Daten-Eingänge:**
- `D`: Der zu speichernde Datenwert (Datentyp: `BOOL`).

**Daten-Ausgänge:**
- `Q`: Der aktuell gespeicherte Wert (Datentyp: `BOOL`).

## Funktionsweise

1. **Datenspeicherung:**
   - Bei jeder positiven Flanke des `CLK`-Signals wird der Wert von `D` in `Q` übernommen
   - Bei Wertänderung wird das `EO`-Ereignis ausgelöst

2. **Datenhaltung:**
   - Zwischen den Taktflanken bleibt der gespeicherte Wert `Q` stabil
   - Änderungen am Eingang `D` haben ohne Taktflanke keine Auswirkung

## Technische Besonderheiten

✔ **Taktgesteuerte Speicherung** für synchrone Systeme  
✔ **Ereignisausgang** für Änderungsdetektion  
✔ **Deterministisches Verhalten** in Echtzeitsystemen  
✔ **Einfache Integration** in IEC 61499-Applikationen  

## Anwendungsszenarien

- **Zustandsspeicherung** in Automatisierungsprozessen
- **Eingabepufferung** für Bedienereingaben
- **Flankenerkennung** in Signalverarbeitungsketten
- **Synchronisation** zwischen asynchronen Systemteilen

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_D_FF | E_SR | E_R_TRIG |
|---------------|--------|------|----------|
| Speichertyp   | D-Flip-Flop | SR-Latch | Flankendetektor |
| Taktung       | Erforderlich | Keine | Keine |
| Datenhaltung  | Ja | Ja | Nein |
| Ereignisausgang | Bei Änderung | Bei Set/Reset | Bei Flanke |

## Fazit

Der E_D_FF-Baustein stellt ein essentielles Speicherelement für IEC 61499-basierte Steuerungssysteme dar. Seine Hauptvorteile sind:

- Zuverlässige taktsynchrone Datenspeicherung
- Sofortige Rückmeldung von Zustandsänderungen
- Robuste Integration in verteilte Steuerungsarchitekturen

Durch seine einfache aber wirkungsvolle Funktionalität bildet er die Grundlage für komplexere Speicher- und Zustandssteuerungen in industriellen Automatisierungslösungen. Die strikte Einhaltung der IEC 61499-Standards gewährleistet dabei die problemlose Interoperabilität mit anderen Funktionsbausteinen.