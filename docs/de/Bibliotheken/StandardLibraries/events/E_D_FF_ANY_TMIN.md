# E_D_FF_ANY_TMIN

* * * * * * * * * *
## Einleitung

Der `E_D_FF_ANY_TMIN` ist die generisch typisierte Variante von [E_D_FF_TMIN](E_D_FF_TMIN.md): Er kombiniert [E_D_FF_ANY](E_D_FF_ANY.md) (änderungserkennendes Latch für beliebige Datentypen) mit [E_TMIN](E_TMIN.md) (Mindestabstandszeit) und eignet sich damit für alle Datentypen, nicht nur `BOOL`.

![E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierung, trägt `Tmin`.
- **CLK**: Taktereignis, übernimmt `D` in `Q`.
    - **Verbundene Daten**: `D`

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt die Initialisierung.
- **EO**: Auf `Tmin` gedrosseltes Änderungsereignis.
    - **Verbundene Daten**: `Q`

### **Daten-Eingänge**

- **D** (ANY): Der zu speichernde Wert, beliebiger Datentyp.
- **Tmin** (TIME): Mindestabstand zwischen zwei `EO`-Ereignissen.

### **Daten-Ausgänge**

- **Q** (ANY): Der zuletzt übernommene Wert.

## Funktionsweise

Identisch zu [E_D_FF_TMIN](E_D_FF_TMIN.md), jedoch mit [E_D_FF_ANY](E_D_FF_ANY.md) statt `E_D_FF`: `CLK` triggert die interne Änderungserkennung (`NE(Q, D)`), deren `EO` an das interne [E_TMIN](E_TMIN.md) weitergeleitet wird, das die zeitliche Drosselung auf mindestens `Tmin` zwischen zwei Auslösungen von `EO` übernimmt.

## Technische Besonderheiten

- **ANY-Typisierung**: kann mit jedem von der Zielumgebung unterstützten Datentyp instanziiert werden (z. B. `TIME`, `REAL`, `DINT`).
- **Zweistufige Filterung**: inhaltliche Änderungserkennung (`E_D_FF_ANY`) plus zeitliche Drosselung (`E_TMIN`), `Q` bleibt davon unbeeinflusst und stets aktuell.

## Zustandsübersicht

Zustandslose Verdrahtungslogik, siehe [E_D_FF_ANY](E_D_FF_ANY.md) (Änderungserkennung) und [E_TMIN](E_TMIN.md) (Zeitdrosselung).

## Anwendungsszenarien

- **Rauscharme Weiterleitung beliebiger Messwerte**: Ein `REAL`- oder `TIME`-Wert schwankt geringfügig, `EO` soll aber höchstens alle `Tmin` ausgelöst werden — z. B. zur Begrenzung der Sendefrequenz an ein übergeordnetes System.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[E_D_FF_ANY](E_D_FF_ANY.md)**: dieselbe Änderungserkennung, aber ohne Zeitdrosselung.
- **[E_D_FF_TMIN](E_D_FF_TMIN.md)**: dieselbe Funktion, aber fest auf `BOOL` beschränkt.
- **[E_TMIN](E_TMIN.md)**: die intern verwendete Drosselungslogik.

## Fazit

`E_D_FF_ANY_TMIN` liefert ein generisch typisiertes, änderungserkennendes Latch mit garantiertem Mindestabstand zwischen Änderungsereignissen für beliebige Datentypen.
