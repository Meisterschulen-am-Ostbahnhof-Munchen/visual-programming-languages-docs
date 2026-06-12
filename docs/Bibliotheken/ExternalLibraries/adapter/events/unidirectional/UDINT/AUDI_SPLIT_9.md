# AUDI_SPLIT_9


![AUDI_SPLIT_9](./AUDI_SPLIT_9.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUDI_SPLIT_9` dient dazu, ein ankommendes AUDI-Signal über einen Socket auf neun identische AUDI-Plugs zu verteilen. Er realisiert eine 1-zu-9-Split-Funktionalität, bei der alle Ausgänge stets den gleichen Wert wie der Eingang führen. Der Baustein ist als generischer FB (GenericClassName `GEN_AUDI_SPLIT`) definiert und ermöglicht die einfache Vervielfältigung von AUDI-Datenströmen innerhalb einer 4diac-IDE-Applikation.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden. Die Datenübertragung erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden. Die Ausgangssignale werden direkt über die Adapter-Plugs bereitgestellt.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden. Die Eingangsdaten werden über den Socket-Adapter `IN` eingelesen.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Die Ausgangsdaten werden über die neun Plug-Adapter `OUT1` bis `OUT9` ausgegeben.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | Empfängt das zu verteilende AUDI-Signal. |
| `OUT1` ... `OUT9` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang) | Neun Ausgänge, die den Wert von `IN` replizieren. Jeder Ausgang ist identisch und unabhängig. |

## Funktionsweise

Der Baustein stellt eine passive Kopplung zwischen dem Socket `IN` und den neun Plugs `OUT1` bis `OUT9` her. Immer wenn der Socket ein gültiges AUDI-Datenpaket empfängt, wird dieses unverändert an alle neun Plugs weitergereicht. Es findet keinerlei Datenmodifikation, Pufferung oder zeitliche Verzögerung statt. Der Baustein besitzt kein eigenes Verhalten – er fungiert als reine Verdrahtungshilfe zur Signalfächerung.

## Technische Besonderheiten

- **Generische Implementierung:** Der FB trägt das Attribut `eclipse4diac::core::GenericClassName = 'GEN_AUDI_SPLIT'`, wodurch er als Instanz eines generischen Split-Bausteins erkannt wird und in Werkzeugen mit generischer Typunterstützung korrekt dargestellt werden kann.
- **Keine Ereignissteuerung:** Da keinerlei Ereignisse vorhanden sind, erfolgt die Datenweitergabe rein über die Adapter-Mechanismen des Zielsystems (z. B. kontinuierlich oder zyklisch, abhängig von der Laufzeitumgebung).
- **Skalierbarkeit:** Die Anzahl der Ausgänge ist fest auf neun ausgelegt. Für andere Anzahlen müssen separate FB-Typen (z. B. `AUDI_SPLIT_2`, `AUDI_SPLIT_4` etc.) definiert oder ein parametrierbarer Baustein verwendet werden.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustand. Sein Verhalten ist vollständig statisch und durch die reine Weiterleitung des Signals definiert. Eine Zustandsmaschine existiert nicht.

## Anwendungsszenarien

- **Verteilen eines Mess-Signals** an mehrere parallele Auswerte- oder Steuereinheiten.
- **Aufteilung eines Steuerbefehls** an mehrere Aktoren, sofern diese das gleiche AUDI-Protokoll verwenden.
- **Test- und Simulationsumgebungen**, bei denen ein generiertes Signal an mehrere Beobachter (z. B. Logging, Visualisierung, Regelung) gleichzeitig gesendet werden soll.
- **Ersatz für mehrere Kopien** eines Quellbausteins, wenn die Quelle nur einmal vorhanden ist.

## Vergleich mit ähnlichen Bausteinen

Gegenüber einem allgemeinen `AUDI_MERGE` (der mehrere Eingänge zu einem Ausgang zusammenführt) oder einem `AUDI_SELECT` (der zwischen mehreren Eingängen umschaltet) bietet der Split-Baustein die exakte Umkehrfunktion: Vervielfältigung statt Zusammenführung oder Selektion. Im Vergleich zu einem eigenen, in Software realisierten Split (z. B. durch mehrfache Verbindung eines Ausgangs in der Applikation) gewährleistet der FB eine saubere, typisierte und wiederverwendbare Schnittstelle und vermeidet potenzielle Mehrfachverbindungsfehler im Editor.

## Fazit

Der `AUDI_SPLIT_9` ist ein einfacher, aber nützlicher Funktionsbaustein zur Vervielfältigung von AUDI-Signalen. Seine Implementation als generischer Typ und die klare Trennung von Eingang und neun Ausgängen erleichtert den Aufbau modularer Automatisierungslösungen. Aufgrund seiner statischen Natur ist er besonders geeignet für datenflussorientierte Anwendungen, bei denen keine Ereignissteuerung erforderlich ist.