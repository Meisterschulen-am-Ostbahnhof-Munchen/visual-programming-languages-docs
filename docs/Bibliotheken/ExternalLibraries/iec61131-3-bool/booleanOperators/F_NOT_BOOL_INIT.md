# F_NOT_BOOL_INIT


![F_NOT_BOOL_INIT](./F_NOT_BOOL_INIT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `F_NOT_BOOL_INIT` realisiert die logische Negation (NOT) eines booleschen Eingangssignals und erweitert die reine NOT-Funktion um einen Initialisierungsmechanismus. Er ist als standardisierter Baustein gemäß IEC 61131-3 für den Einsatz in speicherprogrammierbaren Steuerungen (SPS) konzipiert. Der FB ermöglicht es, bei der Initialisierung eine erste Negation auszulösen und den Ergebniswert am Ausgang bereitzustellen, bevor der normale zyklische Betrieb beginnt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ   | Mit Variablen | Beschreibung |
|----------|-------|---------------|--------------|
| `INIT`   | EInit | `IN`          | Initialisierungsanforderung – der FB wird einmalig initialisiert und der Eingang negiert. |
| `REQ`    | Event | `IN`          | Normale Verarbeitungsanforderung – die logische Negation wird auf den aktuellen Eingangswert angewendet. |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Mit Variablen | Beschreibung |
|----------|-------|---------------|--------------|
| `INITO`  | EInit | `OUT`         | Bestätigung der Initialisierung – wird nach erfolgreicher Initialisierung ausgegeben. |
| `CNF`    | Event | `OUT`         | Bestätigung der normalen Verarbeitung – wird nach jeder Ausführung auf `REQ` gesendet. |

### **Daten-Eingänge**
| Variable | Typ    | Beschreibung |
|----------|--------|--------------|
| `IN`     | BOOL   | Eingangswert, der negiert werden soll. |

### **Daten-Ausgänge**
| Variable | Typ    | Beschreibung |
|----------|--------|--------------|
| `OUT`    | BOOL   | Negierter Wert des Eingangs (`NOT IN`). |

### **Adapter**
Keine.

## Funktionsweise
Der Baustein delegiert die eigentliche Negationsfunktion an den internen FB `F_NOT` (aus der Bibliothek `iec61131::bitwiseOperators`). Die Verarbeitung erfolgt ereignisgesteuert:

- **Bei `INIT`:** Der Eingangswert `IN` wird sofort über die Datenverbindung an den internen `F_NOT` übergeben. Gleichzeitig wird das Ereignis `REQ` an den internen FB gesendet, der die Negation berechnet und das Ergebnis an den Ausgang `OUT` weitergibt. Nach Abschluss dieser Operation wird das Ereignis `INITO` am Ausgang des Hauptbausteins ausgegeben. Dadurch wird der Ausgang `OUT` mit dem negierten Initialwert gesetzt.
- **Bei `REQ` (im laufenden Betrieb):** Der aktuelle Wert von `IN` wird an den internen `F_NOT` übergeben und negiert. Das Ergebnis wird auf `OUT` geschrieben, und anschließend wird das Ereignis `CNF` ausgelöst.

Somit führt sowohl `INIT` als auch `REQ` zur gleichen Kernfunktionalität (Negation), unterscheiden sich jedoch im ausgelösten Ereignis: `INIT` erzeugt `INITO`, `REQ` erzeugt `CNF`.

## Technische Besonderheiten
- Der Baustein enthält keine eigene algorithmische Logik, sondern nutzt einen internen Unterbaustein (`F_NOT`). Dies fördert die Wiederverwendung und Konsistenz.
- Der Initialisierungsmechanismus erlaubt es, den Ausgang bereits vor dem ersten „normalen“ Aufruf mit dem negierten Eingang zu belegen – nützlich in SPS-Programmen, bei denen Startwerte definiert werden müssen.
- Die gleichzeitige Verwendung von `INIT` und `REQ` ermöglicht eine klare Trennung zwischen Startverhalten und zyklischem Betrieb.
- Durch die Mitnahme der Eingangsvariablen in den Ereignissen (WITH) wird sichergestellt, dass die Daten immer aktuell zur Verfügung stehen.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten, da die gesamte Logik im internen Netzwerk abgebildet ist. Es liegt implizit folgendes Verhalten vor:

1. **Initialzustand:** Nach dem Start der SPS sind Ausgänge und interne Werte undefiniert.
2. **Nach `INIT`:** Der Ausgang `OUT` wird auf den negierten Wert von `IN` gesetzt; der FB ist betriebsbereit.
3. **Nach `REQ`:** Für jeden `REQ`-Impuls wird die Negation erneut ausgeführt und `OUT` aktualisiert.

Eine wiederholte Auslösung von `INIT` (z. B. nach einem Reset) führt erneut zur Initialisierung und setzt `OUT` auf den negierten aktuellen Eingangswert.

## Anwendungsszenarien
- **Initialisierung eines Steuerausgangs:** Ein Ausgang soll in der Startphase den negierten Wert eines Sensorsignals annehmen, bevor das zyklische Programm startet.
- **Fehlerüberwachung:** Bei einer Startsequenz wird geprüft, ob ein Eingangssignal den negierten Zustand eines Freigabesignals aufweist.
- **Sicherheitslogik:** Verwendung in Sicherheitsfunktionen, bei denen ein initialer Negationsschritt zwingend erforderlich ist (z. B. NOT-Verknüpfung nach Systemhochlauf).

## Vergleich mit ähnlichen Bausteinen
| Baustein           | Beschreibung                                  | Unterschied zu `F_NOT_BOOL_INIT` |
|--------------------|-----------------------------------------------|----------------------------------|
| `F_NOT` (Standard) | Reine Negation ohne Initialisierungsereignis. | Fehlt das `INIT`/`INITO`-Paar; nach Systemstart ist der Ausgang nicht definiert. |
| `F_NOT_BOOL_INIT`  | Wie `F_NOT`, aber mit explizitem Initialisierungsereignis. | Bietet definiertes Startverhalten und gibt bei Initialisierung ein separates Quittungsereignis aus. |

Der Standard `F_NOT` ist ausreichend, wenn das Startverhalten durch den übergeordneten Steuerungsablauf geregelt wird. Der initialisierbare Baustein ist dann vorteilhaft, wenn der FB selbst die Kontrolle über seine erste Ausführung besitzen soll.

## Fazit
`F_NOT_BOOL_INIT` ist ein nützlicher Baustein, der die einfache NOT-Operation um eine Initialisierungsfazilität ergänzt. Er eignet sich besonders für SPS-Anwendungen, bei denen ein definierter Startwert des negierten Ausgangs erforderlich ist. Durch die klare Ereignissteuerung und die interne Nutzung des bewährten `F_NOT`-Bausteins bleibt die Implementierung robust und übersichtlich. Der FB stellt eine sinnvolle Erweiterung der IEC-61131-Bitoperatoren dar.