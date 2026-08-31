# ALI_MUL_4


![ALI_MUL_4](./ALI_MUL_4.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALI_MUL_4` dient zur Durchführung einer arithmetischen Multiplikation von vier Eingangswerten. Es handelt sich um einen generischen Funktionsbaustein (Generic FB), der auf der Verwendung von unidirektionalen Adaptern (`ALI`) basiert. Durch die Nutzung von Adaptern anstelle von klassischen Daten- und Ereignispins wird die Verdrahtung in 4diac-ide übersichtlicher und modularer gestaltet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung und Triggerung erfolgt über die angebundenen Adapter.

### **Ereignis-Ausgänge**

Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

Die Sockets dienen als Eingänge für die zu multiplizierenden Werte.

- **IN1** (Typ: `adapter::types::unidirectional::ALI`): Erster Faktor für die Multiplikation.
- **IN2** (Typ: `adapter::types::unidirectional::ALI`): Zweiter Faktor für die Multiplikation.
- **IN3** (Typ: `adapter::types::unidirectional::ALI`): Dritter Faktor für die Multiplikation.
- **IN4** (Typ: `adapter::types::unidirectional::ALI`): Vierter Faktor für die Multiplikation.

#### **Plugs (Ausgangs-Adapter)**

Der Plug gibt das berechnete Ergebnis aus.

- **OUT** (Typ: `adapter::types::unidirectional::ALI`): Das berechnete Produkt der vier Eingangs-Adapter.

---

## Funktionsweise

Sobald sich die Eingangswerte an den Adaptern `IN1` bis `IN4` ändern oder ein entsprechendes Aktualisierungsereignis über die Adapter getriggert wird, multipliziert der Baustein die vier Werte intern nach folgendem mathematischen Prinzip:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3} \times \text{IN4}$$

Das Ergebnis sowie das zugehörige Aktualisierungsereignis werden anschließend über den Ausgangs-Adapter `OUT` ausgegeben.

---

## Technische Besonderheiten

- **Generischer Baustein:** Durch das Attribut `GenericClassName` mit dem Wert `GEN_ALI_MUL` ist der Baustein datentypunabhängig konzipiert. Er kann je nach Implementierung der `ALI`-Adapter verschiedene numerische Datentypen (z. B. `INT`, `REAL`, `LREAL`) verarbeiten.
- **Adapter-Kopplung:** Durch den Einsatz von unidirektionalen `ALI`-Adaptern wird eine saubere Kapselung von Daten und Trigger-Ereignissen erreicht, was die Komplexität im Systementwurf reduziert.

---

## Zustandsübersicht

Der Funktionsbaustein ist zustandslos (zustandsfreie, rein kombinatorische Verarbeitung). Es gibt keine internen Zustandsmaschinen (Execution Control Chart / ECC). Die Ausgangswerte hängen direkt von den an den Eingangs-Adaptern anliegenden Werten ab.

---

## Anwendungsszenarien

- **Skalierung und Gewichtung:** Berechnung von zusammengesetzten Skalierungsfaktoren in der Prozessautomatisierung.
- **Volumen- und Massenberechnung:** Kontinuierliche Berechnung physikalischer Größen (z. B. $L\ddot{a}nge \times Breite \times H\ddot{o}he \times Dichte$).
- **Mehrstufige Verstärkungsregelungen:** Kaskadierte Signalverstärkung in der Mess- und Regelungstechnik.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Multiplikationsbaustein (`MUL`) nach IEC 61131-3, der meist nur zwei direkte Dateneingänge besitzt, bietet `ALI_MUL_4`:

1. Die direkte Multiplikation von **vier** Faktoren in einem einzigen Schritt (weniger Bausteine auf dem Control-Canvas nötig).
2. Die Nutzung von **Adaptern** statt Einzelverdrahtungen, was die Übersichtlichkeit des Gesamtprogramms signifikant erhöht.

---

- **[`ALI_MUL_4_UNGATED`](ALI_MUL_4_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALI_MUL_4` ist ein effizienter Hilfsbaustein für arithmetische Berechnungen in komplexen 4diac-Systemen. Er eignet sich besonders für Anwendungen, bei denen mehrere Werte kompakt und strukturiert miteinander multipliziert werden müssen, ohne die Benutzeroberfläche mit unzähligen Verbindungslinien zu überladen.
