# LO

* * * * * * * * * *
## Einleitung
LO ist eine globale Konstantendefinition für Module mit geringer I/O-Dichte. Diese Konstanten definieren spezifische Adressbereiche für I/O-Module und werden in der 4diac-IDE zur Konfiguration von Steuerungssystemen verwendet.

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
Bei LO handelt es sich um globale Konstanten, die als statische Werte definiert sind. Die Konstanten repräsentieren Adressbereiche für I/O-Module mit geringer Dichte und werden zur Kompilierzeit in die Anwendung integriert.

## Technische Besonderheiten
- Alle Konstanten sind vom Typ USINT (Unsigned Short Integer)
- Wertebereich: 217 bis 224
- Statische Initialisierung zur Kompilierzeit
- Konstanten sind unveränderlich während der Laufzeit

## Zustandsübersicht
*Keine Zustandsübergänge vorhanden, da es sich um statische Konstanten handelt*

## Anwendungsszenarien
- Adressierung von I/O-Modulen mit geringer Dichte
- Konfiguration von Hardware-Schnittstellen
- Verwendung in Verbindung mit spezifischen I/O-Treibern
- Vereinfachung der Hardware-Konfiguration durch zentrale Konstantendefinition

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen globalen Konstanten-Bausteinen bietet LO spezifische Adressbereiche für Module mit geringer I/O-Dichte, während andere Bausteine möglicherweise andere Adressbereiche oder Konstantentypen definieren.

## Fazit
Die LO-Konstanten bieten eine strukturierte und zentrale Möglichkeit zur Definition von Hardware-Adressen für I/O-Module mit geringer Dichte. Durch die Verwendung dieser globalen Konstanten wird die Wartbarkeit und Lesbarkeit von Steuerungsprogrammen verbessert.