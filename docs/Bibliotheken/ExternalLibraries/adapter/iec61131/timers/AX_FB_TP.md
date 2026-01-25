# AX_FB_TP

```{index} single: AX_FB_TP
```

<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein funktioniert nur korrekt, wenn er zyklisch aufgerufen wird.**

AX_FB_TP ist ein standardisierter Timer-Funktionsblock gemäß IEC 61131-3, der einen Impuls (Pulse) mit definierter Länge erzeugt. Bei einer steigenden Flanke am Eingang wird ein Ausgangsimpuls für die festgelegte Zeitdauer generiert.

![AX_FB_TP](AX_FB_TP.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Event): Normal Execution Request (übernimmt den Wert von PT); ruft den Baustein auf (muss zyklisch aufgerufen werden)

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge vorhanden

### **Daten-Eingänge**
- **PT** (TIME): Pulszeit - definiert die Dauer des Ausgangsimpulses

### **Daten-Ausgänge**
- **ET** (TIME): Abgelaufene Zeit (Elapsed Time)

### **Adapter**
- **IN** (Socket): Empfängt Eingangsereignisse und -daten (Typ: `adapter::types::unidirectional::AX`)
- **Q** (Plug): Sendet Ausgangsereignisse und -daten (Typ: `adapter::types::unidirectional::AX`)

## Funktionsweise
Der AX_FB_TP-Block arbeitet als Impulsgeber:
1. Bei einer steigenden Flanke (Wechsel von FALSE auf TRUE) am IN-Adapter wechselt der Ausgang am Q-Adapter sofort auf TRUE.
2. Der interne Timer startet und läuft für die Dauer PT.
3. Der Ausgang am Q-Adapter bleibt für die gesamte Zeit PT auf TRUE, unabhängig davon, ob das Eingangssignal am IN-Adapter zwischenzeitlich wieder auf FALSE wechselt.
4. Während der Impuls läuft (solange ET < PT), haben weitere Flanken am Eingang keinen Einfluss auf den laufenden Timer (nicht retriggerbar).
5. Nach Ablauf der Zeit PT wechselt der Ausgang am Q-Adapter zurück auf FALSE.
6. Der Datenausgang ET zeigt die Zeit an, die seit dem Start des Impulses vergangen ist.

## Technische Besonderheiten
- Implementiert auf Basis des IEC 61131-3 TP-Standards
- Verwendet unidirektionale Adapter für eine saubere Kapselung in adapterbasierten Architekturen
- Nicht retriggerbar während der aktiven Pulsphase
- Präzise Zeitsteuerung durch Verwendung des TIME-Datentyps

## Zustandsübersicht
1. **Ruhezustand**: IN ist FALSE, Q ist FALSE, ET ist 0.
2. **Impulsphase**: Steigende Flanke an IN detektiert, Q ist TRUE, ET steigt bis PT.
3. **Abschluss**: ET hat PT erreicht, Q wechselt auf FALSE.
4. **Warten auf Reset**: Wenn IN noch TRUE ist, bleibt Q FALSE und ET bleibt auf PT, bis IN wieder FALSE wird.

## Anwendungsszenarien
- Erzeugung von zeitlich begrenzten Steuersignalen (z. B. Startimpuls für einen Motor)
- Zeitliche Begrenzung von Bedienvorgängen
- Generierung von definierten Signalpulsen in der Prozessautomatisierung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zum [AX_PULSE](../../events/unidirectional/timers/AX_PULSE.md) bietet AX_FB_TP die klassische IEC 61131-3 TP-Charakteristik inklusive dem ET-Statusausgang.



## Zugehörige Übungen

* [Uebung_020f2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f2_AX.md)

## Fazit
AX_FB_TP ist der Standardbaustein für die Erzeugung stabiler, zeitlich exakt definierter Impulse in einer adapterbasierten Umgebung.