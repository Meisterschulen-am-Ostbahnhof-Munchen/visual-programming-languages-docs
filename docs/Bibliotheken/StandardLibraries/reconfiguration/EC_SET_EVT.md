# EC_SET_EVT

```{index} single: EC_SET_EVT
```

![EC_SET_EVT](https://user-images.githubusercontent.com/116869307/214154604-e4081ae0-85d5-496e-a037-2b8bf39eba7d.png)

* * * * * * * * * *

## Einleitung

Der EC_SET_EVT Funktionsblock dient zum Setzen von Ereignis-Ein- oder -Ausgängen einer Funktionsblock-Instanz. Er ermöglicht die gezielte Auslösung von Ereignissen in anderen Funktionsblöcken und kann beispielsweise als Ereignis-Sniffer eingesetzt werden. Der Baustein gehört zur Kategorie der Rekonfigurationsdienste gemäß IEC 61499-1 Standard.

![EC_SET_EVT](EC_SET_EVT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Service-Anfrage - löst die Ausführung des Setzvorgangs aus

### **Ereignis-Ausgänge**

- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**

- **QI** (BOOL): Ereignis-Eingangs-Qualifier - aktiviert/deaktiviert den Service
- **FB_NAME** (WSTRING): Name der Funktionsblock-Instanz
- **FB_EVENT_IO** (WSTRING): Name des zu setzenden Ereignisses
- **DST** (WSTRING): Zielort, an dem das Ereignis gesetzt werden soll (Syntax: ResourceName)

### **Daten-Ausgänge**

- **QO** (BOOL): Ereignis-Ausgangs-Qualifier - zeigt den Status der Service-Ausführung
- **STATUS** (WSTRING): Service-Status (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapter**

Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise

Der EC_SET_EVT Funktionsblock empfängt über das REQ-Ereignis eine Anfrage zum Setzen eines spezifischen Ereignisses in einer anderen Funktionsblock-Instanz. Über die Eingangsdaten werden die Ziel-Funktionsblock-Instanz (FB_NAME), das zu setzende Ereignis (FB_EVENT_IO) und der Zielort (DST) spezifiziert. Nach erfolgreicher Ausführung wird das CNF-Ereignis mit entsprechendem Status zurückgemeldet.

## Technische Besonderheiten

- Implementierung in C++ für GCC-Compiler ab Version 3.0
- Unterstützt Wide-String-Datentypen für internationale Zeichensätze
- Bietet detaillierte Statusrückmeldungen für Fehlerdiagnose
- Arbeitet als Rekonfigurationsdienst zwischen Anwendung und Ressource

## Zustandsübersicht

Der Funktionsblock unterstützt mehrere Service-Sequenzen:
- **normal_establishment**: Erfolgreiche Initialisierung
- **unsuccessful_establishment**: Fehlgeschlagene Initialisierung
- **request_confirm**: Erfolgreiche Service-Ausführung
- **request_inhibited**: Unterdrückte Service-Anfrage
- **request_error**: Fehlerhafte Service-Ausführung
- **application_initiated_termination**: Anwendungsseitige Beendigung
- **resource_initiated_termination**: Ressourcenseitige Beendigung

## Anwendungsszenarien

- Debugging und Monitoring von Ereignisflüssen
- Automatisierte Testumgebungen
- Dynamische Rekonfiguration von Steuerungssystemen
- Ereignis-basierte Diagnosefunktionen
- Simulation von externen Ereignissen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu Standard-Funktionsblöcken bietet EC_SET_EVT spezielle Rekonfigurationsfähigkeiten, die über normale Ereignisverarbeitung hinausgehen. Er ermöglicht externen Zugriff auf Ereignisse anderer Funktionsblöcke, was für Diagnose- und Testzwecke besonders wertvoll ist.

## Fazit

Der EC_SET_EVT Funktionsblock stellt ein leistungsfähiges Werkzeug für erweiterte Steuerungsanwendungen dar, insbesondere für Debugging, Testing und dynamische Rekonfiguration. Seine Fähigkeit, gezielt Ereignisse in anderen Funktionsblock-Instanzen zu setzen, macht ihn zu einem wertvollen Baustein für komplexe Automatisierungssysteme.