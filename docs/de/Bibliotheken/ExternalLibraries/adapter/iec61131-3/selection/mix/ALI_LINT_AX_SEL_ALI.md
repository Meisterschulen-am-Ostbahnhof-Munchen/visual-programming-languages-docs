# ALI_LINT_AX_SEL_ALI


![ALI_LINT_AX_SEL_ALI](./ALI_LINT_AX_SEL_ALI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein `ALI_LINT_AX_SEL_ALI` dient der binären Auswahl (Selektion) zwischen zwei Eingangswerten vom Typ `LINT` (Large Integer). Die Steuerung, welcher der beiden Werte an den Ausgang durchgeschaltet wird, erfolgt über einen binären Selektor. Der Baustein kombiniert die klassische Auswahllogik der IEC 61131-3 mit der ereignisgesteuerten Architektur der IEC 61499 unter Verwendung von anwendungsspezifischen Adaptern zur Signalübertragung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
* **EI1**: Löst die Übernahme des Daten-Eingangswerts `IN1` aus.

### **Ereignis-Ausgänge**
* *Keine direkten Ereignis-Ausgänge auf Bausteinebene vorhanden.* Die Ereignisweiterleitung erfolgt gekapselt über die Adapter-Schnittstellen (z. B. `OUT.E1`).

### **Daten-Eingänge**
* **IN1** (LINT): Selektierbarer Eingangswert 1 (Alternative 1).

### **Daten-Ausgänge**
* *Keine direkten Daten-Ausgänge auf Bausteinebene vorhanden.* Die Datenausgabe erfolgt gekapselt über den Ausgangs-Adapter.

### **Adapter**
* **OUT** (Plug, Typ: `adapter::types::unidirectional::ALI`): Der ausgewählte Ausgangswert (Selected Output).
* **IN0** (Socket, Typ: `adapter::types::unidirectional::ALI`): Selektierbarer Eingangswert 0 (Alternative 0).
* **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Binärer Selektor (Gate), der bestimmt, welcher der beiden Eingänge (`IN0` oder `IN1`) zum Ausgang durchgeschaltet wird.

---

## Funktionsweise
Der Baustein arbeitet intern als ereignisgesteuerter Multiplexer:

1. **Signalspeicherung (Latching):** Sobald an den Eingängen (`IN0`, `IN1` oder `G`) Ereignisse eintreffen, werden die anliegenden Datenwerte über interne D-Flip-Flops (`E_D_FF` und `E_D_FF_ANY`) zwischengespeichert. Dies stellt sicher, dass die Daten konsistent bleiben und nur bei aktiven Events aktualisiert werden.
2. **Datenkopierung:** Die zwischengespeicherten Werte werden über `F_MOVE`-Bausteine an den zentralen Auswahlbaustein übergeben.
3. **Auswahllogik (F_SEL):** Der interne Standardbaustein `F_SEL` wertet den Zustand des Selektors `G` aus:
   - Ist der Selektor `G` **FALSE** (0), wird der Wert von `IN0` gewählt.
   - Ist der Selektor `G` **TRUE** (1), wird der Wert von `IN1` gewählt.
4. **Ausgabe:** Der ausgewählte Wert wird an das Datenfeld des `OUT`-Adapters übergeben und gleichzeitig das dazugehörige Ereignis (`OUT.E1`) getriggert.

---

## Technische Besonderheiten
* **Einsatz von Adaptern:** Durch die Verwendung von Sockets und Plugs wird die Anzahl der notwendigen Verbindungen im übergeordneten Systemdiagramm stark reduziert.
* **Datentypspezifisch:** Der Baustein ist speziell für den Datentyp `LINT` (64-Bit Ganzzahl) optimiert.
* **Flanken- und Event-Synchronisation:** Die interne Logik stellt sicher, dass jede Änderung an den Eingängen deterministisch verarbeitet wird und nur gültige Zustandsänderungen ein Event am Ausgang `OUT` hervorrufen.

---

## Zustandsübersicht

| Ereignis-Trigger | Zustand des Selektors (`G`) | Resultierender Ausgangswert (`OUT.D1`) | Ausgelöstes Ausgangs-Event |
| :--- | :--- | :--- | :--- |
| Event an `IN0.E1` | `FALSE` (0) | Wert von `IN0.D1` | `OUT.E1` |
| Event an `IN0.E1` | `TRUE` (1) | *Keine Änderung (alter Wert bleibt)* | *Kein Event* |
| Event `EI1` | `TRUE` (1) | Wert von `IN1` | `OUT.E1` |
| Event `EI1` | `FALSE` (0) | *Keine Änderung (alter Wert bleibt)* | *Kein Event* |
| Event an `G.E1` (Wechsel auf 0) | `FALSE` (0) | Wert von `IN0.D1` | `OUT.E1` |
| Event an `G.E1` (Wechsel auf 1) | `TRUE` (1) | Wert von `IN1` | `OUT.E1` |

---

## Anwendungsszenarien
* **Umschaltung von Signalquellen:** Dynamische Auswahl zwischen einem Standard-Sensormesswert (über `IN0` als Adapter) und einem manuell vorgegebenen Substitutionswert oder Parameter (über `IN1` als Direkteingang).
* **Betriebsartenwahl:** Umschalten von Sollwerten (z. B. Rezepturnummern, Zählergrenzen) im `LINT`-Format basierend auf dem aktuellen Anlagenstatus (Automatik-/Handbetrieb über Selektor `G`).

---

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem einfachen IEC 61131-3 `F_SEL`-Baustein bietet der `ALI_LINT_AX_SEL_ALI`:
* Eine vollständige Integration in die ereignisgesteuerte IEC 61499-Umgebung.
* Reduzierten Verdrahtungsaufwand durch die Kapselung von Events und Daten in den Adaptern `ALI` und `AX`.
* Automatische Datenpufferung, die verhindert, dass transiente Signaländerungen ohne Event-Trigger fälschlicherweise verarbeitet werden.

---

## Fazit
Der Baustein `ALI_LINT_AX_SEL_ALI` ist eine spezialisierte und performante Lösung für die bedingte Signalweiterleitung von 64-Bit-Ganzzahlwerten. Durch seine adapterbasierte Schnittstelle fördert er ein sauberes, modulares und gut lesbares Applikationsdesign in 4diac-IDE.