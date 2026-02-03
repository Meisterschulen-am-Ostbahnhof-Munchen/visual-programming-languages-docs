# AX_OR_2

```{index} single: AX_OR_2
```

<img width="963" height="265" alt="image" src="https://github.com/user-attachments/assets/3c1d3b81-2420-46cc-b7cf-fc6828db919c" />

* * * * * * * * * *
## Einleitung
Der AX_OR_2 Funktionsblock ist ein generischer Baustein zur Berechnung der booleschen ODER-Verknüpfung. Er verarbeitet zwei Eingangssignale und gibt das logische ODER-Ergebnis aus. Der Baustein ist speziell für die Verwendung in Automatisierungssystemen konzipiert.

![AX_OR_2](AX_OR_2.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
**Eingangsadapter:**
- **IN1** - ODER Eingang 1 (Adapter-Typ: adapter::types::unidirectional::AX)
- **IN2** - ODER Eingang 2 (Adapter-Typ: adapter::types::unidirectional::AX)

**Ausgangsadapter:**
- **OUT** - ODER Ergebnis (Adapter-Typ: adapter::types::unidirectional::AX)

## Funktionsweise
Der AX_OR_2 Funktionsblock führt eine logische ODER-Verknüpfung zwischen den beiden Eingangssignalen IN1 und IN2 durch. Das Ergebnis wird über den Ausgangsadapter OUT ausgegeben. Die Verarbeitung erfolgt kontinuierlich, sobald Eingangssignale verfügbar sind.

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klasse 'GEN_AX_OR'
- Verwendet unidirektionale Adapter für die Signalübertragung
- Implementiert als Teil des Packages "adapter::booleanOperators"
- Unterstützt die Eclipse 4diac Standard-Spezifikation 61499-2

## Zustandsübersicht
Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt AX_OR_2 keinen internen Zustand. Die Ausgabe wird ausschließlich von den aktuellen Eingangswerten bestimmt.

## Anwendungsszenarien
- Sicherheitskreise mit redundanten Sensoren
- Parallele Steuerungsbefehle
- Überwachungssysteme mit mehreren Eingangssignalen
- Logische Verknüpfungen in Steuerungsalgorithmen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen ODER-Bausteinen zeichnet sich AX_OR_2 durch seine Adapter-basierte Schnittstelle aus, die eine flexible Integration in verschiedene Systemarchitekturen ermöglicht. Die unidirektionalen Adapter gewährleisten eine klare Signalflussrichtung.

Vergleich mit [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md)






## Zugehörige Übungen

* [Uebung_002a3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
* [Uebung_002b3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_035a2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_160_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Uebung_160b2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Uebung_160b_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Fazit
Der AX_OR_2 Funktionsblock bietet eine zuverlässige und einfach zu integrierende Lösung für boolesche ODER-Verknüpfungen in Automatisierungssystemen. Seine Adapter-basierte Architektur ermöglicht eine flexible Verwendung in verschiedenen Steuerungskontexten.