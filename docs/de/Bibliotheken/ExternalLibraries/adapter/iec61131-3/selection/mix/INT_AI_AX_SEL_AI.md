# INT_AI_AX_SEL_AI


![INT_AI_AX_SEL_AI](./INT_AI_AX_SEL_AI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `INT_AI_AX_SEL_AI` dient als binärer Selektor (Auswahlbaustein) für analoge Ganzzahlwerte (`INT`). Er ermöglicht es, basierend auf dem Zustand eines Auswahlsignals (über einen Adapter), zwischen einem lokal definierten Ganzzahl-Eingangswert und einem externen, über einen Adapter bereitgestellten Analogwert auszuwählen. Das Ergebnis wird anschließend über einen analogen Ausgangs-Adapter zur Verfügung gestellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- | :--- |
| **EI0** | Event | Setzt bzw. aktualisiert den lokalen Eingangswert `IN0`. | `IN0` |

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten, klassischen Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt ausschließlich gekoppelt über die Adapter-Schnittstellen (insb. den Plug `OUT`).*

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | INT | Auswählbarer lokaler Eingangswert (Ganzzahl). |

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten, klassischen Daten-Ausgänge. Die Datenweiterleitung erfolgt über die Adapter-Schnittstellen.*

### **Adapter**

#### **Plugs (Ausgangs-Adapter)**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::AI` | Der ausgewählte analoge Ausgangswert (unidirektionaler Analog-Input-Adapter). Übermittelt den selektierten Wert (`D1`) und das dazugehörige Aktualisierungsereignis (`E1`). |

#### **Sockets (Eingangs-Adapter)**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN1** | `adapter::types::unidirectional::AI` | Auswählbarer analoger Eingangswert, der über einen Adapter eingespeist wird. |
| **G** | `adapter::types::unidirectional::AX` | Selektor-Eingang (Steuersignal) zur Auswahl des aktiven Kanals. |

---

## Funktionsweise

Der Baustein basiert intern auf einem logischen Netzwerk, welches das Verhalten eines klassischen IEC 61131-3 `SEL`-Bausteins für die 4diac-Umgebung adaptiert:

1. **Eingangssynchronisation:** 
   Sowohl der lokale Eingang `IN0` als auch die über die Adapter `IN1` und `G` eintreffenden Daten werden über flankengetriggerte D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) gepuffert. Dies stellt sicher, dass Datenwerte und Ereignisse synchron verarbeitet werden.
2. **Datenkonvertierung / Pufferung:**
   Die Werte von `IN0` und `IN1` werden über entsprechende Transfer-Bausteine (`F_MOVE_IN0` und `F_MOVE_IN1`) an den zentralen Auswahlbaustein übergeben.
3. **Auswahl-Logik (`F_SEL`):**
   Der interne Baustein `F_SEL` wertet das Steuersignal des Adapters `G` aus:
   - Ist das Auswahlsignal `G` **FALSE** (0), wird der Wert von **IN0** (lokaler Eingang) an den Ausgang durchgeschaltet.
   - Ist das Auswahlsignal `G` **TRUE** (1), wird der Wert von **IN1** (Adapter-Eingang) an den Ausgang durchgeschaltet.
4. **Ausgabe:**
   Der ausgewählte Wert wird über den Konverter `F_MOVE_OUT` und den Ausgangspuffer `E_D_FF_ANY_OUT` an den Ausgangs-Plug `OUT` übergeben und triggert dort das entsprechende Ausgangsereignis (`OUT.E1`).

---

## Technische Besonderheiten

- **Adapter-Verbindung:** Durch die Verwendung von unidirektionalen Adaptern (`AI` / `AX`) eignet sich der Baustein hervorragend für modular strukturierte Anwendungen, bei denen Signale über Adapter-Leitungen statt über lose Event-/Datenverbindungen geführt werden sollen.
- **Ereignisgesteuert:** Jede Änderung an einem der Eingänge (`EI0`, `IN1.E1` oder `G.E1`) triggert eine Neuberechnung und führt zu einer sofortigen Aktualisierung des Ausgangs-Adapters `OUT`.
- **Typkonformität:** Obwohl die Adapter abstrahierte Kanäle darstellen, ist die interne Verarbeitung strikt auf den Datentyp `INT` (Ganzzahl) ausgelegt.

---

## Zustandsübersicht

Da es sich um ein zusammengesetztes Funktionsbaustein-Netzwerk (Composite FB / Subapp-Verhalten) handelt, gibt es keine klassische Zustandsmaschine (ECC). Das Verhalten ist rein datenfluss- und ereignisgesteuert:

| Triggerndes Ereignis | Bedingung am Selektor `G` | Resultierendes Verhalten am Ausgang `OUT` |
| :--- | :--- | :--- |
| Event an `EI0` / `IN1.E1` / `G.E1` | `G.D1` ist `FALSE` | `OUT.D1` wird auf den aktuellen Wert von `IN0` gesetzt; `OUT.E1` wird ausgelöst. |
| Event an `EI0` / `IN1.E1` / `G.E1` | `G.D1` ist `TRUE` | `OUT.D1` wird auf den aktuellen Wert von `IN1.D1` gesetzt; `OUT.E1` wird ausgelöst. |

---

## Anwendungsszenarien

- **Hand-/Automatik-Umschaltung:** Einlesen eines festen Sollwerts (über `IN0` im Handbetrieb) oder eines dynamisch über einen Adapter bereitgestellten Automatik-Sollwerts (`IN1`).
- **Sensor-Fallback-Systeme:** Umschalten auf einen vordefinierten Sicherheitswert (`IN0`), falls ein externer Sensor über den Selektor `G` einen Fehler signalisiert.
- **Signal-Multiplexing:** Strukturierte Weiterleitung von Integer-Messwerten in komplexen, adapterbasierten Feldbussystemen.

---

## Vergleich mit ähnlichen Bausteinen

- **Standard `F_SEL`:** Der Standard-Auswahlbaustein `F_SEL` besitzt keine integrierte Ereignissteuerung und unterstützt keine Adapter. Er arbeitet rein auf Datenebene. `INT_AI_AX_SEL_AI` kapselt diese Funktionalität ereignisbasiert und stellt direkt die passenden Adapter-Schnittstellen bereit.
- **Standard-Multiplexer (MUX):** Ein MUX erlaubt meist die Auswahl aus mehr als zwei Kanälen mittels eines Integer-Auswahlsignals, während dieser Baustein auf eine binäre Auswahl (2 Kanäle) optimiert ist.

---

## Fazit

Der `INT_AI_AX_SEL_AI` ist ein robuster und integrationsfreundlicher Hilfsbaustein für IEC 61499 Anwendungen. Er schließt die Lücke zwischen klassischer IEC 61131-3 Auswahllogik und der modernen, adapterbasierten und ereignisgesteuerten Architektur von 4diac.