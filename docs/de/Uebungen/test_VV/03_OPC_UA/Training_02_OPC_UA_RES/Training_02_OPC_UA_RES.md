# Training_02_OPC_UA_RES: Verteiltes I1→Q1 über OPC-UA ("RES style")

![Training_02_OPC_UA_RES_network](./Training_02_OPC_UA_RES_network.svg)

* * * * * * * * * *
## Einleitung

`Training_02_OPC_UA_RES` zeigt das Grundmuster `Input_I1` → `Output_Q1` aus
`test_B/Uebungen/Uebung_001.SUB` — jetzt aber echt **verteilt** auf zwei
FORTE-Geräte: `FORTE_PC_A` (192.168.1.11) liest `Input_I1`, `FORTE_PC_B`
(192.168.1.12) schaltet `Output_Q1`. Die Verbindung zwischen beiden läuft
über OPC-UA, nicht über FORTE-eigenes Multicast (das zeigt bereits
`Training_01_PUBLISH_SUBSCRIBE`).

Namensgebend ist der **"RES style"**: die eigentlichen
Kommunikationsbausteine (`AX_CLIENT_1_0`, `AX_SUBSCRIBE_1`) stecken in der
`<Resource>` jedes Geräts, nicht im Application-Composite selbst. Das
entspricht dem kanonischen IEC-61499-Verteilungsmuster aus
`distribute4diac.adoc` sowie dem bestehenden `Training_01_PUBLISH_SUBSCRIBE`-
Vorbild. Die Schwester-Übung `Training_01_OPC_UA_SUB` zeigt für denselben
Anwendungsfall den Gegenentwurf ("SUB style", Krauternter-Produktivmuster):
dort steckt das Protokoll direkt im wiederverwendbaren `MyLib::sys`-
Composite statt in der Resource.

## Verwendete Funktionsbausteine (FBs)

| Instanz | Ort | Typ | Zweck |
|---|---|---|---|
| `INPUT_I1` | Application (`App_OPC_UA_RES`) | `logiBUS::io::DI::logiBUS_IXA` | Liest `Input_I1`, stellt den Zustand als AX-Adapter-Plug bereit |
| `OUTPUT_Q1` | Application (`App_OPC_UA_RES`) | `logiBUS::io::DQ::logiBUS_QXA` | Schaltet `Output_Q1`, nimmt den Zustand über AX-Adapter-Socket entgegen |
| `CLIENT_Q1` | Resource `EMB_RES_A` (Gerät A) | `adapter::net::AX_CLIENT_1_0` | Aktiver Remote-Write auf den von Gerät B überwachten OPC-UA-Knoten |
| `SUBSCRIBE_Q1` | Resource `EMB_RES_B` (Gerät B) | `adapter::net::AX_SUBSCRIBE_1` | Lokal überwachter OPC-UA-Knoten, wird von Gerät A remote beschrieben |

Die Application selbst enthält **keine** OPC-UA-Bausteine — sie ist bewusst
so gehalten, wie sie auch in einer nicht-verteilten Übung aussehen würde
(`INPUT_I1.IN` → `OUTPUT_Q1.OUT`, direkte Plug→Socket-Adapterverbindung,
identisch zum Muster in `Uebung_001.SUB`). Erst das `Mapping` verteilt beide
FBs auf unterschiedliche Geräte; die eigentliche Netzwerk-Übertragung
übernehmen `CLIENT_Q1`/`SUBSCRIBE_Q1` unten in den jeweiligen
Resource-FBNetworks.

## OPC-UA-Adressraum

Beide Konstanten liegen in `VV::const::OPC_UA::myOpcUaAddresses` und teilen
sich denselben Node-Pfad/Namen — nur ACTION und (bei `CLIENT`) der
Ziel-Endpoint unterscheiden sich:

| Konstante | Wert | Verwendet von |
|---|---|---|
| `Q1_LOCAL_READ` | `opc_ua[READ;/Objects/DigitalOutput/Q1,1:s=Output_Q1]` | `SUBSCRIBE_Q1` auf Gerät B (lokal überwachter Knoten, `Local\|READ\|SUBSCRIBE`) |
| `Q1_REMOTE_WRITE` | `opc_ua[WRITE;opc.tcp://192.168.1.12:4840#;/Objects/DigitalOutput/Q1,1:s=Output_Q1]` | `CLIENT_Q1` auf Gerät A (aktiver Remote-Write, `Remote\|WRITE\|CLIENT`) |

## Programmablauf und Verbindungen

1. **Application** (`App_OPC_UA_RES`): `INPUT_I1` (`logiBUS_IXA`, `Input_I1`)
   ist über eine Adapterverbindung (`INPUT_I1.IN` → `OUTPUT_Q1.OUT`) direkt
   mit `OUTPUT_Q1` (`logiBUS_QXA`, `Output_Q1`) verbunden — das rein
   logische Modell, unabhängig von der späteren Geräteverteilung.
