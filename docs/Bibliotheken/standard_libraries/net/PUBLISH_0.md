# PUBLISH_0

<img width="1376" height="275" alt="image" src="https://github.com/user-attachments/assets/f9770c1e-3c0e-439f-9f65-d01566aeb2a0" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_0-Funktionsblock dient zum Veröffentlichen von Daten für einen oder mehrere SUBSCRIBE_0-Blöcke. Er ermöglicht eine unbestätigte Kommunikation zwischen verschiedenen Komponenten in einem 4diac-System.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanforderung für Daten (unbestätigt) mit zugehörigem Daten QI

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit zugehörigen Daten QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden mit zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualitätsindikator für die Blockaktivierung
- **ID** (WSTRING): Identifikationsstring für die Kommunikation

### **Daten-Ausgänge**
- **QO** (BOOL): Qualitätsindikator für die Blockausgabe
- **STATUS** (WSTRING): Statusinformationen über die ausgeführte Operation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_0-Block ermöglicht die Veröffentlichung von Daten über ein Publish-Subscribe-Muster. Bei Initialisierung (INIT) wird der Block mit einer spezifischen ID konfiguriert. Bei einer Sendeanforderung (REQ) werden die Daten an alle registrierten Subscriber verteilt. Die Kommunikation erfolgt unbestätigt, was bedeutet, dass keine Rückmeldung von den Empfängern erwartet wird.

## Technische Besonderheiten
- Verwendet WSTRING-Datentypen für ID und STATUS für internationale Zeichenunterstützung
- Implementiert unbestätigte Kommunikation (unconfirmed)
- Unterstützt multiple Subscriber über eine einzige Publish-Instanz
- Generische Implementierung als GEN_PUBLISH

## Zustandsübersicht
Der Block durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Block ist betriebsbereit, aber nicht konfiguriert
2. **Initialisiert**: Block ist konfiguriert und bereit zum Senden
3. **Sendebereit**: Block kann Daten an Subscriber verteilen

## Anwendungsszenarien
- Verteilung von Sensordaten an mehrere Verarbeitungsknoten
- Broadcast von Systemstatusinformationen
- Verteilung von Steuerbefehlen an multiple Aktoren
- Datenaustausch in verteilten Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu bestätigten Kommunikationsblöcken bietet PUBLISH_0:
- Höhere Performance durch unbestätigte Übertragung
- Geringere Latenzzeiten
- Einfacherere Implementierung
- Keine Garantie der Zustellung

## Fazit
Der PUBLISH_0-Block ist ein effizientes Werkzeug für unbestätigte Kommunikation in verteilten Steuerungssystemen. Seine einfache Schnittstelle und die Unterstützung für multiple Empfänger machen ihn ideal für Szenarien, in denen Performance wichtiger ist als garantierte Zustellung.
