# ALI_FB_CTU


![ALI_FB_CTU](./ALI_FB_CTU.svg)

* * * * * * * * * *
## Einleitung
Der **ALI_FB_CTU** ist ein Aufwärtszähler (Counter Up) mit 64‑Bit‑Ganzzahlauflösung (LINT). Er dient als Adapter‑Wrapper für den IEC‑61131‑Zählerbaustein *FB_CTU_LINT* und stellt alle Ein‑ und Ausgangssignale über standardisierte Adapter‑Schnittstellen (AX und ALI) bereit. Dadurch wird eine klare Trennung von Ereignis‑ und Datenflüssen erreicht und die Wiederverwendung in unterschiedlichen Projektumgebungen erleichtert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine separaten, diskreten Ereignis‑Eingänge. Die auslösenden Ereignisse werden über die Adapter **CU**, **R** und **PV** empfangen. Jeder dieser Adapter stellt ein Ereignis (E1) sowie einen zugehörigen Datenwert (D1) bereit. Ein eingehendes Ereignis an einem dieser Adapter startet die Verarbeitung.

### **Ereignis-Ausgänge**
- **CNF** (Execution Confirmation): Wird nach jedem vollständigen Verarbeitungsdurchlauf ausgegeben – unabhängig davon, ob CU, R oder PV das Ereignis ausgelöst hat.
- **Q** (Adapter AX): Stellt das Ausgangsereignis (E1) zur Verfügung, das parallel zum CNF‑Ereignis ausgegeben wird.
- **CV** (Adapter ALI): Gibt ebenfalls ein Ereignis (E1) aus, synchron zum CNF‑Ereignis.

### **Daten-Eingänge**
Der Baustein besitzt keine separaten, diskreten Daten‑Eingänge. Alle Eingangsdaten werden über die Adapter‑Schnittstellen bereitgestellt:
- **CU.D1** – Count‑Up‑Signal (BOOL)
- **R.D1** – Reset‑Signal (BOOL)
- **PV.D1** – Preset‑Wert (LINT)

### **Daten-Ausgänge**
Der Baustein besitzt keine separaten, diskreten Daten‑Ausgänge. Die Ausgangsdaten werden über die Adapter‑Schnittstellen ausgegeben:
- **Q.D1** – Zählerausgang (BOOL): wird TRUE, sobald der aktuelle Zählerstand ≥ PV ist.
- **CV.D1** – Aktueller Zählerstand (LINT)

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Sockets** (Eingänge) | CU | AX | Count‑Up: Ereignis + BOOL‑Signal |
|                        | R  | AX | Reset: Ereignis + BOOL‑Signal |
|                        | PV | ALI | Preset‑Wert: Ereignis + LINT‑Wert |
| **Plugs** (Ausgänge)  | Q  | AX | Ausgangssignal: Ereignis + BOOL‑Wert |
|                        | CV | ALI | Zählerstand: Ereignis + LINT‑Wert |

## Funktionsweise
Der **ALI_FB_CTU** kapselt einen internen *FB_CTU_LINT*. Jedes eingehende Ereignis an einem der drei Adapter **CU**, **R** oder **PV** wird an den REQ‑Event des internen Bausteins weitergeleitet. Gleichzeitig werden die jeweiligen Datenwerte an die entsprechenden Eingänge (*CU*, *R*, *PV*) übergeben. Der interne Zähler arbeitet gemäß der IEC‑61131‑Definition eines CTU:

- **Beim Ereignis an CU**: Der Zählerstand wird um 1 erhöht, sofern das zugehörige Datenbit TRUE ist.
- **Beim Ereignis an R**: Der Zählerstand wird auf 0 zurückgesetzt.
- **Beim Ereignis an PV**: Der übergebene Wert wird als neuer Preset‑Wert gespeichert.

