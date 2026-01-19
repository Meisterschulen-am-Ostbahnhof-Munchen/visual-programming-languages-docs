# SUBSCRIBE_5

```{index} single: SUBSCRIBE_5
```

<img width="1291" height="424" alt="image" src="https://github.com/user-attachments/assets/9b4ee34a-5e64-472b-8ee6-32e06cb25d81" />

* * * * * * * * * *

## Einleitung
Der SUBSCRIBE_5 Funktionsblock dient zum Abonnieren von Daten eines PUBLISH_5 Blocks. Er ermöglicht den Empfang von bis zu fünf verschiedenen Datenpunkten über eine Netzwerkverbindung und stellt eine standardisierte Schnittstelle für die Kommunikation zwischen verteilten Automatisierungskomponenten bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit den zugehörigen Daten QI und ID
- **RSP**: Response-Ereignis mit zugehörigem Datenpunkt QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den Daten QO und STATUS
- **IND**: Indikationsereignis bei neuen verfügbaren Daten mit QO, STATUS und den fünf Datenpunkten RD_1 bis RD_5

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung - aktiviert/deaktiviert den Block
- **ID** (WSTRING): Identifikationsstring zur Zuordnung zum entsprechenden PUBLISH_5 Block

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer-Ausgang - zeigt den Betriebszustand an
- **STATUS** (WSTRING): Statusinformationen und Fehlermeldungen
- **RD_1** bis **RD_5** (ANY): Empfangene Datenpunkte 1 bis 5 mit beliebigem Datentyp

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_5 Block initialisiert sich über das INIT-Ereignis und stellt anschließend eine Verbindung zum entsprechenden PUBLISH_5 Block her. Bei erfolgreicher Initialisierung bestätigt er dies über INITO. Sobald neue Daten vom Publisher verfügbar sind, werden diese über das IND-Ereignis mit den entsprechenden Datenausgängen RD_1 bis RD_5 ausgegeben. Der STATUS-Ausgang liefert dabei Informationen über den Verbindungszustand und eventuelle Fehler.

## Technische Besonderheiten
- Unterstützt bis zu fünf verschiedene Datenpunkte gleichzeitig
- Verwendet WSTRING für ID und STATUS für internationale Zeichensatzunterstützung
- ANY-Typ bei den Datenausgängen ermöglicht flexible Datentypen
- Generische Implementierung durch GEN_SUBSCRIBE Basisklasse

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisierungsphase**: Verarbeitung von INIT mit ID-Parameter
3. **Verbunden**: Erfolgreiche Verbindung zum Publisher, bereit für Datenempfang
4. **Datenempfang**: Verarbeitung eingehender Daten und Ausgabe über IND

## Anwendungsszenarien
- Verteilte Automatisierungssysteme
- Datenverteilung in Produktionsanlagen
- Maschine-zu-Maschine-Kommunikation
- Überwachungssysteme mit mehreren Sensordaten
- SCADA-Systeme mit dezentralen Datenquellen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren SUBSCRIBE-Blöcken bietet SUBSCRIBE_5 die Möglichkeit, bis zu fünf verschiedene Datenpunkte parallel zu empfangen. Die Verwendung von ANY-Typen macht ihn flexibler als typspezifische Subscribe-Blöcke, erfordert jedoch eine korrekte Typzuordnung zum entsprechenden Publisher.

## Fazit
Der SUBSCRIBE_5 Funktionsblock stellt eine leistungsfähige und flexible Lösung für den Empfang multipler Datenströme in verteilten Automatisierungssystemen dar. Seine generische Implementierung und die Unterstützung verschiedener Datentypen machen ihn besonders geeignet für komplexe Anwendungen mit variablen Datenstrukturen.