# logiBUS_IXA_BG_OPC

![logiBUS_IXA_BG_OPC_network](./logiBUS_IXA_BG_OPC_network.svg)

* * * * * * * * * *
## Einleitung

`logiBUS_IXA_BG_OPC` ist der wiederverwendbare Baustein für **einen einzelnen digitalen Eingang** mit VT-Statusanzeige (Hintergrundfarbe) und OPC-UA-Publish. Er wird 8-fach parametrisiert in [`InputOutputTesterButton_DIDO_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md) instanziiert und unverändert auch im PWM-Beispiel [`InputOutputTesterButton_PWM_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md) für dessen 8 Eingänge wiederverwendet.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: logiBUS_IXA_BG_OPC

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **logiBUS_IXA**: `logiBUS::io::DI::logiBUS_IXA` — Adapter-basierter digitaler Eingang; Parameter `QI=TRUE`, `Input` identifiziert `Input_I1..I8`.
    - **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2` — verzweigt das eine Adapter-Signal von `logiBUS_IXA.IN` in zwei unabhängige Ziele.
    - **GreenWhiteBackground1_AX** (SubApp, `MyLib::sys`): setzt die VT-Hintergrundfarbe (Grün/Weiß) passend zum Eingangszustand.
    - **AX_PUBLISH_1**: `adapter::net::AX_PUBLISH_1` — OPC-UA-Publish-Adapter, `QI=TRUE`.
- **Funktionsweise**: Reiner Einweg-Datenfluss vom physischen Eingang zu zwei Anzeige-/Meldewegen — kein Rückschreiben möglich, da ein digitaler Eingang nicht extern gesetzt werden kann.

## Programmablauf und Verbindungen

1. `Input` (Parameter, identifiziert `Input_I1..I8`) → `logiBUS_IXA.Input` (Datenverbindung, ausgeblendet).
2. `u16ObjId` (VT-Objekt-ID der Statusanzeige) → `GreenWhiteBackground1_AX.u16ObjId`.
3. `ID_WRITE` (OPC-UA-Adresse) → `AX_PUBLISH_1.ID`.
4. **Adapterkette**: `logiBUS_IXA.IN` → `AX_SPLIT_2.IN` → `AX_SPLIT_2.OUT1` → `GreenWhiteBackground1_AX.DI1` (VT-Anzeige) und `AX_SPLIT_2.OUT2` → `AX_PUBLISH_1.IN` (OPC-UA-Publish).

## Technische Besonderheiten

- **AX_SPLIT_2 statt zweier Datenverbindungen**: Da ein Adapter-Ausgang nur an eine Stelle direkt verbunden werden kann, verzweigt `AX_SPLIT_2` das Signal für VT-Anzeige und OPC-UA-Publish.
- **Unidirektional**: Im Gegensatz zum Ausgangs-Pendant [`Button_IXA_TO_logiBUS_QXA_BG_OPC`](./Button_IXA_TO_logiBUS_QXA_BG_OPC.md) gibt es hier keinen `AX_SUBSCRIBE_1` — ein Eingang wird nicht vom Web aus geschrieben.

## Anwendungsszenarien

- Jede Übung mit digitalen Eingängen, die sowohl auf dem VT (Statusfarbe) als auch per OPC-UA (Web-Client) sichtbar sein sollen.

## Zusammenfassung

`logiBUS_IXA_BG_OPC` kapselt die Standard-Kombination "digitaler Eingang + VT-Statusfarbe + OPC-UA-Publish" in einem einzigen, mehrfach wiederverwendbaren Baustein.

## 🛠️ Zugehörige Übungen

* [InputOutputTesterButton_DIDO_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md)
* [InputOutputTesterButton_PWM_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
