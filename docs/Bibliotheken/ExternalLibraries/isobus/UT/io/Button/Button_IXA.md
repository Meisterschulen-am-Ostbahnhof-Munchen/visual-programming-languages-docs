# Button_IXA

```{index} single: Button_IXA
```

<img width="1388" height="321" alt="image" src="https://github.com/user-attachments/assets/8f014f19-717a-4392-9d65-ba1fe63e1a6e" />

* * * * * * * * * *

## Einleitung
Button_IXA ist ein zusammengesetzter Funktionsblock zur Verarbeitung von booleschen Eingabedaten. Der Baustein dient als Schnittstelle für Taster-Eingaben und bietet eine standardisierte Verarbeitung von Schaltzuständen in Automatisierungssystemen.

![Button_IXA](Button_IXA.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - wird mit QI, PARAMS und u16ObjId ausgelöst
- **REQ**: Service-Anfrage - wird mit QI ausgelöst

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - wird mit QO und STATUS ausgelöst

### **Daten-Eingänge**
- **QI**: Ereignis-Eingangsqualifizierer (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **u16ObjId**: Objekt-ID (UINT) - Initialwert: ID_NULL

### **Daten-Ausgänge**
- **QO**: Ereignis-Ausgangsqualifizierer (BOOL)
- **STATUS**: Service-Status (STRING)

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ adapter::types::unidirectional::AX

## Funktionsweise
Der Button_IXA Funktionsblock fungiert als Wrapper um den internen Button_IX Baustein. Bei der Initialisierung (INIT) werden die Konfigurationsparameter übergeben und der interne Baustein konfiguriert. Service-Anfragen (REQ) lösen die Abfrage des Tasterzustands aus. Der Adapter IN dient als Schnittstelle für die eigentliche Taster-Eingabe.

## Technische Besonderheiten
- Verwendet ISOBUS-konforme Typen und Adapter
- Unterstützt Objekt-Identifikation über u16ObjId
- Flexible Parametrierung über STRING-Parameter
- Unidirektionale Adapter-Schnittstelle für Eingabedaten

## Zustandsübersicht
Der Baustein verfügt über folgende Hauptzustände:
- Nicht initialisiert: Wartet auf INIT-Ereignis
- Initialisiert: Bereit für REQ-Anfragen
- Aktiv: Verarbeitet Taster-Eingaben über den Adapter

## Anwendungsszenarien
- Taster-Eingaben in landwirtschaftlichen Maschinen
- ISOBUS-kompatible Steuerungssysteme
- Boolesche Eingabeverarbeitung in verteilten Automatisierungssystemen
- Bedienfelder und Schaltpulte

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen booleschen Eingabeblöcken bietet Button_IXA:
- ISOBUS-Kompatibilität
- Erweiterte Parametrierungsmöglichkeiten
- Standardisierte Statusrückmeldungen
- Adapter-basierte Architektur für bessere Wiederverwendbarkeit



## Zugehörige Übungen

* [Uebung_010a2_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010a2_AX.md)
* [Uebung_010a3_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010a3_AX.md)

## Fazit
Button_IXA ist ein spezialisierter Funktionsblock für die zuverlässige Verarbeitung von Taster-Eingaben in ISOBUS-Umgebungen. Durch seine modulare Architektur und standardisierte Schnittstellen eignet er sich ideal für den Einsatz in komplexen Automatisierungssystemen der Agrartechnik.