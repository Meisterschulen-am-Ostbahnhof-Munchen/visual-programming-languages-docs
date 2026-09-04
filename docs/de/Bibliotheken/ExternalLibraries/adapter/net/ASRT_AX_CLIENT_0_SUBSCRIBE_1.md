# ASRT_AX_CLIENT_0_SUBSCRIBE_1

![ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASRT_AX_CLIENT_0_SUBSCRIBE_1** ist ein Composite-Funktionsblock, der drei unabhängige entfernte OPC-UA-**Methodenaufrufe** (Set, Reset und Toggle) über je einen eigenen `CLIENT_0`-Baustein auslöst und den dazugehörigen Zustand über `SUBSCRIBE_1` zurückliest – alles hinter einem einzigen bidirektionalen **ASRT_AX-Adapter-Socket**. Er ist die um einen Zustandskanal erweiterte Variante von [ASRT_CLIENT_0](ASRT_CLIENT_0.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_SET`, `STATUS_RESET`, `STATUS_TOGGLE` und `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` aktualisiert, verbunden mit denselben Variablen

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang für alle vier internen Verbindungen
- **ID_SET** (WSTRING): Remote-Methodenadresse für den Set-Aufruf
- **ID_RESET** (WSTRING): Remote-Methodenadresse für den Reset-Aufruf
- **ID_TOGGLE** (WSTRING): Remote-Methodenadresse für den Toggle-Aufruf
- **ID_STATE** (WSTRING): Lokal überwachter Zustandsknoten (ACTION=READ)

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SET_CLIENT`, `RESET_CLIENT`, `TOGGLE_CLIENT` und `STATE_SUBSCRIBE` aktuell alle `QO = TRUE` melden
- **STATUS_SET** (WSTRING): Statusinformationen von `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Statusinformationen von `RESET_CLIENT`
- **STATUS_TOGGLE** (WSTRING): Statusinformationen von `TOGGLE_CLIENT`
- **STATUS_STATE** (WSTRING): Statusinformationen von `STATE_SUBSCRIBE`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| S_R_T | adapter::types::bidirectional::ASRT_AX | Socket – Set/Reset/Toggle (Ausgang), Zustand (Eingang) | Set/Reset/Toggle nach außen, Zustand zurück |

## Funktionsweise

1. Über das `INIT`-Ereignis werden nacheinander `SET_CLIENT`, `RESET_CLIENT`, `TOGGLE_CLIENT` und `STATE_SUBSCRIBE` initialisiert. Nach allen vier Bestätigungen wird `INITO` nach außen gemeldet.
2. `S_R_T.SET`, `S_R_T.RESET` bzw. `S_R_T.TOGGLE` lösen direkt die jeweils zugehörigen `CLIENT_0`-Methodenaufrufe aus.
3. Sobald `STATE_SUBSCRIBE` per `IND` einen neuen Zustandswert liefert, taktet dies das interne **E_D_FF**-Flipflop, das den Wert übernimmt und stabil hält.
4. Der Ausgang `EO` des Flipflops feuert `S_R_T.EI1` mit dem gepufferten Wert an `S_R_T.DI1` – der Zustand wird über denselben Adapter zurückgemeldet, über den auch Set/Reset/Toggle ausgelöst werden.
5. `AND_QO` (AND_BOOL_4) verundet die `QO`-Ausgänge aller vier internen Bausteine; jede Bestätigung löst zusätzlich `CNF` nach außen aus.

## Technische Besonderheiten

- **Vier Netzverbindungen hinter einem Adapter**: Drei `CLIENT_0`-Instanzen (Set, Reset, Toggle) und ein `SUBSCRIBE_1` (Zustand) werden zu einer einzigen bidirektionalen ASRT_AX-Schnittstelle zusammengefasst.
- **Pufferung mit D-Flipflop**: Der über `SUBSCRIBE_1` empfangene Zustand wird über ein internes `iec61499::events::E_D_FF` stabilisiert, bevor er über den Adapter zurückgemeldet wird.
- **Sequentielle Initialisierung**: `SET_CLIENT` → `RESET_CLIENT` → `TOGGLE_CLIENT` → `STATE_SUBSCRIBE` (Composite-FBTypes verketten `INIT`/`INITO` seriell durch jede Instanz).
- **Kapselung**: Nach außen ist nur noch die ASRT_AX-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Alle vier Verbindungen (Set, Reset, Toggle, Zustandsabo) sind aufgebaut.
3. **Sendeaktiv**: Ein am Adapter eintreffendes Set-, Reset- oder Toggle-Ereignis löst den entsprechenden Remote-Methodenaufruf aus.
4. **Zustandsaktualisierung**: Ein neuer Wert vom Abonnement wird gepuffert und über denselben Adapter zurückgemeldet.

## Anwendungsszenarien

- Fernauslösen von Set/Reset/Toggle auf einem entfernten Aktor und gleichzeitiges Rücklesen des resultierenden Zustands über eine einzige Adapterverbindung
- Reduktion von händischer CLIENT_0/SUBSCRIBE_1-Verdrahtung auf einen einzigen wiederverwendbaren Baustein

## Vergleich mit ähnlichen Bausteinen

- **[ASRT_CLIENT_0](ASRT_CLIENT_0.md)**: Dieselben drei Trigger, aber ohne Zustands-Rücklesung.
- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)**: Dasselbe Muster mit nur zwei Triggern (ohne Toggle).
- **[ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.md)**: Die serverseitige Gegenstelle.

## Fazit

**ASRT_AX_CLIENT_0_SUBSCRIBE_1** bündelt drei Remote-Trigger (Set/Reset/Toggle) und ein Zustands-Abonnement hinter einem einzigen bidirektionalen ASRT_AX-Adapter und macht damit händisch verdrahtete Kombinationen zu einem einzigen wiederverwendbaren Baustein.
