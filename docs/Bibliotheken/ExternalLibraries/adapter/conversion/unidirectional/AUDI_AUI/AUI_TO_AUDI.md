# AUI_TO_AUDI


![AUI_TO_AUDI](./AUI_TO_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_TO_AUDI** ist ein zusammengesetzter (Composite) Baustein, der einen AUI-Adapter (UINT) in einen AUDI-Adapter (UDINT) umwandelt. Er dient dazu, Daten und Ereignisse von einem Adaptertyp auf einen anderen zu übertragen, wobei die zugrundeliegenden Datentypen unterschiedlich sind (UINT → UDINT). Die Umwandlung erfolgt durch einfaches Durchreichen der Signale, ohne zusätzliche Logik.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine eigenen Ereignis-Eingänge: Der Baustein besitzt keine direkten Ereignis-Eingänge. Ereignisse werden über den angeschlossenen Socket-Adapter **AUI_IN** empfangen.

### **Ereignis-Ausgänge**
Keine eigenen Ereignis-Ausgänge: Der Baustein besitzt keine direkten Ereignis-Ausgänge. Ereignisse werden über den angeschlossenen Plug-Adapter **AUDI_OUT** gesendet.

### **Daten-Eingänge**
Keine eigenen Daten-Eingänge: Der Baustein besitzt keine direkten Daten-Eingänge. Daten werden über den angeschlossenen Socket-Adapter **AUI_IN** empfangen.

### **Daten-Ausgänge**
Keine eigenen Daten-Ausgänge: Der Baustein besitzt keine direkten Daten-Ausgänge. Daten werden über den angeschlossenen Plug-Adapter **AUDI_OUT** gesendet.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| AUI_IN | `adapter::types::unidirectional::AUI` | Socket (Eingang) | Empfängt UINT-Daten und zugehöriges Ereignis |
| AUDI_OUT | `adapter::types::unidirectional::AUDI` | Plug (Ausgang) | Sendet UDINT-Daten und zugehöriges Ereignis |

## Funktionsweise
Der Baustein verbindet intern die Schnittstellen des eingehenden AUI-Adapters mit denen des ausgehenden AUDI-Adapters:
- **Ereignisverbindung**: Das Ereignis `E1` des AUI-Adapters wird direkt an das Ereignis `E1` des AUDI-Adapters weitergeleitet.
- **Datenverbindung**: Der Datenwert `D1` des AUI-Adapters (Typ UINT) wird direkt an den Datenwert `D1` des AUDI-Adapters (Typ UDINT) übergeben. Dabei erfolgt eine implizite Typkonvertierung von UINT (16 Bit) nach UDINT (32 Bit).

Der Baustein führt keine eigene Logik oder Umrechnung durch; er fungiert als reine Durchreiche für Adapter mit unterschiedlichen Datentypen.

## Technische Besonderheiten
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional, d.h. Daten und Ereignisse fließen nur in eine Richtung (vom Socket zum Plug).
- **Composite-FB**: Der Baustein ist als Composite (zusammengesetzter FB) realisiert, der die Adapterverbindungen im FBNetwork abbildet.
- **Implizite Typkonvertierung**: Die Konvertierung von UINT zu UDINT erfolgt automatisch im Rahmen der Datenverbindung, basierend auf den IEC 61499-Datentypregeln.
- **Paketstruktur**: Der Baustein gehört zum Paket `adapter::conversion::unidirectional`.

## Zustandsübersicht
Der Baustein besitzt keine eigenen Zustände oder Zustandsautomaten. Das Verhalten ergibt sich ausschließlich aus der weiterleitenden Verbindung der Adapter-Schnittstellen.

## Anwendungsszenarien
- **Adapteranpassung**: Wenn in einem System ein AUI-Adapter (UINT) verwendet wird, aber ein AUDI-Adapter (UDINT) erwartet wird, kann dieser Baustein als Konverter zwischengeschaltet werden.
- **Signalweiterleitung**: Einsatz in hierarchischen Systemen, wo ein unidirektionaler Datenfluss von einem kleineren auf einen größeren Datentyp abgebildet werden muss.
- **Prototypische Integration**: Schnelle Kopplung von Komponenten mit unterschiedlichen Adaptertypen ohne zusätzliche Logik.

## Vergleich mit ähnlichen Bausteinen
- **AUI_TO_AUDI** führt eine reine Typkonvertierung durch, ohne weitere Verarbeitung.
- Ähnliche Bausteine wie `AUDI_TO_AUI` würden die umgekehrte Richtung (UDINT → UINT) abbilden, möglicherweise mit Datenüberlaufbehandlung.
- Andere Adapter-Konverter (z.B. `BOOL_TO_BYTE`) folgen dem gleichen Muster, unterscheiden sich jedoch in den verwendeten Datentypen und der Richtung.

## Fazit
Der **AUI_TO_AUDI**-Baustein ist ein einfacher, aber nützlicher Composite-FB zur Konvertierung eines UINT-basierten AUI-Adapters in einen UDINT-basierten AUDI-Adapter. Er eignet sich besonders für Situationen, in denen eine unidirektionale Signalweiterleitung mit impliziter Datentypanpassung erforderlich ist, ohne dass eine eigene Verarbeitungslogik notwendig wird. Dank seiner klaren Struktur ist er leicht in bestehende 4diac-Projekte integrierbar.