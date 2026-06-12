# AD_SPLIT_4


![AD_SPLIT_4](./AD_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_SPLIT_4** dient dazu, einen eingehenden unidirektionalen AD-Adapter (Adapter Definition) auf vier identische Ausgänge zu verteilen. Es handelt sich um einen generischen Baustein, der speziell für die Aufteilung eines einzelnen AD-Signals in bis zu vier separate Pfade konzipiert ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden. Die Datenübertragung erfolgt ausschließlich über den eingehenden AD-Adapter.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die vier ausgehenden AD-Adapter.

### **Adapter**
Der Baustein verwendet ausschließlich Adapter vom Typ `adapter::types::unidirectional::AD`:

* **Socket (Eingang)**  
  `IN` – Ein unidirektionaler AD-Eingang, der das aufzuteilende Signal empfängt.

* **Plugs (Ausgänge)**  
  `OUT1`, `OUT2`, `OUT3`, `OUT4` – Vier unidirektionale AD-Ausgänge, die das vom Eingang empfangene Signal identisch weiterleiten.

## Funktionsweise
Der **AD_SPLIT_4**-Baustein kopiert den an seinem Socket `IN` ankommenden AD-Datenstrom (ohne Ereignissteuerung) und stellt diesen an allen vier Plugs `OUT1` bis `OUT4` parallel zur Verfügung. Die Verteilung erfolgt ohne Verzögerung oder Pufferung – jede Änderung am Eingang wird sofort an alle Ausgänge propagiert. Der Baustein ist generisch ausgelegt, sodass der konkrete Datentyp des AD-Adapters erst zur Laufzeit festgelegt wird (GenericClassName = `'GEN_AD_SPLIT'`).

## Technische Besonderheiten
* **Generischer Typ**: Der Baustein ist als generischer Funktionsblock implementiert. Der tatsächliche AD-Datentyp wird durch das Attribut `eclipse4diac::core::GenericClassName` (`'GEN_AD_SPLIT'`) bestimmt.
* **Unidirektionale Kommunikation**: Der verwendete Adapter `adapter::types::unidirectional::AD` erlaubt nur eine Datenübertragung vom Socket zu den Plugs – eine Rückkopplung ist nicht vorgesehen.
* **Keine Ereignissteuerung**: Der Baustein benötigt keine Ereignisse, da die Datenweitergabe rein datengetrieben (oder durch die zugrundeliegende Adapter-Logik) erfolgt.

## Zustandsübersicht
Da der Baustein keine Ereignis-Ein-/Ausgänge besitzt, gibt es keine Zustandsmaschine. Das Verhalten ist deterministisch: Die Ausgänge spiegeln stets den aktuellen Zustand des Eingangs wider.

## Anwendungsszenarien
* **Signalverteilung**: Wenn ein einziges AD-Signal (z. B. ein Messwert oder ein Steuerungssignal) an mehrere nachfolgende Funktionsblöcke oder Hardware-Komponenten weitergeleitet werden muss.
* **Monitoring und Kontrolle**: Gleichzeitige Überwachung eines Signals in verschiedenen Logikeinheiten, ohne dass die Signalquelle mehrfach bereitgestellt werden muss.
* **Redundanzpfade**: Aufteilung eines Signals für parallele, unabhängige Verarbeitungspfade.

## Vergleich mit ähnlichen Bausteinen
* **AD_SPLIT_2**, **AD_SPLIT_8**: Verwandte Bausteine mit identischer Funktionsweise, jedoch für zwei bzw. acht Ausgänge. Die Wahl hängt von der Anzahl der benötigten Verteilungen ab.
* **AD_MERGE_4**: Ein Gegenstück, das mehrere AD-Eingänge zu einem Ausgang zusammenführt, im Gegensatz zur Aufteilung.
* **Reine Daten-Split-Bausteine (z. B. D_SPLIT_4)**: Diese teilen einzelne Datenwerte (z. B. INT, REAL) auf, während AD_SPLIT_4 speziell für den komplexen AD-Adapter-Typ ausgelegt ist.

## Fazit
Der **AD_SPLIT_4**-Funktionsblock ist ein kompaktes, generisches Werkzeug zur einfachen Vervielfältigung eines unidirektionalen AD-Signals. Seine klare Schnittstelle ohne Ereignisse macht ihn besonders geeignet für datenflussorientierte Applikationen in der Automatisierungstechnik, bei denen ein Signal an mehrere Empfänger verteilt werden muss. Durch die generische Auslegung kann er flexibel an verschiedene Adapter-Datentypen angepasst werden.