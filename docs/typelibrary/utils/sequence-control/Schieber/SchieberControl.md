# SchieberControl

<img width="1504" height="335" alt="SchieberControl" src="https://github.com/user-attachments/assets/605ff73f-7393-4236-96f6-bcc678f4dcf6" />

* * * * * * * * * *
## Einleitung
Der SchieberControl Funktionsblock dient zur Steuerung eines pneumatischen Schiebersystems. Er ermöglicht das Öffnen, Schließen und Zurücksetzen des Schiebers sowie die Initialisierung und De-Initialisierung des Systems. Der FB bietet verschiedene Zustände für den Betrieb des Schiebers und unterstützt Zeitsteuerungen für Öffnungs- und Schließvorgänge.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit QI, DT_Opening, DT_Closing)
- `Open`: Öffnen des Schiebers
- `Close`: Schließen des Schiebers
- `RESET`: Zurücksetzen auf unbekannten Zustand
- `INPUT_DATA`: Eingangsdatenereignis (mit BT, SK, AUXC)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung (mit QO)
- `EO`: Allgemeines Ausgangsereignis (mit Button, Softkey, Auxiliary, STATE)
- `EO_POWERED`: Aktiviere "Öffnen"-Ventil für Pneumatik (mit DO_POWERED)
- `EO_OPEN`: Aktiviere "Öffnen"-Ventil (mit DO_OPEN)
- `EO_CLOSE`: Aktiviere "Schließen"-Ventil (mit DO_CLOSE)
- `EO1`: Zusätzliches Ausgangsereignis

### **Daten-Eingänge**
- `QI`: Eingangsereignisqualifizierer (BOOL)
- `BT`: Tastereingang (SchieberStruct)
- `SK`: Softkey-Eingang (SchieberStruct)
- `AUXC`: Zusatzsteuerung (SchieberAuxInStruct)
- `DT_Opening`: Öffnungszeit (TIME)
- `DT_Closing`: Schließzeit (TIME)
- `START`: Startzustand (UINT)

### **Daten-Ausgänge**
- `QO`: Ausgangsereignisqualifizierer (BOOL)
- `Button`: Tasterausgang (UINT)
- `Softkey`: Softkey-Ausgang (UINT)
- `Auxiliary`: Zusatzsteuerungsausgang (SchieberAuxOutStruct)
- `DO_POWERED`: Aktiviere "Öffnen"-Ventil für Pneumatik (BOOL)
- `DO_OPEN`: Aktiviere "Öffnen"-Ventil (BOOL)
- `DO_CLOSE`: Aktiviere "Schließen"-Ventil (BOOL)
- `STATE`: Zustandsinformation (STRING)

### **Adapter**
- `timeOut`: TimeOut-Adapter für Zeitsteuerung

## Funktionsweise
Der SchieberControl FB verwaltet verschiedene Zustände des Schiebersystems:
1. **Initialisierung**: Setzt alle Werte und bestätigt die Initialisierung
2. **Betriebszustände**: Geschlossen, Öffnend, Geöffnet, Schließend
3. **Stop-Zustände**: Unterbrechung von Öffnungs-/Schließvorgängen
4. **Unbekannter Zustand**: Reset-Zustand

Die Zeitsteuerung für Öffnungs- und Schließvorgänge erfolgt über den timeOut-Adapter.

## Technische Besonderheiten
- Unterstützt komplexe Zustandsübergänge mit Zeitsteuerung
- Separate Steuerung für pneumatische und elektrische Ventile
- Flexible Konfiguration von Öffnungs-/Schließzeiten
- Visuelle Rückmeldung über Softkeys und Auxiliary-Ausgänge

## Zustandsübersicht
1. **START**: Initialzustand
2. **Init**: Initialisierungsphase
3. **Closed**: Schieber geschlossen
4. **Opening**: Schieber öffnend
5. **Opened**: Schieber geöffnet
6. **Closing**: Schieber schließend
7. **Opening_STOP**: Öffnungsvorgang unterbrochen
8. **Closing_STOP**: Schließvorgang unterbrochen
9. **Unknown**: Unbekannter Zustand
10. **DeInit**: De-Initialisierungsphase

## Anwendungsszenarien
- Steuerung von pneumatischen Schiebersystemen
- Automatisierte Materialzufuhr/-abfuhr
- Sicherheitskritische Ventilsteuerungen
- Prozessautomatisierung mit zeitgesteuerten Abläufen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Schiebersteuerungen bietet dieser FB:
- Erweiterte Zustandsverwaltung
- Zeitgesteuerte Abläufe
- Komplexe Übergangslogik
- Visuelle Rückmeldungen
- Separate Steuerung für pneumatische Systeme

## Fazit
Der SchieberControl FB ist eine leistungsfähige Lösung für die Steuerung pneumatischer Schiebersysteme mit umfangreichen Zustandsmanagement und Zeitsteuerungsfunktionen. Seine flexible Schnittstelle und detaillierte Zustandsverwaltung machen ihn besonders geeignet für komplexe Automatisierungsaufgaben.
