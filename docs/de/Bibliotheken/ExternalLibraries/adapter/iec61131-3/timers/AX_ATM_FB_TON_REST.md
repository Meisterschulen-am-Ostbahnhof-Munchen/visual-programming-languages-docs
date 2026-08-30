# AX_ATM_FB_TON_REST

![AX_ATM_FB_TON_REST](AX_ATM_FB_TON_REST.svg)

* * * * * * * * * *

## Einleitung

`AX_ATM_FB_TON_REST` umhüllt [AX_ATM_FB_TON](AX_ATM_FB_TON.md) mit einem dritten Adapter-Plug,
`REST`, der die verbleibende Zeit (`PT - ET`) als REAL-Sekundenwert führt. Mehrere Anwendungen
brauchen nicht nur "ist der Timer abgelaufen" (`Q`) oder "wie viel Zeit ist vergangen" (`ET`),
sondern "wie viel Zeit bleibt noch" für eine Countdown-Anzeige — das extern aus `PT`/`ET` zu
berechnen bedeutet, an jeder Verwendungsstelle dieselbe Adapterkette (`ATM_SUB` →
`ATM_IN_S_TO_ALR` → `ALR_TO_AR`) zu wiederholen. Dieser Baustein erledigt das einmal, intern, sodass
der Aufrufer `REST` als einen einzigen, publish-fertigen Adapter-Plug erhält.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ** (Event, nicht auslösend): dieselbe Rolle wie bei `AX_ATM_FB_TON` — die Anwendung hängt
  hier typischerweise einen `E_CYCLE` an, damit `ET`/`REST` aktualisiert bleiben, während der Timer
  läuft.

### **Ereignis-Ausgänge**

Keine eigenen; Ereignisse laufen ausschließlich über die Adapter-Plugs `Q`, `ET` und `REST`.

### **Daten-Eingänge**

Keine eigenen. Alle Daten werden über die Adapter-Sockets übertragen.

### **Daten-Ausgänge**

