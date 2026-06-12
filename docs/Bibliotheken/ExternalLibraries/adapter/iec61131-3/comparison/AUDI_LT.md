# AUDI_LT


![AUDI_LT](./AUDI_LT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUDI_LT` realisiert einen „Kleiner-als“-Vergleich (less than) zwischen zwei Eingangswerten. Er wird in der Automatisierungstechnik häufig eingesetzt, um Schwellwerte zu überwachen oder logische Entscheidungen zu treffen. Der Baustein ist nach IEC 61131‑3 als „standard comparison function“ klassifiziert und verwendet Adapter für eine flexible Anbindung unterschiedlicher Datentypen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Über die Adapter-Sockets werden Ereignisse von außen an den FB weitergeleitet:
*   `IN1.E1` – Ereignis, das die Vergleichsoperation anstößt, sobald ein neuer Wert an `IN1` anliegt.
*   `IN2.E1` – Ereignis, das ebenfalls die Vergleichsoperation anstößt, sobald ein neuer Wert an `IN2` anliegt.

### **Ereignis-Ausgänge**
*   `OUT.E1` – Ereignis, das nach Abschluss des Vergleichs ausgegeben wird und signalisiert, dass das Ergebnis am Datenausgang `OUT.D1` gültig ist.

### **Daten-Eingänge**
*   `IN1.D1` – Erster zu vergleichender Wert (Daten vom Typ des Adapters `AUDI`).
*   `IN2.D1` – Zweiter zu vergleichender Wert (Daten vom Typ des Adapters `AUDI`).

### **Daten-Ausgänge**
*   `OUT.D1` – Ergebnis des Vergleichs: `TRUE`, wenn `IN1 < IN2`, sonst `FALSE` (Daten vom Typ des Adapters `AX`).

### **Adapter**
*   `IN1` – Socket (Eingang) vom Typ `adapter::types::unidirectional::AUDI`. Liefert ein Ereignis (`E1`) und einen Datenwert (`D1`) an den FB.
*   `IN2` – Socket (Eingang) vom gleichen Typ `AUDI`. Stellt den zweiten Eingangswert bereit.
*   `OUT` – Plug (Ausgang) vom Typ `adapter::types::unidirectional::AX`. Übernimmt das Ergebnisereignis (`E1`) und den Ergebnis-Datenwert (`D1`) zur Weitergabe an nachfolgende Bausteine.

## Funktionsweise
Der Baustein führt einen numerischen Vergleich der beiden an `IN1` und `IN2` anliegenden Daten durch. Sobald eines der beiden Ereignisse (`IN1.E1` oder `IN2.E1`) eintrifft, wird der interne Funktionsblock `F_LT` (Less Than) aufgerufen. Dieser liest die aktuellen Werte von `IN1` und `IN2` und berechnet deren Größenverhältnis. Das Ergebnis (`TRUE` / `FALSE`) wird am Datenausgang `OUT.D1` bereitgestellt und gleichzeitig das Ereignis `OUT.E1` ausgelöst. Da beide Ereigniseingänge mit dem selben `REQ`-Eingang des internen Bausteins verbunden sind, wird der Vergleich bei jeder Änderung eines der beiden Werte erneut durchgeführt.

## Technische Besonderheiten
- **Adapterbasierte Schnittstellen** – Die Verwendung der Adapter `AUDI` und `AX` ermöglicht eine universelle Kopplung an verschiedene Datentypen, ohne dass der FB selbst typisiert werden muss. Die eigentliche Typanpassung erfolgt in den Adapterdefinitionen.
- **Asynchrone Auslösung** – Der Vergleich wird immer dann gestartet, wenn ein Ereignis an `IN1` oder `IN2` eintrifft. Dadurch reagiert der FB sofort auf Änderungen eines der beiden Eingänge.
- **Zustandslosigkeit** – Der FB besitzt keinen internen Zustand; das Ausgangssignal ist ausschließlich von den aktuellen Eingangswerten abhängig.

## Zustandsübersicht
Der Baustein ist rein funktional und benötigt keinen eigenen Zustandsautomaten. Er führt nach jedem Ereignis eine einmalige Vergleichsoperation durch und kehrt anschließend in einen leeren Wartezustand zurück.

## Anwendungsszenarien
- **Grenzwertüberwachung** – z. B. Prüfen, ob eine Temperatur unter einen Schwellwert fällt.
- **Bereichsprüfung** – Kombination mit weiteren Vergleichsbausteinen (z. B. `AUDI_GT`) zur Realisierung von „innerhalb“ oder „außerhalb“-Logik.
- **Steuerungslogik** – Boolsche Entscheidungen in Abhängigkeit von zwei analogen oder digitalen Größen.

## Vergleich mit ähnlichen Bausteinen
- **`AUDI_EQ`** – Prüft auf Gleichheit (`IN1 = IN2`).
- **`AUDI_GT`** – Prüft auf Größer (`IN1 > IN2`).
- **`AUDI_LT`** – Prüft auf Kleiner (`IN1 < IN2`). Alle drei Bausteine haben identische Schnittstellen und unterscheiden sich nur in der Vergleichsoperation. Sie können leicht ausgetauscht werden, um die Logik anzupassen.

## Fazit
Der `AUDI_LT` ist ein einfacher, aber robuster Vergleichsbaustein, der sich aufgrund seiner Adapter-Schnittstellen flexibel in unterschiedlichste Automatisierungsumgebungen einbinden lässt. Seine asynchrone Arbeitsweise und die klare Trennung von Ereignis und Daten machen ihn zu einem grundlegenden Werkzeug für wertvergleichende Aufgaben in der Steuerungstechnik.