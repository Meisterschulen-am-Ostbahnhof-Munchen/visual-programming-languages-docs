# ADI_ADD_3


![ADI_ADD_3](./ADI_ADD_3.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ADI_ADD_3` ist ein generischer arithmetischer Baustein, der zur Addition von drei Eingangswerten dient. Er basiert auf dem Standard IEC 61499-2 und nutzt ein adapterbasiertes Kommunikationsmodell. Durch die Verwendung von unidirektionalen Adaptern vom Typ `ADI` (Adapter für Datenintegration/Interaktion) ermöglicht der Baustein eine strukturierte und saubere Signal- und Datenführung innerhalb von 4diac-ide.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten, eigenständigen Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird über die zugeordneten Adapter-Eingänge (Sockets) realisiert.*

### **Ereignis-Ausgänge**

*Es sind keine direkten, eigenständigen Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung wird über den Adapter-Ausgang (Plug) realisiert.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübertragung erfolgt gekoppelt über die Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenübertragung erfolgt gekoppelt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

* **IN1** (Typ: `adapter::types::unidirectional::ADI`): Erster Eingangssummand für die Addition.
* **IN2** (Typ: `adapter::types::unidirectional::ADI`): Zweiter Eingangssummand für die Addition.
* **IN3** (Typ: `adapter::types::unidirectional::ADI`): Dritter Eingangssummand für die Addition.

#### **Plugs (Ausgangs-Schnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::ADI`): Ausgang für das berechnete Additionsergebnis ($OUT = IN1 + IN2 + IN3$).

---

## Funktionsweise

Sobald an einem der Eingangs-Sockets (`IN1`, `IN2` oder `IN3`) ein neues Ereignis oder neue Daten eintreffen, liest der Funktionsbaustein die Werte aus den drei Adaptern aus. Er führt eine arithmetische Addition der drei Werte durch:

$$\text{Ergebnis} = \text{IN1} + \text{IN2} + \text{IN3}$$

Das berechnete Ergebnis sowie das zugehörige Aktualisierungsereignis werden anschließend über den Ausgangs-Plug `OUT` an die nachfolgenden Bausteine im System übermittelt.

---

## Technische Besonderheiten

* **Generischer Baustein (Generic FB):** Durch das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `GEN_ADI_ADD` verhält sich dieser Baustein polymorph. Er ist nicht auf einen festen Datentyp (wie z. B. `INT` oder `REAL`) fixiert, sondern passt sich flexibel an den im Adapter definierten Datentyp an.
* **Adapterbasierte Architektur:** Die Kapselung von Daten und Events in den `ADI`-Adaptern reduziert das "Kabelgewirr" in der 4diac-ide erheblich, da keine separaten Event- und Datenleitungen für jeden Summanden gezogen werden müssen.

---

## Zustandsübersicht

Der Funktionsbaustein verhält sich rein zustandslos (reaktiv):
1. **Wartezustand (Idle):** Der Baustein wartet auf Trigger-Signale der Eingangs-Sockets.
2. **Berechnung & Weiterleitung:** Bei Triggerung an `IN1`, `IN2` oder `IN3` wird die Summe instantan gebildet und über den Plug `OUT` ausgegeben.

---

## Anwendungsszenarien

* **Sensor-Konsolidierung:** Aufsummierung von drei verschiedenen physikalischen Größen (z. B. drei Teilströme in einer Anlage zur Ermittlung des Gesamtstroms).
* **Sollwert-Offset-Berechnung:** Kombination aus einem Hauptsollwert, einem Korrekturwert und einem zusätzlichen Toleranz- oder Offsetwert.
* **Prozesswert-Kalkulation:** Bilanzierung von Zuflüssen an drei verschiedenen Messstellen in der Verfahrenstechnik.

---

## Vergleich mit ähnlichen Bausteinen

* **Standard `ADD` (IEC 61131-3):** Der klassische ADD-Baustein verwendet direkte Pins für Daten und Events. `ADI_ADD_3` ist durch die Verwendung von unidirektionalen Adaptern besser für modular aufgebaute und hierarchische Architekturen in IEC 61499 geeignet.
* **Zwei-Wege-Addierer (z.B. `ADI_ADD_2`):** Während für die Addition von drei Werten mit Standardbausteinen zwei Bausteine kaskadiert werden müssten, erledigt `ADI_ADD_3` diese Aufgabe in einem einzigen Schritt, was Ressourcen schont und die Übersichtlichkeit erhöht.

---

## Fazit

Der `ADI_ADD_3` ist ein praktischer, generischer Hilfsbaustein für arithmetische Operationen in modernen IEC 61499 Steuerungsanwendungen. Durch die konsequente Nutzung von Adaptern fügt er sich nahtlos in saubere Software-Architekturen ein und minimiert den Verdrahtungsaufwand in der Entwicklungsumgebung.