Keine eigenen. Alle Daten werden über die Adapter-Plugs übertragen.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::AX` | Startsignal |
| Socket (Eingang) | `PT` | `adapter::types::unidirectional::ATM` | Sollzeit |
| Plug (Ausgang) | `Q` | `adapter::types::unidirectional::AX` | Ausgang, TRUE sobald `IN` seit `PT` ansteht |
| Plug (Ausgang) | `ET` | `adapter::types::unidirectional::ATM` | Abgelaufene Zeit, Event nur bei Wertänderung |
| Plug (Ausgang) | `REST` | `adapter::types::unidirectional::AR` | Verbleibende Zeit `PT - ET` in Sekunden, kein Sentinel-Wert |

## Funktionsweise

Intern übernimmt eine einfache `AX_ATM_FB_TON`-Instanz das eigentliche Timing. Darum herum:

1. `PT` wird aufgeteilt (`ATM_SPLIT_2`), sodass der Wert sowohl das `PT` des gewrappten Timers
   selbst als auch ein `ATM_SUB` erreicht, das `PT - ET` berechnet.
2. Das `ET` des gewrappten Timers wird ebenso aufgeteilt, sodass es sowohl den eigenen `ET`-Plug
   dieses Bausteins als auch dasselbe `ATM_SUB` (als Subtrahend) erreicht.
3. `ATM_SUB.OUT` (ein `ATM`, also `TIME`) wird über `ATM_IN_S_TO_ALR` → `ALR_TO_AR` in Sekunden
   umgerechnet und ergibt den `REST`-Wert.
4. `Q` wird unverändert vom gewrappten Timer durchgereicht.

**Warum einfaches Socket/Plug-Durchreichen hier nicht funktioniert, und was der Baustein
stattdessen tut:** Ein Socket kann nur *von einem Plug gespeist* werden, und ein Plug kann nur
*einen Socket speisen* — eine simple `<Connection Source="IN" Destination="InnerTimer.IN"/>`
zwischen dem eigenen `IN`-Socket dieses Bausteins und dem `IN`-Socket des gewrappten Timers (beides
Sockets) ist keine legale Adapterverbindung, und dasselbe symmetrische Problem besteht bei `Q`
(beides Plugs). Weil `AX_ATM_FB_TON_REST` selbst ein `FBType` ist (kein `SubAppType`), ist der
lesende Dot-Zugriff auf den aktuellen Wert eines Sockets via `IN.D1`/`IN.E1` **hier legal** — die
Lösung besteht daher darin, an jeder Grenze über ein Paar reiner Datenvariablen zu überbrücken:
[AX_BOOL_TO_X](../../conversion/unidirectional/BOOL/AX_BOOL_TO_X.md) liest `IN.D1`/`IN.E1` und gibt
den Wert als Plug wieder aus, der den `IN`-Socket des gewrappten Timers speist; symmetrisch dazu
liest [AX_X_TO_BOOL](../../conversion/unidirectional/BOOL/AX_X_TO_BOOL.md) den `Q`-Plug des
gewrappten Timers und gibt ihn auf den eigenen `Q`-Plug dieses Bausteins aus. Dasselbe Muster gilt
für `PT`/`ET` (`ATM_TIME_TO_TM`/`ATM_TM_TO_TIME`) — jedes Paar überbrückt eine Richtung hinein und
eine Richtung hinaus, weil sowohl Socket als auch Plug des gewrappten Timers einen gebundenen Wert
brauchen. `REST` braucht nur die ausgehende Hälfte dieses Musters — er wird rein intern berechnet
und nie von außen gespeist — daher kommt nur
[AR_R_TO_REAL](../../conversion/unidirectional/REAL/AR_R_TO_REAL.md) zum Einsatz: Er liest den
intern berechneten `AR`-Wert (über seinen eigenen `AR_IN`-Socket, gespeist vom Plug von
`ALR_TO_R`) und gibt den reinen `REAL`-Wert auf die eigenen Plug-Pins von `REST` aus. Dieselbe
Regel — ein Socket kann nur von einem Plug gespeist werden — gilt für jeden Adaptertyp, nicht nur
für `AX`/`ATM`/`AR`.

## Technische Details

- **`REST` führt keine Sentinel-Konvention (kein "-1 = inaktiv").** Ein Aufrufer, der eine solche
  braucht (z. B. "-1, solange der Timer nicht läuft"), gated `REST` selbst mit einem nachgeschalteten
  [AR_AX_SEL_AR](../selection/adapter/AR_AX_SEL_AR.md), der abhängig von seiner eigenen
  "aktiv"-Bedingung zwischen `REST` und einer Konstante auswählt — dieser Baustein meldet immer nur
  die rohe `PT - ET`-Differenz.
- **`REST` aktualisiert sich mit derselben Auflösung wie `ET`**, also nur bei tatsächlicher
  Wertänderung (geerbt von `AX_ATM_FB_TON`s `E_D_FF_ANY` auf `ET`), nicht bei jedem `REQ`-/
  `E_CYCLE`-Tick.
- **Sämtliche `PT`-Semantik von `AX_ATM_FB_TON` gilt unverändert** — `PT` ist live, nicht gelatched;
  `PT = 0` lässt `Q` (und damit ein `REST` von 0) bereits bei der nächsten Auswertung wahr/erreicht
  werden. Siehe [AX_ATM_FB_TON](AX_ATM_FB_TON.md#technische-besonderheiten) für die vollständige
  Aufschlüsselung dieser Grenzfälle.

## Zustandsübersicht

Dieselben vier Zustände wie `AX_ATM_FB_TON`, wobei `REST` durchgehend `PT - ET` folgt:
1. **Ruhezustand**: `IN` ist FALSE, `Q` ist FALSE, `ET` ist 0, `REST` entspricht `PT` in Sekunden.
3. **Ausgelöst**: `ET` hat `PT` erreicht, `REST` erreicht 0, `Q` wird TRUE.
4. **Reset**: `IN` wird FALSE, `Q` wird FALSE, `ET` wird 0, `REST` kehrt zu `PT` zurück.

## Anwendungsszenarien

- **Countdown-Anzeige über OPC-UA**: `PT` aus einem abonnierten REAL-Sekundenwert speisen, `REST`
  direkt an die Visu weitergeben — keine externe `ATM_SUB`/`ATM_IN_S_TO_ALR`/`ALR_TO_AR`-Kette an
  der Verwendungsstelle nötig.
- Jede Stelle, die heute `AX_ATM_FB_TON` zusammen mit einer eigenen Kopie der
  `ATM_SUB`/`ATM_IN_S_TO_ALR`/`ALR_TO_AR`-Kette verdrahtet, um einen Restzeit-Wert zu erhalten —
  dieser Baustein ersetzt alle vier Bausteine durch einen einzigen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[AX_ATM_FB_TON](AX_ATM_FB_TON.md)**: identisches Timing-Verhalten und identische Schnittstelle,
  minus den `REST`-Plug — verwenden, wenn nur `Q`/`ET` gebraucht werden.
- **[AR_AX_SEL_AR](../selection/adapter/AR_AX_SEL_AR.md)**: kein Ersatz, sondern der
  Begleitbaustein, um einen Sentinel-Wert (z. B. "-1 = inaktiv") auf den rohen `REST`-Ausgang dieses
  Bausteins aufzusetzen.

## Fazit

`AX_ATM_FB_TON_REST` fasst das wiederkehrende Muster "Einschaltverzögerungstimer mit
Restzeit-Anzeige" — bisher vier separat verdrahtete Bausteine pro Verwendungsstelle — in einem
einzigen adapterbasierten Baustein zusammen. Dafür nimmt er eine etwas komplexere interne
Verdrahtung (Socket/Plug-Überbrückung an jeder Grenze) in Kauf, zugunsten einer deutlich
einfacheren Verwendungsstelle.
