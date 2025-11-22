# PUBLISH_10

<img width="997" height="411" alt="image" src="https://github.com/user-attachments/assets/02d71bb9-d435-4afe-a4ac-ea80ce21efeb" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_10 Funktionsblock dient zum Verteilen von Daten an einen oder mehrere SUBSCRIBE_10 Blöcke. Er ermöglicht die unbestätigte Übertragung von bis zu 10 verschiedenen Datenwerten über ein Publish-Subscribe-Kommunikationsmuster.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanforderung für unbestätigte Datenübertragung mit 10 Datenvariablen

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit Statusinformationen
- **CNF**: Bestätigung, dass Daten gesendet wurden

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung (TRUE = aktivieren, FALSE = deaktivieren)
- **ID** (WSTRING): Identifikationsstring für den Kommunikationskanal
- **SD_1** bis **SD_10** (ANY): 10 verschiedene zu sendende Datenwerte beliebigen Typs

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer-Ausgang (TRUE = erfolgreich, FALSE = fehlgeschlagen)
- **STATUS** (WSTRING): Statusinformationen als Unicode-String

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_10 Block arbeitet nach dem Publish-Subscribe-Prinzip. Nach erfolgreicher Initialisierung mit dem INIT-Ereignis können über das REQ-Ereignis bis zu 10 verschiedene Datenwerte gleichzeitig an alle angemeldeten Subscriber verteilt werden. Die Datenübertragung erfolgt unbestätigt, was bedeutet, dass der Block keine Rückmeldung von den Empfängern erwartet.

## Technische Besonderheiten
- Unterstützt bis zu 10 verschiedene Datenquellen gleichzeitig
- Verwendet den generischen Datentyp ANY für maximale Flexibilität
- Unicode-String-Unterstützung für ID und STATUS
- Unbestätigte Kommunikation für reduzierte Latenz
- Generische Implementierung durch GEN_PUBLISH Basisklasse

## Zustandsübersicht
1. **Nicht initialisiert**: Block ist inaktiv
2. **Initialisiert**: Block ist bereit für Datenverteilung
3. **Sendebereit**: Verarbeitet REQ-Ereignisse und verteilt Daten

## Anwendungsszenarien
- Verteilung von Sensordaten an mehrere Verbraucher
- Broadcast-Kommunikation in verteilten Systemen
- Datenverteilung in Echtzeit-Steuerungssystemen
- Multi-Consumer Datenpipeline-Architekturen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu bestätigten Kommunikationsblöcken bietet PUBLISH_10 reduzierte Latenz durch unbestätigte Übertragung. Gegenüber Blöcken mit weniger Datenkanälen ermöglicht er die gleichzeitige Verteilung mehrerer Datenströme.

## Fazit
Der PUBLISH_10 Funktionsblock ist eine leistungsstarke Lösung für unbestätigte Multi-Daten-Publish-Subscribe-Kommunikation in IEC 61499-Systemen. Seine Flexibilität bei der Datenaufnahme und die Unterstützung für bis zu 10 parallele Datenkanäle machen ihn ideal für komplexe Datenverteilungsaufgaben in industriellen Automatisierungssystemen.
