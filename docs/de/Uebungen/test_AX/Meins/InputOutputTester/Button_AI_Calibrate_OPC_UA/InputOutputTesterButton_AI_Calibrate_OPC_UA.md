# InputOutputTesterButton_AI_Calibrate_OPC_UA: AI Calibrate Tester (OPC-UA)

![InputOutputTesterButton_AI_Calibrate_OPC_UA_network](./InputOutputTesterButton_AI_Calibrate_OPC_UA_network.svg)

* * * * * * * * * *
## Einleitung

`InputOutputTesterButton_AI_Calibrate_OPC_UA` ist das Trainingsbeispiel für **8 analoge Eingänge mit 2-Punkt-Kalibrierung**, steuerbar sowohl über den ISOBUS-Virtual-Terminal als auch über OPC-UA (Web-Client). Die 12 digitalen Ausgänge sind unverändert aus dem [`InputOutputTesterButton_DIDO_OPC_UA`](../Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md)-Beispiel übernommen; neu ist ausschließlich die Kalibrierlogik für die 8 Analogeingänge.

Anders als bei DIDO/PWM ist die eigentliche Kalibrierlogik pro Kanal deutlich umfangreicher: Jeder Analogeingang durchläuft eine vollständige 2-Punkt-Kalibrierung (Referenzwerte ZERO/SPAN, ausgelöst über zwei VT-/OPC-UA-Tasten CO/CS), deren Ergebnis (OFFSET/SCALE) INI-persistiert wird, sodass die Kalibrierung einen Neustart der Steuerung übersteht.

## Verwendete Funktionsbausteine (FBs)

| SubApp-Instanz | Typ | Zweck |
|---|---|---|
| `AnalogChannel_I1` … `AnalogChannel_I8` | `MyLib::sys::logiBUS_AI_Calibrate_IDA_OPC` | Analogeingang mit 2-Punkt-Kalibrierung, VT-Zahlenfeldern (Rohwert + kalibriert) + Bargraph + OPC-UA |
| `Output_Q1` … `Output_Q12` | `MyLib::sys::Button_IXA_TO_logiBUS_QXA_BG_OPC` | Digitaler Ausgang, unverändert aus dem DIDO-Beispiel übernommen |
| `SystemTickSender` | `MyLib::sys::SystemTickSender` | Zyklischer Zähler für die VT-Statusanzeige (`OutputNumber_Tick`) |

### Sub-Baustein: `logiBUS_AI_Calibrate_IDA_OPC` (Analogeingänge)

*Noch nicht in der Bibliotheksreferenz dokumentiert (`MyLib_AX-1.0.0::sys`) — separate Doku-Lücke, siehe Hinweis am Ende dieser Seite.*

