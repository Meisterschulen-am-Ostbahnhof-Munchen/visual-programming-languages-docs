# SUBSCRIBE_10

<img width="775" height="412" alt="image" src="https://github.com/user-attachments/assets/ac0698e2-c9c3-4335-bb7b-9d6afdab86ca" />

* * * * * * * * * *
## Einleitung
Der SUBSCRIBE_10 Funktionsblock dient als Abonnent in einem Publish-Subscribe-Kommunikationsmuster und ermöglicht das Empfangen von Daten von einem PUBLISH_10 Block. Der Block kann bis zu 10 verschiedene Datenwerte gleichzeitig empfangen und verarbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (Typ: EInit) - Initialisierungsereignis
  - Verknüpft mit: QI, ID
- **RSP** (Typ: Event) - Response-Ereignis
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO** (Typ: EInit) - Initialisierungsausgang
  - Verknüpft mit: QO, STATUS
- **IND** (Typ: Event) - Indikationsereignis (Neue Daten verfügbar)
  - Verknüpft mit: QO, STATUS, RD_1 bis RD_10

### **Daten-Eingänge**
- **QI** (BOOL) - Qualifizierter Eingang (Aktivierung)
- **ID** (WSTRING) - Identifikationsstring für die Verbindung

### **Daten-Ausgänge**
- **QO** (BOOL) - Qualifizierter Ausgang (Status)
- **STATUS** (WSTRING) - Statusinformation
- **RD_1** bis **RD_10** (ANY) - Empfangene Datenwerte 1-10

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_10 Block initialisiert sich über das INIT-Ereignis und verbindet sich mit einem entsprechenden PUBLISH_10 Block basierend auf der angegebenen ID. Sobald neue Daten vom Publisher verfügbar sind, wird das IND-Ereignis ausgelöst und die empfangenen Daten über die RD_1 bis RD_10 Ausgänge bereitgestellt.

## Technische Besonderheiten
- Unterstützt den Datentyp ANY für alle empfangenen Daten, was maximale Flexibilität bei den Datentypen bietet
- Kann bis zu 10 verschiedene Datenwerte parallel empfangen
- Verwendet WSTRING für Status- und Identifikationsinformationen
- Implementiert ein zuverlässiges Publish-Subscribe-Kommunikationsmuster

## Zustandsübersicht
1. **Nicht initialisiert**: Block ist inaktiv
2. **Initialisiert**: Verbindung zum Publisher hergestellt, wartet auf Daten
3. **Datenempfang**: Empfängt und verarbeitet eingehende Daten
4. **Fehlerzustand**: Bei Verbindungsproblemen oder Fehlern

## Anwendungsszenarien
- Verteilte Steuerungssysteme
- Datenverteilung in Automatisierungsnetzwerken
- Kommunikation zwischen verschiedenen Steuerungskomponenten
- Überwachungssysteme mit mehreren Datenquellen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Subscribe-Blöcken bietet SUBSCRIBE_10 die Möglichkeit, bis zu 10 verschiedene Datenwerte gleichzeitig zu empfangen, was ihn für komplexere Anwendungen mit mehreren Datenpunkten geeignet macht.

## Fazit
Der SUBSCRIBE_10 Funktionsblock ist ein leistungsstarkes Werkzeug für die verteilte Kommunikation in IEC 61499-Systemen. Seine Fähigkeit, bis zu 10 verschiedene Datenwerte zu verarbeiten und die flexible ANY-Datentypunterstützung machen ihn besonders geeignet für komplexe Automatisierungsanwendungen mit umfangreichen Datenaustauschanforderungen.
