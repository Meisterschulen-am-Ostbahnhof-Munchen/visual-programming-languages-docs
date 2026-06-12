# GET_ULINT


![GET_ULINT](./GET_ULINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_ULINT** dient dazu, den aktuellen Wert einer als InOut-Parameter bereitgestellten Variable vom Typ `ULINT` (unsigned 64‑Bit‑Integer) zu lesen und an einem Datenausgang als gepufferten Wert bereitzustellen. Auf eine Anfrage (REQ) wird der Wert der Quelle eingelesen und am Ausgang `OUT` ausgegeben. Anschließend wird die Bestätigung (CNF) gesendet. Damit ist GET_ULINT ein einfacher Lese-Baustein für InOut‑Variablen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name  | Typ    | Kommentar               | Mit Daten |
|-------|--------|-------------------------|-----------|
| `REQ` | Event  | Normal Execution Request | `IN`      |

### **Ereignis-Ausgänge**
| Name  | Typ    | Kommentar                | Mit Daten       |
|-------|--------|--------------------------|-----------------|
| `CNF` | Event  | Execution Confirmation   | `OUT`, `IN`     |

### **Daten-Eingänge**
| Name | Typ    | Kommentar       |
|------|--------|-----------------|
| -    | -      | -               |

### **Daten-Ausgänge**
| Name | Typ    | Kommentar                | Initialwert |
|------|--------|--------------------------|-------------|
| `OUT`| ULINT  | Buffered output value    | 0           |

### **Adapter**
Keine Adapter vorhanden.

### **InOut‑Variablen (intern)**
Zusätzlich zu den reinen Ein‑/Ausgängen besitzt der Baustein eine InOut‑Variable:
| Name | Typ    | Kommentar                    | Initialwert |
|------|--------|------------------------------|-------------|
| `IN` | ULINT  | Source variable (InOut)      | 0           |

## Funktionsweise
Der Baustein verarbeitet eine einzige Aktion:
1. Ein eingehendes Ereignis am Eingang `REQ` löst die Ausführung des Algorithmus `REQ` aus.
2. Im Algorithmus wird der aktuelle Wert der InOut‑Variablen `IN` direkt in den Ausgang `OUT` kopiert:  
   `OUT := IN;`
3. Nach Abschluss der Zuweisung wird das Ereignis `CNF` ausgegeben. Die Ausgänge `OUT` und `IN` werden mit dem Ereignis `CNF` assoziiert, sodass aufrufende Bausteine den aktualisierten Wert verarbeiten können.

Durch die Verwendung einer InOut‑Variablen kann der Baustein auf einen Speicherplatz außerhalb des eigenen Kontexts zugreifen, ohne diesen über einen herkömmlichen Eingang zu erhalten. Der Wert wird bei jeder Anfrage frisch gelesen, wodurch sich der Baustein als Lese‑Puffer eignet.

## Technische Besonderheiten
- **InOut‑Variable:** Der Baustein nutzt eine `IN`‑Variable mit der Eigenschaft `InOut`. Dies ermöglicht das Verknüpfen mit einer übergeordneten Variablen (z.B. aus einem Ressourcen‑ oder globalen Datenraum), ohne dass der Baustein die Variable über einen normalen Daten‑Eingang erhalten muss. Der Zugriff erfolgt referenzbasiert.
- **Typ ULINT:** Sowohl `IN` als auch `OUT` sind als vorzeichenloser 64‑Bit‑Integer (ULINT) deklariert – geeignet für große Zählwerte, Zeitstempel oder andere Werte im Bereich 0 … 2⁶⁴‑1.
- **Sofortiges Lesen:** Der Algorithmus ist extrem kurz (eine Zuweisung), wodurch die Ausführungszeit vernachlässigbar ist.

## Zustandsübersicht
Der Baustein ist als SimpleFB mit einem einzigen ECC‑Zustand implementiert:

| Zustand | Aktion | Ausgabeereignis | Bedeutung |
|---------|--------|------------------|-----------|
| `REQ`   | `REQ` (OUT := IN) | `CNF` | Auf eine Anfrage wird der Wert gelesen und bestätigt. |

Es gibt keine weiteren Zustände, keine Verzweigungen und keine internen Speichervariablen (außer dem Ausgang `OUT` selbst, der den letzten gelesenen Wert puffert).

## Anwendungsszenarien
- **Sichere Leseoperation:** Ein übergeordneter Baustein möchte einen aktuellen Wert aus einer gemeinsam genutzten Variablen (z.B. einem Sensorwert, der von einer anderen Steuerungskomponente beschrieben wird) abfragen, ohne den Wert dauerhaft zu referenzieren.
- **Wertpuffer für asynchrone Verarbeitung:** In einem zeitgesteuerten Ablauf kann `GET_ULINT` aufgerufen werden, um einen Schnappschuss einer globalen Zählervariablen zu nehmen und diesen zwischenzuspeichern.
- **Parametrierung über InOut‑Schnittstellen:** Wenn der Baustein in eine übergeordnete Komponente eingebettet ist, kann die InOut‑Variable direkt mit einer Datenverbindung des Elternbausteins verbunden werden, sodass Leseanfragen auf diese Variable zeigen.

## Vergleich mit ähnlichen Bausteinen
- **GET_DINT / GET_LINT / GET_UINT:** Analoge Bausteine für andere Integer‑Typen (DINT, LINT, UINT etc.). Die Funktionsweise ist identisch, der einzige Unterschied ist der Datentyp.
- **READ_ULINT (hypothetisch):** Ein Baustein, der statt einer InOut‑Variable einen separaten Dateneingang für den Quellwert verwendet. Das hätte den Vorteil, dass der Baustein lose gekoppelt ist, aber den Nachteil, dass der Quellwert als Datenstrom mitgeführt werden müsste. Der InOut‑Ansatz von `GET_ULINT` erlaubt eine direkte Referenz auf eine gemeinsam genutzte Variable, was in manchen Architekturen bevorzugt wird.
- **SAMPLE_ULINT:** Ein Baustein, der bei jedem Ereignis den aktuellen Wert eines Eingangs abtastet und puffert – ebenfalls ähnlich, jedoch mit normalem Dateneingang statt InOut.

## Fazit
Der `GET_ULINT`‑Funktionsblock bietet eine einfache und effiziente Möglichkeit, den aktuellen Wert einer InOut‑Variablen vom Typ `ULINT` zu lesen und als gepufferten Ausgang bereitzustellen. Die Verwendung einer InOut‑Variable erlaubt den direkten, referenzbasierten Zugriff auf externe Speicherstellen, ohne zusätzliche Datenkopien während des Aufrufs. Dank seines minimalistischen Zustandsautomaten eignet er sich hervorragend für zeitkritische Anwendungen, in denen ein schnelles Lesen eines Wertes ohne Nebenwirkungen erforderlich ist.