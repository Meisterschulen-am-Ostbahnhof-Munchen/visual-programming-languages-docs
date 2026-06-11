# AUI_TO_AULI


![AUI_TO_AULI](./AUI_TO_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUI_TO_AULI` ist ein Composite-Baustein zur Umwandlung eines unidirektionalen AUI-Adapters (Datentyp `UINT`) in einen unidirektionalen AULI-Adapters (Datentyp `ULINT`). Er dient als einfacher Typkonverter zwischen den beiden Adapter-Schnittstellen, wobei sowohl das Ereignissignal als auch der Datenwert transparent weitergereicht werden. Der Baustein ermöglicht eine nahtlose Integration von Komponenten, die unterschiedliche Adressierungsbreiten verwenden.

## Schnittstellenstruktur

Der Baustein besitzt keine eigenständigen Ereignis- oder Daten-Ein-/Ausgänge, sondern nutzt ausschließlich Adapter-Schnittstellen. Die nachfolgenden Abschnitte beschreiben die Signale, die über die verwendeten Adapter nach außen geführt werden.

### **Ereignis-Eingänge**

| Signal | Beschreibung |
|--------|--------------|
| (E1 über AUI_IN) | Ereigniseingang des angeschlossenen AUI-Adapters (Socket). Ein eingehendes Ereignis wird direkt an den AULI-Adapter weitergeleitet. |

### **Ereignis-Ausgänge**

| Signal | Beschreibung |
|--------|--------------|
| (E1 über AULI_OUT) | Ereignisausgang des angeschlossenen AULI-Adapters (Plug). Das vom AUI-Adapter empfangene Ereignis wird hier ausgegeben. |

### **Daten-Eingänge**

| Signal | Datentyp | Beschreibung |
|--------|----------|--------------|
| (D1 über AUI_IN) | `UINT` (16 Bit) | Dateneingang des AUI-Adapters. Der eingehende Wert wird als 16-Bit-Ganzzahl interpretiert. |

### **Daten-Ausgänge**

| Signal | Datentyp | Beschreibung |
|--------|----------|--------------|
| (D1 über AULI_OUT) | `ULINT` (64 Bit) | Datenausgang des AULI-Adapters. Der vom AUI-Adapter übernommene Wert wird als 64-Bit-Ganzzahl ohne Vorzeichen ausgegeben. |

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AUI` | `AUI_IN` | Socket (Eingang) | Adapter für den Empfang von Ereignissen und Daten im Format `UINT`. |
| `adapter::types::unidirectional::AULI` | `AULI_OUT` | Plug (Ausgang) | Adapter für das Senden von Ereignissen und Daten im Format `ULINT`. |

## Funktionsweise

Der Baustein leitet eingehende Ereignisse und Daten vom Eingangsadapter `AUI_IN` unverändert zum Ausgangsadapter `AULI_OUT` weiter. Dabei wird der Datentyp `UINT` implizit nach `ULINT` konvertiert (Wert bleibt erhalten, lediglich die Bitbreite wird von 16 auf 64 Bit erweitert). Die Verbindung erfolgt im FBNetzwerk des Composite-Bausteins durch direkte Verdrahtung der jeweiligen Ereignis- und Datenkanäle (`E1` und `D1`). Es findet keine zusätzliche Logik oder Zustandsspeicherung statt.

## Technische Besonderheiten

- **Implizite Typkonvertierung:** Die Umwandlung von `UINT` nach `ULINT` erfolgt automatisch durch die 4diac-IDE und erfordert keinen expliziten Konvertierungsbaustein. Der Wertebereich von 0 bis 65535 (UINT) wird auf den entsprechenden ULINT-Bereich abgebildet.
- **Durchreicheverhalten:** Ereignisse und Daten werden ohne Verzögerung oder Pufferung übertragen. Das Ausgangsereignis tritt zeitgleich mit dem Eingangsereignis auf.
- **Unidirektionale Adapter:** Der Baustein unterstützt nur eine Datenflussrichtung (vom AUI-Eingang zum AULI-Ausgang). Eine Rückwärtskommunikation ist nicht vorgesehen.

## Zustandsübersicht

Der Baustein besitzt keine eigenen Zustände, da er ausschließlich aus direkten Verbindungen besteht. Das Verhalten ist rein kombinatorisch: Ein Ereignis am Eingang erzeugt sofort ein Ereignis am Ausgang, und der Datenwert wird kontinuierlich übertragen.

## Anwendungsszenarien

- **Systeme mit gemischter Adressierungsbreite:** Wenn ein Sensor oder eine Komponente Daten im Format `UINT` (z. B. 16-Bit-Zählerwert) liefert, aber eine nachgelagerte Steuerung oder ein Bus-Interface nur `ULINT` (64-Bit) akzeptiert.
- **Adapter-Kopplung:** Einsatz als Zwischenstück zwischen zwei unterschiedlichen Adaptertypen in einer modularen Steuerungsarchitektur, die auf dem 61499-Standard basiert.
- **Prototypenentwicklung:** Schnelle Integration von Bibliotheksbausteinen, die unterschiedliche Adapterschnittstellen verwenden, ohne manuelle Konvertierung.

## Vergleich mit ähnlichen Bausteinen

- **INT_TO_LINT / UINT_TO_ULINT (direkte Datenkonverter):** Diese Bausteine arbeiten auf reinen Datenebenen ohne Ereignisweiterleitung und erfordern separate Ereignisverarbeitung. `AUI_TO_AULI` kombiniert Ereignis- und Datenkonvertierung in einem Adapter-Interface.
- **Adapter-Adapter-Connector:** Andere Composite-Bausteine, die zwei gleichartige Adapter verbinden (z. B. AUI_TO_AUI) – sie unterscheiden sich lediglich durch die fehlende Typumwandlung.
- **Explizite Konvertierungsbausteine mit mehreren Kanälen:** Komplexere Bausteine, die mehrere Signale gleichzeitig konvertieren, sind für einfache Punkt-zu-Punkt-Verbindungen wie diese überdimensioniert.

## Fazit

`AUI_TO_AULI` ist ein schlanker, spezialisierter Composite-Baustein zur Umwandlung eines AUI-Adapters in einen AULI-Adapter. Er vereinfacht die Typanpassung zwischen 16-Bit- und 64-Bit-Adressierung in IEC 61499-Systemen, indem er sowohl Ereignis- als auch Datenpfade automatisch konvertiert und weiterleitet. Dank der impliziten Typkonvertierung von `UINT` nach `ULINT` entfällt die manuelle Implementierung von Konvertierungslogik, was den Entwurf modularer und wiederverwendbarer Steuerungsanwendungen erleichtert.