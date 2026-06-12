# FIELDBUS_USINT_TO_SIGNAL


![FIELDBUS_USINT_TO_SIGNAL](./FIELDBUS_USINT_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock FIELDBUS_USINT_TO_SIGNAL dient der Aufbereitung eines USINT-Signals aus einem Feldbus. Er prüft, ob der eingehende Wert einen gültigen Signalbereich darstellt und spiegelt diesen gegebenenfalls auf den Ausgang. Andernfalls wird der Ausgang auf einen definierten Nullwert gesetzt und das Gültigkeitssignal zurückgesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mit |
|----------|--------------|-----|
| REQ      | Normaler Ausführungsauftrag | IN |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mit |
|----------|--------------|-----|
| CNF      | Ausführungsbestätigung | OUT, VALID |

### **Daten-Eingänge**

| Name | Typ   | Kommentar | Initialwert |
|------|-------|-----------|-------------|
| IN   | USINT | Eingangswert vom Feldbus | BYTE_TO_USINT(NOT_AVAILABLE_B) |

### **Daten-Ausgänge**

| Name  | Typ   | Kommentar | Initialwert |
|-------|-------|-----------|-------------|
| OUT   | USINT | Gefilterter Ausgangswert | 16#00 |
| VALID | BOOL  | TRUE, wenn Signal gültig | FALSE |

### **Adapter**

Keine.

## Funktionsweise

Beim Eintreffen eines REQ-Ereignisses wird der Algorithmus ausgeführt. Der eingehende Wert IN wird mit dem konstanten Grenzwert `VALID_SIGNAL_B` (als USINT interpretiert) verglichen. Wenn `IN <= BYTE_TO_USINT(VALID_SIGNAL_B)` erfüllt ist, wird der Eingangswert direkt auf den Ausgang OUT übernommen und das Gültigkeitssignal VALID auf TRUE gesetzt. Andernfalls wird OUT auf 0 und VALID auf FALSE gesetzt. Das Ergebnis wird mit dem CNF-Ereignis quittiert.

Die beiden Konstanten `NOT_AVAILABLE_B` und `VALID_SIGNAL_B` sind Teil des Pakets `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` und definieren einen Referenzwert für „nicht verfügbar“ bzw. den oberen Grenzwert für gültige Signale.

## Technische Besonderheiten

- Der Initialwert des Eingangs IN ist auf `BYTE_TO_USINT(NOT_AVAILABLE_B)` gesetzt, sodass bei erstmaligem Aufruf ohne gültigen Wert sofort ein ungültiger Zustand signalisiert wird.
- Der Vergleich verwendet die Funktion `BYTE_TO_USINT`, um den Byte-Wert der Konstanten in den Datentyp USINT zu konvertieren.
- Der Baustein ist unter der Eclipse Public License 2.0 lizenziert.

## Zustandsübersicht

Der Funktionsblock besitzt einen einzigen Zustand `REQ`. Sobald ein REQ-Ereignis eintrifft, wird der Algorithmus ausgeführt und unmittelbar das CNF-Ereignis gesendet. Es gibt keine internen Zustandsänderungen oder Verzögerungen.

## Anwendungsszenarien

- **Feldbus-Signalaufbereitung**: Ein Sensor liefert Werte im Bereich 0–127 als gültige Signale. Der Grenzwert VALID_SIGNAL_B wird auf 127 gesetzt. Werte darüber (z. B. 255 als Fehlercode) werden als ungültig erkannt.
- **Initialisierung**: Beim Systemstart ist der Eingang auf den „nicht verfügbar“-Wert vorbesetzt, sodass bis zum ersten gültigen Empfang der Ausgang auf 0 und VALID auf FALSE bleibt.
- **Fehlererkennung**: Durch Anpassung des Grenzwerts können beliebige zulässige Wertebereiche definiert werden.

## Vergleich mit ähnlichen Bausteinen

Ähnliche Bausteine wie `FIELDBUS_BYTE_TO_SIGNAL` oder `FIELDBUS_SINT_TO_SIGNAL` arbeiten nach dem gleichen Prinzip, jedoch mit anderen Datentypen. Dieser Baustein spezialisiert sich auf USINT. Ein einfacher „Mirror“-Baustein ohne Gültigkeitsprüfung würde den Wert ungefiltert durchreichen.

## Fazit

Der `FIELDBUS_USINT_TO_SIGNAL`-Baustein bietet eine einfache und zuverlässige Möglichkeit, USINT-Feldbussignale auf ihre Gültigkeit zu prüfen und nur gültige Werte an die nachfolgende Verarbeitung weiterzugeben. Durch die Verwendung konfigurierbarer Grenzwerte (über die Paketkonstanten) ist er flexibel einsetzbar.