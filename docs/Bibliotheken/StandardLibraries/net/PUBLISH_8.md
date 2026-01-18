# PUBLISH_8

```{index} single: PUBLISH_8
```

<img width="1180" height="444" alt="image" src="https://github.com/user-attachments/assets/3ea0daaf-96d3-41f7-955f-9e7819185dd9" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_8 Funktionsblock dient zum Senden von Daten an einen oder mehrere SUBSCRIBE_8 Blöcke. Er implementiert ein Publisher-Subscriber-Kommunikationsmuster und ermöglicht die Verteilung von bis zu acht verschiedenen Datenwerten an abonnierte Empfänger.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanforderung für Daten (unbestätigt) mit allen acht SD_x Datenwerten

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden, mit QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung
- **ID** (WSTRING): Identifikator für die Kommunikation
- **SD_1** bis **SD_8** (ANY): Acht verschiedene Sendedaten beliebigen Typs

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für Ausgangszustand
- **STATUS** (WSTRING): Statusinformationen

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_8 Block ermöglicht die Verteilung von Daten über ein Publisher-Subscriber-Modell. Bei Empfang eines REQ-Ereignisses werden alle acht SD_x Datenwerte an alle abonnierten SUBSCRIBE_8 Blöcke gesendet. Die INIT-Initialisierung konfiguriert den Block für die Kommunikation, wobei der ID-Parameter zur Identifikation des Publishers dient.

## Technische Besonderheiten
- Unterstützt bis zu acht verschiedene Datenwerte beliebigen Typs (ANY)
- Verwendet Wide-String (WSTRING) für ID und STATUS für internationale Zeichenunterstützung
- Implementiert unbestätigte Kommunikation (REQ ohne direkte Empfangsbestätigung)
- Generische Implementierung basierend auf GEN_PUBLISH

## Zustandsübersicht
Der Block verfügt über zwei Hauptzustände:
1. **Nicht initialisiert**: Block ist betriebsbereit, aber nicht für Kommunikation konfiguriert
2. **Initialisiert**: Block ist konfiguriert und kann Daten an Subscriber verteilen

## Anwendungsszenarien
- Verteilung von Prozessdaten an mehrere Anzeige- oder Steuerungssysteme
- Implementierung von Daten-Broadcasting in verteilten Systemen
- Einsatz in SPS-Systemen für Maschine-zu-Maschine-Kommunikation
- Verwendung in Industrie-4.0-Anwendungen für flexible Datenverteilung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren PUBLISH-Blöcken bietet PUBLISH_8 die Möglichkeit, bis zu acht verschiedene Datenwerte parallel zu verteilen, was eine höhere Datendichte pro Kommunikationszyklus ermöglicht. Die Verwendung von ANY-Typen bietet maximale Flexibilität bei den zu übertragenden Datentypen.

## Fazit
Der PUBLISH_8 Funktionsblock ist eine leistungsstarke Lösung für die Verteilung multipler Datenwerte in verteilten Automatisierungssystemen. Seine Flexibilität bei den Datentypen und die Unterstützung für acht parallele Datenkanäle machen ihn ideal für komplexe Kommunikationsszenarien in industriellen Anwendungen.
