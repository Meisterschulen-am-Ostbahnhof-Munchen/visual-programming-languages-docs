# AUI_SUBSCRIBE_1

![AUI_SUBSCRIBE_1](./AUI_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AUI_SUBSCRIBE_1** ist ein Composite-Funktionsblock, der den netzwerkbasierten `SUBSCRIBE_1`-Funktionsblock aus der IEC 61499-Standardbibliothek kapselt und dessen Schnittstelle auf einen unidirektionalen **AUI-Adapter** abbildet. Er abonniert einen über die `ID` konfigurierten Publish-Kanal und stellt den empfangenen **UINT**-Wert gepuffert über einen D-Flipflop (E_D_FF_ANY) am Adapter-Plug `OUT` bereit. Damit lassen sich Netzkommunikation und UINT-Signalverarbeitung in der AUI-Adapter-Welt sauber verbinden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI` und `ID`
- **RSP** (Event): Response-Ereignis, verbunden mit `QI`

### **Ereignis-Ausgänge**
- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO` und `STATUS`

### **Daten-Eingänge**
- **QI** (BOOL): Qualifier-Eingang, aktiviert den Abonnement-Dienst
- **ID** (WSTRING): Identifikator des zu abonnierenden Publish-Kanals

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifier-Ausgang, Status der Blockausführung
- **STATUS** (WSTRING): Statusinformationen als Unicode-String

### **Adapter**

| Adapter | Typ                          | Richtung | Beschreibung                         |
|---------|------------------------------|----------|--------------------------------------|
| OUT     | adapter::types::unidirectional::AUI | Plug (Ausgang) | Gepufferter empfangener UINT-Wert |

## Funktionsweise
1. Über das `INIT`-Ereignis wird der interne `SUBSCRIBE_1`-Block mit `QI` und `ID` initialisiert. Bei Erfolg quittiert er mit `INITO`.
2. Der interne `SUBSCRIBE_1`-Block überwacht den konfigurierten Kanal. Sobald der zugehörige `PUBLISH_1`-Block Daten veröffentlicht, erzeugt er das Indikationsereignis `IND` und legt den empfangenen Wert an `RD_1` an.
3. `IND` taktet den internen **E_D_FF_ANY**-Flipflop (`CLK`), der den Wert von `RD_1` an seinem Dateneingang `D` übernimmt.
4. Der gespeicherte Wert erscheint stabil am Ausgang `Q` und wird über die Datenverbindung auf `OUT.D1` des AX-Plugs gelegt.
5. Das Ereignis `EO` des Flipflops wird auf den Ereignis-Ausgang `OUT.E1` gelegt, sodass nachgeschaltete Bausteine über die neue Information benachrichtigt werden.

## Technische Besonderheiten
- **Pufferung mit D-Flipflop**: Der empfangene UINT-Wert wird über ein internes `iec61499::events::E_D_FF_ANY` gepuffert und bleibt stabil am Ausgang, bis der nächste Wert empfangen wird. `EO` feuert nur bei einer Änderung von `Q`.
- **RSP ist ein No-Op bei Subscribern**: Laut Quellcode-Analyse von `4diac-forte` (`CCommFB::sendData()`) führt das `RSP`-Ereignis bei `SUBSCRIBE_1` (Service-Typ Subscriber) keine Aktion aus – der Zweig `!= e_Subscriber` wird übersprungen. Das Event-Input-Paar `INIT`/`RSP` wird nur für die Quittierung durchgeführt und ist für die Quittierung im Subscriber-Fall funktionslos. Es wird dennoch nach außen geführt, damit ein konfigurierbarer Anschluss besteht.
- **Kapselung**: Die ursprüngliche Ereignis-/Daten-Schnittstelle von `SUBSCRIBE_1` (inkl. `IND`/`RD_1`) wird nach innen verlegt; nach außen ist nur noch die AUI-Adapter-Schnittstelle sichtbar.

## Zustandsübersicht
1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Das Abonnement ist aktiv; der Block wartet auf Daten vom Publisher.
3. **Datenempfang**: Bei `IND` wird der empfangene UINT-Wert in das interne D-Flipflop übernommen und über `OUT` ausgegeben.

## Anwendungsszenarien
- **Netzwerkkopplung in AUI-Anwendungen**: Empfang von UINT-Signalen (z. B. Schaltbefehle oder Statusbits) über Publish/Subscribe und Weiterleitung über AUI-Adapter an die Adapter-basierte Logik.
- **Event-Storm-Vermeidung**: Gemeinsam mit `AX_PUBLISH_1` und einem echten ereignisbasierten `E_D_FF_ANY` lässt sich die Rückkopplung zwischen `SUBSCRIBE_1` und `PUBLISH_1` entkoppeln (sauberer Fix gegenüber dem Interim-Fix mit `AX_D_FF`).
- **Modulare Steuerungsarchitekturen**: Einbindung von verteilter Kommunikation in Bibliotheken, die durchgängig auf AUI-Adapter setzen.

## Vergleich mit ähnlichen Bausteinen
- **SUBSCRIBE_1**: Der reine Standardbaustein exponiert seine Schnittstelle als Events/Variablen (`IND`, `RD_1`, ...). **AUI_SUBSCRIBE_1** kapselt diesen Baustein, puffert den Wert mit einem D-Flipflop (`E_D_FF_ANY`) und stellt nur noch den AUI-Adapter bereit – dadurch ist die Schnittstelle erheblich kompakter und in Adapter-Netzwerke integrierbar.
- **AX_D_FF**: Puffert einen UINT-Wert auf Adapter-Ebene, kennt aber keine Netzwerkfunktionalität. **AUI_SUBSCRIBE_1** vereint Subscribing und Pufferung in einem Baustein.

## Fazit
**AUI_SUBSCRIBE_1** verbindet die Publish/Subscribe-Kommunikation des Standardbausteins `SUBSCRIBE_1` mit der Adapter-basierten UINT-Verarbeitung. Die interne D-Flipflop-Pufferung hält den empfangenen Wert stabil, bis neue Daten eintreffen, und die reduzierte AUI-Schnittstelle macht den Baustein ideal für durchgängig adapterbasierte IEC 61499-Anwendungen.
