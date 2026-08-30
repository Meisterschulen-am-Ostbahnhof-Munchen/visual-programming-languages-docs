# AUI_ADD_3


![AUI_ADD_3](./AUI_ADD_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUI_ADD_3` ist ein generischer arithmetischer Funktionsbaustein für die IEC 61499 Entwicklungsumgebung (4diac-ide). Seine primäre Aufgabe ist die Addition von drei Eingangswerten, die über standardisierte, unidirektionale Adapterschnittstellen übergeben werden. Das Ergebnis der Addition wird ebenfalls über einen entsprechenden Adapter ausgegeben. Durch die Kapselung von Daten und Steuerungsereignissen in Adaptern wird die Verdrahtung im Applikationseditor erheblich vereinfacht und die Übersichtlichkeit im Systemdesign verbessert.

## Schnittstellenstruktur

Die Schnittstellen von `AUI_ADD_3` basieren vollständig auf Adaptern, um eine saubere Strukturierung der Signale zu gewährleisten.

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge definiert.* Die Ereignissteuerung wird implizit über die Eingangs-Adapter (Sockets) abgewickelt.

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge definiert.* Die Ereignisweiterleitung erfolgt implizit über den Ausgangs-Adapter (Plug).

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge definiert.* Die Daten werden über die Eingangs-Adapter bereitgestellt.

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge definiert.* Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

#### Sockets (Eingangs-Adapter)

- **IN1** (Typ: `adapter::types::unidirectional::AUI`): Erster Eingangswert (Summand 1) für die arithmetische Addition.
- **IN2** (Typ: `adapter::types::unidirectional::AUI`): Zweiter Eingangswert (Summand 2) für die arithmetische Addition.
- **IN3** (Typ: `adapter::types::unidirectional::AUI`): Dritter Eingangswert (Summand 3) für die arithmetische Addition.

#### Plugs (Ausgangs-Adapter)

- **OUT** (Typ: `adapter::types::unidirectional::AUI`): Ausgang für das berechnete Ergebnis (Summe aus `IN1 + IN2 + IN3`).

---

## Funktionsweise

Der Funktionsbaustein realisiert eine dreistellige Addition nach folgender mathematischer Formel:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Sobald an einem der Eingangs-Adapter (`IN1`, `IN2` oder `IN3`) ein Aktualisierungsereignis eintrifft, liest der Funktionsbaustein die aktuellen Werte aller drei Eingänge ein. Anschließend berechnet er die Summe und stellt das Ergebnis am Ausgangs-Adapter `OUT` bereit. Gleichzeitig wird das zugehörige Aktualisierungsereignis über den `OUT`-Adapter weitergegeben, um nachfolgende Bausteine über den neuen Wert zu informieren.

Da es sich um einen generischen Baustein (`GEN_AUI_ADD`) handelt, richtet sich der unterstützte Datentyp (z. B. `INT`, `REAL`, `LREAL`) nach der konkreten Implementierung und Definition des verwendeten Adaptertyps `AUI`.

---

## Technische Besonderheiten

- **Generischer Baustein:** Durch das Attribut `eclipse4diac::core::GenericClassName = 'GEN_AUI_ADD'` ist der Baustein für verschiedene numerische Datentypen flexibel einsetzbar, sofern die verwendeten Adapter dies unterstützen.
- **Kompaktes Design:** Durch die Verwendung von Adaptern anstelle von separaten Event- und Daten-Ports wird das visuelle "Spaghetticode"-Problem in 4diac-Systemen minimiert.
- **Unidirektionale Kommunikation:** Die Verwendung von unidirektionalen Adaptern (`unidirectional::AUI`) stellt sicher, dass der Datenfluss klar definiert von den Eingängen zum Ausgang verläuft.

---

## Zustandsübersicht

Der Baustein arbeitet ereignisgesteuert und zustandslos (bzw. rein reaktiv):

1. **Wartezustand:** Der Baustein wartet auf ein Trigger-Ereignis an einem der Sockets (`IN1`, `IN2`, `IN3`).
2. **Berechnung:** Bei Ereigniseingang werden die Datenwerte ausgelesen und addiert.
3. **Ausgabe:** Der berechnete Wert wird an den Plug `OUT` geschrieben und das Trigger-Ereignis wird gefeuert.
4. **Rückkehr:** Der Baustein kehrt sofort in den Wartezustand zurück.

---

## Anwendungsszenarien

- **Sensorwert-Aggregation:** Addition von drei analogen Messwerten (z. B. drei Temperatursensoren zur Ermittlung einer Gesamtwärme oder drei Durchflussmesser).
- **Sollwert-Generierung:** Zusammenführung von Basis-Sollwert, Hand-Offset und Automatik-Korrekturwert in der Prozesstechnik.
- **Leistungsberechnung:** Summierung der Wirkleistungen von drei einzelnen Phasen eines elektrischen Netzes zu einer Gesamtleistung.

---

## Vergleich mit ähnlichen Bausteinen

- **Standard-ADD-Baustein (IEC 61131-3):** Ein klassischer `ADD`-Baustein besitzt diskrete Eingänge für Daten und Events. `AUI_ADD_3` bündelt diese logisch in Adaptern, was die Wiederverwendbarkeit und Übersichtlichkeit steigert.
- **AUI_ADD_2 (2-fach Addierer):** Während bei einem 2-fach Addierer zur Summierung von drei Werten zwei Bausteine kaskadiert werden müssten, erledigt `AUI_ADD_3` dies in einem einzigen Schritt. Dies spart Ressourcen und reduziert die Latenzzeit im System.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUI_ADD_3` ist ein effizienter Hilfsbaustein für arithmetische Operationen in modernen IEC 61499 Steuerungsanwendungen. Durch die konsequente Nutzung des Adapter-Konzepts fügt er sich nahtlos in serviceorientierte und modular aufgebaute Software-Architekturen ein und trägt zur Reduzierung der Komplexität in der grafischen Programmierung bei.
