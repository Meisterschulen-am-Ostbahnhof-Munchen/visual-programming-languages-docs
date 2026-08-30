# logiBUS_AI_IDA_OPC

![logiBUS_AI_IDA_OPC_network](./logiBUS_AI_IDA_OPC_network.svg)

* * * * * * * * * *
## Einleitung

`logiBUS_AI_IDA_OPC` bindet einen physischen Analogeingang (`logiBUS_AI_IDA`, Rohwert 0-4095, siehe [logiBUS_AI](../../../../hw/logiBUS/index.md) Hardware-Dokumentation) gleichzeitig an ein VT-Zahlenfeld (Rohwert), ein zweites VT-Zahlenfeld/Bargraph (Prozent) und an OPC-UA an: Rohwert (DWORD) und linear umgerechneter Prozentwert (REAL) werden beide separat per OPC-UA publiziert. Die Prozent-Umrechnung erfolgt über [`F_AI_RAW_TO_PERCENT_AD`](./F_AI_RAW_TO_PERCENT_AD.md).

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: logiBUS_AI_IDA_OPC

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **logiBUS_AI_IDA**: `logiBUS::io::AI::logiBUS_AI_IDA` — physischer Analogeingang, Rohwert 0-4095 (12 Bit), `AnalogInput_hysteresis=DWORD#0`, `TimeDelta=DWORD#250`, `TimeRateLimit=DWORD#100`, `QI=TRUE`.
    - **AD_SPLIT_2** (Typ `AD_SPLIT_3`): `adapter::events::unidirectional::AD_SPLIT_3` — verzweigt den DWORD-Adapterwert auf drei unabhängige Ausgänge (`OUT1..OUT3`).
    - **AD_PUBLISH_RAW** (Typ `AD_PUBLISH_1`): `adapter::net::AD_PUBLISH_1` — publiziert den Rohwert (DWORD) per OPC-UA, Zieladresse `ID_RAW_WRITE`, `QI=TRUE`.
    - **Q_NumericValue** (Typ `Q_NumericValue_AUDI`): `isobus::UT::Q::Q_NumericValue_AUDI` — schreibt den Rohwert in das VT-Zahlenfeld `u16ObjId_VALUEVAR`.
    - **F_AI_RAW_TO_PERCENT** (SubApp, Typ `F_AI_RAW_TO_PERCENT_AD`): `MyLib::sys::F_AI_RAW_TO_PERCENT_AD` — rechnet den Rohwert linear in Prozent um (siehe [F_AI_RAW_TO_PERCENT / F_AI_RAW_TO_PERCENT_AD](./F_AI_RAW_TO_PERCENT.md)).
    - **AR_PUBLISH_PERCENT** (Typ `AR_PUBLISH_1`): `adapter::net::AR_PUBLISH_1` — publiziert den Prozentwert (REAL) per OPC-UA, Zieladresse `ID_PERCENT_WRITE`, `QI=TRUE`.
    - **AD_TO_AUDI**: `adapter::conversion::unidirectional::AD_TO_AUDI` — wandelt den DWORD-Rohwert in UDINT für das VT-Zahlenfeld.
- **Funktionsweise**: Der Rohwert wird über `AD_SPLIT_2` verdreifacht: ein Zweig geht direkt an die OPC-UA-Publikation des Rohwerts, ein zweiter über `AD_TO_AUDI` an das VT-Rohwert-Zahlenfeld, ein dritter über `F_AI_RAW_TO_PERCENT_AD` zur Prozent-Umrechnung und anschließenden OPC-UA-Publikation.

## Programmablauf und Verbindungen

1. `Input` → `logiBUS_AI_IDA.Input`; `u16ObjId_VALUEVAR` → `Q_NumericValue.u16ObjId`; `ID_RAW_WRITE` → `AD_PUBLISH_RAW.ID`; `ID_PERCENT_WRITE` → `AR_PUBLISH_PERCENT.ID`.
2. `logiBUS_AI_IDA.IN` (Adapter) → `AD_SPLIT_2.IN` (Adapter).
3. `AD_SPLIT_2.OUT1` → `AD_PUBLISH_RAW.IN` (Rohwert-OPC-UA-Zweig).
4. `AD_SPLIT_2.OUT2` → `AD_TO_AUDI.AD_IN`; `AD_TO_AUDI.AUDI_OUT` → `Q_NumericValue.u32NewValue` (VT-Rohwert-Zweig).
5. `AD_SPLIT_2.OUT3` → `F_AI_RAW_TO_PERCENT.RAW_IN`; `F_AI_RAW_TO_PERCENT.PERCENT_OUT` → `AR_PUBLISH_PERCENT.IN` (Prozent-OPC-UA-Zweig).

## Technische Besonderheiten

- Rohwert-Bereich 0-4095 (12 Bit) — siehe hierzu die verifizierte AI-Hardwaredokumentation.
- Die Prozent-Umrechnung ist rein linear und unkalibriert (kein physikalisches Scaling), wie im Kommentar der SubApp-Definition ausdrücklich vermerkt.
- Drei unabhängige Konsumenten (zwei VT-Anzeigen + zwei OPC-UA-Publikationen) laufen parallel aus derselben `AD_SPLIT_3`-Verzweigung, wodurch alle Werte synchron denselben Erfassungszyklus abbilden.

## Anwendungsszenarien

- Analoger Prozesswert (z. B. Füllstand, Druck), der sowohl lokal am VT (Rohwert und Prozent) angezeigt als auch von einer übergeordneten Leitwarte per OPC-UA in beiden Darstellungen (roh und Prozent) gelesen werden soll.

## Zusammenfassung

Vollständige VT- und OPC-UA-Anbindung eines physischen Analogeingangs mit paralleler Rohwert- und Prozentdarstellung, aufgebaut aus Standard-Adapterbausteinen und der wiederverwendbaren Prozent-Umrechnung.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
