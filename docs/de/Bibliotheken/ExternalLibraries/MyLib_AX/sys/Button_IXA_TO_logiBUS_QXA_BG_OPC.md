# Button_IXA_TO_logiBUS_QXA_BG_OPC

![Button_IXA_TO_logiBUS_QXA_BG_OPC_network](./Button_IXA_TO_logiBUS_QXA_BG_OPC_network.svg)

* * * * * * * * * *

## Einleitung

`Button_IXA_TO_logiBUS_QXA_BG_OPC` ist der wiederverwendbare Baustein für **einen einzelnen digitalen Ausgang**, der sowohl über einen VT-Taster als auch über OPC-UA (Web-Client) geschaltet werden kann — inklusive VT-Statusanzeige. Er wird 12-fach parametrisiert in [`InputOutputTesterButton_DIDO_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md) instanziiert.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Button_IXA_TO_logiBUS_QXA_BG_OPC

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **Button_IXA**: `isobus::UT::io::Button::Button_IXA` — VT-Taster, `QI=TRUE`, `u16ObjId` identifiziert die VT-Taste.
    - **AX_RF_TRIG_BT** / **AX_RF_TRIG_OPC**: je `adapter::events::unidirectional::AX_RF_TRIG` — erkennen echte Flankenwechsel (steigend `ER`/fallend `EF`) an der VT-Taste bzw. am OPC-UA-Subscribe-Wert, statt jeden Wert blind durchzureichen.
    - **AX_SR**: `adapter::events::unidirectional::AX_SR` — gemeinsames Set/Reset-Flipflop für beide Quellen; entkoppelt die Rückkopplung zwischen Publish und Subscribe (siehe Technische Besonderheiten).
    - **AX_SPLIT_3**: `adapter::events::unidirectional::AX_SPLIT_3` — verteilt den Flipflop-Ausgang auf drei Ziele.
    - **logiBUS_QXA**: `logiBUS::io::DQ::logiBUS_QXA` — physischer digitaler Ausgang, `QI=TRUE`.
    - **GreenWhiteBackground1_AX** (SubApp, `MyLib::sys`): VT-Hintergrundfarbe passend zum Ausgangszustand.
    - **AX_SUBSCRIBE_1** / **AX_PUBLISH_1**: `adapter::net::AX_SUBSCRIBE_1`/`AX_PUBLISH_1` — OPC-UA-Lese-/Schreibzugriff, beide `QI=TRUE`.
- **Funktionsweise**: Zwei unabhängige Schaltquellen (VT-Taster, OPC-UA-Schreibzugriff) werden über je eine Flankenerkennung auf ein gemeinsames Set/Reset-Flipflop geführt, dessen Ausgang gleichzeitig den physischen Ausgang, die VT-Statusfarbe und das OPC-UA-Echo speist.

## Programmablauf und Verbindungen

1. **VT-Taster-Pfad**: `Button_IXA.IN` (Adapter) → `AX_RF_TRIG_BT.QI` → `AX_RF_TRIG_BT.ER`/`.EF` → `AX_SR.S`/`.R`.
2. **OPC-UA-Pfad**: `AX_SUBSCRIBE_1.OUT` (Adapter, Web-Schreibzugriff) → `AX_RF_TRIG_OPC.QI` → `AX_RF_TRIG_OPC.ER`/`.EF` → `AX_SR.S`/`.R`.
3. **Gemeinsamer Zustand**: `AX_SR.Q` → `AX_SPLIT_3.IN` → `AX_SPLIT_3.OUT1` → `logiBUS_QXA.OUT` (physischer Ausgang), `AX_SPLIT_3.OUT2` → `GreenWhiteBackground1_AX.DI1` (VT-Statusfarbe), `AX_SPLIT_3.OUT3` → `AX_PUBLISH_1.IN` (OPC-UA-Echo an den Web-Client).
4. **Initialisierungskette**: `AX_SUBSCRIBE_1.INITO` → `AX_PUBLISH_1.INIT` (ausgeblendete Verbindung) — stellt sicher, dass der Publish-Adapter erst initialisiert wird, nachdem der Subscribe-Adapter bereit ist.
5. **Parameter**: `u16ObjId` → `Button_IXA.u16ObjId` und `GreenWhiteBackground1_AX.u16ObjId`; `Output` → `logiBUS_QXA.Output`; `ID_READ` → `AX_SUBSCRIBE_1.ID`; `ID_WRITE` → `AX_PUBLISH_1.ID`.

## Technische Besonderheiten

- **Flankenerkennung statt Wert-Durchleitung**: `AX_RF_TRIG` sorgt dafür, dass nur echte Zustandswechsel (nicht jeder Schreibzugriff mit demselben Wert) das Flipflop auslösen — wichtig, damit wiederholte OPC-UA-Schreibzugriffe mit unverändertem Wert nicht versehentlich toggeln.
- **⚠️ Vermeidung eines OPC-UA-Feedback-Loops**: `AX_PUBLISH_1` und `AX_SUBSCRIBE_1` bedienen denselben OPC-UA-Knoten. Eine naive Verdrahtung (Subscribe-Wert direkt auf Publish durchreichen) würde einen Event-Storm erzeugen: Jede eigene Veröffentlichung erscheint für das eigene Subscribe wie eine externe Änderung und löst erneut eine Indikation aus. Das `AX_SR`-Flipflop durchbricht diese Schleife, da es nur auf echte Set/Reset-Flankenereignisse reagiert, nicht auf den durchlaufenden Wert selbst.
- **`RSP`-Event von `AX_SUBSCRIBE_1` ist wirkungslos**: Quellcode-geprüft in FORTE (`CCommFB::sendData()`, `commfb.cpp`) — für den Service-Typ *Subscriber* ist der `RSP`-Zweig ein kompletter No-Op, das Event-Paar `INIT`/`RSP` existiert nur, weil `CCommFB` die gemeinsame Basisklasse aller "Responder"-artigen Dienst-FBs ist (z. B. `SERVER`, wo `RSP` real etwas auslöst).
- **Boot-Reihenfolge**: `AX_SUBSCRIBE_1.INITO` löst `AX_PUBLISH_1.INIT` aus, um Race Conditions beim Deployment zu vermeiden (vgl. dasselbe Muster im PWM-Beispiel `RampLimitFS_TO_logiBUS_QDA_PWM_OPC`).

## Anwendungsszenarien

- Jeder digitale Ausgang, der sowohl vor Ort (VT-Taster) als auch fernbedient (Web/OPC-UA) schaltbar sein soll, ohne dass die beiden Bedienwege sich gegenseitig stören oder einen Feedback-Loop erzeugen.

## Vergleich mit ähnlichen Bausteinen

Gegenüber dem Eingangs-Pendant [`logiBUS_IXA_BG_OPC`](./logiBUS_IXA_BG_OPC.md) kommt hier die zweite Schreibquelle (OPC-UA-Subscribe) sowie die Flankenerkennungs-/Flipflop-Kette zur Feedback-Loop-Vermeidung hinzu — ein Eingang hat nur eine Datenquelle (die physische Hardware) und braucht diese Entkopplung nicht.

## Zusammenfassung

`Button_IXA_TO_logiBUS_QXA_BG_OPC` löst das grundlegende Problem der bidirektionalen OPC-UA-Anbindung eines digitalen Ausgangs: zwei konkurrierende Schreibquellen (VT-Taster, Web) über Flankenerkennung auf ein gemeinsames Flipflop führen, dessen Zustand dann sicher — ohne Feedback-Loop — an Hardware, VT-Anzeige und OPC-UA-Echo verteilt wird. Dieses Muster ist Vorlage für alle späteren bidirektional angebundenen Bausteine dieses Trainingssystems.

## 🛠️ Zugehörige Übungen

- [InputOutputTesterButton_DIDO_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
