# AUDI_MUL_2


![AUDI_MUL_2](./AUDI_MUL_2.svg)

**Bild:** Kein Bild vorhanden.

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUDI_MUL_2` ist ein generischer Baustein zur Berechnung des arithmetischen Produkts zweier numerischer Werte. Er empfängt seine Operanden über zwei Eingangsadapter und gibt das Ergebnis über einen Ausgangsadapter aus. Die generische Ausprägung erlaubt die Verwendung unterschiedlicher Datentypen (z. B. Ganzzahlen, Gleitkommazahlen), die durch den konkreten Adaptertyp festgelegt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine direkten Datenports. Die Eingangswerte werden über die Adapter `IN1` und `IN2` übertragen.

### **Daten-Ausgänge**

Keine direkten Datenports. Das Ergebnis wird über den Adapter `OUT` ausgegeben.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `IN1` | `adapter::types::unidirectional::AUDI` | Erster Multiplikationsoperand |
| **Socket** (Eingang) | `IN2` | `adapter::types::unidirectional::AUDI` | Zweiter Multiplikationsoperand |
| **Plug** (Ausgang) | `OUT` | `adapter::types::unidirectional::AUDI` | Produkt der beiden Eingangswerte |

*Anmerkung:* Der Adaptertyp `AUDI` ist ein unidirektionaler, typisierter Adapter, der den eigentlichen numerischen Wert kapselt.

## Funktionsweise

Der Baustein führt die Multiplikation `OUT = IN1 * IN2` aus, sobald beide Eingangswerte über die Adapter anliegen. Da keine Ereignisse vorhanden sind, erfolgt die Verarbeitung rein datengetrieben: Sobald die Socket-Adapter `IN1` und `IN2` gültige Werte bereitstellen, wird das Produkt berechnet und über den Plug-Adapter `OUT` ausgegeben.

Der Funktionsblock ist generisch ausgelegt. Der konkrete Datentyp (z. B. `REAL`, `INT`, `LINT`) wird durch den jeweils verwendeten Adaptertyp vorgegeben. Die Multiplikation erfolgt mit der für diesen Typ definierten Operation.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Der Baustein verwendet keine klassischen Ereignis-/Datenports, sondern ausschließlich Adapter. Dies ermöglicht eine lose Kopplung und Wiederverwendung in verschiedenen Kontexten.
- **Generische Auslegung:** Die Attribute `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash` kennzeichnen den Baustein als generisch. Der tatsächliche Datentyp wird erst im konkreten Projekt festgelegt, z. B. durch Typisierung des Adapters.
- **Kein Execution Control Chart (ECC):** Da keine Ereignisse existieren, wird kein Zustandsautomat benötigt. Die Verarbeitung erfolgt kontinuierlich bei gültigen Daten.

## Zustandsübersicht

Der Baustein besitzt keine Zustände oder ECC‑Zustandsdiagramme. Die Ausführung ergibt sich ausschließlich aus dem Datenfluss.

## Anwendungsszenarien

- Arithmetische Berechnungen in industriellen Steuerungsanwendungen, bei denen die Multiplikation zweier Werte benötigt wird (z. B. Skalierung, Umrechnung von Einheiten).
- Verwendung in komplexen Funktionsbausteinen, in denen die Operanden über Adapter aus anderen Komponenten stammen.
- Ersatz für klassische MUL‑Funktionsbausteine, wenn eine lose Kopplung über Adapter gewünscht ist.

## Vergleich mit ähnlichen Bausteinen

- **Klassischer MUL‑FB** (mit Ereignis‑/Datenports): Arbeitet ereignisgesteuert und benötigt explizite Dateneingänge/-ausgänge. `AUDI_MUL_2` hingegen verwendet Adapter, was eine flexiblere Verschaltung ermöglicht.
- **Andere generische Arithmetik‑Bausteine** (z. B. `AUDI_ADD_2`): Gleiche Struktur, aber mit anderer Operation. Das Adapter‑Interface bleibt identisch, sodass eine einfache Austauschbarkeit gegeben ist.

## Fazit

`AUDI_MUL_2` ist ein generischer, adapterbasierter Multiplikationsbaustein für IEC 61499‑Anwendungen. Durch den Verzicht auf Ereignisse und die Nutzung typisierter Adapter eignet er sich besonders für datenflussorientierte und lose gekoppelte Systeme. Die generische Ausprägung erlaubt den Einsatz mit verschiedenen numerischen Datentypen, ohne dass der Baustein selbst angepasst werden muss.