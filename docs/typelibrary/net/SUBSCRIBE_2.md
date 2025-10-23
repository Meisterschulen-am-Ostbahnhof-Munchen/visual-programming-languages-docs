# SUBSCRIBE_2

<img width="1291" height="336" alt="image" src="https://github.com/user-attachments/assets/55eb6a91-e2ee-4848-813e-eb2568e1ed1c" />

* * * * * * * * * *

## Einleitung
Der SUBSCRIBE_2-Funktionsblock dient als Abonnent für einen PUBLISH_2-Block und ermöglicht den Empfang von Daten über ein Publish-Subscribe-Kommunikationsmuster. Der Block kann zwei verschiedene Datenwerte von einem Publisher empfangen und weiterverarbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit den zugehörigen Daten QI und ID
- **RSP**: Response-Ereignis mit zugehörigem Datenwert QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den Daten QO und STATUS
- **IND**: Indikationsereignis bei neuen verfügbaren Daten mit QO, STATUS, RD_1 und RD_2

### **Daten-Eingänge**
- **QI** (BOOL): Qualifier Input - Steuert die Aktivierung des Blocks
- **ID** (WSTRING): Identifikationsstring zur Zuordnung zum entsprechenden Publisher

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifier Output - Status der Blockoperation
- **STATUS** (WSTRING): Statusinformationen als Unicode-String
- **RD_1** (ANY): Empfangene Daten 1 (beliebiger Datentyp)
- **RD_2** (ANY): Empfangene Daten 2 (beliebiger Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_2-Block initialisiert sich über das INIT-Ereignis und abonniert dabei einen spezifischen Publisher mittels des ID-Identifikators. Nach erfolgreicher Initialisierung bestätigt der Block dies über INITO. Bei eingehenden Daten vom Publisher löst der Block das IND-Ereignis aus und stellt die empfangenen Daten über RD_1 und RD_2 zur Verfügung.

## Technische Besonderheiten
- Unterstützt den Empfang von zwei verschiedenen Datenwerten gleichzeitig
- Verwendet WSTRING für Status- und Identifikationsinformationen
- Implementiert generische Datentypen (ANY) für maximale Flexibilität
- Basiert auf dem GEN_SUBSCRIBE-Generic-Template

## Zustandsübersicht
Der Block durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist bereit zum Empfang von Daten
3. **Datenempfang**: Verarbeitung eingehender Daten und Auslösen von IND

## Anwendungsszenarien
- Verteilte Steuerungssysteme mit Datenverteilung
- IoT-Anwendungen mit Publisher-Subscriber-Architektur
- Industrielle Automatisierung mit dezentraler Datenkommunikation
- Systeme mit flexiblen Datentypanforderungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren SUBSCRIBE-Blöcken bietet SUBSCRIBE_2 die Möglichkeit, zwei verschiedene Datenwerte parallel zu empfangen. Die Verwendung von ANY-Datentypen ermöglicht eine höhere Flexibilität gegenüber typspezifischen Implementationen.

## Fazit
Der SUBSCRIBE_2-Block stellt eine erweiterte Lösung für Publish-Subscribe-Kommunikation in 4diac-Systemen dar, die durch die Unterstützung zweier Datenkanäle und generischer Datentypen besonders flexibel einsetzbar ist.
