# ALI_ADD_4


![ALI_ADD_4](./ALI_ADD_4.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ALI_ADD_4` ist ein generischer arithmetischer Funktionsbaustein nach dem IEC 61131-3 Standard. Seine Hauptaufgabe besteht darin, die Summe von vier Eingangswerten zu berechnen. Im Gegensatz zu klassischen arithmetischen Bausteinen, die mit elementaren Datentypen und standardmäßigen Event-Eingängen/-Ausgängen arbeiten, nutzt dieser Baustein unidirektionale Adapter-Verbindungen des Typs `ALI` (Analog Line Interface). Dies ermöglicht eine gekapselte und übersichtliche Signalübertragung von Daten und den dazugehörigen Trigger-Ereignissen innerhalb der 4diac-ide.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Der Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die angeschlossenen Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Der Baustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Der Baustein besitzt keine direkten Daten-Eingänge. Die Datenübergabe erfolgt über die Eingangs-Adapter (Sockets).*

### **Daten-Ausgänge**

*Der Baustein besitzt keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt über den Ausgangs-Adapter (Plug).*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::ALI`): Erster Summand für die Addition.
-   **IN2** (Typ: `adapter::types::unidirectional::ALI`): Zweiter Summand für die Addition.
-   **IN3** (Typ: `adapter::types::unidirectional::ALI`): Dritter Summand für die Addition.
-   **IN4** (Typ: `adapter::types::unidirectional::ALI`): Vierter Summand für die Addition.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::ALI`): Ausgabe des berechneten Additionsergebnisses.

---

## Funktionsweise

Sobald an einem der Eingangs-Adapter (`IN1` bis `IN4`) ein neues Ereignis mitsamt aktualisiertem Datenwert eingeht, führt der Baustein die mathematische Addition der vier Werte aus:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

Das Ergebnis der Berechnung wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben und ein entsprechendes Ausgabe-Ereignis getriggert, um nachfolgende Bausteine im Kontrollfluss zu informieren.

---

## Technische Besonderheiten

-   **Generische Klasse:** Der Baustein basiert auf der generischen Basisklasse `GEN_ALI_ADD` (Attribut: `eclipse4diac::core::GenericClassName`).
-   **Adapter-Kopplung:** Durch die Verwendung von unidirektionalen Adaptern (`ALI`) werden Daten und Ereignisse in einer einzigen Verbindung gebündelt. Dies reduziert die visuelle Komplexität (den "Kabelsalat") im FBD-Editor (Function Block Diagram) von 4diac-ide drastisch.
-   **IEC 61131-3 Konformität:** Entspricht den Richtlinien für standardmäßige arithmetische Funktionen.

---

## Zustandsübersicht

Der Baustein `ALI_ADD_4` ist ein zustandsloser (kombinatorischer) Funktionsbaustein. Er speichert keine internen Zustände oder historischen Werte zwischen den Berechnungszyklen. Jede Berechnung basiert ausschließlich auf den aktuell an den Eingangs-Adaptern anliegenden Werten zum Zeitpunkt des Trigger-Ereignisses.

---

## Anwendungsszenarien

-   **Messwert-Konsolidierung:** Aufsummierung von vier analogen Messgrößen (z. B. Teillastströme, Durchflussmengen oder Einzelleistungen) zu einem Gesamtwert.
-   **Mischprozesse:** Berechnung von Gesamtgewichten oder Gesamtvolumina in Rezepturanlagen, bei denen vier Komponenten zusammengeführt werden.
-   **Signalverarbeitung:** Strukturierte Vorverarbeitung von Sensorsignalen in modular aufgebauten Steuerungsarchitekturen, die konsequent auf Adapter-Verbindungen setzen.

---

## Vergleich mit ähnlichen Bausteinen

-   **Standard ADD-Baustein (IEC 61131-3):** Ein Standard-ADD-Baustein verwendet elementare Datentypen (z. B. `REAL`, `INT`) sowie separate Event-Ports (`REQ` / `CNF`). `ALI_ADD_4` hingegen kapselt diese Schnittstellen in Adaptern, was die Wiederverwendbarkeit und Übersichtlichkeit erhöht.
-   **ALI_ADD_2 / ALI_ADD_3:** Diese Bausteine funktionieren nach demselben Prinzip, sind jedoch auf die Addition von nur zwei bzw. drei Eingangssignalen ausgelegt.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der Funktionsbaustein `ALI_ADD_4` bietet eine elegante und saubere Möglichkeit, vier analoge Werte innerhalb einer adapterbasierten 4diac-Applikation zu addieren. Durch die Kapselung von Daten- und Eventkanälen in `ALI`-Adaptern unterstützt er die Erstellung modularer, übersichtlicher und leicht wartbarer Steuerungssoftware.