Nach jeder Verarbeitung gibt der interne Baustein einen CNF‑Event aus. Dieser wird an alle drei Ausgangsadapter (CNF, Q, CV) weitergegeben, sodass alle Ausgänge synchron aktualisiert werden. Der Ausgang **Q** wird genau dann TRUE, wenn der aktuelle Zählerstand größer oder gleich dem Preset‑Wert ist. Der aktuelle Zählerstand ist über **CV** jederzeit ablesbar.

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle**: Alle Signale werden über standardisierte Adapter (AX für binäre, ALI für numerische Werte) ausgetauscht. Dies vereinfacht die Anbindung an heterogene Systeme und fördert die Wiederverwendbarkeit.
- **64‑Bit‑Auflösung**: Der Zähler verwendet den Datentyp LINT (Signed 64‑Bit Integer), wodurch sehr große Zählbereiche abgedeckt werden.
- **Gemeinsamer Trigger**: Sowohl CU, R als auch PV lösen denselben internen REQ aus. Werden mehrere Adapter gleichzeitig aktiv, werden alle zugehörigen Datenwerte in einem Schritt verarbeitet – der interne Baustein wertet die Signale parallel aus.
- **Hinweis zum Ausgangsverhalten**: Der Baustein feuert das AX‑Ausgangsereignis (Q.E1) bei *jedem* Update – also auch dann, wenn sich der Ausgangszustand nicht ändert. Falls eine reine „On‑Change“‑Auslösung gewünscht ist, muss dem Ausgang ein AX_D_FF (Einschaltverzögerung/Ereignisfilter) nachgeschaltet werden.

## Zustandsübersicht
Der interne Zustand wird durch den Zählerstand (64‑Bit‑Integer) und den booleschen Ausgang Q gebildet. Eine explizite Zustandsmaschine existiert nicht; der Baustein arbeitet ereignisgesteuert:

| Zustandskomponente | Mögliche Werte | Beschreibung |
|--------------------|----------------|--------------|
| Zählerstand (CV)   | 0 … 2⁶³‑1      | Aktueller Zählwert |
| Ausgang Q          | FALSE / TRUE   | TRUE, wenn CV ≥ PV |

## Anwendungsszenarien
- **Ereigniszählung**: Zählen von Impulsen in Fertigungsanlagen, Förderbändern oder Energiezählern.
- **Mengenüberwachung**: Erfassen produzierter Stückzahlen und Auslösen eines Signals bei Erreichen eines Schwellwerts.
- **Reset‑gesteuerte Zähler**: Rücksetzen des Zählers auf Null nach einem manuellen oder automatischen Reset.
- **Preset‑basierte Steuerung**: Dynamisches Ändern des Sollwerts während des Betriebs (z. B. Chargenwechsel).

## Vergleich mit ähnlichen Bausteinen
- **Gegenüber einem direkten FB_CTU_LINT**: Der ALI_FB_CTU abstrahiert die Schnittstellen auf Adapter‑Ebene. Dadurch können die Signale unabhängig von der konkreten Implementierung mit anderen Bausteinen verbunden werden, die ebenfalls AX/ALI‑Adapter verwenden.
- **Gegenüber einem Standard‑CTU mit BOOL‑Eingängen**: Der ALI_FB_CTU erlaubt den Anschluss von Adaptern, die sowohl Ereignisse als auch Daten bündeln. Dies reduziert die Anzahl separater Leitungen und macht den Entwurf übersichtlicher.
- **Gegenüber einem CTU mit INT/DINT**: Durch die Verwendung von LINT wird ein wesentlich größerer Wertebereich abgedeckt, was für hochauflösende Zählaufgaben oder Langzeitzähler vorteilhaft ist.

## Fazit
Der **ALI_FB_CTU** ist ein leistungsfähiger, adapterbasierter Aufwärtszähler für industrielle Automatisierungsumgebungen. Er kombiniert die bewährte IEC‑61131‑Zählerlogik mit modernen Adapter‑Schnittstellen und bietet eine einfache, lesbare Anbindung an andere Komponenten. Die 64‑Bit‑Auflösung, die gemeinsame Ereignisverarbeitung aller Eingänge und die Möglichkeit, Schwellwerte dynamisch zu setzen, machen ihn zu einer flexiblen Lösung für vielfältige Zähl‑ und Überwachungsaufgaben.