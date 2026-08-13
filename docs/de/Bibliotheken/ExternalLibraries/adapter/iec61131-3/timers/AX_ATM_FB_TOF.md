# AX_ATM_FB_TOF

![AX_ATM_FB_TOF](AX_ATM_FB_TOF.svg)

* * * * * * * * * *

## Einleitung

`AX_ATM_FB_TOF` ist die adapterbasierte Variante von [AX_FB_TOF](AX_FB_TOF.md): derselbe
IEC-61131-3-Ausschaltverzögerungstimer (`iec61131::timers::FB_TOF`), aber mit `PT` (Sollzeit) als
Socket und `ET` (abgelaufene Zeit) als Plug — beide vom Typ
[ATM](../../types/unidirectional/TIME/ATM.md) — statt als einfache `TIME`-Datenvariablen. Ebenso
wie [AX_ATM_FB_TON](AX_ATM_FB_TON.md) erlaubt das, den Baustein direkt in adapterbasierte Ketten
einzuhängen, ohne an jeder Verwendungsstelle eigene Datenverbindungen für `PT`/`ET` zu ziehen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ** (Event, nicht auslösend): Normaler Ausführungsaufruf. Die Anwendung hängt hier
  typischerweise einen `E_CYCLE` an, damit `ET` periodisch aktualisiert wird, während der Timer
  läuft.

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
| Plug (Ausgang) | `Q` | `adapter::types::unidirectional::AX` | Ausgang, bleibt TRUE bis `PT` nach dem Abfallen von `IN` |
| Plug (Ausgang) | `ET` | `adapter::types::unidirectional::ATM` | Abgelaufene Zeit, Event nur bei Wertänderung |

## Funktionsweise

Intern wird derselbe `FB_TOF`-Standardbaustein wie in `AX_FB_TOF` verwendet, ergänzt um zwei
`E_D_FF`/`E_D_FF_ANY`-Puffer:

1. `IN.E1`, das eigene `REQ`-Ereignis und `PT.E1` lösen alle gemeinsam `FB_TOF.REQ` aus.
2. `FB_TOF.Q` läuft über ein `E_D_FF` (Change-Detection) auf `Q.D1`/`Q.E1`.
3. `FB_TOF.ET` läuft über ein `E_D_FF_ANY` (generische Change-Detection) auf `ET.D1`/`ET.E1` —
   nur bei tatsächlicher Wertänderung, nicht bei jedem `REQ`-Zyklus.

Im Unterschied zum Einschaltverzögerungstimer setzt `IN = TRUE` den Ausgang `Q` sofort auf TRUE;
erst wenn `IN` wieder auf FALSE fällt, läuft die Zeit `PT` ab, bevor `Q` auf FALSE zurückfällt.

## Technische Besonderheiten

- **`REQ` bleibt bewusst ein einfaches Event, keine Adapterverbindung**, wie bei
  [AX_ATM_FB_TON](AX_ATM_FB_TON.md) — die Anwendung bestimmt selbst die Aktualisierungsrate von
  `ET` über einen extern angeschlossenen `E_CYCLE`.
- **`ET`-Events nur bei Wertänderung**, nach demselben Prinzip wie
  [ASSEMBLE_AB_FROM_AX](../../assembling/ASSEMBLE_AB_FROM_AX.md).
- **`PT` ist live, nicht gelatched — `IN.E1`, `PT.E1` und `REQ` sind für `FB_TOF` gleichwertige
  Auslöser**, genau wie bei [AX_ATM_FB_TON](AX_ATM_FB_TON.md). `PT.D1` liegt als reine
  Datenverbindung dauerhaft an `FB_TOF.PT` an, keine Pufferung/Entprellung im Adapter:
  - **`PT = 0`**: Nachdem `IN` auf FALSE gefallen ist, wird `Q` bei der nächsten Auswertung sofort
    FALSE (kein sichtbarer Nachlauf).
  - **`PT` wird während des Nachlaufs verkleinert**, sodass das bereits gelaufene `ET` die neue
    Sollzeit übersteigt: `Q` wird sofort FALSE.
  - **`PT` wird während des Nachlaufs vergrößert**: `Q` bleibt entsprechend länger TRUE.
  - **Schnell aufeinanderfolgende `PT.E1`-Ereignisse** lösen jeweils eine eigene Auswertung aus,
    keine Zusammenfassung.
  - **Vor dem allerersten `PT.E1`** liegt an `FB_TOF.PT` der `TIME`-Standardwert `T#0s` an.
- **Identisches Verhalten in [AX_ATM_FB_TON](AX_ATM_FB_TON.md) und
  [AX_ATM_FB_TP](AX_ATM_FB_TP.md)** — alle drei sind strukturell identisch verdrahtet, nur der
  intern gewrappte Standardbaustein unterscheidet sich.

## Zustandsübersicht

1. **Ruhezustand**: `IN` ist FALSE, `Q` ist FALSE, `ET` ist 0.
2. **`IN` wird TRUE**: `Q` wird sofort TRUE, `ET` bleibt 0.
3. **`IN` fällt auf FALSE**: Timer startet, `ET` steigt bis `PT`, `Q` bleibt TRUE.
4. **Abgelaufen**: `ET` hat `PT` erreicht, `Q` wird FALSE.

## Anwendungsszenarien

- Nachlaufzeiten, bei denen ein Ausgang nach dem Abschalten eines Eingangs noch eine definierte
  Zeit lang aktiv bleiben soll, mit sichtbarer Restlaufzeit über `ET`.
- Jede Stelle, an der bereits `AX_FB_TOF` verwendet wird, aber `PT`/`ET` über adapterbasierte
  Ketten fließen sollen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[AX_FB_TOF](AX_FB_TOF.md)**: identisches Timing-Verhalten, aber `PT`/`ET` als einfache
  `TIME`-Datenvariablen statt Adapter.
- **[AX_TOF](../../events/unidirectional/BOOL/timers/AX_TOF.md)**: die `events`-Variante ohne
  `ET`-Ausgang.
- **[AX_ATM_FB_TON](AX_ATM_FB_TON.md) / [AX_ATM_FB_TP](AX_ATM_FB_TP.md)**: dieselbe Adapter-
  Erweiterung für Ein-Verzögerung bzw. Impuls statt Aus-Verzögerung.

## Fazit

`AX_ATM_FB_TOF` überträgt das bewährte `AX_FB_TOF`-Timing-Verhalten in eine vollständig
adapterbasierte Schnittstelle, mit Change-Detection auf dem `ET`-Ausgang, um unnötige Ereignisse
zu vermeiden.
