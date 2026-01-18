# eIX

```{index} single: eIX
```

<img width="1435" height="298" alt="image" src="https://github.com/user-attachments/assets/cae6a064-563d-41dd-9f8e-9cb9bb401bc6" />

* * * * * * * * * *

## Einleitung
Der eIX-Funktionsblock ist ein Eingabeservice-Interface für boolesche Eingabedaten mit ereignisbasierter Auslösung. Er dient als Schnittstelle zwischen der Steuerungslogik und physikalischen Eingabegeräten und ermöglicht die Abfrage von digitalen Eingangssignalen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - Initialisiert den Funktionsblock mit Parametern
- **REQ**: Service-Anfrage - Löst eine Abfrage des Eingangssignals aus

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt die erfolgreiche Initialisierung
- **CNF**: Service-Bestätigung - Bestätigt die verarbeitete Service-Anfrage
- **IND**: Indikation von der Ressource - Signalisiert eine Statusänderung des Eingangs

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer - Aktiviert/deaktiviert die Verarbeitung
- **PARAMS** (STRING): Service-Parameter - Konfigurationsparameter für den Service

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer - Status der Verarbeitung
- **STATUS** (STRING): Service-Status - Fehler- oder Statusinformationen
- **IN** (BOOL): Eingabedaten von der Ressource - Aktueller Wert des digitalen Eingangs

### **Adapter**
- **eCONF**: Konfiguration der ereignisbasierten Auslösung - Adapter für die Trigger-Konfiguration

## Funktionsweise
Der eIX-Block arbeitet als Service-Interface für digitale Eingänge. Bei Initialisierung (INIT) werden die Service-Parameter konfiguriert. Über REQ-Ereignisse können gezielte Abfragen des Eingangssignals ausgelöst werden. Der Block liefert über CNF die aktuellen Eingangswerte zurück und kann über IND asynchrone Statusänderungen melden.

## Technische Besonderheiten
- Ereignisbasierte Abfragemechanismen
- Separater Initialisierungs- und Betriebsmodus
- String-basierte Statusrückmeldungen
- Adapter-basierte Konfiguration der Trigger-Logik
- Unterstützung sowohl für angefragte als auch indizierte Operationen

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist betriebsbereit und kann REQ-Ereignisse verarbeiten
3. **Aktiv**: Verarbeitung von Service-Anfragen und Rückmeldung von Eingangswerten
4. **Fehler**: Bei Problemen wird STATUS mit Fehlerinformationen gefüllt

## Anwendungsszenarien
- Abfrage von digitalen Sensoren (Endschalter, Näherungsschalter)
- Überwachung von Schaltzuständen
- Integration von Tastern und Bedienelementen
- Signalverarbeitung in Automatisierungssystemen
- Zustandsüberwachung von Maschinen und Anlagen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsblöcken bietet eIX erweiterte Funktionalität:
- Ereignisbasierte statt zyklische Abfrage
- Detaillierte Statusrückmeldungen
- Konfigurierbare Trigger-Mechanismen
- Separate Initialisierungs- und Betriebsphasen

## Fazit
Der eIX-Funktionsblock stellt eine flexible und robuste Lösung für die Integration digitaler Eingänge in IEC 61499-basierten Steuerungssystemen dar. Durch seine ereignisbasierte Architektur und umfangreiche Statusrückmeldungen eignet er sich besonders für Anwendungen, die zuverlässige und konfigurierbare Eingabeverarbeitung erfordern.
