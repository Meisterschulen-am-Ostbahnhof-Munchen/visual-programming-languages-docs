# E_D_FF_ANY

![E_D_FF_ANY_ecc](./E_D_FF_ANY_ecc.svg)

* * * * * * * * * *

## Einleitung

Der `E_D_FF_ANY` ist die generisch typisierte Variante von `E_D_FF`: Während `E_D_FF` nur `BOOL`-Werte zwischenspeichert, akzeptiert `E_D_FF_ANY` einen Eingang `D` vom Datentyp `ANY` und kann so für beliebige Datentypen (z. B. `TIME`, `DINT`, `REAL`, `STRING`) als taktgesteuertes Latch mit integrierter Änderungserkennung verwendet werden.

![E_D_FF_ANY](E_D_FF_ANY.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **CLK**: Taktereignis, übernimmt den aktuellen Wert von `D`.
    - **Verbundene Daten**: `D`

### **Ereignis-Ausgänge**

- **EO**: Wird nur ausgelöst, wenn sich `Q` durch den `CLK`-Impuls tatsächlich geändert hat.
    - **Verbundene Daten**: `Q`

### **Daten-Eingänge**

- **D** (ANY): Der zu speichernde Wert, beliebiger Datentyp.

### **Daten-Ausgänge**

- **Q** (ANY): Der zuletzt übernommene Wert, vom selben Datentyp wie `D`.

## Funktionsweise

Bei jedem `CLK`-Ereignis vergleicht die ECC den neuen Wert `D` mit dem aktuell gespeicherten `Q` (`NE(Q, D)`). Nur wenn sich der Wert tatsächlich geändert hat, wird `Q := D` ausgeführt und `EO` ausgelöst — bei unverändertem Wert bleibt der Baustein im Zustand `SET`, ohne ein Ereignis zu erzeugen. Der Anfangszustand `START` übernimmt beim ersten `CLK` immer den Wert, unabhängig von einer Änderungserkennung.

## Technische Besonderheiten

- **ANY-Typisierung**: Im Gegensatz zu `E_D_FF` (fest `BOOL`) kann `E_D_FF_ANY` mit jedem IEC-61131-3-Datentyp instanziiert werden, den die Zielumgebung für generische `ANY`-Adaption unterstützt.
- **Eingebaute Änderungserkennung**: Anders als ein reines Latch löst `E_D_FF_ANY` `EO` nur bei tatsächlicher Wertänderung aus — dies reduziert die Ereignislast in nachgeschalteten FB-Netzwerken erheblich.
- **Basis für `_TMIN`-Varianten**: [E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md) kombiniert diesen Baustein zusätzlich mit einer Mindestabstandszeit zwischen zwei `EO`-Ereignissen.

## Zustandsübersicht

| Zustand | Bedeutung |
| --- | --- |
| START | Anfangszustand, erster `CLK` übernimmt `D` unbedingt |
| SET | `Q` enthält den zuletzt übernommenen Wert; weitere `CLK`-Ereignisse lösen nur bei `NE(Q, D)` erneut `EO` aus |

## Anwendungsszenarien

- **Änderungsgesteuerte Weiterverarbeitung beliebiger Datentypen**: Ein `TIME`- oder `REAL`-Wert soll nur dann ein Folgeereignis auslösen, wenn er sich tatsächlich geändert hat — z. B. als Baustein innerhalb von Composite-FBs wie `ATM_SUB` (siehe `adapter`-Bibliothek), die `F_MOVE` + `E_D_FF_ANY` zur expliziten, FBNetwork-sichtbaren Änderungserkennung kombinieren.
- **Generisches Caching**: Zwischenspeichern eines beliebigen Werts mit Benachrichtigung nur bei echter Änderung, unabhängig vom konkreten Datentyp.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_D_FF`**: funktional identisch, aber fest auf `BOOL` beschränkt.
- **[E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)**: dieselbe Funktion, zusätzlich mit Mindestabstandszeit zwischen `EO`-Ereignissen.
- **[E_D_FF_TMIN](E_D_FF_TMIN.md)**: die `BOOL`-Variante mit Mindestabstandszeit.

## Fazit

`E_D_FF_ANY` liefert ein generisch typisiertes, änderungserkennendes Latch und ist ein zentraler Baustein überall dort, wo Composite-FBs für beliebige Datentypen eine Ereignisauslösung nur bei tatsächlicher Wertänderung benötigen.
