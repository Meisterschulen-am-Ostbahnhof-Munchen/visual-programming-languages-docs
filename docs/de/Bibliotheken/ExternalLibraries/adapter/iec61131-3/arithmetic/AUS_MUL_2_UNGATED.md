# AUS_MUL_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AUS_MUL_2`](AUS_MUL_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![AUS_MUL_2_UNGATED](./AUS_MUL_2_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUS_MUL_2_UNGATED` ist ein generischer Arithmetikbaustein für die 4diac-IDE, der zur Multiplikation zweier Werte dient. Im Gegensatz zu klassischen mathematischen Funktionsbausteinen nutzt dieser Baustein ein adapterbasiertes Konzept zur Datenübertragung. Dadurch wird eine strukturierte, modulare und übersichtliche Signalverdrahtung in komplexen IEC 61499 Anwendungen ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird über die angeschlossenen Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge.*

### **Adapter**

Die gesamte Kommunikation (Daten und zugehörige Trigger-Ereignisse) wird über unidirektionale Adapter des Typs `AUS` realisiert.

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AUS`): Der erste Multiplikand (Eingang 1).
-   **IN2** (Typ: `adapter::types::unidirectional::AUS`): Der zweite Multiplikand (Eingang 2).

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AUS`): Das Ergebnis der Multiplikation ($IN1 \times IN2$).

---

## Funktionsweise

Sobald an den Eingangs-Adaptern `IN1` oder `IN2` ein neues Ereignis signalisiert wird, das auf neue Daten hinweist, führt der Funktionsbaustein intern die Multiplikation aus:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

Das Ergebnis der Berechnung sowie das entsprechende Bestätigungsereignis werden anschließend über den Ausgangs-Plug `OUT` an nachfolgende Bausteine weitergegeben. Da es sich um einen generischen Baustein (`GEN_AUS_MUL`) handelt, passt sich die interne Verarbeitung flexibel an den im Adapter definierten Datentyp an.

---

## Technische Besonderheiten

-   **Generischer Charakter:** Der Baustein ist als generischer Typ (`GenericClassName = 'GEN_AUS_MUL'`) deklariert. Dies ermöglicht eine flexible Handhabung verschiedener numerischer Datentypen (z. B. `INT`, `REAL`, `LREAL`), die durch die Adapterstruktur vorgegeben werden.
-   **Adapter-Fokus:** Die Reduktion von klassischen Pins hin zu Adaptern minimiert den Verdrahtungsaufwand im Funktionsplan erheblich und sorgt für ein sauberes, objektorientiertes Design.

---

## Zustandsübersicht

Der Baustein arbeitet ereignisgesteuert basierend auf den Zustandsänderungen der Adapter:

1.  **IDLE (Bereitschaft):** Der Baustein wartet auf eingehende Werte/Ereignisse an den Sockets `IN1` und `IN2`.
2.  **BERECHNUNG:** Bei Empfang eines Triggers wird die Multiplikation der in den Adaptern enthaltenen Datenwerte ausgeführt.
3.  **AUSGABE:** Das Produkt wird in den Adapter `OUT` geschrieben und ein Sende-Ereignis ausgelöst. Der Baustein kehrt in den Zustand *IDLE* zurück.

---

## Anwendungsszenarien

-   **Messwertskalierung:** Multiplikation eines Rohwertes (z. B. aus einem Sensor-Adapter) mit einem Kalibrierungsfaktor.
-   **Leistungsberechnung:** Multiplikation von Strom- und Spannungswerten, die über standardisierte Adapter-Schnittstellen eingelesen werden.
-   **Modulare Signalverarbeitung:** Einsatz in komplexen Regelungsschleifen, bei denen Signalketten sauber durch Adapter gekapselt sind, um die Übersicht im Steuerungsdiagramm zu wahren.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-3-Multiplikationsbaustein (`MUL`), der mit einzelnen Pins für `REQ`, `CNF` sowie direkten Daten-Ein- und Ausgängen arbeitet, bündelt `AUS_MUL_2_UNGATED` all diese Signale in Adaptern. Dies verhindert "Kabelsalat" im Funktionsplan, erfordert jedoch, dass die angebundenen Signale bereits im `AUS`-Adapterformat vorliegen.

---

- **[`AUS_MUL_2`](AUS_MUL_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AUS_MUL_2_UNGATED` ist ein moderner, robuster und wiederverwendbarer Funktionsbaustein zur Multiplikation in der 4diac-IDE. Durch die konsequente Nutzung von unidirektionalen Adaptern eignet er sich hervorragend für serviceorientierte Architekturen und strukturierte Applikationsdesigns im industriellen Umfeld.
