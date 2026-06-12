# AUDI_UDINT_LE


![AUDI_UDINT_LE](./AUDI_UDINT_LE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUDI_UDINT_LE` führt einen Vergleich „kleiner oder gleich“ (less or equal) durch. Er vergleicht zwei Werte des Typs `UDINT` – einen über einen Adaptereingang bereitgestellten Wert und einen direkten Dateneingang – und gibt das Ergebnis über einen Adapterausgang aus. Der Baustein arbeitet ereignisgesteuert und ist nach IEC 61131‑3 als standard comparison function klassifiziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Service Request – löst die Vergleichsoperation aus |

- Der Ereigniseingang `REQ` ist mit dem Dateneingang `IN2` verknüpft (`With Var="IN2"`), d. h. der Wert von `IN2` wird bei der Verarbeitung benötigt.

### **Ereignis-Ausgänge**

Der Funktionsblock besitzt keinen eigenen Ereignisausgang auf der obersten Schnittstelle. Das Ergebnis wird stattdessen über den Adapterausgang `OUT` signalisiert. Der interne Ereignisausgang `CNF` des eingebetteten Vergleichsbausteins wird direkt auf den Ereigniseingang des Ausgangsadapters geführt.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN2` | UDINT | Input value 2 – der rechte Operand des Vergleichs |

### **Daten-Ausgänge**

Der Funktionsblock hat keine direkten Datenausgänge. Das Vergleichsergebnis (boolescher Wert) wird über den Adapter `OUT` bereitgestellt.

### **Adapter**

| Typ | Name | Rolle | Kommentar |
|-----|------|-------|-----------|
| `adapter::types::unidirectional::AUDI` | `IN1` | Socket (Eingangsadapter) | Input value 1 – liefert den linken Operanden des Vergleichs |
| `adapter::types::unidirectional::AX` | `OUT` | Plug (Ausgangsadapter) | Ergebnis des Vergleichs: `IN1 <= IN2` (true/false) |

- Der Adapter `IN1` liefert neben dem Datenwert auch ein Ereignis (`E1`), das mit dem internen Vergleichsbaustein verbunden ist.
- Der Adapter `OUT` empfängt ein Ereignis (`E1`) sowie den Datenwert (`D1`) mit dem Ergebnis.

## Funktionsweise

1. Wird am Ereigniseingang `REQ` ein Signal angelegt, wird der eingebettete Funktionsblock `F_LE` (less or equal) gestartet.
2. Der Datenwert des Adaptereingangs `IN1.D1` und der direkte Dateneingang `IN2` werden an `F_LE.IN1` und `F_LE.IN2` übergeben.
3. Der interne Baustein führt den Vergleich `IN1 ≤ IN2` durch und legt das Ergebnis (typischerweise `TRUE` oder `FALSE`) an seinem Ausgang `OUT` an.
4. Nach Abschluss der Verarbeitung sendet `F_LE` ein Ereignis über seinen Ausgang `CNF`. Dieses Ereignis wird an den Ausgangsadapter `OUT.E1` weitergeleitet, sodass der nachgeschaltete Baustein über den Abschluss und das Ergebnis informiert wird.

- Die Ereignissteuerung kann sowohl über den externen Ereigniseingang `REQ` als auch über das vom Adapter `IN1` kommende Ereignis `IN1.E1` erfolgen (beide sind mit `F_LE.REQ` verbunden). Dies ermöglicht eine flexible Ansteuerung.

## Technische Besonderheiten

- **Adapter‑basierte Schnittstelle:** Der Baustein verwendet standardisierte unidirektionale Adapter (`AUDI` und `AX`), die eine lose Kopplung zwischen den Verbundenen Bausteinen erlauben. Der Datentyp `UDINT` wird über die Adapter‑Schnittstelle transparent übertragen.
- **Wiederverwendung von Standardbausteinen:** Die eigentliche Vergleichslogik wird durch den internen `F_LE`‑Baustein aus der IEC 61131‑3‑Bibliothek realisiert. Dies erhöht die Wartbarkeit und Konsistenz.
- **Ereignisverknüpfung:** Der Ausgangsadapter wird sowohl mit dem Ergebnisdatenwert als auch mit einem Bestätigungsereignis versorgt, sodass der empfangende Baustein den Zeitpunkt der Datenübernahme kennt.
- **Kein eigener Zustand:** Der Baustein ist zustandslos (stateless); die Verarbeitung erfolgt bei jedem Ereignis neu.

## Zustandsübersicht

Der Funktionsblock besitzt keine explizite Zustandsmaschine. Das Verhalten ist rein kombinatorisch: Bei jedem Ereigniseingang wird der Vergleich einmal ausgeführt. Es gibt keine internen Speicher oder zeitlichen Abhängigkeiten.

## Anwendungsszenarien

- **Grenzwertüberwachung:** Überprüfung, ob ein über einen Sensoradapter (z. B. `AUDI`) gelieferter Istwert kleiner oder gleich einem Sollwert (`IN2`) ist. Das Ergebnis kann z. B. eine Alarmgrenze oder eine Freigabebedingung darstellen.
- **Steuerungslogik:** Einsatz in Verbindung mit anderen Funktionsblöcken, wenn eine Bedingung „Wert1 ≤ Wert2“ als Teil einer Verriegelung oder Ablaufsteuerung benötigt wird.
- **Datenfilter:** Selektion von Werten, die eine obere Schranke nicht überschreiten dürfen.

## Vergleich mit ähnlichen Bausteinen

- **Direkter Vergleichs‑FB `F_LE`:** Im Gegensatz zum einfachen `F_LE`‑Baustein bietet `AUDI_UDINT_LE` eine Adapterschnittstelle, die eine modulare Einbindung in adapterbasierte Netzwerke ermöglicht und die Typkonformität durch die spezifischen Adaptertypen sicherstellt.
- **Andere Vergleichsbausteine (z. B. `LT`, `EQ`, `GT`):** Diese unterscheiden sich lediglich in der Vergleichsoperation. Der Aufbau mit Adaptern und Ereignissteuerung ist identisch.
- **Adapter‑Bausteine ohne internen Vergleich:** `AUDI_UDINT_LE` kombiniert Datenbereitstellung über Adapter mit einer festen Vergleichsfunktion, wodurch ein kompakter, wiederverwendbarer Baustein entsteht.

## Fazit

`AUDI_UDINT_LE` ist ein übersichtlicher und effizienter Funktionsblock für den Vergleich „kleiner oder gleich“ von zwei `UDINT`-Werten. Durch die Verwendung standardisierter Adapter und den Rückgriff auf einen bewährten Kernbaustein ist er robust, erweiterbar und gut in industrielle Steuerungsumgebungen integrierbar. Die einfache Schnittstelle und das zustandslose Verhalten machen ihn besonders für sicherheitsgerichtete und modulare Automatisierungslösungen geeignet.