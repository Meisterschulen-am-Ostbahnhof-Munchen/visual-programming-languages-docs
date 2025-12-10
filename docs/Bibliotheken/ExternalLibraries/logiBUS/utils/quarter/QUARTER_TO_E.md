# QUARTER_TO_E

<img width="1487" height="288" alt="image" src="https://github.com/user-attachments/assets/b4e62664-7544-420c-a039-36905d34d735" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTER_TO_E` dient dazu, einen 2-Bit-Zustandswert (ein sogenanntes "Quarter Byte") in vier verschiedene, eindeutige Ereignisse zu übersetzen. Er ist ein Hilfsbaustein, der häufig in Verbindung mit Bausteinen verwendet wird, die mehr als die üblichen zwei Zustände (EIN/AUS) melden, wie z.B. Statusmeldungen von Geräten, die auch Fehler- oder Nicht-Verfügbarkeitszustände anzeigen können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Startet die Verarbeitung. Bei diesem Ereignis wird der aktuelle Wert am Daten-Eingang `IB` ausgewertet.

### **Ereignis-Ausgänge**
*   **CNF**: Signalisiert die erfolgreiche Beendigung der Verarbeitung, unabhängig vom erkannten Zustand. Wird immer nach der Ausgabe eines der spezifischen Ereignisse generiert.
*   **S** (Enabled): Wird ausgelöst, wenn der Zustand "aktiviert" oder "eingeschaltet" erkannt wird.
*   **R** (Disabled): Wird ausgelöst, wenn der Zustand "deaktiviert" oder "ausgeschaltet" erkannt wird.
*   **ERR** (Error): Wird ausgelöst, wenn ein Fehlerzustand erkannt wird.
*   **NONE** (Not available): Wird ausgelöst, wenn der Zustand "nicht verfügbar" oder "nicht installiert" erkannt wird.

### **Daten-Eingänge**
*   **IB** (BYTE): Enthält den zu interpretierenden 2-Bit-Zustandswert. Der Initialwert ist auf `quarter::COMMAND_DISABLE` gesetzt. Die tatsächliche Interpretation erfolgt anhand der definierten Konstanten aus dem `quarter`-Paket.

### **Daten-Ausgänge**
*   **Q** (BOOL): Ein boolescher Ausgang, dessen Wert je nach erkanntem Zustand gesetzt wird. Er dient als einfache, binäre Repräsentation des Hauptzustands (aktiviert/deaktiviert).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der `QUARTER_TO_E` ist ein Basic Function Block mit einem internen Zustandsautomaten (ECC). Bei Eintreffen des `REQ`-Ereignisses wird der Wert am Eingang `IB` mit vordefinierten Konstanten verglichen. Abhängig vom Vergleich springt der Automat in einen der vier Zustände `SET`, `RESET`, `Error` oder `none`. In jedem dieser Zustände wird ein entsprechender Algorithmus ausgeführt, der den booleschen Ausgang `Q` setzt (oder nicht ändert) und das zugehörige spezifische Ereignis (`S`, `R`, `ERR`, `NONE`) auslöst. Anschließend wechselt der Automat in den Zustand `ok`, von wo aus das Bestätigungsereignis `CNF` ausgegeben wird, bevor der Automat in den Ausgangszustand `START` zurückkehrt und auf das nächste `REQ` wartet.

## Technische Besonderheiten
*   Der Block nutzt Konstanten aus dem Paket `logiBUS::utils::quarter::const::quarter` (`STATUS_ENABLED`, `STATUS_DISABLED`, `STATUS_ERROR`, `STATUS_NOT_AVAILABLE`). Diese müssen im Projekt verfügbar sein.
*   Der Ausgang `Q` wird nur in den Zuständen `SET` (auf TRUE), `RESET` (auf FALSE) und `ERROR` (auf FALSE) verändert. Im Zustand `NONE` wird `Q` explizit nicht verändert ("Don't care").
*   Die Ausgabe des `CNF`-Ereignisses erfolgt immer, unabhängig davon, welcher spezifische Zustand erkannt wurde. Dies ermöglicht eine einheitliche Ablaufsteuerung in der Applikation.

## Zustandsübersicht
1.  **START**: Wartezustand. Bei `REQ` erfolgt die Auswertung von `IB` und der Übergang zu einem Verarbeitungszustand.
2.  **SET**: Wird bei `IB = STATUS_ENABLED` erreicht. Setzt `Q:=TRUE` und löst `S` aus.
3.  **RESET**: Wird bei `IB = STATUS_DISABLED` erreicht. Setzt `Q:=FALSE` und löst `R` aus.
4.  **Error**: Wird bei `IB = STATUS_ERROR` erreicht. Setzt `Q:=FALSE` und löst `ERR` aus.
5.  **none**: Wird bei `IB = STATUS_NOT_AVAILABLE` erreicht. Löst `NONE` aus (Q bleibt unverändert).
6.  **ok**: Zwischenzustand, der das `CNF`-Ereignis auslöst und zurück zum `START`-Zustand führt.

## Anwendungsszenarien
*   **Interpretation von Gerätestatus**: Ein Antriebsmeldet seinen Status nicht nur als EIN/AUS, sondern auch als "Fehler" oder "Nicht bereit". Dieser Block wandelt den Gerätestatus in separate, leicht verarbeitbare Ereignisse um.
*   **Vereinfachung der Logik**: Anstatt in nachfolgenden Blöcken ständig den Byte-Wert abfragen zu müssen, können direkt auf die spezifischen Ereignisse (`S`, `R`, `ERR`) reagiert werden.
*   **Abstraktion**: Dient als Adapter zwischen Bausteinen, die einen Quarter-Byte-Status liefern, und einer Logik, die mit klassischen Ereignis-/Boolsignalen arbeitet.

## Vergleich mit ähnlichen Bausteinen
*   **E_DEMUX / E_SELECT**: Diese Blöcke leiten ein Eingangsereignis basierend auf einem Steuerwert an einen von mehreren Ausgängen weiter. `QUARTER_TO_E` ist spezialisierter: Er übersetzt einen spezifischen Datenwert (`IB`) nicht nur in eine Auswahl, sondern löst auch unterschiedliche *inhaltliche* Ereignisse aus und berechnet zusätzlich einen booleschen Wert (`Q`).
*   **BYTE_TO_E**: Ein generischer Block, der jedes Bit eines Bytes in ein separates Ereignis umwandeln könnte. `QUARTER_TO_E` ist semantisch reicher, da er spezifische, vordefinierte Zustände (Enabled, Disabled, Error, None) und deren Bedeutung kennt und ausgibt.

## Fazit
Der `QUARTER_TO_E` ist ein nützlicher und spezialisierter Baustein für die strukturierte Verarbeitung von 4-Zustands-Signalen (Quad-State). Er entlastet die Applikationslogik, indem er die Rohdateninterpretation übernimmt und klare, semantische Ereignisse sowie einen vereinfachten booleschen Status bereitstellt. Seine Stärke liegt in der Kombination aus Datenverarbeitung und ereignisbasierter Ausgabe gemäß der IEC 61499.
