# A2X_AND_2

![A2X_AND_2](A2X_AND_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock A2X_AND_2 berechnet die logische UND-Verknüpfung zweier [A2X](../types/unidirectional/BOOL/A2X.md)-Adapter – getrennt für den UP- und den DOWN-Kanal. Im Gegensatz zu den einkanaligen, generischen `AX_AND`-Bausteinen ist A2X_AND_2 ein handgebauter Composite-Funktionsblock, der zwei Standard-Bausteine `AND_BOOL_2` intern verdrahtet, einen je Kanal.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Eingänge – die Ereignisse laufen über die Adapter `IN1`/`IN2`.

### **Ereignis-Ausgänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Ausgänge – die Ereignisse laufen über den Adapter `OUT`.

### **Daten-Eingänge**

Der Funktionsblock verfügt über keine direkten Daten-Eingänge.

### **Daten-Ausgänge**

Der Funktionsblock verfügt über keine direkten Daten-Ausgänge.

### **Adapter**

**Eingangsadapter:**

- **IN1**: UND-Eingang 1 (Typ: `adapter::types::unidirectional::A2X`)
- **IN2**: UND-Eingang 2 (Typ: `adapter::types::unidirectional::A2X`)

**Ausgangsadapter:**

- **OUT**: UND-Ergebnis (Typ: `adapter::types::unidirectional::A2X`)

## Funktionsweise

Der Baustein enthält zwei interne Instanzen von `iec61131::booleanOperators::AND_BOOL_2`: `AND_UP` verknüpft die UP-Kanäle von `IN1` und `IN2`, `AND_DOWN` die DOWN-Kanäle. Trifft an `IN1` oder `IN2` ein UP-Ereignis (`E_UP`) ein, wird `AND_UP.REQ` ausgelöst, das Ergebnis von `IN1.UP AND IN2.UP` berechnet und über `OUT.E_UP`/`OUT.UP` ausgegeben. Für den DOWN-Kanal läuft dieselbe Logik unabhängig über `AND_DOWN`. Da ein Ereignisziel – anders als ein Datenziel – mehrere Quellen haben darf, dürfen sowohl `IN1.E_UP` als auch `IN2.E_UP` in `AND_UP.REQ` münden; das Ergebnis wird bei jedem der beiden auslösenden Ereignisse neu berechnet.

## Technische Besonderheiten

- Echter Composite-Baustein (kein generischer `GenericClassName`-Mechanismus wie bei `AX_AND_2`), aufgebaut aus zwei Standard-`AND_BOOL_2`-Instanzen
- Zwei unabhängige Kanäle (UP/DOWN), jeweils mit eigenem Ereignispaar – kein gemeinsamer Zustand zwischen den Kanälen
- Da IEC 61499 mehrere Quellen auf ein Ereignisziel erlaubt, aber nicht auf ein Datenziel, wird pro Kanal genau ein Logikbaustein zwischengeschaltet, statt die beiden Eingangsdaten direkt auf eine gemeinsame Variable zu verdrahten

## Zustandsübersicht

Der Baustein ist ein kombinatorischer Logikbaustein ohne internen Zustand; jedes eintreffende Ereignis berechnet das Ergebnis direkt neu:

- IN1.E_UP, IN2.E_UP → AND_UP.REQ; IN1.UP, IN2.UP → AND_UP.IN1/IN2; AND_UP.CNF → OUT.E_UP; AND_UP.OUT → OUT.UP
- IN1.E_DOWN, IN2.E_DOWN → AND_DOWN.REQ; IN1.DOWN, IN2.DOWN → AND_DOWN.IN1/IN2; AND_DOWN.CNF → OUT.E_DOWN; AND_DOWN.OUT → OUT.DOWN

## Anwendungsszenarien

- Sicherheitslogik, bei der zwei UP/DOWN-Signalgeber gleichzeitig aktiv sein müssen, bevor ein Aktor freigegeben wird
- Verriegelungen zwischen zwei redundanten A2X-Signalquellen
- Kombinatorische Logik in Steuerungen, die auf A2X-Adaptern statt auf einfachen BOOL-Signalen basieren

## ⚖️ Vergleich mit ähnlichen Bausteinen

[A2X_OR_2](A2X_OR_2.md) und [A2X_XOR_2](A2X_XOR_2.md) sind baugleich, verwenden aber `OR_BOOL_2` bzw. `XOR_BOOL_2` statt `AND_BOOL_2`. Der einkanalige Vorgänger [AX_AND_2](AX_AND_2.md) verknüpft nur ein einzelnes Bool-Signal und ist – anders als A2X_AND_2 – als generischer Baustein (`GEN_AX_AND`) implementiert. Im Unterschied zu [AB_AND_2](../bitwiseOperators/AB_AND_2.md), das ein komplettes `BYTE`-Bitmuster verknüpft, verarbeitet A2X_AND_2 einzelne boolesche Wahrheitswerte je Kanal.

## Fazit

A2X_AND_2 bringt die logische UND-Verknüpfung auf die zweikanalige A2X-Welt: zwei unabhängige, ereignisgesteuerte UND-Verknüpfungen für UP und DOWN, sauber getrennt und ohne Mehrfachschreiber auf einer gemeinsamen Variable.
