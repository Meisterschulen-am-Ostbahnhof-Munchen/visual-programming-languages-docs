# AX_RS

```{index} single: AX_RS
```

<img width="1188" height="282" alt="image" src="https://github.com/user-attachments/assets/96fcd1e8-c68a-4b6e-a8f0-f615322d30e2" />

* * * * * * * * * *
## Einleitung
Der AX_RS Funktionsblock ist ein ereignisgesteuertes bistabiles Element (Flip-Flop) nach dem RS-Prinzip. Es handelt sich um einen Basic Function Block, der einen Set-Reset-Mechanismus implementiert und über Adapter-Schnittstellen kommuniziert.

![AX_RS](AX_RS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **R**: Reset-Ereignis - setzt den Ausgang Q zurück
- **S**: Set-Ereignis - setzt den Ausgang Q

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **Q**: Adapter vom Typ `adapter::types::unidirectional::AX` - repräsentiert den Wert des Flip-Flops

## Funktionsweise
Der AX_RS Funktionsblock arbeitet als RS-Flip-Flop mit folgenden Eigenschaften:
- Bei Eintreffen eines S-Ereignis (Set) wird der Ausgang Q auf TRUE gesetzt
- Bei Eintreffen eines R-Ereignis (Reset) wird der Ausgang Q auf FALSE gesetzt
- Der Zustand bleibt erhalten, bis ein gegenteiliges Ereignis eintrifft

## Technische Besonderheiten und Normenvergleich

Wie bei allen ereignisgesteuerten bistabilen Elementen in der IEC 61499 (siehe auch Anmerkung 8 in Tabelle A.1 der DIN EN 61499-1) gibt es hier keine inhärente "Dominanz" eines Eingangs, wie man sie von der IEC 61131-3 kennt.

- **Vergleich zur IEC 61131-3**: Siehe [RS (Bistabil, vorrangig rücksetzen)](../../../../Vergleich/IEC61131_3/RS_ALT.md). Während in der klassischen SPS-Welt bei gleichzeitigem TRUE an S und R1 das Rücksetzen gewinnt, wird in der IEC 61499 jedes Ereignis nacheinander verarbeitet. Der Endzustand hängt davon ab, welches Ereignis zuletzt in der Ausführungskette (ECC) abgearbeitet wurde.
- **Funktionale Identität**: `AX_RS` ist funktional identisch zu [AX_SR](AX_SR.md). Die unterschiedliche Benennung dient lediglich der Konsistenz zur klassischen Programmierung und der besseren Lesbarkeit im Schaltplan.
- **Adapter-Kommunikation**: Der Baustein gibt seinen Zustand ausschließlich über den Adapter `Q` (Typ `AX`) aus. Eine Änderung von `Q` löst das Ereignis `Q.E1` aus.

## Zustandsübersicht
Der Funktionsblock verfügt über drei Zustände im ECC:

1. **START**: Initialzustand
2. **SET**: Zustand nach Set-Operation (Q.D1 = TRUE)
3. **RESET**: Zustand nach Reset-Operation (Q.D1 = FALSE)

**Zustandsübergänge:**
- START → SET: bei S-Ereignis
- SET → RESET: bei R-Ereignis
- RESET → SET: bei S-Ereignis

## Anwendungsszenarien
- Speicherung von binären Zuständen mit Adapter-Ausgabe
- Implementierung von Verriegelungsschaltungen in verteilten Systemen
- Zustandsspeicherung in sequentiellen Abläufen
- Signalverarbeitung in ereignisgesteuerten Systemen

## Verwandte Bausteine
- **[AX_SR](AX_SR.md)**: Funktional identisch, Eingänge im Symbol vertauscht.
- **[E_RS](../../../../StandardLibraries/events/E_RS.md)**: Das Standard-Äquivalent mit direkten Daten-/Ereignisausgängen statt Adaptern.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Flip-Flop-Implementierungen:
- Verwendet Adapter-basierte Kommunikation statt direkter Datenausgänge
- Ereignisgesteuerte Zustandsänderungen
- Einfache RS-Logik ohne zusätzliche Takt- oder Enable-Signale

Vergleich mit [E_RS](../../../../StandardLibraries/events/E_RS.md)






## Zugehörige Übungen

* [Uebung_006b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006b_AX.md)
* [Uebung_020a_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020a_AX.md)
* [Uebung_020b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020b_AX.md)
* [Uebung_020d_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020d_AX.md)

## Fazit
Der AX_RS Funktionsblock bietet eine einfache und effiziente Implementierung eines RS-Flip-Flops für 4diac-basierte Steuerungssysteme. Durch die Verwendung von Adaptern ermöglicht er eine flexible Integration in verschiedene Systemarchitekturen und eignet sich besonders für Anwendungen, die zuverlässige Zustandsspeicherung mit ereignisgesteuerter Aktualisierung benötigen.