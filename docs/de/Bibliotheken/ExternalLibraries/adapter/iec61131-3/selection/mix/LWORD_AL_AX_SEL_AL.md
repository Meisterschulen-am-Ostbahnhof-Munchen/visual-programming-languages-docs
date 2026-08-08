# LWORD_AL_AX_SEL_AL


![LWORD_AL_AX_SEL_AL](./LWORD_AL_AX_SEL_AL.svg)

*Kein Bild verfügbar*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `LWORD_AL_AX_SEL_AL` dient der binären Auswahl (Multiplexing) von Daten des Typs `LWORD` (64-Bit-Ganzzahl ohne Vorzeichen). Er ermöglicht es, basierend auf dem Zustand eines Auswahlsignals (Selector) zwischen einem direkt anliegenden Datenwert und einem über eine Adapterschnittstelle bereitgestellten Datenwert zu wählen. Das Ergebnis wird anschließend über einen Ausgangs-Adapter zur Verfügung gestellt. Der Baustein kombiniert dabei klassische Variablen-Schnittstellen mit moderner, adapterbasierter Kommunikation für ereignisgesteuerte 4diac-Systeme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Setzt den Wert der Eingangsvariablen `IN0`. Bei Eintreffen dieses Ereignisses wird der Wert an `IN0` eingelesen und verarbeitet.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge.* (Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`).

### **Daten-Eingänge**

*   **IN0** (LWORD): Eine direkt am Baustein anliegende, auswählbare `LWORD`-Eingangsvariable.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge.* (Die Datenausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`).

### **Adapter**

