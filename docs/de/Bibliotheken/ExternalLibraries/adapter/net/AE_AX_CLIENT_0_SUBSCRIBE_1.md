# AE_AX_CLIENT_0_SUBSCRIBE_1

![AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_AX_CLIENT_0_SUBSCRIBE_1** ist ein Composite-Funktionsblock, der einen entfernten OPC-UA-**Methodenaufruf** über `CLIENT_0` auslöst und den dazugehörigen Zustand über `SUBSCRIBE_1` zurückliest – beides hinter einem einzigen bidirektionalen **AE_AX-Adapter-Socket**. Er kollabiert damit das Muster „ein händisch verdrahteter `CLIENT_0` plus ein `SUBSCRIBE_1`“ zu einem einzigen Baustein mit einem Adapterport.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_TRIGGER` und `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` aktualisiert, verbunden mit `QO`, `STATUS_TRIGGER` und `STATUS_STATE`

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang für beide interne Verbindungen
- **ID** (WSTRING): Remote-Methodenadresse für den Trigger-Aufruf (`CLIENT_0_1`)
- **ID_STATE** (WSTRING): Lokal überwachter Zustandsknoten für `SUBSCRIBE_1` (ACTION=READ)

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `CLIENT_0_1` und `STATE_SUBSCRIBE` aktuell beide `QO = TRUE` melden
- **STATUS_TRIGGER** (WSTRING): Statusinformationen von `CLIENT_0_1`
- **STATUS_STATE** (WSTRING): Statusinformationen von `STATE_SUBSCRIBE`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| TRIGGER | adapter::types::bidirectional::AE_AX | Socket – Trigger (Ausgang), Zustand (Eingang) | Auslösendes Ereignis nach außen, Zustand zurück |

## Funktionsweise

1. Über das `INIT`-Ereignis wird zuerst `STATE_SUBSCRIBE` (`SUBSCRIBE_1`) mit `QI` und `ID_STATE` initialisiert; nach dessen `INITO` wird `CLIENT_0_1` mit `QI` und `ID` initialisiert. Nach beiden Bestätigungen wird `INITO` nach außen gemeldet.
2. Ein am Adapter-Socket eintreffendes Ereignis `TRIGGER.E1` löst direkt den Methodenaufruf `CLIENT_0_1.REQ` aus.
3. Sobald `STATE_SUBSCRIBE` per `IND` einen neuen Zustandswert an `RD_1` liefert, taktet dieses Ereignis das interne **E_D_FF**-Flipflop, das den Wert übernimmt und stabil hält.
4. Der Ausgang `EO` des Flipflops feuert `TRIGGER.EI1` mit dem gepufferten Wert an `TRIGGER.DI1` – der Zustand wird also über denselben Adapter zurückgemeldet, über den auch der Trigger nach außen geht.
5. `AND_QO` (AND_BOOL_2) verundet die `QO`-Ausgänge von `CLIENT_0_1` und `STATE_SUBSCRIBE`; jede Bestätigung (`CLIENT_0_1.CNF` oder `STATE_SUBSCRIBE.IND`) löst zusätzlich `CNF` nach außen aus.

## Technische Besonderheiten

- **Zwei Netzverbindungen hinter einem Adapter**: `CLIENT_0` (Trigger, Schreibrichtung) und `SUBSCRIBE_1` (Zustand, Leserichtung) werden zu einer einzigen bidirektionalen AE_AX-Schnittstelle zusammengefasst.
- **Pufferung mit D-Flipflop**: Der über `SUBSCRIBE_1` empfangene Zustand wird über ein internes `iec61499::events::E_D_FF` stabilisiert, bevor er über den Adapter zurückgemeldet wird.
- **Sequentielle Initialisierung**: `STATE_SUBSCRIBE` wird vor `CLIENT_0_1` initialisiert (Composite-FBTypes verketten `INIT`/`INITO` seriell durch jede Instanz).
- **Kapselung**: Nach außen ist nur noch die AE_AX-Adapter-Schnittstelle sichtbar; `CLIENT_0`s `REQ` und `SUBSCRIBE_1`s `IND`/`RD_1` bleiben intern.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Beide Verbindungen (Trigger und Zustandsabo) sind aufgebaut.
3. **Sendeaktiv**: Ein am Adapter eintreffendes Trigger-Ereignis löst den Remote-Methodenaufruf aus.
4. **Zustandsaktualisierung**: Ein neuer Wert vom Abonnement wird gepuffert und über denselben Adapter zurückgemeldet.

## Anwendungsszenarien

- Fernauslösen einer entfernten Aktion und gleichzeitiges Rücklesen des resultierenden Zustands über eine einzige Adapterverbindung, z. B. für ein Bedienelement, das sofort den tatsächlichen Zustand des entfernten Aktors anzeigt
- Reduktion von händischer CLIENT_0/SUBSCRIBE_1-Verdrahtung auf einen einzigen wiederverwendbaren Baustein

## Vergleich mit ähnlichen Bausteinen

- **[AE_CLIENT_0](AE_CLIENT_0.md)**: Reiner Trigger ohne Zustands-Rücklesung.
- **[AI_SUBSCRIBE_1](AI_SUBSCRIBE_1.md)**: Reines Zustands-Abonnement ohne Trigger-Funktion.
- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)** / **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Erweitern dasselbe Muster auf 2 bzw. 3 parallele Trigger.
- **[AE_AX_SERVER_0_CLIENT_1_0](AE_AX_SERVER_0_CLIENT_1_0.md)**: Die serverseitige Gegenstelle – empfängt statt zu triggern und schreibt statt zu abonnieren.

## Fazit

**AE_AX_CLIENT_0_SUBSCRIBE_1** bündelt einen Remote-Trigger und ein Zustands-Abonnement hinter einem einzigen bidirektionalen AE_AX-Adapter und macht damit händisch verdrahtete CLIENT_0/SUBSCRIBE_1-Kombinationen zu einem einzigen wiederverwendbaren Baustein.
