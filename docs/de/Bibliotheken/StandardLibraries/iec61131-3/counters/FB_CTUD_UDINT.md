# FB_CTUD_UDINT

![FB_CTUD_UDINT](FB_CTUD_UDINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `FB_CTUD_UDINT` ist ein kombinierter Auf-/Abwärtszähler (Up/Down Counter) für den Datentyp `UDINT` (32-Bit-Ganzzahl, vorzeichenlos). Er zählt bei `CU` hoch und bei `CD` herunter, kann über `LD` auf einen Vorgabewert `PV` geladen und über `R` auf `0` zurückgesetzt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Startet die Ausführung, verknüpft mit `CU`, `CD`, `R`, `LD`, `PV`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die Ausführung, verknüpft mit `QU`, `QD`, `CV`.

### **Daten-Eingänge**

- **CU** (BOOL): Aufwärtszählen bei `TRUE`.
- **CD** (BOOL): Abwärtszählen bei `TRUE`.
- **R** (BOOL): Reset — setzt `CV` auf `0`, hat Vorrang vor `LD`/`CU`/`CD`.
- **LD** (BOOL): Load — lädt `PV` in `CV`, sofern `R` nicht aktiv ist.
- **PV** (UDINT): Vorgabewert (Preset Value), gegen den `CV` verglichen wird.

### **Daten-Ausgänge**

- **QU** (BOOL): `TRUE`, wenn `CV >= PV`.
- **QD** (BOOL): `TRUE`, wenn `CV <= 0`.
- **CV** (UDINT): Aktueller Zählerstand.

## Funktionsweise

Bei jedem `REQ`-Ereignis wertet der Baustein die Eingänge in folgender Priorität aus: Ist `R` aktiv, wird `CV := 0`. Andernfalls wird bei aktivem `LD` `CV := PV` gesetzt. Ist weder `R` noch `LD` aktiv und sind `CU`/`CD` nicht gleichzeitig aktiv, wird `CV` bei `CU` (sofern `CV < 4294967295`) um 1 erhöht bzw. bei `CD` (sofern `CV > 0`) um 1 verringert. Abschließend werden `QU := CV >= PV` und `QD := CV <= 0` berechnet.

## Technische Besonderheiten

- **Priorisierung**: `R` (Reset) hat Vorrang vor `LD` (Load), das wiederum Vorrang vor der eigentlichen Zähloperation hat.
- **Gleichzeitiges `CU`+`CD`**: Sind beide gleichzeitig `TRUE`, findet keine Zähländerung statt (`NOT(CU AND CD)`-Bedingung in der Algorithmus-ST).
- **Wertebereichsgrenze**: Der Zählerstand wird bei `4294967295` (Maximalwert von `UDINT`) nach oben und bei `0` nach unten begrenzt.

## Zustandsübersicht

1. **Reset**: `R = TRUE` → `CV := 0`.
2. **Load**: `R = FALSE`, `LD = TRUE` → `CV := PV`.
3. **Zählen**: `R = FALSE`, `LD = FALSE` → `CV` wird je nach `CU`/`CD` angepasst.
4. **Ausgabe**: `QU`/`QD` werden anhand des aktuellen `CV` neu berechnet, `CNF` wird ausgelöst.

## Anwendungsszenarien

- **Bidirektionale Zählaufgaben mit großem Wertebereich**, z. B. Stückzahlen oder Positionswerte, die sowohl inkrementiert als auch dekrementiert werden müssen und den Wertebereich von `UINT`/`DINT` überschreiten können.
- **Füllstands- oder Pufferzählung**, bei der `QU`/`QD` als Ober-/Untergrenzen-Signal für nachgeschaltete Logik dienen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`FB_CTUD`**: dieselbe Funktion für den Datentyp `INT`.
- **`FB_CTUD_DINT`/`FB_CTUD_LINT`/`FB_CTUD_ULINT`**: dieselbe Funktion für andere Ganzzahltypen.
- **`FB_CTU_UDINT`/`FB_CTD_UDINT`**: die reinen Auf- bzw. Abwärtszähler-Varianten für `UDINT`, ohne kombinierte `LD`-Funktion.

## Fazit

`FB_CTUD_UDINT` liefert einen vollständigen Auf-/Abwärtszähler mit Lade- und Reset-Funktion für den `UDINT`-Wertebereich und schließt die Lücke zwischen den bereits vorhandenen `FB_CTUD_*`-Varianten für andere Datentypen.
