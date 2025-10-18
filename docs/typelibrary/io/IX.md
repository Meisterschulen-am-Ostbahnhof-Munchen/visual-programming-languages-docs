# IX

![](https://user-images.githubusercontent.com/69573151/210780918-7dd9c9fc-17da-4fca-983d-f5d40e91ce47.png)

* * * * * * * * * *

## Einleitung
Der IX-Funktionsblock ist ein Service-Interface-Funktionsblock für boolesche Eingabedaten. Er dient als Schnittstelle zur Kommunikation mit Eingabegeräten und ermöglicht die Abfrage und Verarbeitung von digitalen Eingangssignalen in 4diac-Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - Initialisiert den Funktionsblock und konfiguriert die Hardware-Parameter
- **REQ**: Service-Anfrage - Fordert eine Abfrage des aktuellen Eingangswerts an

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt die erfolgreiche Initialisierung
- **CNF**: Bestätigung der angeforderten Service - Bestätigt eine erfolgreiche Abfrage
- **IND**: Indikation von der Ressource - Signalisiert eine Zustandsänderung des Eingangssignals

### **Daten-Eingänge**
- **QI**: Event-Input-Qualifier (BOOL) - Steuert die Aktivierung der Service-Funktionalität
- **PARAMS**: Service-Parameter (STRING) - Enthält Konfigurationsparameter für die Hardware-Schnittstelle

### **Daten-Ausgänge**
- **QO**: Event-Output-Qualifier (BOOL) - Zeigt den Status der Service-Ausführung an
- **STATUS**: Service-Status (STRING) - Liefert Statusinformationen über die Service-Ausführung
- **IN**: Eingabedaten von der Ressource (BOOL) - Enthält den aktuellen Wert des digitalen Eingangs

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der IX-Funktionsblock dient als Vermittler zwischen der Steuerungslogik und physischen Eingabegeräten. Bei der Initialisierung (INIT) werden die Hardware-Parameter konfiguriert. Anschließend kann über REQ-Ereignisse der aktuelle Zustand des Eingangs abgefragt werden. Der Block kann sowohl poll-basierte Abfragen (REQ/CNF) als auch ereignisbasierte Benachrichtigungen (IND) bei Zustandsänderungen verarbeiten.

## Technische Besonderheiten
- Unterstützt sowohl anforderungsbasierte als auch ereignisgesteuerte Betriebsmodi
- Boolescher Datentyp für einfache digitale Eingänge
- Flexible Parameterkonfiguration über STRING-Parameter
- Umfassende Statusrückmeldung für Fehlerdiagnose

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Block ist inaktiv
2. **Initialisiert**: Block ist betriebsbereit nach erfolgreicher INIT-Verarbeitung
3. **Abfrage aktiv**: Verarbeitung einer REQ-Anfrage
4. **Indikationsbereit**: Bereit für ereignisgesteuerte Benachrichtigungen

## Anwendungsszenarien
- Abfrage von digitalen Sensoren (Endschalter, Näherungsschalter)
- Überwachung von Taster-Eingängen
- Lesen von Schalterstellungen
- Digitale Signalverarbeitung in Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Eingabe-Bausteinen bietet IX eine erweiterte Service-Schnittstelle mit sowohl poll-basierten als auch ereignisgesteuerten Betriebsmodi. Während einfachere Eingabeblöcke oft nur direkte Werte liefern, bietet IX zusätzliche Statusinformationen und Fehlerbehandlung.

## Fazit
Der IX-Funktionsblock stellt eine robuste und flexible Lösung für die Integration boolescher Eingabedaten in 4diac-Systeme dar. Seine umfassende Fehlerbehandlung und flexible Betriebsmodi machen ihn besonders geeignet für zuverlässige Automatisierungsanwendungen mit digitalen Eingangssignalen.