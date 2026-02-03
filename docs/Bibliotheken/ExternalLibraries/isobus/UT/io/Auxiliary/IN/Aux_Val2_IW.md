# Aux_Val2_IW

```{index} single: Aux_Val2_IW
```

<img width="1351" height="292" alt="image" src="https://github.com/user-attachments/assets/3d049160-0f3d-47ee-99f9-04a4361361bc" />

* * * * * * * * * *

## Einleitung
Der Aux_Val2_IW ist ein Eingabeservice-Schnittstellen-Funktionsblock für Wort-Eingabedaten. Dieser Baustein dient als Schnittstelle zur Kommunikation mit Ressourcen und ermöglicht die Verarbeitung von 16-Bit-Wort-Eingabedaten in verteilten Automatisierungssystemen.

![Aux_Val2_IW](Aux_Val2_IW.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - Initialisiert den Funktionsblock mit Parametern
- **REQ**: Service-Anfrage - Löst eine Serviceanfrage aus

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt die erfolgte Initialisierung
- **CNF**: Bestätigung der angeforderten Service - Bestätigt eine Serviceanfrage
- **IND**: Indikation von der Ressource - Signalisiert eingehende Daten von der Ressource

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer - Aktiviert/deaktiviert die Verarbeitung
- **PARAMS** (STRING): Service-Parameter - Konfigurationsparameter für den Service
- **u16ObjId** (UINT): Objekt-ID - Identifikator für das Datenobjekt (Initialwert: ID_NULL)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer - Status der Ausgangsverarbeitung
- **STATUS** (STRING): Service-Status - Rückmeldung über den Servicezustand
- **IN** (WORD): Eingabedaten von der Ressource - Die empfangenen 16-Bit-Wortdaten

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock arbeitet als Service-Schnittstelle für Wort-Eingabedaten. Bei der INIT-Initialisierung werden die Service-Parameter und die Objekt-ID konfiguriert. Über REQ-Ereignisse können Serviceanfragen gestellt werden, die mit CNF-Ereignissen bestätigt werden. Bei eingehenden Daten von der Ressource wird ein IND-Ereignis mit den empfangenen Wortdaten ausgegeben.

## Technische Besonderheiten
- Verarbeitet 16-Bit-Wort-Datentypen (WORD)
- Unterstützt konfigurierbare Objekt-IDs für die Datenidentifikation
- Bietet umfangreiche Statusrückmeldungen über den SERVICE-Status
- Ermöglicht parametrierbare Service-Konfiguration

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor der INIT-Initialisierung
2. **Initialisiert**: Nach erfolgreicher INIT-Verarbeitung mit INITO-Bestätigung
3. **Bereit**: Für REQ-Anfragen und IND-Indikationen
4. **Service aktiv**: Während der Bearbeitung von Serviceanfragen

## Anwendungsszenarien
- Einlesen von 16-Bit-Sensordaten in verteilten Systemen
- Kommunikation mit ISOBUS-kompatiblen Geräten
- Eingabe von Wort-Daten in Automatisierungsanwendungen
- Schnittstelle zu externen Ressourcen für Datenerfassung

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Eingabebausteinen bietet Aux_Val2_IW erweiterte Service-Funktionalität mit parametrierbarer Konfiguration, Statusrückmeldungen und Objekt-Identifikation. Er ist speziell für die Verarbeitung von Wort-Daten (16-Bit) ausgelegt.

## Fazit
Der Aux_Val2_IW Funktionsblock stellt eine leistungsfähige Service-Schnittstelle für die Verarbeitung von Wort-Eingabedaten in industriellen Automatisierungssystemen bereit. Durch seine umfangreiche Parametrierbarkeit und Statusrückmeldungen eignet er sich besonders für anspruchsvolle Anwendungen mit hohen Anforderungen an Zuverlässigkeit und Diagnosefähigkeit.