- **Typ**: SubAppType (`MyLib::sys`), Kommentar im Quellbaustein: *"logiBUS_AI_IDA (Analog-Eingang) mit 2-Punkt-Kalibrierung (AR_CALIBRATE_SQ_REF, OFFSET/SCALE + Referenzwerte ZERO/SPAN alle INI-persistiert) auf VT-Zahlenfelder (Rohwert + kalibrierter Wert, je eigene CNumberVariable) + Bargraph (kalibriert) + 2 VT-Tasten (CO/CS) + OPC-UA (Rohwert DWORD + kalibrierter Wert REAL, generisch, ein Kanal)"*
- **Funktionsweise**: Der physische Analogeingang (`logiBUS_AI_IDA`) liefert über eine Kette aus `AD_SPLIT_2`/`AD_TO_AUDI`/`AUDI_SPLIT_2` sowohl den unkalibrierten Rohwert (VT-Anzeige + OPC-UA-Publish über `AD_PUBLISH_1`) als auch den Eingang für die eigentliche Kalibrierung (`AUDI_TO_AR` → `AR_CALIBRATE_SQ_REF`-Adapter). Zwei VT-/OPC-UA-Tasten (`Button_CO`, `Button_CS`) lösen — jeweils über `E_MERGE`-Event-Zusammenführung von lokalem Tastendruck und OPC-UA-Fernauslösung (`AX_SUBSCRIBE_1` → `AX_RF_TRIG`, Flankenerkennung für den Toggle-Mechanismus des Web-Clients) — die beiden Kalibrierschritte CO (Nullpunkt) und CS (Spanne) am `CALIBRATE`-Adapter aus. Das Ergebnis (`OFFSET`, `SCALE`) wird über je einen `INI_AR2`-Baustein persistiert (Default `OFFSET=0.0`, `SCALE=1.0`), ebenso die beiden Referenzwerte `ZERO`/`SPAN` (Default `0.0`/`100.0`). Der kalibrierte Wert (`CALIBRATE.Y`) geht über `AR_SPLIT_2` sowohl an die VT-/OPC-UA-Anzeige (`AR_PUBLISH_1`) als auch an das VT-Zahlenfeld mit Bargraph (`Q_NumericValue_PHYSA`).
- **Referenzwerte von außen setzbar**: Die ZERO-/SPAN-Referenzwerte selbst sind über zwei `MyLib::sys::NumericValue_TO_AR2_OPC`-Sub-Bausteine (`Y_OFFSET_LIT`, `Y_SCALE_LIT` — Namen historisch aus einer früheren Iteration, liefern tatsächlich die ZERO/SPAN-Werte an `CALIBRATE.Y_Offset`/`CALIBRATE.Y_Scale`) sowohl per VT-Eingabefeld als auch per OPC-UA schreibbar — anders als bei DIDO/PWM sind hier also nicht nur Ausgänge, sondern auch Kalibrierparameter bidirektional von VT und Web aus änderbar.
- **Kalibrierverfahren**: Verwendet `AR_CALIBRATE_SQ_REF` statt des einfacheren `AR_CALIBRATE` (siehe [`AR_CALIBRATE_SQ`](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/Engineering/measurements/AR_CALIBRATE_SQ/) in der Bibliotheksreferenz) — laut Baustein-Versionshinweis nach Vorbild einer früheren Übung, aber mit korrigierter Offset-Formel und ECC-erzwungener CO-vor-CS-Reihenfolge (Spanne kann erst nach dem Nullpunkt kalibriert werden).

### Sub-Baustein: [Button_IXA_TO_logiBUS_QXA_BG_OPC](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/typelibrary/MyLib/sys/Button_IXA_TO_logiBUS_QXA_BG_OPC/) (Ausgänge)

Unverändert aus dem DIDO-Beispiel — siehe dortige Beschreibung.

## VT-Anbindung (ISOBUS Virtual Terminal)

Das zugehörige VT-Pool-Projekt `Workspace_AI_Calibrate` (ISO-Designer, `DefaultPool.jop`) besteht aus 5 DataMasken:

| Maske | ObjectID | Inhalt |
|---|---|---|
| `DataMask_M1` | 1000 | Übersichts-/Startmaske (480×480), Zugriffspunkt für die 4 Kanal-Masken |
| `DataMask_AIC1` … `DataMask_AIC4` | 1001–1004 | je **2 Analogkanäle**: Rohwert-Anzeige, kalibrierter Wert, Bargraph, 2 CO/CS-Tasten und 2 Eingabefelder für die ZERO-/SPAN-Referenzwerte pro Kanal |

Die numerischen VT-Objekte (`NumberVariable_AIC_RAW_I0n`, `NumberVariable_AIC_CAL_I0n_N`, `NumberVariable_AIC_I0n_ZERO_N`/`_SPAN_N`, `Button_AIC_I0n_CO`/`_CS`) werden — wie bei allen VT-Übungen in diesem System — über `GcfScript.py` aus dem kompilierten `DefaultPool.iop.h` in eine 4diac-`.gcf`-Konstantendatei (`Uebungen::const::UT::AIC::DefaultPool_AIC`) übersetzt und dort per `Import` in die FB-Netzwerke eingebunden (siehe `test_AX/scripts/RunSkript_Workspace_AI_Calibrate_AX.{bat,sh}`).

## Web-Client (OPC-UA, kein VT-Pixel-Mirror)

