# GET_SINT


![GET_SINT](./GET_SINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **GET_SINT** dient dazu, einen Wert des Datentyps `SINT` (signed short integer) aus einer als `InOut` deklarierten Variable auszulesen und als gepufferten Ausgang bereitzustellen. Er wird typischerweise verwendet, um auf eine gemeinsam genutzte Variable oder einen physikalischen Eingang zuzugreifen, ohne den ursprünglichen Wert zu verändern. Der Baustein arbeitet nach dem **IEC 61499** Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `REQ`    | Event    | Normale Ausführungsanforderung. Löst das Auslesen des InOut-Variablen aus. |

- **With-Verknüpfung**: Der Ereigniseingang `REQ` ist mit der Daten-Variable `IN` verknüpft.

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `CNF`    | Event    | Bestätigung der Ausführung. Wird nach erfolgreichem Kopiervorgang gesendet. |

- **With-Verknüpfung**: Der Ereignisausgang `CNF` ist mit den Daten-Variablen `OUT` und `IN` verknüpft.

### **Daten-Eingänge**

Der Baustein besitzt keine klassischen Daten-Eingänge. Stattdessen wird eine `InOut`-Variable verwendet.

### **Daten-Ausgänge**

| Variable | Datentyp | Initialwert | Kommentar |
|----------|----------|-------------|-----------|
| `OUT`    | SINT     | 0           | Gepufferter Ausgabewert. Enthält die Kopie von `IN` nach einer erfolgreichen `REQ`-Ausführung. |

### **Adapter**

Keine.

## Funktionsweise

Der Baustein führt einen einfachen Kopiervorgang durch:

1. Ein Ereignis am Eingang `REQ` triggert die Ausführung des hinterlegten Algorithmus.
2. Der Algorithmus weist dem Ausgang `OUT` den aktuellen Wert der InOut-Variable `IN` zu: `OUT := IN;`.
3. Nach Abschluss der Zuweisung wird das Ereignis `CNF` gesendet, um dem aufrufenden Baustein die Fertigstellung zu signalisieren.

Die InOut-Variable `IN` erlaubt den direkten Zugriff auf eine externe Variable oder einen Speicherort, ohne dass diese als separater Eingang oder Ausgang geführt werden muss. Der Baustein puffert den gelesenen Wert, sodass der Ausgang `OUT` auch nach Änderungen der Quelle stabil bleibt, bis die nächste Anforderung erfolgt.

## Technische Besonderheiten

- **Verwendung von InOut-Variablen**: `IN` ist als `InOut` deklariert, d.h. sie kann sowohl gelesen als auch geschrieben werden. In diesem Fall wird sie nur gelesen, was eine flexible Kopplung mit dem aufrufenden Netzwerk ermöglicht.
- **Pufferung**: Der Ausgang `OUT` speichert den gelesenen Wert bis zur nächsten Aktualisierung durch `REQ`. Dies verhindert unerwünschte Seiteneffekte durch Änderungen der Quelle.
- **Keine Zustandslogik**: Der Baustein besteht aus einem einzigen Zustand (`REQ`), der auf jedes eingehende Ereignis sofort reagiert. Keine Verzögerung, kein Warten auf Bedingungen.
- **Initialwerte**: Sowohl `IN` als auch `OUT` sind mit `0` initialisiert, was einen definierten Startzustand gewährleistet.

## Zustandsübersicht

Der Baustein verwendet einen einfachen ECA-Zustandsautomaten mit genau einem Zustand:

| Zustand | Aktion | Ausgehendes Ereignis |
|---------|--------|----------------------|
| `REQ`   | `REQ`-Algorithmus (OUT := IN) | `CNF` |

- Jedes eintreffende `REQ`-Ereignis führt sofort zur Aktion und sendet `CNF`. Es gibt keine Verzweigungen, Fehlerzustände oder Zeitverhalten.

## Anwendungsszenarien

- **Auslesen von Hardware-Eingängen**: Wenn ein SINT-Wert von einem analogen Eingangsbaustein oder einer speicherprogrammierbaren Steuerung (SPS) gelesen werden muss, kann `GET_SINT` als Schnittstelle verwendet werden, um den aktuellen Wert zu einem bestimmten Zeitpunkt abzugreifen.
- **Zugriff auf geteilte Variablen**: In einer verteilten Steuerung kann `GET_SINT` genutzt werden, um den Wert einer globalen oder peripheren Variable in eine lokale Verarbeitungskette zu übernehmen.
- **Datenkonsistenz**: Durch die Pufferung wird sichergestellt, dass der gelesene Wert während der gesamten Verarbeitung des nachfolgenden Netzwerks stabil bleibt, auch wenn die Quelle asynchron aktualisiert wird.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Datentyp | Besonderheit |
|----------|----------|--------------|
| `GET_BOOL` | BOOL   | Gleiche Funktionsweise, aber für boolesche Werte. |
| `GET_INT`  | INT    | Entspricht `GET_SINT`, jedoch mit 16-Bit-Ganzzahl (Integer). |
| `GET_REAL` | REAL   | Für Gleitkommazahlen. |
| `MOVE` (generic) | Beliebig | Ein generischer MOVE-Baustein kann ebenfalls Werte kopieren, benötigt aber separate Ein- und Ausgänge. `GET_SINT` nutzt dagegen InOut-Variablen, was bei der Kopplung an periphere Adressen praktischer sein kann. |

Allen `GET_*`-Bausteinen ist gemeinsam, dass sie einen Wert aus einer InOut-Quelle lesen und als gepufferten Ausgang bereitstellen. Im Gegensatz dazu überschreibt `SET_*` den Wert der Quelle.

## Fazit

`GET_SINT` ist ein minimalistischer und zuverlässiger Baustein zum Auslesen eines `SINT`-Wertes aus einer InOut-Variable. Seine Einfachheit macht ihn zu einem idealen Baustein für das Lesen von peripheren oder geteilten Daten in IEC 61499-Anwendungen. Die Verwendung der InOut-Schnittstelle reduziert den Verdrahtungsaufwand und fördert eine saubere Trennung zwischen Datenzugriff und Verarbeitungslogik.