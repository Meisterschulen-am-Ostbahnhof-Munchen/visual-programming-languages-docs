# AUI_TO_AB


![AUI_TO_AB](./AUI_TO_AB.svg)

*Kein Bild verfügbar*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUI_TO_AB** ist ein Composite-Baustein, der eine AUI-Schnittstelle (UINT) in eine AB-Schnittstelle (BYTE) umwandelt. Er kapselt die Konvertierung mittels des internen IEC 61131-Bausteins `F_UINT_TO_BYTE` und stellt über Adapter einen einheitlichen unidirektionalen Datenfluss bereit. Entwickelt wurde dieser Baustein zur Verwendung in Automatisierungssystemen, die unterschiedliche Datentypen zwischen Adaptern übertragen müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Beschreibung | Datentyp |
|------|--------------|----------|
| `AUI_IN.E1` | Ereignis über den AUI-Adapter (Socket), das die Konvertierung auslöst. | Ereignis |

### **Ereignis-Ausgänge**

| Name | Beschreibung | Datentyp |
|------|--------------|----------|
| `AB_OUT.E1` | Ereignis über den AB-Adapter (Plug), das nach erfolgreicher Konvertierung gesendet wird. | Ereignis |

### **Daten-Eingänge**

| Name | Beschreibung | Datentyp |
|------|--------------|----------|
| `AUI_IN.D1` | UINT-Wert, der über den AUI-Adapter empfangen und konvertiert wird. | UINT |

### **Daten-Ausgänge**

| Name | Beschreibung | Datentyp |
|------|--------------|----------|
| `AB_OUT.D1` | Konvertierter BYTE-Wert, der über den AB-Adapter ausgegeben wird. | BYTE |

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::AUI` | `AUI_IN` | Socket | UINT-Adapter-Eingang |
| `adapter::types::unidirectional::AB` | `AB_OUT` | Plug | BYTE-Adapter-Ausgang |

## Funktionsweise

Der Baustein arbeitet als reiner Signalwandler:

1. Ein eingehendes Ereignis am **AUI_IN.E1** wird an den internen Funktionsblock `Convert` (Typ `F_UINT_TO_BYTE`) weitergeleitet.
2. Gleichzeitig wird der Datenwert **AUI_IN.D1** an den Eingang `Convert.IN` übergeben.
3. Der Konverter wandelt den UINT-Wert in einen BYTE-Wert um (Datenkürzung auf niederwertiges Byte).
4. Nach Abschluss wird das Ereignis **AB_OUT.E1** ausgelöst und der konvertierte Wert über **AB_OUT.D1** bereitgestellt.

Intern wird die Mapping-Logik durch einen einzigen IEC 61131-Baustein realisiert, daher ist die Latenz minimal und die Funktion deterministisch.

## Technische Besonderheiten

- **Composite-Struktur**: Der FB ist als Composite implementiert, d.h. er enthält ein internes Netzwerk mit einem einzigen Funktionsblock. Dies erleichtert die Wiederverwendung und Kapselung.
- **Adapter-Konzept**: Die Ein- und Ausgabe erfolgt ausschliesslich über typisierte Adapter (`AUI` und `AB`). Dies ermöglicht eine lose Kopplung und den einfachen Austausch von Kommunikationsprotokollen in der Applikation.
- **Lizenz**: Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0). Der Quellcode ist offen und kann frei angepasst werden.
- **Abhängigkeit**: Er benötigt den IEC 61131-Baustein `F_UINT_TO_BYTE`, der im Paket `iec61131::conversion` enthalten sein muss.

## Zustandsübersicht

Da der Baustein keine interne Zustandsmaschine besitzt (Composite ohne eigenes ECC), ist der Zustand rein durch den internen Funktionsblock `F_UINT_TO_BYTE` bestimmt. Dieser arbeitet ereignisgesteuert und besitzt keinen persistenten Zustand. Nach jedem Ereignis kehrt der Baustein in den Ruhezustand zurück.

## Anwendungsszenarien

- **Datenanpassung**: Wenn ein Sensor Daten im UINT-Format über einen AUI-Adapter liefert, das nachgeschaltete System jedoch einen BYTE-Wert über einen AB-Adapter erwartet.
- **Systemintegration**: Als Vermittler zwischen unterschiedlichen Adapter-Typen in heterogenen Automatisierungsnetzwerken.
- **Protokollanpassung**: In Szenarien, bei denen bestehende Bibliotheken nur bestimmte Adapter-Typen unterstützen und eine Typumwandlung erforderlich ist.

## Vergleich mit ähnlichen Bausteinen

- **Direkter `F_UINT_TO_BYTE`**: Dieser IEC-Baustein wird auch intern verwendet, arbeitet aber ohne Adapter – er benötigt direkte Daten- und Ereignisports. `AUI_TO_AB` kapselt diese Schnittstelle in Adapterform.
- **Andere Adapter-Konverter**: Es existieren ähnliche Bausteine wie `AB_TO_AUI` oder `ADI_TO_AB` für andere Typkombinationen. Sie folgen dem gleichen Pattern und sind austauschbar.

Der entscheidende Vorteil von `AUI_TO_AB` ist die vollständige Integration in adapterbasierte Architekturen – ohne dass die Applikation die interne Konvertierungslogik kennen muss.

## Fazit

Der Funktionsblock **AUI_TO_AB** ist ein einfacher, aber nützlicher Composite-Baustein zur Typumwandlung zwischen zwei unidirektionalen Adaptern. Seine klare Struktur und die Verwendung eines standardisierten Konverters machen ihn zuverlässig und leicht verständlich. Für alle Anwendungen, die eine saubere Adapter-Trennung erfordern, stellt er eine elegante Lösung dar.