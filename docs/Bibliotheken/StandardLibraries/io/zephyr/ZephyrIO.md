# ZephyrIO

```{index} single: ZephyrIO
```

<img width="1451" height="239" alt="image" src="https://github.com/user-attachments/assets/cc273604-5002-4492-a00b-90038a2d5b5f" />

* * * * * * * * * *

## Einleitung
Der ZephyrIO Funktionsblock dient als Template für modulare Ein-/Ausgabe-Funktionalität mit Boards, die das Zephyr Betriebssystem verwenden. Dieser Baustein ermöglicht die Initialisierung und Konfiguration von IO-Services in verteilten Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
  - Verknüpft mit: QI, UpdateInterval

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Steuert die Ausführung des Initialisierungsvorgangs
- **UpdateInterval** (TIME): Aktualisierungsintervall für den Service (Standardwert: T#40ms)

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Zeigt den Status der Initialisierung an
- **STATUS** (STRING): Service-Statusinformationen

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der ZephyrIO Funktionsblock initialisiert IO-Services für Zephyr-basierte Hardware. Bei Empfang des INIT-Ereignisses wird der Service mit dem konfigurierten Update-Intervall gestartet. Nach erfolgreicher Initialisierung wird das INITO-Ereignis mit entsprechenden Statusinformationen ausgegeben.

## Technische Besonderheiten
- Speziell für Zephyr RTOS optimiert
- Konfigurierbares Update-Intervall für periodische Operationen
- Standard-Update-Intervall von 40 Millisekunden
- Statusrückmeldung über STRING-Variable

## Zustandsübersicht
1. **Nicht initialisiert**: Wartet auf INIT-Ereignis
2. **Initialisierung läuft**: Verarbeitet INIT mit QI=true
3. **Initialisiert**: Sendet INITO mit Statusinformationen

## Anwendungsszenarien
- Einbindung von Zephyr-basierten IO-Boards in 4diac-Systeme
- Modulare IO-Erweiterungen für Embedded-Systeme
- Hardware-nahe Echtzeit-Steuerungen mit Zephyr RTOS

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen IO-Bausteinen bietet ZephyrIO spezifische Optimierungen für das Zephyr Betriebssystem und ermöglicht eine nahtlose Integration von Zephyr-basierter Hardware in 4diac-Umgebungen.

## Fazit
Der ZephyrIO Funktionsblock stellt eine spezialisierte Lösung für die Integration von Zephyr-basierten IO-Komponenten in IEC 61499-Systeme dar und bietet eine standardisierte Schnittstelle für modulare Hardware-Erweiterungen.