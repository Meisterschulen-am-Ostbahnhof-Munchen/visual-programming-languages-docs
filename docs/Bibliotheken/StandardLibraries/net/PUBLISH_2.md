# PUBLISH_2

```{index} single: PUBLISH_2
```

<img width="1179" height="286" alt="image" src="https://github.com/user-attachments/assets/ae23ed15-e54c-43ad-8379-07e0e8126f56" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_2-Funktionsblock dient zum Senden von Daten an einen oder mehrere SUBSCRIBE_2-Blöcke. Er ermöglicht eine unbestätigte Kommunikation zwischen verschiedenen Komponenten in einem verteilten System.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit den zugehörigen Daten QI und ID
- **REQ**: Anforderungsereignis zum Senden von Daten mit den zugehörigen Daten QI, SD_1 und SD_2

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit den zugehörigen Daten QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden, mit den zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung und Betrieb
- **ID** (WSTRING): Identifikator für die Kommunikation
- **SD_1** (ANY): Erster zu sendender Datenwert (beliebiger Datentyp)
- **SD_2** (ANY): Zweiter zu sendender Datenwert (beliebiger Datentyp)

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für den Ausgangszustand
- **STATUS** (WSTRING): Statusinformationen über den Betriebszustand

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der PUBLISH_2-Block initialisiert sich über das INIT-Ereignis und sendet anschließend Daten über das REQ-Ereignis. Die Daten SD_1 und SD_2 werden an alle angeschlossenen SUBSCRIBE_2-Blöcke verteilt. Die Kommunikation erfolgt unbestätigt, was bedeutet, dass keine Rückmeldung von den Empfängern erwartet wird.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen für SD_1 und SD_2
- Verwendet WSTRING für ID und STATUS für internationale Zeichenunterstützung
- Unbestätigter Kommunikationsmodus (Publish/Subscribe-Pattern)
- Flexible Datenübertragung mit zwei separaten Datenkanälen

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist betriebsbereit und kann REQ-Ereignisse verarbeiten
3. **Sendebereit**: Verarbeitet REQ-Ereignisse und sendet Daten an Subscriber

## Anwendungsszenarien
- Verteilte Systeme mit mehreren Datenempfängern
- Echtzeit-Datenverteilung ohne Bestätigungsmechanismus
- Systeme mit variablen Datentypen
- Kommunikation zwischen verschiedenen Steuerungskomponenten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu bestätigten Kommunikationsblöcken bietet PUBLISH_2 eine höhere Performance bei gleichzeitig geringerer Zuverlässigkeit. Die Unterstützung für beliebige Datentypen macht ihn flexibler als typspezifische Kommunikationsblöcke.

## Fazit
Der PUBLISH_2-Block ist ein effizientes Werkzeug für unbestätigte Datenverteilung in verteilten Systemen. Seine Flexibilität bei der Datentypunterstützung und die einfache Handhabung machen ihn ideal für Szenarien, in denen Performance wichtiger ist als garantierte Zustellung.