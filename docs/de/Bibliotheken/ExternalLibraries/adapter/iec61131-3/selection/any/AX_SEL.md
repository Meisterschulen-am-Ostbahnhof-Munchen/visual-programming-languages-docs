# AX_SEL


![AX_SEL](./AX_SEL.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AX_SEL` dient der binären Auswahl (Selektion) zwischen zwei Eingangssignalen über einen Adapter-Selektor. Die Besonderheit dieses Bausteins liegt darin, dass ein Ausgangsereignis ausschließlich dann erzeugt wird, wenn sich der Zustand des Selektions-Eingangs (über den Adapter `G`) ändert. Wertänderungen an den Dateneingängen allein lösen keine Datenweiterleitung am Ausgang aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
* **EI0**: Aktualisiert den Wert des Dateneingangs `IN0`.
* **EI1**: Aktualisiert den Wert des Dateneingangs `IN1`.

### **Ereignis-Ausgänge**
* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert, dass ein neuer ausgewählter Wert am Ausgang `OUT` anliegt. Dieses Ereignis wird nur getriggert, wenn sich der Selektor `G` ändert.

### **Daten-Eingänge**
* **IN0** (`ANY`): Erster auswählbarer Dateneingang.
* **IN1** (`ANY`): Zweiter auswählbarer Dateneingang.

### **Daten-Ausgänge**
* **OUT** (`ANY`): Der aktuell ausgewählte Ausgangswert (entspricht entweder `IN0` oder `IN1`).

### **Adapter**
* **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Er enthält:
  * ein Ereignis `E1` (welches als Takt für die Auswahl dient)
  * ein Datenelement `D1` (das eigentliche Auswahlsignal)

---

## Funktionsweise
Intern ist der Composite-Funktionsbaustein `AX_SEL` aus zwei untergeordneten Bausteinen aufgebaut:
1. **`E_D_FF`** (Event-D-Flip-Flop): Dieser Baustein speichert den Zustand des Auswahlsignals `G.D1` ab, sobald das Ereignis `G.E1` eintrifft.
2. **`F_SEL`** (Standard-Auswahlfunktion nach IEC 61131-3): Führt die eigentliche Selektion durch.

Trifft ein Ereignis über den Adapter `G` ein (`G.E1`), wird der Wert von `G.D1` in das Flip-Flop übernommen. Das Flip-Flop gibt daraufhin ein Ereignis `EO` aus, welches die Berechnung im Auswahlbaustein `F_SEL` anstößt. 
* Ist der Zustand des Selektors `FALSE`, wird `IN0` auf den Ausgang `OUT` durchgeschaltet.
* Ist der Zustand des Selektors `TRUE`, wird `IN1` auf den Ausgang `OUT` durchgeschaltet.

Da die Ereigniseingänge `EI0` und `EI1` nicht mit dem internen Trigger-Netzwerk verbunden sind, führt eine reine Wertänderung an den Eingängen `IN0` oder `IN1` zu keiner sofortigen Aktualisierung des Ausgangsereignisses `CNF`.

---

## Technische Besonderheiten
* **Datentyp-Flexibilität**: Durch die Verwendung des generischen Datentyps `ANY` für `IN0`, `IN1` und `OUT` kann der Baustein für verschiedenste Datentypen (z.B. `INT`, `REAL`, `BOOL`, etc.) eingesetzt werden.
* **Ereignisfilterung**: Verhindert "Event-Spamming". Der Ausgang `CNF` wird extrem ressourcenschonend nur dann ausgelöst, wenn ein tatsächlicher Umschaltvorgang über den Adapter `G` stattfindet.

---

## Zustandsübersicht
Der Baustein besitzt keine komplexe interne Zustandsmaschine (ECC), da er als Composite-Funktionsbaustein (Netzwerk) realisiert ist. Das Verhalten wird durch die Kombination des ereignisgesteuerten D-Flip-Flops (`E_D_FF`) und des Standard-Selektors (`F_SEL`) bestimmt:

| Zustand Selektor (`G.D1`) | Trigger-Ereignis | Ausgangswert (`OUT`) | Ausgangsereignis (`CNF`) |
|:---|:---|:---|:---|
| Beliebig | `EI0` oder `EI1` | Keine Änderung am Ausgang | Kein Ereignis |
| `FALSE` | `G.E1` | Wert von `IN0` | `CNF` wird ausgelöst |
| `TRUE` | `G.E1` | Wert von `IN1` | `CNF` wird ausgelöst |

---

## Anwendungsszenarien
* **Umschaltung zwischen Betriebsmodi**: Wahl zwischen einem manuellen Vorgabewert (`IN0`) und einem Automatik-Sollwert (`IN1`), wobei die Umschaltung über ein zentrales Steuersignal (Adapter `G`) koordiniert wird.
* **Redundante Sensorik**: Umschaltung zwischen einem Hauptsensor und einem Ersatzsensor bei Signalwechsel.
* **Ressourceneffiziente Datenübertragung**: Szenarien, in denen nachfolgende Programmteile nur bei einer expliziten Änderung der Signalquelle aktiv werden sollen.

---

## Vergleich mit ähnlichen Bausteinen
* **Standard `F_SEL`**: Der Standard-Auswahlbaustein reagiert direkt auf jedes Berechnungsereignis (`REQ`) und benötigt separate Steuerleitungen. `AX_SEL` hingegen kapselt die Steuerung über eine standardisierte Adapterschnittstelle (`AX`) und sorgt intern dafür, dass Ereignisse nur bei einer Selektor-Änderung weitergeleitet werden.
* **Einfache Multiplexer**: Normale Multiplexer schalten Daten oft kontinuierlich durch. `AX_SEL` arbeitet rein ereignisbasiert und minimiert somit die CPU-Last in verteilten IEC 61499 Systemen.

---

## Fazit
`AX_SEL` ist ein spezialisierter und hocheffizienter Baustein für die Signal-Auswahl in der verteilten Automatisierung. Durch die Bindung der Auswertung an das Adapter-Ereignis wird eine ungewollte Flut an Ausgangsereignissen verhindert, was die Performance und Übersichtlichkeit innerhalb der 4diac-Steuerungsanwendung optimiert.