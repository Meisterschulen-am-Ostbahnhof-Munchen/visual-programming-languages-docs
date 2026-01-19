# LED_FREQ

```{index} single: LED_FREQ
```

* * * * * * * * * *

## Einleitung
LED_FREQ ist eine Sammlung globaler Konstanten für die Steuerung von LED-Blinkmustern mit Prioritätsverwaltung. Die Konstanten definieren verschiedene Blinkfrequenzen und Betriebsmodi für LEDs mit zugeordneten Prioritätswerten, die in Steuerungsanwendungen verwendet werden können.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
*Keine Adapter vorhanden*

## Funktionsweise
Die globalen Konstanten stellen numerische Werte für verschiedene LED-Betriebsmodi bereit. Jeder Modus hat einen spezifischen Prioritätswert, wobei höhere Zahlen eine höhere Priorität darstellen. Die Konstanten können in Funktionsblöcken verwendet werden, um LED-Verhalten zu steuern und Prioritätskonflikte zu lösen.

## Technische Besonderheiten
- **Datentyp**: Alle Konstanten sind vom Typ UINT (unsigned integer)
- **Prioritätsbereich**: Werte von 0 bis 6, wobei 6 die höchste Priorität darstellt
- **Frequenzbereiche**: 5Hz, 2Hz, 1Hz, 0.5Hz Blinken sowie Atmungseffekt
- **Package-Zugehörigkeit**: logiBUS::io::DO_LED

## Zustandsübersicht
*Keine Zustandsmaschine vorhanden - handelt sich um statische Konstanten*

## Anwendungsszenarien
- Steuerung von Status-LEDs in industriellen Steuerungssystemen
- Priorisierte Anzeigesteuerung in Maschinenbedienpanels
- Visualisierung von Betriebszuständen mit unterschiedlicher Dringlichkeit
- Mehrkanalige LED-Steuerung mit Prioritätsverwaltung

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken mit dynamischer Verhaltenssteuerung bietet LED_FREQ statische, vordefinierte Betriebsmodi mit festen Prioritäten. Dies ermöglicht eine einfachere Implementierung bei bekannten, standardisierten Anzeigeanforderungen.

## Fazit
LED_FREQ bietet eine effiziente Methode zur Definition standardisierter LED-Betriebsmodi mit integrierter Prioritätsverwaltung. Die Konstantensammlung eignet sich besonders für Anwendungen, bei denen klare, vorhersehbare LED-Verhaltensmuster mit definierter Priorität benötigt werden.