# AI_MUL_4




![AI_MUL_4](./AI_MUL_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AI_MUL_4` ist ein generischer arithmetischer Baustein für 4diac-IDE, der der Norm IEC 61131-3 entspricht. Seine Hauptaufgabe besteht darin, das mathematische Produkt aus vier analogen Eingangswerten zu berechnen. Der Baustein nutzt unidirektionale Adapter vom Typ `AI` (Analog Input), um sowohl Daten als auch die dazugehörigen Ereignisse gekapselt zu übertragen. Dies reduziert den Verdrahtungsaufwand im Funktionsplan erheblich und sorgt für eine sauberere Strukturierung der Steuerungslogik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsbaustein besitzt keine direkten, eigenständigen Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die angeschlossenen Adapter abgewickelt.

### **Ereignis-Ausgänge**

Der Funktionsbaustein besitzt keine direkten, eigenständigen Ereignis-Ausgänge. Die Triggerung nachfolgender Bausteine erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge vorhanden. Die Wertebereitstellung erfolgt über die Adapter-Eingänge.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Die Ausgabe des berechneten Werts erfolgt über den Adapter-Ausgang.

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AI`): Erster Multiplikand.
-   **IN2** (Typ: `adapter::types::unidirectional::AI`): Zweiter Multiplikand.
-   **IN3** (Typ: `adapter::types::unidirectional::AI`): Dritter Multiplikand.
-   **IN4** (Typ: `adapter::types::unidirectional::AI`): Vierter Multiplikand.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AI`): Produkt der Multiplikation aller vier Eingänge ($OUT = IN1 \cdot IN2 \cdot IN3 \cdot IN4$).

## Funktionsweise

Sobald an einem der Eingangs-Adapter (`IN1` bis `IN4`) ein neues Ereignis signalisiert, dass sich die Daten aktualisiert haben, liest der Funktionsbaustein die analogen Werte der vier Adapter aus.

Die Berechnung erfolgt nach der Formel:
$$\text{Ergebnis} = \text{Wert}(IN1) \cdot \text{Wert}(IN2) \cdot \text{Wert}(IN3) \cdot \text{Wert}(IN4)$$

Das Ergebnis dieser Berechnung wird an den Ausgangs-Adapter `OUT` übergeben, und das entsprechende Aktualisierungsereignis des Adapters wird ausgelöst, um nachfolgende Bausteine im Kontrollfluss über den neuen Wert zu informieren.

## Technische Besonderheiten

-   **Generische Klasse:** Der Baustein basiert intern auf der generischen Klasse `GEN_AI_MUL`. Dies ermöglicht eine flexible Verarbeitung der Datenströme unabhängig von spezifischen Hardware-Implementierungen.
-   **Unidirektionale Adapter:** Durch die Verwendung des Typs `adapter::types::unidirectional::AI` fließen Daten und Trigger-Signale in nur eine Richtung (vom Sender zum Empfänger). Das vereinfacht das Signal-Design und vermeidet Rückkopplungsschleifen.
-   **Kompakte Struktur:** Durch die Verarbeitung von vier Eingängen in einem einzigen Baustein wird das Kaskadieren mehrerer Multiplikationsbausteine überflüssig.

## Zustandsübersicht

Da es sich bei `AI_MUL_4` um einen rein mathematischen, daten- und ereignisgesteuerten Funktionsbaustein handelt, besitzt er keinen internen Zustandsautomaten (ECC). Die Ausführung verhält sich rein zustandslos:

1. **Warten:** Der Baustein wartet auf ein Aktualisierungsereignis an einem der Sockets (`IN1` bis `IN4`).
2. **Berechnen:** Bei Triggerung werden die aktuellen Werte aller vier Eingänge multipliziert.
3. **Ausgeben:** Das Ergebnis wird an den Plug `OUT` angelegt und das Ausgabeereignis getriggert. Der Baustein kehrt sofort in den Wartezustand zurück.

## Anwendungsszenarien

-   **Skalierung und Kalibrierung:** Berechnung von zusammengesetzten Korrekturfaktoren für analoge Sensorwerte (z. B. Sensorwert $\cdot$ Kalibrierungsfaktor $\cdot$ Temperaturkompensation $\cdot$ Einheitenumrechnung).
-   **Physikalische Berechnungen:** Berechnung von Werten, die von mehreren analogen Faktoren abhängen, wie beispielsweise Volumenströme oder elektrische Leistungen unter Einbeziehung verschiedener Wirkungsgrade.
-   **Kaskadierte Verstärkungsglieder:** Einsatz in Regelungskreisen, bei denen mehrere Verstärkungsfaktoren (Gains) nacheinander auf ein analoges Signal angewendet werden müssen.

## Vergleich mit ähnlichen Bausteinen

-   **Standard-MUL (IEC 61131-3):** Klassische Multiplikationsbausteine arbeiten meist nur mit elementaren Datentypen (z. B. `REAL`, `INT`) und benötigen separate Event-Leitungen (`REQ` / `CNF`). Zudem unterstützen sie oft standardmäßig nur zwei Eingänge. `AI_MUL_4` hingegen verarbeitet vier Eingänge direkt und nutzt Adapter zur Kapselung, was das Netzwerklayout übersichtlicher macht.
-   **AI_MUL_2:** Ein ähnlicher adapterbasierter Baustein, jedoch nur für zwei Eingänge. `AI_MUL_4` spart bei komplexeren Berechnungen mit bis zu vier Faktoren zusätzlichen Verdrahtungsaufwand und Baustein-Instanzen.

- **[`AI_MUL_4_UNGATED`](AI_MUL_4_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AI_MUL_4`-Funktionsbaustein bietet eine effiziente und saubere Möglichkeit, komplexe Multiplikationsaufgaben mit bis zu vier analogen Signalen in 4diac-IDE zu realisieren. Durch die konsequente Nutzung von unidirektionalen Adaptern wird der Verkabelungsaufwand minimiert und die Lesbarkeit des Applikationsdesigns signifikant verbessert.
