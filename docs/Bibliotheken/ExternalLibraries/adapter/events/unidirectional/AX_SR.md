# AX_SR

```{index} single: AX_SR
```

<img width="1186" height="279" alt="image" src="https://github.com/user-attachments/assets/da4a5f8e-5e9f-45f9-be8f-ac02a9cdb0ca" />

* * * * * * * * * *

## Einleitung
Der AX_SR Funktionsblock ist ein ereignisgesteuertes bistabiles Element (Flip-Flop), das als Set-Reset-Speicher fungiert. Er ermöglicht das Setzen und Rücksetzen eines logischen Zustands und stellt diesen über eine Adapterschnittstelle zur Verfügung.

![AX_SR](AX_SR.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **S**: Setzt den Ausgang Q auf TRUE
- **R**: Setzt den Ausgang Q auf FALSE

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- Keine Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **Q**: Unidirektionaler Adapter vom Typ "adapter::types::unidirectional::AX", der den aktuellen Zustand des Flip-Flops bereitstellt

## Funktionsweise
Der AX_SR Funktionsblock arbeitet als Set-Reset-Flip-Flop mit folgenden Eigenschaften:
- Bei einem S-Ereignis wird der interne Zustand auf SET gesetzt und der Ausgang Q auf TRUE
- Bei einem R-Ereignis wird der interne Zustand auf RESET gesetzt und der Ausgang Q auf FALSE
- Der Zustand bleibt erhalten, bis ein gegenteiliges Ereignis eintrifft
- Die Zustandsänderungen werden über den Adapter Q kommuniziert

## Technische Besonderheiten
- Implementiert als Basic Function Block gemäß IEC 61499
- Verwendet unidirektionale Adapter für die Ausgabekommunikation
- Besitzt drei definierte Zustände: START, SET und RESET
- Initialzustand ist START

## Zustandsübersicht
1. **START**: Initialzustand
2. **SET**: Zustand nach S-Ereignis, Ausgang Q = TRUE
3. **RESET**: Zustand nach R-Ereignis, Ausgang Q = FALSE

Zustandsübergänge:
- START → SET: Bei S-Ereignis
- SET → RESET: Bei R-Ereignis
- RESET → SET: Bei S-Ereignis

## Anwendungsszenarien
- Speicherung von Schaltzuständen in Steuerungsanwendungen
- Zustandsverwaltung in sequenziellen Abläufen
- Signalverarbeitung mit Speicherfunktion
- Überwachung von Betriebszuständen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Speicherelementen bietet AX_SR:
- Klare Trennung von Set- und Reset-Funktionalität
- Adapter-basierte Schnittstelle für flexible Integration
- Ereignisgesteuerte Zustandsänderungen
- Einfache und robuste Zustandsverwaltung

Vergleich mit [E_SR](../../../../StandardLibraries/events/E_SR.md)

## Fazit
Der AX_SR Funktionsblock stellt eine zuverlässige und einfach zu verwendende Lösung für bistabile Speicherfunktionen in verteilten Automatisierungssystemen dar. Durch die Verwendung von Adaptern ermöglicht er eine flexible Integration in verschiedene Systemarchitekturen und bietet eine klare, ereignisgesteuerte Schnittstelle für Set-Reset-Operationen.