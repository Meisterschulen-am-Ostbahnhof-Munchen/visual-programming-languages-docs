# SEND_RECV_1_1

```{index} single: SEND_RECV_1_1
```

<img width="1257" height="287" alt="image" src="https://github.com/user-attachments/assets/91b59d90-84f9-436c-93b0-702ec3b5def5" />

* * * * * * * * * *

## Einleitung
Der SEND_RECV_1_1 Funktionsblock implementiert eine Duplex-Kommunikationsschnittstelle für den bidirektionalen Datenaustausch über Kommunikationskanäle. Der Baustein ermöglicht sowohl das Senden als auch das Empfangen von Daten über einen gemeinsamen Kanal und unterstützt generische Datentypen für maximale Flexibilität.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit zugehörigen Daten QI und ID
- **REQ**: Sende-Anfrage mit zugehörigen Daten QI und SD_1
- **RSP**: Empfangs-Anfrage mit zugehörigen Daten QI und SD_1

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit QO und STATUS
- **CNF**: Sende-Bestätigung mit QO, STATUS und RD_1
- **IND**: Empfangs-Indikation mit QO, STATUS und RD_1

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **ID** (WSTRING): Kanal-Identifikator
- **SD_1** (ANY): Zu sendende Daten (generischer Datentyp)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (WSTRING): Kanal-Statusinformation
- **RD_1** (ANY): Empfangene Daten (generischer Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock arbeitet als bidirektionale Kommunikationsschnittstelle, die über den INIT-Ereigniseingang initialisiert wird. Nach erfolgreicher Initialisierung können über REQ Daten gesendet und über RSP Daten empfangen werden. Die Kommunikation erfolgt über einen durch ID identifizierten Kanal. Der generische ANY-Datentyp ermöglicht die Übertragung beliebiger Datenstrukturen.

## Technische Besonderheiten
- Unterstützung generischer Datentypen (ANY) für maximale Flexibilität
- Bidirektionale Kommunikation über einen gemeinsamen Kanal
- Unicode-String-Unterstützung für Kanal-IDs und Statusmeldungen
- Separate Qualifizierer für Eingangs- und Ausgangsereignisse
- Statusrückmeldung über WSTRING für detaillierte Fehlerinformationen

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor INIT-Aufruf
2. **Initialisiert**: Nach erfolgreicher INIT/INITO-Sequenz
3. **Sende-Betrieb**: Während REQ/CNF-Operation
4. **Empfangs-Betrieb**: Während RSP/IND-Operation

## Anwendungsszenarien
- Client-Server-Kommunikation in verteilten Systemen
- Bidirektionale Datenübertragung zwischen Steuerungskomponenten
- Protokollimplementierungen mit Anfrage-Antwort-Mustern
- Netzwerkkommunikation in industriellen Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen SEND- oder RECV-Blöcken bietet SEND_RECV_1_1 die kombinierte Funktionalität beider Operationen in einem einzigen Baustein. Die Duplex-Fähigkeit unterscheidet ihn von Simplex-Kommunikationsblöcken und ermöglicht effizientere Kommunikationsmuster.

## Fazit
Der SEND_RECV_1_1 Funktionsblock stellt eine vielseitige Lösung für bidirektionale Kommunikationsanforderungen in verteilten Automatisierungssystemen dar. Durch die Unterstützung generischer Datentypen und die kombinierte Sende-/Empfangsfunktionalität bietet er eine effiziente Basis für verschiedene Kommunikationsszenarien.
