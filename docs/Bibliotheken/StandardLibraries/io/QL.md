# QL

```{index} single: QL
```

![](https://user-images.githubusercontent.com/69573151/210781586-ad33d398-c369-4e16-b79e-20ed939fcdd6.png)

* * * * * * * * * *

## Einleitung
Der QL-Funktionsblock ist ein Ausgabeservice-Interface-Baustein für die Verarbeitung von Long-Word-Ausgabedaten. Er dient als Schnittstelle zwischen der Steuerungslogik und externen Ressourcen und ermöglicht die Ausgabe von 64-Bit-Datenwerten.

![QL](QL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **OUT** (LWORD): Ausgabedaten für die Ressource (64-Bit)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der QL-Block verarbeitet zwei Hauptoperationen: Initialisierung und Datenausgabe. Bei der INIT-Operation werden die Service-Parameter konfiguriert und die Verbindung zur Ressource initialisiert. Die REQ-Operation führt die eigentliche Datenausgabe des LWORD-Wertes an die angeschlossene Ressource durch. Jede Operation wird durch entsprechende Bestätigungsereignisse quittiert.

## Technische Besonderheiten
- Verarbeitung von 64-Bit-Datenwerten (LWORD)
- String-basierte Parameterkonfiguration
- Statusrückmeldung über STRING-Variable
- Qualifizierer für Ereignissteuerung (QI/QO)

## Zustandsübergänge
Der Block verfügt über zwei Hauptzustände:
1. **Initialisierungszustand**: Verarbeitung der INIT-Anfrage mit PARAMS
2. **Betriebszustand**: Verarbeitung von REQ-Anfragen mit OUT-Daten

## Anwendungsszenarien
- Ausgabe von 64-Bit-Steuerwerten an Hardware-Schnittstellen
- Kommunikation mit externen Peripheriegeräten
- Integration in verteilte Steuerungssysteme
- Anbindung an spezielle IO-Module

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Ausgabeblöcken bietet QL die Verarbeitung von 64-Bit-Daten und eine erweiterte Parameterkonfiguration. Gegenüber universelleren Kommunikationsblöcken ist QL speziell auf die Ausgabefunktionalität optimiert.

## Fazit
Der QL-Funktionsblock stellt eine leistungsfähige Schnittstelle für die Ausgabe von Long-Word-Daten dar und bietet durch seine strukturierte Ereignissteuerung und Statusrückmeldung eine zuverlässige Grundlage für die Anbindung externer Ressourcen in Automatisierungssystemen.