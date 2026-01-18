# Wago459

```{index} single: Wago459
```

<img width="1338" height="318" alt="image" src="https://github.com/user-attachments/assets/a327cecb-2330-4f40-9961-8c1c1b151097" />

* * * * * * * * * *

## Einleitung
Der Wago459 ist ein Service Interface Function Block für die Anbindung von Wago-750-459 Analog-Eingangsmodulen in 4diac-Systemen. Dieser Funktionsblock ermöglicht die Konfiguration und Überwachung von bis zu vier analogen Eingangskanälen und stellt die Kommunikation mit dem Wago-Bussystem her.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **MAP**: Startet die Pin-Zuordnung für die analogen Eingänge. Wird mit den Datenvariablen AnalogInput_1 bis AnalogInput_4 und QI verknüpft.

### **Ereignis-Ausgänge**
- **MAPO**: Bestätigt die erfolgreiche Pin-Zuordnung. Wird mit QO verknüpft.
- **IND**: Liefert Statusinformationen vom Ressourcen-Manager. Wird mit QO und STATUS verknüpft.

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Steuert die Aktivierung des Funktionsblocks
- **AnalogInput_1** (STRING): Konfiguration für analogen Eingang 1
- **AnalogInput_2** (STRING): Konfiguration für analogen Eingang 2
- **AnalogInput_3** (STRING): Konfiguration für analogen Eingang 3
- **AnalogInput_4** (STRING): Konfiguration für analogen Eingang 4

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Zeigt den Betriebszustand an
- **STATUS** (WSTRING): Detaillierte Statusinformationen des Service

### **Adapter**
- **BusAdapterOut** (Plug): Ausgehende Bus-Adapter-Verbindung vom Typ WagoBusAdapter
- **BusAdapterIn** (Socket): Eingehende Bus-Adapter-Verbindung vom Typ WagoBusAdapter

## Funktionsweise
Der Wago459-Funktionsblock dient als Schnittstelle zwischen der 4diac-Steuerung und dem Wago-750-459 Analog-Eingangsmodul. Beim Empfang des MAP-Ereignisses werden die konfigurierten Pin-Zuordnungen (AnalogInput_1 bis AnalogInput_4) an das Bus-System übertragen. Der Block bestätigt erfolgreiche Zuordnungen über MAPO und liefert kontinuierlich Statusinformationen über IND-Ereignisse.

## Technische Besonderheiten
- Unterstützt bis zu vier analoge Eingangskanäle
- Verwendet STRING-Datentypen für flexible Pin-Konfiguration
- Bietet umfangreiche Statusrückmeldungen via WSTRING
- Implementiert ein bidirektionales Adapter-System für Bus-Kommunikation
- Enthält Qualifier-Variablen (QI/QO) für zuverlässige Zustandsverwaltung

## Zustandsübersicht
Der Funktionsblock verfügt über folgende Betriebszustände:
- Inaktiv: Wartet auf MAP-Ereignis mit aktiviertem QI
- Konfiguration: Verarbeitet Pin-Zuordnungen nach MAP-Ereignis
- Betrieb: Überwacht kontinuierlich den Modulstatus und sendet IND-Ereignisse
- Fehler: Bei Problemen wird STATUS mit Fehlerinformationen gefüllt

## Anwendungsszenarien
- Anbindung von Wago-750-459 Analog-Eingangsmodulen in Automatisierungssystemen
- Messwerterfassung von analogen Sensoren (0-10V, 0-20mA, 4-20mA)
- Prozessüberwachung in industriellen Steuerungssystemen
- Integration in dezentrale Peripheriesysteme mit Wago-Busarchitektur

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen IO-Funktionsblöcken bietet Wago459:
- Spezifische Optimierung für Wago-750-459 Hardware
- Vorkonfigurierte Adapter für Wago-Bussysteme
- Direkte Unterstützung für alle vier Kanäle des Moduls
- Integrierte Statusüberwachung und Fehlerbehandlung

## Fazit
Der Wago459-Funktionsblock stellt eine zuverlässige und spezialisierte Lösung für die Integration von Wago-750-459 Analog-Eingangsmodulen in 4diac-basierte Steuerungssysteme dar. Durch seine klare Schnittstellendefinition und umfassende Statusrückmeldungen ermöglicht er eine effiziente Implementierung analoger Messwertverarbeitung in industriellen Automatisierungsprojekten.
