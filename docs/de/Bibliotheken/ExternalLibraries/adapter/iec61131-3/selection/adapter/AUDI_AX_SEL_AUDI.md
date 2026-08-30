# AUDI_AX_SEL_AUDI


![AUDI_AX_SEL_AUDI](./AUDI_AX_SEL_AUDI.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUDI_AX_SEL_AUDI` dient als binärer Selektor (Auswahlschalter) für unidirektionale Kommunikationsadapter. Er ermöglicht es, basierend auf dem Zustand eines Steuersignals an einem Selektor-Adapter, den Daten- und Ereignisstrom zwischen zwei alternativen Eingangs-Adaptern auf einen einzigen Ausgangs-Adapter umzuleiten.

Der Baustein kapselt die dafür notwendige Synchronisations- und Konvertierungslogik, um eine saubere Trennung von Ereignissen und Datenflüssen innerhalb von IEC 61499 Anwendungen zu gewährleisten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge auf der Bausteinoberfläche definiert. Die Ereignisverarbeitung erfolgt vollständig gekapselt über die angeschlossenen Adapter.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge auf der Bausteinoberfläche definiert. Die Ereignisweiterleitung erfolgt vollständig über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Anschlüsse)**

- **IN0** (Typ: `adapter::types::unidirectional::AUDI`):
  Erster auswählbarer Eingangs-Adapter. Die dort ankommenden Daten und Ereignisse werden an den Ausgang durchgereicht, wenn das Auswahlsignal `G` den logischen Zustand `FALSE` (bzw. `0`) besitzt.
- **IN1** (Typ: `adapter::types::unidirectional::AUDI`):
  Zweiter auswählbarer Eingangs-Adapter. Die dort ankommenden Daten und Ereignisse werden an den Ausgang durchgereicht, wenn das Auswahlsignal `G` den logischen Zustand `TRUE` (bzw. `1`) besitzt.
- **G** (Typ: `adapter::types::unidirectional::AX`):
  Selektor-Adapter. Das Signal auf diesem Adapter bestimmt, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang geschaltet wird.

#### **Plugs (Ausgangs-Anschlüsse)**

- **OUT** (Typ: `adapter::types::unidirectional::AUDI`):
  Ausgangs-Adapter. Gibt die Daten und das dazugehörige Triggerereignis des aktuell ausgewählten Eingangs aus.

---

## Funktionsweise

Das interne Verhalten des Bausteins wird durch ein Netzwerk aus Standard-Funktionsbausteinen realisiert:

1. **Ereignis- und Datensynchronisation**:
   Die über die Sockets eingehenden Signale (`IN0`, `IN1`, `G`) werden zunächst über flanken- bzw. pegelgesteuerte D-Flip-Flops (`E_D_FF` und `E_D_FF_ANY`) geführt. Dies stellt sicher, dass Datenwerte (`D1`) und Ereignisse (`E1`) synchron zueinander verarbeitet werden.
2. **Datenkonvertierung**:
   Die synchronisierten Datenwerte der beiden Eingänge werden über zwei Transfer-Bausteine (`F_MOVE` mit dem Datentyp `UDINT`) an den Auswahlbaustein übergeben.
3. **Auswahlsteuerung**:
   Der Baustein `F_SEL` (IEC 61131-3 Selection) führt die eigentliche logische Umschaltung durch:
   - Ist das Steuersignal des Adapters `G` auf `0` (`FALSE`), wird der Wert von `IN0` gewählt.
   - Ist das Steuersignal des Adapters `G` auf `1` (`TRUE`), wird der Wert von `IN1` gewählt.
4. **Ausgabe**:
   Das selektierte Ergebnis wird über einen weiteren Transfer-Baustein (`F_MOVE_OUT`) an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übertragen. Dieses generiert das Ausgangsereignis `OUT.E1` und stellt den selektierten Datenwert an `OUT.D1` bereit.

---

## Technische Besonderheiten

- **UDINT-Datenverarbeitung**: Obwohl die Adapter vom generischen Typ `AUDI` sind, werden die Nutzdaten (`D1`) intern explizit als `UDINT` (Unsigned Double Integer / 32-Bit Ganzzahl) verarbeitet und übertragen.
- **Ereignisgesteuertes Verhalten**: Jede Änderung an den Eingängen oder am Selektor führt über das interne Koppelnetzwerk zu einer Neuberechnung und triggert das Ausgangsereignis des Adapters `OUT`.
- **Kapselung**: Durch die Verwendung von Adaptern statt loser Event- und Daten-Ports wird der Verdrahtungsaufwand im übergeordneten Systemdiagramm extrem minimiert.

---

## Zustandsübersicht

Da der Baustein als FB-Netzwerk aufgebaut ist, besitzt er keine klassische Zustandsmaschine (ECC). Das logische Verhalten lässt sich stattdessen über folgende Funktionstabelle beschreiben:

| Zustand Selektor (`G.D1`) | Triggerndes Ereignis | Aktiver Datenpfad | Wert am Ausgang (`OUT.D1`) | Ereignis am Ausgang (`OUT.E1`) |
| :--- | :--- | :--- | :--- | :--- |
| `FALSE` | Event an `IN0.E1` oder `G.E1` | `IN0` -> `OUT` | Entspricht `IN0.D1` | Wird ausgelöst |
| `TRUE` | Event an `IN1.E1` oder `G.E1` | `IN1` -> `OUT` | Entspricht `IN1.D1` | Wird ausgelöst |

---

## Anwendungsszenarien

- **Sollwert-Umschaltung**: Wechsel zwischen einem Automatik-Sollwert (z.B. von einem PID-Regler an `IN1`) und einem Hand-Sollwert (z.B. von einer Visualisierung an `IN0`) über ein Auswahlsignal an `G`.
- **Sensor-Redundanz**: Ausfallsichere Umschaltung zwischen einem Hauptsensor und einem Ersatzsensor bei Signalstörungen.
- **Rezeptursteuerung**: Auswahl unterschiedlicher vordefinierter Parameter-Profile im laufenden Betrieb.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet `AUDI_AX_SEL_AUDI` den Vorteil, dass er direkt mit strukturierten, unidirektionalen Adaptern (`AUDI` und `AX`) interagieren kann. Bei der Verwendung des Standard-`F_SEL`-Bausteins müssten alle Event- und Datenleitungen der Adapter manuell aufgesplittet, einzeln verschaltet und anschließend wieder zusammengeführt werden, was fehleranfällig ist und das Anwendungsdiagramm unübersichtlich macht.

---

## Fazit

Der Baustein `AUDI_AX_SEL_AUDI` bietet eine elegante, saubere und wiederverwendbare Lösung für die Signalumschaltung in 4diac-basierten Steuerungsarchitekturen. Durch die konsequente Nutzung von Adaptern trägt er maßgeblich zur Modularität und Übersichtlichkeit komplexer Steuerungsprogramme bei.
