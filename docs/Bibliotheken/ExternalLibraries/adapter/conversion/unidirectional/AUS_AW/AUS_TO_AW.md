# AUS_TO_AW


![AUS_TO_AW](./AUS_TO_AW.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AUS_TO_AW** ist ein Composite-Baustein, der eine einfache und standardisierte Konvertierung eines **USINT**-Werts (0–255) in einen **WORD**-Wert (16 Bit) über Adapter-Schnittstellen ermöglicht. Er dient als Vermittler zwischen Systemen, die unterschiedliche Datentypen über unidirektionale Adapter bereitstellen oder erwarten.

## Schnittstellenstruktur
Der Baustein selbst besitzt keine direkten Ein- oder Ausgänge. Die gesamte Kommunikation erfolgt über die beiden integrierten Adapter.

### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge vorhanden. Die Ereignissteuerung wird über den **AUS_IN**-Adapter realisiert. Dieser stellt einen Ereigniseingang **E1** bereit, dessen Aktivierung den Konvertierungsvorgang startet.

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge vorhanden. Ein Ereignis wird nach erfolgreicher Konvertierung über den **AW_OUT**-Adapter ausgegeben (Ereignisausgang **E1**).

### **Daten-Eingänge**
Keine direkten Dateneingänge vorhanden. Der zu konvertierende USINT-Wert wird über den Dateneingang **D1** des **AUS_IN**-Adapters eingelesen (Typ: USINT).

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden. Der konvertierte WORD-Wert wird über den Datenausgang **D1** des **AW_OUT**-Adapters ausgegeben (Typ: WORD).

### **Adapter**
- **AUS_IN** (Socket): Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AUS`. Erwartet einen USINT-Wert und ein Ereignis zur Auslösung der Konvertierung.
- **AW_OUT** (Plug): Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AW`. Stellt nach erfolgter Konvertierung den WORD-Wert und ein Bestätigungsereignis bereit.

## Funktionsweise
1. Ein externes Ereignis am **E1**-Eingang des **AUS_IN**-Adapters triggert die Ausführung.
2. Der interne Funktionsbaustein **F_USINT_TO_WORD** (aus der IEC‑61131‑Bibliothek) übernimmt den an **AUS_IN.D1** anliegenden USINT-Wert und konvertiert ihn in einen WORD-Wert.
3. Nach Abschluss der Konvertierung wird der WORD-Wert am **OUT**-Ausgang von **F_USINT_TO_WORD** an **AW_OUT.D1** weitergeleitet.
4. Gleichzeitig wird ein Ereignis am **CNF**-Ausgang von **F_USINT_TO_WORD** erzeugt, das über **AW_OUT.E1** nach außen signalisiert, dass der konvertierte Wert bereitsteht.

## Technische Besonderheiten
- **Composite-Baustein**: Die Konvertierungslogik ist in einem eigenen Netzwerk gekapselt, was Wiederverwendung und Übersichtlichkeit fördert.
- **Unidirektionale Adapter**: Die Adapter **AUS** und **AW** sind als reine Daten‑ und Ereignispipelines ausgelegt – eine Rückwärtskommunikation ist nicht vorgesehen.
- **Standardkonvertierung**: Die eigentliche Typumwandlung basiert auf dem geprüften Baustein `F_USINT_TO_WORD` aus der IEC‑61131‑Bibliothek.
- **Keine eigene Zustandslogik**: Der Baustein delegiert die gesamte Steuerung an den internen Konverter und die Adapter‑Schnittstellen.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Der Ablauf ist ereignisgesteuert und erfolgt streng sequenziell:
- **Idle**: Warten auf ein Ereignis am AUS_IN‑Adapter.
- **Konvertierung aktiv**: Interner **F_USINT_TO_WORD** wird ausgeführt. Nach Abschluss wechselt der Baustein automatisch zurück in den Idle‑Zustand.
- **Ausgabe**: Das Bestätigungsereignis wird am AW_OUT‑Adapter gesendet.

## Anwendungsszenarien
- **Systemintegration**: Ein Sensor liefert Messwerte als USINT über einen unidirektionalen AUS‑Adapter, die Steuerung erwartet jedoch WORD‑Werte über einen AW‑Adapter.
- **Datenaufbereitung**: In einer Adapter‑basierten Kommunikationskette soll eine einfache Typanpassung ohne zusätzliche Logik erfolgen.
- **Prototypenentwicklung**: Schnelle Kopplung zweier Komponenten, die unterschiedliche Datentypen verwenden, ohne die bestehende Adapterstruktur zu verändern.

## Vergleich mit ähnlichen Bausteinen
- **F_USINT_TO_WORD** (direkt): Bietet die reine Konvertierung ohne Adapter‑Anbindung – geeignet für interne Flüsse innerhalb eines Geräts.
- **AUS_TO_AW**: Erweitert die Konvertierung um unidirektionale Adapter, wodurch eine lose Kopplung zwischen unabhängigen Systemen erreicht wird.
- **Andere Adapter‑Konverter (z. B. INT_TO_DWORD)**: Folgen dem gleichen Muster, aber mit anderen Zieltypen. **AUS_TO_AW** ist speziell für die Paarung USINT → WORD optimiert.

## Fazit
**AUS_TO_AW** ist ein kompakter, zuverlässiger Composite‑Baustein, der die Konvertierung von USINT‑ zu WORD‑Daten über unidirektionale Adapter standardisiert und in bestehende 4diac‑Projekte nahtlos integriert werden kann. Er reduziert Entwicklungsaufwand und erhöht die Wiederverwendbarkeit in modularen Automatisierungssystemen.