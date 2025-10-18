# ST_DEL_FB

![ST_DEL_FB](https://user-images.githubusercontent.com/116869307/214154809-ea8eaf7b-a851-4b0e-9cc9-2d7cdd14fcbd.png)

* * * * * * * * * *

## Einleitung

Der ST_DEL_FB Funktionsblock dient zum Löschen einer Funktionsblock-Instanz eines bestimmten Funktionsblock-Typs. Dieser Baustein gehört zur Kategorie der Rekonfigurationsdienste und ermöglicht die dynamische Verwaltung von Funktionsblock-Instanzen zur Laufzeit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Ereignis zum Anfordern des Löschens einer FB-Instanz

### **Ereignis-Ausgänge**

- **CNF**: Ereignis zur Bestätigung, dass die FB-Instanz gelöscht wurde

### **Daten-Eingänge**

- **QI** (BOOL): Ereignis-Eingangs-Qualifier
- **FB_NAME** (WSTRING): Name der zu löschenden FB-Instanz
- **DST** (WSTRING): Zielort, an dem die FB-Instanz gelöscht werden muss (Syntax: ResourceName)

### **Daten-Ausgänge**

- **QO** (BOOL): Ereignis-Ausgangs-Qualifier
- **STATUS** (WSTRING): Servicestatus (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapter**

Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise

Der ST_DEL_FB Funktionsblock reagiert auf das REQ-Ereignis und versucht, die spezifizierte Funktionsblock-Instanz am angegebenen Zielort zu löschen. Bei erfolgreicher Ausführung wird ein CNF-Ereignis mit entsprechendem Status ausgegeben. Der Baustein unterstützt verschiedene Betriebszustände und Fehlerbehandlungen.

## Technische Besonderheiten

- Unterstützt dynamische Rekonfiguration von Funktionsblöcken
- Verwendet WSTRING-Datentypen für internationale Zeichensätze
- Bietet detaillierte Statusrückmeldungen über den Löschvorgang
- Implementiert gemäß IEC 61499-1 Standard für strukturelle Dienste

## Zustandsübersicht

Der Funktionsblock unterstützt mehrere Service-Sequenzen:
- Normale Einrichtung (normal_establishment)
- Erfolglose Einrichtung (unsuccessful_establishment)
- Anforderungsbestätigung (request_confirm)
- Unterdrückte Anforderung (request_inhibited)
- Anforderungsfehler (request_error)
- Anwendungsinitiierte Beendigung (application_initiated_termination)
- Ressourceninitiierte Beendigung (resource_initiated_termination)

## Anwendungsszenarien

- Dynamische Rekonfiguration von Steuerungssystemen
- Ressourcenmanagement in verteilten Automatisierungssystemen
- Laufzeit-Anpassung von Funktionsblock-Architekturen
- Wartung und Updates von Automatisierungsanlagen

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu statischen Funktionsblöcken ermöglicht ST_DEL_FB die dynamische Verwaltung von FB-Instanzen zur Laufzeit. Er unterscheidet sich von Erstellungs-Bausteinen durch seine spezifische Löschfunktionalität und bietet damit komplementäre Funktionalität für vollständige Lebenszyklusverwaltung.

## Fazit

Der ST_DEL_FB Funktionsblock ist ein essentielles Werkzeug für Systeme, die dynamische Rekonfiguration erfordern. Seine robuste Fehlerbehandlung und detaillierte Statusrückmeldungen machen ihn zu einer zuverlässigen Lösung für die Verwaltung von Funktionsblock-Instanzen in komplexen Automatisierungsumgebungen.