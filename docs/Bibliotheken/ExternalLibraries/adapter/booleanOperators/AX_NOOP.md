# AX_NOOP


![AX_NOOP](./AX_NOOP.svg)

* * * * * * * * * *
## Einleitung
Der Baustein **AX_NOOP** (No Operation) dient als reine Durchleitungsfunktion. Er verbindet einen eingehenden Adapter (`IN`) direkt mit einem ausgehenden Adapter (`OUT`), ohne Daten zu verändern oder Ereignisse zu verarbeiten. Der FB ist als Basisbaustein für Test-, Debugging- und Platzhalterzwecke konzipiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden.  
Ereignisse werden über den Adapter `IN` empfangen.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden.  
Ereignisse werden über den Adapter `OUT` weitergegeben.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden.  
Daten werden über den Adapter `IN` empfangen.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden.  
Daten werden über den Adapter `OUT` weitergegeben.

### **Adapter**
| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::AX` | IN | Socket (Eingang) | Empfängt Ereignisse und Daten |
| `adapter::types::unidirectional::AX` | OUT | Plug (Ausgang) | Gibt Ereignisse und Daten unverändert weiter |

## Funktionsweise
Der Baustein stellt eine Punkt-zu-Punkt-Verbindung zwischen dem Eingangsadapter `IN` und dem Ausgangsadapter `OUT` her. Intern werden folgende Verbindungen realisiert:
- **Ereignisverbindung**: `IN.E1` → `OUT.E1`
- **Datenverbindung**: `IN.D1` → `OUT.D1`

Jedes eingehende Ereignis an `IN.E1` wird sofort an `OUT.E1` weitergeleitet. Jeder Datenwert an `IN.D1` wird unverändert an `OUT.D1` durchgereicht. Es findet keine Logik, Verzögerung oder Zustandsänderung statt.

## Technische Besonderheiten
- Reine Durchschaltung ohne Verarbeitung.
- Verwendet den Adaptertyp `AX` für die Kommunikation.
- Keine veränderbaren Parameter oder Konfigurationen.
- Ideal geeignet als Platzhalter oder zum Debugging von Adapterverbindungen in der 4diac-IDE.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Sein Verhalten ist statisch und entspricht einer direkten Verdrahtung.

## Anwendungsszenarien
- **Testumgebungen**: Ersetzen eines komplexen FB während der Testphase, um die Verdrahtung zu prüfen.
- **Debugging**: Einschleusen eines Mess- oder Trace-Punkts in einen Adapterpfad.
- **Platzhalter**: Vorübergehendes Einfügen bei der schrittweisen Implementierung eines größeren Systems.
- **Adapter-Transparenz**: Überprüfen, ob ein Adaptertyp korrekt verbunden ist, ohne Funktionslogik.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Beschreibung | Unterschied |
|----------|--------------|-------------|
| `E_NOP` | Ereignis-NOP mit direkten Ereignis-/Daten-Ein-/Ausgängen | Verwendet Standard-I/O statt Adapter |
| `MUX` | Auswahl zwischen mehreren Datenquellen | Bietet Auswahl, kein reiner Durchgriff |
| `BYE` | Explizite End-of-Service-Markierung | Besitzt spezielle Semantik, kein Durchgriff |
| **AX_NOOP** | Reine Adapter-Durchleitung | Speziell für den Adaptertyp `AX` ausgelegt |

## Fazit
Der **AX_NOOP** ist ein minimalistischer, aber nützlicher Baustein für die Arbeit mit Adapterschnittstellen. Dank seiner einfachen Durchleitungsfunktion eignet er sich hervorragend zum Testen, Debuggen und als Platzhalter in der 4diac-IDE. Trotz fehlender eigener Logik erfüllt er eine wichtige Rolle beim schrittweisen Aufbau und der Verifikation von verbindungsintensiven Anwendungen.