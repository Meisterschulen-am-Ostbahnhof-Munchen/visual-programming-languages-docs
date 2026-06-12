# GET_LWORD


![GET_LWORD](./GET_LWORD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **GET_LWORD** dient dem konsistenten Auslesen eines LWORD-Wertes aus einer **InOut-Variable**. Er puffert den aktuellen Wert der quellvariablen und stellt ihn am Ausgang `OUT` bereit. Dies ist besonders nützlich, wenn der Inhalt einer gemeinsam genutzten Variablen zu einem definierten Zeitpunkt festgehalten werden soll, ohne von nachfolgenden Schreibzugriffen anderer Bausteine beeinflusst zu werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|---|---|
| `REQ` | Startet die Auslese-Operation. Der aktuelle Wert von `IN` wird in `OUT` übernommen. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|---|---|
| `CNF` | Bestätigt die erfolgreiche Durchführung der Operation. Wird nach dem Kopiervorgang ausgelöst. |

### **Daten-Eingänge**

Der Baustein besitzt keine klassischen Dateneingänge, sondern verwendet einen **InOut-Parameter**, der als bidirektionale Schnittstelle fungiert.

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
|---|---|---|
| `OUT` | `LWORD` | Gepufferter Ausgabewert. Enthält die Kopie des Werts von `IN` zum Zeitpunkt des letzten `REQ`. Initialwert = `0`. |

### **Adapter**

Keine vorhanden.

## Funktionsweise

Der Baustein implementiert einen einfachen Ablauf:

1. **Ereignis `REQ`** löst die Ausführung des Algorithmus `REQ` aus.
2. **Algorithmus `REQ`**: Die Anweisung `OUT := IN;` kopiert den aktuellen Wert der InOut-Variablen `IN` in den Ausgangspuffer `OUT`. Die InOut-Schnittstelle gewährleistet dabei einen direkten Lesezugriff auf die quellvariable.
3. Nach Abschluss der Zuweisung wird das Ausgangsereignis **`CNF`** gesendet. Die Ereignisausgänge `CNF` sind sowohl mit `OUT` als auch mit `IN` verknüpft, sodass nachfolgende Bausteine sowohl den neuen Wert als auch die Referenz auf die InOut-Variable nutzen können.

Die Pufferung stellt sicher, dass der Wert von `OUT` während eines Ablaufzyklus stabil bleibt, auch wenn die Quelle `IN` zwischenzeitlich von anderen Bausteinen geändert wird.

## Technische Besonderheiten

- **InOut-Parameter**: Die Variable `IN` ist als `InOutVar` deklariert. Dies ermöglicht dem Baustein, direkt auf einen externen Speicherort zuzugreifen, ohne dass eine zusätzliche Verbindung als Dateneingang nötig ist. Der Baustein liest diesen Wert, verändert ihn jedoch nicht.
- **Einfache Zustandslogik**: Der Baustein besitzt nur einen einzigen Zustand `REQ`. Dadurch wird bei jedem `REQ`-Ereignis genau eine Aktion ausgeführt – die Ausführung ist deterministisch und ohne Verzögerung.
- **Typ der Variablen**: `LWORD` (64‑Bit logarithmischer oder Bifeldwert) wird als sicherer Puffer behandelt.

## Zustandsübersicht

| Zustand | Beschreibung |
|---|---|
| `REQ` | Initialer und einziger Zustand. Nach Eingang von `REQ` wird der Algorithmus ausgeführt und `CNF` gesendet. Der Zustand bleibt erhalten, sodass bei erneutem `REQ` der Vorgang wiederholt wird. |

## Anwendungsszenarien

- **Konsistentes Abtasten**: Ein `GET_LWORD`-Baustein kann eingesetzt werden, um den Wert eines zyklisch aktualisierten Sensors zu einem definierten Zeitpunkt auszulesen und für die weitere Verarbeitung (z. B. eine Berechnungskette) festzuhalten.
- **Vermeidung von Wettlaufsituationen**: In Systemen mit mehreren parallel arbeitenden Funktionsblöcken, die auf dieselbe Speicherstelle zugreifen, verhindert die Pufferung, dass ein Baustein zwischendurch einen inkonsistenten Wert erhält.
- **Datenprotokollierung**: Vor dem Ablegen einer Messung in einem Protokollspeicher kann mit `GET_LWORD` eine Momentaufnahme erstellt werden.

## Vergleich mit ähnlichen Bausteinen

- **`GET_INT`, `GET_DWORD`, `GET_BOOL`** etc.: Diese Bausteine folgen dem gleichen Prinzip, unterscheiden sich jedoch im Datentyp. `GET_LWORD` ist speziell für 64‑Bit-Werte vorgesehen.
- **Einfache Eingangsvariable**: Ein reiner Dateneingang würde erfordern, dass der verbindende Baustein den Wert selbst puffert oder die Verbindung ständig aktualisiert. Der InOut-Mechanismus bietet eine Referenz auf das Original, was in manchen Architekturen direkter und speicherschonender ist.
- **`MUX`-Bausteine**: Ein Multiplexer könnte ebenfalls einen Wert auswählen, benötigt aber zusätzliche Steuerleitungen. `GET_LWORD` ist für das einmalige, deterministische Auslesen optimiert.

## Fazit

Der Funktionsblock `GET_LWORD` ist ein einfacher, aber wirkungsvoller Baustein zur sicheren und zeitlich kontrollierten Abfrage einer InOut-Variablen vom Typ `LWORD`. Seine minimale Zustandsmaschine und die direkte Kopierlogik machen ihn ideal für Echtzeitanwendungen, bei denen konsistente Datenabgriffe erforderlich sind. Durch die Nutzung des InOut-Konzepts wird eine effiziente Kopplung an bestehende Speicherstellen erreicht, ohne die Verbindungsstruktur aufzublähen.