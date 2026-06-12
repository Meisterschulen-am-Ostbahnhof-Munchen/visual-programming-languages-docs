# AQ_SPLIT_4


![AQ_SPLIT_4](./AQ_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AQ_SPLIT_4` dient als Fan-Out-Komponente zur Verteilung eines eingehenden AQ-Adapters auf vier identische Ausgangs-Adapter. Er wird eingesetzt, um ein analoges Signal oder eine Steuergröße (AQ – Analog Quantity) von einem Sender an mehrere unabhängige Empfänger weiterzuleiten, ohne die Signalintegrität zu beeinträchtigen.

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
| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AQ` | Socket (Eingang) | `IN` | Eingehender AQ-Adapter, der auf die vier Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AQ` | Plug (Ausgang) | `OUT1` | Erster ausgehender AQ-Adapter. |
| `adapter::types::unidirectional::AQ` | Plug (Ausgang) | `OUT2` | Zweiter ausgehender AQ-Adapter. |
| `adapter::types::unidirectional::AQ` | Plug (Ausgang) | `OUT3` | Dritter ausgehender AQ-Adapter. |
| `adapter::types::unidirectional::AQ` | Plug (Ausgang) | `OUT4` | Vierter ausgehender AQ-Adapter. |

## Funktionsweise
Der `AQ_SPLIT_4` leitet alle über den Socket `IN` ankommenden Daten und Ereignisse des AQ-Adapters unverändert an die vier Plug-Adapter `OUT1` bis `OUT4` weiter. Es findet keine Verarbeitung, Filterung oder Verzögerung der Signale statt. Die Verteilung erfolgt rein auf Verbindungsebene, sodass alle Ausgänge stets denselben Zustand wie der Eingang haben.

## Technische Besonderheiten
- **Generische Typisierung**: Der FB verwendet das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AQ_SPLIT'`. Dadurch kann er in 4diac-IDE als generischer Baustein angesprochen werden, was die Wiederverwendbarkeit in verschiedenen Anwendungskontexten erhöht.
- **Keine Zustandslogik**: Der Baustein besitzt keine interne Zustandsmaschine (ECC) und keine Ein-/Ausgangs-Ereignisse. Er agiert als reine „Verdrahtungshilfe“ für Adapterverbindungen.
- **Unidirektionaler Adapter**: Alle verwendeten Adapter sind vom Typ `unidirectional::AQ`, d.h. die Daten fließen nur in eine Richtung (vom Socket zu den Plugs).

## Zustandsübersicht
Der Funktionsblock verfügt über keine Zustandsmaschine. Er ist passiv und führt keinerlei zeit- oder ereignisgesteuerte Operationen aus. Die Signalweitergabe erfolgt kontinuierlich und ohne Zwischenspeicherung.

## Anwendungsszenarien
- **Verteilen eines Messwerts**: Ein analoger Sensor (z.B. Temperatur, Druck, Durchfluss) wird über einen AQ-Adapter angeschlossen und muss an mehrere Regel- oder Überwachungseinheiten gesendet werden.
- **Mehrfachnutzung eines Stellsignals**: Ein von einer Steuerung ausgegebenes analoges Stellsignal wird parallel an mehrere Aktoren (z.B. Ventile, Frequenzumrichter) weitergegeben.
- **Signalüberwachung**: Das ursprüngliche Signal wird unverändert an die Endgeräte gesendet, während ein zusätzlicher Ausgang zur Diagnose oder Protokollierung verwendet wird.

## Vergleich mit ähnlichen Bausteinen
- **AQ_SPLIT_2**: Verteilt ein AQ-Signal auf zwei statt vier Ausgänge – platzsparender bei geringerem Bedarf.
- **IQ_SPLIT_4**: Analoger Baustein für digitale Adapter (z.B. `adapter::types::unidirectional::IQ`), ansonsten identische Funktionsweise.
- **Manuelle Parallelschaltung**: Theoretisch könnte man einen AQ-Socket manuell mit mehreren Plugs verbinden, aber der `AQ_SPLIT_4` bietet eine übersichtliche und wiederverwendbare Kapselung.

## Fazit
Der `AQ_SPLIT_4` ist ein einfacher, aber nützlicher Funktionsblock zur Signalverteilung in der industriellen Automatisierung mit 4diac. Durch seine generische Auslegung und das Fehlen interner Logik ist er leicht verständlich, robust und flexibel einsetzbar. Er trägt zur Strukturierung und Wiederverwendbarkeit von Funktionsblocknetzwerken bei.