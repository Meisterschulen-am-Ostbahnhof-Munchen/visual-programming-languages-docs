# AULI_ULINT_AX_SEL_AULI


![AULI_ULINT_AX_SEL_AULI](./AULI_ULINT_AX_SEL_AULI.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AULI_ULINT_AX_SEL_AULI` dient als binärer Selektor (Auswahlschalter) in einer IEC 61499-Angebung. Er ermöglicht es, ereignisgesteuert zwischen einem über einen Adapter bereitgestellten Wert (`IN0`) und einem direkt anstehenden numerischen Standard-Datentyp (`IN1` vom Typ `ULINT`) auszuwählen. Die Auswahl wird über einen separaten Steueradapter (`G`) vorgenommen. Das Ergebnis wird an einen Ausgangs-Adapter (`OUT`) übergeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| `EI1` | Aktualisiert und setzt den Wert des direkten Dateneingangs `IN1`. | `IN1` |

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt ausschließlich gekoppelt über die Adapter-Schnittstellen (Plugs/Sockets).*

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| `IN1` | `ULINT` | Wählbarer Eingangswert (Eingang 1), der bei aktivem Selektor an den Ausgang durchgeschaltet wird. |

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt über den Adapter-Plug `OUT`.*

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| `OUT` | `adapter::types::unidirectional::AULI` | Plug (Ausgang) | Der ausgewählte Ausgangswert. |
| `IN0` | `adapter::types::unidirectional::AULI` | Socket (Eingang) | Wählbarer Eingangswert (Eingang 0). |
| `G` | `adapter::types::unidirectional::AX` | Socket (Eingang) | Selektor-Signal zur Steuerung des Auswahlschalters. |

---

## Funktionsweise

Der Baustein basiert intern auf einem logischen Netzwerk, das die Datenströme der Adapter und des Direkteingangs synchronisiert:

1. **Eingangssynchronisation:** Die Eingangssignale aus den Sockets `IN0` und `G` sowie der direkte Dateneingang `IN1` (getriggert über `EI1`) werden über interne flanken- und datengesteuerte Flip-Flops (`E_D_FF` und `E_D_FF_ANY`) gepuffert.
2. **Datenweiterleitung (`F_MOVE`):** Die ankommenden Werte werden über interne `F_MOVE`-Bausteine für die Weiterverarbeitung im Selektor vorbereitet.
3. **Auswahl-Logik (`F_SEL`):** Der Kern-Auswahlbaustein `F_SEL` wertet den Zustand des Selektors `G` aus:
   - Ist das Signal an `G` **FALSE** (0), wird der Wert von `IN0` an den Ausgang `OUT` weitergeleitet.
   - Ist das Signal an `G` **TRUE** (1), wird der Wert von `IN1` an den Ausgang `OUT` weitergeleitet.
4. **Ausgabe:** Sobald sich ein relevanter Eingangswert oder das Selektorsignal ändert, wird der ausgewählte Wert über den Adapter-Plug `OUT` ausgegeben und das entsprechende Ereignis (`OUT.E1`) ausgelöst.

---

## Technische Besonderheiten

- **Hybrid-Schnittstelle:** Der Baustein kombiniert nahtlos die Verwendung von standardisierten, unidirektionalen Adaptern (`AULI`, `AX`) mit klassischen IEC 61131-Datentypen (`ULINT`).
- **Ereignisgesteuert:** Durch die interne Verwendung von `E_D_FF_ANY`-Bausteinen ist sichergestellt, dass Daten nur dann verarbeitet und weitergeleitet werden, wenn tatsächlich ein neues Ereignis die Gültigkeit der Daten signalisiert. Dies schont die Systemressourcen der Laufzeitumgebung.

---

## Zustandsübersicht

Die logische Zuordnung des Ausgangs verhält sich wie folgt:

| Selektor-Zustand (`G.D1`) | Aktives Ereignis an Quelle | Ausgangswert (`OUT.D1`) |
| :--- | :--- | :--- |
| `FALSE` | Event an `IN0.E1` oder `G.E1` | Entspricht dem Wert von `IN0.D1` |
| `TRUE` | Event an `EI1` oder `G.E1` | Entspricht dem Wert von `IN1` |

---

## Anwendungsszenarien

- **Signal-Umschaltung im Feld:** Umschalten zwischen einem standardmäßig über einen Bus/Adapter übertragenen Wert (`IN0`) und einem lokalen Ersatz- oder Festwert (`IN1`).
- **Betriebsartenwahl:** Auswahl zwischen einem automatischen Prozesswert (z.B. Zählerstand als `ULINT` an `IN1`) und einem manuell vorgegebenen Wert über ein HMI-Interface (über Adapter `IN0`).

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-`F_SEL`-Baustein nach IEC 61131-3, welcher lediglich Rohdaten ohne ereignisgesteuerte Synchronisation verarbeitet, bietet dieser Baustein eine direkte Integration in die ereignisorientierte Architektur der IEC 61499. Er erspart dem Anwender das manuelle Erstellen von Hilfsnetzwerken zur Ereigniskopplung und Adapterauflösung.

---

## Fazit

Der `AULI_ULINT_AX_SEL_AULI`-Baustein ist eine spezialisierte und robuste Lösung für Auswahlszenarien in modular aufgebauten Steuerungsanwendungen. Durch die Kapselung der Adapter- und Flip-Flop-Logik sorgt er für übersichtliche und leicht zu wartende Anwendungsdiagramme in der 4diac-IDE.