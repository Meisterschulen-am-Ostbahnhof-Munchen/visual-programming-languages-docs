# AB_MUX_3


![AB_MUX_3](./AB_MUX_3.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein `AB_MUX_3` ist ein generischer Multiplexer für Adapter vom Typ `adapter::types::unidirectional::AB`. Er wählt abhängig vom Wert des Index `K` (0, 1 oder 2) einen von drei Eingängen (`IN1`, `IN2`, `IN3`) aus und leitet diesen auf den Ausgang `OUT` durch. Die Umschaltung wird durch das Ereignis `REQ` ausgelöst und nach Abschluss mit `CNF` quittiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name  | Typ   | Kommentar                |
|-------|-------|--------------------------|
| `REQ` | Event | Set Index K (mit Var `K`)|

### **Ereignis-Ausgänge**
| Name  | Typ   | Kommentar                       |
|-------|-------|----------------------------------|
| `CNF` | Event | Confirmation of Set Index K      |

### **Daten-Eingänge**
| Name | Typ   | Kommentar   |
|------|-------|-------------|
| `K`  | UINT  | Index (0-2) |

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Name | Richtung | Typ                                  | Kommentar                     |
|------|----------|--------------------------------------|-------------------------------|
| `OUT`| Plug     | `adapter::types::unidirectional::AB` | Ausgang – verbindet den ausgewählten Eingang |
| `IN1`| Socket   | `adapter::types::unidirectional::AB` | Eingangswert 1 (bei K=0)      |
| `IN2`| Socket   | `adapter::types::unidirectional::AB` | Eingangswert 2 (bei K=1)      |
| `IN3`| Socket   | `adapter::types::unidirectional::AB` | Eingangswert 3 (bei K=2)      |

## Funktionsweise
1. Der Baustein wartet auf ein `REQ`-Ereignis.
2. Beim Eintreffen wird der Wert von `K` gelesen.
3. Abhängig von `K` (0, 1 oder 2) wird der entsprechende Socket-Adapter (`IN1`, `IN2`, `IN3`) auf den Plug-Adapter `OUT` durchgeschaltet.
4. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` gesendet.
5. Der Baustein kehrt in den Wartezustand zurück und kann erneut durch `REQ` gesteuert werden.

## Technische Besonderheiten
- Der Baustein ist generisch und wird in der Entwicklungsumgebung als `GEN_AB_MUX` geführt (Attribut `GenericClassName`).
- Alle Adapter sind unidirektional vom Typ `adapter::types::unidirectional::AB`.
- Es sind keine Datenausgänge vorhanden – die gesamte Datenweitergabe erfolgt über den Adapter `OUT`.
- Der Index `K` ist als `UINT` (vorzeichenlose Ganzzahl) definiert, Werte außerhalb 0‑2 sind undefiniert.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine (ECC) in der XML-Definition. Die implizite Ablaufsteuerung lässt sich wie folgt darstellen:

```
[Idle] → bei REQ → [Execute] → setze OUT gemäß K → sende CNF → [Idle]
```

- **Idle**: Warten auf ein `REQ`-Ereignis.
- **Execute**: Auswerten von `K`, Durchschalten des Adapters, Senden von `CNF`.

## Anwendungsszenarien
- **Signalumschaltung**: Auswahl zwischen drei verschiedenen AB‑Adapter-Signalen (z. B. Sensordaten, Steuerbefehle).
- **Betriebsartenwahl**: Umschalten zwischen unterschiedlichen Konfigurationsquellen in einer Automatisierungsanwendung.
- **Agrartechnik**: Beispielsweise das Umschalten zwischen verschiedenen Messwerten (Drehzahl, Temperatur, Druck) auf einen gemeinsamen Ausgang.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑MUX‑Bausteine** (z. B. `MUX_2`, `MUX_4`) arbeiten meist mit einfachen Datentypen (BOOL, INT) statt mit Adaptern. `AB_MUX_3` ist speziell für AB‑Adapter ausgelegt.
- Im Gegensatz zu einem generischen Multiplexer mit variabler Anzahl von Eingängen ist dieser Baustein auf drei Eingänge festgelegt, was die Handhabung vereinfacht und die Typsicherheit erhöht.

## Fazit
Der `AB_MUX_3` ist ein kompakter und spezialisierter Funktionsbaustein zur Auswahl eines von drei AB‑Adapter-Eingängen. Er eignet sich besonders für Anwendungen, die eine zuverlässige Umschaltung zwischen verschiedenen Adapterquellen erfordern, ohne dass zusätzliche Datenkonvertierungen nötig sind.