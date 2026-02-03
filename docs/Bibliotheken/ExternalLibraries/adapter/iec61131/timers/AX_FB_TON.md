# AX_FB_TON

```{index} single: AX_FB_TON
```

<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein funktioniert nur korrekt, wenn er zyklisch aufgerufen wird.**

AX_FB_TON ist ein standardisierter Timer-Funktionsblock gemäß IEC 61131-3, der eine Einschaltverzögerung (On-Delay Timing) realisiert und über Adapter-Schnittstellen verfügt. Der Baustein wartet nach Aktivierung eine definierte Zeit ab, bevor er das Ausgangssignal setzt, und stellt die abgelaufene Zeit zur Verfügung.

![AX_FB_TON](AX_FB_TON.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Event): Normal Execution Request (übernimmt den Wert von PT); ruft den Baustein auf (muss zyklisch aufgerufen werden)

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge vorhanden (Steuerung über Adapter)

### **Daten-Eingänge**
- **PT** (TIME): Prozesszeit - definiert die Verzögerungsdauer

### **Daten-Ausgänge**
- **ET** (TIME): Abgelaufene Zeit (Elapsed Time)

### **Adapter**
- **IN** (Socket): Empfängt Eingangsereignisse und -daten (Typ: `adapter::types::unidirectional::AX`)
- **Q** (Plug): Sendet Ausgangsereignisse und -daten (Typ: `adapter::types::unidirectional::AX`)

## Funktionsweise
Der AX_FB_TON-Block arbeitet als Einschaltverzögerungstimer. Bei Empfang eines Signals über den IN-Adapter startet der interne Timer.
1. Wenn der Eingang am IN-Adapter TRUE wird, beginnt der Timer zu laufen.
2. Nach Ablauf der eingestellten Prozesszeit (PT) wird der Ausgang am Q-Adapter TRUE.
3. Der Datenausgang ET zeigt die Zeit an, die seit dem Start des Timers vergangen ist, bis PT erreicht ist.
4. Wird der Eingang am IN-Adapter FALSE, wird der Timer zurückgesetzt und der Ausgang am Q-Adapter wird ebenfalls FALSE.

## Technische Besonderheiten
- Implementiert auf Basis des IEC 61131-3 TON-Standards
- Verwendet unidirektionale Adapter für die Integration in adapterbasierte Architekturen
- Bietet einen ET-Ausgang zur Überwachung des Zeitverlaufs
- Kompatibel mit IEC 61131-3 und IEC 61499

## Zustandsübersicht
1. **Ruhezustand**: IN ist FALSE, Timer inaktiv, Q ist FALSE, ET ist 0.
2. **Timing-Zustand**: IN ist TRUE, Timer läuft, ET steigt an, Q ist FALSE.
3. **Ausgelöst**: IN ist TRUE, ET hat PT erreicht, Q ist TRUE.
4. **Reset**: IN wird FALSE, Timer stoppt, Q wird FALSE, ET wird 0.

## Anwendungsszenarien
- Klassische Einschaltverzögerungen in der SPS-Programmierung
- Überwachung von Prozesszeiten mit Visualisierung der Restlaufzeit (über ET)
- Kaskadierung von Zeitabläufen in adapterbasierten Systemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zum [AX_TON](../../events/unidirectional/timers/AX_TON.md) bietet AX_FB_TON zusätzlich den Ausgang **ET** für die abgelaufene Zeit und folgt strikt dem Verhalten des IEC 61131-3 TON Blocks, während AX_TON eher auf den IEC 61499 E_TON optimiert ist.





## Zugehörige Übungen

* [Uebung_020c3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020c3_AX.md)

## Fazit
AX_FB_TON kombiniert das bewährte Verhalten des IEC 61131-3 TON-Timers mit der Flexibilität von Adapter-Schnittstellen und ermöglicht so eine präzise Zeitsteuerung mit Rückmeldung des aktuellen Zeitstatus.