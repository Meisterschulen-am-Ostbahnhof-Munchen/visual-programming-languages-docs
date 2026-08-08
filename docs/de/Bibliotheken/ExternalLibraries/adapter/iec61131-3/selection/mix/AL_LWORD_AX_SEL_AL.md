# AL_LWORD_AX_SEL_AL


![AL_LWORD_AX_SEL_AL](./AL_LWORD_AX_SEL_AL.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AL_LWORD_AX_SEL_AL` dient der binären Auswahl (Multiplexing) von 64-Bit-Datenworten (`LWORD`). Er ermöglicht es, ereignisgesteuert zwischen zwei Eingangssignalen auszuwählen und das ausgewählte Signal an einen Ausgang weiterzuleiten. Die Besonderheit dieses Bausteins liegt in seiner Mischarchitektur aus klassischen IEC 61499 Ereignis-/Datenschnittstellen und modernen, adapterbasierten Verbindungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
* **EI1**: Löst die Übernahme und Verarbeitung des direkt anliegenden Datenwerts `IN1` aus.

### **Ereignis-Ausgänge**
* *(Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`)*

### **Daten-Eingänge**
* **IN1** (LWORD): Auswählbarer Daten-Eingang (wird bei einem Ereignis an `EI1` eingelesen).

### **Daten-Ausgänge**
* *(Keine direkten Daten-Ausgänge vorhanden. Die Datenausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`)*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**
* **IN0** (Typ: `adapter::types::unidirectional::AL`): Unidirektionaler Adapter, welcher den ersten auswählbaren Eingangskanal bereitstellt. Er transportiert das Ereignis `E1` und die Daten `D1` (LWORD).
* **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Selektor-Adapter. Das empfangene Datenbit `D1` (BOOL) steuert, welcher Eingang ausgewählt wird.

#### **Plugs (Ausgangs-Schnittstellen)**
* **OUT** (Typ: `adapter::types::unidirectional::AL`): Unidirektionaler Ausgangs-Adapter, der das ausgewählte `LWORD`-Signal (`D1`) zusammen mit dem Trigger-Ereignis (`E1`) ausgibt.

---

## Funktionsweise
Der Baustein basiert intern auf einem FB-Netzwerk, das die asynchronen Eingangssignale synchronisiert und die Auswahllogik steuert:

1. **Datenspeicherung und Synchronisation:**
   Sowohl die Adapter-Eingänge (`IN0`, `G`) als auch der direkte Eingang (`IN1` über `EI1`) sind intern mit ereignisgesteuerten D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) verbunden. Bei jedem eintreffenden Ereignis an einem der Eingänge wird der entsprechende Datenwert zwischengespeichert.

2. **Auswahl-Logik (Multiplexer):**
   Der interne Baustein `F_SEL` (Standard-Auswahlglied) wertet das Steuersignal `G` (Selector) aus:
   * Ist das Signal des Adapters `G` auf **`FALSE`**, wird der Wert von **`IN0`** ausgewählt.
   * Ist das Signal des Adapters `G` auf **`TRUE`**, wird der Wert von **`IN1`** ausgewählt.

3. **Ereignis- und Datenausgabe:**
   Sobald sich ein Eingangswert oder das Auswahlsignal ändert und neu berechnet wurde, wird der ausgewählte Wert über das Ausgangs-Flip-Flop an den Adapter-Plug `OUT` übergeben. Gleichzeitig wird am Adapter das Ausgangsereignis `E1` ausgelöst.

---

## Technische Besonderheiten
* **Asymmetrisches Design:** Der Baustein kombiniert einen Adapter-Eingang (`IN0`) und einen klassischen Pin-Eingang (`IN1`). Dies ist besonders nützlich, wenn ein Signal aus einer adapterbasierten Busstruktur mit einem lokal in der Applikation erzeugten Einzelwert verglichen oder umgeschaltet werden soll.
* **Ereignisgesteuerte Datenkonsistenz:** Durch den Einsatz von `E_D_FF` (Event Double Flip-Flop) Bausteinen im internen Netzwerk wird sichergestellt, dass Datenänderungen nur dann verarbeitet werden, wenn das dazugehörige Ereignis eintrifft.

---

## Zustandsübersicht
Da es sich um ein reines Daten- und Ereignisfluss-Netzwerk (Composite FB) ohne internen Zustandsautomaten (ECC) handelt, lässt sich das Verhalten über folgende Signalpfade beschreiben:

* **Trigger über `G.E1`:** Aktualisiert den Selektor. Der Ausgang `OUT` spiegelt sofort den dem neuen Selektorzustand entsprechenden Eingang wider.
* **Trigger über `IN0.E1`:** Aktualisiert den Datenwert `IN0`. Wenn `G` aktiv auf `FALSE` steht, wird dieser neue Wert sofort an `OUT` ausgegeben.
* **Trigger über `EI1`:** Aktualisiert den Datenwert `IN1`. Wenn `G` aktiv auf `TRUE` steht, wird dieser neue Wert sofort an `OUT` ausgegeben.

---

## Anwendungsszenarien
* **Signalquellen-Umschaltung:** Umschalten zwischen einem Standard-Prozesswert (`IN0` via Adapter) und einem manuell vorgegebenen Ersatzwert/Konstante (`IN1`).
* **Betriebsartenwahl:** Routing von unterschiedlichen 64-Bit-Steuerworten oder Bitmasken je nach gewähltem Anlagenstatus (Automatik/Handbetrieb über Selektor `G`).
* **Schnittstellen-Konvertierung:** Einbindung von klassischen Steuerungssignalen in adapterbasierte Programmarchitekturen.

---

## Vergleich mit ähnlichen Bausteinen
* **F_SEL (Standard IEC 61131-3):** Der Standardbaustein `F_SEL` arbeitet rein datenflussorientiert und besitzt keine ereignisbasierte Steuerung oder Adapterunterstützung. `AL_LWORD_AX_SEL_AL` kapselt diese Kernfunktion und macht sie im IEC 61499-Kontext direkt für ereignisgesteuerte Adapter-Netzwerke nutzbar.
* **Standard-Kanalwähler (MUX):** Im Gegensatz zu einem Multiplexer, der viele Kanäle über Integer-Indizes auswählt, ist dieser Baustein als binärer 2-Kanal-Wähler hochoptimiert und benötigt lediglich ein Boolean-Signal zur Steuerung.

---

## Fazit
Der `AL_LWORD_AX_SEL_AL` ist ein spezialisierter Hilfsbaustein, der eine Brücke zwischen klassischen Daten-Eingängen und modernen, adapterbasierten Kommunikationsstrukturen schlägt. Durch die interne Zwischenspeicherung garantiert er eine deterministische und ereignisrichtige Signalweiterleitung von 64-Bit-Datenwerten.