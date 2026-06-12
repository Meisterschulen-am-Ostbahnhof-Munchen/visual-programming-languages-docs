# AX_AUI_SEL_AUI


![AX_AUI_SEL_AUI](./AX_AUI_SEL_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_AUI_SEL_AUI** realisiert eine binäre Auswahl (binary selection). Er wählt zwischen zwei 16-Bit-Eingangswerten (**IN0** und **IN1**) aus und gibt den ausgewählten Wert über einen standardisierten Ausgangsadapter aus. Die Auswahl wird durch ein boolesches Signal gesteuert, das über einen Eingangsadapter bereitgestellt wird. Der Baustein kombiniert die Funktionalität des IEC‑61131‑3‑Bausteins `F_SEL` mit modularen Adapterschnittstellen und eignet sich besonders für Steuerungsanwendungen mit wiederverwendbaren, gekapselten Verbindungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar          | Mit Daten      |
|------|-------|--------------------|----------------|
| EI0  | Event | Set IN0            | IN0            |
| EI1  | Event | Set IN1            | IN1            |

- **EI0**: Durch Senden eines Ereignisses an `EI0` wird der Wert von **IN0** aktualisiert (der mitgegebene Datenwert wird übernommen).  
- **EI1**: Analog zu `EI0` für **IN1**.

**Hinweis:** Die Ereignisse dienen der Aktualisierung der Eingangsdaten **vor** der eigentlichen Auswahl. Die Selektion selbst wird ausschließlich durch das Ereignis des Eingangsadapters **G** ausgelöst.

### **Ereignis-Ausgänge**

Keine direkten Ereignisausgänge vorhanden. Die Ergebnisweitergabe erfolgt über den Ausgangsadapter **OUT** (siehe Adapter).

### **Daten-Eingänge**

| Name | Typ  | Kommentar                         |
|------|------|-----------------------------------|
| IN0  | UINT | Erster auswählbarer Eingangswert |
| IN1  | UINT | Zweiter auswählbarer Eingangswert |

Beide Datenwerte sind vorzeichenlose 16‑Bit‑Ganzzahlen (UINT).

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Das Ergebnis wird über den Ausgangsadapter **OUT** bereitgestellt.

### **Adapter**

| Bezeichnung | Typ                              | Richtung | Kommentar          |
|-------------|----------------------------------|----------|--------------------|
| G           | `adapter::types::unidirectional::AX` | Socket   | Selektorsignal     |
| OUT         | `adapter::types::unidirectional::AUI`| Plug     | Ausgewählter Wert  |

- **Adapter G (Socket):**  
  Stellt ein Ereignis **E1** und ein Datum **D1** bereit.  
  - `G.D1` (BOOL) – Auswahlsignal: `TRUE` wählt **IN1**, `FALSE` wählt **IN0**.  
  - `G.E1` (Event) – Triggert die Auswahloperation.

- **Adapter OUT (Plug):**  
  Liefert ein Ereignis **E1** und ein Datum **D1**.  
  - `OUT.D1` (UINT) – Der ausgewählte Wert (IN0 oder IN1).  
  - `OUT.E1` (Event) – Signalisiert, dass ein neuer Ausgabewert anliegt.

## Funktionsweise

Der Baustein arbeitet als Kapselung des Standardbausteins `F_SEL` aus IEC 61131-3. Die interne Verdrahtung verbindet:

- `G.E1` → `F_SEL.REQ` (Start der Auswahl)  
- `IN0` → `F_SEL.IN0`  
- `IN1` → `F_SEL.IN1`  
- `G.D1` → `F_SEL.G` (Steuereingang)  
- `F_SEL.OUT` → `OUT.D1`  
- `F_SEL.CNF` → `OUT.E1`

**Ablauf:**

1. Die Eingangswerte **IN0** und **IN1** werden entweder statisch vorgegeben oder über die Ereignisse `EI0` / `EI1` aktualisiert.  
2. Ein Ereignis am Adapter **G** (Signal `G.E1`) startet die Selektion.  
3. Der interne `F_SEL` wertet das boolesche Signal `G.D1` aus:  
   - Ist `G.D1 = FALSE`: Ausgabe = **IN0**  
   - Ist `G.D1 = TRUE`:  Ausgabe = **IN1**  
4. Das Ergebnis wird auf `OUT.D1` gelegt und gleichzeitig das Ereignis `OUT.E1` ausgelöst, um nachgeschaltete Bausteine zu informieren.

Der Baustein realisiert damit eine zeitlich gesteuerte, ereignisgetriebene Zuweisung: Die Auswahl erfolgt nur auf ein äußeres Ereignis hin, wobei die Daten bereits vorliegen müssen.

## Technische Besonderheiten

- **Composite‑Baustein:** Der FB ist aus einem vorhandenen IEC‑61131‑3‑Baustein (`F_SEL`) aufgebaut – das erleichtert Wartung und Zertifizierung.  
- **Adapterbasierte Schnittstellen:** Die Verwendung der Adapter `AX` und `AUI` ermöglicht eine lose Kopplung und erleichtert den Austausch von Submodulen.  
- **Datentyp:** `UINT` (16 Bit) – geeignet für Zähler, Konfigurationswerte oder analoge Skalierungen.  
- **Lizenz:** Eclipse Public License 2.0 – erlaubt uneingeschränkte industrielle Nutzung.  
- **Keine internen Zustände:** Der Baustein ist rein kombinatorisch mit ereignisgesteuerter Ausgabe; es werden keine Zustände gespeichert.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Die Funktionsweise ist vollständig durch das Zusammenspiel der Ereignisse definiert:

1. **Warten auf Triggereingang** – Es liegt kein Ereignis an `G.E1` an.  
2. **Auswahl und Ausgabe** – Nach Eintreffen von `G.E1` wird innerhalb eines Verarbeitungsschritts das Ergebnis ermittelt und über `OUT` ausgegeben (Ereignis `OUT.E1`).  

Eine explizite Zustandsmaschine ist nicht erforderlich, da der interne `F_SEL` keine Verzögerungen oder Speicher besitzt.

## Anwendungsszenarien

- **Umschaltung zwischen Betriebsmodi:** Ein Steuersignal (z. B. über einen digitalen Eingang) wählt zwischen zwei Parametersätzen, etwa Geschwindigkeitsgrenzen oder Konfigurationswerten.  
- **MUX‑Funktion in Datenpfaden:** In einer Messkette kann zwischen zwei Sensorkanälen gewählt werden, ohne die gesamte Signalverarbeitung zu duplizieren.  
- **Fehlersichere Rückschaltung:** Fällt der primäre Wert aus, kann über ein logisches Signal auf einen Ersatzwert umgeschaltet werden.  
- **Anbindung an Adapter‑Netzwerke:** Dank der standardisierten Adapter `AX`/`AUI` lässt sich der Baustein nahtlos in bestehende modulare Steuerungsarchitekturen einfügen.

## Vergleich mit ähnlichen Bausteinen

| Baustein            | Beschreibung                                                                 |
|---------------------|-------------------------------------------------------------------------------|
| **`F_SEL`**         | Reine IEC‑61131‑3‑Funktion, keine Adapter – direkte Daten‑/Ereignis‑Anschlüsse. |
| **`AX_AUI_SEL_AUI`**| Gleiche Auswahlfunktion, aber gekapselt mit Adaptern für modulare Vernetzung. |
| **`MUX`‑Bausteine** | Oft mehr als zwei Eingänge (z. B. 4‑Kanal‑Multiplexer) – hier nur binäre Auswahl. |

Der AX_AUI_SEL_AUI bietet im Vergleich zu einem direkten `F_SEL` den Vorteil der standardisierten, adapterbasierten Ein- und Ausgabe, was die Wiederverwendbarkeit und Austauschbarkeit in komplexen Systemen erhöht.

## Fazit

Der Funktionsblock **AX_AUI_SEL_AUI** stellt eine robuste, IEC‑61131‑3‑konforme Lösung für die binäre Auswahl von 16‑Bit‑Daten dar. Seine adapterbasierte Schnittstelle erleichtert die Integration in modulare Steuerungsarchitekturen und macht ihn besonders geeignet für industrielle Automatisierungslösungen, bei denen Flexibilität und Standardisierung gefordert sind. Der ereignisgesteuerte Ablauf ermöglicht eine präzise zeitliche Steuerung der Umschaltung.