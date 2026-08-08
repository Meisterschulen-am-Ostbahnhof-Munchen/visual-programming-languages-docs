# AS_ADD_3


![AS_ADD_3](./AS_ADD_3.svg)

**********

## Einleitung

Der Funktionsbaustein `AS_ADD_3` ist ein generischer Funktionsbaustein (Generic FB) für die IEC 61499, der für die Durchführung einer arithmetischen Addition von drei Eingangswerten entwickelt wurde. Die Besonderheit dieses Bausteins liegt darin, dass er keine direkten Daten- und Ereignis-Ein-/Ausgänge besitzt, sondern vollständig auf der Verwendung von unidirektionalen Adaptern basiert. Dies vereinfacht die Modellierung und Verdrahtung in komplexeren Systemen erheblich.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird über die angeschlossenen Adapter abgewickelt.

### **Ereignis-Ausgänge**
Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**
Es sind keine direkten Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Es sind keine direkten Daten-Ausgänge vorhanden.

### **Adapter**

Der Baustein kommuniziert ausschließlich über Adapter-Schnittstellen.

#### **Sockets (Buchsen - Eingänge):**
*   **IN1** (Typ: `adapter::types::unidirectional::AS`): Erster Eingang für die Addition.
*   **IN2** (Typ: `adapter::types::unidirectional::AS`): Zweiter Eingang für die Addition.
*   **IN3** (Typ: `adapter::types::unidirectional::AS`): Dritter Eingang für die Addition.

#### **Plugs (Stecker - Ausgänge):**
*   **OUT** (Typ: `adapter::types::unidirectional::AS`): Ausgang, der das Ergebnis der Addition (`IN1 + IN2 + IN3`) bereitstellt.

---

## Funktionsweise

Der Funktionsbaustein `AS_ADD_3` führt eine klassische Addition aus:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Da der Baustein als generischer Funktionsbaustein (`GEN_AS_ADD`) definiert ist, kann er je nach konkreter Instanziierung und dem im Adapter verwendeten Datentyp verschiedene numerische Datentypen (z. B. `INT`, `REAL`, `DINT`) verarbeiten.

Sobald an den Eingangs-Adaptern (`IN1`, `IN2`, `IN3`) neue Werte und die dazugehörigen Ereignisse signalisiert werden, berechnet der Baustein die Summe und triggert das entsprechende Ausgangsereignis am `OUT`-Adapter, um den neuen Wert an nachfolgende Bausteine weiterzugeben.

---

## Technische Besonderheiten

*   **Generischer Typ (Generic FB):** Der Baustein nutzt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AS_ADD'`. Dies ermöglicht eine flexible Anpassung an unterschiedliche Datentypen, ohne dass für jeden Typ ein eigener Baustein erstellt werden muss.
*   **Kapselung durch Adapter:** Durch die Verwendung von unidirektionalen Adaptern (`AS`) werden Daten und die dazugehörigen Trigger-Ereignisse in einer einzigen Verbindung gekapselt. Dies sorgt für ein sauberes und übersichtliches Oberflächendesign in der 4diac IDE.

---

## Zustandsübersicht

Der Baustein arbeitet ereignisgesteuert und besitzt kein komplexes internes Zustandsdiagramm (ECC). Seine Ausführung wird durch die an den Sockets eingehenden Adapter-Ereignisse getriggert:

1.  **Warten:** Der Baustein wartet auf ein Aktualisierungsereignis an den Adaptern `IN1`, `IN2` oder `IN3`.
2.  **Berechnung:** Bei Empfang eines Ereignisses werden die aktuellen Werte der drei Eingänge addiert.
3.  **Ausgabe:** Das Ergebnis wird an den Plug `OUT` angelegt und ein Aktualisierungsereignis über den Adapter gesendet.

---

## Anwendungsszenarien

*   **Messwert-Summierung:** Addition von drei analogen Sensorwerten (z. B. drei Durchflussmesser, um einen Gesamtdurchfluss zu berechnen).
*   **Sollwert-Offset-Berechnung:** Berechnung eines Gesamtsollwerts basierend auf einem Basissollwert, einem Benutzer-Offset und einem Korrekturwert aus einer übergeordneten Steuerung.
*   **Kombination von Signalquellen:** Zusammenführung von drei Teilsignalen in der Prozessautomatisierung unter Verwendung standardisierter Adapter-Strukturen.

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard-ADD-Bausteine (IEC 61131-3):** Klassische ADD-Bausteine nutzen dedizierte Daten-Pins (z. B. `IN1`, `IN2`) und separate Event-Pins (`REQ`, `CNF`). `AS_ADD_3` reduziert den Verdrahtungsaufwand im FBD (Function Block Diagram) durch die Nutzung von Adaptern auf ein Minimum.
*   **AS_ADD_2 (Zwei-Wege-Addierer):** Im Vergleich zu einer Variante mit nur zwei Eingängen spart der `AS_ADD_3` bei der Addition von drei Werten einen kompletten Baustein sowie die dazugehörige Zwischenverdrahtung ein.

---

## Fazit

Der `AS_ADD_3` ist ein hocheffizienter, modularer Baustein zur Addition von drei Werten. Durch die konsequente Nutzung von unidirektionalen Adaptern fügt er sich perfekt in moderne, serviceorientierte und sauber strukturierte IEC 61499 Steuerungsanwendungen ein.