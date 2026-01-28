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

## Technische Besonderheiten
- Implementiert als Basic Function Block mit drei Zuständen
- Verwendet unidirektionale Adapter für die Ausgabe
- Der Ausgabewert wird über den Adapter Q.D1 transportiert
- Ereignisausgaben werden über Q.E1 signalisiert

## Zustandsübersicht
Der Funktionsblock verfügt über drei Zustände:

1. **START**: Initialzustand
2. **SET**: Zustand nach Set-Operation (Q = TRUE)
3. **RESET**: Zustand nach Reset-Operation (Q = FALSE)

**Zustandsübergänge:**
- START → SET: bei S-Ereignis
- SET → RESET: bei R-Ereignis
- RESET → SET: bei S-Ereignis

## Anwendungsszenarien
- Speicherung von binären Zuständen in Steuerungsanwendungen
- Implementierung von Verriegelungsschaltungen
- Zustandsspeicherung in sequentiellen Abläufen
- Signalverarbeitung in ereignisgesteuerten Systemen

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