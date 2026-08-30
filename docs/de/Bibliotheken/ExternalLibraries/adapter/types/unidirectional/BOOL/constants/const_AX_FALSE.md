# const_AX_FALSE

![const_AX_FALSE](const_AX_FALSE.svg)

* * * * * * * * * *

## Einleitung

`const_AX_FALSE` ist das Gegenstück zu [const_AX_TRUE](const_AX_TRUE.md): Ein einfacher Konstanten-Baustein, der bei seiner Initialisierung den festen Wert `FALSE` auf einen [AX](../AX.md)-Adapter-Plug legt. Er dient dazu, statisch verdrahtete boolesche Konstanten in ein AX-Adapternetzwerk einzuspeisen, ohne dass dafür eine eigene Verdrahtung von Ereignis- und Datenleitung nötig ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierungsanforderung. Löst die Ausgabe des Konstantwerts über den Plug `OUT` aus.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt den Abschluss der Initialisierung.

### **Daten-Eingänge**

- Keine. Der Wert `FALSE` ist fest im Baustein verdrahtet (`Parameter Name="D1" Value="FALSE"` auf dem Plug `OUT`).

### **Daten-Ausgänge**

- Keine direkten Datenausgänge; der Wert wird ausschließlich über den Adapter `OUT` bereitgestellt.

### **Adapter**

- **OUT** (Plug, Typ `AX`): gibt bei `INIT` den festen Wert `FALSE` über sein `E1`/`D1`-Adapterereignis aus.

## Funktionsweise

Bei Eintreffen des Ereignisses `INIT` löst `const_AX_FALSE` intern zwei Verbindungen aus: Zum einen wird `INIT` direkt an `OUT.E1` weitergereicht -- der `OUT`-Plug feuert damit sein Adapterereignis mit dem fest parametrierten Datenwert `D1 = FALSE`. Zum anderen wird `INIT` an `INITO` weitergereicht, wodurch der Aufrufer den Abschluss der Initialisierung bestätigt bekommt.

## Technische Besonderheiten

- Der Wert `FALSE` ist als `Parameter`-Attribut direkt am `AdapterDeclaration`-Element von `OUT` hinterlegt, nicht als Laufzeitdatum -- der Baustein besitzt keine Möglichkeit, zur Laufzeit einen anderen Wert auszugeben. Wird ein zur Laufzeit konfigurierbarer Startwert benötigt, ist stattdessen [initval_AX](../initval/initval_AX.md) zu verwenden.
- Reine Verdrahtungslogik ohne eigene ECC/Zustandsmaschine (Composite-FB ohne innere Funktionsblöcke).

## Zustandsübersicht

Der Baustein ist zustandslos: Jedes `INIT`-Ereignis führt unmittelbar zur Ausgabe von `FALSE` auf `OUT` und zur Bestätigung über `INITO`.

## Anwendungsszenarien

- Initialisierung von AX-Adapterverbindungen mit einem festen `FALSE`-Startwert, z. B. als Sperr- oder Disable-Konstante
- Testaufbauten, in denen ein AX-Eingang ohne echten Sensor/Vorgänger-Baustein mit einem festen Wert versorgt werden muss
- Ersatz für eine manuell verdrahtete Konstanten-Verbindung in generischen, AX-adapterbasierten Netzwerken

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [const_AX_TRUE](const_AX_TRUE.md), der denselben Mechanismus für den Wert `TRUE` nutzt, sowie mit [initval_AX](../initval/initval_AX.md), der denselben Zweck mit einem zur Laufzeit über `INIT_VAL` konfigurierbaren Wert erfüllt statt eines fest verdrahteten.

## Fazit

`const_AX_FALSE` ist der einfachste Weg, einen AX-Adapter-Plug mit einer festen `FALSE`-Konstante zu initialisieren, und eignet sich überall dort, wo der Wert zur Entwurfszeit feststeht und keine Laufzeitkonfiguration erforderlich ist.
