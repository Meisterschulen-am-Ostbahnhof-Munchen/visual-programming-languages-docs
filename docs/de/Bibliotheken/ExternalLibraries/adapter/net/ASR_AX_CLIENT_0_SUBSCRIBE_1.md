# ASR_AX_CLIENT_0_SUBSCRIBE_1

![ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASR_AX_CLIENT_0_SUBSCRIBE_1** ist ein Composite-Funktionsblock, der zwei unabhängige entfernte OPC-UA-**Methodenaufrufe** (Set und Reset) über je einen eigenen `CLIENT_0`-Baustein auslöst und den dazugehörigen Zustand über `SUBSCRIBE_1` zurückliest – alles hinter einem einzigen bidirektionalen **ASR_AX-Adapter-Socket**. Er ist die um einen Zustandskanal erweiterte Variante von [ASR_CLIENT_0](ASR_CLIENT_0.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_SET`, `STATUS_RESET` und `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` aktualisiert, verbunden mit denselben Variablen

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang für alle drei internen Verbindungen
- **ID_SET** (WSTRING): Remote-Methodenadresse für den Set-Aufruf
- **ID_RESET** (WSTRING): Remote-Methodenadresse für den Reset-Aufruf
- **ID_STATE** (WSTRING): Lokal überwachter Zustandsknoten (ACTION=READ)

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SET_CLIENT`, `RESET_CLIENT` und `STATE_SUBSCRIBE` aktuell alle `QO = TRUE` melden
- **STATUS_SET** (WSTRING): Statusinformationen von `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Statusinformationen von `RESET_CLIENT`
- **STATUS_STATE** (WSTRING): Statusinformationen von `STATE_SUBSCRIBE`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| S_R | adapter::types::bidirectional::ASR_AX | Socket – Set/Reset (Ausgang), Zustand (Eingang) | Set/Reset nach außen, Zustand zurück |

## Funktionsweise

1. Über das `INIT`-Ereignis wird zuerst `STATE_SUBSCRIBE` initialisiert, danach nacheinander `SET_CLIENT` und `RESET_CLIENT`. Nach allen Bestätigungen wird `INITO` nach außen gemeldet.
2. `S_R.SET` bzw. `S_R.RESET` lösen direkt die Methodenaufrufe `SET_CLIENT.REQ` bzw. `RESET_CLIENT.REQ` aus.
3. Sobald `STATE_SUBSCRIBE` per `IND` einen neuen Zustandswert liefert, taktet dies das interne **E_D_FF**-Flipflop, das den Wert übernimmt und stabil hält.
4. Der Ausgang `EO` des Flipflops feuert `S_R.EI1` mit dem gepufferten Wert an `S_R.DI1` – der Zustand wird über denselben Adapter zurückgemeldet, über den auch Set/Reset ausgelöst werden.
5. `AND_QO` (AND_BOOL_3) verundet die `QO`-Ausgänge aller drei internen Bausteine; jede Bestätigung löst zusätzlich `CNF` nach außen aus.

## Technische Besonderheiten

- **Drei Netzverbindungen hinter einem Adapter**: Zwei `CLIENT_0`-Instanzen (Set, Reset) und ein `SUBSCRIBE_1` (Zustand) werden zu einer einzigen bidirektionalen ASR_AX-Schnittstelle zusammengefasst.
- **Pufferung mit D-Flipflop**: Der über `SUBSCRIBE_1` empfangene Zustand wird über ein internes `iec61499::events::E_D_FF` stabilisiert, bevor er über den Adapter zurückgemeldet wird.
- **Sequentielle Initialisierung**: `STATE_SUBSCRIBE` → `SET_CLIENT` → `RESET_CLIENT` (Composite-FBTypes verketten `INIT`/`INITO` seriell durch jede Instanz).
- **Kapselung**: Nach außen ist nur noch die ASR_AX-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Alle drei Verbindungen (Set, Reset, Zustandsabo) sind aufgebaut.
3. **Sendeaktiv**: Ein am Adapter eintreffendes Set- oder Reset-Ereignis löst den entsprechenden Remote-Methodenaufruf aus.
4. **Zustandsaktualisierung**: Ein neuer Wert vom Abonnement wird gepuffert und über denselben Adapter zurückgemeldet.

## Anwendungsszenarien

- Fernauslösen von Set/Reset auf einem entfernten Aktor und gleichzeitiges Rücklesen des resultierenden Zustands über eine einzige Adapterverbindung
- Reduktion von händischer CLIENT_0/SUBSCRIBE_1-Verdrahtung auf einen einzigen wiederverwendbaren Baustein

## Vergleich mit ähnlichen Bausteinen

- **[ASR_CLIENT_0](ASR_CLIENT_0.md)**: Dieselben zwei Trigger, aber ohne Zustands-Rücklesung.
- **[AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md)**: Dasselbe Muster mit nur einem Trigger statt zwei.
- **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Erweitert dasselbe Muster um einen dritten Trigger (Toggle).
- **[ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.md)**: Die serverseitige Gegenstelle.

## Fazit

**ASR_AX_CLIENT_0_SUBSCRIBE_1** bündelt zwei Remote-Trigger (Set/Reset) und ein Zustands-Abonnement hinter einem einzigen bidirektionalen ASR_AX-Adapter und macht damit händisch verdrahtete Kombinationen zu einem einzigen wiederverwendbaren Baustein.
