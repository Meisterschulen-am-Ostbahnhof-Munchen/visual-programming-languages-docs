# AQ_SPLIT_2


![AQ_SPLIT_2](./AQ_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AQ_SPLIT_2` dient als Fan-Out-Baustein. Er verteilt ein eingehendes AQ (Analog Quantity) Signal unidirektional auf zwei identische Ausgänge. Er realisiert damit eine einfache 1:2-Signalvervielfachung für analoge Größen.

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

| Typ | Name | Richtung | Beschreibung |
|------|------|----------|--------------|
| `adapter::types::unidirectional::AQ` | `IN` | Socket (Eingang) | Eingangsadapter für das zu teilende AQ-Signal. |
| `adapter::types::unidirectional::AQ` | `OUT1` | Plug (Ausgang) | Erster Ausgang – liefert unverändertes Eingangssignal. |
| `adapter::types::unidirectional::AQ` | `OUT2` | Plug (Ausgang) | Zweiter Ausgang – liefert ebenfalls unverändertes Eingangssignal. |

## Funktionsweise
Der Baustein empfängt ein analoges Signal über den Adapter-Socket `IN`. Dieses Signal wird intern ohne Verzögerung oder Umwandlung auf beide Adapter-Plugs `OUT1` und `OUT2` durchgeschaltet. Es findet keinerlei Signalverarbeitung statt – der FB agiert als reiner Splitter.

## Technische Besonderheiten
- **Generische Implementierung**: Der FB ist als generischer Typ `GEN_AQ_SPLIT` deklariert und kann für beliebige AQ-Adapter verwendet werden, solange diese dem unidirektionalen AQ-Interface entsprechen.
- **Keine Ereignissteuerung**: Der Baustein arbeitet rein datengetrieben ohne Ereignisse – eine Zustandsänderung am Eingang wirkt sich sofort auf beide Ausgänge aus.
- **Unidirektional**: Die Adapter sind für eine Richtung ausgelegt (Eingang → Ausgänge).

## Zustandsübersicht
Der FB besitzt keine internen Zustände. Er ist zustandslos (kombinatorisch) und gibt zu jedem Zeitpunkt das aktuell anliegende Eingangssignal an beiden Ausgängen aus.

## Anwendungsszenarien
- **Signalverteilung** in Steuerungssystemen: Ein von einer Sensorik bereitgestelltes analoges Signal soll parallel an zwei unterschiedliche Verbraucher (z.B. zwei Regler oder Anzeigeeinheiten) weitergegeben werden.
- **Test- und Simulationsaufbauten**: Ein Referenzsignal wird ohne Rückwirkung auf mehrere Testpunkte aufgeteilt.
- **Redundante Weiterleitung**: Das Signal wird an zwei unabhängige Pfade gesendet, um Ausfallsicherheit zu erhöhen.

## Vergleich mit ähnlichen Bausteinen
- **`AQ_SPLIT_N`** (hypothetisch): Ein vergleichbarer Baustein mit `N` Ausgängen – `AQ_SPLIT_2` ist eine spezialisierte 1:2-Version.
- **Ereignisgesteuerte Split-Bausteine**: Diese benötigen oft Trigger-Ereignisse und führen dann eine Signalweitergabe durch. `AQ_SPLIT_2` arbeitet dagegen rein signalgetrieben ohne Ereignisse.
- **Bus-basierte Splitter**: Diese verteilen mehrere Signale über einen gemeinsamen Bus (z.B. über Multicast). `AQ_SPLIT_2` arbeitet punktuell und einzeln über Adapter.

## Fazit
Der `AQ_SPLIT_2` ist ein einfacher, aber nützlicher Baustein zur Verteilung eines analogen Signals auf zwei identische Ausgänge. Dank seiner generischen Natur lässt er sich in verschiedenen 4diac-Projekten ohne Anpassungen einsetzen. Die zustandslose Funktionsweise minimiert die Komplexität und macht ihn ideal für Echtzeitanwendungen, bei denen eine sofortige Signalweitergabe erforderlich ist.