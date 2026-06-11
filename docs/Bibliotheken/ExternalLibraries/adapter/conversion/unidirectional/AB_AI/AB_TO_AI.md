# AB_TO_AI


![AB_TO_AI](./AB_TO_AI.svg)

* * * * * * * * * *

## Einleitung

Der **AB_TO_AI** ist ein Composite-Funktionsblock zur Konvertierung eines **AB-Adapters (BYTE)** in einen **AI-Adapter (INT)**. Er ermöglicht die nahtlose Integration von BYTE-basierten Adapter-Schnittstellen in Systeme, die INT-Werte erwarten. Der Baustein nutzt intern den IEC‑61131‑Konvertierungsbaustein `F_BYTE_TO_INT`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Das Ereignis wird über den angeschlossenen Adapter **AB_IN** (Socket) bereitgestellt:

- **AB_IN.E1** – Ereignis, das die Konvertierung eines eingehenden BYTE-Wertes auslöst.

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Das Ausgangsereignis wird über den angeschlossenen Adapter **AI_OUT** (Plug) gesendet:

- **AI_OUT.E1** – Ereignis, das signalisiert, dass der konvertierte INT-Wert am Ausgang anliegt.

### **Daten-Eingänge**

Der FB besitzt keine direkten Daten-Eingänge. Der Eingangswert wird über den Adapter **AB_IN** (Socket) bereitgestellt:

- **AB_IN.D1** – BYTE-Wert (0…255), der in einen INT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**

Der FB besitzt keine direkten Daten-Ausgänge. Der Ausgangswert wird über den Adapter **AI_OUT** (Plug) bereitgestellt:

- **AI_OUT.D1** – INT-Wert, der das konvertierte BYTE darstellt.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| **AB_IN**   | `adapter::types::unidirectional::AB` | Socket (Eingang) | BYTE-adapter, der den zu konvertierenden Wert sowie das Start-Ereignis liefert. |
| **AI_OUT**  | `adapter::types::unidirectional::AI` | Plug (Ausgang)   | INT-adapter, der den konvertierten Wert und das Bestätigungs-Ereignis bereitstellt. |

## Funktionsweise

1. Ein eingehendes Ereignis auf **AB_IN.E1** triggert die Verarbeitung.
2. Der von **AB_IN.D1** gelieferte BYTE-Wert wird an den internen Baustein `F_BYTE_TO_INT` übergeben.
3. `F_BYTE_TO_INT` führt die Typkonvertierung durch und stellt den INT-Wert an seinem Ausgang `OUT` bereit.
4. Nach erfolgreicher Konvertierung wird das Ereignis **AI_OUT.E1** gesendet, und der INT-Wert liegt an **AI_OUT.D1** an.

Die Konvertierung erfolgt ohne Wertebereichsverlust: BYTE (0…255) wird direkt auf INT abgebildet.

## Technische Besonderheiten

- **Composite-FB:** Die Logik wird vollständig durch ein internes Netzwerk aus einem einzigen Konvertierungsbaustein realisiert.
- **Wiederverwendbar:** Der Baustein kann in Projekte eingebunden werden, die eine unidirektionale Adapter-Konvertierung benötigen.
- **Lizenz:** Der Baustein und die zugehörigen Materialien stehen unter der **Eclipse Public License 2.0**.
- **Paket:** `adapter::conversion::unidirectional`

## Zustandsübersicht

Der FB besitzt keinen eigenen internen Zustandsautomaten. Das Verhalten wird ausschließlich durch die auslösenden Ereignisse und den eingebetteten Baustein `F_BYTE_TO_INT` bestimmt. Es gibt keine persistenten Zustände.

## Anwendungsszenarien

- **Sensoranbindung:** Ein Sensor liefert Daten als BYTE über einen AB-Adapter; die nachgelagerte Verarbeitung erwartet INT-Werte über einen AI-Adapter.
- **Protokollanpassung:** In heterogenen Kommunikationspfaden müssen BYTE-kodierte Informationen in ein INT-basiertes Datenmodell überführt werden.
- **Adapter-Vermittlung:** Als Zwischenstück zwischen zwei Systemkomponenten, die unterschiedliche Adaptertypen verwenden.

## Vergleich mit ähnlichen Bausteinen

Es existieren häufig direkte Konvertierungsbausteine wie `F_BYTE_TO_INT` (IEC‑61131), die jedoch keine Adapter-Ereignissteuerung bieten. Der **AB_TO_AI** kapselt diese Konvertierung in einen vollständigen Adapter-zu-Adapter-Übergang mit Ereignisweitergabe. Ähnliche Bausteine für andere Datentypen (z. B. WORD zu DINT) könnten nach demselben Muster aufgebaut werden.

## Fazit

Der **AB_TO_AI** ist ein nützlicher und einfacher Funktionsblock, der die Lücke zwischen BYTE- und INT-basierten Adapter-Schnittstellen schließt. Er erleichtert die Integration von Komponenten mit unterschiedlichen Datentypschnittstellen in der 4diac-IDE und folgt bewährten Entwurfsmustern der IEC‑61499‑Norm. Dank seiner Composite-Struktur ist er leicht erweiterbar und kann als Vorlage für ähnliche Adapter-Konvertierungen dienen.