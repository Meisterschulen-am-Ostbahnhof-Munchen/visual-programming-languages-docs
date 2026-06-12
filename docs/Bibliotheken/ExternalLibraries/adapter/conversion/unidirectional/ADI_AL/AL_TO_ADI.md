# AL_TO_ADI


![AL_TO_ADI](./AL_TO_ADI.svg)

* * * * * * * * * *

## Einleitung

Der Composite-Funktionsblock `AL_TO_ADI` dient der standardisierten Umwandlung eines unidirektionalen LWORD-Adapters (`AL`) in einen unidirektionalen DINT-Adapter (`ADI`). Er ermöglicht die nahtlose Integration von Komponenten, die mit unterschiedlichen Datentypen in einer 4diac-Adapterlandschaft arbeiten.

## Schnittstellenstruktur

Da der FB als Composite realisiert ist, besitzt er keine eigenen Ereignis- oder Datenschnittstellen außerhalb der Adapter. Alle Ein- und Ausgaben erfolgen über die integrierten Adapter.

### **Ereignis-Eingänge**

Keine eigenen Ereignis-Eingänge. Das Ereignis zur Auslösung der Konvertierung wird über den Socket `AL_IN` (dort über das Ereignis `E1`) empfangen.

### **Ereignis-Ausgänge**

Keine eigenen Ereignis-Ausgänge. Das Bestätigungsereignis nach abgeschlossener Konvertierung wird über den Plug `ADI_OUT` (dort über das Ereignis `E1`) gesendet.

### **Daten-Eingänge**

Keine eigenen Daten-Eingänge. Der zu konvertierende LWORD-Wert wird über den Socket `AL_IN` (dort über das Datum `D1`) bereitgestellt.

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge. Der konvertierte DINT-Wert wird über den Plug `ADI_OUT` (dort über das Datum `D1`) ausgegeben.

### **Adapter**

- **AL_IN (Socket)**  
  Typ: `adapter::types::unidirectional::AL`  
  Aufnahme eines unidirektionalen LWORD-Adapters. Stellt das Auslöseereignis (`E1`) und den LWORD-Eingabewert (`D1`) bereit.

- **ADI_OUT (Plug)**  
  Typ: `adapter::types::unidirectional::ADI`  
  Bereitstellung eines unidirektionalen DINT-Adapters. Liefert das Bestätigungsereignis (`E1`) und den konvertierten DINT-Ausgabewert (`D1`).

## Funktionsweise

Der FB ist ein Composite-Baustein, der intern die IEC‑61131‑Standardfunktion `F_LWORD_TO_DINT` verwendet. Der Ablauf ist:

1. Ein Ereignis am Socket `AL_IN.E1` aktiviert den internen Konverter (`Convert.REQ`).
2. Der Konverter liest den LWORD-Wert von `AL_IN.D1`, wandelt ihn in einen DINT um und legt das Ergebnis an `Convert.OUT` an.
3. Nach erfolgreicher Konvertierung wird ein Ereignis von `Convert.CNF` an den Plug `ADI_OUT.E1` weitergeleitet.
4. Gleichzeitig wird der konvertierte DINT-Wert von `Convert.OUT` an `ADI_OUT.D1` übergeben.

Damit wird eine vollständige und zeitlich korrekte Umwandlung von einem LWORD-Adapter in einen DINT-Adapter realisiert.

## Technische Besonderheiten

- Der FB nutzt die IEC‑61131‑3 Funktion `F_LWORD_TO_DINT` – eine standardisierte und zuverlässige Typkonvertierung.
- Es handelt sich um eine reine **unidirektionale** Konvertierung: Daten und Ereignisse fließen nur vom Socket (`AL_IN`) zum Plug (`ADI_OUT`).
- Der FB ist als Composite modelliert, was eine klare Trennung von Konvertierungslogik und Adapterschnittstellen ermöglicht und die Wiederverwendung fördert.
- Bei der Umwandlung von LWORD (64 Bit) nach DINT (32 Bit) können Werte außerhalb des DINT-Bereichs zu Überläufen oder Begrenzungen führen – dies ist durch die IEC‑Funktion definiert.

## Zustandsübersicht

Der FB besitzt keine eigene Zustandsmaschine (ECC), da er als Composite ohne sequentielle Logik realisiert ist. Die Funktionalität wird rein durch die ereignisgesteuerte Verkettung der internen Elemente abgebildet. Ein einmaliger Konvertierungsdurchlauf erfolgt bei jedem eingehenden Ereignis am `AL_IN`.

## Anwendungsszenarien

- **Sensor-Anbindung:** Ein Sensor liefert LWORD-Daten (z. B. ein Zeitsignal oder eine große Zählvariable), die in einer Steuerung als DINT weiterverarbeitet werden müssen.
- **Systemintegration:** Brückenschlag zwischen Adapter-basierten Subsystemen, die unterschiedliche Datentypen verwenden – ohne dass der Anwender manuelle Konvertierungsbausteine einfügen muss.
- **Bibliothekserweiterung:** Einsatz als Teil einer Sammlung von unidirektionalen Typkonverter-Adaptern für verschiedene IEC‑61131‑3 Datentypen.

## Vergleich mit ähnlichen Bausteinen

Ähnliche Konverter-Adapter in 4diac existieren etwa für `AL_TO_UDINT`, `BYTE_TO_DINT` oder `LWORD_TO_REAL`. Der `AL_TO_ADI` ist speziell auf die Kombination LWORD → DINT ausgelegt. Im Gegensatz zu einfachen Funktionsbausteinen, die nur Daten konvertieren, bietet er die vollständige Adapter-Kopplung mit Ereignissteuerung. Gegenüber bidirektionalen Adaptern ist er auf die Datenflussrichtung von AL zu ADI festgelegt. Ein möglicher Datenverlust durch die Verkleinerung der Bitbreite (64 → 32 Bit) muss bei der Auswahl berücksichtigt werden.

## Fazit

Der Composite-FB `AL_TO_ADI` stellt eine saubere und standardisierte Lösung zur Konvertierung eines unidirektionalen LWORD-Adapters auf einen DINT-Adapter dar. Durch die Nutzung der IEC‑61131‑Funktion und die Einbettung in das 4diac-Adapterkonzept erleichtert er die Integration heterogener Systemkomponenten erheblich. Er ist wartungsfreundlich, wiederverwendbar und folgt bewährten Entwurfsmustern der industriellen Automatisierung.