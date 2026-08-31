# ALI_ADD_2


![ALI_ADD_2](./ALI_ADD_2.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALI_ADD_2` ist ein generischer arithmetischer Baustein zur Durchführung einer Addition (ADD) auf Basis des Standards IEC 61131-3. Er ist als Standard-Arithmetikfunktion klassifiziert und dient dazu, zwei Eingangswerte über eine Adapter-Schnittstelle zu addieren und das Ergebnis auszugeben.

Durch die Verwendung von Adaptern ermöglicht dieser Baustein eine hochgradig modulare und übersichtliche Verdrahtung innerhalb der 4diac-IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Steuerung und Synchronisation erfolgt über die Adapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Steuerung und Synchronisation erfolgt über die Adapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

- **IN1 (Socket / Buchse)**: Eingangsadapter vom Typ `adapter::types::unidirectional::ALI`. Repräsentiert den ersten Summanden der Addition.
- **IN2 (Socket / Buchse)**: Eingangsadapter vom Typ `adapter::types::unidirectional::ALI`. Repräsentiert den zweiten Summanden der Addition.
- **OUT (Plug / Stecker)**: Ausgangsadapter vom Typ `adapter::types::unidirectional::ALI`. Liefert das mathematische Ergebnis der Addition (`IN1 + IN2`).

## Funktionsweise

Der Funktionsbaustein `ALI_ADD_2` führt eine klassische mathematische Addition aus. Sobald sich die Werte an den Eingangs-Adaptern `IN1` und/oder `IN2` ändern oder ein entsprechendes Übertragungsereignis über die Adapter getriggert wird, berechnet der Baustein die Summe:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

Das Ergebnis wird unmittelbar über den Ausgangsadapter `OUT` zur Verfügung gestellt. Da der Baustein als generischer Typ definiert ist (implementiert über die generische Klasse `GEN_ALI_ADD`), ist er nicht auf einen festen Datentyp fixiert, sondern kann sich an verschiedene kompatible numerische Datentypen anpassen.

## Technische Besonderheiten

- **Generische Implementierung**: Durch das Attribut `GenericClassName` mit dem Wert `'GEN_ALI_ADD'` kann der Baustein flexibel für unterschiedliche Datentypen (z. B. INT, REAL, LREAL) instanziiert werden.
- **Adapter-Kopplung**: Im Gegensatz zu traditionellen Funktionsbausteinen, die diskrete Pins für Daten und Events nutzen, bündelt dieser Baustein die Signale in unidirektionalen `ALI`-Adaptern. Dies reduziert das „Drahtgewitter“ im Funktionsplan erheblich.

## Zustandsübersicht

Der Funktionsbaustein ist zustandslos (kombinatorisches Verhalten). Er besitzt keine interne State Machine (ECC). Jede Änderung an den Eingängen führt direkt zur Aktualisierung des Ausgangs.

## Anwendungsszenarien

- **Signalverarbeitung**: Summierung von zwei Sensorwerten oder physikalischen Größen, die bereits über ein Adapter-System in der Anwendung verteilt werden.
- **Sollwert-Generierung**: Aufaddieren eines Basis-Sollwerts und eines Korrektur-Offsets.
- **Modularer Anlagenbau**: Einsatz in Systemen, bei denen Schnittstellen konsequent über Adapter abgebildet werden, um die Wiederverwendbarkeit und Lesbarkeit des Codes zu maximieren.

## Vergleich mit ähnlichen Bausteinen

Klassische `ADD`-Bausteine nach IEC 61131-3 verfügen meist über direkte Dateneingänge (`IN1`, `IN2`...) und Event-Pins (`REQ`, `CNF`). Der `ALI_ADD_2` unterscheidet sich dadurch, dass er diese Kanäle in Adaptern (`ALI`) kapselt. Dies führt zu einer besseren Kapselung und einer saubereren Strukturierung in komplexen 4diac-Applikationen, erfordert jedoch, dass die verbundenen Bausteine ebenfalls das `ALI`-Adapterprotokoll unterstützen.

- **[`ALI_ADD_2_UNGATED`](ALI_ADD_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALI_ADD_2` ist ein spezialisierter, hocheffizienter Additionsbaustein für adapterbasierte Architekturen in der 4diac-IDE. Er vereint die mathematische Standardfunktionalität der Addition mit den strukturellen Vorteilen moderner, adapterbasierter Kommunikationsparadigmen.
