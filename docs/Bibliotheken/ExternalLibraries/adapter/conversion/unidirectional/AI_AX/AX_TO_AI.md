# AX_TO_AI


![AX_TO_AI](./AX_TO_AI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_TO_AI** ist ein zusammengesetzter Baustein, der einen BOOL-Adapter (AX) in einen INT-Adapter (AI) umwandelt. Er dient als Brücke zwischen Schnittstellen, die boolesche Signale (TRUE / FALSE) verarbeiten, und solchen, die ganzzahlige Werte erwarten. Die Konvertierung erfolgt über einen internen Aufruf des Bausteins `F_BOOL_TO_INT` aus der IEC 61131 Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine direkten Ereignis-Eingänge. Der Ereignis-Eingang des Bausteins wird über den Socket `AX_IN` (E1) realisiert.

### **Ereignis-Ausgänge**

Keine direkten Ereignis-Ausgänge. Der Ereignis-Ausgang des Bausteins wird über den Plug `AI_OUT` (E1) realisiert.

### **Daten-Eingänge**

Keine direkten Daten-Eingänge. Der Daten-Eingang des Bausteins wird über den Socket `AX_IN` (D1) realisiert (BOOL).

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Der Daten-Ausgang des Bausteins wird über den Plug `AI_OUT` (D1) realisiert (INT).

### **Adapter**

| Richtung | Name   | Typ (Adapter) | Erläuterung                        |
|----------|--------|---------------|------------------------------------|
| Socket   | AX_IN  | `AX`          | Boolescher Eingangsadapter (BOOL)  |
| Plug     | AI_OUT | `AI`          | Integer-Ausgangsadapter (INT)      |

Der Adapter `AX` stellt einen Ereignis-Eingang `E1` und einen Daten-Eingang `D1` (BOOL) zur Verfügung.  
Der Adapter `AI` stellt einen Ereignis-Ausgang `E1` und einen Daten-Ausgang `D1` (INT) zur Verfügung.

## Funktionsweise

Der Baustein arbeitet als sogenannter *Composite FB*, d.h. er nutzt intern einen anderen Funktionsblock zur Realisierung seiner Logik.

- Am Socket `AX_IN` wird ein BOOL-Signal über den Daten-Eingang `D1` empfangen.
- Ein eingehendes Ereignis an `AX_IN.E1` löst den internen Baustein `Convert` (Typ: `F_BOOL_TO_INT`) über dessen `REQ`-Eingang aus.
- Der `F_BOOL_TO_INT`-Baustein wandelt den BOOL-Wert am Eingang `IN` in einen INT-Wert (0 für `FALSE`, 1 für `TRUE`) um.
- Das Ergebnis wird am Ausgang `OUT` bereitgestellt und an den Plug `AI_OUT.D1` weitergeleitet.
- Nach Abschluss der Umwandlung sendet der interne Baustein ein Bestätigungsereignis (`CNF`), welches über `AI_OUT.E1` als Ausgangsereignis ausgegeben wird.

Die Abarbeitung erfolgt streng sequentiell: erst die boolesche Eingabe verarbeiten, dann die Integer-Ausgabe liefern.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Der Baustein verwendet ausschließlich Adapter-Schnittstellen (Socket und Plug) und keine klassischen Ein-/Ausgangsports. Dies ermöglicht eine lose Kopplung zwischen Komponenten und eine einfache Wiederverwendung in verschiedenen Umgebungen.
- **Unidirektionaler Datenaustausch:** Die verwendeten Adapter `AX` und `AI` sind als unidirektionale Typen definiert, d.h. die Daten fließen nur in eine Richtung – vom Socket zum Plug.
- **Externe Bibliothek:** Für die Konvertierung wird der Baustein `F_BOOL_TO_INT` aus der Bibliothek `iec61131::conversion` importiert. Dadurch müssen keine eigenen Konvertierungslogiken implementiert werden.
- **Kein eigener Zustandsautomat:** Da es sich um einen Composite-FB handelt, besitzt er kein eigenes ECC (Execution Control Chart). Die Zustandslogik wird vollständig durch den internen Baustein abgebildet.

## Zustandsübersicht

Der Baustein verfügt über keinen eigenen Zustandsautomaten. Die Ausführung erfolgt ereignisgesteuert:

1. **Warten:** Am Socket `AX_IN` wird auf ein Ereignis gewartet.
2. **Konvertieren:** Nach Empfang eines Ereignisses wird der interne FB `F_BOOL_TO_INT` ausgeführt und das Ergebnis an den Plug `AI_OUT` weitergegeben.
3. **Abgeschlossen:** Ein Bestätigungsereignis wird über `AI_OUT.E1` gesendet; der Baustein kehrt in den Wartezustand zurück.

Dieses Verhalten wird implizit durch die Ereignisverkabelung im Netzwerk gesteuert.

## Anwendungsszenarien

- **Signalumsetzung in der Automatisierungstechnik:** Wenn ein Sensor oder eine Steuerung boolesche Werte (z.B. „Tür offen/geschlossen“) liefert, ein nachgeschaltetes Modul aber ganzzahlige Werte (0/1) erwartet, kann dieser Baustein die Anpassung übernehmen.
- **Adapter-Integration:** Er dient als Konverter zwischen verschiedenen Adaptertypen, um Komponenten unterschiedlicher Hersteller oder Bibliotheken miteinander zu verbinden.
- **Protokollanpassung:** In heterogenen Systemen können boolesche Signale mit Hilfe dieses Bausteins in einheitliche Integer-Formate umgewandelt werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein            | Funktion                                  | Unterschied zu AX_TO_AI                                     |
|---------------------|-------------------------------------------|-------------------------------------------------------------|
| `DI_TO_AI`          | Wandelt digitalen Input in INT-Adapter um | Benötigt separate Ein-/Ausgangsports; keine Adapter-Schnittstelle |
| `AX_TO_DINT`        | BOOL‑Adapter → DINT‑Adapter               | Liefert einen 32‑Bit‑Integer; hier wird 16‑Bit INT verwendet |
| `F_BOOL_TO_INT`     | Standard-Konvertierung (BOOL→INT)         | Kein Adapter‑Wrapper; nur als interner Baustein verfügbar   |

Im Gegensatz zu diesen Alternativen bietet AX_TO_AI eine adressierbare, ereignisgesteuerte Adapter‑Schnittstelle und erleichtert die modulare Verschaltung in IEC 61499‑Projekten.

## Fazit

Der Funktionsblock `AX_TO_AI` stellt eine einfache, aber effektive Lösung zur Umwandlung boolescher Adapter-Signale in Integer-Adapter-Signale dar. Er kapselt die Logik in einem wiederverwendbaren Composite-Baustein, nutzt Standardbibliotheken und ermöglicht eine saubere, adapterbasierte Kommunikation. Der Baustein eignet sich besonders für modulare Automatisierungslösungen, bei denen unterschiedliche Schnittstellentypen aufeinander abgestimmt werden müssen.