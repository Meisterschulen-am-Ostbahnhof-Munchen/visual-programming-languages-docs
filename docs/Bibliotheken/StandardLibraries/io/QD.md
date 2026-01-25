# QD

```{index} single: QD
```

![](https://user-images.githubusercontent.com/69573151/210781704-73d6a020-e7c0-430e-9797-2d0ef1cc6cc3.png)

* * * * * * * * * *
## Einleitung
Der QD-Funktionsblock ist ein Ausgabeservice-Interface-Baustein für die Ausgabe von Doppelwort-Daten (DWORD). Er dient als Schnittstelle zwischen der Anwendungslogik und den physikalischen Ausgabegeräten eines Ressourcen-Managers.

![QD](QD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - initialisiert den Funktionsblock mit den erforderlichen Parametern
- **REQ**: Service-Anforderung - löst die Datenausgabe an die Ressource aus

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - bestätigt den Abschluss der Initialisierung
- **CNF**: Bestätigung der angeforderten Service-Ausführung - signalisiert den Abschluss der Datenausgabe

### **Daten-Eingänge**
- **QI**: Event-Input-Qualifier (BOOL) - steuert die Ausführung der Service-Anforderungen
- **PARAMS**: Service-Parameter (STRING) - Konfigurationsparameter für den Service
- **OUT**: Ausgabedaten (DWORD) - die an die Ressource zu übertragenden Doppelwort-Daten

### **Daten-Ausgänge**
- **QO**: Event-Output-Qualifier (BOOL) - Status der Service-Ausführung
- **STATUS**: Service-Status (STRING) - detaillierte Statusinformationen über die Service-Ausführung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der QD-Block arbeitet als zyklischer Service-Interface-Baustein. Bei Empfang des INIT-Ereignisses wird der Block mit den über PARAMS übergebenen Konfigurationsdaten initialisiert. Die eigentliche Datenausgabe wird durch das REQ-Ereignis ausgelöst, wobei die im OUT-Eingang bereitgestellten DWORD-Daten an die zugeordnete Ressource übertragen werden. Jede Service-Anforderung wird durch entsprechende Bestätigungsereignisse (INITO bzw. CNF) quittiert.

## Technische Besonderheiten
- Verarbeitet 32-Bit-Daten (DWORD)
- Unterstützt parametrierbare Service-Konfiguration
- Bietet detaillierte Statusrückmeldungen
- Arbeitet mit Qualifier-Flags für zuverlässige Service-Steuerung

## Zustandsübersicht
Der Block durchläuft folgende Zustände:
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist betriebsbereit und wartet auf REQ-Ereignisse
3. **Service-Ausführung**: Verarbeitung einer REQ-Anforderung
4. **Bestätigung**: Rückmeldung des Service-Ergebnisses

## Anwendungsszenarien
- Ansteuerung von digitalen Ausgabemodulen mit 32-Bit-Datenbreite
- Steuerung von komplexen Aktoren mit Mehrfach-Parameterübergabe
- Integration in verteilte Steuerungssysteme mit Ressourcen-Management
- Anwendungen mit hohen Anforderungen an die Ausgabedatenintegrität

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Ausgabeblöcken bietet QD:
- Erweiterte Parametrierbarkeit durch STRING-Parameter
- DWORD-Datenbreite statt einfacher BOOL- oder BYTE-Werte
- Detaillierte Statusrückmeldungen für Fehlerdiagnose
- Vollständige Service-Interface-Charakteristik mit Initialisierungsprozedur


## Zugehörige Übungen

* [Uebung_060](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_060.md)

## Fazit
Der QD-Funktionsblock stellt eine leistungsstarke und flexible Lösung für die Ausgabe von Doppelwort-Daten in IEC 61499-Systemen dar. Seine umfassende Parametrierbarkeit und detaillierte Statusrückmeldungen machen ihn besonders geeignet für anspruchsvolle Automatisierungsanwendungen, die zuverlässige und konfigurierbare Ausgabeservices erfordern.