# SchieberStruct

```{index} single: SchieberStruct
```

* * * * * * * * * *
## Einleitung
Der `SchieberStruct` ist ein strukturierter Datentyp, der zur Abbildung aller möglichen Zustände eines Schiebers (z. B. eines Ventils, einer Klappe oder eines Verschlusses) innerhalb eines Steuerungssystems dient. Er dient als zentraler Container für die Objekt-Identifikatoren (IDs), die den verschiedenen Zuständen des Schiebers zugeordnet sind. Dieser Datentyp wird typischerweise in Verbindung mit Funktionsblöcken verwendet, die Zustandsmaschinen oder Sequenzen für Schiebersteuerungen implementieren.

## Schnittstellenstruktur
Der `SchieberStruct` ist ein Datentyp und besitzt daher keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne. Seine Struktur besteht ausschließlich aus Datenfeldern.

### **Daten-Eingänge**
Nicht zutreffend. Die Struktur definiert einen Datentyp, keine Funktionsblock-Schnittstellen.

### **Daten-Ausgänge**
Nicht zutreffend. Die Struktur definiert einen Datentyp, keine Funktionsblock-Schnittstellen.

### **Adapter**
Nicht zutreffend.

## Funktionsweise
Die `SchieberStruct` ist eine Datenstruktur, die fünf Felder vom Typ `UINT` (16-Bit unsigned integer) enthält. Jedes Feld repräsentiert einen spezifischen Zustand eines Schiebers und speichert die entsprechende Objekt-ID (`u16ObjId`). Diese IDs werden verwendet, um in einem übergeordneten System (z. B. einer Visualisierung oder einem Logikbaustein) auf die grafischen oder logischen Repräsentationen der Zustände zuzugreifen.

Die Initialwerte aller Felder sind auf die Konstante `ID_NULL` gesetzt, was einen undefinierten oder nicht zugewiesenen Zustand kennzeichnet. Diese müssen vor der Nutzung der Struktur mit gültigen Objekt-IDs belegt werden.

## Technische Besonderheiten
*   **Initialisierung:** Alle Mitgliedsvariablen werden standardmäßig mit dem Wert `ID_NULL` initialisiert. Dies stellt sicher, dass die Struktur in einem definierten, neutralen Zustand beginnt, bevor spezifische IDs zugewiesen werden.
*   **Typensicherheit:** Durch die Verwendung eines strukturierten Datentyps anstelle einzelner, lose gekoppelter Variablen wird die Code-Wartbarkeit und Lesbarkeit verbessert.
*   **Kompilierungshinweis:** Der Datentyp ist im Package `logiBUS::utils::sequence::schieber` definiert und importiert die Konstante `ID_NULL` aus dem `isobus::UT::Q::const::IDs`-Namespace.

## Zustandsübersicht
Die Struktur bildet explizit folgende fünf Zustände eines Schiebers ab:
1.  **`Unknown`:** Der Zustand des Schiebers ist unbekannt oder konnte nicht ermittelt werden.
2.  **`Closed`:** Der Schieber befindet sich in der geschlossenen Endlage.
3.  **`Opening`:** Der Schieber ist gerade dabei, sich zu öffnen (Bewegungszustand).
4.  **`Opened`:** Der Schieber befindet sich in der geöffneten Endlage.
5.  **`Closing`:** Der Schieber ist gerade dabei, sich zu schließen (Bewegungszustand).

## Anwendungsszenarien
*   **Zustandsverwaltung:** Ein übergeordneter Steuerungsbaustein kann eine Instanz dieser Struktur halten, um die aktuell gültigen Objekt-IDs für alle Schieberzustände zentral zu verwalten.
*   **Parametrierung:** Die Struktur kann als konfigurierbarer Parameter an einen Funktionsblock übergeben werden, der dann basierend auf seinem internen Zustand die entsprechende ID aus der Struktur auswählt und z. B. an ein Visualisierungssystem weiterleitet.
*   **Visualisierung:** Ein HMI- oder SCADA-System kann die in der Struktur hinterlegten IDs nutzen, um das grafische Symbol des Schiebers entsprechend seines aktuellen Zustands (z. B. Farbe, Symbol) zu aktualisieren.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken wie `E_SR` (Speicherglied) oder `E_CTUD` (Zähler), die aktive Logik implementieren, ist `SchieberStruct` ein passiver Datentyp. Ähnliche strukturierte Datentypen könnten für andere Geräte mit Zustandsmaschinen definiert werden (z. B. `PumpeStruct`, `MotorStruct`). Die Besonderheit liegt in der spezifischen Abbildung der für einen linearen Schieber charakteristischen Zustände `Opening`, `Closing`, `Opened` und `Closed` inklusive eines `Unknown`-Zustands.

## Fazit
Der `SchieberStruct` Datentyp ist ein nützliches Hilfskonstrukt für die strukturierte und typsichere Handhabung von Zustandsinformationen für Schieberaktoren. Durch die Kapselung der relevanten Objekt-IDs in einer einzigen Struktur wird die Konfiguration und Wartung von Anwendungen vereinfacht, die solche Aktoren steuern und visualisieren. Seine Verwendung fördert einen klaren und konsistenten Programmierstil.
