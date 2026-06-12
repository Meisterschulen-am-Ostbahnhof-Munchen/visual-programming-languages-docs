# AW_TO_AUS


![AW_TO_AUS](./AW_TO_AUS.svg)

* * * * * * * * * *

## Einleitung

Der Composite Funktionsblock `AW_TO_AUS` dient der Konvertierung eines `WORD`-Adapter-Signals in ein `USINT`-Adapter-Signal. Er kapselt die IEC 61131-3 Standardfunktion `F_WORD_TO_USINT` in einer Adapter-gekoppelten Umgebung und ermöglicht so eine nahtlose Integration zwischen unterschiedlichen Adaptertypen.

## Schnittstellenstruktur

Der FB besitzt keine eigenständigen Ereignis- oder Datenports auf der Ebene der Funktionsblock-Schnittstelle. Die gesamte Kommunikation erfolgt ausschließlich über die beiden Adapter.

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `AW_IN` | `adapter::types::unidirectional::AW` | Erwartet einen `WORD`-Wert über den Datenport `D1` und ein Ereignis über `E1`. |
| Plug (Ausgang) | `AUS_OUT` | `adapter::types::unidirectional::AUS` | Liefert den konvertierten `USINT`-Wert über den Datenport `D1` und ein Bestätigungsereignis über `E1`. |

## Funktionsweise

1. Ein eingehendes Ereignis am Adapter-Socket `AW_IN.E1` triggert den internen Konvertierungsbaustein `Convert` (Typ `F_WORD_TO_USINT`) über dessen Ereigniseingang `REQ`.
2. Gleichzeitig wird der Datenwert von `AW_IN.D1` (vom Typ `WORD`) an den Dateneingang `Convert.IN` weitergeleitet.
3. Nach der Konvertierung wird das Ergebnis (`USINT`) am Datenausgang `Convert.OUT` bereitgestellt und an den Datenport `AUS_OUT.D1` übergeben.
4. Der Konvertierungsbaustein signalisiert die Fertigstellung über sein Ereignis `CNF`, welches direkt den Ereignisausgang `AUS_OUT.E1` aktiviert.

Dadurch entsteht eine synchrone, ereignisgesteuerte Umwandlung von einem `WORD`- zu einem `USINT`-Wert.

## Technische Besonderheiten

- **Composite Pattern**: Der Baustein ist als Composite FB realisiert, der die vorhandene Standardfunktion `F_WORD_TO_USINT` kapselt.
- **Adapter-Kopplung**: Der FB vereinfacht die Integration in bestehende Systeme, die auf die Adapter `AW` und `AUS` angewiesen sind, indem er die Konvertierung in einem einzigen Block zusammenfasst.
- **Keine eigene Zustandslogik**: Die gesamte Logik wird delegiert; der Baustein selbst hat keine eigene Ablaufsteuerung (ECC) und verhält sich rein direktional.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine. Der Ablauf wird vollständig durch die eingebettete Funktion `F_WORD_TO_USINT` und die Ereignisverbindungen bestimmt. Der FB ist daher als **stateless** zu betrachten.

## Anwendungsszenarien

- **Adapter-Konvertierung**: Wenn in einer 4diac-Applikation ein Adapter vom Typ `AW` (mit `WORD`-Daten) vorliegt, aber ein nachfolgender Baustein einen Adapter vom Typ `AUS` (mit `USINT`-Daten) erwartet.
- **Protokollanpassung**: Vereinfacht die Anbindung von Komponenten, die unterschiedliche Datentypen über ihre Adapter-Schnittstellen verwenden.
- **Minimaler Konvertierungsaufwand**: Ideal, wenn keine zusätzliche Logik erforderlich ist und lediglich eine einfache Typumwandlung (z.B. aus einem 16-Bit-Wert in einen 8-Bit-Wert) durchgeführt werden muss.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Verwendung von `F_WORD_TO_USINT`**: Dieser Standardbaustein arbeitet auf Datenebene, benötigt jedoch manuelle Ereignis- und Datenverbindungen. `AW_TO_AUS` kapselt diese Verbindungen und bietet eine adapterbasierte Schnittstelle.
- **Andere Adapter-Konverter (z.B. `AW_TO_ABOOL`)**: Unterscheiden sich durch den Ziel-Datentyp. Das vorliegende Schema (Socket -> Konvertierungs-FB -> Plug) kann für beliebige Datentypen analog aufgebaut werden.

## Fazit

`AW_TO_AUS` ist ein einfacher, aber nützlicher Composite FB zur Konvertierung von `WORD`-Adapter-Signalen in `USINT`-Adapter-Signale. Er nutzt eine bewährte IEC 61131-3 Standardfunktion und bietet eine saubere, adapterbasierte Schnittstelle. Der Baustein erfordert keine eigene Konfiguration und fügt sich nahtlos in ereignisgesteuerte Abläufe ein. Er eignet sich besonders für Anwendungen, bei denen eine schnelle und zuverlässige Datentypanpassung ohne zusätzliche Logik gewünscht ist.