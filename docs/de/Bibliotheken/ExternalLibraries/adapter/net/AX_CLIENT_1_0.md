# AX_CLIENT_1_0

![AX_CLIENT_1_0](./AX_CLIENT_1_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_CLIENT_1_0** ist ein Composite-Funktionsblock, der den netzwerkbasierten `CLIENT_1_0`-Funktionsblock aus der IEC 61499-Standardbibliothek kapselt und dessen Schnittstelle auf einen unidirektionalen **AX-Adapter** abbildet. Ein am Adapter-Socket `IN` anliegender **BOOL**-Wert wird über ein internes D-Flipflop (E_D_FF) gepuffert und anschließend über `CLIENT_1_0` als OPC-UA-**Write** an den unter `ID` konfigurierten entfernten Knoten gesendet.

Im Unterschied zu **AX_PUBLISH_1** (lokales Publish/Subscribe) schreibt `CLIENT_1_0` aktiv auf einen **entfernten** Server – laut der OPC-UA-Adressierungstabelle in `opcua.adoc` ist das der korrekte Baustein für ein Remote-`WRITE`, während `PUBLISH_1`/`AX_PUBLISH_1` nur lokal veröffentlichen können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI` und `ID`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO` und `STATUS`
- **CNF** (Event): Bestätigung, dass die Daten gesendet wurden, verbunden mit `QO` und `STATUS`

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang, öffnet (TRUE) bzw. schließt (FALSE) die Verbindung zum Server
- **ID** (WSTRING): Identifikator der Verbindung (OPC-UA-Adresse des Zielknotens, z. B. `opc_ua[WRITE;opc.tcp://192.168.1.12:4840#;...]`)

### **Daten-Ausgänge**

- **QO** (BOOL): Qualifier-Ausgang, Verbindungsstatus
- **STATUS** (WSTRING): Statusinformationen als Unicode-String

### **Adapter**

| Adapter | Typ                          | Richtung | Beschreibung          |
|---------|------------------------------|----------|------------------------|
| IN      | adapter::types::unidirectional::AX | Socket (Eingang) | Zu sendender BOOL-Wert |

## Funktionsweise

1. Über das `INIT`-Ereignis wird der interne `CLIENT_1_0`-Block mit `QI` und `ID` initialisiert; er baut die Verbindung zum entfernten Server auf. Bei Erfolg quittiert er mit `INITO`.
2. Sobald der AX-Socket `IN` ein Ereignis auf `IN.E1` liefert, wird der gleichzeitig an `IN.D1` anliegende BOOL-Wert in das interne **E_D_FF**-Flipflop übernommen (`CLK` bzw. `D`).
3. Das Flipflop hält den Wert stabil an seinem Ausgang `Q` und erzeugt bei einer Wertänderung das Ereignis `EO`.
4. `EO` löst das Sendeereignis `REQ` des internen `CLIENT_1_0`-Blocks aus; der gepufferte Wert `Q` wird über die Datenverbindung als `SD_1` übergeben und per OPC-UA-Write an den Server gesendet.
5. Nach erfolgreichem Senden bestätigt der `CLIENT_1_0`-Block mit `CNF`, das nach außen geführt wird.

## Technische Besonderheiten

- **Pufferung mit D-Flipflop**: Der zu sendende BOOL-Wert wird über ein internes `iec61499::events::E_D_FF` gepuffert. Dadurch wird verhindert, dass ein sich während der Verarbeitung ändernder Eingangswert den Sendevorgang stört.
- **Remote-Write statt lokalem Publish**: `CLIENT_1_0` adressiert einen entfernten OPC-UA-Server direkt (ACTION=WRITE mit vollständigem ENDPOINT in der `ID`), im Gegensatz zu `PUBLISH_1`/`SUBSCRIBE_1`, die nur lokal auf demselben FORTE-Knoten funktionieren.
- **Kapselung**: Die ursprüngliche Ereignis-/Daten-Schnittstelle von `CLIENT_1_0` (inkl. `REQ`/`SD_1`) wird nach innen verlegt; nach außen ist nur noch die AX-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Die Verbindung zum entfernten Server ist aufgebaut, der Block ist bereit zu senden.
3. **Sendeaktiv**: Ein am AX-Socket eintreffendes Ereignis puffert den Wert und veranlasst den Remote-Write über den internen `CLIENT_1_0`-Block.

## Anwendungsszenarien

- **Fernsteuerung anderer Module**: Ein VT-Tastendruck auf einem Modul mit eigener ISOBUS/VT-Verbindung löst einen OPC-UA-Write auf ein anderes, entferntes Steuerungsmodul aus (z. B. STG1 schaltet einen Ausgang auf STG2–STG5).
- **Netzwerkkopplung in AX-Anwendungen**: Senden von Bool-Signalen (Schaltbefehle) aus der Adapter-basierten Logik direkt an einen entfernten OPC-UA-Server.
- **Modulare Steuerungsarchitekturen**: Einbindung von verteilter Fernsteuerung in Bibliotheken, die durchgängig auf AX-Adapter setzen.

## Vergleich mit ähnlichen Bausteinen

- **CLIENT_1_0**: Der reine Standardbaustein exponiert seine Schnittstelle als Events/Variablen (`REQ`, `SD_1`, ...). **AX_CLIENT_1_0** kapselt diesen Baustein, puffert den Wert mit einem D-Flipflop und stellt nur noch den AX-Adapter bereit.
- **AX_PUBLISH_1**: Strukturell identisch aufgebaut (gleiche Ereignisse/Variablen/Adapter), kapselt aber `PUBLISH_1` statt `CLIENT_1_0` – veröffentlicht also nur lokal, statt aktiv auf einen entfernten Knoten zu schreiben.

## Fazit

**AX_CLIENT_1_0** verbindet die verbindungsorientierte Remote-Write-Kommunikation des Standardbausteins `CLIENT_1_0` mit der Adapter-basierten Bool-Verarbeitung. Die interne D-Flipflop-Pufferung stabilisiert den Sendewert; die reduzierte AX-Schnittstelle macht den Baustein ideal, um in durchgängig adapterbasierten IEC 61499-Anwendungen einen entfernten OPC-UA-Server direkt zu schreiben.
