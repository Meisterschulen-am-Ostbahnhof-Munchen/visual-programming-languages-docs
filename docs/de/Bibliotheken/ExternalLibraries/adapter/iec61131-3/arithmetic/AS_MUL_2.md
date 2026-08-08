# AS_MUL_2


![AS_MUL_2](./AS_MUL_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AS_MUL_2` ist ein generischer, arithmetischer Multiplikationsbaustein für IEC 61499-Anwendungen in der 4diac-IDE. Er dient dazu, zwei Eingangswerte miteinander zu multiplizieren. Die Besonderheit dieses Bausteins liegt in der Verwendung von Adapterschnittstellen anstelle von klassischen, diskreten Event- und Datenkanälen. Dies ermöglicht eine strukturierte und übersichtliche Signalübertragung.

## Schnittstellenstruktur
Der Baustein besitzt keine direkt herausgeführten standardmäßigen Event- oder Daten-Pins, sondern kapselt diese vollständig in Adaptern.

### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge vorhanden (Ereignisse werden über die Adapter empfangen).*

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden (Ereignisse werden über die Adapter gesendet).*

### **Daten-Eingänge**
*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**
* **Sockets (Eingangs-Schnittstellen):**
  * `IN1` (Typ: `adapter::types::unidirectional::AS`): Der erste Eingang (Multiplikand) für die Berechnung.
  * `IN2` (Typ: `adapter::types::unidirectional::AS`): Der zweite Eingang (Multiplikator) für die Berechnung.
* **Plugs (Ausgangs-Schnittstellen):**
  * `OUT` (Typ: `adapter::types::unidirectional::AS`): Das Ergebnis der Multiplikation ($OUT = IN1 \times IN2$).

---

## Funktionsweise
Sobald über die Eingangsadapter `IN1` und `IN2` Daten sowie ein auslösendes Ereignis eingehen, führt der Baustein die Multiplikation aus. Das mathematische Produkt der beiden Eingangswerte wird berechnet und zusammen mit dem entsprechenden Trigger-Ereignis über den Ausgangsadapter `OUT` zur weiteren Verwendung im System bereitgestellt.

Da der Baustein generisch ausgelegt ist (`GenericClassName = 'GEN_AS_MUL'`), passt er sich flexibel an die zugrundeliegenden Datentypen der verbundenen Adapter an (z. B. `INT`, `REAL`, `DINT`).

---

## Technische Besonderheiten
* **Generischer Baustein:** Durch die Definition als `GEN_AS_MUL` ist der Baustein nicht auf einen festen Datentyp fixiert.
* **Unidirektionale Adapterkopplung:** Die Verwendung des Adaptertyps `adapter::types::unidirectional::AS` sorgt für einen klaren, gerichteten Daten- und Signalfluss, wodurch Rückkopplungsschleifen vermieden werden.
* **Reduzierte Komplexität im Editor:** Durch die Kapselung von Daten und Events in Adaptern wird das visuelle "Spaghetticode"-Problem (zu viele Verbindungslinien) in der 4diac-IDE minimiert.

---

## Zustandsübersicht
Der Baustein verhält sich rein ereignisgesteuert:
1. **Wartestatus:** Der Baustein wartet auf ein Ereignis an den Sockets `IN1` oder `IN2`.
2. **Berechnung:** Nach Eintreffen eines Ereignisses werden die aktuellen Werte aus `IN1` und `IN2` gelesen und multipliziert.
3. **Ausgabe:** Das Ergebnis wird an `OUT` angelegt, und ein Ausgangsereignis wird über den Plug `OUT` emittiert.

---

## Anwendungsszenarien
* **Signal-Skalierung:** Multiplikation von analogen Sensorwerten mit einem Skalierungsfaktor, der über einen Adapter eingespeist wird.
* **Modulare Berechnungen:** Verwendung in komplexeren mathematischen Berechnungsnetzwerken, bei denen Datenströme strukturiert über Adapterbusse transportiert werden sollen.
* **Leistungsberechnung:** Multiplikation von Strom- und Spannungswerten zur Ermittlung der elektrischen Leistung in Echtzeitsystemen.

---

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem Standard-`MUL`-Baustein der IEC 61131-3 / IEC 61499, welcher mit einzelnen Pins für `REQ`, `CNF`, `IN1`, `IN2` und `OUT` arbeitet, bündelt `AS_MUL_2` diese Signale in jeweils einem einzigen logischen Kanal pro Anschluss. Dies erhöht die Wiederverwendbarkeit und sorgt für ein saubereres Anwendungsdesign, erfordert jedoch die Definition und Verwendung passender Adaptertypen im Projekt.

---

## Fazit
Der `AS_MUL_2` ist ein moderner und flexibler Funktionsbaustein für arithmetische Operationen in IEC 61499-Steuerungsprogrammen. Dank der generischen Struktur und der konsequenten Nutzung von Adaptern eignet er sich hervorragend für saubere, modulare und gut wartbare Software-Architekturen in der industriellen Automatisierung.