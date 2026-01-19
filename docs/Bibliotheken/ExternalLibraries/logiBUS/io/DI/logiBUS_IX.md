# logiBUS_IX

```{index} single: logiBUS_IX
```

<img width="1789" height="343" alt="image" src="https://github.com/user-attachments/assets/8c558337-facf-438d-87ba-69a1b8e110a9" />

* * * * * * * * * *

## Einleitung
Der logiBUS_IX Funktionsblock ist ein Eingabeservice-Interface für boolesche Eingangsdaten, der speziell für die Kommunikation mit logiBUS-Eingabemodulen entwickelt wurde. Er dient als Schnittstelle zwischen der Steuerungslogik und physischen Eingabesignalen und ermöglicht die Abfrage von digitalen Eingangswerten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Anfrage
- **IND**: Anzeige vom Ressourcen-Interface

### **Daten-Eingänge**
- **QI**: Ereignis-Eingangsqualifizierer (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **Input**: Identifiziert den Eingang I1..I8 (logiBUS_DI_S) - Initialwert: Invalid

### **Daten-Ausgänge**
- **QO**: Ereignis-Ausgangsqualifizierer (BOOL)
- **STATUS**: Service-Status (STRING)
- **IN**: Eingangsdaten von der Ressource (BOOL)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert sich über das INIT-Ereignis und kann anschließend über das REQ-Ereignis Eingangsdaten anfordern. Bei erfolgreicher Initialisierung gibt er das INITO-Ereignis zurück. Die tatsächlichen Eingangswerte werden über den IN-Ausgang bereitgestellt, während der STATUS-Ausgang Informationen über den aktuellen Betriebszustand liefert.

## Technische Besonderheiten
- Unterstützt bis zu 8 digitale Eingänge (I1..I8)
- Verwendet spezielle logiBUS-Datentypen für die Eingangsidentifikation
- Bietet umfangreiche Statusrückmeldungen über den STATUS-Ausgang
- Initialisiert mit einem ungültigen Eingangswert (Invalid)

## Zustandsübersicht
Der Funktionsblock durchläuft typischerweise folgende Zustände:
1. **Nicht initialisiert**: Vor der INIT-Anforderung
2. **Initialisiert**: Nach erfolgreicher INIT-Verarbeitung
3. **Bereit**: Kann REQ-Anfragen verarbeiten
4. **Aktiv**: Verarbeitet gerade eine Service-Anfrage

## Anwendungsszenarien
- Abfrage von digitalen Eingangssignalen in Automatisierungssystemen
- Integration von logiBUS-Eingabemodulen in 4diac-basierte Steuerungen
- Überwachung von Schalterzuständen und Sensorsignalen
- Industrielle E/A-Steuerung mit Statusüberwachung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsblöcken bietet logiBUS_IX:
- Erweiterte Statusinformationen
- Parametrierbare Service-Parameter
- Spezifische logiBUS-Hardware-Integration
- Umfangreichere Initialisierungs- und Bestätigungsmechanismen

## Fazit
Der logiBUS_IX Funktionsblock stellt eine robuste und flexible Lösung für die Integration von logiBUS-Eingabemodulen in 4diac-basierte Steuerungssysteme dar. Seine umfangreiche Statusrückmeldung und parametrierbare Schnittstelle machen ihn besonders geeignet für industrielle Anwendungen, bei denen zuverlässige E/A-Kommunikation erforderlich ist.