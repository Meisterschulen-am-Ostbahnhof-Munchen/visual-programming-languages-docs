# QUARTER_TO_BOOL

<img width="1424" height="183" alt="image" src="https://github.com/user-attachments/assets/81acd0ec-c837-49d1-9ed8-3000cb65786e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTER_TO_BOOL` dient der Konvertierung eines 4-Zustands-Signals (Quad-State), das in den unteren zwei Bits eines BYTE-Wertes kodiert ist, in ein einfaches BOOL-Signal. Er ist besonders für die Anbindung an Systeme nützlich, die Statusinformationen mit mehr als zwei Zuständen liefern, die jedoch in einer einfachen binären Logik weiterverarbeitet werden sollen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Startet die Konvertierung. Mit diesem Ereignis wird der anliegende Eingangswert `IB` ausgewertet.

### **Ereignis-Ausgänge**
*   **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird immer nach der Bearbeitung eines `REQ`-Ereignisses ausgegeben.

### **Daten-Eingänge**
*   **IB** (BYTE): Enthält den zu konvertierenden 4-Zustands-Wert in seinen unteren zwei Bits. Der Initialwert ist `quarter::COMMAND_DISABLE`. Die erwarteten Werte sind spezifische Konstanten aus dem `quarter`-Namespace.

### **Daten-Ausgänge**
*   **Q** (BOOL): Das Ergebnis der Konvertierung. Der Initialwert ist `FALSE`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung durch ein `REQ`-Ereignis liest der Baustein den Wert am Daten-Eingang `IB`. Anschließend wird dieser Wert mit vordefinierten Konstanten verglichen, um den entsprechenden internen Zustand zu ermitteln. Je nach Zustand wird ein spezifischer Algorithmus ausgeführt, der den BOOL-Ausgang `Q` setzt oder seinen Wert beibehält. Nach Ausführung des Algorithmus wird das `CNF`-Ereignis ausgelöst, und der Baustein kehrt in seinen Startzustand zurück.

Die konkrete Abbildung der Eingangswerte auf die Ausgangslogik ist wie folgt:
*   `quarter::STATUS_ENABLED` → Algorithmus `SET` → `Q := TRUE`
*   `quarter::STATUS_DISABLED` → Algorithmus `RESET` → `Q := FALSE`
*   `quarter::STATUS_ERROR` → Algorithmus `ERROR` → `Q := FALSE`
*   `quarter::STATUS_NOT_AVAILABLE` → Algorithmus `NONE` → `Q` bleibt unverändert

## Technische Besonderheiten
*   **Zustandsbehandlung**: Der Baustein ist als Basic-FB implementiert und besitzt eine explizite Zustandsmaschine (ECC). Die Zustände `SET`, `RESET`, `ERROR` und `none` sind reine Algorithmuszustände, während der Zustand `ok` für die Ausgabe des Bestätigungsereignisses verantwortlich ist.
*   **Wertbeibehaltung**: Im Fall des Status `STATUS_NOT_AVAILABLE` wird der Algorithmus `NONE` ausgeführt, der den aktuellen Wert des Ausgangs `Q` explizit nicht verändert. Dies ermöglicht ein "Don't Care"- oder "Hold"-Verhalten.
*   **Initialisierung**: Der Datenausgang `Q` wird beim Start auf `FALSE` initialisiert.

## Zustandsübersicht
Die ECC (Execution Control Chart) besteht aus sechs Zuständen:
1.  **START**: Initial- und Wartezustand. Bei eintreffendem `REQ` erfolgt je nach Wert von `IB` ein Übergang zu `SET`, `RESET`, `Error` oder `none`.
2.  **SET**: Führt den Algorithmus `SET` aus (setzt `Q` auf TRUE).
3.  **RESET**: Führt den Algorithmus `RESET` aus (setzt `Q` auf FALSE).
4.  **Error**: Führt den Algorithmus `ERROR` aus (setzt `Q` auf FALSE).
5.  **none**: Führt den Algorithmus `NONE` aus (lässt `Q` unverändert).
6.  **ok**: Löst das `CNF`-Ausgangsereignis aus und wechselt anschließend zurück in den `START`-Zustand.

## Anwendungsszenarien
*   **Anbindung von Feldgeräten**: Viele Sensoren oder Aktoren melden Status wie "Bereit", "Gestört", "Wartung" oder "Nicht verbunden". Dieser Baustein kann solche Meldungen in ein einfaches "Ein/Aus"- oder "OK/Nicht OK"-Signal für übergeordnete Steuerlogiken umwandeln.
*   **Vereinfachung von Logik**: In Steuerungen, die nur binäre Entscheidungen benötigen (z.B. "Prozess freigeben" ja/nein), kann dieser FB komplexere Statusmeldungen auf die entscheidende binäre Information reduzieren.
*   **Fehlerbehandlung**: Ein einheitlicher Umgang mit Fehlerzuständen (`STATUS_ERROR`) durch Setzen des Ausgangs auf `FALSE`.

## Vergleich mit ähnlichen Bausteinen
*   **Standardkonverter (z.B., `BYTE_TO_BOOL`)**: Ein einfacher `BYTE_TO_BOOL`-Konverter würde typischerweise einen Schwellwert verwenden (z.B., alles >0 wird zu TRUE). `QUARTER_TO_BOOL` hingegen interpretiert spezifische, benannte Zustände und bietet ein definiertes Verhalten für jeden einzelnen, einschließlich der Möglichkeit, den Ausgang bei einem Zustand unverändert zu lassen.
*   **`E_SELECT`- oder `E_DEMUX`-Bausteine**: Diese könnten verwendet werden, um basierend auf einem Eingangswert unterschiedliche Ereignispfade zu aktivieren. `QUARTER_TO_BOOL` kapselt diese Logik speziell für die Konvertierung von 4-Zustands-Signalen und liefert direkt das boolesche Ergebnis.

## Fazit
Der `QUARTER_TO_BOOL`-Funktionsblock ist ein spezialisierter und nützlicher Konverter für Anwendungen, in denen kompakte Statusinformationen mit vier diskreten Zuständen in eine einfache binäre Logik integriert werden müssen. Seine klare Definition des Verhaltens für jeden Zustand, insbesondere die Beibehaltung des Ausgangswerts im "Nicht verfügbar"-Fall, macht ihn robust und gut vorhersagbar. Er eignet sich ideal für die Schnittstelle zwischen komplexeren Feldbussystemen und grundlegender binärer Steuerungslogik.
