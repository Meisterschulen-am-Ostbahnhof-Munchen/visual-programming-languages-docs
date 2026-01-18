# GPIOChip

```{index} single: GPIOChip
```

<img width="1343" height="245" alt="image" src="https://github.com/user-attachments/assets/612f184c-bce3-4376-bb09-9881ec2162c0" />

* * * * * * * * * *

## Einleitung
Der GPIOChip Funktionsblock ist ein Service Interface Function Block zur Ansteuerung von GPIO-Chips unter Linux-Systemen. Er ermöglicht den Zugriff auf GPIO-Lines über das Linux GPIO Character Device Interface (/dev/gpiochipX) und unterstützt verschiedene Betriebsmodi für das Lesen und Schreiben von GPIO-Signalen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service Initialisierungs-Ereignis mit den zugehörigen Daten QI, VALUE, ChipNumber, LineNumber, ReadWriteMode, BiasMode und ActiveLow

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit QO und STATUS
- **IND**: Indikation vom Resource mit QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier
- **VALUE** (WSTRING): Receiver IX/QX block name
- **ChipNumber** (UINT): ID des /dev/gpiochipX Devices (Initialwert: 0)
- **LineNumber** (UINT): ID der GPIO-Line innerhalb des ausgewählten Chips (Initialwert: 0)
- **ReadWriteMode** (UINT): Lese-/Schreibmodus der Line (0=read, 1=write push/pull, 2=open drain, 3=open source) (Initialwert: 0)
- **BiasMode** (UINT): Bias-Modus der Line (0=none, 1=pull up, 2=pull down) (Initialwert: 0)
- **ActiveLow** (BOOL): True, wenn logisch 1 niedriger Spannung entspricht (Initialwert: 0)

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (WSTRING): Service Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der GPIOChip FB initialisiert bei Empfang des INIT-Ereignisses eine Verbindung zu einem spezifischen GPIO-Chip und einer definierten GPIO-Line. Die Konfiguration umfasst den Betriebsmodus (Lesen/Schreiben), den Bias-Modus und die Polaritätseinstellung (ActiveLow). Nach erfolgreicher Initialisierung bestätigt der Block mit INITO+, bei Fehlern mit INITO- und einem entsprechenden STATUS.

## Technische Besonderheiten
- Unterstützt verschiedene GPIO-Betriebsmodi: Lesen, Schreiben (Push/Pull), Open Drain und Open Source
- Konfigurierbare Bias-Einstellungen: None, Pull-Up, Pull-Down
- Aktiv-Niedrig Modus für invertierte Logik
- Linux GPIO Character Device Interface basiert
- Automatische Fehlerbehandlung mit Statusrückmeldung

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Ausgangszustand vor INIT
2. **Initialisierung**: Während der GPIO-Chip Konfiguration
3. **Bereit**: Nach erfolgreicher Initialisierung (INITO+)
4. **Fehler**: Bei Initialisierungsfehlern (INITO-)

## Anwendungsszenarien
- Ansteuerung von GPIO-Pins in Embedded Linux Systemen
- Hardware-nahe E/A-Operationen in Automatisierungssystemen
- Schnittstelle zu externen Sensoren und Aktoren
- Prototyping und Entwicklung von IoT-Geräten
- Industrielle Steuerungsanwendungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen I/O-Blöcken bietet GPIOChip erweiterte Funktionen wie konfigurierbare Bias-Modi, verschiedene Schreibmodi und direkten Zugriff auf das Linux GPIO-Subsystem. Er ist spezifisch für Linux-Systeme mit GPIO-Chip Unterstützung ausgelegt.

## Fazit
Der GPIOChip Funktionsblock stellt eine leistungsfähige Schnittstelle zur GPIO-Hardwaresteuerung unter Linux bereit. Durch die umfangreiche Konfigurierbarkeit und das standardisierte Service Interface eignet er sich ideal für anspruchsvolle Embedded-Anwendungen, die direkten Hardwarezugriff erfordern.