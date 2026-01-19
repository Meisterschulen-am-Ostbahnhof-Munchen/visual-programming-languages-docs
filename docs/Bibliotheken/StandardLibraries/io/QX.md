# QX

```{index} single: QX
```

![](https://user-images.githubusercontent.com/69573151/210781265-4dabab2d-a9e3-4da6-a14b-8df0a8ed36e5.png)

* * * * * * * * * *

## Einleitung
Der QX-Funktionsblock ist ein Ausgabeservice-Schnittstellen-Funktionsblock für boolesche Ausgabedaten. Er dient als Schnittstelle zwischen der Steuerungslogik und physikalischen Ausgabegeräten und ermöglicht die Ausgabe von digitalen Signalen an externe Ressourcen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter für Konfiguration
- **OUT** (BOOL): Ausgabedaten für die Ressource

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformationen

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der QX-Block verarbeitet zwei Hauptoperationen: Initialisierung und Service-Anfragen. Bei INIT-Ereignis wird der Service mit den angegebenen PARAMS initialisiert. Bei REQ-Ereignis wird der boolesche OUT-Wert an die angeschlossene Ressource ausgegeben. Jede Operation generiert eine entsprechende Bestätigung (INITO oder CNF) mit Statusinformationen.

## Technische Besonderheiten
- Spezialisiert auf boolesche Ausgabedaten
- Unterstützt parametrisierbare Service-Konfiguration
- Liefert detaillierte Statusinformationen über den STRING-Ausgang STATUS
- Verwendet Qualifizierer (QI/QO) für Ereignissteuerung

## Zustandsübersicht
Der Block wechselt zwischen folgenden Zuständen:
1. **Nicht initialisiert**: Vor der ersten INIT-Operation
2. **Initialisiert**: Nach erfolgreicher INIT-Operation, bereit für REQ-Operationen
3. **Aktiv**: Während der Verarbeitung von REQ-Operationen

## Anwendungsszenarien
- Ansteuerung von digitalen Ausgängen (Relais, LEDs, Ventile)
- Schnittstelle zu Aktoren in Automatisierungssystemen
- Integration in IO-Subsysteme für verteilte Steuerungen
- Test- und Simulationsumgebungen für Ausgabesignale

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen Ausgabeblöcken bietet QX spezifische Service-Schnittstellenfunktionalität mit parametrisierbarer Konfiguration und detailliertem Status-Reporting. Andere Blöcke wie einfache BOOL-Ausgaben haben typischerweise weniger Konfigurationsmöglichkeiten und Statusinformationen.

## Fazit
Der QX-Funktionsblock stellt eine robuste und konfigurierbare Lösung für boolesche Ausgabeservices dar. Seine strukturierte Ereignisbehandlung und detaillierte Statusrückmeldung machen ihn besonders geeignet für zuverlässige Automatisierungsanwendungen, bei denen Transparenz über den IO-Status erforderlich ist.