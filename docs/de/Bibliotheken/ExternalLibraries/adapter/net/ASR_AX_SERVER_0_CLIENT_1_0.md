# ASR_AX_SERVER_0_CLIENT_1_0

![ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASR_AX_SERVER_0_CLIENT_1_0** ist ein Composite-Funktionsblock, der zwei unabhängige entfernte OPC-UA-**Methodenaufrufe** (Set und Reset) über je einen eigenen `SERVER_0`-Baustein empfängt und den resultierenden Zustand über `CLIENT_1_0` an einen entfernten Knoten zurückschreibt – alles hinter einem einzigen bidirektionalen **ASR_AX-Adapter-Plug**. Er ist die serverseitige Gegenstelle zu [ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_SET`, `STATUS_RESET` und `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` aktualisiert, verbunden mit denselben Variablen

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang für alle drei internen Verbindungen
- **ID_SET** (WSTRING): Lokale Methodenadresse (ACTION=CREATE_METHOD) für den Set-Methodenaufruf
- **ID_RESET** (WSTRING): Lokale Methodenadresse (ACTION=CREATE_METHOD) für den Reset-Methodenaufruf
- **ID_STATE** (WSTRING): Remote-Ziel-Adresse (ACTION=WRITE) für den Zustand

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SET_SERVER`, `RESET_SERVER` und `STATE_CLIENT` aktuell alle `QO = TRUE` melden
- **STATUS_SET** (WSTRING): Statusinformationen von `SET_SERVER`
- **STATUS_RESET** (WSTRING): Statusinformationen von `RESET_SERVER`
- **STATUS_STATE** (WSTRING): Statusinformationen von `STATE_CLIENT`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| S_R | adapter::types::bidirectional::ASR_AX | Plug – Set/Reset (Eingang), Zustand (Ausgang) | Empfangenes Set/Reset, Zustand nach außen |

## Funktionsweise

1. Über das `INIT`-Ereignis werden nacheinander `SET_SERVER`, `RESET_SERVER` und `STATE_CLIENT` initialisiert. Nach allen drei Bestätigungen wird `INITO` nach außen gemeldet.
2. Ein entfernter Set-Aufruf auf `SET_SERVER` löst `S_R.SET` aus, ein entfernter Reset-Aufruf auf `RESET_SERVER` löst `S_R.RESET` aus – beide werden also über den Adapter nach innen gemeldet.
3. Sobald die weiterverarbeitende Logik über den Adapter ein Rückmeldeereignis `S_R.EI1` mit Datum `S_R.DI1` liefert, taktet dies das interne **E_D_FF**-Flipflop, das den Wert übernimmt und stabil hält.
4. Der Ausgang `EO` des Flipflops löst `STATE_CLIENT.REQ` aus; der gepufferte Wert wird per OPC-UA-Write an den unter `ID_STATE` konfigurierten entfernten Knoten gesendet.
5. `AND_QO` (AND_BOOL_3) verundet die `QO`-Ausgänge aller drei internen Bausteine; jede Bestätigung löst zusätzlich `CNF` nach außen aus.

## Technische Besonderheiten

- **Drei Netzverbindungen hinter einem Adapter**: Zwei `SERVER_0`-Instanzen (Set, Reset) und ein `CLIENT_1_0` (Zustand) werden zu einer einzigen bidirektionalen ASR_AX-Schnittstelle zusammengefasst.
- **Pufferung mit D-Flipflop**: Der über den Adapter gemeldete Rückmeldewert wird über ein internes `iec61499::events::E_D_FF` stabilisiert, bevor er per `CLIENT_1_0` verschickt wird.
- **Sequentielle Initialisierung**: `SET_SERVER` → `RESET_SERVER` → `STATE_CLIENT` (Composite-FBTypes verketten `INIT`/`INITO` seriell durch jede Instanz).
- **Kapselung**: Nach außen ist nur noch die ASR_AX-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Alle drei Verbindungen (Set-Server, Reset-Server, Zustands-Client) sind aufgebaut.
3. **Empfangsaktiv**: Ein entfernter Set- oder Reset-Aufruf wird über den Adapter an die interne Logik gemeldet.
4. **Zustandsschreibvorgang**: Ein Rückmeldewert der internen Logik wird gepuffert und per Remote-Write an den konfigurierten Zielknoten gesendet.

## Anwendungsszenarien

- Entgegennahme entfernter Set/Reset-Aufrufe und gleichzeitiges Zurückschreiben des resultierenden Zustands an einen anderen entfernten Knoten über eine einzige Adapterverbindung
- Serverseitiges Gegenstück zu [ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md) in verteilten Steuerungsarchitekturen

## Vergleich mit ähnlichen Bausteinen

- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)**: Die client-/aufrufende Gegenstelle.
- **[AE_AX_SERVER_0_CLIENT_1_0](AE_AX_SERVER_0_CLIENT_1_0.md)**: Dasselbe Muster mit nur einem empfangenden Server statt zwei.
- **[ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.md)**: Erweitert dasselbe Muster um einen dritten empfangenden Server (Toggle).

## Fazit

**ASR_AX_SERVER_0_CLIENT_1_0** bündelt zwei empfangende Server (Set/Reset) und einen zustandsschreibenden Client hinter einem einzigen bidirektionalen ASR_AX-Adapter und bildet damit die serverseitige Entsprechung zu [ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md).
