# FB_TP

```{index} single: FB_TP
```

<img width="1339" height="243" alt="image" src="https://github.com/user-attachments/assets/81d9eac8-28d0-415d-9678-95305521054c" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein funktioniert nur korrekt, wenn er zyklisch aufgerufen wird.**

Der FB_TP (Timer Pulse) ist ein standardisierter Zeitgeber-Funktionsblock nach IEC 61131-3, der eine pulsierende Ausgangsfunktion bereitstellt. Der Baustein erzeugt einen Impuls mit einer definierten Zeitdauer, unabhängig von der Dauer des Eingangssignals.

![FB_TP](FB_TP.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anforderung - Startet den Zeitgeber

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - Signalisiert das Ende des Zeitimpulses

### **Daten-Eingänge**
- **IN**: Eingangssignal (BOOL) - Steuert den Start des Zeitgebers
- **PT**: Impulszeit (TIME) - Definiert die Dauer des Ausgangsimpulses

### **Daten-Ausgänge**
- **Q**: Ausgangssignal (BOOL) - Gibt den aktuellen Zustand des Zeitgebers aus
- **ET**: Verstrichene Zeit (TIME) - Zeigt die bereits verstrichene Zeit des laufenden Impulses an

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der FB_TP funktioniert als monostabiler Multivibrator (One-Shot). Bei einem positiven Flanke am IN-Eingang startet der Zeitgeber und setzt den Q-Ausgang für die in PT definierte Zeitdauer auf TRUE. Die verstrichene Zeit wird kontinuierlich am ET-Ausgang ausgegeben. Nach Ablauf der eingestellten Zeit PT wird Q automatisch auf FALSE zurückgesetzt, unabhängig vom Zustand des IN-Eingangs.

## Technische Besonderheiten
- Zeitmessung erfolgt unabhängig von der Dauer des Eingangssignals
- ET-Ausgang zeigt die aktuelle Laufzeit des Impulses
- Sofortige Reaktion auf positive Flanke am IN-Eingang
- Automatische Rücksetzung nach Zeitablauf

## Zustandsübergänge
1. **Ruhezustand**: IN = FALSE, Q = FALSE, ET = 0
2. **Start**: Positive Flanke an IN → Q = TRUE, ET-Zählung beginnt
3. **Laufzeit**: Q bleibt TRUE während ET < PT
4. **Ende**: Wenn ET ≥ PT → Q = FALSE, ET-Zählung stoppt

## Anwendungsszenarien
- Erzeugung von genau definierten Impulsen
- Zeitgesteuerte Steuerungsabläufe
- Verzögerungsschaltungen
- Taktgenerierung für Prozesssteuerungen
- Sicherheitszeitüberwachung

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **FB_TON**: Einschaltverzögerung - Q wird erst nach Ablauf von PT aktiv
- **FB_TOF**: Ausschaltverzögerung - Q bleibt nach IN-Rücksetzung noch für PT aktiv
- **FB_TP**: Impulsgeber - Erzeugt einen festen Impuls unabhängig von IN






## 🛠️ Zugehörige Übungen

* [Uebung_020f2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020f2.md)
* [Uebung_020f2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f2_AX.md)

## Fazit
Der FB_TP ist ein essentieller Baustein für zeitgesteuerte Anwendungen in der Automatisierungstechnik. Seine einfache Handhabung und zuverlässige Funktionsweise machen ihn ideal für Anwendungen, bei denen präzise Zeitimpulse benötigt werden. Die klare Trennung von Startimpuls und Impulsdauer ermöglicht flexible Steuerungskonzepte.