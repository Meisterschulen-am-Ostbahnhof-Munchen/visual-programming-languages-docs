# Training_03_OPC_UA_RES: Toggle-Flipflop über OPC-UA ("SUB style")

![Training_03_OPC_UA_RES_network](./Training_03_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Einleitung

`Training_03_OPC_UA_RES` überträgt `Uebung_010d_AX` (SoftKey-getriggertes
Toggle-Flipflop mit `GreenWhiteBackground`, siehe
[`Uebung_010d_AX.md`](../../../test_AX/Uebungen_doc/Uebung_010d_AX.md)) auf
zwei physisch getrennte FORTE-Geräte, verbunden über OPC-UA.

Anders als `Training_02_OPC_UA_RES` ("RES style": die Kommunikationsbausteine
stecken in der `<Resource>` jedes Geräts) verwendet diese Übung den
**"SUB style"**: das gesamte Protokoll — SoftKey-Eingabe, OPC-UA-Client/
-Server-Bausteine und `GreenWhiteBackground` — steckt in zwei
wiederverwendbaren `MyLib::sys`-Composites (`Uebung_010d_PC_A_OPC`,
`Uebung_010d_PC_B_OPC`). Die `.sys`-Datei selbst enthält dadurch **keine**
FBs mehr, nur noch zwei `SubApp`-Instanzen und das Geräte-`Mapping`.

## Verwendete Composites

| Composite | Gerät | Zweck |
|---|---|---|
| [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC_network.svg) | A (Station 11, `192.168.1.11`) | `SoftKey_F1` löst per `CLIENT_0` einen argument- und rückgabewertlosen OPC-UA-Methodenaufruf auf Gerät B aus; `GreenWhiteBackground` zeigt den von Gerät B lokal überwachten Zustand |
| [`Uebung_010d_PC_B_OPC`](./Uebung_010d_PC_B_OPC_network.svg) | B (Station 12, `192.168.1.12`) | Empfängt den Methodenaufruf per `SERVER_0`, taktet `AX_T_FF` (Toggle-Flipflop), schaltet `Output_Q1` und schreibt den neuen Zustand aktiv per `AX_CLIENT_1_0` zurück auf Gerät A |

Auf Gerät A ist **kein** `AX_T_FF` nötig — der SoftKey-Druck ist ein reiner
RPC-Trigger ohne Wertwechsel-Trick. Auf Gerät A liest ein `AX_SUBSCRIBE_1`
(`STATE_SUBSCRIBE`) den von Gerät B geschriebenen Zustand lokal und speist
`GreenWhiteBackground_AX`.

## OPC-UA-Adressraum

Beide Konstanten-Paare liegen in `VV::const::OPC_UA::myOpcUaAddresses`:

| Konstante | Wert | Verwendet von |
|---|---|---|
| `FF1_TRIGGER_LOCAL_METHOD` | `opc_ua[CREATE_METHOD;/Objects/ToggleFF/FF1_Trigger]` | `TRIGGER_SERVER` auf Gerät B (lokal erzeugte Methode) |
| `FF1_TRIGGER_REMOTE_CALL` | `opc_ua[CALL_METHOD;opc.tcp://192.168.1.12:4840#;/Objects/ToggleFF/FF1_Trigger]` | `TRIGGER_CLIENT` auf Gerät A (ruft dieselbe Methode remote auf) |
| `FF1_STATE_LOCAL_READ` | `opc_ua[READ;/Objects/ToggleFF/FF1_State,1:s=FF1_State]` | `STATE_SUBSCRIBE` auf Gerät A (lokal überwachter Zustandsknoten) |
| `FF1_STATE_REMOTE_WRITE` | `opc_ua[WRITE;opc.tcp://192.168.1.11:4840#;/Objects/ToggleFF/FF1_State,1:s=FF1_State]` | `STATE_CLIENT` auf Gerät B (schreibt denselben Knoten remote) |

Anders als `Q1_LOCAL_READ`/`Q1_REMOTE_WRITE` in Training_02 (reiner Werte-
Transport) sind `FF1_TRIGGER_*` eine echte OPC-UA-**Methode** (RPC), nicht
ein geschriebener/gelesener Knoten — passend zum ereignisgetriebenen
SoftKey-Tastendruck, der keinen Wert trägt.

## Programmablauf und Verbindungen

1. **`Uebung_010d_PC_A_OPC`** (Gerät A): `SoftKey_UP_F1.IND` (Softkey
   losgelassen) löst `TRIGGER_CLIENT.REQ` aus — `CLIENT_0` ruft die
   Remote-Methode `FF1_TRIGGER_REMOTE_CALL` auf. Parallel liefert
   `STATE_SUBSCRIBE` (`AX_SUBSCRIBE_1`) den von Gerät B geschriebenen
   Zustand per Adapterverbindung an `GreenWhiteBackground_AX.DI1`.
2. **`Uebung_010d_PC_B_OPC`** (Gerät B): `TRIGGER_SERVER.IND` (Methode
   aufgerufen) taktet `AX_T_FF.CLK` — das Toggle-Flipflop invertiert seinen
   Zustand. `AX_SPLIT_2` verteilt den neuen Zustand an zwei Ziele:
   `DigitalOutput_Q1.OUT` (lokal, schaltet `Output_Q1`) und
   `STATE_CLIENT.IN` (`AX_CLIENT_1_0`, schreibt den Zustand aktiv nach
   `FF1_STATE_REMOTE_WRITE` zurück auf Gerät A).
3. **Mapping/Devices**: `App_OPC_UA_RES2.SubApp_PC_A` → `FORTE_PC_A`,
   `SubApp_PC_B` → `FORTE_PC_B`; je ein `E_TRIG('EInit')` pro Gerät
   initialisiert das jeweilige Composite beim Start.

## Technische Besonderheiten

- **RPC statt Wertübertragung**: `FF1_TRIGGER_*` nutzt `CALL_METHOD`/
  `CREATE_METHOD` statt `READ`/`WRITE` — der richtige ACTION-Typ für einen
  argumentlosen, zustandslosen Auslöser (ein Tastendruck hat keinen Wert,
  der übertragen werden müsste).
- **"SUB style" vs. "RES style"**: Das Protokoll steckt hier vollständig im
  wiederverwendbaren `MyLib::sys`-Composite, nicht in der Resource des
  Geräts. Der Vorteil: dasselbe Composite lässt sich unverändert auf jedem
  Gerät instanzieren, das dieselbe Rolle (A oder B) spielt — die `.sys`-
  Datei bleibt auf Mapping und Geräte-Setup reduziert.
- **Kein Wertwechsel-Trick nötig**: Da der Trigger eine echte RPC-Methode
  ist (nicht ein beobachteter Wert), braucht Gerät A kein eigenes
  `AX_T_FF` — anders als bei reiner Read/Write-basierter Signalisierung,
  wo ein Flankenwechsel simuliert werden müsste.

## Lernziele

- OPC-UA-Methodenaufrufe (`CALL_METHOD`/`CREATE_METHOD`) als RPC-Alternative
  zu `READ`/`WRITE` für ereignisgetriggerte, wertlose Trigger.
- "SUB style"-Verteilungsmuster: Protokoll im wiederverwendbaren Composite
  statt in der Resource.
- Rückweg (Zustand von B nach A) über einen zweiten, unabhängigen
  Read/Write-Adresskanal, getrennt vom Trigger-Kanal.

**Schwierigkeitsgrad**: Mittel
**Vorkenntnisse**: `Uebung_010d_AX.SUB` (lokales Toggle-Flipflop-Muster),
`Training_02_OPC_UA_RES` (RES-style-Verteilung, `AX_CLIENT_1_0`/
`AX_SUBSCRIBE_1`).

## Zusammenfassung

`Training_03_OPC_UA_RES` verteilt `Uebung_010d_AX` auf zwei Geräte und führt
dabei zwei neue Konzepte gegenüber Training_02 ein: OPC-UA-Methodenaufrufe
als RPC-Alternative zur reinen Wertübertragung, und das "SUB style"-Muster,
bei dem das Protokoll im wiederverwendbaren Composite statt in der Resource
steckt.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
