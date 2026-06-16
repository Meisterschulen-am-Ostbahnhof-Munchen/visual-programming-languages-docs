# AI_TO_AS


![AI_TO_AS](./AI_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_TO_AS** ist ein Composite-Baustein, der einen Adapter vom Typ `AI` (basierend auf `INT`) in einen Adapter vom Typ `AS` (basierend auf `SINT`) umwandelt. Er dient als Schnittstellenkonverter zwischen unterschiedlichen Datenformaten in der IEC 61499-Architektur.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine eigenen Ereignis-Eingänge. Die Ereignissteuerung erfolgt vollständig über den Adapter-Eingang `AI_IN` (siehe Abschnitt Adapter). Intern wird das Ereignis `E1` des Adapters verarbeitet.

### **Ereignis-Ausgänge**
Der FB besitzt keine eigenen Ereignis-Ausgänge. Das Ergebnisereignis wird über den Adapter-Ausgang `AS_OUT` bereitgestellt (siehe Abschnitt Adapter). Nach erfolgreicher Konvertierung wird das Ereignis `E1` auf dem Ausgangsadapter ausgelöst.

### **Daten-Eingänge**
Der FB besitzt keine eigenen Daten-Eingänge. Der zu konvertierende `INT`-Wert wird über den Adapter-Eingang `AI_IN` (Datenpunkt `D1`) eingelesen.

### **Daten-Ausgänge**
Der FB besitzt keine eigenen Daten-Ausgänge. Der konvertierte `SINT`-Wert wird über den Adapter-Ausgang `AS_OUT` (Datenpunkt `D1`) ausgegeben.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `AI_IN` | Eingang (Socket) | `adapter::types::unidirectional::AI` | INT-basierter Adapter-Eingang; liefert das Ereignis `E1` und den Datenwert `D1` (Typ `INT`). |
| `AS_OUT` | Ausgang (Plug) | `adapter::types::unidirectional::AS` | SINT-basierter Adapter-Ausgang; empfängt das Ereignis `E1` und gibt den konvertierten Datenwert `D1` (Typ `SINT`) weiter. |

## Funktionsweise
Der Baustein führt eine **Typkonvertierung von `INT` nach `SINT`** durch.  
Sobald am Adapter-Eingang `AI_IN` ein Ereignis `E1` eintrifft, wird der zugehörige Datenwert `D1` (INT) ausgelesen. Dieser Wert wird dem internen Baustein `F_INT_TO_SINT` übergeben. Die Konvertierung erfolgt gemäß der IEC 61131-3-Definition; dabei wird der `INT`-Wert auf den Wertebereich von `SINT` (-128...127) begrenzt. Nach erfolgreicher Umwandlung wird am Adapter-Ausgang `AS_OUT` das Ereignis `E1` erzeugt und der konvertierte `SINT`-Wert über `D1` übergeben.

## Technische Besonderheiten
- **Composite-Struktur**: Der FB ist als Composite realisiert, der auf den Standard-Baustein `F_INT_TO_SINT` zurückgreift. Dies ermöglicht eine einfache Wiederverwendung und klare Trennung der Konvertierungslogik.
- **Adapter-basierte Schnittstelle**: Die Ein- und Ausgänge sind als unidirektionale Adapter (`AI` und `AS`) ausgeführt, was eine flexible Anbindung an andere Komponenten mit kompatiblen Adapterschnittstellen erlaubt.
- **Keine Bereichsüberprüfung**: Der zugrunde liegende Baustein `F_INT_TO_SINT` führt keine explizite Fehlerbehandlung bei Wertebereichsüberschreitung durch. Liegt der `INT`-Wert außerhalb des `SINT`-Bereichs, kann es zu unerwarteten Ergebnissen oder Überläufen kommen (abhängig von der Zielplattform).

## Zustandsübersicht
Der FB verfügt über keine eigene Zustandsmaschine. Die interne Logik folgt dem einfachen Ablauf des Bausteins `F_INT_TO_SINT`:

| Zustand | Beschreibung |
|---------|--------------|
| **Idle** | Warten auf ein Ereignis an `AI_IN.E1`. |
| **Convert** | Bei Eintreffen von `E1` wird der Wert von `AI_IN.D1` gelesen, konvertiert und an `AS_OUT.D1` übergeben. Anschließend wird `AS_OUT.E1` ausgelöst. Der FB kehrt sofort in den Idle-Zustand zurück. |

## Anwendungsszenarien
- **Datenformat-Anpassung**: Wenn eine vorliegende INT-Schnittstelle in ein System integriert werden soll, das ausschließlich SINT-Werte verarbeitet (z. B. ältere Steuerungen oder begrenzte Busprotokolle).
- **Adapter-Wechsel**: Ersetzen eines AI-Adapters durch einen AS-Adapter in einer bestehenden Komponentenstruktur, ohne die interne Logik anzupassen.
- **Prototypen/Testaufbauten**: Schnelle Umwandlung von Testsignalen zwischen unterschiedlichen Datenbreiten.

## Vergleich mit ähnlichen Bausteinen
- **AI_TO_AS (INT → SINT)**: Speziell für die Konvertierung von INT zu SINT mit unidirektionalen Adaptern.
- **AY_TO_AS (DINT → SINT)**: Konvertiert DINT-Werte in SINT; prinzipiell gleicher Aufbau, aber anderer Datentyp.
- **Direkte Konvertierung ohne Adapter**: Bausteine wie `F_INT_TO_SINT` bieten die reine Typumwandlung, erfordern aber separate Ereignis- und Datenverbindungen. Der `AI_TO_AS` kapselt diese in einer Adapterlogik.

## Fazit
Der `AI_TO_AS`-Baustein stellt eine einfache und kompakte Lösung zur Umwandlung eines INT-basierten Adapters in einen SINT-basierten Adapter dar. Durch die Composite-Struktur und die klare Schnittstellendefinition lässt er sich leicht in IEC 61499-Applikationen integrieren. Die fehlende Bereichsprüfung sollte bei sicherheitskritischen Anwendungen beachtet werden. Insgesamt ist er ein nützlicher Helfer für die Signalaufbereitung in heterogenen Automatisierungssystemen.