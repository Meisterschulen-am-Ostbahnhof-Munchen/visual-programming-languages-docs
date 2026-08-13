# AX_ATM_FB_TON

![AX_ATM_FB_TON](AX_ATM_FB_TON.svg)

* * * * * * * * * *

## Einleitung

`AX_ATM_FB_TON` ist die adapterbasierte Variante von [AX_FB_TON](AX_FB_TON.md): derselbe
IEC-61131-3-Einschaltverzögerungstimer (`iec61131::timers::FB_TON`), aber mit `PT` (Sollzeit) als
Socket und `ET` (abgelaufene Zeit) als Plug — beide vom Typ
[ATM](../../types/unidirectional/TIME/ATM.md) — statt als einfache `TIME`-Datenvariablen. Das
erlaubt, den Baustein direkt in adapterbasierte Ketten einzuhängen (z. B. hinter ein
`AR_SUBSCRIBE_1`, das eine per OPC-UA geschriebene REAL-Sekundenzahl liefert, umgewandelt in
`TIME`), ohne an jeder Verwendungsstelle eigene Datenverbindungen für `PT`/`ET` zu ziehen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ** (Event, nicht auslösend): Normaler Ausführungsaufruf. Die Anwendung hängt hier
  typischerweise einen `E_CYCLE` an, damit `ET` periodisch aktualisiert wird, während der Timer
  läuft — ohne einen externen `E_CYCLE` bliebe `ET` zwischen `IN`- bzw. `PT`-Ereignissen stehen.

### **Ereignis-Ausgänge**

Keine eigenen Ereignis-Ausgänge; Ereignisse laufen ausschließlich über die Adapter-Plugs `Q` und
`ET`.

### **Daten-Eingänge**

Keine eigenen Daten-Eingänge. Alle Daten werden über die Adapter-Sockets übertragen.

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge. Alle Daten werden über die Adapter-Plugs übertragen.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::AX` | Startsignal |
| Socket (Eingang) | `PT` | `adapter::types::unidirectional::ATM` | Sollzeit |
| Plug (Ausgang) | `Q` | `adapter::types::unidirectional::AX` | Ausgang, TRUE nachdem `IN` seit `PT` ansteht |
| Plug (Ausgang) | `ET` | `adapter::types::unidirectional::ATM` | Abgelaufene Zeit, Event nur bei Wertänderung |

## Funktionsweise

Intern wird derselbe `FB_TON`-Standardbaustein wie in `AX_FB_TON` verwendet, ergänzt um zwei
`E_D_FF`/`E_D_FF_ANY`-Puffer:

1. `IN.E1`, das eigene `REQ`-Ereignis und `PT.E1` lösen alle gemeinsam `FB_TON.REQ` aus — jede der
   drei Quellen (Eingang ändert sich, Sollzeit ändert sich, oder ein zyklischer Anstoß von außen)
   soll die aktuelle Zeitbasis neu berechnen.
2. `FB_TON.Q` läuft über ein `E_D_FF` (Change-Detection) auf `Q.D1`/`Q.E1` — der `Q`-Plug feuert
   sein Ereignis nur, wenn sich der boolesche Ausgang tatsächlich ändert.
3. `FB_TON.ET` läuft über ein `E_D_FF_ANY` (generische Change-Detection) auf `ET.D1`/`ET.E1` —
   ebenso nur bei tatsächlicher Wertänderung, nicht bei jedem `REQ`-Zyklus.

## Technische Besonderheiten

- **`REQ` bleibt bewusst ein einfaches Event, keine Adapterverbindung.** Damit kann die Anwendung
  selbst entscheiden, mit welcher Zykluszeit `ET` aktualisiert wird (z. B. per `E_CYCLE`), statt
  dass der Baustein eine feste Aktualisierungsrate vorgibt.
- **`ET`-Events nur bei Wertänderung**, nach demselben Prinzip wie
  [ASSEMBLE_AB_FROM_AX](../../assembling/ASSEMBLE_AB_FROM_AX.md) und
  [AB_AX_SEL_AB](../selection/adapter/AB_AX_SEL_AB.md) — verhindert Event-Flut bei jedem
  `E_CYCLE`-Tick, wenn sich der Zeitwert (je nach Auflösung) gar nicht geändert hat.
- **`PT.E1` triggert ebenfalls neu.** Ändert die Anwendung die Sollzeit zur Laufzeit (z. B. weil
  ein OPC-UA-Wert neu geschrieben wurde), wird sofort neu gerechnet, statt auf den nächsten
  `E_CYCLE`-Tick zu warten.
- **`adapter::events::unidirectional::timers`-Familie (`AX_TON` etc.) hat keinen `ET`-Ausgang.**
  Wird die verbleibende/abgelaufene Zeit gebraucht (z. B. für einen Countdown in der Visu), ist
  diese `iec61131-3`-Familie erforderlich, nicht die einfachere `events`-Familie.

## Zustandsübersicht

Wie `AX_FB_TON`: kein eigenes ECC, reines Composite-Verdrahtungsmuster um den Standard-`FB_TON`.

1. **Ruhezustand**: `IN` ist FALSE, `Q` ist FALSE, `ET` ist 0.
2. **Timing-Zustand**: `IN` ist TRUE, Timer läuft, `ET` steigt bis `PT`, `Q` bleibt FALSE.
3. **Ausgelöst**: `ET` hat `PT` erreicht, `Q` wird TRUE.
4. **Reset**: `IN` wird FALSE, `Q` wird FALSE, `ET` wird 0.

## Anwendungsszenarien

- **Countdown-Anzeige über OPC-UA**: `PT` aus einem abonnierten REAL-Sekundenwert (z. B.
  `Override.Dauer`) speisen, `ET` (bzw. `PT - ET` für die Restzeit) über einen Publish-Baustein an
  die Visu weiterreichen.
- Jede Stelle, an der bereits `AX_FB_TON` verwendet wird, aber zusätzlich `PT`/`ET` über
  adapterbasierte Ketten statt einzelner Datenverbindungen fließen sollen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[AX_FB_TON](AX_FB_TON.md)**: identisches Timing-Verhalten, aber `PT`/`ET` als einfache
  `TIME`-Datenvariablen statt Adapter.
- **[AX_TON](../../events/unidirectional/BOOL/timers/AX_TON.md)**: die `events`-Variante ohne
  `ET`-Ausgang überhaupt — geeignet, wenn nur das Timing-Ergebnis (`Q`), nicht aber die
  verstrichene Zeit gebraucht wird.
- **[AX_ATM_FB_TOF](AX_ATM_FB_TOF.md) / [AX_ATM_FB_TP](AX_ATM_FB_TP.md)**: dieselbe Adapter-
  Erweiterung für Aus-Verzögerung bzw. Impuls statt Ein-Verzögerung.

## Fazit

`AX_ATM_FB_TON` überträgt das bewährte `AX_FB_TON`-Timing-Verhalten in eine vollständig
adapterbasierte Schnittstelle, sodass sowohl Sollzeit als auch abgelaufene Zeit ohne zusätzliche
Datenverbindungen durch adapterbasierte Netzwerke fließen können — inklusive Change-Detection auf
dem `ET`-Ausgang, um unnötige Ereignisse zu vermeiden.
