# SUBSCRIBE_4

<img width="1291" height="393" alt="image" src="https://github.com/user-attachments/assets/64c5b7ee-a7e0-4217-a6d8-5b4904bf79d4" />

* * * * * * * * * *
## Einleitung
Der SUBSCRIBE_4 Funktionsblock dient zum Abonnieren von Daten eines PUBLISH_4 Blocks. Er ermöglicht den Empfang von bis zu vier verschiedenen Datenpunkten über eine Kommunikationsverbindung und stellt diese bei Verfügbarkeit zur Verfügung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (Typ: EInit) - Initialisierungsereignis
  - Verknüpft mit: QI, ID
- **RSP** (Typ: Event) - Response-Ereignis
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO** (Typ: EInit) - Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **IND** (Typ: Event) - Datenverfügbarkeitsmeldung
  - Verknüpft mit: QO, STATUS, RD_1, RD_3, RD_2, RD_4

### **Daten-Eingänge**
- **QI** (BOOL) - Qualifizierter Input (Aktivierung/Deaktivierung)
- **ID** (WSTRING) - Identifikator für die Kommunikationsverbindung

### **Daten-Ausgänge**
- **QO** (BOOL) - Qualifizierter Output (Statusrückmeldung)
- **STATUS** (WSTRING) - Statusinformationen
- **RD_1** (ANY) - Empfangene Daten 1
- **RD_2** (ANY) - Empfangene Daten 2
- **RD_3** (ANY) - Empfangene Daten 3
- **RD_4** (ANY) - Empfangene Daten 4

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_4 Block initialisiert bei Empfang des INIT-Ereignisses eine Abonnement-Verbindung zu einem PUBLISH_4 Block unter Verwendung der angegebenen ID. Nach erfolgreicher Initialisierung bestätigt er dies mit INITO. Bei Verfügbarkeit neuer Daten vom Publisher wird das IND-Ereignis ausgelöst und die empfangenen Daten über die RD_1 bis RD_4 Ausgänge bereitgestellt.

## Technische Besonderheiten
- Unterstützt den Empfang von bis zu vier verschiedenen Datentypen (ANY-Typ)
- Verwendet WSTRING für Status- und Identifikationsinformationen
- Generische Implementierung durch GEN_SUBSCRIBE Basisklasse
- Robuste Fehlerbehandlung über STATUS-Ausgabe

## Zustandsübersicht
1. **Inaktiv**: Block ist nicht initialisiert
2. **Initialisiert**: Abonnement aktiv, wartet auf Daten
3. **Datenempfang**: Verarbeitet eingehende Daten und gibt IND-Ereignis aus

## Anwendungsszenarien
- Verteilte Automatisierungssysteme
- Datenverteilung in dezentralen Steuerungen
- Kommunikation zwischen verschiedenen Steuerungskomponenten
- Überwachungssysteme mit Datenabonnement

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren SUBSCRIBE-Blöcken bietet SUBSCRIBE_4 die Möglichkeit, bis zu vier verschiedene Datenpunkte gleichzeitig zu empfangen. Die erweiterte Funktionalität macht ihn besonders geeignet für komplexere Kommunikationsszenarien, bei denen mehrere Datenquellen konsolidiert werden müssen.

## Fazit
Der SUBSCRIBE_4 Funktionsblock stellt eine leistungsfähige Lösung für Abonnement-basierte Kommunikation in IEC 61499-Systemen dar. Seine Fähigkeit, mehrere Datenpunkte parallel zu verwalten, macht ihn zu einer flexiblen Wahl für anspruchsvolle Automatisierungsanwendungen mit verteilter Datenkommunikation.
