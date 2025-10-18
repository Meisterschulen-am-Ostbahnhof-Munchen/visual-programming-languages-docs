# DataPanel_STATUS_SAE_J1939

* * * * * * * * * *

## Einleitung
Der Funktionsblock DataPanel_STATUS_SAE_J1939 dient zur Statusausgabe eines DataPanel-Knotens gemäß SAE J1939 Standard. Er ermöglicht die Initialisierung und Überwachung eines Netzwerkknotens sowie die Bereitstellung von Statusinformationen und Fehlercodes.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit Parametern QI und u8SAMember

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit QO und STATUS
- **IND**: Indikation vom Resource mit umfangreichen Statusdaten
- **TIMEOUT**: Timeout-Ereignis mit Zeitstempel und Statusinformation

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier
- **u8SAMember** (USINT): Node SA 224..239, Initialwert: MI::MI_00

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status
- **Q_timeout** (BOOL): Timeout-Qualifier
- **timestamp_timeout** (DINT): Zeitstempel für Timeout
- **timestamp_data** (DINT): Zeitstempel für Daten
- **Version** (USINT): Versionsnummer
- **Revision** (USINT): Revisionsnummer
- **Fault_Code** (USINT): Fehlercode
- **User_ID** (USINT): Benutzer-ID
- **Hardware_Version** (USINT): Hardware-Version
- **Status_01** bis **Status_14** (BOOL): 14 einzelne Statusbits

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert einen SAE J1939 DataPanel-Knoten über das INIT-Ereignis. Nach erfolgreicher Initialisierung bestätigt er dies über INITO. Während des Betriebs liefert er über IND-Ereignisse umfangreiche Statusinformationen des Knotens, einschließlich Versionen, Hardware-Informationen und 14 einzelner Statusbits. Bei Kommunikationsproblemen wird ein TIMEOUT-Ereignis ausgelöst.

## Technische Besonderheiten
- Unterstützt SAE J1939 Standard für landwirtschaftliche und mobile Maschinen
- Spezifische Adressierung im Bereich 224-239 für Source Address (SA)
- Umfangreiche Statusüberwachung mit 14 einzelnen Statusbits
- Integrierte Timeout-Erkennung mit Zeitstempeln
- Versions- und Revisionsverwaltung für Software und Hardware

## Zustandsübersicht
1. **Nicht initialisiert**: Wartet auf INIT-Ereignis
2. **Initialisiert**: Betriebsbereit, wartet auf Statusupdates
3. **Datenempfang**: Verarbeitet eingehende Statusinformationen
4. **Timeout**: Erkennt Kommunikationsausfälle

## Anwendungsszenarien
- Überwachung von DataPanel-Knoten in landwirtschaftlichen Fahrzeugen
- Integration in SAE J1939-Netzwerke für mobile Maschinen
- Statusmonitoring von Steuergeräten in Fahrzeugnetzwerken
- Fehlerdiagnose und Systemüberwachung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Statusbausteinen bietet dieser Funktionsblock spezifische SAE J1939-Funktionalität mit erweiterter Statusinformation und Timeout-Erkennung. Die 14 Statusbits ermöglichen eine detaillierte Systemüberwachung, die über Standard-Statusbausteine hinausgeht.

## Fazit
Der DataPanel_STATUS_SAE_J1939 Funktionsblock stellt eine umfassende Lösung für die Statusüberwachung von DataPanel-Knoten in SAE J1939-Netzwerken dar. Seine spezialisierte Funktionalität, kombiniert mit robusten Fehlererkennungsmechanismen, macht ihn ideal für den Einsatz in anspruchsvollen mobilen Anwendungen.