2. **Mapping**: `INPUT_I1` → `FORTE_PC_A.EMB_RES_A`, `OUTPUT_Q1` →
   `FORTE_PC_B.EMB_RES_B`.
3. **Resource `EMB_RES_A`** (Gerät A): `START.COLD` initialisiert zuerst
   `App_OPC_UA_RES.INPUT_I1` selbst (dotted-path-Referenz auf dessen
   `.INIT`); erst dessen `.INITO`-Bestätigung löst `CLIENT_Q1.INIT` aus.
   Die eigentliche Adapterverbindung `App_OPC_UA_RES.INPUT_I1.IN` →
   `CLIENT_Q1.IN` überbrückt die Mapping-Grenze per dotted-path-Referenz —
   Application-Plug und Resource-Socket direkt verbunden, ohne
   Zwischenbaustein.
4. **Resource `EMB_RES_B`** (Gerät B): spiegelbildlich — `START.COLD` →
   `SUBSCRIBE_Q1.INIT`, dessen `.INITO` → `App_OPC_UA_RES.OUTPUT_Q1.INIT`,
   und `SUBSCRIBE_Q1.OUT` → `App_OPC_UA_RES.OUTPUT_Q1.OUT` (wieder direkte
   Plug→Socket-Adapterverbindung über die Mapping-Grenze hinweg).
5. **Laufzeit**: Ändert sich `Input_I1` auf Gerät A, schreibt `CLIENT_Q1`
   den neuen Wert per OPC-UA auf `opc.tcp://192.168.1.12:4840` in den von
   `SUBSCRIBE_Q1` überwachten Knoten — Gerät B übernimmt den Wert und
   schaltet `Output_Q1`. Diese Verbindung existiert **nicht** als Modell-
   Verbindung in der `.sys`-Datei, sondern ausschließlich als
   OPC-UA-Netzwerkkommunikation zur Laufzeit.

## Technische Besonderheiten

- **Adapterverbindungen können die Mapping-Grenze überschreiten**: Anders
  als ursprünglich angenommen, akzeptiert 4diac eine `AdapterConnections`-
  Verbindung zwischen einem Application-FB-Pin und einem Resource-FB-Pin per
  dotted-path-Referenz — genau wie bei einer reinen Event-/Datenverbindung
  (siehe `Training_01_PUBLISH_SUBSCRIBE`). Ein separater Konvertierungs-
  baustein (`AX_BOOL_TO_X`/`AX_X_TO_BOOL`) ist deshalb hier nicht nötig, weil
  `INPUT_I1`/`OUTPUT_Q1` selbst bereits adapterbasiert sind
  (`logiBUS_IXA`/`logiBUS_QXA`).
- **Zweistufige Initialisierung**: `START.COLD` initialisiert zuerst den
  physischen I/O-Baustein (`INPUT_I1`/`OUTPUT_Q1`), erst dessen `INITO`
  triggert den Kommunikationsbaustein (`CLIENT_Q1`/`SUBSCRIBE_Q1`) — so ist
  sichergestellt, dass die I/O-Anbindung steht, bevor der OPC-UA-Kanal
  aktiv wird.

## Lernziele

- Kanonisches IEC-61499-Verteilungsmuster: Application bleibt geräte-
  neutrale, portable Logik; die Resource jedes Geräts trägt die
  protokollspezifische Kommunikation.
- Korrekte ACTION-Zuordnung für lokal überwachte (`READ`/`SUBSCRIBE`) und
  remote geschriebene (`WRITE`/`CLIENT`) OPC-UA-Knoten.
- Explizite Initialisierungsreihenfolge (`START.COLD` → I/O-Baustein →
  Kommunikationsbaustein) statt blindem Verlassen auf automatisches
  EInit-Feuern.

**Schwierigkeitsgrad**: Mittel
**Vorkenntnisse**: `Uebung_001.SUB` (Grundmuster I1→Q1), Grundlagen der
OPC-UA-Adapterbausteine (`AX_CLIENT_1_0`/`AX_SUBSCRIBE_1`), IEC-61499-
Mapping/Distribution-Konzepte.

## Zusammenfassung

`Training_02_OPC_UA_RES` überträgt das triviale `Uebung_001.SUB`-Muster
(`Input_I1` → `Output_Q1`) auf zwei physisch getrennte FORTE-Geräte und
demonstriert dabei das kanonische IEC-61499-"RES style"-Verteilungsmuster:
portable Logik auf Application-Ebene, Kommunikation auf Resource-Ebene, per
dotted-path-Adapterverbindung über die Mapping-Grenze hinweg verknüpft.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
