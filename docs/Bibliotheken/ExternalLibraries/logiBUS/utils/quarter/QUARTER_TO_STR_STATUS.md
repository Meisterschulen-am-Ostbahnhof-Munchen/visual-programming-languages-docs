# QUARTER_TO_STR_STATUS

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

---- 
```{index} single: QUARTER_TO_STR_STATUS
```

<img width="1745" height="212" alt="image" src="https://github.com/user-attachments/assets/52b6d758-7780-49a2-98e0-8be5f868339f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTER_TO_STR_STATUS` dient der Konvertierung eines 2-Bit-Statuswerts (auch als "Quarter Byte" bezeichnet) in einen menschenlesbaren Text-String. Er ist Teil der `logiBUS::utils::quarter`-Bibliothek und wird typischerweise verwendet, um kompakte Statusinformationen aus Steuerungen oder Geräten für Anzeige-, Protokollierungs- oder Diagnosezwecke in eine verständliche Textform zu überführen.

![QUARTER_TO_STR_STATUS](QUARTER_TO_STR_STATUS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Startet die Verarbeitung. Bei Eintreffen dieses Ereignisses wird der Wert am Daten-Eingang `IB` ausgelesen und die entsprechende Konvertierung durchgeführt.

### **Ereignis-Ausgänge**
*   **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten String am Daten-Ausgang `STR` ausgegeben.

### **Daten-Eingänge**
*   **IB** (BYTE): Der Eingang für den 2-Bit-Statuswert. Es werden nur die untersten zwei Bits (Bit 0 und 1) ausgewertet. Der Block erwartet spezifische, vordefinierte Konstanten aus der `quarter`-Bibliothek. Der Initialwert ist `quarter::COMMAND_DISABLE`.

### **Daten-Ausgänge**
*   **STR** (STRING): Der Ausgang, an dem der dem Statuswert entsprechende Text-String bereitgestellt wird. Der Initialwert ist `quarter::COMMAND_DISABLE_msg`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Der `QUARTER_TO_STR_STATUS` ist ein Basic Function Block (BFB) mit einem definierten Execution Control Chart (ECC). Bei einem eingehenden `REQ`-Ereignis wird der Wert an `IB` mit vordefinierten Konstanten verglichen. Abhängig von diesem Vergleich verzweigt die Steuerung in einen von vier möglichen Zuständen (`SET`, `RESET`, `Error`, `none`). In jedem dieser Zustände wird ein spezifischer Algorithmus ausgeführt, der den Ausgangs-`STR` auf einen entsprechenden Text-String setzt. Nach Ausführung des Algorithmus wechselt der Block in den Zustand `ok`, von dem aus das `CNF`-Ereignis ausgelöst wird. Anschließend kehrt der Block in den initialen `START`-Zustand zurück und ist bereit für die nächste Anfrage.

Die konkreten String-Werte werden aus der `quarter`-Konstanten-Bibliothek (`logiBUS::utils::quarter::const::quarter`) geladen. Die erwarteten Eingangswerte und ihre zugehörigen Ausgangsstrings sind:
*   `quarter::STATUS_ENABLED` → `quarter::COMMAND_ENABLE_msg`
*   `quarter::STATUS_DISABLED` → `quarter::COMMAND_DISABLE_msg`
*   `quarter::STATUS_ERROR` → `quarter::COMMAND_RESERVED_msg`
*   `quarter::STATUS_NOT_AVAILABLE` → `quarter::COMMAND_NO_ACTION_msg`

## Technische Besonderheiten
*   **Typensicherheit:** Der Block verwendet streng typisierte Konstanten aus einer speziellen Bibliothek, was die Fehleranfälligkeit gegenüber der direkten Verwendung von Rohwerten (z.B. 0, 1, 2, 3) verringert.
*   **2-Bit-Verarbeitung:** Obwohl der Eingang als `BYTE` deklariert ist, wird nur ein Quarter (2 Bit) dieses Bytes effektiv genutzt. Die Semantik der vier möglichen Zustände ist durch die verwendete Konstantenbibliothek festgelegt.
*   **Deterministisches Verhalten:** Die Zustandsübergänge sind ausschließlich vom Eingangswert bei `REQ` abhängig. Es gibt keine internen Speicher oder Hysterese-Effekte.

## Zustandsübersicht
Der ECC besteht aus sechs Zuständen:
1.  **START:** Initialer, wartender Zustand. Hier wird auf das `REQ`-Ereignis gewartet.
2.  **SET:** Wird bei `IB = quarter::STATUS_ENABLED` aktiviert. Führt Algorithmus `SET` aus.
3.  **RESET:** Wird bei `IB = quarter::STATUS_DISABLED` aktiviert. Führt Algorithmus `RESET` aus.
4.  **Error:** Wird bei `IB = quarter::STATUS_ERROR` aktiviert. Führt Algorithmus `ERROR` aus.
5.  **none:** Wird bei `IB = quarter::STATUS_NOT_AVAILABLE` aktiviert. Führt Algorithmus `NONE` aus.
6.  **ok:** Gemeinsamer Zustand nach jeder erfolgreichen Konvertierung. Löst das `CNF`-Ausgangsereignis aus und führt zurück zum `START`-Zustand.

## Anwendungsszenarien
*   **HMI-/SCADA-Anbindung:** Konvertierung von internen Gerätestati (z.B. "aktiviert", "fehlerhaft") in Strings für die Anzeige auf Bedienpanels oder in Visualisierungssoftware.
*   **Protokollierung und Diagnose:** Umwandlung von Statuscodes in lesbare Texte für Log-Dateien oder Diagnosetools, um die Fehleranalyse zu erleichtern.
*   **Schnittstelle zu Text-basierten Systemen:** Vorbereitung von Statusinformationen für die Weiterverarbeitung in Systemen, die mit String-Nachrichten arbeiten (z.B. MQTT-Topics, CSV-Export).

## Vergleich mit ähnlichen Bausteinen
*   **`E_SR` oder `E_RS` (Flip-Flops):** Diese Blöcke speichern einen binären Zustand (SET/RESET). `QUARTER_TO_STR_STATUS` hingegen konvertiert einen vorhandenen 4-Zustands-Wert nur in einen String; er besitzt keinen eigenen Speicher.
*   **`E_SELECT` oder `E_MUX`:** Können ebenfalls zwischen verschiedenen Pfaden/Werten wählen, sind aber generischer und nicht speziell auf die Konvertierung in Strings mit vordefinierten Quarter-Statuswerten ausgelegt.
*   **Einfache `STRING`-Zuweisung:** Eine direkte Zuweisung im ST-Code könnte ähnliches leisten, aber der `QUARTER_TO_STR_STATUS`-Block kapselt die Logik, fördert die Wiederverwendbarkeit und erzwingt die Verwendung der standardisierten Konstanten, was die Konsistenz im gesamten Projekt erhöht.

## Fazit
Der `QUARTER_TO_STR_STATUS` ist ein spezialisierter und nützlicher Funktionsblock für Anwendungen, die mit dem spezifischen 4-Zustands-Statusmodell (Quarter Byte) arbeiten. Durch die Nutzung einer Konstantenbibliothek und die klare Trennung von Logik und Schnittstelle trägt er zur Robustheit und Wartbarkeit von IEC 61499-Applikationen bei. Er ist die ideale Wahl, wenn kompakte Statusinformationen zuverlässig und einheitlich in eine für den Menschen lesbare Form gebracht werden müssen.