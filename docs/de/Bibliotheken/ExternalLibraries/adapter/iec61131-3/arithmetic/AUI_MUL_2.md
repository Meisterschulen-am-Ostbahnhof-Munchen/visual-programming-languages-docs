# AUI_MUL_2


![AUI_MUL_2](./AUI_MUL_2.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_MUL_2` ist ein generischer arithmetischer Funktionsblock für die Entwicklungsumgebung 4diac-ide, der zur Durchführung einer Multiplikation von zwei Eingangswerten dient. 

Die Besonderheit dieses Bausteins liegt in seiner adapterbasierten Architektur. Statt klassischer, einzelner Daten- und Ereignisleitungen nutzt dieser Baustein unidirektionale Adapter (`AUI`), um Daten und die dazugehörigen Steuerungsereignisse gekapselt zu übertragen. Dies reduziert die visuelle Komplexität von Steuerungsanwendungen erheblich.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird vollständig über die Eingangsadapter abgewickelt.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung wird vollständig über den Ausgangsadapter abgewickelt.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

* **`IN1` (Typ: `adapter::types::unidirectional::AUI` - Socket / Buchse):** 
  Der erste Eingangsadapter, der den ersten Faktor für die Multiplikation liefert.
* **`IN2` (Typ: `adapter::types::unidirectional::AUI` - Socket / Buchse):** 
  Der zweite Eingangsadapter, der den zweiten Faktor für die Multiplikation liefert.
* **`OUT` (Typ: `adapter::types::unidirectional::AUI` - Plug / Stecker):** 
  Der Ausgangsadapter, der das berechnete Produkt der beiden Eingangswerte sowie das entsprechende Aktualisierungsereignis ausgibt.

---

## Funktionsweise

Sobald an einem der Eingangsadapter (`IN1` oder `IN2`) ein Ereignis signalisiert, dass ein neuer Wert vorliegt, liest der Funktionsblock die aktuellen Werte aus beiden Adaptern aus. 

Die Berechnung erfolgt nach der klassischen mathematischen Formel:
`OUT = IN1 * IN2`

Nach erfolgreicher Berechnung wird das Ergebnis an den Ausgangsadapter `OUT` übergeben und gleichzeitig ein Ausgangsereignis ausgelöst, um nachfolgende Bausteine über das Vorhandensein eines neuen Werts zu informieren.

---

## Technische Besonderheiten

* **Generisches Verhalten:** Der Baustein ist über das Compiler-Attribut `GenericClassName` mit dem Wert `'GEN_AUI_MUL'` verknüpft. Das bedeutet, dass der Baustein datentypunabhängig (z. B. für `INT`, `REAL`, `LREAL` etc.) agieren kann, je nachdem, welcher konkrete Datentyp durch die angeschlossenen Adapter definiert wird.
* **Effiziente Verdrahtung:** Durch die Kapselung in `AUI`-Adapter (Adapter Unidirectional Interface) wird die Anzahl der Verbindungen im Funktionsplan drastisch reduziert, da Daten- und Ereignisflüsse zusammengefasst sind.

---

## Zustandsübersicht

Der Funktionsbaustein arbeitet rein ereignisgesteuert und zustandslos (reaktiv):
1. **Bereitschaftszustand:** Der Baustein wartet auf eingehende Ereignisse über `IN1` oder `IN2`.
2. **Berechnungsphase:** Ein eingehendes Ereignis triggert die interne Multiplikation der aktuellen Adapterdaten.
3. **Ausgabephase:** Das berechnete Produkt wird an `OUT` angelegt und das Ausgabeereignis getriggert. Der Baustein kehrt sofort in den Bereitschaftszustand zurück.

---

## Anwendungsszenarien

* **Messwertskalierung:** Multiplikation eines analogen Sensorwerts (z. B. Spannung) mit einem Skalierungsfaktor zur Berechnung des physikalischen Istwerts.
* **Leistungsberechnung:** Kontinuierliche Multiplikation von Strom (I) und Spannung (U) zur Ermittlung der aktuellen Wirkleistung (P).
* **Signalverstärkung:** Anwendung im Bereich der Signalverarbeitung zur einfachen Pegelanpassung.

---

## Vergleich mit ähnlichen Bausteinen

* **Standard `MUL` Baustein (IEC 61131-3):** Ein Standard-Multiplikationsbaustein benötigt separate Pins für jedes Datensignal sowie für die Ausführungssteuerung (`REQ`/`CNF`). `AUI_MUL_2` löst dies eleganter und platzsparender über Adapterverbindungen.
* **Multi-Input-Multiplizierer (`MUL_3`, `MUL_4`):** Während Bausteine wie `AUI_MUL_2` fest auf zwei Eingänge ausgelegt sind, erlauben Multi-Input-Bausteine die Multiplikation von drei oder mehr Faktoren in einem einzigen Schritt, weisen dafür jedoch eine höhere Komplexität auf.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUI_MUL_2` ist ein hochgradig modularer und moderner Funktionsbaustein für die 4diac-ide. Durch die konsequente Nutzung von unidirektionalen Adaptern fördert er ein sauberes Softwaredesign in verteilten Steuerungssystemen nach IEC 61499, ohne dabei an Flexibilität bei den verarbeiteten Datentypen einzubüßen.