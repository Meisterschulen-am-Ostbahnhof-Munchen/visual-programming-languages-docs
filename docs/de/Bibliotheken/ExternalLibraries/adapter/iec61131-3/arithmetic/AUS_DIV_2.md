# AUS_DIV_2


![AUS_DIV_2](./AUS_DIV_2.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein (FB) **AUS_DIV_2** ist ein generischer Baustein zur Durchführung der arithmetischen Division (DIV). Er ist für den Einsatz in IEC 61499-konformen Systemen (wie Eclipse 4diac) konzipiert. Der Baustein nutzt unidirektionale Adapter des Typs `AUS`, um die Eingangsdaten zu empfangen, die Division durchzuführen und das Ergebnis über einen entsprechenden Ausgangsadapter weiterzuleiten. Durch die Kapselung der Signale in Adaptern wird die Verdrahtung innerhalb der Entwicklungsumgebung erheblich vereinfacht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Es sind keine direkten Ereignis-Eingänge auf der Bausteinoberfläche vorhanden. Die ereignisbasierte Steuerung und Triggerung der Berechnung erfolgt intern über die angeschlossenen Eingangs-Adapter.

### **Ereignis-Ausgänge**

Es sind keine direkten Ereignis-Ausgänge auf der Bausteinoberfläche vorhanden. Die Weiterleitung von Berechnungs- und Aktualisierungsereignissen erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Der Baustein besitzt keine direkten elementaren Daten-Eingänge. Alle Eingangsdaten werden über die Adapter-Schnittstellen übergeben.

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten elementaren Daten-Ausgänge. Das Berechnungsergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

| Typ | Name | Adaptertyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Socket (Eingang)** | `IN1` | `adapter::types::unidirectional::AUS` | Erster Eingangswert für die Division (Dividend). |
| **Socket (Eingang)** | `IN2` | `adapter::types::unidirectional::AUS` | Zweiter Eingangswert für die Division (Divisor). |
| **Plug (Ausgang)** | `OUT` | `adapter::types::unidirectional::AUS` | Ausgang für das Ergebnis der Division (Quotient). |

## Funktionsweise

Der Baustein `AUS_DIV_2` führt eine klassische Division nach folgendem mathematischen Prinzip aus:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Da es sich um einen generischen Funktionsbaustein handelt (gekennzeichnet durch das Attribut `GEN_AUS_DIV`), ist der Baustein nicht auf einen festen Datentyp (wie z. B. `INT` oder `REAL`) festgelegt. Der tatsächliche Datentyp wird bei der Instanziierung in der 4diac-IDE basierend auf den verbundenen Adaptern aufgelöst.

Sobald an den Eingangs-Adaptern `IN1` oder `IN2` ein neues Datenereignis signalisiert wird, führt der Baustein die Division durch und aktualisiert den Wert am Ausgangs-Adapter `OUT`, gefolgt von einem entsprechenden Freigabeereignis über den Ausgangs-Plug.

## Technische Besonderheiten

- **Generischer Typ (`GEN_AUS_DIV`):** Ermöglicht eine flexible Wiederverwendung für unterschiedliche numerische Datentypen, ohne dass separate Bausteine für `INT`, `REAL` oder `LREAL` angelegt werden müssen.
- **Unidirektionale Adapter:** Die Verwendung des Typs `adapter::types::unidirectional::AUS` sorgt für eine saubere Daten- und Event-Kapselung. Dies reduziert die visuelle Komplexität im Systementwurf (weniger "Spaghetti-Code" durch lose Event- und Datenlinien).
- **Division durch Null:** Bei der Implementierung auf der Zielplattform (Runtime) ist darauf zu achten, wie der Baustein auf einen Divisor von `0` reagiert (z. B. Ausgabe von `NaN`/`INF` bei Gleitkommazahlen oder Systemfehler bei Ganzzahlen).

## Zustandsübersicht

Der Baustein besitzt kein komplexes internes Zustandsdiagramm (ECC). Seine Ausführung ist rein transaktional:

1. **Wartezustand:** Der Baustein wartet auf ein Aktualisierungsereignis an den Sockets `IN1` oder `IN2`.
2. **Berechnung:** Bei Ereigniseingang werden die Werte ausgelesen und dividiert.
3. **Ausgabe:** Das Ergebnis wird an den Plug `OUT` geschrieben und das Ausgangsereignis getriggert. Der Baustein kehrt sofort in den Wartezustand zurück.

## Anwendungsszenarien

- **Messwertskalierung:** Division von Sensorwerten durch konstante Faktoren, die über Adapterstrukturen im System verteilt werden.
- **Mittelwertberechnung:** Einsatz in mathematischen Berechnungsnetzwerken innerhalb von verteilten Steuerungssystemen.
- **Verhältnissteuerung:** Berechnung von Verhältnissen (z. B. Luft-Brennstoff-Verhältnis in Brennersteuerungen), bei denen die Eingangssignale bereits als standardisierte `AUS`-Adapter vorliegen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Ganzzahl-Divisionsbaustein (wie dem IEC 61131-3 `DIV` Baustein) bietet `AUS_DIV_2` folgende Vorteile:

- **Adapterbasierte Kopplung:** Standard-FBs benötigen separate Pins für Daten und Events (REQ/CNF). `AUS_DIV_2` bündelt diese logisch in den `AUS`-Adaptern.
- **Datentyp-Flexibilität:** Während klassische Bausteine oft fest für z. B. `REAL` (e.g., `R_DIV`) definiert sind, passt sich dieser generische Baustein dem verwendeten Adaptertyp an.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der Funktionsbaustein `AUS_DIV_2` ist ein hocheffizienter, wiederverwendbarer Hilfsbaustein für arithmetische Berechnungen in modernen, adapterbasierten IEC 61499-Architekturen. Er trägt maßgeblich zur Übersichtlichkeit von Applikationsdiagrammen bei, indem er die Signal- und Eventflüsse für mathematische Divisionen in standardisierten Adaptern konsolidiert.
