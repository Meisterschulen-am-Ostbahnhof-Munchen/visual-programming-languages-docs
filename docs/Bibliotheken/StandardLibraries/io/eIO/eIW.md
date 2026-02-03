# eIW

```{index} single: eIW
```

<img width="1434" height="296" alt="image" src="https://github.com/user-attachments/assets/4b045e96-1325-4fca-9291-53d4d39a6161" />

* * * * * * * * * *

## Einleitung
Der eIW-Funktionsblock ist ein Eingabeservice-Interface für Wort-Eingabedaten (WORD) mit ereignisbasierter Auslösung. Er dient als Schnittstelle zwischen der Steuerungsanwendung und physikalischen Eingabegeräten und ermöglicht die Abfrage von 16-Bit-Datenwörtern.

![eIW](eIW.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - initialisiert den Funktionsblock und konfiguriert die Hardware-Parameter
- **REQ**: Service-Anfrage - löst eine Abfrage der Eingabedaten aus

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - bestätigt die erfolgreiche Initialisierung
- **CNF**: Bestätigung der angeforderten Service-Anfrage - liefert die angeforderten Eingabedaten
- **IND**: Indikation von der Ressource - signalisiert asynchrone Zustandsänderungen der Eingabedaten

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifikator - steuert die Ausführung der Service-Anfragen
- **PARAMS** (STRING): Service-Parameter - Konfigurationsparameter für die Hardware-Schnittstelle

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifikator - zeigt den Erfolg oder Fehler der Operation an
- **STATUS** (STRING): Service-Status - detaillierte Statusinformationen über die ausgeführte Operation
- **IN** (WORD): Eingabedaten von der Ressource - die gelesenen 16-Bit-Daten

### **Adapter**
- **eCONF** (eclipse4diac::io::eio::eGenAdapter): Konfiguration der ereignisbasierten Auslösung - ermöglicht die Anpassung des Trigger-Verhaltens

## Funktionsweise
Der eIW-Funktionsblock arbeitet als Vermittler zwischen der Steuerungsanwendung und physikalischen Eingabegeräten. Bei der Initialisierung (INIT) werden die Hardware-Parameter konfiguriert. Anschließend können über REQ-Ereignisse gezielt Eingabedaten abgefragt werden. Der Block unterstützt sowohl synchrone Abfragen (CNF) als auch asynchrone Benachrichtigungen bei Zustandsänderungen (IND).

## Technische Besonderheiten
- Verarbeitet 16-Bit-Wort-Daten (WORD-Datentyp)
- Unterstützt ereignisbasierte und polling-basierte Abfragemodi
- Bietet detaillierte Statusrückmeldungen über den STATUS-Ausgang
- Ermöglicht flexible Hardware-Konfiguration über PARAMS-Eingang
- Integriert Adapter-Schnittstelle für erweiterte Trigger-Konfiguration

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Block ist betriebsbereit, aber nicht konfiguriert
2. **Initialisiert**: Hardware-Parameter sind konfiguriert, Block ist betriebsbereit
3. **Abfrage aktiv**: Service-Anfrage wird verarbeitet
4. **Daten verfügbar**: Eingabedaten stehen zur Verfügung und werden ausgegeben

## Anwendungsszenarien
- Abfrage von digitalen Eingangsgruppen (16-Bit)
- Lesen von Encoder-Werten
- Überwachung von Statusregistern
- Erfassung von Sensor-Datenwörtern
- Schnittstelle zu I/O-Modulen mit Wort-Zugriff

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingabeblöcken bietet eIW:
- Erweiterte 16-Bit-Datenverarbeitung
- Detaillierte Statusrückmeldungen
- Flexible Konfigurationsmöglichkeiten
- Unterstützung für ereignisbasierte und polling-basierte Betriebsarten
- Adapter-Schnittstelle für erweiterte Funktionalität

## Fazit
Der eIW-Funktionsblock stellt eine leistungsstarke und flexible Schnittstelle für die Verarbeitung von Wort-Eingabedaten in IEC 61499-Steuerungssystemen dar. Seine kombinierte Unterstützung für synchrone Abfragen und asynchrone Benachrichtigungen macht ihn besonders geeignet für Anwendungen, die sowohl deterministische Abfragen als auch zeitkritische Zustandsänderungen erfordern.