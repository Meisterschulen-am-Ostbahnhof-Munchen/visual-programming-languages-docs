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

## Technische Besonderheiten und Normenvergleich

Wie bei allen ereignisgesteuerten bistabilen Elementen in der IEC 61499 (siehe auch Anmerkung 8 in Tabelle A.1 der DIN EN 61499-1) gibt es hier keine inhärente "Dominanz" eines Eingangs, wie man sie von der IEC 61131-3 kennt.

- **Vergleich zur IEC 61131-3**: Siehe [SR (Bistabil, vorrangig setzen)](../../../../Vergleich/IEC61131_3/SR_ALT.md). Während in der klassischen SPS-Welt bei gleichzeitigem TRUE an S1 und R das Setzen gewinnt, wird in der IEC 61499 jedes Ereignis nacheinander verarbeitet. Der Endzustand hängt davon ab, welches Ereignis zuletzt in der Ausführungskette (ECC) abgearbeitet wurde.
- **Funktionale Identität**: `AX_SR` ist funktional identisch zu [AX_RS](AX_RS.md). Die unterschiedliche Benennung und Anordnung der Pins dient lediglich der besseren Orientierung für Entwickler, die an die IEC 61131-3 gewöhnt sind.
- **Adapter-Kommunikation**: Der Baustein stellt seinen Zustand über den Adapter `Q` zur Verfügung.

## Zustandsübersicht
1. **START**: Initialzustand
2. **SET**: Zustand nach S-Ereignis, Ausgang Q.D1 = TRUE
3. **RESET**: Zustand nach R-Ereignis, Ausgang Q.D1 = FALSE

Zustandsübergänge:
- START → SET: Bei S-Ereignis
- SET → RESET: Bei R-Ereignis
- RESET → SET: Bei S-Ereignis

## Anwendungsszenarien
- Speicherung von Schaltzuständen in verteilten Steuerungsanwendungen
- Zustandsverwaltung über Adapterschnittstellen
- Signalverarbeitung mit Speicherfunktion
- Überwachung von Betriebszuständen

## Verwandte Bausteine
- **[AX_RS](AX_RS.md)**: Funktional identisch, Eingänge im Symbol vertauscht.
- **[E_SR](../../../../StandardLibraries/events/E_SR.md)**: Das Standard-Äquivalent mit direkten Daten-/Ereignisausgängen statt Adaptern.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Speicherelementen bietet AX_SR:
- Klare Trennung von Set- und Reset-Funktionalität
- Adapter-basierte Schnittstelle für flexible Integration
- Ereignisgesteuerte Zustandsänderungen
- Einfache und robuste Zustandsverwaltung

Vergleich mit [E_SR](../../../../StandardLibraries/events/E_SR.md)



## Zugehörige Übungen

* [Uebung_004b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_004b_AX.md)
* [Uebung_006_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006_AX.md)
* [Uebung_006d_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006d_AX.md)
* [Uebung_007a3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_007a3_AX.md)
* [Uebung_008_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_008_AX.md)
* [Uebung_009_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_009_AX.md)
* [Uebung_013_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_013_AX.md)

## Fazit
Der AX_SR Funktionsblock stellt eine zuverlässige und einfach zu verwendende Lösung für bistabile Speicherfunktionen in verteilten Automatisierungssystemen dar. Durch die Verwendung von Adaptern ermöglicht er eine flexible Integration in verschiedene Systemarchitekturen und bietet eine klare, ereignisgesteuerte Schnittstelle für Set-Reset-Operationen.