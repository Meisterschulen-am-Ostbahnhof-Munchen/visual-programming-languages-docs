# EBSlave2181

```{index} single: EBSlave2181
```

<img width="1232" height="438" alt="image" src="https://github.com/user-attachments/assets/c74605d8-26e7-4c52-9109-9f513c0e811a" />

* * * * * * * * * *

## Einleitung
Der EBSlave2181 ist ein Service Interface Function Block für die Kommunikation mit EtherBrick-Slave-Modulen. Dieser Funktionsblock ermöglicht die Konfiguration und Überwachung von digitalen Ein- und Ausgängen eines EtherBrick-Slave-Moduls und dient als Schnittstelle zwischen der Steuerungslogik und der physikalischen Feldbus-Kommunikation.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **MAP**: Wird zur Konfiguration der Pin-Zuordnungen verwendet. Löst die Zuordnung der digitalen Ein- und Ausgänge aus.

### **Ereignis-Ausgänge**
- **MAPO**: Bestätigt die erfolgreiche Pin-Zuordnung.
- **IND**: Zeigt Statusänderungen oder Fehler vom Slave-Modul an.

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Aktiviert/deaktiviert den Funktionsblock
- **DigitalInput_1** bis **DigitalInput_8** (WSTRING): Konfiguration der digitalen Eingänge 1-8
- **DigitalOutput_1** bis **DigitalOutput_8** (WSTRING): Konfiguration der digitalen Ausgänge 1-8  
- **UpdateInterval** (UINT): Aktualisierungsintervall des Slave-Moduls in Hz (vom Master geerbt)

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Status des Funktionsblocks
- **STATUS** (WSTRING): Service Status - Enthält Statusinformationen oder Fehlermeldungen

### **Adapter**
- **BusAdapterOut** (Plug): Ausgehender Bus-Adapter für EtherBrick-Kommunikation
- **BusAdapterIn** (Socket): Eingehender Bus-Adapter für EtherBrick-Kommunikation

## Funktionsweise
Der EBSlave2181 dient als Vermittler zwischen der IEC 61499-Steuerungslogik und einem EtherBrick-Slave-Modul. Beim Empfang des MAP-Ereignisses werden die konfigurierten digitalen Ein- und Ausgänge dem Slave-Modul zugeordnet. Das MAPO-Ereignis bestätigt den erfolgreichen Abschluss dieser Zuordnung. Das IND-Ereignis signalisiert Statusänderungen oder Fehlerzustände des Slave-Moduls.

## Technische Besonderheiten
- Unterstützt 8 digitale Eingänge und 8 digitale Ausgänge
- Verwendet WSTRING-Datentyp für Pin-Konfiguration
- Ermöglicht konfigurierbare Aktualisierungsintervalle
- Integriert sich über standardisierte Bus-Adapter in die EtherBrick-Architektur
- Implementiert Qualifier-Pattern (QI/QO) für zuverlässige Statusverwaltung

## Zustandsübersicht
Der Funktionsblock verfügt über folgende Betriebszustände:
- **Inaktiv**: QI = FALSE, Funktionsblock reagiert nicht auf Ereignisse
- **Konfigurierend**: Verarbeitung des MAP-Ereignisses und Zuordnung der Pins
- **Aktiv**: Erfolgreich konfiguriert, wartet auf IND-Ereignisse vom Slave
- **Fehler**: STATUS enthält Fehlerinformationen, QO kann FALSE sein

## Anwendungsszenarien
- Anbindung von EtherBrick-Slave-Modulen in verteilten Automatisierungssystemen
- Konfiguration digitaler I/O-Module in Industrieanlagen
- Integration in Steuerungssysteme mit EtherBrick-Feldbus-Kommunikation
- Überwachung und Diagnose von Slave-Modulen in Echtzeit

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen I/O-Funktionsblöcken bietet der EBSlave2181 spezifische Integration für EtherBrick-Systeme mit vordefinierten Bus-Adapter-Schnittstellen. Er ist spezialisiert auf die Konfiguration und Überwachung von Slave-Modulen und bietet direkte Unterstützung für die EtherBrick-Kommunikationsprotokolle.

## Fazit
Der EBSlave2181 ist ein spezialisierter Service Interface Function Block, der eine zuverlässige und standardisierte Schnittstelle für die Integration von EtherBrick-Slave-Modulen in IEC 61499-basierte Steuerungssysteme bereitstellt. Seine strukturierte Schnittstelle und klare Zustandsverwaltung machen ihn zu einer robusten Lösung für industrielle Feldbus-Kommunikation.
