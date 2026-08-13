# AR_MUL_2


![AR_MUL_2](./AR_MUL_2.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein (FB) **AR_MUL_2** ist ein generischer Arithmetik-Baustein für die 4diac-IDE. Er dient zur Multiplikation von zwei Werten, die über unidirektionale Adapter übertragen werden. Durch die Kapselung der mathematischen Operation in eine Adapter-Schnittstelle ermöglicht dieser Baustein eine saubere, modulare und übersichtliche Modellierung von Berechnungen innerhalb von IEC 61499 Anwendungen.

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen ereignis- oder datenbasierten Ein- und Ausgänge. Die gesamte Kommunikation wird über Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden.* (Die Ereignissteuerung wird über die Adapter realisiert.)

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::AR`): Erster Eingangswert (Multiplikand 1) für die Multiplikation.
*   **IN2** (Typ: `adapter::types::unidirectional::AR`): Zweiter Eingangswert (Multiplikand 2) für die Multiplikation.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::AR`): Ausgang für das berechnete Produkt der Multiplikation ($OUT = IN1 \times IN2$).

---

## Funktionsweise

Sobald über die Eingangs-Adapter `IN1` und `IN2` neue Werte oder entsprechende Trigger-Ereignisse eintreffen, multipliziert der Funktionsbaustein die Werte der beiden Eingänge. Das Ergebnis der mathematischen Operation ($IN1 \cdot IN2$) wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben und für nachfolgende Bausteine bereitgestellt.

Da es sich um einen generischen Funktionsbaustein (`GEN_AR_MUL`) handelt, ist die Implementierung flexibel gegenüber den konkret verwendeten Datentypen innerhalb der `AR`-Adapterstruktur.

---

## Technische Besonderheiten

*   **Generischer Baustein:** Durch das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AR_MUL'` ist der Baustein für verschiedene numerische Datentypen einsetzbar, sofern die Adapter diese unterstützen.
*   **Unidirektionale Adapter:** Die Verwendung des Typs `unidirectional::AR` sorgt für einen klaren Datenfluss ohne Rückkopplungsschleifen, was die Stabilität der Applikation erhöht und die Latenz minimiert.
*   **Compiler-Zugehörigkeit:** Der FB ist dem Package `adapter::iec61131::arithmetic` zugeordnet und konform zum Standard IEC 61499-2.

---

## Zustandsübersicht

Da dieser Funktionsbaustein primär datenflussgesteuert über Adapter arbeitet, besitzt er kein komplexes internes Zustandsdiagramm (ECC). Er agiert als zustandsloses Übertragungsglied:
1. **Warten:** Baustein wartet auf Datenaktualisierungen an den Adaptern `IN1` und/oder `IN2`.
2. **Berechnung:** Bei Wertänderung wird das Produkt gebildet.
3. **Ausgabe:** Das Ergebnis wird direkt an den Ausgang `OUT` weitergeleitet.

---

## Anwendungsszenarien

*   **Messwertskalierung:** Multiplikation eines analogen Sensorwertes (z. B. einer Spannung) mit einem Skalierungsfaktor zur Umrechnung in eine physikalische Einheit.
*   **Signalverstärkung:** Proportionale Verstärkung von Regelsignalen in der Prozessautomatisierung.
*   **Mathematische Berechnungen:** Einsatz als modularer Baustein in komplexeren Berechnungsnetzwerken innerhalb von 4diac-Applikationen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu Standard-Multiplikationsbausteinen (wie dem klassischen `MUL`-Baustein nach IEC 61131-3), die mit elementaren Datentypen (z.B. `INT`, `REAL`) arbeiten, nutzt `AR_MUL_2` strukturierte **Adapter**. Dies hat folgende Vorteile:
*   **Geringerer Verdrahtungsaufwand:** Signale und dazugehörige Steuerungsereignisse werden in einer einzigen Adapterverbindung gebündelt.
*   **Bessere Lesbarkeit:** Komplexe Steuerungsdiagramme bleiben übersichtlich, da weniger Einzelverbindungen auf der Arbeitsfläche gezogen werden müssen.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AR_MUL_2`-Funktionsbaustein ist ein effizientes Werkzeug für arithmetische Operationen in modernen, adapterbasierten Steuerungsprogrammen. Durch die Kapselung in unidirektionale Schnittstellen bietet er ein hohes Maß an Wiederverwendbarkeit und sorgt für ein sauberes und strukturiertes Design innerhalb der 4diac-Umgebung.