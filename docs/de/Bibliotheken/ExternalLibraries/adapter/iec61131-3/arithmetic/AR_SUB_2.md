# AR_SUB_2




![AR_SUB_2](./AR_SUB_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AR_SUB_2` dient zur Durchführung einer arithmetischen Subtraktion (Subtrahend von Minuend). Es handelt sich um einen generischen Funktionsbaustein (`GEN_AR_SUB`), der für die Berechnung keine klassischen diskreten Ein- und Ausgänge nutzt, sondern vollständig auf einer adapterbasierten Schnittstellenstruktur aufbaut. Die Werte und die dazugehörige Steuerungslogik werden über unidirektionale Adapter vom Typ `AR` übertragen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Dieser Funktionsbaustein besitzt keine direkten, diskreten Ereignis-Eingänge. Die Ereignissteuerung wird über die angeschlossenen Adapter realisiert.

### **Ereignis-Ausgänge**

Dieser Funktionsbaustein besitzt keine direkten, diskreten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge vorhanden. Die Eingangsdaten werden über die Adapter-Eingänge empfangen.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Das Berechnungsergebnis wird über den Adapter-Ausgang bereitgestellt.

### **Adapter**

- **Sockets (Eingangs-Adapter):**
  - **IN1** (Typ: `adapter::types::unidirectional::AR`): Erster Eingang der Subtraktion (Minuend).
  - **IN2** (Typ: `adapter::types::unidirectional::AR`): Zweiter Eingang der Subtraktion (Subtrahend).

- **Plugs (Ausgangs-Adapter):**
  - **OUT** (Typ: `adapter::types::unidirectional::AR`): Ausgang für das Ergebnis der Subtraktion ($OUT = IN1 - IN2$).

## Funktionsweise

Der Baustein subtrahiert den Wert, der am Adapter `IN2` anliegt, von dem Wert des Adapters `IN1`. Das Ergebnis dieser arithmetischen Operation wird an den Ausgangs-Plug `OUT` übergeben.

Da es sich um unidirektionale Adapter handelt, triggern eingehende Ereignisse auf den Sockets `IN1` oder `IN2` die interne Berechnung. Nach erfolgter Subtraktion wird das entsprechende Aktualisierungsereignis über den Plug `OUT` an die nachfolgenden Bausteine signalisiert.

## Technische Besonderheiten

- **Generischer Typ (`GEN_AR_SUB`)**: Der Baustein ist generisch implementiert. Dies ermöglicht eine flexible Handhabung verschiedener numerischer Datentypen, sofern diese innerhalb der Definition der `AR`-Adapterstruktur zulässig sind.
- **Kapselung**: Durch die Verwendung von Adaptern werden Daten- und Event-Leitungen gebündelt. Dies reduziert die Anzahl der sichtbaren Verbindungslinien im Funktionsplan der 4diac-IDE erheblich.

## Zustandsübersicht

Der Baustein besitzt keine komplexe interne Zustandsmaschine (kein Execution Control Chart - ECC), da es sich um einen rein datenflussorientierten Berechnungsbaustein handelt. Die Verarbeitung verhält sich wie folgt:

1. **Warten auf Event**: Der Baustein wartet auf ein Aktualisierungsereignis an `IN1` oder `IN2`.
2. **Berechnung**: Bei Erhalt eines Events werden die aktuellen Werte aus `IN1` und `IN2` gelesen und voneinander abgezogen.
3. **Ausgabe**: Das Ergebnis wird in `OUT` geschrieben und ein Ausgangs-Event am Plug `OUT` ausgelöst.

## Anwendungsszenarien

- **Soll-Istwert-Vergleich**: Berechnung der Regelabweichung ($e = w - x$) in Regelungskreisen, bei denen die Signale bereits als Adapterstrukturen vorliegen.
- **Offset-Kompensation**: Subtraktion eines Nullpunktfehlers oder Offsets von einem analogen Sensorwert.
- **Strukturierte Signalverarbeitung**: Mathematische Berechnungen in komplexen, verteilten Steuerungssystemen zur Wahrung einer übersichtlichen Software-Architektur.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Subtraktionsbaustein `SUB` (aus den klassischen IEC 61131-3 Elementen), welcher mit diskreten Eingängen wie `IN1` und `IN2` sowie expliziten Events (`REQ` / `CNF`) arbeitet, bietet `AR_SUB_2` durch die Nutzung von Adaptern eine wesentlich höhere Abstraktion. Dies spart Entwicklungszeit bei der Kopplung komplexer Signalglieder, erfordert jedoch eine konsistente Verwendung von Adaptern im gesamten Projekt.

- **[`AR_SUB_2_UNGATED`](AR_SUB_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AR_SUB_2` ist ein spezialisierter und moderner Rechenbaustein für die 4diac-IDE. Er eignet sich hervorragend für serviceorientierte Architekturen innerhalb der IEC 61499, bei denen Übersichtlichkeit und standardisierte Adapter-Schnittstellen im Vordergrund stehen.
