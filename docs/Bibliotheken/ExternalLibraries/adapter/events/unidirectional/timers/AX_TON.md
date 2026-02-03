# AX_TON

```{index} single: AX_TON
```

<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

AX_TON ist ein standardisierter Timer-Funktionsblock, der eine Einschaltverzögerung (On-Delay Timing) realisiert. Der Baustein wartet nach Aktivierung eine definierte Zeit ab, bevor er das Ausgangssignal setzt.

![AX_TON](AX_TON.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereigniseingänge vorhanden

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge vorhanden

### **Daten-Eingänge**
- **PT** (TIME): Prozesszeit - definiert die Verzögerungsdauer

### **Daten-Ausgänge**
- Keine direkten Datenausgänge vorhanden

### **Adapter**
- **IN** (Input-Adapter): Empfängt Eingangsereignisse und -daten
- **Q** (Output-Adapter): Sendet Ausgangsereignisse und -daten

## Funktionsweise
Der AX_TON-Block arbeitet als Einschaltverzögerungstimer. Bei Empfang eines Eingangsereignisses über den IN-Adapter startet der interne Timer. Nach Ablauf der eingestellten Prozesszeit (PT) wird über den Q-Adapter ein Ausgangsereignis mit dem Status TRUE gesendet. Wird der Eingang während der Zeitüberwachung deaktiviert, wird der Timer zurückgesetzt.

## Technische Besonderheiten
- Implementiert auf Basis des E_TON-Standardtimerblocks
- Verwendet unidirektionale Adapter für Ein- und Ausgänge
- Unterstützt TIME-Datentyp für präzise Zeitsteuerung
- Kompatibel mit IEC 61499-2 Standard

## Zustandsübersicht
1. **Ruhezustand**: Kein aktiver Timer, Ausgang FALSE
2. **Aktivierungszustand**: Timer läuft nach Eingangssignal
3. **Verzögerungszustand**: Timer zählt ab, Ausgang bleibt FALSE
4. **Auslösezustand**: Nach Zeitablauf, Ausgang wird TRUE

## Anwendungsszenarien
- Steuerung von zeitverzögerten Prozessstarts
- Überwachung von Mindestlaufzeiten
- Verzögerte Aktivierung von Maschinenkomponenten
- Sicherheitsrelevante Zeitüberwachungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Timer-Blöcken bietet AX_TON eine standardisierte Schnittstelle durch Adapter, was die Wiederverwendbarkeit und modulare Integration in größere Steuerungssysteme erleichtert.

Vergleich mit [E_TON](../../../../../StandardLibraries/events/timer/E_TON.md)






## 🛠️ Zugehörige Übungen

* [Uebung_020c_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020c_AX.md)
* [Uebung_160b2_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b2_AX.md)

## Fazit
AX_TON ist ein robuster und zuverlässiger Timer-Baustein für Einschaltverzögerungen, der durch seine standardisierte Adapter-basierte Schnittstelle eine flexible Integration in verschiedene Automatisierungssysteme ermöglicht.