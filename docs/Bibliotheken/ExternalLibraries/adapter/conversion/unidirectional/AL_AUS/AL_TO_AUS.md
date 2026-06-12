# AL_TO_AUS


![AL_TO_AUS](./AL_TO_AUS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein AL_TO_AUS dient der Umwandlung eines AL-Adapters (LWORD) in einen AUS-Adapter (USINT). Er ist als Composite-FB realisiert und kapselt die Konvertierungslogik mithilfe des Bausteins F_LWORD_TO_USINT. Die Ein- und Ausgabe erfolgen über unidirektionale Adapter-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Stattdessen werden Ereignisse über den Adapter-Socket `AL_IN` empfangen. Der Socket stellt den Ereignis-Eingang `E1` bereit.

- **`AL_IN.E1`** (Ereignis): Auslöser für die Datenkonvertierung.

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Ereignisse werden über den Adapter-Plug `AUS_OUT` gesendet. Der Plug stellt den Ereignis-Ausgang `E1` bereit.

- **`AUS_OUT.E1`** (Ereignis): Signalisiert den Abschluss der Konvertierung und das Vorliegen des Ausgangswerts.

### **Daten-Eingänge**

Die Daten werden über den Adapter-Socket `AL_IN` bereitgestellt.

- **`AL_IN.D1`** (LWORD): Der einzulesende LWORD-Wert, der in einen USINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**

Die konvertierten Daten werden über den Adapter-Plug `AUS_OUT` ausgegeben.

- **`AUS_OUT.D1`** (USINT): Der konvertierte USINT-Wert.

### **Adapter**

- **Socket `AL_IN`** (Typ: `adapter::types::unidirectional::AL`): Unidirektionaler LWORD-Eingangsadapter.
- **Plug `AUS_OUT`** (Typ: `adapter::types::unidirectional::AUS`): Unidirektionaler USINT-Ausgangsadapter.

## Funktionsweise

Der Baustein wartet auf ein Ereignis am Eingangsadapter `AL_IN.E1`. Sobald dieses eintrifft, wird der an `AL_IN.D1` anliegende LWORD-Wert ausgelesen und an den internen Konvertierungsbaustein `F_LWORD_TO_USINT` übergeben. Dieser führt die Konvertierung in einen USINT-Wert durch. Nach erfolgreicher Konvertierung wird der Ergebniswert an den Ausgangsadapter `AUS_OUT.D1` weitergeleitet und gleichzeitig ein Ereignis an `AUS_OUT.E1` gesendet.

Die Verbindungen im Inneren sind:

- Vom Ereigniseingang des Sockets zum `REQ`-Eingang des Konverters.
- Vom `CNF`-Ausgang des Konverters zum Ereignisausgang des Plugs.
- Vom Dateneingang des Sockets zum `IN`-Eingang des Konverters.
- Vom `OUT`-Ausgang des Konverters zum Datenausgang des Plugs.

## Technische Besonderheiten

- Der Baustein ist als Composite-FB realisiert, der auf die IEC-61131-Konvertierungsfunktion `F_LWORD_TO_USINT` zurückgreift.
- Die Adapter sind unidirektional ausgelegt, d.h. die Daten- und Ereignisflüsse verlaufen nur in eine Richtung.
- Der Konvertierungsbaustein stammt aus der Bibliothek `iec61131::conversion`.
- Durch die Kapselung in einem Composite-FB wird die Wiederverwendbarkeit und Austauschbarkeit der Konvertierungslogik erhöht.

## Zustandsübersicht

Der Baustein hat keinen eigenen definierten Zustandsautomaten. Die interne Logik besteht aus einem einzigen Konvertierungsbaustein und festen Verbindungen. Der Ablauf ist rein ereignisgesteuert:

1. Warten auf Ereignis am Eingang (`AL_IN.E1`).
2. Konvertierung durchführen.
3. Ergebnis ausgeben und Ereignis am Ausgang (`AUS_OUT.E1`) setzen.

## Anwendungsszenarien

- Anbindung von Sensoren oder Aktoren, die einen LWORD-Wert liefern, an ein System, das USINT erwartet.
- Protokollumsetzung in Automatisierungsanlagen, bei denen unterschiedliche Datentypen zwischen Adaptern konvertiert werden müssen.
- Einbettung in größere Composite-FBs, die mehrere Konvertierungsschritte kombinieren.

## Vergleich mit ähnlichen Bausteinen

- **F_LWORD_TO_UINT**: Wandelt LWORD in UINT (16 Bit) um.
- **F_LWORD_TO_DWORD**: Wandelt LWORD in DWORD (32 Bit) um.
- **F_LWORD_TO_BYTE**: Wandelt LWORD in BYTE (8 Bit) um, liefert aber ein signed/unsigned? USINT ist unsigned 8 Bit.
- Der vorliegende Baustein füllt die Lücke für die direkte Umwandlung in den Datentyp USINT im Adapter-Kontext.

## Fazit

Der Composite-FB AL_TO_AUS bietet eine einfache und saubere Lösung zur Umwandlung eines LWORD-Adapter-Eingangs in einen USINT-Adapter-Ausgang. Durch die Verwendung standardisierter Konvertierungsbausteine und die Kapselung in einem eigenen FB-Typ wird die Wartbarkeit und Lesbarkeit des Gesamtsystems verbessert. Er eignet sich besonders für Szenarien, in denen unidirektionale Adapter-Schnittstellen mit unterschiedlichen Datentypen verbunden werden müssen.