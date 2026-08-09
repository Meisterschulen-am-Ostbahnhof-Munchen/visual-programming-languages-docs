# AI_AX_SEL_AI


![AI_AX_SEL_AI](./AI_AX_SEL_AI.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AI_AX_SEL_AI` ist ein binärer Selektor (Multiplexer) für analoge Signale, der auf der IEC 61499-Architektur basiert. Er dient dazu, basierend auf einem Steuersignal (Selektor) eines von zwei analogen Eingangssignalen auszuwählen und an den Ausgang weiterzuleiten. Die Besonderheit dieses Bausteins liegt in der konsequenten Nutzung von Adaptern, was die Verkabelung innerhalb der Entwicklungsumgebung 4diac-ide erheblich vereinfacht und strukturiert.

## Schnittstellenstruktur

Der Funktionsbaustein besitzt keine klassischen diskreten Ein- und Ausgänge für Daten und Ereignisse auf seiner Hauptebene. Stattdessen ist die gesamte Kommunikation über standardisierte Adapter realisiert.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (vollständig über Adapter gekapselt).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (vollständig über Adapter gekapselt).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden (vollständig über Adapter gekapselt).*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden (vollständig über Adapter gekapselt).*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

* **G** (Typ: `adapter::types::unidirectional::AX`): Der Selektor-Eingang. Dieser Adapter liefert das Steuersignal (boolescher Zustand), das bestimmt, welcher der beiden analogen Eingänge auf den Ausgang geschaltet wird.
* **IN0** (Typ: `adapter::types::unidirectional::AI`): Der auswählbare Analogeingang 0. Dieser Wert wird durchgeschaltet, wenn das Selektorsignal `G` den Zustand `FALSE` (0) aufweist.
* **IN1** (Typ: `adapter::types::unidirectional::AI`): Der auswählbare Analogeingang 1. Dieser Wert wird durchgeschaltet, wenn das Selektorsignal `G` den Zustand `TRUE` (1) aufweist.

#### **Plugs (Ausgangs-Schnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::AI`): Der ausgewählte Analogausgang. Er gibt das Signal des jeweils aktiven Eingangs (`IN0` oder `IN1`) aus.

---

## Funktionsweise

Die interne Logik des Bausteins steuert den Daten- und Ereignisfluss wie folgt:

1. **Ereignissteuerung & Datenerfassung:**
   * Jedes Mal, wenn an einem der Eingangs-Adapter (`IN0`, `IN1` oder `G`) ein Ereignis (`E1`) eintrifft, wird das zugehörige Datenelement (`D1`) über interne flanken- bzw. ereignisgesteuerte Speicherbausteine (`E_D_FF` und `E_D_FF_ANY`) zwischengespeichert.
   * Interne `F_MOVE`-Bausteine konvertieren und übergeben die Werte (als Datentyp `INT`) an den zentralen Auswahlbaustein.

2. **Auswahllogik (Selection):**
   * Der Kernbaustein `F_SEL` (ein standardisierter IEC 61131-3 Auswahl-Funktionsbaustein) wertet das Steuersignal `G` aus.
   * Ist das Steuersignal `G` auf `FALSE`, wird der Wert von `IN0` gewählt.
   * Ist das Steuersignal `G` auf `TRUE`, wird der Wert von `IN1` gewählt.

3. **Ausgabe:**
   * Nach erfolgreicher Auswahl wird der ausgewählte Wert über einen weiteren `F_MOVE`-Baustein und ein Ausgangs-Flip-Flop (`E_D_FF_ANY_OUT`) an den Ausgangs-Plug `OUT` übergeben.
   * Gleichzeitig wird das Ausgangsereignis `OUT.E1` ausgelöst, um nachfolgende Bausteine über die Wertänderung zu informieren.

---

## Technische Besonderheiten

* **Datentyp-Spezifizierung:** Intern arbeitet der Baustein mit dem Datentyp `INT` (Ganzzahl) für die analogen Werte, was durch die Parametrierung der internen `F_MOVE`-Instanzen festgelegt ist.
* **Adapterbasierte Architektur:** Durch die Kapselung von Ereignis und Daten in den Adaptern `AI` (Analog Input) und `AX` (Auxiliary Control) wird die Anzahl der Verbindungsleitungen im übergeordneten Systemdiagramm drastisch reduziert.
* **Event-Driven Propagation:** Jede Aktualisierung eines Eingangs (unabhängig davon, ob es sich um die Daten oder den Selektor handelt) stößt die Neuberechnung und die Ausgabe eines Ereignisses am Ausgang an.

---

## Zustandsübersicht

Der Baustein verhält sich rein ereignis- und datenflussgesteuert. Es gibt keine komplexen internen Zustände (keine Zustandsmaschine / ECC im klassischen Sinne), sondern eine direkte Abhängigkeit des Ausgangs von den Eingängen:

| Selektor-Eingang (`G.D1`) | Aktiver Pfad | Ausgangswert (`OUT.D1`) | Ausgangsereignis (`OUT.E1`) |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | Wert von `IN0.D1` | Wird bei jedem Trigger ausgelöst |
| `TRUE` | `IN1` | Wert von `IN1.D1` | Wird bei jedem Trigger ausgelöst |

---

## Anwendungsszenarien

* **Redundante Sensorik:** Umschalten zwischen einem primären und einem sekundären (Backup-) Analogsensor bei einem detektierten Ausfall.
* **Hand-/Automatik-Umschaltung:** Auswahl zwischen einem manuell vorgegebenen Sollwert (z.B. über ein HMI an `IN0`) und einem automatisiert berechneten Regler-Sollwert (an `IN1`).
* **Rezepturgesteuerte Signalumleitung:** Dynamische Zuweisung von analogen Prozessparametern basierend auf dem aktuellen Betriebszustand einer Anlage.

---

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL` (IEC 61131-3):** Der klassische `F_SEL`-Baustein benötigt diskrete Pins für Ereignisse und Daten. `AI_AX_SEL_AI` kapselt diese Funktionalität in anwendungsfreundliche Adapterstrukturen, was die Wiederverwendbarkeit und Übersichtlichkeit in komplexen IEC 61499-Anwendungen erhöht.
* **Klassische Multiplexer (z.B. MUX):** Während ein Multiplexer oft mehrere Kanäle (z.B. 4 oder 8) bedient, ist dieser Baustein als schlanker, hocheffizienter 2-Wege-Auswahlschalter für dedizierte Analogsignale optimiert.

---

## Fazit

Der `AI_AX_SEL_AI`-Baustein stellt eine elegante, adapterbasierte Lösung für die binäre Auswahl von Analogsignalen in verteilten Steuerungssystemen dar. Durch die saubere Trennung und Kapselung der Schnittstellen in standardisierte Adapter eignet er sich hervorragend für den Einsatz in modularen und serviceorientierten Automatisierungsarchitekturen innerhalb von Eclipse 4diac.