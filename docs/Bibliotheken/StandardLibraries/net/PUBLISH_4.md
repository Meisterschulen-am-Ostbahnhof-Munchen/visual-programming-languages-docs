# PUBLISH_4

```{index} single: PUBLISH_4
```

<img width="1179" height="342" alt="image" src="https://github.com/user-attachments/assets/0369a464-ad16-499d-9887-36a8fca536b5" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_4 Funktionsblock dient zur Veröffentlichung von Daten an einen oder mehrere SUBSCRIBE_4 Blöcke. Er ermöglicht die unbestätigte Übertragung von bis zu vier verschiedenen Datenwerten über ein Publish-Subscribe-Kommunikationsmuster.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanforderung für Daten (unbestätigt) mit zugehörigen Daten QI, SD_1, SD_2, SD_3 und SD_4

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit zugehörigen Daten QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden, mit zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung und Sendeoperationen
- **ID** (WSTRING): Identifikationsstring für die Kommunikation
- **SD_1** (ANY): Erster zu sendender Datenwert (beliebiger Datentyp)
- **SD_2** (ANY): Zweiter zu sendender Datenwert (beliebiger Datentyp)
- **SD_3** (ANY): Dritter zu sendender Datenwert (beliebiger Datentyp)
- **SD_4** (ANY): Vierter zu sendender Datenwert (beliebiger Datentyp)

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für Ausgangsereignisse
- **STATUS** (WSTRING): Statusinformationen als Wide-String

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_4 Block initialisiert sich über das INIT-Ereignis und bestätigt dies mit INITO. Nach erfolgreicher Initialisierung können über das REQ-Ereignis bis zu vier verschiedene Datenwerte (SD_1 bis SD_4) gleichzeitig an alle verbundenen SUBSCRIBE_4 Blöcke gesendet werden. Die Datenübertragung erfolgt unbestätigt, wobei der Block lediglich bestätigt, dass die Daten gesendet wurden (CNF), nicht jedoch, dass sie empfangen wurden.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (ANY) für alle vier Datenkanäle
- Verwendet Wide-Strings (WSTRING) für ID und STATUS
- Unbestätigter Sendemodus (fire-and-forget)
- Maximale Kapazität von vier gleichzeitigen Datenwerten
- Generische Implementierung als GEN_PUBLISH

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block bereit zum Empfang von REQ-Ereignissen
3. **Sendeaktiv**: Verarbeitung von REQ-Ereignissen und Auslösung von CNF

## Anwendungsszenarien
- Verteilte Systeme mit Publish-Subscribe-Architektur
- Echtzeit-Datenverteilung an mehrere Empfänger
- Systeme mit unidirektionaler Datenkommunikation
- Anwendungen, die gleichzeitige Übertragung mehrerer Datenwerte benötigen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu bestätigten Kommunikationsblöcken bietet PUBLISH_4 geringere Latenz durch den unbestätigten Sendemodus. Gegenüber Blöcken mit weniger Datenkanälen ermöglicht er die gleichzeitige Übertragung von bis zu vier verschiedenen Datenwerten.

## Fazit
Der PUBLISH_4 Funktionsblock ist eine effiziente Lösung für unbestätigte Datenverteilung in verteilten Systemen. Seine Flexibilität bei der Unterstützung beliebiger Datentypen und die Möglichkeit, vier Datenwerte parallel zu senden, machen ihn besonders geeignet für komplexe Kommunikationsszenarien in industriellen Automatisierungssystemen.