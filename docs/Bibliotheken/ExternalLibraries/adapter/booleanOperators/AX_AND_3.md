# AX_AND_3

```{index} single: AX_AND_3
```

<img width="1009" height="296" alt="image" src="https://github.com/user-attachments/assets/42842c64-6ed6-4728-8d41-60a0c3f2ab31" />

* * * * * * * * * *

## Einleitung
Der AX_AND_3 ist ein generischer Funktionsblock zur Berechnung einer logischen UND-Verknüpfung mit drei Eingängen. Der Baustein führt eine boolesche AND-Operation auf drei unabhängigen Eingangssignalen durch und gibt das Ergebnis über einen Adapter-Ausgang aus.

![AX_AND_3](AX_AND_3.svg)

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

**Eingangsadapter (Sockets):**
- **IN1** - AND-Eingang 1 (Typ: adapter::types::unidirectional::AX)
- **IN2** - AND-Eingang 2 (Typ: adapter::types::unidirectional::AX)
- **IN3** - AND-Eingang 3 (Typ: adapter::types::unidirectional::AX)

**Ausgangsadapter (Plugs):**
- **OUT** - AND-Ergebnis (Typ: adapter::types::unidirectional::AX)

## Funktionsweise
Der AX_AND_3-Block führt eine logische UND-Verknüpfung der drei Eingangssignale durch. Das Ausgangssignal ist nur dann aktiv (TRUE), wenn alle drei Eingangssignale gleichzeitig aktiv (TRUE) sind. Die Verarbeitung erfolgt kontinuierlich basierend auf den aktuellen Eingangswerten.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter für die Signalübertragung
- Implementiert als generischer Funktionsblock mit der generischen Klasse 'GEN_AX_AND'
- Arbeitet mit AX-Typ Adaptern für standardisierte Signalübertragung
- Keine Ereignissteuerung - kontinuierliche Auswertung

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustandsautomaten, da er als kombinatorische Logikschaltung arbeitet. Die Ausgabe wird direkt aus der aktuellen Kombination der Eingangswerte berechnet.

## Anwendungsszenarien
- Sicherheitssteuerungen, bei denen mehrere Bedingungen gleichzeitig erfüllt sein müssen
- Verknüpfung von Sensor-Signalen in industriellen Steuerungen
- Logische Verarbeitung in Automatisierungssystemen
- Überwachungssysteme mit Mehrfachbedingungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-AND-Blöcken bietet AX_AND_3:
- Drei Eingänge statt der typischen zwei Eingänge
- Adapter-basierte Schnittstelle statt direkter Daten-Ein-/Ausgänge
- Spezifische AX-Typ-Kompatibilität
- Unidirektionale Signalübertragung

Vergleich mit [AND_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_3.md)






## 🛠️ Zugehörige Übungen

* [Uebung_002a6_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a6_AX.md)

## Fazit
Der AX_AND_3 ist ein spezialisierter Logikbaustein für Anwendungen, die eine dreifache UND-Verknüpfung mit standardisierten AX-Adaptern erfordern. Seine Adapter-basierte Architektur ermöglicht eine einfache Integration in bestehende Steuerungssysteme und bietet eine zuverlässige Lösung für komplexe logische Verknüpfungen.