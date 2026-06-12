# AI_TO_AW


![AI_TO_AW](./AI_TO_AW.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AI_TO_AW** ist ein Composite-Baustein zur Umsetzung eines INT-Adapters (AI) in einen WORD-Adapter (AW). Er wird verwendet, um die Schnittstelle eines AI-Adapters (Typ INT) auf einen AW-Adapter (Typ WORD) zu konvertieren, damit die Daten und Ereignisse nahtlos zwischen unterschiedlichen Adapter-Typen weitergegeben werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **AI_IN.E1** (über Socket AI_IN): Ereigniseingang, der den Konvertierungsvorgang auslöst.

### **Ereignis-Ausgänge**

- **AW_OUT.E1** (über Plug AW_OUT): Ereignisausgang, der nach erfolgreicher Konvertierung aktiviert wird.

### **Daten-Eingänge**

- **AI_IN.D1** (über Socket AI_IN): Dateninput vom Typ **INT**, der den zu konvertierenden Wert bereitstellt.

### **Daten-Ausgänge**

- **AW_OUT.D1** (über Plug AW_OUT): Datenoutput vom Typ **WORD**, der das konvertierte Ergebnis liefert.

### **Adapter**

- **AI_IN** (Socket): Erwartet einen Adapter vom Typ `adapter::types::unidirectional::AI` (INT-basiert).
- **AW_OUT** (Plug): Stellt einen Adapter vom Typ `adapter::types::unidirectional::AW` (WORD-basiert) bereit.

## Funktionsweise

Der Baustein arbeitet als Kapselung eines einfachen Typkonvertierungs-Funktionsblocks (`F_INT_TO_WORD`) innerhalb einer Composite-Struktur. Der Ablauf ist wie folgt:

1. Ein Ereignis am Eingang **AI_IN.E1** wird an den internen Baustein `F_INT_TO_WORD` weitergeleitet.
2. Gleichzeitig wird der Wert von **AI_IN.D1** (INT) an den Eingang `IN` des Konvertierungsblocks übergeben.
3. Der interne Baustein führt die Konvertierung von INT nach WORD durch und legt das Ergebnis an seinem Ausgang `OUT` an.
4. Nach Abschluss der Konvertierung wird das Ereignis **AW_OUT.E1** gesendet und der konvertierte Wert (WORD) an **AW_OUT.D1** ausgegeben.

Somit wird die gesamte Adapter-Konvertierung durch ein einzelnes Ereignis gesteuert und die Daten werden automatisch umgesetzt.

## Technische Besonderheiten

- **Composite-Baustein**: Die Logik ist durch einen internen Subbaustein realisiert, was eine klare Trennung von Konvertierungslogik und Schnittstellenadaptern ermöglicht.
- **Wiederverwendbarkeit**: Der Baustein basiert auf dem Standardbaustein `iec61131::conversion::F_INT_TO_WORD` und kann daher in jeder IEC 61499-konformen Umgebung eingesetzt werden.
- **Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 (EPL-2.0) veröffentlicht.
- **Namensschema**: Der Baustein befindet sich im Paket `adapter::conversion::unidirectional`, was auf seine Funktion als unidirektionale Adapterkonvertierung hinweist.

## Zustandsübersicht

Da es sich um einen Composite-Baustein ohne eigene Zustandsmaschine handelt, wird das Zustandsverhalten vollständig durch den internen `F_INT_TO_WORD`-Baustein bestimmt. Im Wesentlichen gibt es zwei Zustände:

- **Idle**: Warten auf ein Ereignis am Eingang **AI_IN.E1**.
- **Converting**: Nach Empfang des Ereignisses wird die Konvertierung ausgeführt. Dabei sind keine Verzögerungen oder Wartezeiten vorgesehen – die Ausgabe erfolgt unmittelbar im selben Zyklus.

## Anwendungsszenarien

- **Systemintegration**: Wenn ein Subsystem oder eine Komponente Daten über einen INT-Adapter (AI) bereitstellt, aber die Zielkomponente einen WORD-Adapter (AW) erwartet.
- **Protokollanpassung**: In Anlagensteuerungen, bei denen Sensordaten als INT geliefert werden, aber die Kommunikationsschnittstelle auf WORD-Basis arbeitet.
- **Typkonvertierung in Adapterketten**: Der Baustein kann als Teil einer Adapterkette verwendet werden, um unterschiedliche Adapter-Typen zu verbinden, ohne dass manuelle Konvertierung notwendig ist.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Adapter-Konvertierungsbausteine wie z.B. `WORD_TO_INT` oder `REAL_TO_DINT` – jedoch fokussiert sich `AI_TO_AW` speziell auf die Adapter-Umwandlung von INT (AI) nach WORD (AW). Im Gegensatz zu einfachen Typkonvertierungsbausteinen (z.B. `F_INT_TO_WORD`) integriert dieser Baustein die Adapterschnittstellen direkt, sodass der Entwickler keine separate Adapter-Instanzierung vornehmen muss.

## Fazit

Der **AI_TO_AW**-Funktionsblock bietet eine einfache und robuste Lösung zur Konvertierung eines INT-Adapters in einen WORD-Adapter. Durch die Composite-Struktur bleibt die Logik überschaubar und erweiterbar. Der Baustein eignet sich besonders für Szenarien, in denen unterschiedliche Adapter-Typen in einer IEC 61499-Applikation harmonisiert werden müssen, und reduziert den Implementierungsaufwand für derartige Konvertierungen erheblich.