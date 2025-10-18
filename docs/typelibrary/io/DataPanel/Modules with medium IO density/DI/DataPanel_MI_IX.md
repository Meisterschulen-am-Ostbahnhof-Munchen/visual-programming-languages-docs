# DataPanel_MI_IX

* * * * * * * * * *

## Einleitung
Der DataPanel_MI_IX ist ein Service-Interface-Funktionsblock für boolesche Eingabedaten. Er dient als Schnittstelle für digitale Eingänge und ermöglicht die Kommunikation zwischen der Steuerung und den angeschlossenen Eingabegeräten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit den zugehörigen Variablen QI, PARAMS, u8SAMember und Input
- **REQ**: Service-Anfrage mit der zugehörigen Variable QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den Variablen QO und STATUS
- **CNF**: Bestätigung der angeforderten Service-Funktion mit den Variablen QO, STATUS und IN
- **IND**: Indikation von der Ressource mit den Variablen QO, STATUS und IN

### **Daten-Eingänge**
- **QI**: BOOL - Ereignis-Eingangsqualifikator
- **PARAMS**: STRING - Service-Parameter
- **u8SAMember**: USINT - Knoten SA 224..239 (Initialwert: MI::MI_00)
- **Input**: DataPanel_MI_DI_S - Identifiziert den digitalen Eingang DigitalInput_5A..8B (Initialwert: DataPanel_MI_DI::Invalid)

### **Daten-Ausgänge**
- **QO**: BOOL - Ereignis-Ausgangsqualifikator
- **STATUS**: STRING - Service-Status
- **IN**: BOOL - Eingabedaten von der Ressource

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert sich über das INIT-Ereignis und bestätigt die Initialisierung mit INITO. Über das REQ-Ereignis können Service-Anfragen gestellt werden, die mit CNF bestätigt werden. Zusätzlich sendet der Block IND-Ereignisse bei Änderungen der Eingangsdaten von der Ressource.

## Technische Besonderheiten
- Unterstützt spezifische Node-SA-Adressierung im Bereich 224-239
- Verwendet einen strukturierten Datentyp DataPanel_MI_DI_S zur Identifikation digitaler Eingänge
- Bietet umfangreiche Statusrückmeldungen über die STATUS-Variable

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor der INIT-Initialisierung
2. **Initialisiert**: Nach erfolgreicher INIT-Initialisierung
3. **Bereit**: Kann REQ-Anfragen verarbeiten
4. **Aktiv**: Verarbeitet Eingangsdaten und generiert IND-Ereignisse

## Anwendungsszenarien
- Anbindung digitaler Eingänge in Automatisierungssystemen
- Überwachung von Schaltzuständen in industriellen Steuerungen
- Integration in Datenerfassungssysteme für boolesche Signale

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren digitalen Eingangsblöcken bietet DataPanel_MI_IX erweiterte Service-Funktionalität mit Initialisierungs- und Statusrückmeldungen sowie spezifische Adressierungsmöglichkeiten für komplexere Automatisierungsnetzwerke.

## Fazit
Der DataPanel_MI_IX ist ein leistungsfähiger Service-Interface-Block für die Anbindung boolescher Eingabedaten, der durch seine erweiterte Funktionalität und Statusüberwachung besonders für anspruchsvolle Automatisierungsanwendungen geeignet ist.