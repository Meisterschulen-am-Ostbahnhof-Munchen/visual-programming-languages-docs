# logiBUS_IXA

```{index} single: logiBUS_IXA
```

<img width="1838" height="367" alt="image" src="https://github.com/user-attachments/assets/fcf18e0e-a542-4642-a00f-1438f4caf5fb" />

* * * * * * * * * *

## Einleitung
Der logiBUS_IXA ist ein Composite-Funktionsblock zur Verarbeitung von booleschen Eingangsdaten. Er dient als Schnittstelle für digitale Eingänge und ermöglicht die Initialisierung und Abfrage von Eingangssignalen über standardisierte Service-Schnittstellen.

![logiBUS_IXA](logiBUS_IXA.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis mit den zugehörigen Daten QI, PARAMS und Input
- **REQ**: Service-Anfrageereignis mit dem zugehörigen Datenwert QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den zugehörigen Datenwerten QO und STATUS

### **Daten-Eingänge**
- **QI**: Boolescher Ereignis-Eingangsqualifizierer
- **PARAMS**: Service-Parameter als Zeichenkette
- **Input**: Identifiziert die Eingänge Q1 bis Q8 mit dem Typ logiBUS_DI_S und Initialwert "Invalid"

### **Daten-Ausgänge**
- **QO**: Boolescher Ereignis-Ausgangsqualifizierer
- **STATUS**: Service-Status als Zeichenkette

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ AX für die Eingangsdatenverarbeitung

## Funktionsweise
Der Composite-Funktionsblock logiBUS_IXA kapselt den Basisfunktionsblock logiBUS_IX und erweitert dessen Funktionalität durch zusätzliche Adapter-Schnittstellen. Bei INIT-Ereignissen werden die Parameter an den internen IX-Block weitergeleitet, der die Initialisierung durchführt. Die IND-Ereignisse des IX-Blocks werden an den Eingangsadapter IN weitergegeben, während die Datenverbindungen die entsprechende Signalverarbeitung sicherstellen.

## Technische Besonderheiten
- Verwendet den spezifischen Datentyp logiBUS_DI_S für die Eingangsidentifikation
- Implementiert standardisierte Service-Schnittstellen gemäß 61499-2
- Unterstützt Parameterübergabe via STRING-Datentyp
- Bietet Statusrückmeldungen über STATUS-Ausgang

## Zustandsübersicht
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Nicht initialisiert**: Vor dem INIT-Ereignis
2. **Initialisiert und betriebsbereit**: Nach erfolgreicher INIT-Bestätigung

## Anwendungsszenarien
- Anbindung digitaler Eingänge in Automatisierungssystemen
- Integration in logiBUS-basierte Steuerungsarchitekturen
- Verwendung in SPS-Systemen mit booleschen Signalverarbeitungsanforderungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsblöcken bietet logiBUS_IXA erweiterte Service-Funktionalitäten mit Parametrierungsmöglichkeiten und Statusrückmeldungen. Die Composite-Struktur ermöglicht eine bessere Wiederverwendbarkeit und erweiterte Diagnosefähigkeiten.



## Zugehörige Übungen

* [Uebung_001_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_001_AX.md)
* [Uebung_001_AX_b](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_001_AX_b.md)
* [Uebung_001c_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_001c_AX.md)
* [Uebung_002_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002_AX.md)
* [Uebung_002a2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a2_AX.md)
* [Uebung_002a3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
* [Uebung_002a5_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a5_AX.md)
* [Uebung_002a5b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a5b_AX.md)
* [Uebung_002a6_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a6_AX.md)
* [Uebung_002a7_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a7_AX.md)
* [Uebung_002a_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a_AX.md)
* [Uebung_002b3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_003_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_003_AX.md)
* [Uebung_003a0_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_003a0_AX.md)
* [Uebung_003a_AX_sub](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_003a_AX_sub.md)
* [Uebung_003c_sub_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_003c_sub_AX.md)
* [Uebung_003d_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_003d_AX.md)
* [Uebung_005_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_005_AX.md)
* [Uebung_006e1_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006e1_AX.md)
* [Uebung_006e2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006e2_AX.md)
* [Uebung_020a_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020a_AX.md)
* [Uebung_020b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020b_AX.md)
* [Uebung_020c3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020c3_AX.md)
* [Uebung_020c_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020c_AX.md)
* [Uebung_020d_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020d_AX.md)
* [Uebung_020e2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020e2_AX.md)
* [Uebung_020e_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020e_AX.md)
* [Uebung_020f2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f2_AX.md)
* [Uebung_020f_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f_AX.md)
* [Uebung_020g_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020g_AX.md)
* [Uebung_020i_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020i_AX.md)
* [Uebung_020j2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j2_AX.md)
* [Uebung_020j_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j_AX.md)
* [Uebung_090a1_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_090a1_AX.md)
* [Uebung_090a2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_090a2_AX.md)
* [Uebung_094a_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_094a_AX.md)
* [Uebung_095_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_095_AX.md)
* [Uebung_103](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_103c](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c.md)
* [Uebung_103c2](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c2.md)
* [Uebung_160_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Uebung_160b2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Uebung_177_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_177_AX.md)
* [Uebung_178_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_178_AX.md)

## Fazit
Der logiBUS_IXA Funktionsblock stellt eine robuste und flexible Lösung für die Verarbeitung digitaler Eingangssignale in 4diac-basierten Automatisierungssystemen dar. Durch seine standardisierten Schnittstellen und erweiterten Service-Funktionen eignet er sich besonders für komplexe Anwendungen mit hohen Anforderungen an Diagnose und Parametrierbarkeit.