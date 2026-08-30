# InputOutputTesterButton_PWM_OPC_UA: PWM Tester (OPC-UA)

![InputOutputTesterButton_PWM_OPC_UA_network](./InputOutputTesterButton_PWM_OPC_UA_network.svg)

* * * * * * * * * *
## Einleitung

`InputOutputTesterButton_PWM_OPC_UA` ist das PWM-Trainingsbeispiel zu **12 analogen Ausgängen (0–100 % Duty)**, steuerbar sowohl über den ISOBUS-Virtual-Terminal als auch über OPC-UA (Web-Client). Es ist das direkte Pendant zum bestehenden DI/DO-Beispiel `Meins::InputOutputTester::Button_DIDO_OPC_UA`: Die 8 digitalen Eingänge (`Input_I1`…`Input_I8`) bleiben unverändert, die früher rein digitalen Ausgänge werden hier durch **12 PWM-Kanäle** ersetzt, jeder mit VT-Zahlenfeld, Balkengrafik, 6 Ramp-Tasten, Kanal-Ein/Aus-Schalter und 3-Farben-Statusanzeige.

Da ein logiBUS-Controller nur **8 PWM-Kanäle gleichzeitig** physisch bedienen kann, sind beim Deployment die Kanäle 1–8 aktiv (`bDefaultEnabled=TRUE`) und die Kanäle 9–12 zunächst deaktiviert (`bDefaultEnabled=FALSE`); jeder Kanal lässt sich per Schalter unabhängig ein-/ausschalten.

Die Übung ist ein reines Top-Level-Composite: Sie instanziiert die 8 unveränderten Eingangs-Bausteine, 12× den PWM-Kanal-Baustein und einen `SystemTickSender`, ohne selbst Logik zu enthalten.

## Verwendete Funktionsbausteine (FBs)

| SubApp-Instanz | Typ | Zweck |
|---|---|---|
| `Input_I1` … `Input_I8` | `MyLib::sys::logiBUS_IXA_BG_OPC` | Unveränderte digitale Eingänge, je mit VT-Anzeige (`Button_I01..I08`) und OPC-UA-Publish (`I1_WRITE..I8_WRITE`) |
| `Output_Q1` … `Output_Q12` | `MyLib::sys::RampLimitFS_TO_logiBUS_QDA_PWM_OPC` | Je ein vollständiger PWM-Kanal (VT + physischer Ausgang + OPC-UA) |
| `SystemTickSender` | `MyLib::sys::SystemTickSender` | Zyklischer Zähler für die VT-Statusanzeige (`OutputNumber_Tick`) |

Alle 12 `Output_Qxx`-Instanzen sind dieselbe wiederverwendbare Composite-SubApp `RampLimitFS_TO_logiBUS_QDA_PWM_OPC` (siehe [Sub-Baustein](../../../../../Bibliotheken/typelibrary/MyLib/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md) unten) und unterscheiden sich nur durch ihre Parameter:

### Sub-Baustein: RampLimitFS_TO_logiBUS_QDA_PWM_OPC

- **Typ**: SubAppType (`MyLib::sys`)
- **Instanziiert 12×** mit je eigenen Objekt-IDs für VT-Zahlenfeld/Balken (`u16ObjId_VALUEVAR`), 6 Ramp-Tasten (`u16ObjId_ZERO/DOWN_FAST/DOWN_SLOW/UP_SLOW/UP_FAST/FULL`), Kanal-Schalter (`u16ObjId_SWITCH`) und Status-Hintergrundfarbe (`u16ObjId_STATUS`), physischem PWM-Ausgang (`Output`, `logiBUS::io::DQ::logiBUS_DO_S`) sowie fünf OPC-UA-Adressen (`ID_READ`, `ID_WRITE`, `ID_SWITCH_READ`, `ID_SWITCH_WRITE`, `ID_STATUS_WRITE`).
- **Parameter `bDefaultEnabled`**: `TRUE` für Kanal 1–8, `FALSE` für Kanal 9–12 — legt den Enable-Zustand beim Deployment fest, da nur 8 PWM-Kanäle gleichzeitig physisch verfügbar sind.
- **Funktionsweise**: Verrechnet VT-Sollwert (Zahlenfeld/Ramp-Tasten) und Web-Sollwert (OPC-UA-Subscribe, Prozent REAL) auf denselben `RampLimitFS`-Rampenbaustein, gibt das Ergebnis als 13-Bit-PWM-Rohwert an den physischen `logiBUS_QD_PWM`-Ausgang und spiegelt Sollwert, Enable-Zustand und Ist-Status (`QO`) über OPC-UA-Publish zurück. Details siehe eigene Dokumentation des Bausteins.

