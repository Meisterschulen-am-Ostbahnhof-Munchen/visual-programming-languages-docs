# LED_strip

* * * * * * * * * *
## Einleitung
LED_strip ist ein GlobalConstants-Baustein, der globale Konstanten für die Ansteuerung von LED-Streifen bereitstellt. Der Baustein definiert eine Ausgabevariable für die Steuerung von LED-Streifen und ist Teil des logiBUS-Systems.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der LED_strip-Baustein definiert eine globale Konstante `Output_strip` vom Typ USINT (Unsigned Short Integer) mit dem Initialwert 0. Diese Konstante dient als Referenz für die Ausgabesteuerung von LED-Streifen und kann von anderen Funktionsblöcken im System verwendet werden.

## Technische Besonderheiten
- Die Konstante `Output_strip` ist vom Typ USINT (8-Bit unsigned integer)
- Initialwert ist 0
- Teil des logiBUS::io::DO_LED Packages
- Unterstützt die Eclipse Public License 2.0

## Zustandsübersicht
Da es sich um einen GlobalConstants-Baustein handelt, gibt es keine Zustandsübergänge oder -verwaltung. Die definierte Konstante behält ihren festgelegten Wert während der gesamten Laufzeit.

## Anwendungsszenarien
- Definition von Ausgabekanälen für LED-Streifen
- Zentrale Verwaltung von Hardware-Ausgabereferenzen
- Verwendung in kombination mit digitalen Ausgabeblöcken
- Integration in Beleuchtungssteuerungssysteme

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen GlobalConstants-Bausteinen bietet LED_strip eine spezifische Konstante für LED-Streifen-Steuerung. Während allgemeine Konstantenbausteine universelle Werte definieren, ist dieser Baustein auf die spezifischen Anforderungen der LED-Ansteuerung ausgelegt.

## Fazit
Der LED_strip GlobalConstants-Baustein bietet eine einfache und effektive Möglichkeit, Ausgabereferenzen für LED-Streifen zentral zu verwalten. Durch die Verwendung als globale Konstante ermöglicht er eine konsistente und wartbare Integration in größere Steuerungssysteme.