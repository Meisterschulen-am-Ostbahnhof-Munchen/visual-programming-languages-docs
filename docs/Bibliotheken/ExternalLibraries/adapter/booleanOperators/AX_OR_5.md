# AX_OR_5

<img width="963" height="369" alt="image" src="https://github.com/user-attachments/assets/7be25f5c-a69e-444a-9f06-b216c3290d77" />

* * * * * * * * * *

## Einleitung
Der AX_OR_5 Funktionsblock ist ein generischer Baustein zur Berechnung der booleschen ODER-Verknüpfung mit fünf Eingängen. Er dient zur logischen Verarbeitung von Signalen in Automatisierungssystemen und ermöglicht die Kombination mehrerer Eingangssignale zu einem Ausgangssignal.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden.

### **Adapter**
**Plug-Adapter:**
- **OUT**: Unidirektionaler Adapter für das ODER-Ergebnis

**Socket-Adapter:**
- **IN1**: Unidirektionaler Adapter für ODER-Eingang 1
- **IN2**: Unidirektionaler Adapter für ODER-Eingang 2  
- **IN3**: Unidirektionaler Adapter für ODER-Eingang 3
- **IN4**: Unidirektionaler Adapter für ODER-Eingang 4
- **IN5**: Unidirektionaler Adapter für ODER-Eingang 5

## Funktionsweise
Der Funktionsblock berechnet die logische ODER-Verknüpfung der fünf Eingangssignale. Das Ausgangssignal ist TRUE, wenn mindestens einer der fünf Eingänge TRUE ist. Sind alle Eingänge FALSE, wird das Ausgangssignal ebenfalls FALSE. Die Verarbeitung erfolgt über Adapter-Schnittstellen, wobei alle Ein- und Ausgänge unidirektional konfiguriert sind.

## Technische Besonderheiten
- Generischer Funktionsblock mit fünf Eingängen
- Verwendung von unidirektionalen Adaptern für alle Schnittstellen
- Implementiert als ODER-Verknüpfung mit fünf Operanden
- Keine Ereignissteuerung, kontinuierliche Signalverarbeitung

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustand und arbeitet stateless. Die Ausgabe wird kontinuierlich basierend auf den aktuellen Eingangswerten berechnet.

## Anwendungsszenarien
- Sicherheitskreise mit mehreren Not-Aus-Tastern
- Überwachungssysteme mit mehreren Sensoren
- Steuerungslogik mit parallelen Bedingungen
- Alarmierungssysteme mit mehreren Auslösern

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-ODER-Bausteinen mit weniger Eingängen bietet AX_OR_5 die Möglichkeit, fünf Signale gleichzeitig zu verarbeiten, was die Verdrahtung vereinfacht und Platz spart. Gegenüber kaskadierten ODER-Verknüpfungen bietet dieser Baustein eine integrierte Lösung.

Vergleich mit [OR_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_5.md)

## Fazit
Der AX_OR_5 Funktionsblock stellt eine effiziente Lösung für ODER-Verknüpfungen mit fünf Eingängen dar. Durch die Verwendung von Adaptern ermöglicht er eine flexible Integration in verschiedene Systemarchitekturen und eignet sich besonders für Anwendungen, bei denen mehrere Signale logisch verknüpft werden müssen.