### OPC-UA-Adressraum

Für jeden Kanal `Qnn` (01–12) legt `SubStrings.gcf` einen eigenen Ordnerknoten unter `/Objects/PWM/Qnn/` an (FORTE erzeugt fehlende Zwischenordner automatisch als `FolderType`):

| Node-Pfad | Node-ID | Richtung | Bedeutung |
|---|---|---|---|
| `/Objects/PWM/Qnn/VALUE` | `s=PWM_Qnn` | Read+Write | Sollwert Prozent (REAL 0.0–100.0) |
| `/Objects/PWM/Qnn/SWITCH` | `s=PWM_Qnn_SWITCH` | Read+Write | Kanal aktiviert/deaktiviert (BOOL) |
| `/Objects/PWM/Qnn/STATUS` | `s=PWM_Qnn_STATUS` | Write (nur lesend für den Client) | Ist-Status `logiBUS_QD_PWM.QO` (BOOL) |

Der Web-Client `apixon-pwm-client` bildet für jeden Kanal einen REAL-Slider mit Zahlenfeld (0–100 %) sowie die kombinierte 3-Farben-Statuslogik (Weiß=deaktiviert, Grün=aktiv+OK, Rot=aktiv+Störung) aus denselben zwei bereits publizierten Bits `SWITCH`/`STATUS`.

## Programmablauf und Verbindungen

Die Übung selbst enthält **keine Verbindungen** (`EventConnections`/`DataConnections` sind leer) — sie besteht ausschließlich aus 21 parallel arbeitenden SubApp-Instanzen, deren Verdrahtung mit der physischen Hardware und den OPC-UA-Adressen über `Parameter`-Zuweisungen erfolgt:

1. **8 unveränderte Eingänge**: `Input_I1`…`Input_I8` lesen die physischen Eingänge `Input_I1`…`Input_I8` und spiegeln sie per VT-Anzeige (`Button_I01`…`Button_I08`) und OPC-UA-Publish (`I1_WRITE`…`I8_WRITE`).
2. **12 PWM-Kanäle**: `Output_Q1`…`Output_Q12` verbinden je einen physischen PWM-Ausgang (`Output_Q1`…`Output_Q12`) mit einer eigenen Gruppe von VT-Objekten und OPC-UA-Adressen. Jede Instanz arbeitet unabhängig — es gibt keine Verbindungen zwischen den Kanälen.
3. **Zeitgeber**: `SystemTickSender` zählt zyklisch hoch und speist das VT-Zahlenfeld `OutputNumber_Tick` sowie den OPC-UA-Knoten `Tick_WRITE` — dient als "Lebenszeichen" der Steuerung auf VT und Web-UI.

**Registrierung im Trainingssystem**: Kein eigenes `Application`-Element nötig. Das Trainingssystem besitzt genau einen `Control`-Slot pro `System`, der per "Change Type" im 4diac IDE auf den gewünschten Übungstyp umgeschaltet wird — die PWM-Composite ist damit ein wählbares Ziel, ohne die Systemstruktur (`test_AX.sys`) zu ändern.

