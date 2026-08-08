# AX_SEL_LREAL


![AX_SEL_LREAL](./AX_SEL_LREAL.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AX_SEL_LREAL` dient der binären Auswahl (Selektion) zwischen zwei analogen Eingangswerten des Datentyps `LREAL` (Double Precision Floating Point). Die Steuerung, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird, erfolgt über einen angeschlossenen Adapter vom Typ `AX`. Der Baustein ist für den Einsatz in ereignisgesteuerten Systemen nach dem IEC 61499-Standard konzipiert und optimiert die Netzwerkbelastung, indem er Ereignisse effizient filtert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
* **EI0**: Aktualisiert den Wert des ersten Daten-Eingangs (`IN0`).
* **EI1**: Aktualisiert den Wert des zweiten Daten-Eingangs (`IN1`).

### **Ereignis-Ausgänge**
* **CNF**: Bestätigungsereignis (Confirmation). Wird ausgelöst, wenn sich der ausgewählte Ausgangswert geändert hat.

### **Daten-Eingänge**
* **IN0** (LREAL): Erster auswählbarer Eingangswert. Wird an den Ausgang durchgereicht, wenn die Selektion (`G`) den Wert `FALSE` (bzw. 0) vorgibt.
* **IN1** (LREAL): Zweiter auswählbarer Eingangswert. Wird an den Ausgang durchgereicht, wenn die Selektion (`G`) den Wert `TRUE` (bzw. 1) vorgibt.

### **Daten-Ausgänge**
* **OUT** (LREAL): Der aktuell ausgewählte Eingangswert.

### **Adapter**
* **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Über diesen Adapter wird das Steuersignal zur Auswahl des aktiven Eingangs eingelesen.

---

## Funktionsweise
Im Inneren des Composite-Funktionsbausteins `AX_SEL_LREAL` arbeitet ein Netzwerk aus Standard-Auswahl- und Filter-Bausteinen:
1. **Wert-Speicherung**: Die Eingangsdaten an `IN0` und `IN1` werden bei Eintreffen der entsprechenden Ereignisse (`EI0`, `EI1`) über Flankenerkennungs- und Speicherbausteine (`E_D_FF_ANY`) gepuffert.
2. **Selektion**: Der Adapter `G` liefert das Auswahlsignal. Bei einem Ereignis am Adapter (`G.E1`) wird der Zustand von `G.D1` in ein internes Flip-Flop übernommen.
3. **Durchschaltung**: Der Standard-Auswahlbaustein `F_SEL` schaltet basierend auf dem Zustand des Selektors entweder `IN0` oder `IN1` durch.
4. **Ereignis-Filterung**: Der Ausgang `OUT` wird über einen `E_D_FF_ANY`-Baustein überwacht. Ein `CNF`-Ausgangsereignis wird nur dann erzeugt, wenn sich der tatsächliche Wert am Ausgang `OUT` ändert. Dies verhindert unnötige Folge-Berechnungen im System bei redundanten Signalaktualisierungen.

---

## Technische Besonderheiten
* **Ereignis-Reduktion**: Durch den integrierten Wertänderungsdetektor am Ausgang wird sichergestellt, dass nachfolgende Programmteile nur bei einer echten Wertänderung (und nicht bei jedem beliebigen Eingangsereignis) getriggert werden.
* **Asynchroner Betrieb**: Die Eingänge und der Selektor können völlig unabhängig voneinander und zu unterschiedlichen Zeiten aktualisiert werden.

---

## Zustandsübersicht
Da es sich um einen Composite-Funktionsbaustein (FB-Netzwerk) handelt, wird das Verhalten durch die Zustände der internen Bausteine bestimmt:
* **Zustand "Warten" (Idle)**: Der Baustein wartet auf ein Ereignis an `EI0`, `EI1` oder dem Adapter `G`.
* **Zustand "Eingangs-Update"**: Ein Wert an `IN0` oder `IN1` ändert sich. Der Wert wird intern aktualisiert. Eine Weiterleitung an den Ausgang erfolgt jedoch nur, wenn der betroffene Kanal gerade aktiv geschaltet ist und sich der Ausgangswert dadurch ändert.
* **Zustand "Umschaltung"**: Das Signal am Adapter `G` ändert sich. Der Baustein schaltet unverzüglich auf den anderen Kanal um und gibt bei einer Wertänderung das `CNF`-Ereignis aus.

---

## Anwendungsszenarien
* **Sollwert-Umschaltung**: Wechsel zwischen einem Automatik-Sollwert (z.B. von einer Rezeptursteuerung) und einem manuellen Sollwert (z.B. von einer Visualisierung/HMI).
* **Sensor-Redundanz**: Umschalten zwischen einem Primär- und einem Sekundärsensor (LREAL-Präzision) im Falle eines Sensorfehlers.
* **Betriebsarten-Wahl**: Routing von verschiedenen physikalischen Messgrößen je nach aktivem Prozessschritt.

---

## Vergleich mit ähnlichen Bausteinen
* **Standard `F_SEL` (IEC 61131-3)**: Der Standard-Selektor besitzt keine Ereignissteuerung und keine integrierten Adapteranschlüsse. `AX_SEL_LREAL` erweitert diese Grundfunktionalität um die vollständige IEC 61499-Konformität inklusive ereignisbasierter Optimierung und standardisierter Adapter-Kopplung.
* **`AX_SEL_REAL`**: Arbeitet analog zu diesem Baustein, ist jedoch auf den Datentyp `REAL` (einfache Genauigkeit) beschränkt. `AX_SEL_LREAL` bietet die für hochpräzise Berechnungen notwendige 64-Bit-Fließkommadarstellung.

---

## Fazit
`AX_SEL_LREAL` ist ein robuster und effizienter Baustein zur ereignisgesteuerten Signalumschaltung. Durch die Kapselung der Adapter-Schnittstelle und die intelligente Unterdrückung redundanter Ausgangsereignisse eignet er sich hervorragend für performante und saubere Steuerungsarchitekturen in der industriellen Automation.