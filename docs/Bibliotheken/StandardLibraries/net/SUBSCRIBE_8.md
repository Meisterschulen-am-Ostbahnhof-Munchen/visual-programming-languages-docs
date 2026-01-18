# SUBSCRIBE_8

```{index} single: SUBSCRIBE_8
```

<img width="1108" height="438" alt="image" src="https://github.com/user-attachments/assets/e671e3e6-2912-493f-ad24-79f5c5e9dfce" />

* * * * * * * * * *

## Einleitung
Der SUBSCRIBE_8 Funktionsblock dient als Abonnent für einen PUBLISH_8 Block und ermöglicht den Empfang von bis zu 8 verschiedenen Datenwerten über eine Kommunikationsverbindung. Der Block implementiert ein Publish-Subscribe-Kommunikationsmuster und ist Teil des iec61499::net Pakets.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** - Initialisierungsereignis
  - Verknüpft mit: QI, ID
- **RSP** - Response-Ereignis
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO** - Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **IND** - Indikationsereignis bei neuen Daten
  - Verknüpft mit: QO, STATUS, RD_1 bis RD_8

### **Daten-Eingänge**
- **QI** (BOOL) - Qualifizierter Eingang für Initialisierung
- **ID** (WSTRING) - Identifikationsstring für die Verbindung

### **Daten-Ausgänge**
- **QO** (BOOL) - Qualifizierter Ausgang
- **STATUS** (WSTRING) - Statusinformationen
- **RD_1** bis **RD_8** (ANY) - Empfangene Datenwerte 1 bis 8

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_8 Block initialisiert sich über das INIT-Ereignis und stellt dabei eine Verbindung zu einem entsprechenden PUBLISH_8 Block her. Nach erfolgreicher Initialisierung bestätigt er dies mit dem INITO-Ereignis. Bei empfangenen Daten vom Publisher wird das IND-Ereignis ausgelöst und die empfangenen Daten über die RD_1 bis RD_8 Ausgänge bereitgestellt.

## Technische Besonderheiten
- Unterstützt den Datentyp ANY für alle Datenausgänge, was maximale Flexibilität bei den übertragenen Datentypen ermöglicht
- Verwendet WSTRING für Statusmeldungen und Identifikation
- Implementiert ein zuverlässiges Initialisierungsprotokoll mit Qualifikationsbits
- Kann bis zu 8 verschiedene Datenwerte parallel empfangen

## Zustandsübersicht
1. **Nicht initialisiert** - Block wartet auf INIT-Ereignis
2. **Initialisierung** - Verarbeitung des INIT-Ereignisses
3. **Bereit** - Erfolgreich initialisiert, wartet auf Daten
4. **Datenempfang** - Verarbeitung eingehender Daten mit IND-Auslösung

## Anwendungsszenarien
- Verteilte Steuerungssysteme mit Datenverteilung
- Überwachungssysteme mit zentraler Datenerfassung
- Kommunikation zwischen verschiedenen Steuerungskomponenten
- Systeme mit Publish-Subscribe-Architektur

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Subscribe-Blöcken bietet SUBSCRIBE_8 die Möglichkeit, bis zu 8 verschiedene Datenwerte parallel zu empfangen. Die Verwendung des ANY-Datentyps ermöglicht eine höhere Flexibilität als typspezifische Subscribe-Blöcke.

## Fazit
Der SUBSCRIBE_8 Funktionsblock stellt eine leistungsstarke und flexible Lösung für Publish-Subscribe-Kommunikation in verteilten Automatisierungssystemen dar. Seine Fähigkeit, multiple Datenwerte unterschiedlicher Typen zu empfangen, macht ihn besonders geeignet für komplexe Kommunikationsszenarien in industriellen Steuerungssystemen.
