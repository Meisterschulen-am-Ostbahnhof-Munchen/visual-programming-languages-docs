# SINT_AS_AX_SEL_AS


![SINT_AS_AX_SEL_AS](./SINT_AS_AX_SEL_AS.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `SINT_AS_AX_SEL_AS` ist ein binärer Selektor (Multiplexer) für vorzeichenbehaftete 8-Bit-Ganzzahlen (`SINT`). Er dient dazu, basierend auf einem Auswahlsignal (`G`) zwischen zwei Eingangswerten (`IN0` und `IN1`) zu wählen und den ausgewählten Wert an den Ausgang (`OUT`) weiterzuleiten. Der Baustein nutzt eine Kombination aus klassischen Schnittstellen und modernen Adapter-Schnittstellen, um eine modulare und übersichtliche Verdrahtung innerhalb von 4diac-Applikationen zu ermöglichen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Löst die Übernahme und Verarbeitung des Daten-Eingangs `IN0` aus.

### **Ereignis-Ausgänge**

* *Keine direkten Ereignis-Ausgänge auf Blockebene.* Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.

### **Daten-Eingänge**

* **IN0** (`SINT`): Der erste auswählbare Eingangswert (Standard-SINT-Variable).

### **Daten-Ausgänge**

* *Keine direkten Daten-Ausgänge auf Blockebene.* Die Datenausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.

### **Adapter**

* **OUT** (Plug, Typ: `adapter::types::unidirectional::AS`): Der ausgewählte Ausgangskanal, über den der selektierte `SINT`-Wert und das zugehörige Ereignis ausgegeben werden.
* **IN1** (Socket, Typ: `adapter::types::unidirectional::AS`): Der zweite auswählbare Eingangskanal, der als Adapter ausgeführt ist.
* **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Eingang zur Auswahl des aktiven Kanals (Adapter für das Auswahlsignal).

---

## Funktionsweise

Der Baustein arbeitet intern als ereignisgesteuertes Netzwerk, das die Eingangswerte puffert und über ein Standard-Auswahlglied leitet:

1. **Eingangspufferung**: 
   * Ein Ereignis an `EI0` speichert den Wert von `IN0` in einem internen Flip-Flop (`E_D_FF_ANY_IN0`).
   * Ein Ereignis am Adapter-Eingang `IN1` (`IN1.E1`) speichert den Wert `IN1.D1` im Flip-Flop `E_D_FF_ANY_IN1`.
   * Eine Änderung am Selektor-Adapter `G` (`G.E1`) speichert den Zustand `G.D1` im Flip-Flop `E_D_FF_G`.

2. **Auswahl-Logik (`F_SEL`)**:
   Sobald sich einer der Eingänge oder das Auswahlsignal ändert, wird die Selektion im internen Baustein `F_SEL` getriggert:
   * Ist das Auswahlsignal (`G`) **FALSE** (0), wird der Wert von **IN0** an den Ausgang durchgeschaltet.
   * Ist das Auswahlsignal (`G`) **TRUE** (1), wird der Wert von **IN1** an den Ausgang durchgeschaltet.

3. **Ausgabe**:
   Der ausgewählte Wert wird über ein internes `F_MOVE`-Glied an den Ausgangs-Adapter `OUT` übertragen. Gleichzeitig wird das Ausgangsereignis `OUT.E1` generiert, um nachfolgende Bausteine über die Wertänderung zu informieren.

---

## Technische Besonderheiten

* **Hybride Schnittstellen**: Der Baustein kombiniert klassische IEC 61499-Variablen (`IN0`, `EI0`) mit Adapter-Schnittstellen (`IN1`, `G`, `OUT`). Dies ermöglicht eine flexible Integration in bestehende Systeme.
* **Asynchrone Ereignisverarbeitung**: Jede Änderung an einem der Eingänge (sei es `IN0`, `IN1` oder der Selektor `G`) führt sofort zu einer Neubewertung und ggf. Aktualisierung des Ausgangs.
* **Datentyp-Spezifisch**: Optimiert für den Datentyp `SINT` (Short Integer, 8-Bit), was für eine effiziente Speichernutzung bei kleineren Zahlenbereichen sorgt.

---

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) handelt, wird das Verhalten durch den internen Signalfluss bestimmt:

| Trigger-Ereignis | Zustand Selektor `G` | Gewählter Ausgang (`OUT.D1`) | Generiertes Ereignis |
| :--- | :--- | :--- | :--- |
| `EI0` | `FALSE` | Wert von `IN0` | `OUT.E1` |
| `EI0` | `TRUE` | Wert von `IN1.D1` (unverändert) | `OUT.E1` |
| `IN1.E1` | `FALSE` | Wert von `IN0` (unverändert) | `OUT.E1` |
| `IN1.E1` | `TRUE` | Wert von `IN1.D1` | `OUT.E1` |
| `G.E1` (Wechsel auf `FALSE`) | `FALSE` | Wert von `IN0` | `OUT.E1` |
| `G.E1` (Wechsel auf `TRUE`) | `TRUE` | Wert von `IN1.D1` | `OUT.E1` |

---

## Anwendungsszenarien

* **Umschaltung zwischen Betriebsmodi**: Wahlweise Vorgabe eines manuellen Festwerts (`IN0`) oder eines dynamisch über einen Adapter empfangenen Automatikwerts (`IN1`).
* **Signal-Routing**: Dynamische Weiterleitung von Sensor- oder Steuerungsdaten in modularen Anlagenstrukturen.
* **Kompakte Programmierung**: Reduzierung von Linienkreuzungen im FB-Netzwerk durch die Verwendung von Adaptern für Signale und Werte.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet `SINT_AS_AX_SEL_AS` eine integrierte Ereignissteuerung. Während ein Standard-`F_SEL` rein datenflussorientiert arbeitet und externe Trigger benötigt, regelt dieser Baustein die Event-Generierung und Wertespeicherung (Latching) über interne D-Flip-Flops selbstständig. Zudem spart die Verwendung von Adaptern gegenüber klassischen Multiplexern signifikant Verdrahtungsaufwand im grafischen Editor.

---

## Fazit

`SINT_AS_AX_SEL_AS` ist ein spezialisierter, aber hocheffizienter Baustein für die Signalsteuerung im 8-Bit-Bereich. Durch die Kapselung der Event-Logik und die Nutzung von Adaptern trägt er maßgeblich zur Übersichtlichkeit und Wartbarkeit von komplexen IEC 61499 Steuerungsanwendungen bei.