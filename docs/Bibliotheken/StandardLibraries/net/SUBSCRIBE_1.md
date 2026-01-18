# SUBSCRIBE_1

```{index} single: SUBSCRIBE_1
```

<img width="1067" height="302" alt="image" src="https://github.com/user-attachments/assets/952821fc-318a-4f24-8140-74d1dc6759eb" />

* * * * * * * * * *

## Einleitung
Der SUBSCRIBE_1 Funktionsblock dient zum Abonnieren von Daten eines PUBLISH_1 Blocks. Er ermöglicht die Kommunikation zwischen verschiedenen Komponenten in einem verteilten System, indem er Daten von einem Publisher empfängt und bei neuen Daten verfügbar macht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit den zugehörigen Daten QI und ID
- **RSP**: Response-Ereignis mit zugehörigem Daten QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsausgang mit den zugehörigen Daten QO und STATUS
- **IND**: Indikationsereignis bei neuen verfügbaren Daten mit zugehörigen Daten QO, STATUS und RD_1

### **Daten-Eingänge**
- **QI** (BOOL): Qualifier Input - Steuert die Aktivierung des Blocks
- **ID** (WSTRING): Identifikator - Eindeutige ID für die Abonnement-Verbindung

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifier Output - Status der Blockausführung
- **STATUS** (WSTRING): Statusinformationen als Unicode-String
- **RD_1** (ANY): Empfangene Daten - Kann beliebigen Datentyp enthalten

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der SUBSCRIBE_1 Block initialisiert sich über das INIT-Ereignis und abonniert dabei Daten eines PUBLISH_1 Blocks mit der angegebenen ID. Bei erfolgreicher Initialisierung bestätigt er dies über INITO. Wenn neue Daten vom Publisher verfügbar sind, wird das IND-Ereignis ausgelöst und die empfangenen Daten über RD_1 bereitgestellt. Der STATUS-Ausgang liefert dabei Statusinformationen über den Abonnement-Vorgang.

## Technische Besonderheiten
- Verwendet WSTRING für ID und STATUS für Unicode-Kompatibilität
- RD_1 unterstützt den ANY-Datentyp für maximale Flexibilität bei den empfangenen Daten
- Zwei getrennte Ereignispfade für Initialisierung und Datenempfang
- Qualifier-Eingänge (QI) und -Ausgänge (QO) für zuverlässige Zustandssteuerung

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Abonnement aktiv, wartet auf Daten vom Publisher
3. **Datenempfang**: Verarbeitet eingehende Daten und triggert IND-Ereignis

## Anwendungsszenarien
- Verteile Steuerungssysteme mit Datenverteilung
- IoT-Anwendungen mit Publisher-Subscriber-Architektur
- Industrie 4.0 Kommunikationsstrukturen
- Echtzeit-Datenaustausch zwischen verschiedenen Steuerungskomponenten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Kommunikationsblöcken bietet SUBSCRIBE_1 eine spezialisierte Lösung für das Publisher-Subscriber-Muster mit Fokus auf Flexibilität durch den ANY-Datentyp und Unicode-Unterstützung.

## Fazit
Der SUBSCRIBE_1 Funktionsblock ist ein essentieller Baustein für verteilte Systeme in 4diac, der eine robuste und flexible Kommunikation zwischen verschiedenen Komponenten ermöglicht. Seine einfache Schnittstelle und die Unterstützung beliebiger Datentypen machen ihn vielseitig einsetzbar in verschiedenen Automatisierungsanwendungen.
