# SUBSCRIBE_3

```{index} single: SUBSCRIBE_3
```

<img width="1291" height="365" alt="image" src="https://github.com/user-attachments/assets/45f461a5-c84b-4b74-bb5a-f54b1c6dd6a4" />

* * * * * * * * * *

## Einleitung
Der SUBSCRIBE_3 Funktionsblock dient zum Abonnieren von Daten eines PUBLISH_3 Blocks. Er ermöglicht den Empfang von drei verschiedenen Datenströmen über eine Netzwerkverbindung und stellt einen standardisierten Mechanismus für die Kommunikation zwischen verteilten Systemkomponenten bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **RSP**: Response-Ereignis mit zugehörigem Daten QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit zugehörigen Daten QO und STATUS
- **IND**: Datenverfügbarkeitsereignis mit zugehörigen Daten QO, STATUS, RD_1, RD_3 und RD_2

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung und Betrieb
- **ID** (WSTRING): Identifikationsstring für die Verbindung

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für Ausgangszustand
- **STATUS** (WSTRING): Statusinformationen der Verbindung
- **RD_1** (ANY): Empfangene Daten vom Typ 1
- **RD_2** (ANY): Empfangene Daten vom Typ 2  
- **RD_3** (ANY): Empfangene Daten vom Typ 3

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_3 Block initialisiert sich über das INIT-Ereignis und stellt eine Verbindung zu einem entsprechenden PUBLISH_3 Block her. Nach erfolgreicher Initialisierung bestätigt er dies über INITO. Bei eingehenden Daten vom Publisher wird das IND-Ereignis ausgelöst und die empfangenen Daten über RD_1, RD_2 und RD_3 ausgegeben. Der STATUS-Parameter liefert dabei Informationen über den Verbindungszustand.

## Technische Besonderheiten
- Unterstützt drei unabhängige Datenkanäle (RD_1, RD_2, RD_3) mit ANY-Datentyp
- Verwendet WSTRING für ID und STATUS für internationale Zeichenunterstützung
- Implementiert ein zuverlässiges Initialisierungsprotokoll mit QI/QO-Handshake
- Generische Implementierung durch GEN_SUBSCRIBE Basisklasse

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisierung**: Verarbeitung von INIT mit ID-Parameter
3. **Betriebsbereit**: Erfolgreiche Verbindung zum Publisher
4. **Datenempfang**: Verarbeitung eingehender Daten mit IND-Auslösung

## Anwendungsszenarien
- Verteilte Steuerungssysteme in der Automatisierungstechnik
- Datenverteilung in IoT-Anwendungen
- Kommunikation zwischen verschiedenen Steuerungsebenen
- Maschine-zu-Maschine-Kommunikation in Industrie 4.0 Umgebungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren SUBSCRIBE-Blöcken bietet SUBSCRIBE_3 die Möglichkeit, drei verschiedene Datenströme parallel zu empfangen. Die Verwendung von ANY-Datentypen ermöglicht größere Flexibilität bei den übertragenen Datenformaten.

## Fazit
Der SUBSCRIBE_3 Funktionsblock stellt eine leistungsfähige Lösung für die Kommunikation in verteilten Automatisierungssystemen dar. Durch die Unterstützung mehrerer Datenkanäle und flexible Datentypen eignet er sich besonders für komplexe Anwendungen, bei mehrere Datenquellen parallel überwacht werden müssen.
