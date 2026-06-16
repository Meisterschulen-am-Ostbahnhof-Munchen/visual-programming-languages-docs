# ATM_D_FF_TMIN


![ATM_D_FF_TMIN](./ATM_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ATM_D_FF_TMIN` realisiert ein taktgesteuertes D‑Flipflop (Data Latch), das den anliegenden Datenwert bei einem Taktereignis übernimmt und als gespeicherten Wert ausgibt. Eine Besonderheit ist die einstellbare Mindestzeit (`Tmin`) zwischen zwei aufeinanderfolgenden Ausgangsereignissen, die eine definierte Totzeit garantiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                        |
|-------|--------|----------------------------------|
| INIT  | EInit  | Initialisierungsanforderung (mit `Tmin`) |

### **Ereignis-Ausgänge**

| Name  | Typ    | Kommentar                        |
|-------|--------|----------------------------------|
| INITO | EInit  | Initialisierungsbestätigung      |

### **Daten-Eingänge**

| Name  | Typ    | Kommentar                                      |
|-------|--------|------------------------------------------------|
| Tmin  | TIME   | Minimaler zeitlicher Abstand zwischen zwei EO-Ereignissen |

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Datenausgänge. Der gespeicherte Wert wird über den Adapter-Ausgang `Q.D1` bereitgestellt.

### **Adapter**

| Richtung | Name | Typ                                      | Kommentar            |
|----------|------|------------------------------------------|----------------------|
| Eingang (Socket) | I    | `adapter::types::unidirectional::ATM`    | Zu übernehmender Wert |
| Ausgang (Plug)   | Q    | `adapter::types::unidirectional::ATM`    | Gespeicherter Wert    |

Der Adapter `ATM` bietet je einen Ereignis- und einen Datenkanal (`E1`, `D1` für Eingang; `E1`, `D1` für Ausgang).

## Funktionsweise
1. **Initialisierung**: Durch ein Ereignis an `INIT` wird der Baustein initialisiert und der Parameter `Tmin` übernommen.
2. **Takten**: Ein Ereignis am Adapter-Eingang `I.E1` (Takt) veranlasst den Baustein, den aktuellen Datenwert von `I.D1` zu übernehmen. Bei gültiger Übernahme wird der Wert am Adapter-Ausgang `Q.D1` ausgegeben und gleichzeitig ein Ereignis an `Q.E1` gesendet.
3. **Minimale Ausgangsverzögerung**: Nach jedem ausgegebenen Ereignis (`Q.E1`) wird eine interne Sperre aktiviert. Erst nach Ablauf der Zeit `Tmin` kann ein weiteres Taktereignis zu einer erneuten Ausgabe führen. Geht innerhalb der Sperrzeit ein neues Taktsignal ein, wird es ignoriert oder die Ausgabe bis zum Ablauf von `Tmin` verzögert (abhängig von der Implementierung des internen FB `E_D_FF_ANY_TMIN`).

## Technische Besonderheiten
- **Totzeit-Regelung**: Der Parameter `Tmin` erzwingt eine minimale Pause zwischen zwei Ausgangsereignissen – nützlich, um nachgeschaltete Komponenten zu schützen oder Signalflanken zu entprellen.
- **Interne Realisierung**: Der Baustein verwendet intern den FB `iec61499::events::E_D_FF_ANY_TMIN`, der die eigentliche Flipflop-Logik mit Zeitüberwachung bereitstellt. Der `ATM_D_FF_TMIN` fungiert als Schnittstellenanpassung für den Adapter `ATM`.
- **Adapter-Schnittstelle**: Sowohl Eingangs- als auch Ausgangsdaten werden über unidirektionale Adapter ausgetauscht, was eine lose Kopplung in der Applikation ermöglicht.

## Zustandsübersicht
Obwohl kein explizites Zustandsdiagramm vorliegt, lassen sich folgende logische Zustände ableiten:
1. **Bereit**: Wartet auf ein Taktereignis, keine Sperre aktiv.
2. **Gesetzt**: Wert wurde übernommen und ausgegeben, die Sperre `Tmin` läuft.
3. **Gesperrt**: Während `Tmin` werden eingehende Taktereignisse ignoriert oder zurückgehalten.

Nach Ablauf der Sperre kehrt der Baustein in den Zustand **Bereit** zurück.

## Anwendungsszenarien
- **Signalaufbereitung** in der Automatisierungstechnik, bei der ein Schaltsignal nach einer definierten Mindestpause erneut ausgewertet werden soll (z. B. Totzeit bei Ventilumschaltungen).
- **Entprellung** von binären Sensoren, bei denen ein nachgeschalteter Ausgang nur nach einer stabilen Zeit von `Tmin` erzeugt werden darf.
- **Synchronisation** von Datenströmen, bei denen eine minimale Paketlücke eingehalten werden muss.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑D‑Flipflop** (z. B. `E_D_FF`): Liefert sofort nach jedem Takt einen Ausgang – ohne zeitliche Einschränkung. Der `ATM_D_FF_TMIN` erweitert dies um die Totzeit `Tmin`.
- **Monostabile Kippglieder** (Timer): Erzeugen einen Impuls definierter Länge. Der `ATM_D_FF_TMIN` hingegen sperrt nur die Ausgabe, ohne den Ausgangspegel zurückzusetzen.

Der vorliegende Baustein vereint die Eigenschaften eines Flipflops mit einer einstellbaren Mindestausblendzeit und ist daher für zeitkritische Steuerungsaufgaben besonders geeignet.

## Fazit
`ATM_D_FF_TMIN` ist ein spezialisierter D‑Flipflop‑Baustein, der die minimale Verweilzeit zwischen zwei Ausgangsereignissen garantiert. Die Nutzung von Adaptern vereinfacht die Integration in modulare Steuerungsanwendungen, während die einstellbare Totzeit hohe Flexibilität für unterschiedliche physikalische Randbedingungen bietet. Er ist eine sinnvolle Erweiterung der IEC‑61499‑Bibliothek für zeitdiskrete Signalverarbeitung.