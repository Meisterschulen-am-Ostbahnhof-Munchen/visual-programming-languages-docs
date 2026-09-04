# ASRT_CLIENT_0

![ASRT_CLIENT_0](ASRT_CLIENT_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASRT_CLIENT_0** ist ein Composite-Funktionsblock, der drei unabhängige entfernte OPC-UA-**Methodenaufrufe** (Set, Reset und Toggle) über je einen eigenen `CLIENT_0`-Baustein auslöst, gesteuert über einen einzigen unidirektionalen **ASRT-Adapter-Socket**. Er ist die um einen dritten Trigger erweiterte Variante von [ASR_CLIENT_0](ASR_CLIENT_0.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_SET`, `STATUS_RESET` und `STATUS_TOGGLE`
- **CNF** (Event): Bestätigung, dass einer der Methodenaufrufe gesendet wurde, verbunden mit denselben Statusvariablen

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang, öffnet (TRUE) bzw. schließt (FALSE) alle drei Verbindungen
- **ID_SET** (WSTRING): Remote-Methodenadresse für den Set-Aufruf
- **ID_RESET** (WSTRING): Remote-Methodenadresse für den Reset-Aufruf
- **ID_TOGGLE** (WSTRING): Remote-Methodenadresse für den Toggle-Aufruf

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SET_CLIENT`, `RESET_CLIENT` und `TOGGLE_CLIENT` aktuell alle `QO = TRUE` melden
- **STATUS_SET** (WSTRING): Statusinformationen von `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Statusinformationen von `RESET_CLIENT`
- **STATUS_TOGGLE** (WSTRING): Statusinformationen von `TOGGLE_CLIENT`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| S_R_T | adapter::types::unidirectional::ASRT | Socket (Eingang) | Set/Reset/Toggle |

## Funktionsweise

1. Über das `INIT`-Ereignis werden die internen `SET_CLIENT`-, `RESET_CLIENT`- und `TOGGLE_CLIENT`-Blöcke nacheinander (seriell verkettet über `INIT`/`INITO`) mit `QI` und ihrer jeweiligen `ID` initialisiert. Nach allen drei Bestätigungen wird `INITO` nach außen gemeldet.
2. Ein Ereignis am Adapter-Socket `S_R_T.SET`, `S_R_T.RESET` bzw. `S_R_T.TOGGLE` löst direkt den jeweils zugehörigen `CLIENT_0`-Methodenaufruf aus.
3. Alle drei `CLIENT_0`-Instanzen bestätigen unabhängig voneinander mit `CNF`, das jeweils nach außen weitergegeben wird.
4. Der Baustein `AND_QO` (AND_BOOL_3) verundet die `QO`-Ausgänge aller drei `CLIENT_0`-Instanzen zu einem gemeinsamen `QO`.

## Technische Besonderheiten

- **Drei parallele CLIENT_0-Instanzen**: Set, Reset und Toggle werden über getrennte `CLIENT_0`-Bausteine (unterschiedliche `ID`, unabhängige Verbindungen) abgewickelt.
- **Sequentielle Initialisierung**: Die drei internen Blöcke werden nacheinander initialisiert (`SET_CLIENT.INITO` → `RESET_CLIENT.INIT` → `TOGGLE_CLIENT.INIT`), da Composite-FBTypes ihr `INIT`/`INITO` explizit durch jede Instanz seriell verketten müssen.
- **Kapselung**: Nach außen ist nur noch die ASRT-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Alle drei Verbindungen sind aufgebaut, der Block ist bereit, Set-, Reset- oder Toggle-Aufrufe auszulösen.
3. **Sendeaktiv**: Ein am ASRT-Socket eintreffendes Ereignis löst den entsprechenden Remote-Methodenaufruf aus.

## Anwendungsszenarien

- Fernauslösen dreier unabhängiger entfernter Aktionen (Set/Reset/Toggle) über einen einzigen Adapter, z. B. zum Schalten eines entfernten Aktors mit zusätzlicher Toggle-Funktion
- Netzwerkkopplung in ASRT-Adapter-basierten Anwendungen

## Vergleich mit ähnlichen Bausteinen

- **[ASR_CLIENT_0](ASR_CLIENT_0.md)**: Dieselbe Grundstruktur mit nur zwei Triggern (ohne Toggle).
- **[AE_CLIENT_0](AE_CLIENT_0.md)**: Reduziert dasselbe Muster auf einen einzelnen Trigger.
- **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Kombiniert dieselben drei `CLIENT_0`-Trigger zusätzlich mit einem `SUBSCRIBE_1`-Zustandskanal hinter einem bidirektionalen Adapter.

## Fazit

**ASRT_CLIENT_0** bündelt drei unabhängige Remote-Methodenaufrufe (Set/Reset/Toggle) hinter einem einzigen ASRT-Adapter-Socket und eignet sich damit für Anwendungen, in denen ein entfernter Aktor über drei getrennte OPC-UA-Methoden geschaltet wird.
