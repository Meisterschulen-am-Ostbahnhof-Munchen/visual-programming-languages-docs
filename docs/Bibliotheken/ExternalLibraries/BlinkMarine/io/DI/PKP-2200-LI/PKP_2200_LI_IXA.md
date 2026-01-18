# PKP_2200_LI_IXA

```{index} single: PKP_2200_LI_IXA
```

<img width="1960" height="384" alt="image" src="https://github.com/user-attachments/assets/1b07f3e6-433e-4e24-be44-50268e3eb4f4" />

* * * * * * * * * *
## Einleitung
Der PKP_2200_LI_IXA ist ein zusammengesetzter Funktionsblock zur Verarbeitung von booleschen Eingangsdaten. Er dient als Schnittstelle für digitale Eingänge und bietet standardisierte Initialisierungs- und Abfragefunktionen für Eingabesignale.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung (mit QI, PARAMS, u8SAMember, Input)
- **REQ**: Service-Anfrage (mit QI)

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung (mit QO, STATUS)

### **Daten-Eingänge**
- **QI**: Ereignis-Eingangsqualifizierer (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **u8SAMember**: Knoten-SA (USINT) - Standardwert: PKP_2200::PKP_2200_DEFAULT
- **Input**: Eingangsidentifikation (BlinkMarine::io::DI::PKP_2200_LI_DI_S) - Standardwert: Invalid

### **Daten-Ausgänge**
- **QO**: Ereignis-Ausgangsqualifizierer (BOOL)
- **STATUS**: Service-Status (STRING)

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ AX

## Funktionsweise
Der Funktionsblock initialisiert sich über das INIT-Ereignis und bestätigt die erfolgreiche Initialisierung mit INITO. Über das REQ-Ereignis können Service-Anfragen gestellt werden. Die Eingabedaten werden über den Adapter IN verarbeitet und die Ergebnisse über die entsprechenden Ausgänge bereitgestellt.

## Technische Besonderheiten
- Verwendet standardisierte Initialisierungsprozeduren nach EInit-Typ
- Unterstützt Konfiguration über SA-Member (Standard: 21h)
- Bietet Fehlerbehandlung über STATUS-Ausgabe
- Implementiert qualifizierte Ereignisverarbeitung

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor INIT-Ereignis
2. **Initialisierung**: Während INIT-Verarbeitung
3. **Bereit**: Nach erfolgreicher Initialisierung (INITO)
4. **Service-Anfrage**: Während REQ-Verarbeitung

## Anwendungsszenarien
- Digitale Eingangssignalverarbeitung in Automatisierungssystemen
- IO-Kommunikation mit PKP-2200-kompatiblen Geräten
- Integration in verteilte Steuerungssysteme
- Boolesche Signalverarbeitung mit Qualitätsüberwachung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsblöcken bietet PKP_2200_LI_IXA erweiterte Funktionalität durch:
- Parametrierbare SA-Member-Konfiguration
- Detaillierte Statusrückmeldungen
- Standardisierte Initialisierungsprozeduren
- Adapter-basierte Schnittstelle

## Fazit
Der PKP_2200_LI_IXA ist ein robuster und flexibler Funktionsblock für die Verarbeitung digitaler Eingangssignale mit erweiterten Konfigurations- und Diagnosemöglichkeiten. Seine standardisierte Schnittstelle ermöglicht eine einfache Integration in komplexe Automatisierungssysteme.
