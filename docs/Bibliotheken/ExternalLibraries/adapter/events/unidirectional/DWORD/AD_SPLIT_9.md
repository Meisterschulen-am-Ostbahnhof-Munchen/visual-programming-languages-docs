# AD_SPLIT_9


![AD_SPLIT_9](./AD_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_SPLIT_9** verteilt einen eingehenden unidirektionalen Adapter (AD) auf neun identische Ausgänge. Er ist als generischer FB realisiert und eignet sich zur Mehrfachnutzung eines Adaptersignals in verschiedenen nachgelagerten Komponenten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**
| Name | Typ | Richtung |
|------|-----|----------|
| IN   | adapter::types::unidirectional::AD | Socket (Eingang) |
| OUT1 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT2 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT3 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT4 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT5 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT6 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT7 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT8 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT9 | adapter::types::unidirectional::AD | Plug (Ausgang) |

## Funktionsweise
Der FB führt eine **1:n-Verteilung** des eingehenden Adaptersignals durch. Jeder der neun Ausgangsadapter (OUT1 … OUT9) stellt exakt die gleichen Daten wie der Eingangsadapter (IN) bereit. Da der FB weder Ereignis- noch Dateneingänge besitzt, erfolgt die Signalweitergabe rein strukturell: die Verbindung zwischen IN und allen OUTs wird zur Konfigurationszeit festgelegt und zur Laufzeit transparent weitergeleitet.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB trägt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AD_SPLIT'`, wodurch er als Platzhalter für eine typspezifische Instantiierung dient.
- **Typbindung**: Alle Adapter sind vom Typ `adapter::types::unidirectional::AD` – einer standardisierten unidirektionalen Adapterschnittstelle.
- **Keine Ereignissteuerung**: Die Verteilung erfolgt ohne zeitliche Synchronisation oder Ereignisse; Änderungen am Eingangssignal werden sofort an alle Ausgänge weitergegeben.

## Zustandsübersicht
Der FB besitzt keinen internen Zustandsautomaten und führt keinerlei sequentielle Logik aus. Das Verhalten ist **rein kombinatorisch**.

## Anwendungsszenarien
- **Signalmultiplex**: Ein von einem Sensor oder einer Steuerung bereitgestellter Adapter soll an mehrere unabhängige Auswerteeinheiten (z. B. Visualisierung, Protokollierung, Alarmgenerierung) angebunden werden.
- **Modulare Architektur**: In einer IEC 61499-basierten Anwendung kann ein zentraler Datenprovider seine Informationen über `AD_SPLIT_9` an bis zu neun verschiedene Submodule verteilen, ohne die Quelllogik zu vervielfachen.

## Vergleich mit ähnlichen Bausteinen
- **AD_SPLIT_2 / AD_SPLIT_4 / AD_SPLIT_8**: Diese Bausteine bieten die gleiche Funktionalität, jedoch mit einer geringeren Anzahl von Ausgängen (2, 4, 8). `AD_SPLIT_9` ergänzt das Portfolio für Anwendungen, die genau neun parallele Ausgänge benötigen.
- **Andere Split-Bausteine**: Datentyp-orientierte Split-FBs (z. B. für INTEGER oder BOOL) teilen einzelne Datenwerte auf, während `AD_SPLIT_9` vollständige Adapterstrukturen vervielfältigt. Der Adapter kann dabei mehrere zusammengehörige Daten und Ereignisse bündeln.

## Fazit
`AD_SPLIT_9` ist ein einfacher, aber nützlicher generischer Funktionsblock zur unidirektionalen Aufteilung eines Adaptersignals auf neun identische Ausgänge. Er hilft, Redundanz im Systemdesign zu vermeiden und erleichtert die modulare Strukturierung von IEC 61499-Anwendungen.