**VT-Projekt**: `Workspace_PWM12` stellt die passenden ISO-Designer-Objekte bereit — eine Übersichtsseite plus 3 Datenmasken (`DataMask_PWM1/2/3`, 4 Kanäle je Seite), pro Kanal eine horizontale Zeile mit Label, Prozent-Zahlenfeld, Rohwert-Zahlenfeld, horizontalem Balkendiagramm und den 6 Ramp-Tasten in der Reihenfolge `0 -- - + ++ F`.

## Wertebereiche und Umrechnungsketten

Intern rechnet die Übung durchgängig in der SAE-J1939/ISO-11783-Fieldbus-Konvention (`VALID_SIGNAL_W`, 0–64255 statt einer frei erfundenen Skala):

- **VT/Web ↔ Fieldbus**: `F_PWM_PERCENT_TO_RAW`/`F_PWM_RAW_TO_PERCENT` (SubApp, `MyLib::sys`) rechnen zwischen Anteil 0.0–1.0 und Fieldbus-Rohwert 0–64255 um.
- **Prozent ↔ Anteil**: `F_PERCENT_TO_FRACTION`/`F_FRACTION_TO_PERCENT` (FBType, `logiBUS::signalprocessing::fieldbus`) rechnen zwischen Prozent 0–100 und Anteil 0.0–1.0 um — nötig, weil OPC-UA/Web in Prozent REAL kommuniziert, die internen Umrechnungsbausteine aber mit Anteil 0.0–1.0 arbeiten.
- **Fieldbus ↔ physischer PWM-Ausgang**: `logiBUS_QD_PWM.OUT` erwartet einen rohen 13-Bit-Wert (0–8191), daher rechnet der Kanal-Baustein zusätzlich `×8191 / 64255`.

## Lernziele

- Verständnis, wie ein Trainingsbeispiel mit vielen gleichartigen Kanälen durch **eine einzige wiederverwendbare Composite-SubApp** (statt kopierter Logik) aufgebaut wird — hier 12× `RampLimitFS_TO_logiBUS_QDA_PWM_OPC` mit unterschiedlicher Parametrierung.
- Umgang mit **analogen (PWM-)Ausgängen** im Gegensatz zu rein digitalen Ausgängen (`Button_DIDO_OPC_UA`), inklusive Sollwert-Ramping, Skalierungsketten und 13-Bit-Rohwertformat.
- Bidirektionale **OPC-UA-Synchronisation** eines analogen Sollwerts (VT ↔ Web, mit Mehrfachquellen-Mux über `E_RS`+`F_SEL`) sowie eines Kanal-Enable-Schalters.
- Grenzen der physischen Hardware (max. 8 gleichzeitige PWM-Kanäle) softwareseitig über einen individuell schaltbaren Enable-Zustand abbilden.

**Schwierigkeitsgrad**: Fortgeschritten
**Vorkenntnisse**: `Button_DIDO_OPC_UA` (digitales Gegenstück), `Uebung_094a` (QI-basiertes Enable statt PERMIT), Grundlagen von `RampLimitFS` und OPC-UA-Adaptern (`AR_SUBSCRIBE_1`/`AR_PUBLISH_1`, `AX_SUBSCRIBE_1`/`AX_PUBLISH_1`).

## Zusammenfassung

`InputOutputTesterButton_PWM_OPC_UA` demonstriert, wie sich ein komplettes 12-Kanal-PWM-Trainingsbeispiel mit VT- und Web-Bedienung allein durch mehrfache Instanziierung eines einzigen, gut gekapselten Kanal-Bausteins (`RampLimitFS_TO_logiBUS_QDA_PWM_OPC`) aufbauen lässt. Die eigentliche Komplexität — Sollwert-Ramping, Skalierung zwischen Prozent/Anteil/Fieldbus-Rohwert/13-Bit-PWM, Mehrfachquellen-Mux zwischen VT und Web sowie die 3-Farben-Statuslogik — steckt vollständig in diesem Sub-Baustein; die Top-Level-Übung selbst bleibt eine reine Parametrierungs- und Verdrahtungsliste.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
