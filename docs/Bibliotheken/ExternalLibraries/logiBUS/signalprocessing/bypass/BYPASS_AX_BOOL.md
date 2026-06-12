# BYPASS_AX_BOOL


![BYPASS_AX_BOOL](./BYPASS_AX_BOOL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BYPASS_AX_BOOL` realisiert eine Bypass-Funktionalität für ein boolesches Signal. Er leitet den Wert des Eingangs `IN` direkt zum Ausgang `OUT` weiter und erzeugt parallel dazu einen über einen Adapter angebundenen Bypass-Pfad. Dieser Pfad erlaubt das Einblenden eines externen Signals (`BY_IN.D1`) in die interne Logik und gibt das Ergebnis über den Ausgangsadapter `BY_OUT` aus.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| REQ  | Event | Normaler Ausführungsanstoß |

### **Ereignis-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| CNF  | Event | Bestätigung der Ausführung |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| IN   | BOOL | Eingangssignal |

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| OUT  | BOOL | Durchgeschleiftes Eingangssignal (identisch zu IN) |

### **Adapter**
| Rolle | Name | Typ | Richtung | Beschreibung |
|-------|------|-----|----------|--------------|
| Plug  | BY_OUT | `adapter::types::unidirectional::AX` | Ausgang | Gibt den gespeicherten Bypass-Zustand aus |
| Socket| BY_IN  | `adapter::types::unidirectional::AX` | Eingang | Nimmt das Bypass-Eingangssignal (D1) und Ereignis (E1) entgegen |

## Funktionsweise
Bei jedem Ereignis `REQ` wird unverzüglich der Ausgang `CNF` gesetzt (Ereignisdurchschleifung). Gleichzeitig wird das Datenwort `IN` direkt auf `OUT` kopiert. 

Intern wird eine ODER-Verknüpfung zwischen `IN` und dem Adaptersignal `BY_IN.D1` gebildet. Diese Verknüpfung wird durch `REQ` oder durch das Ereignis `BY_IN.E1` angestoßen. Das Ergebnis der ODER-Operation wird in einem flankengetakteten D-Flipflop gespeichert; die Taktflanke wird durch die Beendigung der ODER-Berechnung (Ereignis `CNF` des internen OR-Bausteins) erzeugt. Der gespeicherte Wert des Flipflops wird über den Ausgangsadapter `BY_OUT.D1` ausgegeben und der zugehörige Ereignisausgang `BY_OUT.E1` wird aktiviert.

Der Baustein arbeit somit als Kombination aus einem reinen Durchschleifer für `IN → OUT` und einem flankengesteuerten Bypass-Pfad, der das eingehende Adaptersignal mit dem aktuellen `IN` verknüpft und speichert.

## Technische Besonderheiten
- Die direkte Verbindung `IN → OUT` erfolgt ohne Verzögerung durch interne Logik – der Wert liegt sofort an.
- Der Bypass-Pfad nutzt ein D-Flipflop (`E_D_FF`) zur Zustandsspeicherung. Der gespeicherte Wert wird nur bei einer steigenden Flanke des internen Takts aktualisiert, der durch die ODER-Berechnung erzeugt wird.
- Der Adapter `BY_IN` muss angeschlossen sein, um den Bypass-Pfad zu nutzen; ohne Anschluss verhält sich der Baustein wie ein einfacher Durchschleifer.
- Das Ereignis `BY_IN.E1` kann die ODER-Berechnung unabhängig von `REQ` auslösen, sodass der Bypass auch asynchron aktualisiert werden kann.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten, aber der interne D-Flipflop speichert einen booleschen Zustand (`Q = 0` oder `Q = 1`). Dieser Zustand repräsentiert den zuletzt gültigen Bypass-Wert, der über den Ausgangsadapter ausgegeben wird. Der Zustand ändert sich nur bei einer steigenden Flanke des Taktsignals (Beendigung einer ODER-Berechnung).

## Anwendungsszenarien
- **Manuelles Übersteuern** eines digitalen Signals in der Automatisierungstechnik: Der normale Wert (`IN`) wird an die Steuerung weitergegeben, während über den Bypass ein Handeingriff (z. B. über eine Bedienschnittstelle) zugemischt und gespeichert werden kann.
- **Signalüberwachung und -korrektur**: Ein externes Überwachungssystem kann über den Bypass-Adapter einen Korrekturwert einblenden, der mit dem Originalsignal verknüpft wird.
- **Bypass für Testzwecke**: Während der Inbetriebnahme kann der normale Pfad (IN→OUT) aufrechterhalten, gleichzeitig aber ein Testsignal über den Bypass eingeschleift werden.

## Vergleich mit ähnlichen Bausteinen
- **Einfacher Durchschleifer** (z. B. `MOVE`): Würde nur `IN` auf `OUT` übertragen, ohne Möglichkeit eines externen Eingriffs.
- **Set-/Reset-Flipflop** (z. B. `SR`): Erlaubt das Setzen und Rücksetzen eines Ausgangs, jedoch ohne direkte Durchschleifung des Eingangs.
- **Auswahlbaustein** (z. B. `SEL`): Wählt zwischen zwei Eingängen – hier wird dagegen der Eingang immer durchgereicht und der Bypass additiv verknüpft.

Der `BYPASS_AX_BOOL` kombiniert die Durchschleifung mit einer integrierbaren, flankengesteuerten Logik für externe Signale.

## Fazit
Der Funktionsblock `BYPASS_AX_BOOL` ist ein spezialisierter Baustein für Anwendungen, bei denen ein boolesches Signal unverändert weitergeleitet, aber gleichzeitig ein externes Bypass-Signal zugemischt und gespeichert werden soll. Die Kombination aus direkter Durchschleifung und flankengesteuerter ODER-Verknüpfung mit Speicherung ermöglicht flexible Eingriffe in Signalketten, ohne die normale Funktion zu unterbrechen. Der Baustein eignet sich besonders für Steuerungssysteme, die sowohl einen Standardbetrieb als auch temporäre oder dauerhafte Überlagerungen benötigen.