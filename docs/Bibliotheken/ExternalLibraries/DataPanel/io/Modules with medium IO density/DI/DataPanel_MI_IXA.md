# DataPanel_MI_IXA

<img width="1325" height="246" alt="image" src="https://github.com/user-attachments/assets/32729d23-7ab3-4b67-a1f0-aba3120aaa91" />

* * * * * * * * * *

## Einleitung
Der DataPanel_MI_IXA ist ein zusammengesetzter Funktionsblock für die Verarbeitung von booleschen Eingabedaten. Er dient als Schnittstelle für digitale Eingänge und ermöglicht die Initialisierung und Abfrage von Eingangsdaten über standardisierte Service-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit den zugehörigen Daten QI, PARAMS, u8SAMember und Input
- **REQ**: Service-Anfrage mit dem zugehörigen Daten QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI**: Ereignis-Eingangsqualifizierer (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **u8SAMember**: Knoten SA 224..239 (USINT) mit Initialwert MI::MI_00
- **Input**: Identifizierung des digitalen Eingangs DigitalInput_5A..8B mit Initialwert Invalid

### **Daten-Ausgänge**
- **QO**: Ereignis-Ausgangsqualifizierer (BOOL)
- **STATUS**: Service-Status (STRING)

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ AX für die Datenkommunikation

## Funktionsweise
Der Funktionsblock fungiert als Wrapper für den internen DataPanel_MI_IX-Baustein und leitet alle Ereignisse und Daten entsprechend weiter. Bei der INIT-Initialisierung werden alle Parameter an den internen Baustein übergeben, und die Bestätigung erfolgt über INITO. REQ-Anfragen werden direkt an den internen Baustein weitergeleitet.

## Technische Besonderheiten
- Verwendet spezielle Typen aus dem DataPanel::io::MI::DI-Namensraum
- Unterstützt SA-Mitglieder im Bereich 224-239
- Bietet Initialisierung mit Standardwerten für u8SAMember und Input
- Implementiert Fehlerbehandlung über den Invalid-Initialwert

## Zustandsübersicht
Der Baustein verfügt über einen initialisierten und einen Betriebszustand. Nach erfolgreicher INIT-Initialisierung ist der Baustein betriebsbereit und kann REQ-Anfragen verarbeiten.

## Anwendungsszenarien
- Anbindung digitaler Eingänge in Automatisierungssystemen
- Integration in DataPanel-IO-Strukturen
- Verwendung in Steuerungssystemen mit SA-Bus-Kommunikation
- Abstraktion von Hardware-Eingängen in standardisierten Schnittstellen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsbausteinen bietet DataPanel_MI_IXA erweiterte Initialisierungsmöglichkeiten und Parameterisierung über den PARAMS-Eingang. Die SA-Mitgliedsnummerierung ermöglicht eine spezifische Adressierung in größeren Systemen.

## Fazit
Der DataPanel_MI_IXA ist ein robuster und flexibler Funktionsblock für die Integration digitaler Eingänge in komplexe Automatisierungssysteme. Seine strukturierte Schnittstelle und erweiterte Parametrierungsmöglichkeiten machen ihn besonders für anspruchsvolle Anwendungen in industriellen Umgebungen geeignet.
