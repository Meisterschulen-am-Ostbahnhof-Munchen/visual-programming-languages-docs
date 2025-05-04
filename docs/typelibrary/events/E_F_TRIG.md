# E_F_TRIG

![E_F_TRIG Diagram](https://user-images.githubusercontent.com/113907528/204898671-3eb058ff-7481-4fc8-a2d4-8cf50f349cee.png)

* * * * * * * * * *

## Einleitung
Der **E_F_TRIG** (Falling Edge Trigger) ist ein grundlegender Funktionsbaustein der IEC 61499 Norm zur Erkennung von fallenden Signalflanken. Dieser Baustein spielt eine wichtige Rolle in der Ereignisdetektion und Signalverarbeitung industrieller Steuerungssysteme.

## Struktur des E_F_TRIG-Bausteins

### Schnittstelle (Interface)

**Ereignis-Eingänge:**
- `EI` (Event Input): Aktiviert die Flankenerkennung
- `QI`: Zu überwachendes Eingangssignal (BOOL)

**Ereignis-Ausgänge:**
- `EO` (Event Output): Wird bei Erkennung einer fallenden Flanke ausgelöst

## Funktionsweise

1. **Flankenerkennung:**
   - Bei jedem `EI`-Ereignis wird der aktuelle Zustand von `QI` geprüft
   - Eine fallende Flanke liegt vor, wenn `QI` von TRUE auf FALSE wechselt

2. **Ereignisauslösung:**
   - Bei Erkennung einer fallenden Flanke wird `EO` ausgelöst
   - Ohne Flankenwechsel bleibt `EO` inaktiv

3. **Speicherverhalten:**
   - Der Baustein merkt sich den letzten Zustand von `QI`
   - Nur echte Zustandsänderungen werden detektiert

## Technische Besonderheiten

✔ **Präzise Flankendetektion** für zuverlässige Signalauswertung  
✔ **Ereignisgesteuert** (kein zyklischer Aufruf erforderlich)  
✔ **Echtzeitfähig** für industrielle Anwendungen  
✔ **Einfache Integration** in bestehende Steuerungsarchitekturen  

## Anwendungsszenarien

- **Sensordatenauswertung**: Erkennung von Schaltvorgängen
- **Maschinensicherheit**: Detektion von Not-Aus-Signalen
- **Prozessüberwachung**: Erkennung von Zustandsänderungen
- **Taktgenerierung**: Erzeugung von Steuerimpulsen

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_F_TRIG | E_R_TRIG | E_SWITCH |
|---------------|----------|----------|----------|
| Flankentyp    | Fallend  | Steigend | -        |
| Ereignissteuerung | Ja     | Ja       | Ja       |
| Signalauswertung | Boolesch | Boolesch | Analog/Digital |

## Fazit

Der E_F_TRIG-Baustein ist ein unverzichtbares Werkzeug für die Signalverarbeitung in Automatisierungssystemen. Seine Hauptvorteile sind:

- Zuverlässige Erkennung fallender Flanken
- Sofortige Reaktion auf Signaländerungen
- Robuste Integration in verteilte Steuerungsarchitekturen

Durch seine spezialisierte Funktionalität und Standardkonformität nach IEC 61499 eignet er sich ideal für Sicherheitsanwendungen und präzise Steuerungsaufgaben in industriellen Umgebungen. Die ereignisgesteuerte Arbeitsweise macht ihn besonders effizient in komplexen Steuerungssystemen.