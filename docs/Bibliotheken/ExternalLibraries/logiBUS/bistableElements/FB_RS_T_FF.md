# FB_RS_T_FF


![FB_RS_T_FF](./FB_RS_T_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_RS_T_FF` realisiert einen bistabilen, reset-dominanten Latch mit zusätzlicher Toggle-Funktion. Er kombiniert die Eigenschaften eines RS-Flipflops (Setzen und Zurücksetzen) mit der Möglichkeit, den Ausgang bei jedem positiven Flankenwechsel des Taktsignals umzuschalten. Der Reset-Eingang hat dabei Priorität, gefolgt vom Set-Eingang und dann der Toggle-Funktion.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ` | Normaler Ausführungsanforderung – löst die Verarbeitung der Eingangssignale aus. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF` | Bestätigt die Ausführung nach erfolgter Berechnung des Ausgangs `Q1`. |

### **Daten-Eingänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| `S`      | BOOL  | Setzen – setzt den Ausgang `Q1` auf `TRUE`, sofern `R1` nicht gleichzeitig aktiv ist. |
| `R1`     | BOOL  | Reset (dominant) – setzt den Ausgang `Q1` auf `FALSE` und hat Vorrang vor `S` und Toggle. |
| `CLK`    | BOOL  | Clock – Taktgeber für die Toggle-Funktion; bei steigender Flanke wird `Q1` invertiert, wenn weder Reset noch Set aktiv sind. |

### **Daten-Ausgänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| `Q1`     | BOOL  | Ausgang des Latch – zeigt den aktuellen gespeicherten Zustand an. |

### **Adapter**
Der Funktionsblock besitzt keine Adapter-Schnittstellen.

## Funktionsweise
Bei jedem Ereignis `REQ` wird der Algorithmus abgearbeitet:
- **Reset dominant**: Falls `R1 = TRUE`, wird `Q1` sofort auf `FALSE` gesetzt – unabhängig von allen anderen Eingängen.
- **Set**: Falls `R1 = FALSE` und `S = TRUE`, wird `Q1` auf `TRUE` gesetzt.
- **Toggle**: Falls weder Reset noch Set aktiv sind (`R1 = FALSE`, `S = FALSE`), wird der Toggle-Mechanismus ausgelöst: Wenn `CLK` den Wert `TRUE` annimmt und eine steigende Flanke erkannt wird (d.h. `CLK` war beim vorherigen Aufruf `FALSE`, gespeichert in der internen Variable `EDGE`), dann wird `Q1` invertiert (`Q1 := NOT Q1`).
- Anschließend wird die interne Variable `EDGE` auf den aktuellen Wert von `CLK` gesetzt, um Flanken für den nächsten Aufruf zu erkennen.

Der Algorithmus wird wie folgt im ST-Code umgesetzt:
```structured text
IF R1 THEN
    Q1 := BOOL#FALSE;
ELSIF S THEN
    Q1 := BOOL#TRUE;
ELSIF CLK AND NOT EDGE THEN
    Q1 := NOT Q1;
END_IF;
EDGE := CLK;
```

## Technische Besonderheiten
- **Reset-Dominanz**: Der R1-Eingang hat höchste Priorität; wird er gesetzt, überschreibt er sowohl Set- als auch Toggle-Befehle.
- **Flankenerkennung**: Der Toggle erfolgt nur bei einer steigenden Flanke von `CLK` (Übergang von `FALSE` auf `TRUE`), was durch die interne Variable `EDGE` realisiert wird.
- **Initialzustand**: Die interne `EDGE`-Variable ist mit `TRUE` initialisiert, sodass beim ersten Aufruf kein ungewollter Toggle ausgelöst wird, da die Bedingung `CLK AND NOT EDGE` sonst bei einem statischen `TRUE`-Pegel erfüllt wäre.
- **Datentyp**: Alle Ein- und Ausgänge sind vom Typ `BOOL`.

## Zustandsübersicht
Der Funktionsblock besitzt keinen expliziten Zustandsautomaten; der Zustand wird implizit durch die internen Variablen `Q1` und `EDGE` abgebildet. Eine Zustandstabelle fasst das Verhalten zusammen:

| Aktuelles `Q1` | `R1` | `S` | `CLK` (steigende Flanke) | Neues `Q1` |
|----------------|------|-----|---------------------------|-------------|
| x              | TRUE | x   | x                         | FALSE       |
| x              | FALSE| TRUE| x                         | TRUE        |
| x              | FALSE| FALSE| TRUE (und vorher FALSE)   | NOT Q1      |
| x              | FALSE| FALSE| FALSE oder keine Flanke   | unverändert |

## Anwendungsszenarien
- **Reset-dominante Steuerung** mit zusätzlicher Umschaltmöglichkeit, z. B. für manuelle Übersteuerung in Sicherheitskreisen.
- **Toggle-Funktion** bei Taktflanken, z. B. als Frequenzteiler oder Umschalter in digitalen Logikschaltungen.
- **Kombinierte Set/Reset/Toggle-Steuerung** in Automatisierungssystemen, wo ein Ausgang sowohl durch Sensorsignale gesetzt als auch durch einen Taster umgeschaltet werden kann.

## Vergleich mit ähnlichen Bausteinen
- **RS-Flipflop**: Reines RS ohne Toggle; `FB_RS_T_FF` erweitert es um eine Toggle-Funktion.
- **Toggle-Flipflop (T-FF)**: Reiner Toggle ohne Set/Reset; dieser Baustein kombiniert beide Funktionen, wobei der Toggle nur bei inaktiven Set/Reset ausgeführt wird.
- **JK-Flipflop**: Bietet ähnliche Flexibilität (Set, Reset, Toggle), benötigt aber zwei Ereigniseingänge (z. B. für J und K). `FB_RS_T_FF` vereinfacht die Schnittstelle auf einen Ereigniseingang und drei boolesche Daten.

## Fazit
`FB_RS_T_FF` ist ein vielseitiger Funktionsblock, der einen reset-dominanten Latch mit einer flankengetriggerten Toggle-Funktion kombiniert. Er eignet sich für Anwendungen, die sowohl feste Setz- und Rücksetzsignale als auch umschaltbare Zustandswechsel erfordern. Die klare Priorisierung (Reset > Set > Toggle) sowie die eingebaute Flankenerkennung machen ihn robust und einfach in Steuerungslogiken einsetzbar.