# A2X_SPLIT_4


![A2X_SPLIT_4](./A2X_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **A2X_SPLIT_4** dient der Aufteilung eines eingehenden A2X-Adaptersignals auf vier identische A2X-Ausgänge. Er ist als generischer Baustein ausgelegt und ermöglicht so eine flexible Verwendung in unterschiedlichsten Automatisierungsumgebungen, in denen ein A2X-Signal mehrfach benötigt wird.

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
| Richtung | Bezeichner | Typ | Beschreibung |
|----------|------------|-----|--------------|
| **Socket (Eingang)** | IN | `adapter::types::unidirectional::A2X` | Ein eingehendes A2X-Signal (unidirektional) |
| **Plug (Ausgang 1)** | OUT1 | `adapter::types::unidirectional::A2X` | Erster ausgehender A2X-Kanal |
| **Plug (Ausgang 2)** | OUT2 | `adapter::types::unidirectional::A2X` | Zweiter ausgehender A2X-Kanal |
| **Plug (Ausgang 3)** | OUT3 | `adapter::types::unidirectional::A2X` | Dritter ausgehender A2X-Kanal |
| **Plug (Ausgang 4)** | OUT4 | `adapter::types::unidirectional::A2X` | Vierter ausgehender A2X-Kanal |

## Funktionsweise
Der Baustein arbeitet als reiner Signalverteiler. Das am Socket **IN** anliegende A2X-Adapter-Interface wird intern ohne weitere Verarbeitung oder Verzögerung auf die vier Ausgangs-Plugs **OUT1** bis **OUT4** durchgeschaltet. Jeder Ausgang liefert exakt dasselbe Signal wie der Eingang. Da es sich um unidirektionale Adapter handelt, erfolgt keine Rückkopplung von den Ausgängen zum Eingang.

## Technische Besonderheiten
- **Generischer Baustein** – Der FB wird als `GEN_A2X_SPLIT` instanziiert und kann durch Typparameter an unterschiedliche A2X-Varianten angepasst werden.
- **Keine Ereignis- oder Datenverarbeitung** – Die gesamte Funktionalität beschränkt sich auf die Weiterleitung des Adaptersignals. Es existieren weder Ereignisse noch Daten-Ein-/Ausgänge.
- **Lizenzierung** – Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0).

## Zustandsübersicht
Der FB besitzt keine Zustandsautomaten (ECC) und kein internes Verhalten, das zeitlich oder zustandsabhängig wäre. Die Ausgangssignale folgen unmittelbar dem Eingangssignal.

## Anwendungsszenarien
- **Verteilung eines A2X-Signals** an mehrere nachgelagerte Funktionsbausteine, die auf dieselben A2X-Informationen angewiesen sind.
- **Sternförmige Topologien** in der Kommunikation zwischen Komponenten eines verteilten Steuerungssystems.
- **Test- und Simulationsumgebungen**, bei denen ein A2X-Signal parallel aufgezeichnet oder analysiert werden soll.

## Vergleich mit ähnlichen Bausteinen
- **A2X_SPLIT_2** / **A2X_SPLIT_3** / **A2X_SPLIT_N** – Diese Bausteine bieten dieselbe Funktionalität mit einer anderen Anzahl von Ausgängen.
- Im Gegensatz zu einem **Multiplexer** oder **Demultiplexer** findet hier keine Selektion statt – das Signal wird immer auf alle Ausgänge dupliziert.

## Fazit
Der **A2X_SPLIT_4** ist ein einfacher, aber nützlicher Baustein zur Vervielfältigung eines unidirektionalen A2X-Adaptersignals. Durch seine generische Auslegung und die klare Schnittstelle lässt er sich leicht in bestehende 4diac-IDE-Projekte integrieren und trägt zur Modularisierung von Steuerungsapplikationen bei.