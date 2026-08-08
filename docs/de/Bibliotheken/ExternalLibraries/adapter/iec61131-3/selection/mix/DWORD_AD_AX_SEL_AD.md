# DWORD_AD_AX_SEL_AD


![DWORD_AD_AX_SEL_AD](./DWORD_AD_AX_SEL_AD.svg)

*Kein Bild vorhanden*

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `DWORD_AD_AX_SEL_AD` ist ein zusammengesetzter (Composite) Funktionsbaustein für die ereignisgesteuerte binäre Auswahl (Selektion) von zwei Signalquellen des Datentyps `DWORD`. Er dient als Multiplexer, der basierend auf dem Zustand eines Selektionssignals `G` (bereitgestellt über einen Adapter vom Typ `AX`) entweder den direkten Dateneingang `IN0` oder den über einen Adapter (`AD`) bereitgestellten Eingang `IN1` auf den Ausgangsadapter `OUT` schaltet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
* **EI0**: Löst die Übernahme und Speicherung des direkt anliegenden Datenwerts `IN0` aus.

### **Ereignis-Ausgänge**
* *Keine direkten Ereignis-Ausgänge.* (Die Ereignisweiterleitung erfolgt gekoppelt über den Ausgangsadapter `OUT`).

### **Daten-Eingänge**
* **IN0** (DWORD): Direkt anliegende, auswählbare Eingangsvariable.

### **Daten-Ausgänge**
* *Keine direkten Daten-Ausgänge.* (Die Datenweiterleitung erfolgt gekoppelt über den Ausgangsadapter `OUT`).

### **Adapter**
* **OUT** (Plug, Typ: `adapter::types::unidirectional::AD`): Der Ausgangsadapter, der den ausgewählten `DWORD`-Wert (`D1`) zusammen mit dem zugehörigen Aktualisierungsereignis (`E1`) ausgibt.
* **IN1** (Socket, Typ: `adapter::types::unidirectional::AD`): Der Eingangsadapter für die alternative `DWORD`-Auswahlvariable. Liefert das Datum (`D1`) und das Aktualisierungsereignis (`E1`).
* **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter. Das binäre Signal (`D1`) steuert die Auswahl, das Ereignis (`E1`) triggert die Aktualisierung des Selektionszustands.

---

## Funktionsweise
Im Inneren des Funktionsbausteins arbeiten mehrere standardisierte Unter-Bausteine zusammen, um die Daten ereignisgesteuert zu verarbeiten und weiterzuleiten:

1. **Datenspeicherung (Latch-Mechanismus):**
   * Jedes Mal, wenn ein Ereignis an einem der Eingänge (`EI0`, `G.E1`, `IN1.E1`) registriert wird, speichert ein interner Flip-Flop-Baustein (`E_D_FF` bzw. `E_D_FF_ANY`) den aktuellen Wert des zugehörigen Datenpunkts zwischen.
   * Der Wert von `IN0` wird bei `EI0` im Baustein `E_D_FF_ANY_IN0` gespeichert.
   * Der Wert von `IN1.D1` wird bei `IN1.E1` im Baustein `E_D_FF_ANY_IN1` gespeichert.
   * Das Auswahlsignal `G.D1` wird bei `G.E1` im Baustein `E_D_FF_G` gespeichert.

2. **Wertübertragung (Move):**
   * Die zwischengespeicherten Eingangswerte werden über `F_MOVE_IN0` und `F_MOVE_IN1` an den zentralen Selektionsbaustein weitergeleitet.

3. **Auswahl (Selection):**
   * Der Baustein `F_SEL` (IEC 61131-3 Standard Selection) entscheidet anhand des Zustands von `G`:
     * Ist **`G` = FALSE**, wird der Wert von **`IN0`** an den Ausgang durchgereicht.
     * Ist **`G` = TRUE**, wird der Wert von **`IN1`** an den Ausgang durchgereicht.

4. **Ausgabe-Synchronisation:**
   * Nach erfolgter Auswahl wird der Wert über `F_MOVE_OUT` an den Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übergeben.
   * Dieser gibt den ausgewählten Wert schließlich an `OUT.D1` aus und triggert das Ereignis `OUT.E1`.

---

## Technische Besonderheiten
* **Vollständige Ereignisentkopplung:** Durch die Verwendung von Event-Flip-Flops (`E_D_FF`) an allen Eingängen wird sichergestellt, dass Daten nur bei einer expliziten Ereignisflanke verarbeitet werden. Dies verhindert inkonsistente Zustände oder unnötige Rechenzyklen bei rein statischen Signaländerungen.
* **Adapterbasierte Architektur:** Die Verwendung von standardisierten unidirektionalen Adaptern (`AD` und `AX`) minimiert den Verdrahtungsaufwand im übergeordneten System und erhöht die Modularität im 4diac-Netzwerk.

---

## Zustandsübersicht

| Zustand Selektor (`G`) | Triggerndes Ereignis | Aktiver Eingang | Ausgangswert (`OUT.D1`) | Ausgangsereignis (`OUT.E1`) |
| :--- | :--- | :--- | :--- | :--- |
| **FALSE** | `EI0` oder `G.E1` | `IN0` (Direkt) | Wert von `IN0` | Wird ausgelöst |
| **TRUE** | `IN1.E1` oder `G.E1` | `IN1` (Adapter) | Wert von `IN1` | Wird ausgelöst |

---

## Anwendungsszenarien
* **Umschaltung zwischen Hand- und Automatikwerten:** Direkte Vorgabe eines Parameters über eine HMI (`IN0` über `EI0`) oder Übernahme eines automatisch berechneten Werts aus einem anderen Programmteil (`IN1` über Adapter).
* **Sensor-Redundanz/Fallback-Systeme:** Umschalten zwischen einem primären Sensor-Wert und einem Standardwert/Ersatzwert bei Signalverlust oder Fehlerzuständen.
* **Dynamische Parametersteuerung:** Flexible Zuweisung von Konfigurations- oder Schwellwerten in komplexen Steuerungsnetzwerken.

---

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zum standardmäßigen IEC 61131-3 `F_SEL` Baustein bietet `DWORD_AD_AX_SEL_AD` folgende Vorteile:
* **Ereignissteuerung:** Der Standard-`F_SEL` arbeitet rein datenflussorientiert. Dieser Baustein integriert die ereignisbasierte Ausführung von IEC 61499.
* **Schnittstellen-Kapselung:** Er kombiniert Daten- und Ereignisleitungen in Adaptern, wodurch Signalbus-Strukturen sauberer modelliert werden können, anstatt eine Vielzahl einzelner Event- und Data-Verbindungen ziehen zu müssen.

---

## Fazit
Der `DWORD_AD_AX_SEL_AD` ist ein robuster, wiederverwendbarer Selektionsbaustein für verteilte Steuerungssysteme. Er eignet sich hervorragend für Applikationen, bei denen `DWORD`-Datenströme ereignisgesteuert und modular umgeschaltet werden müssen.