*   **IN1** (Socket, Typ: `adapter::types::unidirectional::AL`): Ein unidirektionaler Eingangs-Adapter, der einen auswählbaren `LWORD`-Wert (`D1`) und das dazugehörige Aktualisierungsereignis (`E1`) liefert.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter. Er liefert das Steuersignal (`D1` als Boolean) und ein Trigger-Ereignis (`E1`). Er bestimmt, welcher der Eingänge auf den Ausgang geschaltet wird.
*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AL`): Der Ausgangs-Adapter, der den ausgewählten `LWORD`-Wert (`D1`) zusammen mit einem Bestätigungsereignis (`E1`) ausgibt.

---

## Funktionsweise

Die interne Logik des Bausteins basiert auf dem klassischen IEC 61131-3 `SEL`-Auswahlprinzip, das um ereignisgesteuerte Speicherstufen erweitert wurde. 

1.  **Zwischenspeicherung (Latching):**
    Sobald an einem der Eingänge ein Ereignis eintrifft (`EI0` für `IN0`, `IN1.E1` für `IN1` oder `G.E1` für das Auswahlsignal `G`), wird der entsprechende Datenwert in einem internen Flip-Flop (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert. Dies stellt sicher, dass auch asynchron eintreffende Datenänderungen konsistent verarbeitet werden.
2.  **Wertübernahme:**
    Die zwischengespeicherten Daten für `IN0` und `IN1` werden über Kopier-Funktionsbausteine (`F_MOVE_IN0` und `F_MOVE_IN1`) an den Auswahlbaustein übergeben.
3.  **Auswahllogik (`F_SEL`):**
    Der Baustein `F_SEL` führt die eigentliche Selektion durch:
    *   Ist der Selektor `G` = **`FALSE`**, wird der Wert von **`IN0`** an den Ausgang durchgeschaltet.
    *   Ist der Selektor `G` = **`TRUE`**, wird der Wert von **`IN1`** an den Ausgang durchgeschaltet.
4.  **Ausgabe:**
    Der ausgewählte Wert wird über einen weiteren Kopierbaustein (`F_MOVE_OUT`) an ein Ausgangs-Flip-Flop geleitet und über den Adapter `OUT` mit dem Ereignis `E1` ausgegeben.

---

## Technische Besonderheiten

*   **Hybrid-Schnittstelle:** Der Baustein schließt die Lücke zwischen klassischer variablenbasierter Verdrahtung (`IN0` über Datenpin) und adapterbasierter Modularisierung (`IN1`, `G` und `OUT` über Adapter).
*   **Ereignisentkopplung durch Flip-Flops:** Durch den Einsatz von `E_D_FF` (bzw. `E_D_FF_ANY`) auf allen Eingangspfaden wird sichergestellt, dass jeder Trigger auf einem beliebigen Eingangspfad eine Neuberechnung und eine entsprechende Ausgabe am Adapter `OUT` zur Folge hat.
*   **Typkonformität:** Alle internen Operationen und Datenpfade für die Werte `IN0`, `IN1` und `OUT` sind strikt auf den Datentyp `LWORD` (64-Bit) ausgelegt.

---

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB / FBNetwork) handelt, wird das Verhalten durch das Zusammenspiel der internen Bausteine bestimmt:

| Ereignis-Quelle | Zustand Selektor `G` | Interne Aktion | Ergebnis am Adapter `OUT` |
| :--- | :--- | :--- | :--- |
| `EI0` | `FALSE` | `IN0` wird aktualisiert, `F_SEL` schaltet `IN0` durch | `OUT.D1` = `IN0`, Ereignis `OUT.E1` wird ausgelöst |
| `EI0` | `TRUE` | `IN0` wird aktualisiert, `F_SEL` schaltet weiterhin `IN1` durch | `OUT.D1` = `IN1`, Ereignis `OUT.E1` wird ausgelöst |
| `IN1.E1` | `FALSE` | `IN1` wird aktualisiert, `F_SEL` schaltet weiterhin `IN0` durch | `OUT.D1` = `IN0`, Ereignis `OUT.E1` wird ausgelöst |
| `IN1.E1` | `TRUE` | `IN1` wird aktualisiert, `F_SEL` schaltet `IN1` durch | `OUT.D1` = `IN1`, Ereignis `OUT.E1` wird ausgelöst |
| `G.E1` | Wechsel zu `FALSE` | Selektor ändert sich, `F_SEL` schaltet `IN0` durch | `OUT.D1` = `IN0`, Ereignis `OUT.E1` wird ausgelöst |
| `G.E1` | Wechsel zu `TRUE` | Selektor ändert sich, `F_SEL` schaltet `IN1` durch | `OUT.D1` = `IN1`, Ereignis `OUT.E1` wird ausgelöst |

---

## Anwendungsszenarien

*   **Umschaltung zwischen lokalem und entferntem Sollwert:** `IN0` kann als lokal im FB-Netzwerk berechneter Standard- oder Ersatzwert dienen, während `IN1` einen über ein Bussystem oder ein anderes Modul (via Adapter) gelieferten dynamischen Wert einspeist.
*   **Modus-Selektion in Steuerungen:** Signalquellenumschaltung bei Hand-/Automatikbetrieb, bei dem der Selektor `G` den Betriebsmodus vorgibt.
*   **Redundante Datenpfade:** Schnelles Umschalten zwischen zwei Signalquellen im Fehlerfall eines Sensors oder Kommunikationsteilnehmers.

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard `F_SEL`:** Der klassische IEC 61131-3 `F_SEL`-Baustein besitzt nur elementare Dateneingänge und keine integrierte Ereignissteuerung oder Adapter-Unterstützung. Er benötigt externe Logik, um in einer ereignisgesteuerten IEC 61499-Umgebung zuverlässig zu arbeiten.
*   **`LWORD_AL_AX_SEL_AL` vs. andere Typvarianten:** Es existieren analoge Implementierungen für andere Datentypen (z. B. für `DWORD`, `REAL` etc.). Dieser spezifische Baustein ist exklusiv für 64-Bit-Datenbreiten (`LWORD`) optimiert.

---

## Fazit

Der `LWORD_AL_AX_SEL_AL` ist ein hochgradig spezialisierter, modularer Auswahlbaustein für IEC 61499-Anwendungen. Durch die Kapselung der Speicher- und Auswahllogik in Kombination mit flexiblen Adapterschnittstellen vereinfacht er das Design von übersichtlichen und wartungsfreundlichen Applikationen in der industriellen Automatisierungstechnik, insbesondere wenn große Datenwortbreiten sicher geschaltet werden müssen.