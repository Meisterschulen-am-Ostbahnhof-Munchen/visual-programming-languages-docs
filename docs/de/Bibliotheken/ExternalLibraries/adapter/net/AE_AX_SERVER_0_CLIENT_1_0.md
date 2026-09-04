# AE_AX_SERVER_0_CLIENT_1_0

![AE_AX_SERVER_0_CLIENT_1_0](AE_AX_SERVER_0_CLIENT_1_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_AX_SERVER_0_CLIENT_1_0** ist ein Composite-Funktionsblock, der einen entfernten OPC-UA-**Methodenaufruf** über `SERVER_0` empfängt und den resultierenden Zustand über `CLIENT_1_0` an einen entfernten Knoten zurückschreibt – beides hinter einem einzigen bidirektionalen **AE_AX-Adapter-Plug**. Er ist die serverseitige Gegenstelle zu [AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO`, `STATUS_TRIGGER` und `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` aktualisiert, verbunden mit `QO`, `STATUS_TRIGGER` und `STATUS_STATE`

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang für beide interne Verbindungen
- **ID** (WSTRING): Lokale Methodenadresse (ACTION=CREATE_METHOD) für den Trigger-Methodenaufruf (`SERVER_0_1`)
- **ID_STATE** (WSTRING): Remote-Ziel-Adresse (ACTION=WRITE) für den Zustand (`STATE_CLIENT`)

### **Daten-Ausgänge**

- **QO** (BOOL): TRUE nur wenn `SERVER_0_1` und `STATE_CLIENT` aktuell beide `QO = TRUE` melden
- **STATUS_TRIGGER** (WSTRING): Statusinformationen von `SERVER_0_1`
- **STATUS_STATE** (WSTRING): Statusinformationen von `STATE_CLIENT`

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| TRIGGER | adapter::types::bidirectional::AE_AX | Plug – Trigger (Eingang), Zustand (Ausgang) | Empfangenes Ereignis, Zustand nach außen |

## Funktionsweise

1. Über das `INIT`-Ereignis wird zuerst `SERVER_0_1` mit `QI` und `ID` initialisiert; nach dessen `INITO` wird `STATE_CLIENT` mit `QI` und `ID_STATE` initialisiert. Nach beiden Bestätigungen wird `INITO` nach außen gemeldet.
2. Ein entfernter Methodenaufruf auf `SERVER_0_1` erzeugt das Indikationsereignis `IND`, das direkt auf `TRIGGER.E1` gelegt wird – der Adapter meldet den Aufruf also nach innen an die weiterverarbeitende Logik.
3. Sobald die weiterverarbeitende Logik über den Adapter ein Rückmeldeereignis `TRIGGER.EI1` mit Datum `TRIGGER.DI1` liefert, taktet dies das interne **E_D_FF**-Flipflop, das den Wert übernimmt und stabil hält.
4. Der Ausgang `EO` des Flipflops löst `STATE_CLIENT.REQ` aus; der gepufferte Wert wird als `SD_1` übergeben und per OPC-UA-Write an den unter `ID_STATE` konfigurierten entfernten Knoten gesendet.
5. `AND_QO` (AND_BOOL_2) verundet die `QO`-Ausgänge von `SERVER_0_1` und `STATE_CLIENT`; jede Bestätigung löst zusätzlich `CNF` nach außen aus.

## Technische Besonderheiten

- **Zwei Netzverbindungen hinter einem Adapter**: `SERVER_0` (Empfang, Server-Rolle) und `CLIENT_1_0` (Zustand, Remote-Write) werden zu einer einzigen bidirektionalen AE_AX-Schnittstelle zusammengefasst.
- **Pufferung mit D-Flipflop**: Der über den Adapter gemeldete Rückmeldewert wird über ein internes `iec61499::events::E_D_FF` stabilisiert, bevor er per `CLIENT_1_0` verschickt wird.
- **Sequentielle Initialisierung**: `SERVER_0_1` wird vor `STATE_CLIENT` initialisiert (Composite-FBTypes verketten `INIT`/`INITO` seriell durch jede Instanz).
- **Kapselung**: Nach außen ist nur noch die AE_AX-Adapter-Schnittstelle sichtbar; `SERVER_0`s `IND` und `CLIENT_1_0`s `REQ`/`SD_1` bleiben intern.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Beide Verbindungen (Server und Zustands-Client) sind aufgebaut.
3. **Empfangsaktiv**: Ein entfernter Methodenaufruf wird über den Adapter an die interne Logik gemeldet.
4. **Zustandsschreibvorgang**: Ein Rückmeldewert der internen Logik wird gepuffert und per Remote-Write an den konfigurierten Zielknoten gesendet.

## Anwendungsszenarien

- Entgegennahme eines entfernten Trigger-Aufrufs und gleichzeitiges Zurückschreiben des resultierenden Zustands an einen anderen entfernten Knoten über eine einzige Adapterverbindung
- Serverseitiges Gegenstück zu [AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md) in verteilten Steuerungsarchitekturen

## Vergleich mit ähnlichen Bausteinen

- **[AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md)**: Die client-/aufrufende Gegenstelle – triggert aktiv statt zu empfangen, abonniert statt zu schreiben.
- **[AX_CLIENT_1_0](AX_CLIENT_1_0.md)**: Reiner Remote-Write ohne Empfangsseite.
- **[ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.md)** / **[ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.md)**: Erweitern dasselbe Muster auf 2 bzw. 3 parallele Empfangs-Server.

## Fazit

**AE_AX_SERVER_0_CLIENT_1_0** bündelt einen empfangenden Server und einen zustandsschreibenden Client hinter einem einzigen bidirektionalen AE_AX-Adapter und bildet damit die serverseitige Entsprechung zu [AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md).
