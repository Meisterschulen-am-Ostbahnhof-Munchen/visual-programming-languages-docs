# AX_AND_4

```{index} single: AX_AND_4
```

<img width="1010" height="334" alt="image" src="https://github.com/user-attachments/assets/439ed538-1eef-44d6-95c8-5d2a9f64fd6a" />

* * * * * * * * * *

## Einleitung
Der AX_AND_4 Funktionsblock ist ein generischer Baustein zur Berechnung einer logischen UND-Verknüpfung mit vier Eingängen. Er dient zur Verarbeitung von booleschen Signalen in Automatisierungssystemen und ermöglicht die Kombination mehrerer Eingangssignale zu einem gemeinsamen Ausgangssignal.

![AX_AND_4](AX_AND_4.svg)

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

**Plug-Adapter:**
- **OUT**: AND-Ergebnis (Adapter-Typ: adapter::types::unidirectional::AX)

**Socket-Adapter:**
- **IN1**: UND-Eingang 1 (Adapter-Typ: adapter::types::unidirectional::AX)
- **IN2**: UND-Eingang 2 (Adapter-Typ: adapter::types::unidirectional::AX)
- **IN3**: UND-Eingang 3 (Adapter-Typ: adapter::types::unidirectional::AX)
- **IN4**: UND-Eingang 4 (Adapter-Typ: adapter::types::unidirectional::AX)

## Funktionsweise
Der Funktionsblock berechnet eine logische UND-Verknüpfung über vier Eingänge. Das Ausgangssignal ist nur dann aktiv (TRUE), wenn alle vier Eingangssignale gleichzeitig aktiv (TRUE) sind. Sobald mindestens einer der vier Eingänge inaktiv (FALSE) ist, wird auch der Ausgang inaktiv.

## Technische Besonderheiten
- Generischer Funktionsblock mit vordefiniertem Klassennamen 'GEN_AX_AND'
- Verwendet unidirektionale Adapter für die Signalübertragung
- Implementiert als Teil des Packages "adapter::booleanOperators"
- Unterstützt vier unabhängige Eingangssignale

## Zustandsübersicht
Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt der AX_AND_4 keine internen Zustände. Die Ausgabe wird ausschließlich durch die aktuellen Eingangswerte bestimmt.

## Anwendungsszenarien
- Sicherheitssteuerungen, bei denen mehrere Bedingungen gleichzeitig erfüllt sein müssen
- Überwachung von Mehrfachsensoren
- Verknüpfung von Freigabesignalen in Prozesssteuerungen
- Logische Verknüpfung von Steuerbefehlen

Vergleich mit [AND_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_4.md)

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen UND-Bausteinen mit weniger Eingängen bietet AX_AND_4 die Möglichkeit, vier Signale direkt zu verknüpfen, ohne zusätzliche Verkettungen. Gegenüber ODER-Verknüpfungen stellt die UND-Verknüpfung strengere Anforderungen an die Aktivierung.

## Fazit
Der AX_AND_4 Funktionsblock bietet eine effiziente Lösung für die Verknüpfung von vier booleschen Eingangssignalen mittels logischer UND-Operation. Durch die Verwendung von Adaptern ermöglicht er eine flexible Integration in verschiedene Steuerungssysteme und eignet sich besonders für Anwendungen, bei denen mehrere Sicherheits- oder Freigabebedingungen gleichzeitig erfüllt sein müssen.