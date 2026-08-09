# AI_PUBLISH_1

![AI_PUBLISH_1](./AI_PUBLISH_1.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AI_PUBLISH_1** ist ein Composite-Funktionsblock, der den netzwerkbasierten `PUBLISH_1`-Funktionsblock aus der IEC 61499-Standardbibliothek kapselt und dessen Schnittstelle auf einen unidirektionalen **AI-Adapter** abbildet. Ein am Adapter-Socket `IN` anliegender **INT**-Wert wird über ein internes D-Flipflop (E_D_FF_ANY) gepuffert und anschließend über den konfigurierten Publish-Kanal an alle zugehörigen `SUBSCRIBE_1`-Empfänger gesendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI` und `ID`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO` und `STATUS`
- **CNF** (Event): Bestätigung, dass die Daten gesendet wurden, verbunden mit `QO` und `STATUS`

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang, aktiviert den Publish-Dienst
- **ID** (WSTRING): Identifikator des Publish-Kanals

### **Daten-Ausgänge**

- **QO** (BOOL): Qualifier-Ausgang, Status der Blockausführung
- **STATUS** (WSTRING): Statusinformationen als Unicode-String

### **Adapter**

| Adapter | Typ                          | Richtung | Beschreibung                    |
|---------|------------------------------|----------|---------------------------------|
| IN      | adapter::types::unidirectional::AI | Socket (Eingang) | Zu veröffentlichender INT-Wert |

## Funktionsweise

1. Über das `INIT`-Ereignis wird der interne `PUBLISH_1`-Block mit `QI` und `ID` initialisiert. Bei Erfolg quittiert er mit `INITO`.
2. Sobald der AI-Socket `IN` ein Ereignis auf `IN.E1` liefert, wird der gleichzeitig an `IN.D1` anliegende INT-Wert in das interne **E_D_FF_ANY**-Flipflop übernommen (`CLK` bzw. `D`).
3. Das Flipflop hält den Wert stabil an seinem Ausgang `Q` und erzeugt bei einer Wertänderung das Ereignis `EO`.
4. `EO` löst das Sendeereignis `REQ` des internen `PUBLISH_1`-Blocks aus; der gepufferte Wert `Q` wird über die Datenverbindung als `SD_1` übergeben und auf dem konfigurierten Kanal veröffentlicht.
5. Nach erfolgreichem Senden bestätigt der `PUBLISH_1`-Block mit `CNF`, das nach außen geführt wird.

## Technische Besonderheiten

- **Pufferung mit D-Flipflop**: Der zu sendende INT-Wert wird über ein internes `iec61499::events::E_D_FF_ANY` gepuffert. Dadurch wird verhindert, dass ein sich während der Verarbeitung ändernder Eingangswert den Sendevorgang stört.
- **Ereignisbasierte Entkopplung**: Durch das echte ereignisbasierte `E_D_FF_ANY` werden unmittelbare Rückkopplungsschleifen zwischen `PUBLISH_1` und `SUBSCRIBE_1` (z. B. auf demselben OPC-UA-Knoten) entkoppelt – der saubere Fix gegenüber dem Interim-Fix mit `AX_D_FF`.
- **Kapselung**: Die ursprüngliche Ereignis-/Daten-Schnittstelle von `PUBLISH_1` (inkl. `REQ`/`SD_1`) wird nach innen verlegt; nach außen ist nur noch die AI-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Der Block ist bereit, Daten über den konfigurierten Kanal zu veröffentlichen.
3. **Sendeaktiv**: Ein am AI-Socket eintreffendes Ereignis puffert den Wert und veranlasst das Senden über den internen `PUBLISH_1`-Block.

## Anwendungsszenarien

- **Netzwerkkopplung in AI-Anwendungen**: Senden von INT-Signalen (z. B. Schaltbefehle oder Statusbits) aus der Adapter-basierten Logik über Publish/Subscribe an entfernte Empfänger.
- **Event-Storm-Vermeidung**: Gemeinsam mit `AX_SUBSCRIBE_1` werden Rückkopplungen zwischen eigenen Veröffentlichungen und dem eigenen Abonnement entkoppelt.
- **Modulare Steuerungsarchitekturen**: Einbindung von verteilter Kommunikation in Bibliotheken, die durchgängig auf AI-Adapter setzen.

## Vergleich mit ähnlichen Bausteinen

- **PUBLISH_1**: Der reine Standardbaustein exponiert seine Schnittstelle als Events/Variablen (`REQ`, `SD_1`, ...). **AI_PUBLISH_1** kapselt diesen Baustein, puffert den Wert mit einem D-Flipflop (`E_D_FF_ANY`) und stellt nur noch den AI-Adapter bereit – dadurch ist die Schnittstelle erheblich kompakter und in Adapter-Netzwerke integrierbar.
- **AX_D_FF**: Puffert einen INT-Wert auf Adapter-Ebene, kennt aber keine Netzwerkfunktionalität. **AI_PUBLISH_1** vereint Puffern und Veröffentlichen in einem Baustein.

## Fazit

**AI_PUBLISH_1** verbindet die Publish/Subscribe-Kommunikation des Standardbausteins `PUBLISH_1` mit der Adapter-basierten INT-Verarbeitung. Die interne D-Flipflop-Pufferung stabilisiert den Sendewert und entkoppelt Rückkopplungsschleifen; die reduzierte AI-Schnittstelle macht den Baustein ideal für durchgängig adapterbasierte IEC 61499-Anwendungen.
