# TIME_ATM_AX_SEL_ATM


![TIME_ATM_AX_SEL_ATM](./TIME_ATM_AX_SEL_ATM.svg)

*Kein Bild verfügbar*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `TIME_ATM_AX_SEL_ATM` dient der binären Auswahl (Selektion) zwischen zwei Zeitwerten (Datentyp `TIME`) basierend auf einem Selektionssignal. 

Der Baustein kombiniert die klassische Auswahl-Logik des IEC 61131-3 `SEL`-Bausteins mit der ereignisgesteuerten Architektur der IEC 61499. Durch die Verwendung von standardisierten, unidirektionalen Adaptern wird eine saubere Kapselung und eine Reduzierung der Verbindungsleitungen in komplexen Steuerungsnetzen erreicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Löst die Übernahme und Verarbeitung des Daten-Eingangs `IN0` aus.

### **Ereignis-Ausgänge**

*(Keine direkten Ereignis-Ausgänge deklariert. Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Adapter `OUT`)*

### **Daten-Eingänge**

*   **IN0** (`TIME`): Der erste auswählbare Zeitwert. Dieser Wert wird an den Ausgang durchgeschaltet, wenn das Selektionssignal des Adapters `G` den Zustand `FALSE` aufweist.

### **Daten-Ausgänge**

*(Keine direkten Daten-Ausgänge deklariert. Die Datenweitergabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`)*

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::ATM`): Der ausgewählte Ausgangsadapter. Über diesen wird der selektierte Zeitwert (`D1`) zusammen mit dem zugehörigen Bestätigungsereignis (`E1`) ausgegeben.
*   **IN1** (Socket, Typ: `adapter::types::unidirectional::ATM`): Der zweite auswählbare Zeitwert, der über diesen Adapter empfangen wird (`D1` als Zeitwert, `E1` als Trigger-Ereignis). Dieser Wert wird ausgewählt, wenn das Selektionssignal `TRUE` ist.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter. Das boolesche Signal (`D1`) bestimmt, welcher Eingang auf den Ausgang geschaltet wird. Das Ereignis `E1` triggert die Neuberechnung.

---

## Funktionsweise

Das Verhalten des Bausteins basiert auf einem internen Netzwerk aus Standard-Funktionsbausteinen:

1.  **Datenerfassung und Synchronisation:**
    Trifft ein Ereignis an einem der Eingänge (`EI0`, `IN1.E1` oder `G.E1`) ein, wird der jeweilige Wert über D-Flipflops (`E_D_FF` bzw. `E_D_FF_ANY`) stabilisiert und zwischengespeichert.
2.  **Wertübertragung:**
    Über interne Move-Bausteine (`F_MOVE`) werden die Daten an den zentralen Auswahlbaustein `F_SEL` übergeben.
3.  **Auswahllogik (Selection):**
    Der Baustein `F_SEL` wertet das Steuersignal aus dem Adapter `G` aus:
    *   Ist `G.D1` = `FALSE`, wird der Wert von `IN0` gewählt.
    *   Ist `G.D1` = `TRUE`, wird der Wert von `IN1.D1` gewählt.
4.  **Ausgabe:**
    Der ausgewählte Wert wird an den Plug `OUT` übergeben. Das Ausgangsereignis `OUT.E1` signalisiert dem nachfolgenden System, dass ein neuer gültiger Zeitwert an `OUT.D1` anliegt.

```
                  +-------------------------+
                  |  TIME_ATM_AX_SEL_ATM    |
   (TIME) IN0 ---->                         |
  (Event) EI0 ---->                         |     +-----------+
                  |                         |====>|    OUT    | (Plug: ATM)
  (Socket) IN1 ===>                         |     +-----------+
  (Socket)   G ===>                         |
                  +-------------------------+
```

---

## Technische Besonderheiten

*   **Ereignisentkopplung:** Durch die Verwendung von D-Flipflops im internen Netzwerk werden die Datenwerte von den Trigger-Ereignissen entkoppelt. Dies verhindert unkontrollierte Zustandsänderungen bei asynchron eintreffenden Ereignissen.
*   **Adapterorientiertes Design:** Minimiert den Verdrahtungsaufwand in 4diac-IDE, da Zeit- und Steuersignale gebündelt über Adaptergassen (`ATM` und `AX`) geführt werden.

---

## Zustandsübersicht

| Selektionssignal (`G.D1`) | Trigger-Ereignis | Ausgewählter Ausgang (`OUT.D1`) |
| :--- | :--- | :--- |
| `FALSE` | `EI0` / `G.E1` | Wert von `IN0` |
| `TRUE` | `IN1.E1` / `G.E1` | Wert von `IN1.D1` |

---

## Anwendungsszenarien

*   **Umschaltung von Prozesszeiten:** Dynamische Auswahl zwischen zwei verschiedenen Timer-Laufzeiten (z. B. Umschaltung zwischen einem schnellen "Standard-Intervall" und einem langsameren "Wartungs-Intervall" in einer Prozesssteuerung).
*   **Rezeptursteuerung:** Zeitgesteuerte Abläufe, bei denen je nach Betriebsmodus (z. B. Automatik vs. Handbetrieb) unterschiedliche Verzögerungszeiten angewendet werden müssen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen, rein datenflussorientierten Selektor-Baustein (wie dem IEC 61131-3 `SEL`):
*   **Vorteil:** Der `TIME_ATM_AX_SEL_ATM` arbeitet vollständig ereignisgesteuert. Es wird nur dann ein Ausgangsereignis generiert, wenn sich tatsächlich Eingangsdaten oder das Auswahlsignal ändern.
*   **Struktur:** Durch die Verwendung von Adaptern anstelle von Einzelpins bleibt das Applikationsdiagramm auch bei vielen Signalpfaden übersichtlich.

---

## Fazit

Der `TIME_ATM_AX_SEL_ATM` ist ein spezialisierter und robuster Hilfsbaustein für die strukturierte Auswahl von Zeitwerten. Er eignet sich hervorragend für modulare Architekturen, in denen Übersichtlichkeit und ereignisdiskrete Verarbeitung im Vordergrund stehen.