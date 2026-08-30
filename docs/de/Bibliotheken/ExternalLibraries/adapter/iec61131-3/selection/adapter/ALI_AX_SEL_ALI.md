# ALI_AX_SEL_ALI


![ALI_AX_SEL_ALI](./ALI_AX_SEL_ALI.svg)

*[Bild des Funktionsblocks]*

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ALI_AX_SEL_ALI` ist ein binärer Auswahlbaustein (Selection Block), der für die Verwendung mit unidirektionalen Adaptern konzipiert ist. Er ermöglicht es, basierend auf einem Auswahlsignal (Selector), zwischen zwei Eingangssignalen zu wählen und das ausgewählte Signal an einen Ausgang weiterzuleiten. Dieser Baustein kapselt die Standard-Auswahllogik und passt sie an eine ereignisgesteuerte Adapter-Schnittstelle an.

## Schnittstellenstruktur

Da es sich um einen adapterbasierten Funktionsblock handelt, besitzt er keine direkten, klassischen Ereignis- oder Dateneingänge auf der obersten Ebene. Die gesamte Kommunikation wird über Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (Steuerung erfolgt über die Adapter).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (Steuerung erfolgt über die Adapter).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingang-Schnittstellen)**

- **G** (`adapter::types::unidirectional::AX`): Der Selektor-Adapter (Gate). Er steuert, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird.
- **IN0** (`adapter::types::unidirectional::ALI`): Der erste auswählbare Eingangs-Adapter (wird standardmäßig bei `G = FALSE` gewählt).
- **IN1** (`adapter::types::unidirectional::ALI`): Der zweite auswählbare Eingangs-Adapter (wird bei `G = TRUE` gewählt).

#### **Plugs (Ausgang-Schnittstellen)**

- **OUT** (`adapter::types::unidirectional::ALI`): Der Ausgangs-Adapter, der das ausgewählte Signal und das dazugehörige Ereignis bereitstellt.

---

## Funktionsweise

Der Funktionsblock arbeitet als Multiplexer für die Adapter-Signale:

1. **Ereignis-Erfassung**: Sobald an einem der Eingangs-Adapter (`IN0`, `IN1`) oder dem Selektor-Adapter (`G`) ein Ereignis (`E1`) eingeht, wird dieses über interne flankengetriggerte Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) abgefangen.
2. **Datenpufferung**: Die Daten der Eingänge (`IN0.D1` und `IN1.D1`) werden über interne `F_MOVE`-Bausteine (konfiguriert auf den Datentyp `LINT`) an den zentralen Auswahlbaustein `F_SEL` weitergegeben.
3. **Auswahl**: Der Baustein `F_SEL` wertet den Zustand des Selektors `G.D1` aus:
   - Ist `G.D1` auf `FALSE`, wird der Wert von `IN0` ausgewählt.
   - Ist `G.D1` auf `TRUE`, wird der Wert von `IN1` ausgewählt.
4. **Ausgabe**: Der ausgewählte Wert wird an das Flip-Flop `E_D_FF_ANY_OUT` übergeben. Dieses aktualisiert den Ausgangs-Datenpunkt `OUT.D1` und triggert gleichzeitig das Ausgangsereignis `OUT.E1`.

---

## Technische Besonderheiten

- **Datentyp-Spezifität**: Die internen Verschiebungs-Bausteine (`F_MOVE`) sind fest auf den Datentyp `LINT` (Long Integer) eingestellt. Das bedeutet, dass die über die `ALI`-Adapter übertragenen Daten als `LINT` interpretiert und verarbeitet werden.
- **Ereignisentkopplung**: Durch die Verwendung von Flip-Flops (`E_D_FF`) wird sichergestellt, dass Datenänderungen an den Eingängen konsistent und synchronisiert mit den entsprechenden Ereignissen am Ausgang ankommen.

---

## Zustandsübersicht

Der Funktionsblock besitzt keine eigene Zustandshierarchie (kein ECC), da er als zusammengesetzter Netzwerk-Funktionsblock (Composite FB) realisiert ist. Sein Verhalten ist rein daten- und ereignisflussgesteuert:

| Zustand Selektor (`G.D1`) | Trigger-Ereignis | Aktion / Ergebnis |
| :--- | :--- | :--- |
| `FALSE` | Ereignis an `IN0.E1`, `IN1.E1` oder `G.E1` | Wert von `IN0.D1` wird an `OUT.D1` übergeben; `OUT.E1` wird ausgelöst. |
| `TRUE` | Ereignis an `IN0.E1`, `IN1.E1` oder `G.E1` | Wert von `IN1.D1` wird an `OUT.D1` übergeben; `OUT.E1` wird ausgelöst. |

---

## Anwendungsszenarien

- **Sollwert-Umschaltung**: Auswahl zwischen einem automatischen (z.B. von einem Regler berechneten) Sollwert und einem manuell vorgegebenen Sollwert in einer industriellen Anlage.
- **Sensor-Redundanz**: Umschaltung zwischen zwei redundanten Sensoren (z.B. bei Ausfall oder zur Kalibrierung), die ihre Daten über standardisierte Adapter-Schnittstellen bereitstellen.
- **Rezepturgesteuerte Pfadauswahl**: Dynamische Auswahl von Prozessparametern basierend auf einem binären Steuersignal im Ablaufprogramm.

---

## Vergleich mit ähnlichen Bausteinen

- **F_SEL (Standard IEC 61131-3)**: Der standardmäßige Auswahleffekt-Block arbeitet direkt mit elementaren Datentypen und benötigt explizite Event-Verbindungen. `ALI_AX_SEL_ALI` kapselt diesen Baustein und erweitert ihn um die direkte Unterstützung für die strukturiertere und sauberere Verwendung von unidirektionalen Adaptern (`ALI`/`AX`).
- **Klassische Multiplexer (MUX)**: Während ein MUX oft mehrere Kanäle (z.B. 4, 8) bedienen kann, ist dieser Baustein strikt auf eine binäre Auswahl (2 Kanäle) optimiert, bietet dafür jedoch eine schlanke Adapter-Integration.

---

## Fazit

Der `ALI_AX_SEL_ALI` ist ein spezialisierter Hilfsbaustein, der die Signal- und Ereignisweiterleitung in komplexen 4diac-Systemen vereinfacht. Durch die Kapselung der Adapterlogik trägt er maßgeblich zur Übersichtlichkeit im Applikations-Netzwerk bei, indem er das manuelle Entpacken und Neuverpacken von Adapter-Signalen überflüssig macht.
