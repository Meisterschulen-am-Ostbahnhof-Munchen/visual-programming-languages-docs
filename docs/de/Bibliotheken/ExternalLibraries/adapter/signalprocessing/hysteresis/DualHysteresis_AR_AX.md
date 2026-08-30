# DualHysteresis_AR_AX


![DualHysteresis_AR_AX](./DualHysteresis_AR_AX.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `DualHysteresis_AR_AX` dient der zweitwegigen (dualen) Analog-Digital-Wandlung mit Hystereseverhalten. Er vergleicht ein analoges Eingangssignal mit einem definierten Mittelpunkt (`MI`), um über zwei separate Digitalausgänge (UP und DOWN) Steuerbefehle auszugeben. Dies entspricht der Funktionsweise eines klassischen Dreipunktreglers mit Totband und Hystereseschwellen. Der Baustein ist für die Signalverarbeitung im Rahmen von Regelungs- und Steuerungsaufgaben konzipiert und nutzt Adapter für eine strukturierte Kopplung der Signale.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

-   `INIT` (Typ: `EInit`): Initialisierungsanfrage. Startet oder stoppt den Baustein in Abhängigkeit des Daten-Eingangs `QI`.

### **Ereignis-Ausgänge**

-   `INITO` (Typ: `EInit`): Initialisierungsbestätigung. Signalisiert den erfolgreichen Übergang in den initialisierten bzw. deinitialisierten Zustand.

### **Daten-Eingänge**

-   `QI` (Typ: `BOOL`): Eingangshilfsvariable (Input Event Qualifier). Bestimmt, ob der Baustein aktiv arbeiten soll (`TRUE`) oder in den sicheren Deinitialisierungszustand versetzt wird (`FALSE`).

### **Daten-Ausgänge**

-   `QO` (Typ: `BOOL`): Ausgangshilfsvariable (Output Event Qualifier). Spiegelt den aktuellen Status und die Betriebsbereitschaft des Bausteins wider.

### **Adapter**

-   **Plugs (Stecker):**
    -   `DO_UP` (Typ: `adapter::types::unidirectional::AX`): Ausgangsadapter für die Aufwärtsbewegung / den oberen Schwellwert (UP).
    -   `DO_DOWN` (Typ: `adapter::types::unidirectional::AX`): Ausgangsadapter für die Abwärtsbewegung / den unteren Schwellwert (DOWN).
-   **Sockets (Buchsen):**
    -   `INPUT` (Typ: `adapter::types::unidirectional::AR`): Der aktuelle analoge Mess- oder Eingangswert.
    -   `MI` (Typ: `adapter::types::unidirectional::AR`): Der Mittelpunkt bzw. Sollwert der Regelung (Center Point, z. B. `0.5` für 50%).
    -   `DEAD` (Typ: `adapter::types::unidirectional::AR`): Das Totband um den Mittelpunkt (Absolutwert). Definiert die Ausschaltpunkte.
    -   `HYSTERESIS` (Typ: `adapter::types::unidirectional::AR`): Die Hysterese (Absolutwert). Definiert zusammen mit dem Totband die Einschaltpunkte.

---

## Funktionsweise

Die Zustandsumschaltung erfolgt ereignisgesteuert über den Eingang `INPUT.E1`. Die mathematische Auswertung stellt sicher, dass negative Parametereingaben für das Totband (`DEAD`) und die Hysterese (`HYSTERESIS`) durch die Verwendung von Absolutwerten (`ABS`) abgefangen werden.

Die logischen Schwellenwerte verhalten sich wie folgt:

-   **Einschalten UP (Wechsel nach UP):**
    $$INPUT \ge MI + |DEAD| + |HYSTERESIS|$$
    *(Ausgänge: `DO_UP.D1` = `TRUE`, `DO_DOWN.D1` = `FALSE`)*

-   **Ausschalten UP (Wechsel zurück nach Neutral):**
    $$INPUT < MI + |DEAD|$$
    *(Ausgänge: `DO_UP.D1` = `FALSE`, `DO_DOWN.D1` = `FALSE`)*

-   **Einschalten DOWN (Wechsel nach DOWN):**
    $$INPUT \le MI - |DEAD| - |HYSTERESIS|$$
    *(Ausgänge: `DO_UP.D1` = `FALSE`, `DO_DOWN.D1` = `TRUE`)*

-   **Ausschalten DOWN (Wechsel zurück nach Neutral):**
    $$INPUT > MI - |DEAD|$$
    *(Ausgänge: `DO_UP.D1` = `FALSE`, `DO_DOWN.D1` = `FALSE`)*

---

## Technische Besonderheiten

-   **Fehlersicherheit durch Absolutwerte:** Die Schwellenwertberechnungen nutzen explizit die `ABS`-Funktion für die Parameter `DEAD` und `HYSTERESIS`. Dies verhindert Fehlverhalten bei versehentlich negativ parametrisierten Werten.
-   **Sicherer Zustand:** Im deinitialisierten Zustand (`QI` = `FALSE`) oder im Zustand `Neutral` werden beide Digitalausgänge (`DO_UP.D1` und `DO_DOWN.D1`) zwingend auf `FALSE` gesetzt.
-   **Adapter-Anbindung:** Die Verwendung von `AR` (Analog Receiver) und `AX` (Digital Actuator) Adaptern sorgt für eine standardisierte, saubere Kapselung der Signalwege innerhalb der 4diac-IDE.

---

## Zustandsübersicht

Der Baustein basiert auf einer Zustandsmaschine (ECC) mit folgenden Zuständen:

1.  `START`: Ruhezustand vor der ersten Initialisierung.
2.  `Init`: Initialisierungsphase. Setzt die Ausgänge in den sicheren Zustand.
3.  `Neutral`: Der Eingangswert befindet sich innerhalb des zulässigen Bereichs. Beide Ausgänge sind inaktiv.
4.  `UP`: Der obere Einschaltpunkt wurde überschritten. Der Ausgang `DO_UP` ist aktiv.
5.  `DOWN`: Der untere Einschaltpunkt wurde unterschritten. Der Ausgang `DO_DOWN` ist aktiv.
6.  `DeInit`: Übergangszustand zur Deaktivierung des Bausteins.

---

## Anwendungsszenarien

-   **Dreipunktregler:** Temperaturregelungen (z. B. Heizen / Neutral / Kühlen) oder Füllstandsregelungen (z. B. Zulaufventil öffnen / Neutral / Ablaufventil öffnen).
-   **Spurführungs- und Lenksysteme:** Automatische Lenkungen in der Landtechnik oder Logistik, bei denen eine Abweichung von der Spurmitte (`MI`) nach links (`DOWN`) oder rechts (`UP`) korrigiert werden muss.
-   **Sollwert-Bandüberwachung:** Überwachung physikalischer Größen, bei denen erst bei signifikanten Abweichungen (Totband + Hysterese) ein Aktor angesteuert werden soll, um ständiges "Flattern" des Aktors zu vermeiden.

---

## Vergleich mit ähnlichen Bausteinen

Klassische Hysteresebausteine (z. B. Zweipunktregler) steuern lediglich einen einzelnen Digitalausgang an. Der `DualHysteresis_AR_AX` vereint zwei entgegengesetzte Hystereseschleifen in einem einzigen Baustein (Dreipunktverhalten). Zudem zeichnet er sich im Vergleich zu Standard-FBs mit elementaren Datentypen durch die Verwendung von unidirektionalen Adaptern (`AR` und `AX`) aus, was die Verdrahtung in komplexen Applikationen vereinfacht.

---

## Fazit

Der `DualHysteresis_AR_AX` ist ein robuster und flexibler Funktionsbaustein zur Realisierung von Dreipunkt-Regelungen. Durch die mathematische Absicherung der Grenzwerte und das klar definierte Zustandsverhalten eignet er sich hervorragend für anspruchsvolle Steuerungsaufgaben, bei denen Aktoren materialschonend und flatterfrei angesteuert werden müssen.
