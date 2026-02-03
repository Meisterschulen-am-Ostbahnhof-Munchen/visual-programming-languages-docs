# Softkey_IXA

```{index} single: Softkey_IXA
```
## 🎧 Podcast

* [ISO 11783-6: Softkeys und das Virtual Terminal verstehen – Dein Schlüssel zur Landmaschinen-Mechatronik](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISO-11783-6-Softkeys-und-das-Virtual-Terminal-verstehen--Dein-Schlssel-zur-Landmaschinen-Mechatronik-e36a8b0)

## Einleitung
Softkey_IXA ist ein Composite-Funktionsblock zur Verarbeitung von booleschen Eingabedaten. Der Baustein dient als Schnittstelle für Softkey-Operationen und ermöglicht die Initialisierung und Abfrage von Eingabezuständen über standardisierte ISOBUS-Kommunikationsprotokolle.

![Softkey_IXA](Softkey_IXA.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis mit den zugehörigen Daten QI, PARAMS und u16ObjId
- **REQ**: Service-Anfrageereignis mit dem Qualifier QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den Ausgabedaten QO und STATUS

### **Daten-Eingänge**
- **QI**: BOOL - Event Input Qualifier
- **PARAMS**: STRING - Service-Parameter
- **u16ObjId**: UINT - Objekt-ID mit Initialwert ID_NULL

### **Daten-Ausgänge**
- **QO**: BOOL - Event Output Qualifier
- **STATUS**: STRING - Service-Status

### **Adapter**
- **IN**: Adapter vom Typ adapter::types::unidirectional::AX für unidirektionale Kommunikation

## Funktionsweise
Der Composite-Funktionsblock Softkey_IXA kapselt den internen Funktionsblock Softkey_IX und dient als Vermittler zwischen externen Aufrufen und der eigentlichen Softkey-Funktionalität. Bei Initialisierung (INIT) werden die Parameter an den internen Baustein weitergeleitet, und bei Service-Anfragen (REQ) werden die entsprechenden Abfragen durchgeführt. Der Adapter IN ermöglicht die Kommunikation mit externen Komponenten.

## Technische Besonderheiten
- Verwendet ISOBUS-spezifische Typen und Konstanten
- Unterstützt Objekt-Identifikation über u16ObjId
- Flexible Parameterübergabe via STRING-Parameter
- Unidirektionale Adapter-Schnittstelle für erweiterte Kommunikation

## Zustandsübersicht
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Initialisierungszustand**: Verarbeitung der INIT-Ereignisse mit Parameterübergabe
2. **Service-Zustand**: Bearbeitung von REQ-Anfragen und Rückgabe der Ergebnisse

## Anwendungsszenarien
- Landwirtschaftliche Bedienterminals mit Softkey-Funktionalität
- ISOBUS-kompatible Steuersysteme
- Anwendungen mit booleschen Eingabeabfragen
- Systeme mit parametrierbaren Service-Schnittstellen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen booleschen Eingabeblöcken bietet Softkey_IXA erweiterte ISOBUS-Kompatibilität, parametrierbare Service-Schnittstellen und Adapter-basierte Erweiterbarkeit. Die Composite-Struktur ermöglicht eine klare Trennung zwischen Schnittstellenlogik und Kernfunktionalität.


## Zugehörige Übungen

* [Uebung_010_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010_AX.md)
* [Uebung_010a4_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010a4_AX.md)
* [Uebung_010a_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010a_AX.md)
* [Uebung_010b4_sub_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010b4_sub_AX.md)
* [Uebung_010b5_sub_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010b5_sub_AX.md)
* [Uebung_010c2_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c2_AX.md)
* [Uebung_010c3_sub_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c3_sub_AX.md)
* [Uebung_010c4_sub_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c4_sub_AX.md)
* [Uebung_010c_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c_AX.md)

## Fazit
Softkey_IXA stellt einen robusten und erweiterbaren Composite-Funktionsblock für Softkey-Operationen in ISOBUS-Umgebungen dar. Durch die klare Schnittstellentrennung und Adapter-Unterstützung eignet er sich ideal für komplexe Steuerungssysteme in der Agrartechnik.