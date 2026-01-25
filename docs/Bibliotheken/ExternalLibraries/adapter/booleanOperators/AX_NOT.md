# AX_NOT

```{index} single: AX_NOT
```

<img width="820" height="231" alt="image" src="https://github.com/user-attachments/assets/dc31ab7f-e7b2-434e-88d6-7cf13a88d725" />

* * * * * * * * * *

## Einleitung
Der AX_NOT Funktionsblock ist ein standardisierter boolescher NOT-Operator, der gemäß der Norm IEC 61131-3 implementiert wurde. Dieser Baustein führt eine logische Negation (NOT-Operation) auf den Eingangswerten durch und gibt das invertierte Ergebnis aus.

![AX_NOT](AX_NOT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Funktionsblock verfügt über keine direkten Ereignis-Eingänge.

### **Ereignis-Ausgänge**
Der Funktionsblock verfügt über keine direkten Ereignis-Ausgänge.

### **Daten-Eingänge**
Der Funktionsblock verfügt über keine direkten Daten-Eingänge.

### **Daten-Ausgänge**
Der Funktionsblock verfügt über keine direkten Daten-Ausgänge.

### **Adapter**
- **IN** (Socket): Eingangsadapter vom Typ `adapter::types::unidirectional::AX` - dient zur Übertragung der Eingangsdaten
- **OUT** (Plug): Ausgangsadapter vom Typ `adapter::types::unidirectional::AX` - dient zur Ausgabe der verarbeiteten Daten

## Funktionsweise
Der AX_NOT Funktionsblock führt eine logische Negation auf den über den IN-Adapter empfangenen booleschen Werten durch. Das Ergebnis der NOT-Operation wird über den OUT-Adapter ausgegeben. Die Verarbeitung erfolgt bidirektional zwischen Anwendungs- und Ressourcenebene.

## Technische Besonderheiten
- Implementiert gemäß IEC 61131-3 Standard für boolesche Funktionen
- Verwendet unidirektionale AX-Adapter für die Datenübertragung
- Arbeitet mit dem Package `adapter::booleanOperators`
- Unterstützt TypeHash-Funktionalität für Typidentifikation

## Zustandsübersicht
Der Funktionsblock arbeitet zustandslos und führt die NOT-Operation direkt auf den eingehenden Daten durch, ohne internen Zustand zu speichern.

## Anwendungsszenarien
- Logische Invertierung von booleschen Signalen in Steuerungsanwendungen
- Signalumkehr in Automatisierungssystemen
- Verwendung in kombinatorischen Schaltungen
- Integration in größere Steuerungslogiken zur Signalverarbeitung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen booleschen Operatoren wie AND oder OR führt AX_NOT ausschließlich die Negationsoperation durch. Die Verwendung von Adaptern anstelle direkter Ein-/Ausgänge ermöglicht eine flexiblere Integration in komplexere Systemarchitekturen.

Vergleich mit [F_NOT](../../../StandardLibraries/iec61131-3/bitwiseOperators/F_NOT.md)


## Zugehörige Übungen

* [Uebung_006a3_sub_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006a3_sub_AX.md)

## Fazit
Der AX_NOT Funktionsblock bietet eine zuverlässige und standardkonforme Implementierung der booleschen NOT-Operation. Durch die Adapter-basierte Schnittstellengestaltung eignet er sich besonders für modulare Systemdesigns und ermöglicht eine einfache Integration in bestehende Automatisierungslösungen.