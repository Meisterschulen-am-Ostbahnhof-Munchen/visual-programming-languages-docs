# FIELDBUS_UINT_TO_SIGNAL_SCALED


![FIELDBUS_UINT_TO_SIGNAL_SCALED](./FIELDBUS_UINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_UINT_TO_SIGNAL_SCALED** dient der Aufbereitung eines über einen Fieldbus empfangenen UINT-Wertes. Er prüft die Gültigkeit des Eingangssignals und skaliert dieses bei gültigem Wert mittels einer Multiplikationskonstante (SCALE) und eines additiven Offsets (OFFSET) zu einem REAL-Ausgang. Bei ungültigem Signal wird der Ausgang auf Null gesetzt und ein Validitäts-Flag auf FALSE gesetzt. Typische Anwendung ist die Umrechnung roher Feldbus-Daten in physikalische Größen mit gleichzeitiger Erkennung von Ausnahmezuständen wie Drahtbruch oder Sensorfehlern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (EInit): Initialisierungsanfrage. Mit diesem Ereignis werden die Parameter `SCALE` und `OFFSET` gesetzt.
- **REQ** (Event): Normale Ausführungsanfrage. Mit diesem Ereignis wird der aktuelle Wert `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **INITO** (EInit): Bestätigung der Initialisierung. Wird nach Verarbeitung des INIT-Ereignisses gesendet.
- **CNF** (Event): Bestätigung der Ausführung. Wird nach Verarbeitung des REQ-Ereignisses gesendet und transportiert die Ausgangsdaten `OUT` und `VALID`.

### **Daten-Eingänge**

| Name   | Typ   | Initialwert                     | Beschreibung                                              |
|--------|-------|----------------------------------|-----------------------------------------------------------|
| IN     | UINT  | WORD_TO_UINT(NOT_AVAILABLE_WM)   | Rohwert vom Feldbus, der skaliert werden soll.            |
| SCALE  | REAL  | REAL#1.0                        | Skalierungsfaktor (Multiplikation).                       |
| OFFSET | DINT  | DINT#0                          | Additiver Offset, der nach der Skalierung addiert wird.   |

### **Daten-Ausgänge**

| Name   | Typ   | Initialwert | Beschreibung                                              |
|--------|-------|-------------|-----------------------------------------------------------|
| OUT    | REAL  | REAL#0.0    | Skalierter Ausgangswert. Bei ungültigem Signal = 0.0.     |
| VALID  | BOOL  | FALSE       | Gültigkeitsflag: TRUE wenn das Eingangssignal gültig ist. |

### **Adapter**
Keine.

## Funktionsweise
Der FB besitzt zwei Betriebszustände, die durch die entsprechenden Ereignisse gesteuert werden.

- **INIT-Zustand**: Beim Empfang von `INIT` werden die Parameter `SCALE` und `OFFSET` übernommen (der Algorithmus ist leer, die Übergabe erfolgt implizit über die `With`-Verknüpfung). Anschließend wird das Ereignis `INITO` gesendet.
- **REQ-Zustand**: Beim Empfang von `REQ` wird folgender Algorithmus ausgeführt:
  1. Prüfung, ob der Eingangswert `IN` kleiner oder gleich einer fest definierten Gültigkeitsschwelle ist. Diese Schwelle ist durch die importierte Konstante `VALID_SIGNAL_W` gegeben (aus dem Namespace `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`).
  2. **Gültig (`IN <= VALID_SIGNAL_W`)**:
     - `OUT := UINT_TO_REAL(IN) * SCALE + DINT_TO_REAL(OFFSET)`
     - `VALID := TRUE`
  3. **Ungültig (`IN > VALID_SIGNAL_W`)**:
     - `OUT := 0.0`
     - `VALID := FALSE`
  4. Anschließend wird das Ereignis `CNF` mit den aktuellen Werten von `OUT` und `VALID` gesendet.

Die Gültigkeitsschwelle wird als Teil der importierten Bibliothek bereitgestellt und muss entsprechend der verwendeten Feldbus-Norm definiert sein. Der initiale Wert von `IN` ist `WORD_TO_UINT(NOT_AVAILABLE_WM)`, wodurch bei fehlender Datenübergabe standardmäßig ein ungültiges Signal erkannt wird.

## Technische Besonderheiten
- **Verwendung von importierten Konstanten**: Die Gültigkeitsprüfung erfolgt anhand von Konstanten aus dem Namespace `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. Diese müssen im Zielsystem korrekt definiert sein (z. B. `VALID_SIGNAL_W` als maximaler gültiger UINT-Wert, `NOT_AVAILABLE_WM` als Kennzeichnung für „nicht verfügbar“).
- **Leerer INIT-Algorithmus**: Das INIT-Ereignis dient lediglich der Parameterübergabe. Eine explizite Initialisierungslogik existiert nicht – die Werte von `SCALE` und `OFFSET` werden direkt aus den Daten-Eingängen übernommen. Daher können diese Parameter auch vor dem ersten INIT gesetzt sein (siehe Initialwerte).
- **Typerhaltung**: Der Eingang ist UINT, der Ausgang REAL. Die Skalierung erfolgt mit REAL-Arithmetik nach einer expliziten Typumwandlung.
- **Keine Zustandsautomaten-Logik**: Der FB ist als SimpleFB realisiert, das nur die zwei Zustände INIT und REQ kennt. Es gibt keine zeitlichen oder wiederholten Abläufe; jede Ausführung erfolgt streng ereignisgesteuert.

## Zustandsübersicht
Der FB besitzt genau zwei EC-States:

| Zustand | Eingang | Algorithmus | Ausgangsereignis |
|---------|---------|-------------|------------------|
| INIT    | INIT    | – (leer)    | INITO            |
| REQ     | REQ     | REQ         | CNF              |

Es existiert keine Zustandsschleife oder Verweildauer. Der FB startet nach der Initialisierung im Zustand INIT und kann danach beliebig oft durch REQ ausgeführt werden. Ein erneutes INIT setzt die Parameter zurück.

## Anwendungsszenarien
- **Skalierung von Analogwerten**: Ein Feldbus liefert einen rohen 16‑Bit‑Messwert (z. B. 0–4095). Mit `SCALE = 0.001` und `OFFSET = -5.0` wird daraus z. B. ein Druck in bar.
- **Erkennung von Fehlerwerten**: Viele Feldbus‑Protokolle definieren bestimmte Bit‑Muster für „Sensorfehler“ oder „Drahtbruch“. Der FB erkennt solche Werte, indem er sie über der Gültigkeitsschwelle (z. B. 0xFFFE oder 0x8000) einstuft und den Ausgang auf Null setzt.
- **Initialisierungssequenz**: Nach Systemstart kann ein INIT‑Aufruf die Skalierungsparameter aus einer Konfigurationsdatei laden. Danach werden in schneller Folge REQ‑Aufrufe zur zyklischen Messwertverarbeitung gesendet.

## Vergleich mit ähnlichen Bausteinen
- **FIELDBUS_UINT_TO_SIGNAL (ohne Skalierung)**: Ein einfacherer FB, der den UINT‑Wert direkt als REAL ausgibt und nur die Gültigkeitsprüfung durchführt. Die Skalierung muss extern erfolgen.
- **FIELDBUS_UINT_TO_SIGNAL_FILTERED**: Zusätzlich zur Skalierung wird ein Tiefpass oder Medianfilter angewendet – geeignet für verrauschte Signale.
- **FIELDBUS_INT_TO_SIGNAL_SCALED**: Analoger FB für vorzeichenbehaftete Eingänge (INT), mit entsprechender Anpassung der Gültigkeitslogik.

Der vorliegende FB zeichnet sich durch seine Einfachheit, klare Trennung von Skalierung und Gültigkeitserkennung sowie die Verwendung von importierten Konstanten aus, die eine flexible Anpassung an verschiedene Feldbus‑Normen erlaubt.

## Fazit
**FIELDBUS_UINT_TO_SIGNAL_SCALED** ist ein kompakter, ereignisgesteuerter Funktionsblock zur Umrechnung eines UINT‑Feldbussignals in einen skalierten REAL‑Wert. Durch die integrierte Gültigkeitsprüfung wird eine einfache Fehlererkennung ermöglicht. Der Baustein eignet sich besonders für Anwendungen, in denen rohe Busdaten mit geringem Aufwand in physikalische Größen gewandelt werden müssen und gleichzeitig die Signalqualität überwacht werden soll. Die klare Schnittstelle und die Verwendung von importierten Konstanten erleichtern die Wiederverwendung in verschiedenen Projektkontexten.