# AUS_ADD_3


![AUS_ADD_3](./AUS_ADD_3.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUS_ADD_3` ist ein generischer arithmetischer Additionsbaustein für die 4diac-IDE. Er dient dazu, die Werte von drei Eingangs-Adaptern (`IN1`, `IN2` und `IN3`) zu addieren und das Ergebnis über einen Ausgangs-Adapter (`OUT`) bereitzustellen. Der Baustein nutzt dafür unidirektionale Adapter vom Typ `AUS`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Steuerung und Triggerung erfolgt über die Adapter-Schnittstellen.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt über die Adapter-Schnittstellen.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

Der Baustein kommuniziert ausschließlich über Adapter-Schnittstellen:

**Sockets (Eingangs-Adapter):**

- **IN1** (Typ: `adapter::types::unidirectional::AUS`): Erster Summand für die Addition.
- **IN2** (Typ: `adapter::types::unidirectional::AUS`): Zweiter Summand für die Addition.
- **IN3** (Typ: `adapter::types::unidirectional::AUS`): Dritter Summand für die Addition.

**Plugs (Ausgangs-Adapter):**

- **OUT** (Typ: `adapter::types::unidirectional::AUS`): Ausgangsadapter, der das Ergebnis der Addition (`IN1 + IN2 + IN3`) führt.

## Funktionsweise

Sobald an einem der Eingangs-Adapter (`IN1`, `IN2` oder `IN3`) ein neues Ereignis oder ein geänderter Datenwert signalisiert wird, führt der Baustein intern eine Addition der Werte aus.
Die Berechnung folgt der mathematischen Formel:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Nach erfolgreicher Berechnung wird das Ergebnis sowie das zugehörige Aktualisierungsereignis über den Ausgangs-Adapter `OUT` an nachfolgende Bausteine weitergeleitet.

## Technische Besonderheiten

- **Generischer Baustein:** Der Baustein basiert auf der generischen Klasse `GEN_AUS_ADD` (Attribut `eclipse4diac::core::GenericClassName`). Dies ermöglicht eine flexible Anpassung an unterschiedliche Datentypen innerhalb des `AUS`-Adapters.
- **Adapterbasierte Architektur:** Durch die Verwendung von Adaptern anstelle von Standard-Event/Data-Verbindungen wird der Verdrahtungsaufwand im Funktionsplan drastisch reduziert, da Events und Daten in einem einzigen Kanal (dem Adapter) gebündelt sind.
- **Unidirektionaler Datenfluss:** Die verwendeten Adapter sind unidirektional, was eine klare Richtung der Datenverarbeitung von den Eingängen zum Ausgang vorgibt.

## Zustandsübersicht

Da es sich um einen kombinatorischen (bzw. zustandslosen) Funktionsbaustein handelt, besitzt `AUS_ADD_3` keine komplexen internen Zustände (keine State Machine). Die Verarbeitung erfolgt rein ereignisgesteuert:

1. **Wartezustand:** Der Baustein wartet auf ein Ereignis an einem der Eingänge (`IN1`, `IN2`, `IN3`).
2. **Berechnung:** Bei Eintreffen eines Ereignisses werden die Daten ausgelesen und addiert.
3. **Aktualisierung:** Das Ergebnis wird an `OUT` geschrieben und das entsprechende Ausgangsereignis am Adapter ausgelöst.

## Anwendungsszenarien

- **Messwert-Aggregat:** Zusammenführung und Summation von drei analogen Sensorwerten (z. B. drei Durchflussmesser, Temperaturfühler oder Stromverbraucher), die über Adapter-Schnittstellen im System verteilt sind.
- **Sollwert-Generierung:** Addition von Basis-Sollwerten, Korrekturwerten und Offsets in Regelungssystemen.

## Vergleich mit ähnlichen Bausteinen

- **Standard-ADD (IEC 61131-3):** Klassische `ADD`-Bausteine nutzen dedizierte Event- und Datenleitungen. `AUS_ADD_3` hingegen kapselt diese in Adaptern, was zu saubereren Software-Architekturen führt.
- **AUS_ADD_2 / AUS_ADD_4:** Im Vergleich zu Varianten mit zwei oder vier Eingängen ist dieser Baustein speziell auf genau drei Eingangskanäle optimiert, um ungenutzte Schnittstellen im Programmcode zu vermeiden.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUS_ADD_3` ist ein effizienter und wiederverwendbarer Funktionsbaustein zur Addition von drei Signalen. Durch die konsequente Nutzung von unidirektionalen Adaptern fördert er ein modulares, übersichtliches und wartungsfreundliches Anwendungsdesign innerhalb der IEC 61499 Entwicklungsumgebung.
