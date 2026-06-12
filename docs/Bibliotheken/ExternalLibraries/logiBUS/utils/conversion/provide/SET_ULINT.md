# SET_ULINT


![SET_ULINT](./SET_ULINT.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **SET_ULINT** dient dazu, einen unsignierten 64-Bit-Ganzzahlwert (ULINT) von einem Dateneingang auf eine InOut-Variable zu schreiben. Er wird typischerweise verwendet, um Werte in verbundene Variablen oder globale Speicherstellen zu setzen, die auch von anderen Bausteinen gelesen werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Normaler Ausführungsauftrag. Der Wert von `IN` wird auf die InOut-Variable `OUT` übertragen und nach Abschluss der Ereignisausgang `CNF` gesendet. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung der Ausführung. Wird ausgelöst, sobald die Zuweisung von `IN` an `OUT` erfolgt ist. |

### **Daten-Eingänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| IN   | ULINT    | Der zu schreibende Wert. Voreinstellung: `0`. |

### **Daten-Ausgänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| OUT  | ULINT    | InOut-Variable – Ziel der Zuweisung. Sie kann sowohl gelesen als auch beschrieben werden und steht nach der Ausführung auf dem neuen Wert. |

### **Adapter**
Keine.

## Funktionsweise
Der Funktionsblock ist als einfacher Zustandsautomat (SimpleFB) realisiert. Ein einziger Zustand `REQ` führt bei Aktivierung den Algorithmus `REQ` aus:  
```
OUT := IN;
```
Anschließend wird der Ereignisausgang `CNF` gesendet. Der übergebene Wert `IN` wird also direkt in die InOut-Variable `OUT` kopiert. Da `OUT` als InOut deklariert ist, kann der Baustein den vorherigen Wert von `OUT` nicht lesen – es erfolgt eine reine Überschreibung.

## Technische Besonderheiten
- Der Baustein verwendet eine **InOut-Variable** (`OUT`), die im IEC 61499-Modell sowohl als Eingangs- als auch als Ausgangsport fungiert. Dies ermöglicht direkte Verbindungen zu Variablen, die von mehreren Bausteinen gemeinsam genutzt werden.
- Das Paket `logiBUS::utils::conversion::provide` im CompilerInfo zeigt an, dass der FB für die Nutzung im logiBUS-Ökosystem vorgesehen ist.
- Der Algorithmus ist sehr einfach gehalten – lediglich eine ST-Zuweisung – und daher extrem schnell ausführbar.
- Der initiale Wert von `OUT` ist `0`, sodass bei erstmaliger Nutzung ohne vorherige Initialisierung ein definierter Startwert vorliegt.

## Zustandsübersicht
Der FB besitzt genau einen EC-Zustand:

| Zustand | Aktion | Ausgabe |
|---------|--------|---------|
| REQ     | `REQ` (OUT := IN) | CNF |

Nach dem Start oder Reset befindet sich der FB im Zustand `REQ`. Jeder `REQ`-Ereignisimpuls löst die Aktion aus und erzeugt danach `CNF`.

## Anwendungsszenarien
- **Parametriert von Echtzeitsystemen**: Setzen von Sollwerten oder Konfigurationsparametern in einer Variablen, die von mehreren Funktionsblöcken überwacht wird.
- **Globale Statusvariablen**: Schreiben von Fehlercodes oder Betriebszuständen in eine zentrale `ULINT`-Variable.
- **Test- und Diagnosezwecke**: Gezieltes Überschreiben von Werten in einer laufenden Steuerung zu Analysezwecken.

## Vergleich mit ähnlichen Bausteinen
- **SET_INT, SET_DINT, SET_LINT**: Gleichartige Bausteine für andere Ganzzahltypen (INT, DINT, LINT). Die Funktionsweise ist identisch, nur der Datentyp unterschiedlich.
- **MOVE_ULINT**: Viele Bibliotheken enthalten einen MOVE-Baustein, der einen Wert von einem Eingang auf einen Ausgang kopiert. `SET_ULINT` unterscheidet sich durch die Verwendung einer **InOut-Variable**, die es erlaubt, direkt auf eine bestehende Variable zuzugreifen, ohne den Umweg über einen reinen Ausgang.

## Fazit
Der **SET_ULINT**-Funktionsblock ist ein einfaches, aber effektives Werkzeug zum Setzen von ULINT-Werten in gemeinsam genutzten Variablen. Seine InOut-Schnittstelle macht ihn besonders geeignet für Anwendungen, in denen Werte überschrieben werden müssen, ohne dass der vorherige Zustand ausgewertet wird. Aufgrund seiner schlanken Implementierung eignet er sich gut für zeitkritische Steuerungen.