# AD_TO_AR

![AD_TO_AR](./AD_TO_AR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AD_TO_AR** ist ein Composite-Baustein, der einen DWORD-Wert aus einem unidirektionalen AD-Adapter (Socket) auf einen REAL-Wert an einem AR-Adapter (Plug) abbildet.

> **⚠️ Achtung — keine numerische Wertumwandlung:** `AD_TO_AR` nutzt intern `F_DWORD_TO_REAL`, was im FORTE-Kern für Bit-String-Quelltypen (BYTE/WORD/DWORD/LWORD) eine reine IEEE754-**Bit-Reinterpretation** ist, keine Zahlenwert-Umwandlung. Ein roher Zähler- oder Analogwert wie `DWORD#2048` wird dadurch **nicht** zu `REAL#2048.0`, sondern zu einer bedeutungslosen Zahl nahe Null. Für eine echte numerische DWORD→REAL-Umwandlung siehe [`AD_TO_AR_NUM`](./AD_TO_AR_NUM.md) (zweistufig über UDINT). `AD_TO_AR` ist nur dann korrekt, wenn `AD_IN` bereits ein Bitmuster ist, das als REAL interpretiert werden soll (z. B. das Ergebnis von `F_REAL_TO_DWORD`).

## Schnittstellenstruktur

Der Baustein besitzt keine direkten (einzelnen) Ereignis- oder Daten-Ein-/Ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter-Schnittstellen:

### **Ereignis-Eingänge**

- *Keine direkten Ereignis-Eingänge* – die Ereignissteuerung erfolgt über den eingehenden Adapter.

### **Ereignis-Ausgänge**

- *Keine direkten Ereignis-Ausgänge* – die Ereignisausgabe erfolgt über den ausgehenden Adapter.

### **Daten-Eingänge**

- *Keine direkten Daten-Eingänge* – die Datenaufnahme erfolgt über den eingehenden Adapter.

### **Daten-Ausgänge**

- *Keine direkten Daten-Ausgänge* – die Datenausgabe erfolgt über den ausgehenden Adapter.

### **Adapter**

| Name   | Typ                                       | Richtung | Beschreibung                                                                 |
|--------|--------------------------------------------|----------|-----------------------------------------------------------------------------|
| AD_IN  | `adapter::types::unidirectional::AD`      | Socket   | Empfängt ein Ereignis (E1) und einen DWORD-Wert (D1) zur Konvertierung.    |
| AR_OUT | `adapter::types::unidirectional::AR`      | Plug     | Sendet ein Ereignis (E1) mit dem konvertierten REAL-Wert (D1) aus.         |

## Funktionsweise

Der Baustein arbeitet als ereignisgesteuerte Pipeline:

1. Ein eingehendes Ereignis am Socket **AD_IN.E1** triggert die Konvertierung.
2. Der Datenwert **AD_IN.D1** (DWORD) wird an den internen Funktionsblock `F_DWORD_TO_REAL` übergeben.
3. Nach erfolgreicher Konvertierung signalisiert der interne Baustein ein Ausgangsereignis (**CNF**).
4. Dieses Ereignis wird an den Plug **AR_OUT.E1** weitergeleitet und zeitgleich der konvertierte REAL-Wert über **AR_OUT.D1** ausgegeben.

`F_DWORD_TO_REAL` reinterpretiert dabei lediglich das 32-Bit-Muster des DWORD als IEEE754-`REAL` (Bit-Kopie), es findet **keine** Zahlenwert-Konvertierung statt.

## Technische Besonderheiten

- **⚠️ Bit-Reinterpretation statt Zahlenwert-Umwandlung**: Siehe Warnhinweis in der Einleitung. Betroffen sind alle Bit-String-Quelltypen (`AB`/BYTE, `AW`/WORD, `AD`/DWORD, `AL`/LWORD) beim Umwandeln in `AR`/REAL oder `ALR`/LREAL — der einzige weitere Fall in dieser Bibliothek ist [`AL_TO_ALR`](../AL_ALR/AL_TO_ALR.md) (LWORD→LREAL).
- **Composite-Baustein**: Die Konvertierungslogik ist vollständig in einem internen Netzwerk aus einem einzigen Funktionsblock realisiert.
- **Typkonvertierung über Adapter**: Der Baustein ermöglicht die Anbindung von Komponenten, die ausschließlich über Adapter-Schnittstellen kommunizieren, ohne dass zusätzliche manuelle Konvertierungen notwendig sind.
- **Standardkonformität**: Verwendet die IEC-61131-Bibliotheksfunktion `F_DWORD_TO_REAL`, dadurch portabel und gut getestet.
- **Unidirektionale Adapter**: Sowohl Eingangs- als auch Ausgangsadapter sind als unidirektional ausgeführt, d.h. es findet nur eine Datenflussrichtung statt.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen Zustandsautomaten. Die Verarbeitung erfolgt streng kausal: Ein Ereignis am Eingang löst sofort die Konvertierung und Ausgabe aus. Es gibt keine Verzögerungen oder Zwischenzustände.

## Anwendungsszenarien

- **Bitmuster-Weitergabe**: `AD_IN` liefert bereits ein Bitmuster, das als REAL interpretiert werden soll (z. B. das Ergebnis eines `F_REAL_TO_DWORD` an anderer Stelle im Netzwerk, oder deserialisierte Float-Rohdaten aus einem Feldbus/Protokoll).
- **NICHT geeignet** für rohe Zähler-, Analog- oder sonstige Ganzzahlwerte, die als derselbe Zahlenwert in REAL vorliegen sollen — dafür [`AD_TO_AR_NUM`](./AD_TO_AR_NUM.md) verwenden.

## Vergleich mit ähnlichen Bausteinen

- **`AD_TO_AR_NUM`** (numerisch, DWORD→UDINT→REAL): der sichere Ersatz, wenn tatsächlich ein Zahlenwert gemeint ist.
- **`AI_TO_AR`/`ADI_TO_AR`/`AUDI_TO_AR`** (INT/DINT/UDINT→REAL): diese sind bereits numerisch korrekt, da ihre Quelltypen `ANY_INT` (nicht `ANY_BIT`) sind — kein Trap.
- **`AL_TO_ALR`** (LWORD→LREAL): dieselbe Bit-Reinterpretations-Falle, nur mit den 64-Bit-Pendants.

## Fazit

Der **AD_TO_AR**-Baustein bietet eine kompakte Lösung, um ein DWORD-Bitmuster über Adapter-Schnittstellen als REAL bereitzustellen — **aber keine numerische Wertumwandlung**. Für rohe Zähler- oder Analogwerte, die als derselbe Zahlenwert in REAL vorliegen sollen, [`AD_TO_AR_NUM`](./AD_TO_AR_NUM.md) verwenden.

---

### 📖 Hintergrund

* [Numerisch vs. bitweise: Die Konvertierungs-Falle in FORTE](../Numerisch_vs_Bitweise.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
