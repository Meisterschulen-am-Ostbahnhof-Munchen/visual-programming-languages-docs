# AUS_SPLIT_2


![AUS_SPLIT_2](./AUS_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AUS_SPLIT_2** dient dazu, ein eingehendes AUS-Signal auf zwei identische Ausgänge zu verteilen. Er ist als generischer Baustein (generic FB) realisiert und eignet sich für Anwendungen, bei denen ein universelles Steuersignal mehrfach benötigt wird. Der Baustein arbeitet rein adapterbasiert und besitzt keine eigenen Ereignis- oder Dateneingänge.

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
| Richtung | Name | Typ              | Beschreibung                                       |
|----------|------|------------------|----------------------------------------------------|
| Sockets  | IN   | AUS (unidirectional) | Eingangsadapter, der das zu verteilende Signal empfängt |
| Plugs    | OUT1 | AUS (unidirectional) | Erster Ausgangsadapter, identisch zum Eingangssignal |
| Plugs    | OUT2 | AUS (unidirectional) | Zweiter Ausgangsadapter, identisch zum Eingangssignal |

## Funktionsweise
Der Baustein leitet das am Socket **IN** anliegende AUS-Signal unverändert an beide Plugs **OUT1** und **OUT2** weiter. Es findet keine Verarbeitung oder Pufferung statt – die Aufteilung erfolgt rein topologisch. Das Eingangssignal wird auf beiden Ausgängen gleichzeitig und ohne Verzögerung zur Verfügung gestellt. Die Verbindung wird erst dann aktiv, wenn der Socket mit einem entsprechenden Adapter verbunden ist.

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein ist als `GEN_AUS_SPLIT` mit dem Attribut `eclipse4diac::core::GenericClassName` deklariert. Dadurch kann er in verschiedenen Projekten ohne Typanpassung wiederverwendet werden.
- **Keine Zustandsabhängigkeit**: Der Baustein arbeitet zustandslos – es gibt kein internes Verhalten, das von einer Zustandsmaschine gesteuert wird.
- **Adapterbasiert**: Alle Schnittstellen sind als Adapter vom Typ `adapter::types::unidirectional::AUS` ausgeführt. Dies ermöglicht flexible Verkabelung in einer gerichteten Kommunikation.
- **Copyright**: Der Baustein stammt von der HR Agrartechnik GmbH und unterliegt der Eclipse Public License 2.0.

## Zustandsübersicht
Da der Baustein keinerlei Zustandslogik besitzt, existiert keine Zustandsmaschine. Die Funktionalität beschränkt sich auf die einfache Signaldurchleitung.

## Anwendungsszenarien
- **Signalverteilung in der Steuerungstechnik**: Wenn ein Bus-Signal oder ein universelles Steuersignal an mehrere parallele Module weitergegeben werden muss.
- **Test- und Simulationsaufbauten**: Um ein einzelnes Testsignal auf zwei parallele Pfade zu splitten.
- **Redundante Anbindung**: Falls ein Signal aus Gründen der Verfügbarkeit an zwei unabhängige Empfänger gesendet werden soll.

## Vergleich mit ähnlichen Bausteinen
- **AUS_SPLIT_3 / AUS_SPLIT_N**: Analoge Bausteine mit drei oder mehr Ausgängen. `AUS_SPLIT_2` ist die einfachste Variante zur Aufteilung auf zwei Kanäle.
- **Ereignis-basierte Splitter**: Im Gegensatz zu Bausteinen mit Ereignis-Eingängen (z.B. `E_SPLIT`) arbeitet `AUS_SPLIT_2` ausschließlich über Adapter und eignet sich daher für reine Signalverteilung ohne Steuerlogik.
- **Merge-Bausteine**: Während Splitter Signale vervielfältigen, fassen Merge-Bausteine mehrere Signale zu einem zusammen (z.B. `AUS_MERGE_2`).

## Fazit
Der `AUS_SPLIT_2` ist ein minimalistischer, aber nützlicher Funktionsbaustein zur dezentralen Signalverteilung in 4diac-Anwendungen. Seine generische Natur und die reine Adapter-Schnittstelle machen ihn universell einsetzbar, insbesondere wenn nur eine unidirektionale Signalkopie benötigt wird. Für komplexere Aufgaben mit Steuer- oder Verarbeitungslogik sind erweiterte Varianten erforderlich.