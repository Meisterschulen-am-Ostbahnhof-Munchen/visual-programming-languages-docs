# initval_ALI

![initval_ALI](initval_ALI.svg)

* * * * * * * * * *

## Einleitung

`initval_ALI` ist der konfigurierbare Initialisierungsbaustein für den [ALI](../ALI.md)-Adapter (Datentyp `LINT`, 64-Bit-Ganzzahl (vorzeichenbehaftet)): Er nimmt bei der Initialisierung einen Startwert als Dateneingang entgegen und legt diesen auf einen `ALI`-Adapter-Plug. Damit ersetzt er die früher verbreitete Praxis, einen konstanten Vergleichswert über einen gemischten Adapter/Elementar-Baustein einzuspeisen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierungsanforderung, liefert `INIT_VAL`. Löst die Ausgabe von `INIT_VAL` über den Plug `OUT` aus.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt den Abschluss der Initialisierung.

### **Daten-Eingänge**

- **INIT_VAL** (LINT): Der Startwert, der beim Eintreffen von `INIT` auf den Adapter `OUT` geschrieben wird.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge; der Wert wird ausschließlich über den Adapter `OUT` bereitgestellt.

### **Adapter**

- **OUT** (Plug, Typ `ALI`): gibt bei `INIT` den über `INIT_VAL` übergebenen Wert über sein `E1`/`D1`-Adapterereignis aus.

## Funktionsweise

Bei Eintreffen des Ereignisses `INIT` (mit `With Var="INIT_VAL"`) verknüpft `initval_ALI` intern zwei Datenpfade: `INIT_VAL` wird per Datenverbindung auf `OUT.D1` kopiert, und `INIT` wird per Ereignisverbindung an `OUT.E1` weitergereicht -- der `OUT`-Plug feuert damit sein Adapterereignis mit dem gerade übergebenen Wert. Anschließend wird `INIT` zusätzlich an `INITO` weitergereicht, wodurch der Aufrufer den Abschluss der Initialisierung bestätigt bekommt.

## Technische Besonderheiten

- Der ausgegebene Wert ist nicht im Baustein selbst parametriert, sondern kommt bei jedem `INIT`-Aufruf frisch über `INIT_VAL` -- der Baustein kann also auch außerhalb einer reinen Initialisierungsphase zum dynamischen Setzen eines `ALI`-Werts verwendet werden.
- Reine Verdrahtungslogik ohne eigene ECC/Zustandsmaschine (Composite-FB ohne innere Funktionsblöcke); die Datenverbindung `INIT_VAL → OUT.D1` muss vor der Ereignisverbindung ausgewertet sein, damit `OUT.E1` den aktuellen Wert trägt -- dies wird durch die 61499-Ausführungsreihenfolge der `FBNetwork`-Verbindungen sichergestellt und ist nicht separat zu verdrahten.

## Zustandsübersicht

Der Baustein ist zustandslos: Jedes `INIT`-Ereignis führt unmittelbar zur Übernahme von `INIT_VAL` auf `OUT` und zur Bestätigung über `INITO`.

## Anwendungsszenarien

- Initialisierung von `ALI`-Adapterverbindungen mit einem projekt- oder parameterabhängigen Startwert (z. B. aus einer Konfigurationsvariable)
- Ersatz für die entfernten „gemischten" Adapter↔Elementar-Vergleichsbausteine: Ein konstanter `LINT`-Wert wird über `initval_ALI` auf einen `ALI`-Adapter gelegt und kann dann mit dem reinen adapterbasierten `ALI`-Vergleichsbaustein weiterverwendet werden.
- Wiederverwendbare Bausteinvorlage für Testaufbauten, in denen unterschiedliche `ALI`-Startwerte durchprobiert werden sollen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [initval_AX](../../BOOL/initval/initval_AX.md), das denselben Verdrahtungsmechanismus für den Datentyp `BOOL` nutzt. Anders als `const_AX_TRUE`/`const_AX_FALSE` (die es nur für `AX` gibt) parametriert `initval_ALI` den Ausgabewert nicht fest im Baustein, sondern nimmt ihn über den Dateneingang `INIT_VAL` entgegen.

## Fazit

`initval_ALI` liefert eine einfache, wiederverwendbare Initialisierungslogik für den `ALI`-Adapter und macht den ausgegebenen Wert über `INIT_VAL` frei konfigurierbar. Er eignet sich überall dort, wo ein `LINT`-Startwert nicht bereits zur Entwurfszeit feststeht oder als Ersatz für einen entfernten gemischten Vergleichsbaustein benötigt wird.
