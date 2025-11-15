# AuxiliaryState

* * * * * * * * * *

## Einleitung
AuxiliaryState ist eine Sammlung von globalen Konstanten für Hilfseingänge in ISOBUS-Systemen. Diese Konstanten definieren verschiedene Zustände von Auxiliary-Eingängen, die typischerweise für Steuerfunktionen in landwirtschaftlichen und mobilen Arbeitsmaschinen verwendet werden.

## Schnittstellenstruktur
Bei AuxiliaryState handelt es sich um globale Konstanten und nicht um einen Funktionsblock im klassischen Sinne. Daher verfügt diese Komponente über keine Ereignis- oder Datenschnittstellen.

### **Ereignis-Eingänge**
- Nicht vorhanden (Globale Konstanten)

### **Ereignis-Ausgänge**
- Nicht vorhanden (Globale Konstanten)

### **Daten-Eingänge**
- Nicht vorhanden (Globale Konstanten)

### **Daten-Ausgänge**
- Nicht vorhanden (Globale Konstanten)

### **Adapter**
- Nicht vorhanden

## Funktionsweise
AuxiliaryState definiert eine Reihe von vordefinierten Konstanten für den Datentyp `AuxiliaryState_S`. Jede Konstante repräsentiert einen spezifischen Zustand eines Auxiliary-Eingangs mit einem entsprechenden numerischen Wert und optionalen Zusatzparametern.

## Technische Besonderheiten
- Alle Konstanten sind vom Typ `isobus::UT::io::Auxiliary::IN::AuxiliaryState_S`
- Die Wertebereiche reichen von 0 bis 255
- Einige Konstanten enthalten zusätzlich das Flag `bCyclic := FALSE`
- Die Struktur folgt ISOBUS-Standards für landwirtschaftliche Steuerungen

## Zustandsübersicht
Die definierten Konstanten umfassen folgende Zustände:

| Konstante | Wert | Beschreibung |
|-----------|------|--------------|
| `AuxDisabled` | 0 | Aus - rückwärts, unten, links oder nicht gedrückt |
| `AuxDisabled_START` | 0 | Aus - rückwärts, unten, links oder nicht gedrückt (mit bCyclic=FALSE) |
| `AuxEnabled` | 1 | Ein - vorwärts, oben, rechts oder gedrückt |
| `AuxEnabled_START` | 1 | Ein - vorwärts, oben, rechts oder gedrückt (mit bCyclic=FALSE) |
| `AuxHeld` | 2 | Gehalten (vorwärts, oben oder rechts) |
| `AuxHeld_START` | 2 | Gehalten (vorwärts, oben oder rechts) (mit bCyclic=FALSE) |
| `AuxEnabledBackwards` | 4 | Momentan ein - rückwärts, unten oder links |
| `AuxHeldBackwards` | 8 | Gehalten (rückwärts, unten oder links) |
| `AuxHeldBackwards_START` | 8 | Gehalten (rückwärts, unten oder links) (mit bCyclic=FALSE) |
| `AuxDefault` | 9 | Standardwert |
| `Invalid` | 255 | Ungültiger Wert |

## Anwendungsszenarien
- Steuerung von Hydraulikfunktionen in Traktoren
- Bedienung von Anbaugeräten über ISOBUS-Schnittstellen
- Zustandsüberwachung von Hilfsfunktionen in mobilen Arbeitsmaschinen
- Implementierung von standardisierten Eingabezuständen in landwirtschaftlichen Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken mit aktiver Logik handelt es sich bei AuxiliaryState um passive Konstantendefinitionen, die als Referenzwerte in anderen Funktionsblöcken verwendet werden können. Sie bieten eine standardisierte Möglichkeit, Auxiliary-Zustände in ISOBUS-Umgebungen zu definieren.

## Fazit
AuxiliaryState stellt eine umfassende Sammlung von standardisierten Konstanten für die Behandlung von Auxiliary-Eingängen in ISOBUS-Systemen bereit. Die klare Definition der verschiedenen Zustände ermöglicht eine konsistente Implementierung von Steuerungslogik über verschiedene Systeme hinweg und erleichtert die Wartbarkeit und Lesbarkeit des Codes.