# ILOCK_T_FF


![ILOCK_T_FF](./ILOCK_T_FF.svg)

* * * * * * * * * *
## Einleitung
Der **ILOCK_T_FF** ist ein zusammengesetzter Funktionsblock (Composite FB), der einen sperrbaren Toggle-Flipflop (T-Flipflop) realisiert. Er erweitert ein einfaches T-Flipflop um eine bidirektionale Interlock-Schnittstelle, die das Verketten mehrerer Bausteine zu einer Verriegelungskette erlaubt. Der Baustein eignet sich vor allem für sicherheitsgerichtete Steuerungen, bei denen einmal geschaltete Zustände blockiert und an nachfolgende Glieder weitergegeben werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| CLK  | Ereignis | Triggersignal zum Umschalten des Ausgangs (Toggle). |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| EO   | Ereignis | Wird ausgelöst, sobald der interne Set‑/Reset‑Latch seinen Zustand geändert hat. |

### **Daten-Eingänge**
Keine Dateneingänge (die Steuerung erfolgt rein über Ereignisse und die Adapter).

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| Q    | BOOL | Aktueller Zustand des Flipflops (0 oder 1). |

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|-------------|
| ILOCK_IN | `adapter::types::bidirectional::AE2` | Sockel (Socket) | Empfängt und sendet Lock‑Signale von bzw. an vorgeschaltete Bausteine in der Kette. |
| ILOCK_OUT| `adapter::types::bidirectional::AE2` | Stecker (Plug)  | Sendet und empfängt Lock‑Signale von bzw. an nachgeschaltete Bausteine. |

## Funktionsweise
Der Baustein besteht intern aus einem **E_SWITCH** (Ereignisverzweiger) und einem **E_SR** (Set‑Reset‑Latch):

1. **Normalbetrieb (kein Lock)**  
   - Ein Ereignis am **CLK** wird an den **E_SWITCH** weitergeleitet.  
   - Der Ausgang **Q** des internen Latches dient als Steuersignal **G** für den **E_SWITCH**:  
     - Ist **Q = FALSE**, schaltet der **E_SWITCH** das Ereignis auf **E_SR.S** (Set) – **Q** wird **TRUE**.  
     - Ist **Q = TRUE**, schaltet der **E_SWITCH** das Ereignis auf **E_SR.R** (Reset) – **Q** wird **FALSE**.  
   - Dadurch wird bei jedem **CLK** ein sauberer Toggle (Flankenwechsel) ausgeführt.

2. **Lock‑Mechanismus (Interlock)**  
   - Über die Adapter **ILOCK_IN** und **ILOCK_OUT** können Lock‑Ereignisse in die Kette eingespeist werden.  
   - Ein Lock‑Ereignis (z.B. von einem vorgeschalteten Baustein über **ILOCK_IN.EO1** oder von einem nachgeschalteten über **ILOCK_OUT.EI1**) wird auf den **Reset** (**R**) des Latches gelegt.  
   - Dadurch wird **Q** sofort zurückgesetzt (**FALSE**). Der Toggle‑Vorgang wird unterbrochen, weil der **E_SWITCH** nun im Zustand **Q = FALSE** verharrt und bei nächstem **CLK** versuchen würde zu setzen – doch das Lock‑Signal kann erneut wirken.  
   - **Weiterleitung des Locks**: Jedes eingehende Lock‑Ereignis wird gleichzeitig an den jeweils anderen Adapterausgang weitergegeben:  
     - **ILOCK_IN.EO1** → **ILOCK_OUT.EO1** (an nachfolgende Bausteine)  
     - **ILOCK_OUT.EI1** → **ILOCK_IN.EI1** (an vorherige Bausteine)  
   - Dadurch breitet sich ein Lock in beide Richtungen aus (**Multi‑Hop Chain Propagation**).

3. **Ergebnis**  
   - Solange kein Lock anliegt, arbeitet der Baustein wie ein normaler T‑Flipflop.  
   - Sobald ein Lock aktiv wird, erzwingt er ein **Q = FALSE** und blockiert weitere Toggle‑Versuche, bis der Lock wieder aufgehoben wird.

## Technische Besonderheiten
- **Bidirektionale Lock‑Propagation**: Der Baustein kann Lock‑Signale sowohl aufnehmen als auch weitergeben, sodass eine Daisy‑Chain mehrerer ILOCK_T_FF möglich ist.
- **Rückkopplung des eigenen Zustands**: Das Ausgangssignal **Q** wird intern als Steuersignal für den **E_SWITCH** verwendet und bestimmt die Toggle‑Richtung.
- **Kein eigenes ECC**: Die gesamte Logik wird durch die beiden enthaltenen Basisbausteine (E_SR, E_SWITCH) abgebildet.

## Zustandsübersicht
Da der Baustein kein eigenes Zustandsdiagramm besitzt, ergeben sich die Zustände aus dem internen **E_SR**:

| Zustand **Q** | Bedeutung im Normalbetrieb | Bedeutung bei aktivem Lock |
|---------------|----------------------------|-----------------------------|
| 0             | Beim nächsten CLK wird auf 1 getoggelt. | Lock hat Q auf 0 gesetzt und hält es dort. |
| 1             | Beim nächsten CLK wird auf 0 getoggelt. | Lock setzt Q sofort auf 0 zurück. |

Ein aktiver Lock liegt vor, sobald eines der Adapter‑Ereignisse (ILOCK_IN.EO1 oder ILOCK_OUT.EI1) empfangen wurde. Der Lock wird solange gehalten, bis kein Lock‑Ereignis mehr anliegt (die genaue Auflösung hängt von der externen Signalsteuerung ab).

## Anwendungsszenarien
- **Sicherheitsverriegelungen in der Landtechnik** (z.B. Steuerung von Anbaugeräten): Ein einmal aktivierter Sperrzustand blockiert alle folgenden Schaltvorgänge und wird über die Kette an alle weiteren Komponenten weitergegeben.
- **Verkettete Not‑Aus‑Systeme**: Erlaubt das Fortpflanzen eines Stopp‑Signals entlang mehrerer Stationen, während jede Station selbst den Zustand verwaltet.
- **Protokolladaption für Interlock‑Signale**: Der Baustein kann als universelles Glied in einer Verriegelungskette eingesetzt werden, bei der der Ausgang Q einen Schaltvorgang repräsentiert.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften | Unterschied zum ILOCK_T_FF |
|----------|---------------|----------------------------|
| **T‑Flipflop (z.B. `E_TOGGLE`)** | Reine Toggle‑Funktion ohne Sperrlogik. | Fehlende Lock‑/Interlock‑Fähigkeit, kein Adapter‑Interface. |
| **RS‑Flipflop (z.B. `E_SR`)** | Set‑Reset mit zwei Eingängen, kein Toggle. | Kann mit externer Logik zum Toggle erweitert werden, aber ohne integrierte Lock‑Propagation. |
| **Einfacher Interlock‑Baustein** | Nur Lock‑Weitergabe, kein Toggle. | Der ILOCK_T_FF kombiniert Toggle und Lock‑Propagation in einem Baustein. |

## Fazit
Der **ILOCK_T_FF** vereint die Funktionalität eines getakteten T‑Flipflops mit einer effizienten, bidirektionalen Interlock‑Propagation. Durch die integrierte Multi‑Hop‑Weiterleitung eignet er sich ideal für vernetzte Sicherheitsketten, in denen ein Schaltzustand blockiert und gleichzeitig an die gesamte Kette weitergegeben werden muss. Sein kompakter Aufbau als Composite FB macht ihn leicht verständlich und wiederverwendbar.