# AI_MUL_3


![AI_MUL_3](./AI_MUL_3.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AI_MUL_3` ist ein generischer arithmetischer Baustein, der für die Multiplikation von drei Eingangswerten entwickelt wurde. Er entspricht der Klassifizierung für Standard-Arithmetikfunktionen nach IEC 61131-3 und nutzt das Adapter-Konzept von 4diac. Durch die Kapselung der Signale in Adaptern wird die visuelle Komplexität im Funktionsplan erheblich reduziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird intern über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignissteuerung wird intern über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::AI`): Der erste Multiplikand (Eingangswert 1).
*   **IN2** (Typ: `adapter::types::unidirectional::AI`): Der zweite Multiplikand (Eingangswert 2).
*   **IN3** (Typ: `adapter::types::unidirectional::AI`): Der dritte Multiplikand (Eingangswert 3).

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::AI`): Das Ergebnis der Multiplikation.

---

## Funktionsweise

Der Funktionsbaustein führt eine kontinuierliche oder ereignisgesteuerte arithmetische Multiplikation der drei über die Sockets anliegenden Werte aus. 

Die mathematische Formel lautet:
$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3}$$

Sobald sich die Werte an den Eingangs-Adaptern ändern oder ein entsprechendes Aktualisierungsereignis über die Adapter getriggert wird, berechnet der Baustein das Produkt und stellt dieses am Ausgangs-Adapter `OUT` zur Verfügung.

---

## Technische Besonderheiten

*   **Generischer Charakter:** Der Baustein ist als generischer Typ deklariert (`GenericClassName` = `'GEN_AI_MUL'`). Das bedeutet, dass er flexibel mit verschiedenen numerischen Datentypen (wie z. B. REAL, LREAL, INT) arbeiten kann, sofern diese vom Adaptertyp `AI` unterstützt werden.
*   **Adapter-Kopplung:** Durch die Verwendung von unidirektionalen Adaptern (`unidirectional::AI`) werden Daten und deren Gültigkeitsereignisse zusammengefasst. Dies vereinfacht die Verdrahtung in der 4diac-IDE drastisch, da keine separaten Event- und Datenleitungen gezogen werden müssen.

---

## Zustandsübersicht

Der Baustein besitzt kein komplexes internes Zustandsdiagramm (zustandslos). Er reagiert rein reaktiv auf Wertänderungen oder Trigger-Ereignisse an den Eingängen `IN1`, `IN2` und `IN3` und gibt das Ergebnis unmittelbar an `OUT` weiter.

---

## Anwendungsszenarien

*   **Messwertskalierung:** Multiplikation eines analogen Rohwertes (`IN1`) mit einem Kalibrierungsfaktor (`IN2`) und einem weiteren Korrekturfaktor (`IN3`).
*   **Physikalische Berechnungen:** Berechnung von Volumina ($V = l \times b \times h$) oder Leistungen, bei denen drei Faktoren direkt miteinander multipliziert werden müssen.
*   **Kaskadierte Verstärkungen:** Signalverarbeitungsketten, bei denen ein Signal nacheinander zwei Verstärkungsstufen durchläuft.

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard-MUL-Baustein (IEC 61131-3):** Klassische Multiplikationsbausteine besitzen direkte Datenpins (z. B. `ANY_NUM`) und benötigen explizite Event-Verbindungen (`REQ` / `CNF`). `AI_MUL_3` bündelt diese Logik in Adaptern.
*   **AI_MUL_2 (Zweifach-Multiplizierer):** Während bei der Multiplikation von drei Werten mit einem Standard-Zweifach-Multiplizierer zwei Bausteine hintereinandergeschaltet werden müssen, erledigt `AI_MUL_3` dies in einem einzigen Schritt, was Ressourcen und Platz im Steuerungsdiagramm spart.

---

## Fazit

Der `AI_MUL_3` Funktionsbaustein bietet eine effiziente, saubere und performante Möglichkeit, dreifache Multiplikationen innerhalb einer 4diac-Anwendung zu realisieren. Durch die konsequente Nutzung des Adapter-Konzepts trägt er maßgeblich zur Übersichtlichkeit und Wartbarkeit von Steuerungssoftware bei.