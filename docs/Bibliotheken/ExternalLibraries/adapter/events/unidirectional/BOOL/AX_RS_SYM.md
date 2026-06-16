# AX_RS_SYM


![AX_RS_SYM](./AX_RS_SYM.svg)

* * * * * * * * * *
## Einleitung
Der **AX_RS_SYM** ist ein ereignisgesteuerter, bistabiler Funktionsblock (RS‑Flip‑Flop) mit symmetrischem Start‑Up‑Verhalten. Er verfügt über zwei Ereigniseingänge `R` (Reset) und `S` (Set), die jeweils den Zustand des Ausgangs `Q` setzen. Der Ausgang wird als unidirektionaler Adapter bereitgestellt, über den sowohl ein Datenwert (D1) als auch ein Ereignis (E1) übertragen werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `R` | Event | Setzt den Ausgang `Q.D1` auf `FALSE` und feuert `Q.E1` |
| `S` | Event | Setzt den Ausgang `Q.D1` auf `TRUE` und feuert `Q.E1` |

### **Ereignis-Ausgänge**
Der FB besitzt keine eigenen Ereignis-Ausgänge. Das Ereignis wird über den Adapter `Q` mittels `Q.E1` ausgegeben.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Der FB besitzt keine separaten Daten-Ausgänge. Der aktuelle Zustand wird über den Adapter `Q` als `Q.D1` (vom Typ BOOL) bereitgestellt.

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `Q` | `adapter::types::unidirectional::AX` | Bietet den Flip‑Flop‑Wert (D1) und ein Bestätigungsereignis (E1) |

## Funktionsweise
Der Funktionsblock realisiert ein klassisches RS‑Flip‑Flop:
- Bei Eintreffen des Ereignisses `S` wird der Ausgangswert `Q.D1` auf `TRUE` gesetzt und anschließend das Ereignis `Q.E1` ausgelöst.
- Bei Eintreffen des Ereignisses `R` wird der Ausgangswert `Q.D1` auf `FALSE` gesetzt und ebenfalls `Q.E1` ausgelöst.

Das Besondere ist das **symmetrische Start‑Up‑Verhalten**: Unmittelbar nach der Initialisierung befindet sich der FB im Zustand `START`. Wird als erstes Ereignis `S` empfangen, wechselt er in den Zustand `SET`; bei `R` wechselt er in den Zustand `RESET`. Damit ist von Anfang an ein definierter Zustand gegeben – es gibt keinen undefinierten oder zufälligen Anfangswert.

## Technische Besonderheiten
- **Symmetrisches Startverhalten**: Beide Eingänge `R` und `S` werden gleichberechtigt behandelt. Der FB hat keinen bevorzugten Anfangszustand; der erste ankommende Impuls bestimmt den Zustand.
- **Adapter‑basierte Ausgabe**: Der Ausgang ist als unidirektionaler Adapter realisiert. Dies erlaubt eine flexible Weiterverwendung des Wertes und des Ereignisses in komplexeren Strukturen.
- **Kein undefinierter Zustand**: Durch die Zustandsmaschine mit drei Zuständen (START, SET, RESET) wird vermieden, dass der FB nach dem Hochlauf in einem unbekannten oder metastabilen Zustand verharrt.

## Zustandsübersicht
Die interne Zustandsmaschine besteht aus folgenden Zuständen und Transitionen:

| Zustand | Bedeutung | Aktion bei Eintritt |
|---------|-----------|---------------------|
| START | Initialzustand nach dem Einschalten | Keine Aktion (wartet auf erstes Ereignis) |
| SET | Ausgang `Q.D1` ist `TRUE` | Führt Algorithmus `SET` aus: `Q.D1 := TRUE` und feuert `Q.E1` |
| RESET | Ausgang `Q.D1` ist `FALSE` | Führt Algorithmus `RESET` aus: `Q.D1 := FALSE` und feuert `Q.E1` |

**Transitionen:**
- `START` → `SET` bei Bedingung `S`
- `START` → `RESET` bei Bedingung `R`
- `SET` → `RESET` bei Bedingung `R`
- `RESET` → `SET` bei Bedingung `S`

## Anwendungsszenarien
- **Einfacher Schalter/Taster**: Ein Tastendruck setzt ein Merker‑Bit, ein zweiter Tastendruck setzt es zurück.
- **Verriegelungen** (z. B. in Sicherheitssteuerungen): Ein Set‑Impuls aktiviert eine Aktion, ein Reset‑Impuls deaktiviert sie.
- **Zustandssteuerung in Ablaufketten**: Als Gedächtnisbaustein für Ereignisse, die später ausgewertet werden.
- **Start‑Up‑Verhalten**: Besonders geeignet, wenn die Anlage nach dem Einschalten in einem definierten, aber noch nicht durch Vorlogik vorgegebenen Zustand starten soll.

## Vergleich mit ähnlichen Bausteinen
- **AX_RS**: Ein oft verwendetes RS‑Flip‑Flop mit asynchronem Set/Reset. Im Gegensatz zu `AX_RS_SYM` definiert die meisten Implementierungen einen bevorzugten Zustand (z. B. setzt das „R“-Signal beim Start den Ausgang zurück). `AX_RS_SYM` behandelt beide Ereignisse symmetrisch, was das Start‑Up‑Verhalten vorhersagbar macht.
- **AX_SR (Set‑dominant)** oder **AX_RS (Reset‑dominant)**: Diese Bausteine haben eine dominante Eingangsreihenfolge bei gleichzeitigem Eintreffen von S und R. Hier hingegen ist die Symmetrie nur auf das Startverhalten bezogen; während des Betriebs wird bei gleichzeitigen Ereignissen die Reihenfolge durch die EVENT‑Verarbeitung der Laufzeitumgebung bestimmt – der FB selbst kann keine Gleichzeitigkeit abfangen.
- **SR‑Flip‑Flop im IEC‑61131‑3**: (z. B. `SR` oder `RS`) arbeiten meist mit statischen Signalen. `AX_RS_SYM` ist rein event‑getrieben und daher für ereignisorientierte Steuerungen (z. B. 4diac‑IDE mit FORTE) optimiert.

## Fazit
Der **AX_RS_SYM** ist ein einfacher, aber flexibler ereignisgesteuerter RS‑Flip‑Flop‑Baustein. Seine Besonderheit liegt im symmetrischen Start‑Up‑Verhalten, das einen definierten Anfangszustand ohne feste Voreinstellung ermöglicht. Die Adapter‑Schnittstelle erleichtert die Einbindung in größere Systeme. Für Anwendungen, bei denen nach dem Hochlauf weder ein Setzen noch ein Zurücksetzen bevorzugt werden soll, ist dieser Baustein die ideale Wahl.