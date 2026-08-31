# AS_MUL_3_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AS_MUL_3`](AS_MUL_3.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![AS_MUL_3_UNGATED](./AS_MUL_3_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AS_MUL_3_UNGATED` ist ein generischer Funktionsblock (Generic FB) für die 4diac-IDE, der zur Durchführung einer arithmetischen Multiplikation mit drei Eingangswerten dient. Er basiert auf der Verwendung von unidirektionalen Adaptern (`adapter::types::unidirectional::AS`), was eine saubere Strukturierung und Kapselung von Daten und Kontrollflüssen in IEC 61499-Anwendungen ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung und Ereignisverarbeitung erfolgt implizit über die Adapter-Schnittstellen.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt implizit über die Adapter-Schnittstellen.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge. Die Datenübergabe erfolgt über die Sockets der Adapter-Schnittstellen.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt über den Plug der Adapter-Schnittstelle.*

### **Adapter**

Die gesamte Kommunikation des Bausteins wird über Adapter abgewickelt:

- **Sockets (Eingangs-Adapter):**
  - **IN1** (Typ: `adapter::types::unidirectional::AS`): Der erste Eingangswert (Multiplikand 1) für die Multiplikation.
  - **IN2** (Typ: `adapter::types::unidirectional::AS`): Der zweite Eingangswert (Multiplikand 2) für die Multiplikation.
  - **IN3** (Typ: `adapter::types::unidirectional::AS`): Der dritte Eingangswert (Multiplikand 3) für die Multiplikation.

- **Plugs (Ausgangs-Adapter):**
  - **OUT** (Typ: `adapter::types::unidirectional::AS`): Der Ausgangs-Adapter, der das Ergebnis der Multiplikation bereitstellt.

---

## Funktionsweise

Der Funktionsbaustein `AS_MUL_3_UNGATED` multipliziert die über die Eingangs-Adapter `IN1`, `IN2` und `IN3` empfangenen Werte miteinander. Sobald sich Werte an den Eingängen ändern oder ein entsprechendes Trigger-Ereignis über die Adapter eingeht, wird die Berechnung ausgeführt und das Ergebnis an den Ausgangs-Adapter `OUT` übergeben.

Die mathematische Formel lautet:
$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3}$$

---

## Technische Besonderheiten

- **Generischer Typ:** Der Baustein ist als generischer Typ (`GEN_AS_MUL`) definiert. Dies ermöglicht eine flexible Anpassung an unterschiedliche numerische Datentypen (z. B. `INT`, `REAL`, `LREAL`), die vom zugrundeliegenden Adaptertyp unterstützt werden.
- **Adapter-basierte Architektur:** Durch die Nutzung von unidirektionalen Adaptern (`AS`) wird der Verkabelungsaufwand in der 4diac-IDE drastisch reduziert, da Ereignis- und Datenleitungen in einer einzigen Verbindung gebündelt sind.

---

## Zustandsübersicht

Der Baustein verhält sich wie ein klassischer zustandsloser Berechnungsbaustein. Die Ausführung wird durch eingehende Ereignisse auf den Sockets (`IN1`, `IN2`, `IN3`) getriggert. Nach erfolgreicher Berechnung des Produkts wird das Ausgangsereignis direkt über den Plug `OUT` zusammen mit dem berechneten Wert emittiert.

---

## Anwendungsszenarien

- **Sensorskalierung und Kalibrierung:** Berechnung von korrigierten Messwerten, bei denen ein Rohwert mit zwei verschiedenen Korrekturfaktoren multipliziert werden muss.
- **Volumenberechnungen:** Multiplikation von drei Dimensionen (Länge × Breite × Höhe) zur Bestimmung eines Volumens in der Prozesstechnik.
- **Mehrstufige Verstärkungsregelung:** Kaskadierte Signalverstärkung in der Regelungstechnik.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu Standard-Multiplikationsbausteinen (wie `MUL`), die mit separaten Event- und Datenleitungen (z. B. `REQ`/`CNF` und Standard-Datentypen) arbeiten, bietet `AS_MUL_3_UNGATED` durch die Kapselung in Adaptern eine deutlich aufgeräumtere visuelle Darstellung im Application Editor der 4diac-IDE. Es entfällt das manuelle Verknüpfen von "With"-Verbindungen zwischen Ereignissen und Daten.

---

- **[`AS_MUL_3`](AS_MUL_3.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

`AS_MUL_3_UNGATED` ist ein effizienter, modularer und wiederverwendbarer Funktionsbaustein für arithmetische Dreifach-Multiplikationen. Er eignet sich hervorragend für moderne, adapter-basierte Softwarearchitekturen innerhalb der IEC 61499 und trägt zur Übersichtlichkeit komplexer Steuerungsanwendungen bei.
