# AX_OR_8

```{index} single: AX_OR_8
```

<img width="960" height="469" alt="image" src="https://github.com/user-attachments/assets/a5f20ed5-b8ed-4f26-9696-860bc64cfb6f" />

* * * * * * * * * *
## Einleitung
Der AX_OR_8 Funktionsblock ist ein generischer Baustein zur Berechnung einer logischen ODER-Verknüpfung mit acht Eingängen. Er dient zur Verarbeitung von booleschen Signalen in Steuerungsanwendungen und ermöglicht die Kombination mehrerer Eingangssignale zu einem gemeinsamen Ausgangssignal.

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
- **IN1** - OR input 1 (unidirektionaler AX-Adapter)
- **IN2** - OR input 2 (unidirektionaler AX-Adapter)
- **IN3** - OR input 3 (unidirektionaler AX-Adapter)
- **IN4** - OR input 4 (unidirektionaler AX-Adapter)
- **IN5** - OR input 5 (unidirektionaler AX-Adapter)
- **IN6** - OR input 6 (unidirektionaler AX-Adapter)
- **IN7** - OR input 7 (unidirektionaler AX-Adapter)
- **IN8** - OR input 8 (unidirektionaler AX-Adapter)

**Ausgangsadapter:**
- **OUT** - OR result (unidirektionaler AX-Adapter)

## Funktionsweise
Der AX_OR_8 Block führt eine logische ODER-Verknüpfung über alle acht Eingänge durch. Das Ausgangssignal wird auf TRUE gesetzt, wenn mindestens einer der acht Eingänge TRUE ist. Nur wenn alle Eingänge FALSE sind, wird der Ausgang ebenfalls FALSE.

Die Funktionsweise entspricht der booleschen Gleichung:
OUT = IN1 ∨ IN2 ∨ IN3 ∨ IN4 ∨ IN5 ∨ IN6 ∨ IN7 ∨ IN8

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klassennamen-Kennung 'GEN_AX_OR'
- Verwendet unidirektionale AX-Adapter für alle Schnittstellen
- Keine internen Zustände oder Speicherfunktionen
- Sofortige Verarbeitung ohne Verzögerung
- Teil des Pakets "adapter::booleanOperators"

## Zustandsübersicht
Der Funktionsblock ist zustandslos und führt bei jeder Änderung an den Eingängen sofort die ODER-Berechnung durch. Es werden keine internen Zustände gespeichert.

## Anwendungsszenarien
- Sicherheitskreise mit mehreren Not-Aus-Tastern
- Überwachungssysteme mit mehreren Sensoren
- Steuerungslogik mit parallelen Bedingungen
- Alarmierungssysteme mit mehreren Auslösern
- Verknüpfung mehrerer Freigabesignale

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen ODER-Bausteinen mit weniger Eingängen bietet AX_OR_8 die Möglichkeit, bis zu acht Signale direkt zu verknüpfen, ohne zusätzliche Verkettung mehrerer Bausteine. Die Verwendung von Adaptern statt direkter Datenanschlüsse ermöglicht eine flexiblere Integration in verschiedene Systemarchitekturen.

Vergleich mit [OR_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_8.md)

## Fazit
Der AX_OR_8 Funktionsblock stellt eine effiziente Lösung für komplexe ODER-Verknüpfungen mit bis zu acht Eingängen dar. Durch die Verwendung von Standard-Adaptern und die generische Implementierung eignet er sich besonders für wiederverwendbare Steuerungslogik in industriellen Automatisierungsanwendungen.
