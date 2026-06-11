# ADI_TO_AW


![ADI_TO_AW](./ADI_TO_AW.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ADI_TO_AW** ist ein zusammengesetzter Baustein, der die Umwandlung eines DINT-Wertes in einen WORD-Wert realisiert. Er fungiert als unidirektionaler Konverter zwischen einem **ADI**-Adapter (DINT-Eingang) und einem **AW**-Adapter (WORD-Ausgang). Der FB kapselt die Konvertierungslogik und stellt eine standardisierte Schnittstelle für den Datenaustausch auf Adapterebene bereit.

## Schnittstellenstruktur

Der FB verfügt über keine direkten Ereignis- oder Datenein-/ausgänge. Die gesamte Kommunikation erfolgt über Adapter:

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::ADI` | `ADI_IN` | Socket (Eingang) | DINT-Adapter, der den zu konvertierenden Wert bereitstellt |
| `adapter::types::unidirectional::AW` | `AW_OUT` | Plug (Ausgang) | WORD-Adapter, der den konvertierten Wert ausgibt |

Die internen Ereignis- und Datenverbindungen des Composite-FBs ergeben sich aus den genutzten Adapter-Schnittstellen:

### **Ereignis-Eingänge** (über ADI_IN)

| Ereignis | Beschreibung |
|----------|--------------|
| `E1` | Trigger für die Konvertierung des DINT-Wertes |

### **Ereignis-Ausgänge** (über AW_OUT)

| Ereignis | Beschreibung |
|----------|--------------|
| `E1` | Bestätigung der erfolgten Konvertierung und Ausgabe des WORD-Wertes |

### **Daten-Eingänge** (über ADI_IN)

| Bezeichner | Typ | Beschreibung |
|------------|-----|--------------|
| `D1` | `DINT` | Der zu konvertierende Ganzzahlwert |

### **Daten-Ausgänge** (über AW_OUT)

| Bezeichner | Typ | Beschreibung |
|------------|-----|--------------|
| `D1` | `WORD` | Der konvertierte Bitmuster-Wert (16 Bit) |

## Funktionsweise

Der FB arbeitet ereignisgesteuert:

1. Ein eingehendes Ereignis an `ADI_IN.E1` wird intern an den Konvertierungsbaustein `F_DINT_TO_WORD` weitergeleitet (über dessen `REQ`-Eingang).
2. Gleichzeitig wird der Datenwert von `ADI_IN.D1` als `DINT` an den `IN`-Eingang der Konvertierungsfunktion übergeben.
3. Der Baustein `F_DINT_TO_WORD` wandelt den `DINT`-Wert in einen `WORD`-Wert um (gemäß IEC 61131-3).
4. Nach Abschluss der Konvertierung wird das Ausgangsereignis (`CNF`) des Konverters abgesetzt.
5. Dieses Ereignis wird an `AW_OUT.E1` weitergeleitet, und der konvertierte `WORD`-Wert (von `OUT`) wird an `AW_OUT.D1` übergeben.

Somit erfolgt die gesamte Konvertierung in einem strengen Ereignis-/Daten-Fluss ohne zusätzliche Zustände.

## Technische Besonderheiten

- **Adapterbasierte Kapselung:** Der FB nutzt ausschließlich Adapter für Ein- und Ausgabe, was eine modulare und wiederverwendbare Anbindung in 4diac-Projekten ermöglicht.
- **Unidirektionale Konvertierung:** Es findet nur eine Datenwandlung vom Socket zum Plug statt; eine Rückwärtskonvertierung ist nicht vorgesehen.
- **Verwendung von IEC 61131-Bibliotheken:** Die Kernfunktion `F_DINT_TO_WORD` stammt aus dem `iec61131::conversion`-Paket, sodass die Konvertierung standardkonform und performant ist.
- **Keine eigenen Zustände:** Der FB besitzt kein internes Zustandsdiagramm; die Logik wird allein durch das Verhalten des enthaltenen Bausteins bestimmt.

## Zustandsübersicht

Da es sich um einen rein strukturierten Composite-FB ohne eigene ECC (Execution Control Chart) handelt, existiert kein explizites Zustandsmodell. Das Verhalten ist rein datenstromgetrieben und entspricht dem des internen Konvertierungsbausteins (IDLE → REQ → CNF → IDLE).

## Anwendungsszenarien

- **SPS-Kopplung:** Anbindung eines DINT-basierten Sensors (z. B. Encoder) an ein Subsystem, das WORD-Werte erwartet.
- **Datenformat-Konvertierung in Adapterketten:** Einsatz in einer 4diac-Anwendung, bei der verschiedene Adapter-Typen harmonisiert werden müssen.
- **Vereinheitlichung von Schnittstellen:** Umsetzung einer einheitlichen WORD-Schnittstelle für nachgelagerte Logikbausteine, während die Quelle im DINT-Format vorliegt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| `F_DINT_TO_WORD` | Direkte Konvertierung DINT → WORD | Keine Adapter-Kapselung; muss manuell in ein Netzwerk integriert werden |
| `ADI_TO_AW` | Adapterbasierte Kapselung derselben Konvertierung | Bietet sofort einsatzbereite Adapter-Schnittstellen; vereinfacht die Wiederverwendung |
| `WORD_TO_DINT` | Umgekehrte Konvertierung | Andere Richtung; eigener Adapter-Typ erforderlich |

Der `ADI_TO_AW` ist speziell für Umgebungen optimiert, in denen Adapter als standardisierte Schnittstellen gefordert sind.

## Fazit

Der Funktionsblock `ADI_TO_AW` stellt eine wiederverwendbare, adapterbasierte Lösung zur Konvertierung von `DINT` nach `WORD` dar. Er kapselt die Konvertierungslogik sauber und ermöglicht eine einfache Integration in 4diac-Architekturen, die auf dem Adapter-Konzept basieren. Durch die Verwendung von Standardbibliotheken ist die Funktion zuverlässig und spezifikationstreu. Der Baustein eignet sich besonders für Szenarien, bei denen unterschiedliche Datenformate über Adapterbrücken verbunden werden müssen.