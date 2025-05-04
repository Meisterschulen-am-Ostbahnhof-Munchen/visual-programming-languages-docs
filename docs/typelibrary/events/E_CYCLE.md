# E_CYCLE

![E_CYCLE Diagram](https://user-images.githubusercontent.com/113907471/204306660-9e93e9cc-10f0-4d51-829f-229ee64a1227.png)

* * * * * * * * * *

## Einleitung
Der **E_CYCLE** ist ein taktgebender Funktionsbaustein nach IEC 61499, der zyklische Ereignisse mit einstellbarer Dauer generiert. Hauptsächlich als Blinker oder Zeitschaltrelais eingesetzt, ermöglicht er die Steuerung periodischer Prozesse in industriellen Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START`: Aktiviert den Taktgenerator
- `STOP`: Deaktiviert den Taktgenerator

### **Ereignis-Ausgänge**
- `EO` (Event Output): Zyklisches Ausgangssignal

### **Daten-Eingänge**
| Port | Typ | Beschreibung |
|------|-----|-------------|
| DT   | TIME | Zykluszeit (Ein-/Ausschaltdauer) |

## Funktionsweise

1. **Startphase**
   - Bei `START`-Ereignis beginnt der Zyklus
   - Ausgang `EO` wird aktiviert

2. **Zyklusbetrieb**
   - Nach Ablauf von `DT` wechselt der Ausgangszustand
   - Dieser Wechsel wiederholt sich kontinuierlich

3. **Stoppphase**
   - `STOP`-Ereignis beendet den Zyklus
   - Ausgang `EO` wird deaktiviert

## Technische Besonderheiten

✔ **Präzise Zeitsteuerung** (millisekundengenaue Zykluszeiten)
✔ **Ereignisgesteuerte Steuerung** (kein Polling erforderlich)
✔ **Echtzeitfähig** für industrielle Anwendungen
✔ **Einfache Konfiguration** durch TIME-Parameter

## Anwendungsszenarien

- **Warnblinkanlagen**: Periodische Signalisierung
- **Maschinensteuerung**: Zyklische Prozessabläufe
- **Beleuchtungstechnik**: Blinklichtsteuerung
- **Testautomation**: Periodische Stimuli

## Vergleich mit ähnlichen Bausteinen

| Feature | E_CYCLE | E_DELAY | E_PULSE |
|---------|---------|---------|---------|
| Typ | Taktgeber | Verzögerung | Einmalimpuls |
| Wiederholung | Kontinuierlich | Einmalig | Einmalig |
| Steuerung | START/STOP | START | REQ |

## Fazit

Der E_CYCLE-Baustein bietet eine effiziente Lösung für alle Anwendungen, die periodische Signale oder Aktionen benötigen. Seine Hauptvorteile sind:

- Einfache Parametrierung der Zykluszeit
- Zuverlässige ereignisgesteuerte Architektur
- Sofortige Reaktion auf Steuersignale

Besonders in Sicherheitsanwendungen wie Warnlichtsystemen oder in Produktionsanlagen für rhythmische Prozesssteuerungen beweist der Baustein seine Stärken. Die Compliance mit IEC 61499 gewährleistet dabei die problemlose Integration in bestehende Automatisierungssysteme.