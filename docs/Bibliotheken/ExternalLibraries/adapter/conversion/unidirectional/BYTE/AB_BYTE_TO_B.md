# AB_BYTE_TO_B

```{index} single: AB_BYTE_TO_B
```

<img width="1201" height="230" alt="image" src="https://github.com/user-attachments/assets/51ece190-d883-49b1-9fe3-c91b94247501" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock AB_BYTE_TO_B ist ein Composite-Funktionsblock, der zur Konvertierung eines BYTE-Datentyps in das AB-Adapterformat dient. Er ermöglicht die unidirektionale Datenübertragung von Byte-Werten über ein standardisiertes Adapter-Interface.

![AB_BYTE_TO_B](AB_BYTE_TO_B.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anforderungsereignis zur Auslösung der Adapter-Konvertierung

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
- **OUT**: BYTE-Eingangswert, der an den Adapter weitergeleitet wird

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden*

### **Adapter**
- **AB_OUT**: Unidirektionaler AB-Adapterausgang für die Datenausgabe

## Funktionsweise
Der Funktionsblock empfängt über den REQ-Ereigniseingang eine Anforderung zur Datenkonvertierung. Gleichzeitig wird der Byte-Wert am Daten-Eingang OUT verarbeitet. Bei Eintreffen des REQ-Ereignisses wird der Byte-Wert über den AB_OUT-Adapter ausgegeben. Die Datenübertragung erfolgt unidirektional vom Funktionsblock zum angeschlossenen Adapter.

## Technische Besonderheiten
- Implementiert als Composite-Funktionsblock mit interner Netzwerkstruktur
- Verwendet das unidirektionale AB-Adapter-Interface
- Direkte Ereignis- und Datenverbindungen zwischen Eingängen und Adapter
- Positionierungsattribute für grafische Darstellung in der Entwicklungsumgebung

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. **Wartezustand**: Keine aktive Verarbeitung
2. **Aktivierungszustand**: Bei REQ-Ereignis werden Daten an den Adapter weitergeleitet
3. **Rückkehr**: Automatische Rückkehr in Wartezustand nach Verarbeitung

## Anwendungsszenarien
- Konvertierung von Byte-Daten für Adapter-basierte Kommunikation
- Integration in größere Steuerungssysteme mit standardisierten Adapter-Schnittstellen
- Datenaufbereitung für nachgelagerte Verarbeitungskomponenten
- Protokollumsetzung bei unterschiedlichen Datentypen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsblöcken bietet AB_BYTE_TO_B den Vorteil der standardisierten Adapter-Schnittstelle, was eine bessere Wiederverwendbarkeit und Integration in komplexere Systemarchitekturen ermöglicht. Die unidirektionale Ausrichtung macht ihn speziell für Ausgabeszenarien geeignet.

## Fazit
AB_BYTE_TO_B ist ein spezialisierter Konvertierungsbaustein, der durch seine Adapter-basierte Architektur eine flexible und standardkonforme Integration in 4diac-basierte Steuerungssysteme ermöglicht. Seine einfache und robuste Funktionsweise macht ihn zu einer zuverlässigen Lösung für Byte-zu-Adapter-Konvertierungen.