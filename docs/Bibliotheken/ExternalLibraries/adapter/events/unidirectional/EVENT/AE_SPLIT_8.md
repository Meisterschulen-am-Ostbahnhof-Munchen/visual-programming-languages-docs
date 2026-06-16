# AE_SPLIT_8


![AE_SPLIT_8](./AE_SPLIT_8.svg)

*Bild des Funktionsblocks: [Hier einfügen, sofern vorhanden]*

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AE_SPLIT_8** dient als generischer Verteiler für einen unidirektionalen Adaptereingang (AE) auf acht identische Adapterausgänge. Er ermöglicht die Mehrfachverwendung eines eingehenden Signals, ohne dieses zu modifizieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** | `IN` | `adapter::types::unidirectional::AE` | Eingehender unidirektionaler AE-Adapter |
| **Plug** | `OUT1` | `adapter::types::unidirectional::AE` | Erster ausgehender AE-Adapter |
| **Plug** | `OUT2` | `adapter::types::unidirectional::AE` | Zweiter ausgehender AE-Adapter |
| **Plug** | `OUT3` | `adapter::types::unidirectional::AE` | Dritter ausgehender AE-Adapter |
| **Plug** | `OUT4` | `adapter::types::unidirectional::AE` | Vierter ausgehender AE-Adapter |
| **Plug** | `OUT5` | `adapter::types::unidirectional::AE` | Fünfter ausgehender AE-Adapter |
| **Plug** | `OUT6` | `adapter::types::unidirectional::AE` | Sechster ausgehender AE-Adapter |
| **Plug** | `OUT7` | `adapter::types::unidirectional::AE` | Siebter ausgehender AE-Adapter |
| **Plug** | `OUT8` | `adapter::types::unidirectional::AE` | Achter ausgehender AE-Adapter |

## Funktionsweise
Der Baustein leitet das am Socket `IN` anliegende Adaptersignal ohne Verzögerung oder Veränderung an alle acht Plugs (`OUT1` bis `OUT8`) weiter. Es findet keine logische oder zeitliche Aufbereitung statt – der eingehende Adapter wird eins-zu-eins vervielfältigt.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Baustein (`GenericClassName: GEN_AE_SPLIT`) definiert und kann in verschiedenen Kontexten wiederverwendet werden.
- **Unidirektionalität**: Sowohl der Eingangs- als auch die Ausgangsadapter sind unidirektional ausgelegt. Eine Rückkopplung von den Ausgängen zum Eingang ist nicht möglich.
- **Keine Ereignissteuerung**: Der Baustein besitzt keine Ereigniseingänge und arbeitet rein passiv. Das Weiterleiten erfolgt sofort bei Verbindungsaufbau.
- **Skalierbarkeit**: Durch die feste Anzahl von acht Ausgängen ist der FB für Anwendungen optimiert, die genau eine 1:8-Verteilung benötigen.

## Zustandsübersicht
Der FB besitzt keine internen Zustände oder Ablaufsteuerung. Es gibt keine ECC (Execution Control Chart) – die Funktionalität ist rein kombinatorisch.

## Anwendungsszenarien
- **Signalverteilung in Steuerungsnetzwerken**: Ein von einem Sensor oder einer übergeordneten Steuerung kommender AE-Adapter soll gleichzeitig an mehrere nachgelagerte Funktionsbausteine weitergegeben werden.
- **Test- und Simulationsumgebungen**: Mehrere Empfänger sollen dasselbe Adaptersignal erhalten, um parallele Reaktionen zu beobachten.
- **Redundante Anbindung**: Das gleiche Signal kann auf mehreren Pfaden parallel verarbeitet werden, beispielsweise für Sicherheits- oder Überwachungsfunktionen.

## Vergleich mit ähnlichen Bausteinen
- **AE_SPLIT_2/AE_SPLIT_4**: Bausteine mit geringerer Anzahl an Ausgängen (2 bzw. 4) für kleinere Verteilungen. **AE_SPLIT_8** erweitert dies auf acht Ausgänge.
- **Daten-Splitter (z. B. SPLIT_INT, SPLIT_BOOL)**: Diese verteilen Datenwerte, während **AE_SPLIT_8** Adaptersignale verteilt. Adapter können komplexe zusammengesetzte Schnittstellen (Ereignisse und Daten) bündeln.
- **Ereignis-Splitter (z. B. E_SPLIT)**: Verteilen ausschließlich Ereignisse. **AE_SPLIT_8** überträgt den gesamten Adapterkontext, einschließlich aller darin enthaltenen Daten- und Ereignisverbindungen.

## Fazit
Der **AE_SPLIT_8** ist ein einfacher und effizienter Baustein zur 1:8-Verteilung unidirektionaler Adaptersignale. Durch seine generische Natur und den Verzicht auf Ereignissteuerung eignet er sich besonders für Anwendungen, in denen ein Signal ohne Verzögerung an mehrere Empfänger parallel weitergeleitet werden muss.