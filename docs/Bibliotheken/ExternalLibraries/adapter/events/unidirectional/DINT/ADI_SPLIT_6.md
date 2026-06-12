# ADI_SPLIT_6


![ADI_SPLIT_6](./ADI_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock ADI_SPLIT_6 dient dazu, einen einzelnen ADI-Adapter-Eingang (unidirektional) auf sechs identische ADI-Adapter-Ausgänge zu verteilen. Er ist als generischer Baustein für das Eclipse 4diac Framework konzipiert und wird typischerweise eingesetzt, wenn ein ADI-Signal an mehrere nachfolgende Komponenten weitergeleitet werden muss.

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
Der Baustein kommuniziert ausschließlich über Adapter-Schnittstellen:

**Socket (Eingang):**
- `IN`: Typ `adapter::types::unidirectional::ADI` – nimmt ein unidirektionales ADI-Signal entgegen.

**Plugs (Ausgänge):**
- `OUT1` bis `OUT6`: jeweils Typ `adapter::types::unidirectional::ADI` – geben das eingehende Signal identisch auf sechs parallele Ausgänge weiter.

## Funktionsweise
Der FB führt eine reine 1:6-Verteilung des ADI-Adapter-Signals durch. Alle Daten und Ereignisse, die am Socket `IN` ankommen, werden unverändert und zeitgleich an alle sechs Plugs `OUT1`…`OUT6` weitergegeben. Es findet keine Pufferung, Filterung oder Verzögerung statt. Der Baustein arbeitet somit als passiver Splitter auf Adapterebene.

## Technische Besonderheiten
- **Generische Implementierung:** Der FB ist als generischer Baustein (`eclipse4diac::core::GenericClassName = 'GEN_ADI_SPLIT'`) realisiert und kann in verschiedenen Projekten wiederverwendet werden.
- **Unidirektionale Adapter:** Die verwendeten ADI-Adapter sind unidirektional ausgelegt; eine Rückkopplung über die Ausgänge ist nicht vorgesehen.
- **Keine eigenen Zustände:** Da der FB keine Ereignis- oder Datenverarbeitung durchführt, besitzt er keinen internen Zustandsautomaten.
- **Performance:** Durch die direkte Weiterleitung ohne Logik oder Speicher entsteht praktisch keine Latenz.

## Zustandsübersicht
Der Baustein verfügt über keinen Zustandsautomaten oder explizite Betriebszustände. Er ist stets aktiv und gibt das Eingangssignal sofort an alle Ausgänge weiter.

## Anwendungsszenarien
- **Signalverteilung in Steuerungssystemen:** Ein von einem Sensor oder einer zentralen Logik bereitgestelltes ADI-Signal soll parallel an mehrere Aktoren, Anzeigen oder nachgelagerte Funktionen gesendet werden.
- **Testumgebungen:** Bei der Simulation oder beim Debugging kann ein einzelnes Signal auf mehrere Empfänger aufgeteilt werden, um verschiedene Komponenten gleichzeitig zu testen.
- **Redundanzabbildung:** Falls ein Signal mehrfach benötigt wird (z. B. für Überwachungs- und Steuerungspfade), kann dieser Splitter eine saubere Entkopplung der Ausgänge ermöglichen.

## Vergleich mit ähnlichen Bausteinen
- **SPLIT für Standard-Datentypen:** Viele Frameworks bieten Splitter für einfache Datentypen (z. B. `SPLIT_INT`). Der `ADI_SPLIT_6` ist speziell für den Adapter-Typ `ADI` ausgelegt und arbeitet auf einer höheren Abstraktionsebene (Adapter statt einzelner Datenpunkte).
- **ADI_MERGE / ADI_COMBINE:** Während dieser Baustein ein Signal verteilt, fassen andere Bausteine mehrere Adapter-Eingänge zu einem Ausgang zusammen.
- **Weitere Splitter-Varianten:** Es existieren möglicherweise Splitter für andere Adapter-Typen (z. B. bidirektionale ADI). Der vorliegende FB beschränkt sich auf unidirektionale Signale.

## Fazit
Der `ADI_SPLIT_6` ist ein einfacher aber effektiver Baustein zur Vervielfachung unidirektionaler ADI-Adapter-Signale. Durch die generische Auslegung und die geringe Komplexität eignet er sich hervorragend für den modularen Aufbau von Steuerungsanwendungen im Eclipse 4diac Umfeld. Seine Einsatzmöglichkeiten reichen von der reinen Signalverteilung bis hin zu Test- und Redundanzszenarien.