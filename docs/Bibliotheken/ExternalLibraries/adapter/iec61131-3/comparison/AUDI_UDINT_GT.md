# AUDI_UDINT_GT


![AUDI_UDINT_GT](./AUDI_UDINT_GT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUDI_UDINT_GT` führt einen Vergleich zweier vorzeichenloser 32‑Bit‑Ganzzahlen (UDINT) durch. Er prüft, ob der Wert eines über einen Adapter‑Socket bereitgestellten Eingangs (IN1) größer ist als ein zweiter, direkt als Dateneingang übergebener Wert (IN2). Das Ergebnis wird über einen Adapter‑Plug ausgegeben. Der Baustein realisiert den in IEC 61131‑3 spezifizierten Vergleichsoperator **GRÖSSER ALS** .

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Beschreibung                                 |
|------|-------|----------------------------------------------|
| REQ  | Event | Dienstaufforderung (Service Request) zur Auslösung des Vergleichs. Mit diesem Ereignis wird der Dateneingang IN2 gelesen. |

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenen Ereignis‑Ausgänge. Das Ergebnis des Vergleichs wird jedoch über den Adapter‑Plug `OUT` signalisiert (siehe Abschnitt Adapter).

### **Daten-Eingänge**

| Name | Typ   | Beschreibung          |
|------|-------|-----------------------|
| IN2  | UDINT | Zweiter Vergleichswert (rechte Seite des Operators >). |

### **Daten-Ausgänge**

Der FB besitzt keine eigenen Daten‑Ausgänge. Der Ergebniswert wird über den Adapter‑Plug `OUT` bereitgestellt (siehe Abschnitt Adapter).

### **Adapter**

| Typ        | Name | Art   | Beschreibung                                                                             |
|------------|------|-------|------------------------------------------------------------------------------------------|
| Socket (IN1) | AUDI | Socket | Liefert den ersten Vergleichswert. Dieser Adapter stellt einen Ereignis‑Eingang (E1) und einen Daten‑Eingang (D1) zur Verfügung. |
| Plug (OUT)   | AX   | Plug  | Gibt das Vergleichsergebnis aus. Dieser Adapter besitzt einen Ereignis‑Ausgang (E1) und einen Daten‑Ausgang (D1). Das Ergebnis ist **TRUE**, wenn IN1 > IN2, sonst **FALSE**. |

## Funktionsweise

1. Der Baustein wartet auf ein **REQ‑Ereignis**.
2. Bei Eintreffen von REQ werden die aktuellen Werte von IN2 (direkter Dateneingang) sowie von IN1 (über den Adapter‑Socket) eingelesen.
3. Intern wird der vordefinierte Funktionsbaustein `F_GT` (IEC 61131‑3 „Greater Than“) aktiviert. Dieser vergleicht die beiden UDINT‑Werte.
4. Das Ergebnis des Vergleichs (Boolescher Wert) wird über den Adapter‑Plug `OUT` ausgegeben. Ein entsprechendes Ereignis signalisiert die Verfügbarkeit des Ergebnisses auf dem Adapter‑Ausgang.
5. Der Baustein kehrt daraufhin in den Wartezustand zurück und kann erneut über REQ angestoßen werden.

## Technische Besonderheiten

- **Adapter‑basierte Schnittstelle:** Der FB nutzt die 4diac‑eigene Adaptertechnologie, um Eingänge und Ausgänge flexibel zu kapseln. Die Adapter `AUDI` und `AX` entsprechen den Standard‑Unidirectional‑Typen.
- **IEC 61131‑3‑Konformität:** Der Vergleich wird durch den standardisierten Baustein `F_GT` realisiert, was Wiederverwendbarkeit und Interoperabilität gewährleistet.
- **Implizite Ereignisverkettung:** Durch die Kopplung des internen `F_GT` mit dem Ausgangsadapter wird der Ereignis‑Daten‑Zusammenhang automatisch hergestellt – kein manuelles Verknüpfen von Ausgangsereignissen erforderlich.
- **Typensicherheit:** Beide Vergleichswerte müssen vom Typ `UDINT` sein. Der Baustein führt keine impliziten Typkonvertierungen durch.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten. Er arbeitet ereignisgesteuert:
- **Idle:** Warten auf das **REQ**‑Ereignis.
- **Processing:** Nach REQ werden die Werte gelesen, der interne `F_GT` abgearbeitet und das Ergebnis über den OUT‑Adapter ausgegeben. Der Zustand wird nach Abschluss der Ausgabe sofort wieder verlassen.

Die interne Ausführung des `F_GT` erfolgt gemäß dessen Spezifikation in einem Schritt.

## Anwendungsszenarien

- **Schwellwertüberwachung:** Überwachen, ob ein Prozesswert (über IN1) einen Grenzwert (über IN2) überschreitet.
- **Qualitätskontrolle:** Prüfen, ob eine Zählung oder ein Messwert einen vorgegebenen Sollwert überschreitet.
- **Ablaufsteuerungen:** Aktivieren von nachfolgenden Logikschritten, wenn ein bestimmter Zahlenbereich verlassen wird.
- **Sicherheitsfunktionen:** Auslösen von Alarmen, wenn ein messbarer Parameter (z. B. Temperatur, Druck) einen maximal zulässigen Wert übersteigt.

## Vergleich mit ähnlichen Bausteinen

| Baustein          | Vergleichsoperation            | Datentypunterstützung              |
|-------------------|--------------------------------|------------------------------------|
| `AUDI_UDINT_GT`   | > (Größer als)                 | UDINT (32‑Bit, vorzeichenlos)      |
| `AUDI_UDINT_GE`   | >= (Größer oder gleich)        | UDINT                              |
| `AUDI_UDINT_EQ`   | = (Gleich)                     | UDINT                              |
| `AUDI_UDINT_LT`   | < (Kleiner als)                | UDINT                              |
| `F_GT` (direkt)   | > (Größer als)                 | UDINT (und weitere unterstützte Typen) |

Der Unterschied zu einer direkten Verwendung von `F_GT` liegt in der adapterbasierten Kapselung: `AUDI_UDINT_GT` erwartet den ersten Wert über einen Socket-Adapter, was eine modulare und wiederverwendbare Verknüpfung in Projektierungsframeworks ermöglicht.

## Fazit

Der Funktionsbaustein `AUDI_UDINT_GT` bietet eine standardisierte und typensichere Möglichkeit, einen „Größer‑als“‑Vergleich für vorzeichenlose 32‑Bit‑Ganzzahlen zu realisieren. Durch seine Adapter‑Schnittstelle lässt er sich nahtlos in IEC 61131‑3‑konforme Automatisierungsprojekte einbinden und ist besonders für Schwellwertvergleiche und Überwachungsfunktionen geeignet. Die interne Nutzung des normierten Bausteins `F_GT` garantiert dabei ein deterministisches und portables Verhalten.