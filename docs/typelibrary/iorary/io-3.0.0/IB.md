# IB

* * * * * * * * * *
## Einleitung
Der IB-Funktionsblock (Input Byte) ist ein Dienstschnittstellen-Funktionsblock für die Verarbeitung von Byte-Eingabedaten. Er dient als Schnittstelle zwischen einem IEC 61499-Steuerungssystem und externen Eingabegeräten oder Ressourcen, die Byte-Daten liefern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Dienstinitialisierung - Initialisiert den Funktionsblock und konfiguriert die Schnittstellenparameter
- **REQ**: Dienstanforderung - Fordert eine aktuelle Dateneingabe an

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt die erfolgreiche Initialisierung
- **CNF**: Dienstbestätigung - Bestätigt die angeforderten Dienstoperationen
- **IND**: Indikation von der Ressource - Signalisiert eingehende Daten von der externen Ressource

### **Daten-Eingänge**
- **QI**: Ereigniseingangsqualifizierer (BOOL) - Steuert die Ausführung der Ereignisse
- **PARAMS**: Dienstparameter (STRING) - Konfigurationsparameter für die Schnittstelle

### **Daten-Ausgänge**
- **QO**: Ereignisausgangsqualifizierer (BOOL) - Statusindikator für die Ausgangsereignisse
- **STATUS**: Dienststatus (STRING) - Statusinformationen über die aktuelle Operation
- **IN**: Eingabedaten von der Ressource (BYTE) - Die empfangenen Byte-Daten

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der IB-Funktionsblock arbeitet als bidirektionale Schnittstelle für Byte-Eingabedaten. Bei Initialisierung (INIT) werden die Schnittstellenparameter konfiguriert. Über REQ-Ereignisse können Daten explizit angefordert werden, während IND-Ereignisse asynchrone Dateneingänge signalisieren. Die empfangenen Byte-Daten werden über den IN-Ausgang bereitgestellt.

## Technische Besonderheiten
- Unterstützt sowohl anforderungsbasierte (REQ/CNF) als auch ereignisbasierte (IND) Datenerfassung
- BYTE-Datentyp für kompakte 8-Bit-Datenverarbeitung
- String-basierte Parameterkonfiguration für flexible Anpassung
- Statusrückmeldung über SERVICE-Statusausgang

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Wartet auf INIT-Ereignis
2. **Initialisiert**: Bereit für Datenerfassung
3. **Datenanforderung**: Verarbeitet REQ-Ereignisse
4. **Datenempfang**: Verarbeitet eingehende IND-Ereignisse

## Anwendungsszenarien
- Einlesen von 8-Bit-Sensordaten
- Schnittstelle zu einfachen digitalen Eingabegeräten
- Kommunikation mit Peripheriegeräten, die Byte-Daten liefern
- Protokollimplementierungen mit Byte-orientierten Datenformaten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Eingabebausteinen:
- IB spezialisiert auf BYTE-Datentyp (8-Bit)
- Bietet sowohl pollende (REQ) als auch interrupt-artige (IND) Betriebsmodi
- Einfacher als komplexere Protokollbausteine, aber spezifischer für Byte-Daten

## Fazit
Der IB-Funktionsblock bietet eine effiziente und flexible Lösung für die Integration von Byte-basierten Eingabedaten in IEC 61499-Steuerungssysteme. Seine duale Betriebsart (anforderungsbasiert und ereignisgesteuert) macht ihn vielseitig einsetzbar für verschiedene Anwendungsfälle in der industriellen Automatisierung.