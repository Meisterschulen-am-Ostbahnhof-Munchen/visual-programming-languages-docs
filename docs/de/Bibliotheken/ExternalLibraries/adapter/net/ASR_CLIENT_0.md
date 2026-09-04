# ASR_CLIENT_0

![ASR_CLIENT_0](ASR_CLIENT_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASR_CLIENT_0** ist ein Composite-Funktionsblock, der zwei unabhängige entfernte OPC-UA-**Methodenaufrufe** (Set und Reset) über je einen eigenen `CLIENT_0`-Baustein auslöst, gesteuert über einen einzigen unidirektionalen **ASR-Adapter-Socket**. Er ist die um einen zweiten Trigger erweiterte Variante von [AE_CLIENT_0](AE_CLIENT_0.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_SET` und `STATUS_RESET`
- **CNF** (Event): Bestätigung, dass einer der Methodenaufrufe gesendet wurde, verbunden mit `QO`, `STATUS_SET` und `STATUS_RESET`

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang, öffnet (TRUE) bzw. schließt (FALSE) beide Verbindungen
- **ID_SET** (WSTRING): Remote-Methodenadresse für den Set-Aufruf
- **ID_RESET** (WSTRING): Remote-Methodenadresse für den Reset-Aufruf

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SET_CLIENT` und `RESET_CLIENT` aktuell beide `QO = TRUE` melden
- **STATUS_SET** (WSTRING): Statusinformationen von `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Statusinformationen von `RESET_CLIENT`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| S_R | adapter::types::unidirectional::ASR | Socket (Eingang) | Set/Reset |

## Funktionsweise

1. Über das `INIT`-Ereignis werden die internen `SET_CLIENT`- und `RESET_CLIENT`-Blöcke nacheinander (`INIT` → `INITO` → `INIT`) mit `QI` und ihrer jeweiligen `ID` initialisiert. Nach beiden Bestätigungen wird `INITO` nach außen gemeldet.
2. Ein Ereignis am Adapter-Socket `S_R.SET` löst direkt den internen `SET_CLIENT`-Methodenaufruf aus; `S_R.RESET` löst entsprechend `RESET_CLIENT` aus.
3. Beide `CLIENT_0`-Instanzen bestätigen unabhängig voneinander mit `CNF`, das jeweils nach außen weitergegeben wird.
4. Der Baustein `AND_QO` verundet die `QO`-Ausgänge beider `CLIENT_0`-Instanzen zu einem gemeinsamen `QO`.

## Technische Besonderheiten

- **Zwei parallele CLIENT_0-Instanzen**: Set und Reset werden über getrennte `CLIENT_0`-Bausteine (unterschiedliche `ID`, unabhängige Verbindungen) abgewickelt.
- **Sequentielle Initialisierung**: Die beiden internen Blöcke werden nacheinander initialisiert (`SET_CLIENT.INITO` → `RESET_CLIENT.INIT`), da Composite-FBTypes ihr `INIT`/`INITO` explizit durch jede Instanz seriell verketten müssen.
- **Kapselung**: Nach außen ist nur noch die ASR-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Beide Verbindungen sind aufgebaut, der Block ist bereit, Set- oder Reset-Aufrufe auszulösen.
3. **Sendeaktiv**: Ein am ASR-Socket eintreffendes Set- oder Reset-Ereignis löst den entsprechenden Remote-Methodenaufruf aus.

## Anwendungsszenarien

- Fernauslösen zweier unabhängiger entfernter Aktionen (Set/Reset) über einen einzigen Adapter, z. B. zum Schalten eines entfernten Aktors
- Netzwerkkopplung in ASR-Adapter-basierten Anwendungen

## Vergleich mit ähnlichen Bausteinen

- **[AE_CLIENT_0](AE_CLIENT_0.md)**: Dieselbe Grundstruktur mit nur einem Trigger statt zwei.
- **[ASRT_CLIENT_0](ASRT_CLIENT_0.md)**: Erweitert dasselbe Muster um einen dritten Trigger (Toggle).
- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)**: Kombiniert dieselben zwei `CLIENT_0`-Trigger zusätzlich mit einem `SUBSCRIBE_1`-Zustandskanal hinter einem bidirektionalen Adapter.

## Fazit

**ASR_CLIENT_0** bündelt zwei unabhängige Remote-Methodenaufrufe (Set/Reset) hinter einem einzigen ASR-Adapter-Socket und eignet sich damit für Anwendungen, in denen ein entfernter Aktor über zwei getrennte OPC-UA-Methoden geschaltet wird.