Der Web-Client `apixon-ai-calibrate-client` (Vue 3, `ApixonAICalibrate.vue`) ist **kein** visueller Nachbau der DataMasken (anders als ein `vt-ui-mirror`-Projekt), sondern eine eigenständige, funktionale Web-Oberfläche: Er verbindet sich direkt per WebSocket-OPC-UA (`OPCUAClient`, Standardport `4841`) mit dem FORTE-Laufzeitsystem und abonniert/schreibt dieselben Knoten wie die FB-Netzwerke (Rohwert, kalibrierter Wert, CO-/CS-Toggle, ZERO/SPAN-Referenzwerte je Kanal) — unabhängig vom Layout der VT-Masken.

## Programmablauf und Verbindungen

1. **8 Analogkanäle**: `AnalogChannel_I1`…`AnalogChannel_I8` lesen `AnalogInput_I1`…`AnalogInput_I8`, kalibrieren sie 2-Punkt-basiert und veröffentlichen Rohwert + kalibrierten Wert per OPC-UA (`AIC_I1_RAW_WRITE`…`AIC_I8_CAL_WRITE`); die CO-/CS-Tasten sind sowohl lokal (VT) als auch remote (OPC-UA, `AIC_I*_CO_READ`/`_CS_READ`) auslösbar.
2. **12 digitale Ausgänge**: `Output_Q1`…`Output_Q12`, unverändert aus dem DIDO-Beispiel.
3. **Zeitgeber**: `SystemTickSender` speist das VT-Zahlenfeld `OutputNumber_Tick` sowie den OPC-UA-Knoten `Tick_WRITE`.

**Registrierung im Trainingssystem**: Wie bei allen Übungen in diesem System kein eigenes `Application`-Element nötig — Auswahl per "Change Type" im 4diac IDE auf den einen `Control`-Slot des `System`.

## Lernziele

- 2-Punkt-Kalibrierung (`AR_CALIBRATE_SQ_REF`) eines Analogeingangs mit paralleler VT- **und** OPC-UA-Bedienung, inklusive INI-Persistenz der Kalibrierparameter über einen Neustart hinweg.
- Bidirektionale Fernauslösung eines lokal ausgelösten Vorgangs (CO/CS-Tasten) über OPC-UA mittels Flankenerkennung (`AX_RF_TRIG`) statt direkter Zustandsübernahme — Toggle-Semantik des Web-Clients.
- Kombination aus reinem Publish (Rohwert), bidirektionalem Trigger (CO/CS) und bidirektional beschreibbaren Parametern (ZERO/SPAN-Referenzwerte) in einem einzigen Baustein.

**Schwierigkeitsgrad**: Mittel bis Fortgeschritten
**Vorkenntnisse**: [`InputOutputTesterButton_DIDO_OPC_UA`](../Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md) (Grundmuster VT+OPC-UA), [`AR_CALIBRATE_SQ`](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/Engineering/measurements/AR_CALIBRATE_SQ/)-Adapter, INI-Persistenz (`eclipse4diac::storage::INI_AR2`).

## Zusammenfassung

`InputOutputTesterButton_AI_Calibrate_OPC_UA` demonstriert 2-Punkt-Analogkalibrierung mit vollem VT- und OPC-UA-Zugriff auf Rohwert, kalibrierten Wert, Kalibrierauslösung und die Referenzwerte selbst — die bisher komplexeste Kombination aus lokaler und ferngesteuerter Bedienung in diesem Trainingssystem.

> **Hinweis**: Der Sub-Baustein `MyLib::sys::logiBUS_AI_Calibrate_IDA_OPC` sowie `MyLib::sys::NumericValue_TO_AR2_OPC` liegen unter `MyLib_AX-1.0.0` und haben noch keine eigene Seite in der Bibliotheksreferenz (`Bibliotheken/typelibrary/MyLib_AX/sys/`) — das ist Teil einer separaten, größeren Doku-Lücke für die `MyLib_AX`/`MyLib_B`-Bibliotheksreferenz und nicht Gegenstand dieser Seite.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
