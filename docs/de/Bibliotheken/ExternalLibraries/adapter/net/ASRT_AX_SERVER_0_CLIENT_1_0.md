# ASRT_AX_SERVER_0_CLIENT_1_0

![ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASRT_AX_SERVER_0_CLIENT_1_0** ist ein Composite-Funktionsblock, der drei unabhängige entfernte OPC-UA-**Methodenaufrufe** (Set, Reset und Toggle) über je einen eigenen `SERVER_0`-Baustein empfängt und den resultierenden Zustand über `CLIENT_1_0` an einen entfernten Knoten zurückschreibt – alles hinter einem einzigen bidirektionalen **ASRT_AX-Adapter-Plug**. Er ist die serverseitige Gegenstelle zu [ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_SET`, `STATUS_RESET`, `STATUS_TOGGLE` und `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` aktualisiert, verbunden mit denselben Variablen

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang für alle vier internen Verbindungen
- **ID_SET** (WSTRING): Lokale Methodenadresse (ACTION=CREATE_METHOD) für den Set-Methodenaufruf
- **ID_RESET** (WSTRING): Lokale Methodenadresse (ACTION=CREATE_METHOD) für den Reset-Methodenaufruf
- **ID_TOGGLE** (WSTRING): Lokale Methodenadresse (ACTION=CREATE_METHOD) für den Toggle-Methodenaufruf
- **ID_STATE** (WSTRING): Remote-Ziel-Adresse (ACTION=WRITE) für den Zustand

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SET_SERVER`, `RESET_SERVER`, `TOGGLE_SERVER` und `STATE_CLIENT` aktuell alle `QO = TRUE` melden
- **STATUS_SET** (WSTRING): Statusinformationen von `SET_SERVER`
- **STATUS_RESET** (WSTRING): Statusinformationen von `RESET_SERVER`
- **STATUS_TOGGLE** (WSTRING): Statusinformationen von `TOGGLE_SERVER`
- **STATUS_STATE** (WSTRING): Statusinformationen von `STATE_CLIENT`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| S_R_T | adapter::types::bidirectional::ASRT_AX | Plug – Set/Reset/Toggle (Eingang), Zustand (Ausgang) | Empfangenes Set/Reset/Toggle, Zustand nach außen |

## Funktionsweise

1. Über das `INIT`-Ereignis werden nacheinander `SET_SERVER`, `RESET_SERVER`, `TOGGLE_SERVER` und `STATE_CLIENT` initialisiert. Nach allen vier Bestätigungen wird `INITO` nach außen gemeldet.
2. Ein entfernter Set-, Reset- bzw. Toggle-Aufruf auf dem jeweiligen `SERVER_0`-Baustein löst `S_R_T.SET`, `S_R_T.RESET` bzw. `S_R_T.TOGGLE` aus – alle drei werden also über den Adapter nach innen gemeldet.
3. Sobald die weiterverarbeitende Logik über den Adapter ein Rückmeldeereignis `S_R_T.EI1` mit Datum `S_R_T.DI1` liefert, taktet dies das interne **E_D_FF**-Flipflop, das den Wert übernimmt und stabil hält.
4. Der Ausgang `EO` des Flipflops löst `STATE_CLIENT.REQ` aus; der gepufferte Wert wird per OPC-UA-Write an den unter `ID_STATE` konfigurierten entfernten Knoten gesendet.
5. `AND_QO` (AND_BOOL_4) verundet die `QO`-Ausgänge aller vier internen Bausteine; jede Bestätigung löst zusätzlich `CNF` nach außen aus.

## Technische Besonderheiten

- **Vier Netzverbindungen hinter einem Adapter**: Drei `SERVER_0`-Instanzen (Set, Reset, Toggle) und ein `CLIENT_1_0` (Zustand) werden zu einer einzigen bidirektionalen ASRT_AX-Schnittstelle zusammengefasst.
- **Pufferung mit D-Flipflop**: Der über den Adapter gemeldete Rückmeldewert wird über ein internes `iec61499::events::E_D_FF` stabilisiert, bevor er per `CLIENT_1_0` verschickt wird.
- **Sequentielle Initialisierung**: `SET_SERVER` → `RESET_SERVER` → `TOGGLE_SERVER` → `STATE_CLIENT` (Composite-FBTypes verketten `INIT`/`INITO` seriell durch jede Instanz).
- **Kapselung**: Nach außen ist nur noch die ASRT_AX-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Alle vier Verbindungen (Set-, Reset-, Toggle-Server, Zustands-Client) sind aufgebaut.
3. **Empfangsaktiv**: Ein entfernter Set-, Reset- oder Toggle-Aufruf wird über den Adapter an die interne Logik gemeldet.
4. **Zustandsschreibvorgang**: Ein Rückmeldewert der internen Logik wird gepuffert und per Remote-Write an den konfigurierten Zielknoten gesendet.

## Anwendungsszenarien

- Entgegennahme entfernter Set/Reset/Toggle-Aufrufe und gleichzeitiges Zurückschreiben des resultierenden Zustands an einen anderen entfernten Knoten über eine einzige Adapterverbindung
- Serverseitiges Gegenstück zu [ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md) in verteilten Steuerungsarchitekturen

## Vergleich mit ähnlichen Bausteinen

- **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Die client-/aufrufende Gegenstelle.
- **[ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.md)**: Dasselbe Muster mit nur zwei empfangenden Servern (ohne Toggle).

## Fazit

**ASRT_AX_SERVER_0_CLIENT_1_0** bündelt drei empfangende Server (Set/Reset/Toggle) und einen zustandsschreibenden Client hinter einem einzigen bidirektionalen ASRT_AX-Adapter und bildet damit die serverseitige Entsprechung zu [ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md).
