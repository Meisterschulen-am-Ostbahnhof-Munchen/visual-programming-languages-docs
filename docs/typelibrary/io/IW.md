# IW

![](https://user-images.githubusercontent.com/69573151/210780698-5e8f8f13-fa13-49a1-91fa-d132aec3db58.png)

* * * * * * * * * *
## Einleitung
Der IW-Funktionsblock (Input Word) ist ein Dienstschnittstellen-Funktionsblock für die Verarbeitung von Wort-Eingabedaten in 4diac-Systemen. Er dient als Schnittstelle zwischen der Steuerungslogik und externen Eingabegeräten oder Ressourcen, die Wort-Daten (16-Bit) bereitstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Dienstinitialisierung - Initialisiert den Funktionsblock und konfiguriert die Hardware-Parameter
- **REQ**: Dienstanforderung - Fordert eine aktuelle Eingabe vom angeschlossenen Gerät an

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt den Abschluss der Initialisierung
- **CNF**: Bestätigung der angeforderten Dienstleistung - Quittiert eine erfolgreiche REQ-Anfrage
- **IND**: Indikation von der Ressource - Signalisiert eingehende Daten ohne vorherige Anfrage

### **Daten-Eingänge**
- **QI**: Ereignis-Eingabe-Qualifizierer (BOOL) - Aktiviert/deaktiviert die Verarbeitung
- **PARAMS**: Dienstparameter (STRING) - Konfigurationsparameter für die Hardware-Schnittstelle

### **Daten-Ausgänge**
- **QO**: Ereignis-Ausgabe-Qualifizierer (BOOL) - Status der Verarbeitung
- **STATUS**: Dienststatus (STRING) - Fehlermeldungen oder Statusinformationen
- **IN**: Eingabedaten von der Ressource (WORD) - Die gelesenen 16-Bit-Daten

## Funktionsweise
Der IW-Block arbeitet als bidirektionale Schnittstelle für Wort-Eingabedaten. Bei der Initialisierung (INIT) werden die Hardware-Parameter konfiguriert. Der Block kann sowohl auf explizite Anfragen (REQ) reagieren als auch asynchrone Datenindikationen (IND) von der angeschlossenen Ressource verarbeiten. Die gelesenen WORD-Daten werden an den Ausgang IN ausgegeben.

## Technische Besonderheiten
- Verarbeitet 16-Bit WORD-Datentypen
- Unterstützt sowohl anforderungsbasierte (REQ/CNF) als auch ereignisbasierte (IND) Kommunikation
- String-basierte Parameterkonfiguration für flexible Hardware-Anbindung
- Umfassende Statusrückmeldung über STATUS-Ausgang

## Zustandsübersicht
Der Block durchläuft folgende Hauptzustände:
- **Nicht initialisiert**: Block wartet auf INIT-Ereignis
- **Initialisiert**: Block ist betriebsbereit und kann Daten verarbeiten
- **Datenanforderung**: Verarbeitung einer REQ-Anfrage
- **Datenempfang**: Verarbeitung eingehender IND-Daten

## Anwendungsszenarien
- Anbindung von 16-Bit Eingabegeräten (Sensoren, Encoder, Schaltergruppen)
- Lesen von digitalen Eingangswörtern aus Prozessperipherie
- Schnittstelle zu IO-Modulen mit Wort-basierten Eingängen
- Überwachung von Statuswörtern aus verteilten Systemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu IB (Input Byte) verarbeitet IW 16-Bit anstelle von 8-Bit Daten. Gegenüber ID (Input Double Word) bietet IW eine geringere Datenbreite. Der Block ähnelt in der Struktur anderen IO-Schnittstellenblöcken, ist jedoch speziell auf WORD-Datentypen optimiert.

## Fazit
Der IW-Funktionsblock bietet eine robuste und flexible Schnittstelle für die Verarbeitung von 16-Bit Eingabedaten in 4diac-Systemen. Seine klare Ereignisstruktur und umfassende Statusrückmeldung machen ihn zu einer zuverlässigen Lösung für die Anbindung von Wort-basierten Eingabegeräten in industriellen Automatisierungsanwendungen.