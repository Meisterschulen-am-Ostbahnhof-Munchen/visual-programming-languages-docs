# E_DELAY

```{index} single: E_DELAY
```
## 🎧 Podcast

* [E_DELAY in IEC 61499: Präzise, Abbrechbare Zeitverzögerung in Steuerungssystemen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_DELAY-in-IEC-61499-Przise--Abbrechbare-Zeitverzgerung-in-Steuerungssystemen-e3674le)

## Einleitung
Der **E_DELAY** ist ein zentraler Funktionsbaustein der IEC 61499 Norm für industrielle Steuerungssysteme. Als ereignisgesteuerter Timer ermöglicht er die verzögerte Auslösung von Ereignissen mit konfigurierbarer Zeitspanne und Abbruchmöglichkeit. Dieser Baustein findet breite Anwendung in zeitgesteuerten Automatisierungsprozessen.

![E_DELAY](E_DELAY.svg)

## Struktur des E_DELAY-Bausteins

### Schnittstelle (Interface)

**Ereignis-Eingänge:**
- `START`: Initialisiert die Verzögerung
- `STOP`: Bricht die aktive Verzögerung ab

**Ereignis-Ausgänge:**
- `EO` (Event Output): Wird nach Ablauf der Verzögerung ausgelöst

**Daten-Eingänge:**
- `DT` (Delay Time): TIME-Wert für die Verzögerungsdauer

## Funktionsweise

1. **Verzögerungsstart:**
   - Bei `START`-Ereignis beginnt der Timer mit der eingestellten Zeit `DT`
   - Während der Laufzeit werden weitere `START`-Ereignisse ignoriert

2. **Verzögerungsabbruch:**
   - `STOP`-Ereignis bricht die aktive Verzögerung sofort ab
   - Kein `EO`-Ereignis wird generiert

3. **Verzögerungsabschluss:**
   - Nach exakt `DT` wird das `EO`-Ereignis ausgelöst
   - Bei DT ≤ T#0s erfolgt sofortige Auslösung ohne Verzögerung

## Technische Besonderheiten

✔ **Präzise Zeitsteuerung** (millisekundengenaue Verzögerung)
✔ **Abbruchfunktion** für flexible Prozesssteuerung
✔ **Ereignisgesteuert** (kein zyklischer Aufruf erforderlich)
✔ **Echtzeitfähig** für industrielle Anwendungen

## Anwendungsszenarien

- **Maschinensicherheit**: Verzögerte Abschaltung von Anlagen
- **Prozesssteuerung**: Zeitgesteuerte Prozessschritte
- **Alarmmanagement**: Verzögerte Störmeldungen
- **Testautomation**: Zeitgesteuerte Testsequenzen

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_DELAY | E_CYCLE | E_PULSE |
|---------------|---------|---------|---------|
| Funktionsprinzip | Einmalverzögerung | Dauerzyklus | Einmalimpuls |
| Abbruchmöglichkeit | Ja | Ja | Nein |
| Zeitparameter | DT (Verzögerung) | DT (Zykluszeit) | PT (Impulsdauer) |






## Zugehörige Übungen

* [Uebung_018](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_018.md)
* [Uebung_020b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020b.md)
* [Uebung_020b_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020b_AX.md)
* [Uebung_020d](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020d.md)
* [Uebung_020d_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020d_AX.md)
* [Uebung_024](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_024.md)
* [Uebung_025](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_025.md)
* [Uebung_026](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_026.md)
* [Uebung_160b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_160b.md)
* [Uebung_160b_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Fazit

Der E_DELAY-Baustein ist ein unverzichtbares Werkzeug für zeitgesteuerte Automatisierungsprozesse. Seine Hauptvorteile sind:

- Präzise und flexible Zeitsteuerung
- Sofortige Reaktion auf Steuerereignisse
- Robuste Integration in verteilte Steuerungsarchitekturen

Durch seine zuverlässige Funktionsweise und Standardkonformität nach IEC 61499 eignet er sich ideal für Sicherheitsanwendungen und komplexe Prozesssteuerungen in industriellen Umgebungen. Die Abbruchfunktion macht ihn besonders wertvoll für flexible Produktionsszenarien.