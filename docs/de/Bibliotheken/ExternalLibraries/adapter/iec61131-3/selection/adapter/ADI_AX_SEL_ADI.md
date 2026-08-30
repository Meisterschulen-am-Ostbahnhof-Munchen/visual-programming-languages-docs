# ADI_AX_SEL_ADI


![ADI_AX_SEL_ADI](./ADI_AX_SEL_ADI.svg)

*Kein Bild verfügbar*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ADI_AX_SEL_ADI` dient der binären Auswahl (Selektion) zwischen zwei analogen bzw. ganzzahligen Eingangssignalen, die über unidirektionale Adapter übertragen werden. Basierend auf dem Zustand eines digitalen Auswahlsignals (Selectors) wird entweder der Wert des ersten oder des zweiten Eingangs auf den Ausgang durchgeschaltet.

Der Baustein ist als zusammengesetzter Funktionsbaustein (Composite FB) realisiert und nutzt intern standardisierte Auswahl- und Kopierfunktionen nach IEC 61131-3, die für die ereignisgesteuerte IEC 61499-Adapter-Architektur angepasst wurden.

## Schnittstellenstruktur

Die Schnittstelle dieses Funktionsbausteins ist vollständig über Adapter realisiert. Es gibt keine direkten elementaren Daten- oder Ereigniseingänge außerhalb der Adapterstrukturen.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (Ereignisse werden über die Adapter-Schnittstellen empfangen).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (Ereignisse werden über die Adapter-Schnittstellen gesendet).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Plugs (Stecker - Ausgänge)**

- **OUT** (Typ: `adapter::types::unidirectional::ADI`):
  Der ausgewählte Ausgang (Selected Output). Sendet das ausgewählte Datensignal (`D1`) und das zugehörige Aktualisierungsereignis (`E1`).

#### **Sockets (Buchsen - Eingänge)**

- **IN0** (Typ: `adapter::types::unidirectional::ADI`):
  Erster auswählbarer Eingang. Dieser Wert wird zum Ausgang durchgeschaltet, wenn das Auswahlsignal `G` auf `FALSE` (0) steht.
- **IN1** (Typ: `adapter::types::unidirectional::ADI`):
  Zweiter auswählbarer Eingang. Dieser Wert wird zum Ausgang durchgeschaltet, wenn das Auswahlsignal `G` auf `TRUE` (1) steht.
- **G** (Typ: `adapter::types::unidirectional::AX`):
  Der Selector (Gate) zur Steuerung des Auswahlprozesses. Ein Wechsel des Zustands steuert die Umschaltung zwischen `IN0` und `IN1`.

---

## Funktionsweise

Die interne Struktur von `ADI_AX_SEL_ADI` arbeitet rein ereignisgesteuert:

1. **Eingangserfassung**:
   Trifft an einem der Eingänge (`IN0`, `IN1`) oder am Selector (`G`) ein Ereignis (`E1`) ein, wird der dazugehörige interne Datenwert (`D1`) über ereignisgesteuerte Speicherglieder (`E_D_FF_ANY` bzw. `E_D_FF`) erfasst.
2. **Datenpufferung**:
   Die Bausteine `F_MOVE_IN0` und `F_MOVE_IN1` kopieren die Daten (interpretiert als Datentyp `DINT`) an den zentralen Auswahlbaustein `F_SEL`.
3. **Auswahllogik (Selection)**:
   Der Baustein `F_SEL` (entspricht dem klassischen `SEL`-Standardbaustein aus der IEC 61131-3) wertet das Steuersignal `G` aus:
   - Ist das Signal des Adapters `G` gleich `FALSE`, wird das Signal von `IN0` gewählt.
   - Ist das Signal des Adapters `G` gleich `TRUE`, wird das Signal von `IN1` gewählt.
4. **Ausgabe**:
   Der ausgewählte Wert wird über `F_MOVE_OUT` an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übergeben. Dieses setzt den Wert `D1` am Ausgangsadapter `OUT` und triggert sofort das dazugehörige Ereignis `OUT.E1`, um nachgelagerte Bausteine über die Datenänderung zu informieren.

---

## Technische Besonderheiten

- **Adapter-Kapselung**: Durch die Verwendung von Adaptern (`ADI` und `AX`) wird die Anzahl der sichtbaren Verbindungslinien im 4diac-Anwendungsdiagramm drastisch reduziert, was die Übersichtlichkeit und Wartbarkeit erhöht.
- **Datentyp-Spezifizierung**: Die internen Kopiervorgänge (`F_MOVE_IN0`, `F_MOVE_IN1` und `F_MOVE_OUT`) sind fest für den Datentyp `DINT` (Double Integer) konfiguriert.
- **Echtzeit-Durchreichung**: Der Baustein reagiert verzögerungsfrei auf jede Flanke der Eingangssignale sowie des Auswahlsignals.

---

## Zustandsübersicht

Da es sich um einen rein datenfluss- und ereignisgesteuerten Netzwerk-Baustein (Composite FB) handelt, besitzt er keine interne Zustandsmaschine (ECC). Das Verhalten lässt sich statisch wie folgt beschreiben:

| Zustand Selector `G` | Ereignis an Eingang | Verhalten am Ausgang `OUT` |
| :--- | :--- | :--- |
| `FALSE` | Beliebiges Ereignis | `OUT.D1` erhält den Wert von `IN0.D1`; `OUT.E1` wird ausgelöst. |
| `TRUE` | Beliebiges Ereignis | `OUT.D1` erhält den Wert von `IN1.D1`; `OUT.E1` wird ausgelöst. |

---

## Anwendungsszenarien

- **Hand-/Automatik-Umschaltung**: Auswahl zwischen einem manuell vorgegebenen Sollwert (z. B. über ein HMI an `IN1`) und einem automatisch berechneten Regler-Sollwert (an `IN0`).
- **Sensor-Redundanz**: Umschaltung auf einen Backup-Sensor (`IN1`), falls eine Diagnose-Logik einen Fehler beim Hauptsensor (`IN0`) erkennt und das Signal `G` auf `TRUE` setzt.
- **Rezeptursteuerung**: Dynamische Auswahl verschiedener vordefinierter Prozessparameter während des Betriebs.

---

## Vergleich mit ähnlichen Bausteinen

- **Standard `F_SEL`**: Der Standard-Auswahlbaustein arbeitet mit elementaren Datentypen und benötigt explizite Event-Verbindungen für Trigger und Confirmation. `ADI_AX_SEL_ADI` automatisiert diesen Prozess vollständig über strukturierte Adapter-Kanäle.
- **Analoge Multiplexer**: Im Gegensatz zu Multiplexern mit einer unbestimmten Anzahl an Kanälen ist dieser Baustein auf die schnelle und effiziente binäre Auswahl (1 aus 2) spezialisiert.

---

## Fazit

Der `ADI_AX_SEL_ADI` ist ein äußerst nützlicher Hilfsbaustein für IEC 61499-Anwendungen in der 4diac IDE. Er verbindet die bewährte Selektionslogik der IEC 61131-3 mit den modernen, sauberen Design-Prinzipien der adapterbasierten ereignisorientierten Kommunikation.
