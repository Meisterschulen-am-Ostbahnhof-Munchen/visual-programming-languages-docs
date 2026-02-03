# Aux_Val1_IW

```{index} single: Aux_Val1_IW
```

<img width="1351" height="292" alt="image" src="https://github.com/user-attachments/assets/c88e5ead-0835-4374-be47-397bd18dd315" />

* * * * * * * * * *

## Einleitung
Der Aux_Val1_IW Funktionsblock ist ein Eingabeservice-Schnittstellen-Funktionsblock für Wort-Eingabedaten. Er dient als Schnittstelle zwischen der Steuerungslogik und externen Ressourcen zur Verarbeitung von 16-Bit-Wort-Eingabedaten im ISOBUS-Kontext.

![Aux_Val1_IW](Aux_Val1_IW.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung
  - Verknüpft mit: QI, PARAMS, u16ObjId
- **REQ**: Service-Anfrage
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **CNF**: Bestätigung der angeforderten Service-Anfrage
  - Verknüpft mit: QO, STATUS, IN
- **IND**: Indikation von der Ressource
  - Verknüpft mit: QO, STATUS, IN

### **Daten-Eingänge**
- **QI**: Event-Eingabe-Qualifier (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **u16ObjId**: Objekt-ID (UINT) - Initialwert: ID_NULL

### **Daten-Ausgänge**
- **QO**: Event-Ausgabe-Qualifier (BOOL)
- **STATUS**: Service-Status (STRING)
- **IN**: Eingabedaten von der Ressource (WORD)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock ermöglicht die Kommunikation mit externen Ressourcen zur Erfassung von Wort-Eingabedaten. Über die INIT-Initialisierung werden die Service-Parameter und die Objekt-ID konfiguriert. Die REQ-Anfrage löst die Datenerfassung aus, während IND-Ereignisse asynchrone Datenupdates von der Ressource signalisieren.

## Technische Besonderheiten
- Verwendet WORD-Datentyp für 16-Bit-Datenerfassung
- ISOBUS-kompatible Schnittstelle
- Unterstützt asynchrone Datenindikationen
- Initialisierung mit konfigurierbaren Parametern
- Fehlerstatus-Rückmeldung über STATUS-Ausgabe

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Wartet auf INIT-Ereignis
2. **Initialisiert**: Bereit für REQ-Anfragen
3. **Aktiv**: Verarbeitet Datenanfragen und -indikationen
4. **Fehler**: Statusmeldung bei Problemen

## Anwendungsszenarien
- ISOBUS-basierte Landmaschinensteuerung
- Erfassung von 16-Bit-Sensordaten
- Kommunikation mit externen I/O-Modulen
- Automatisierungssysteme in der Agrartechnik

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Eingabeblöcken bietet Aux_Val1_IW erweiterte ISOBUS-Funktionalität mit parametrierbarer Initialisierung, Statusrückmeldungen und asynchronen Indikationsmechanismen.

## Fazit
Der Aux_Val1_IW Funktionsblock stellt eine robuste und flexible Lösung für die Erfassung von Wort-Eingabedaten in ISOBUS-Umgebungen dar, mit umfassender Fehlerbehandlung und konfigurierbaren Service-Parametern.