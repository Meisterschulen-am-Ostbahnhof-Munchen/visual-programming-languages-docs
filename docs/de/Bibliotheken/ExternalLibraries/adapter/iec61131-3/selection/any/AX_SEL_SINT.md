# AX_SEL_SINT




![AX_SEL_SINT](./AX_SEL_SINT.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_SINT` ist ein standardisierter Auswahlbaustein (Selection Function) für den Datentyp `SINT` (Short Integer). Er ermöglicht die binäre Auswahl zwischen zwei Eingangswerten basierend auf dem Zustand eines Selektionssignals, das über einen Adapter eingelesen wird. Der Baustein ist für den Einsatz in ereignisgesteuerten Systemen konzipiert und kombiniert klassische IEC 61131-3 Auswahl-Logik mit der ereignisbasierten Ausführung nach IEC 61499.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Aktualisiert den Wert des Daten-Eingangs `IN0`.
*   **EI1**: Aktualisiert den Wert des Daten-Eingangs `IN1`.

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungsereignis (Confirmation). Signalisiert, dass eine Auswertung stattgefunden hat und ein aktualisierter Wert an `OUT` bereitsteht.

### **Daten-Eingänge**

*   **IN0** (SINT): Erster auswählbarer Eingangswert. Dieser Wert wird an den Ausgang durchgeschaltet, wenn das Selektionssignal des Adapters `FALSE` ist.
*   **IN1** (SINT): Zweiter auswählbarer Eingangswert. Dieser Wert wird an den Ausgang durchgeschaltet, wenn das Selektionssignal des Adapters `TRUE` ist.

### **Daten-Ausgänge**

*   **OUT** (SINT): Der aktuell ausgewählte Ausgangswert.

### **Adapter**

*   **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Empfänger-Adapter, der als Selektor dient. Über diesen Adapter wird das Steuersignal für die Auswahl (Datenwert `D1`, getaktet durch das Ereignis `E1`) empfangen.

---

## Funktionsweise

Der Baustein `AX_SEL_SINT` arbeitet intern als zusammengesetzter Funktionsbaustein (Composite FB). Er koordiniert den Datenfluss zwischen den Eingängen und dem Ausgang über Speicherglieder (D-Flip-Flops):

1.  **Eingangsaktualisierung**: Sobald an `EI0` oder `EI1` ein Ereignis eintrifft, wird der entsprechende Datenwert (`IN0` bzw. `IN1`) über ein internes Flip-Flop (`E_D_FF_ANY`) übernommen und an den internen Auswahlkern weitergeleitet.
2.  **Selektor-Eingang**: Ein Ereignis am Adapter-Eingang `G.E1` triggert die Übernahme des Auswahlsignals `G.D1` via `E_D_FF_G`.
3.  **Auswahllogik (F_SEL)**:
    *   Ist das Selektionssignal `FALSE`, wird `IN0` auf den Ausgang `OUT` geschaltet.
    *   Ist das Selektionssignal `TRUE`, wird `IN1` auf den Ausgang `OUT` geschaltet.
4.  **Ereignis-Generierung**: Jede Änderung oder Aktualisierung der Eingänge oder des Selektors führt über die interne Verschaltung zu einer Neuberechnung. Nach erfolgreicher Selektion wird das Ausgangsereignis `CNF` ausgelöst, um nachfolgende Bausteine über den neuen Wert an `OUT` zu informieren.

---

## Technische Besonderheiten

*   **Adapter-Kopplung**: Die Verwendung eines unidirektionalen Adapters für das Selektionssignal erlaubt eine saubere Kapselung und vermindert den Verdrahtungsaufwand im FB-Netzwerk.
*   **Ereignisgesteuerte Speicher**: Durch den Einsatz von `E_D_FF` und `E_D_FF_ANY` werden Eingangswerte stabil zwischengespeichert, sodass auch asynchrone Signaländerungen fehlerfrei verarbeitet werden.
*   **Signaländerung**: Ein Ausgangsereignis wird zuverlässig erzeugt, wenn eine der Eingangskomponenten (`IN0`, `IN1`) oder das Selektorsignal aktualisiert wird.

---

## Zustandsübersicht

Da `AX_SEL_SINT` ein Composite-Funktionsbaustein ist, besitzt er keine eigene interne Zustandsmaschine (ECC). Das Verhalten wird vollständig durch das Zusammenspiel der internen Bausteine und deren Daten-/Ereignisflüsse bestimmt:

| Auslösendes Ereignis | Zustand Selektor (`G.D1`) | Effekt am Ausgang | Ausgangs-Event |
| :--- | :--- | :--- | :--- |
| `EI0` / `EI1` / `G.E1` | `FALSE` | `OUT` nimmt den Wert von `IN0` an | `CNF` |
| `EI0` / `EI1` / `G.E1` | `TRUE` | `OUT` nimmt den Wert von `IN1` an | `CNF` |

---

## Anwendungsszenarien

*   **Sollwert-Umschaltung**: Umschalten zwischen zwei vordefinierten Zuständen oder Grenzwerten (z. B. Rezepturwerte, Standard- vs. Wartungsgeschwindigkeiten), die als `SINT` (Bereich -128 bis 127) vorliegen.
*   **Hand-/Automatik-Umschaltung**: Auswahl eines Stellwerts entweder aus einer automatischen Regelung (`IN1`) oder einer manuellen Vorgabe (`IN0`) über ein logisches Steuersignal am Adapter `G`.

---

## Vergleich mit ähnlichen Bausteinen

*   **F_SEL (IEC 61131-3)**: Der Standard-Auswahlbaustein `F_SEL` arbeitet rein datenflussorientiert. `AX_SEL_SINT` erweitert diese Funktionalität um die ereignisgesteuerte Ausführung der IEC 61499 und bindet das Auswahlsignal elegant über eine Adapterschnittstelle an.
*   **Andere AX_SEL-Bausteine**: Bausteine wie `AX_SEL_INT` oder `AX_SEL_REAL` bieten dieselbe Funktionalität, sind jedoch für größere Ganzzahl- oder Gleitkommadatentypen ausgelegt. `AX_SEL_SINT` ist für ressourcenschonende 8-Bit-Ganzzahlen optimiert.

---

## Fazit

`AX_SEL_SINT` bietet eine performante und saubere Möglichkeit, binäre Selektionen auf `SINT`-Daten in IEC 61499-Anwendungen zu realisieren. Die Kombination aus Adapter-Anbindung und ereignisgesteuerter Triggerung macht ihn zu einem flexiblen Baustein für modulare Steuerungsarchitekturen.