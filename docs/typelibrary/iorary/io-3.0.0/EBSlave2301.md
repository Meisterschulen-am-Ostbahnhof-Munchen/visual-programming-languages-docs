# EBSlave2301

* * * * * * * * * *

## Einleitung
Der EBSlave2301 ist ein Service Interface Function Block für die Kommunikation mit einem EtherBrick Slave-Modul. Dieser Funktionsblock dient als Schnittstelle zur Konfiguration und Steuerung von bis zu sechs Relais-Ausgängen über ein EtherBrick-Bussystem.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **MAP**: Wird ausgelöst, um die Pin-Zuordnungen zu konfigurieren. Begleitet von den Datenvariablen Relay_1 bis Relay_6 und QI.

### **Ereignis-Ausgänge**
- **MAPO**: Bestätigt die erfolgreiche Pin-Zuordnung. Wird mit QO ausgegeben.
- **IND**: Meldung vom Ressourcen-Interface. Wird mit QO und STATUS ausgegeben.

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Aktiviert/deaktiviert den Funktionsblock
- **Relay_1** bis **Relay_6** (WSTRING): Konfiguration der Relais-Pins
- **UpdateInterval** (UINT): Aktualisierungsintervall des Slave-Moduls in Hz (vom Master geerbt)

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Status der Operation
- **STATUS** (WSTRING): Service-Statusinformationen

### **Adapter**
- **BusAdapterOut** (Plug): Ausgehender Bus-Adapter vom Typ EBBusAdapter
- **BusAdapterIn** (Socket): Eingehender Bus-Adapter vom Typ EBBusAdapter

## Funktionsweise
Der EBSlave2301 ermöglicht die Konfiguration von bis zu sechs Relais-Ausgängen über das MAP-Ereignis. Bei Aktivierung durch QI werden die Relais-Parameter über die Bus-Adapter an das EtherBrick-System übertragen. Das MAPO-Ereignis bestätigt den erfolgreichen Abschluss der Konfiguration, während IND-Ereignisse Statusinformationen vom Ressourcen-Interface liefern.

## Technische Besonderheiten
- Unterstützt WSTRING-Datentypen für Relais-Konfiguration
- Verwendet ein Adapter-basiertes Bussystem für die Kommunikation
- UpdateInterval wird vom Master-System geerbt
- Bietet qualifizierte Ereignissteuerung über QI und QO

## Zustandsübersicht
Der Funktionsblock wechselt zwischen folgenden Zuständen:
- Inaktiv: QI = FALSE
- Konfigurationsmodus: Bei MAP-Ereignis mit QI = TRUE
- Betriebsbereit: Nach erfolgreicher MAPO-Bestätigung
- Fehlerzustand: Bei IND-Ereignis mit Statusinformationen

## Anwendungsszenarien
- Steuerung von Relais-basierten Aktoren in Automatisierungssystemen
- Integration in EtherBrick-basierte IO-Systeme
- Verteiltes Steuerungssystem mit Master-Slave-Architektur
- Anwendungen mit konfigurierbaren Relais-Zuordnungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgangsbausteinen bietet der EBSlave2301:
- Konfigurierbare Pin-Zuordnungen zur Laufzeit
- Adapter-basierte Buskommunikation
- Qualifizierte Ereignissteuerung
- Statusrückmeldungen vom Ressourcen-Interface

## Fazit
Der EBSlave2301 ist ein spezialisierter Funktionsblock für die flexible Steuerung von Relais-Ausgängen in EtherBrick-Systemen. Durch seine konfigurierbaren Schnittstellen und Adapter-basierte Architektur eignet er sich besonders für anspruchsvolle Automatisierungsanwendungen mit dynamischen IO-Konfigurationen.