# BOOL_TO_QUARTER


## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

---- 
```{index} single: BOOL_TO_QUARTER
```

<img width="1677" height="214" alt="image" src="https://github.com/user-attachments/assets/78d7da91-c9c9-424a-a08b-2ac7b67c5662" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BOOL_TO_QUARTER` dient der Konvertierung eines binären BOOL-Signals in ein spezielles, vordefiniertes Quartal-Byte (quarter byte). Er übersetzt die logischen Zustände `TRUE` und `FALSE` in entsprechende, semantisch bedeutungsvolle Byte-Konstanten, die typischerweise für Steuerbefehle (z. B. ENABLE/DISABLE) verwendet werden. Dieser Baustein ist Teil der `logiBUS::utils::quarter`-Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Konvertierungsfunktion aus. Bei seinem Eintreffen wird der aktuelle Wert am Daten-Eingang `I` gelesen und verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis signalisiert den Abschluss der Konvertierung. Es wird zusammen mit dem berechneten Ausgangswert `QB` ausgegeben.

### **Daten-Eingänge**
*   **I** (BOOL, Initialwert: `FALSE`): Der binäre Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
*   **QB** (BYTE, Initialwert: `quarter::COMMAND_DISABLE`): Der Ausgangswert als Byte. Der Block nutzt ein sogenanntes "Quarter Byte" (2 Bit), das vier Zustände repräsentieren kann, von denen in dieser Implementierung nur zwei genutzt werden. Der konkrete Wert wird aus den Konstanten der importierten Bibliothek abgeleitet.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Auslösung durch das `REQ`-Ereignis wertet der Block den Wert am Eingang `I` aus. Die Verarbeitung erfolgt über eine `CASE`-Anweisung:
*   Wenn `I` den Wert `BOOL#TRUE` hat, wird der Ausgang `QB` auf die Konstante `quarter::COMMAND_ENABLE` gesetzt.
*   In allen anderen Fällen (standardmäßig also bei `FALSE`) wird der Ausgang `QB` auf die Konstante `quarter::COMMAND_DISABLE` gesetzt.

Unmittelbar nach der Zuweisung wird das `CNF`-Ereignis zusammen mit dem neuen Wert von `QB` ausgegeben.

## Technische Besonderheiten
*   **Bibliotheksabhängigkeit**: Der Block importiert und nutzt Konstanten (`quarter::COMMAND_ENABLE`, `quarter::COMMAND_DISABLE`) aus dem Paket `logiBUS::utils::quarter::const::quarter`. Die tatsächlichen Byte-Werte sind somit dort definiert und zentral änderbar.
*   **Quarter Byte Konzept**: Der Ausgang ist als `BYTE` deklariert, nutzt konzeptionell aber nur die unteren 2 Bit (ein "Quarter Byte"). Dies ermöglicht eine spätere Erweiterung um weitere Zustände, ohne die Schnittstelle ändern zu müssen.
*   **Initialwerte**: Sowohl der Eingang `I` als auch der Ausgang `QB` haben definierte Initialwerte (`FALSE` bzw. `COMMAND_DISABLE`), was ein deterministisches Startverhalten gewährleistet.

## Zustandsübersicht
Der Block besitzt keinen internen Zustand im Sinne eines Speichers. Er verhält sich rein kombinatorisch in Bezug auf die Eingangsdaten bei Auftreten des `REQ`-Ereignisses. Der Ausgang `QB` behält seinen zuletzt zugewiesenen Wert bis zum nächsten Ausführungszyklus.

## Anwendungsszenarien
*   **Steuerung von Aktoren**: Umwandlung eines einfachen Freigabe-Signals (`BOOL`) in einen gerätespezifischen Enable/Disable-Befehl, der als Byte über ein Feldbusprotokoll versendet wird.
*   **Schnittstellenanpassung**: Anbindung von Logikbausteinen, die mit BOOL-Werten arbeiten, an Steuerungskomponenten, die Befehle im Quarter-Byte-Format erwarten.
*   **Code-Vereinheitlichung**: Sicherstellung, dass in einem Projekt immer die gleichen, zentral definierten Konstanten für Enable-/Disable-Befehle verwendet werden.

## Vergleich mit ähnlichen Bausteinen
*   **`BOOL_TO_BYTE`**: Ein generischer Konverter, der `TRUE` typischerweise auf `1` und `FALSE` auf `0` abbildet. `BOOL_TO_QUARTER` ist spezialisierter und verwendet projektspezifische, semantische Konstanten anstelle numerischer Werte.
*   **Direkte Zuweisung**: Die Funktionalität könnte auch durch direkte Zuweisung in ST-Code (`QB := I`) nachgebildet werden, dabei gingen jedoch die Vorteile der zentralen Konstantendefinition und der klaren Schnittstelle (Events) verloren.

## Fazit
Der `BOOL_TO_QUARTER`-Funktionsblock ist ein spezialisierter, aber nützlicher Konverter für Steueranwendungen. Er bietet eine saubere Schnittstelle mit Ereignissteuerung, verwendet zentral verwaltete Konstanten für eine einheitliche Semantik und ist durch das Quarter-Byte-Konzept potentiell erweiterbar. Seine Stärke liegt in der Verbindung von einfacher binärer Logik mit gerätespezifischen Steuerprotokollen.