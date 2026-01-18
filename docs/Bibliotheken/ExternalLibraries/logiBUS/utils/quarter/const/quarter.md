# quarter

## 🎧 Podcast

* [Das Geheimnis des 2-Bit-Quarter: Effizienz im CAN-Bus für Nutzfahrzeuge](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Das-Geheimnis-des-2-Bit-Quarter-Effizienz-im-CAN-Bus-fr-Nutzfahrzeuge-e3673bk)
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

---- 
```{index} single: quarter
```

* * * * * * * * * *
## Einleitung
Die `quarter`-Bibliothek ist eine Sammlung globaler Konstanten, die für die Arbeit mit SAE J1939-konformen Status- und Befehlswerten in logiBUS-Anwendungen vorgesehen ist. Sie definiert standardisierte 2-Bit-Werte (repräsentiert als `BYTE`) und zugehörige Klartextbeschreibungen (`STRING`) für Zustände und Steuerbefehle. Diese Konstanten dienen der Vereinheitlichung und verbesserten Lesbarkeit von Code, der mit binären Statusinformationen und Steuerkommandos arbeitet.

## Schnittstellenstruktur
Bei `quarter` handelt es sich um eine Sammlung globaler Konstanten (`GLOBALCONSTANTS`). Es ist daher kein Funktionsblock (FB) im klassischen Sinne mit Ereignis- oder Datenschnittstellen. Die Schnittstelle besteht ausschließlich aus den definierten Konstanten, die direkt im Code referenziert werden können.

### **Daten-Eingänge**
Nicht vorhanden (Konstantensammlung).

### **Daten-Ausgänge**
Nicht vorhanden (Konstantensammlung). Die Konstanten selbst stellen symbolische Namen für feste Werte dar.

### **Ereignis-Eingänge**
Nicht vorhanden (Konstantensammlung).

### **Ereignis-Ausgänge**
Nicht vorhanden (Konstantensammlung).

### **Adapter**
Nicht vorhanden (Konstantensammlung).

## Funktionsweise
Die Bibliothek stellt lediglich benannte Konstanten zur Verfügung. Bei der Verwendung im Code wird der symbolische Name (z.B. `STATUS_ENABLED`) durch den zugewiesenen Wert (z.B. `2#01`) ersetzt. Die `_msg`-Varianten enthalten beschreibende Texte, die für Debugging, Logging oder Benutzerausgaben genutzt werden können.

## Technische Besonderheiten
*   **Datentypen:** Alle Status- und Befehlskonstanten sind vom Typ `BYTE`, obwohl sie nur die unteren zwei Bits nutzen (Werte 0-3). Die zugehörigen Textkonstanten sind vom Typ `STRING`.
*   **Werte:** Die Werte sind als Binärliterale (`2#00`, `2#01`, etc.) definiert, was ihre Interpretation als 2-Bit-Felder klar hervorhebt.
*   **Paket:** Die Konstanten sind im Paket `logiBUS::utils::quarter::const` organisiert.

## Zustandsübersicht
Nicht anwendbar, da es sich um eine statische Wertesammlung handelt.

## Anwendungsszenarien
*   **SAE J1939-Kommunikation:** Verwendung in Funktionsblöcken, die Parameter gemäß SAE J1939 senden oder empfangen, insbesondere für Status- und Steuerinformationen, die als 2-Bit-Felder übertragen werden.
*   **Statusverwaltung:** Zuweisung und Abfrage von Geräte- oder Funktionszuständen (z.B. ein/aus, fehlerhaft, nicht verfügbar) innerhalb einer Steuerungsapplikation.
*   **Kommando-Schnittstellen:** Definition von Steuerbefehlen für entfernte Geräte oder Subsysteme (deaktivieren, aktivieren, keine Aktion).
*   **Logging und Diagnose:** Nutzung der `_msg`-Strings zur Generierung lesbarer Log-Einträge oder Anzeigen im Bedienpanel.

## Vergleich mit ähnlichen Bausteinen
*   **`logiBUS::utils::bit::const`:** Enthält Konstanten für einzelne Bits (z.B. `BIT_FALSE`, `BIT_TRUE`). `quarter` erweitert dieses Konzept auf 2-Bit-Felder mit anwendungsspezifischer Semantik.
*   **Manuelle Definition:** Anstelle der Verwendung dieser Bibliothek könnten die Werte direkt im Code als Zahlen oder Binärliterale geschrieben werden. Die Verwendung von `quarter` erhöht jedoch die Wartbarkeit, Lesbarkeit und Konsistenz über das gesamte Projekt hinweg.
*   **SAE J1939-spezifische Bibliotheken:** `quarter` ist eine grundlegende Hilfsbibliothek. Umfangreichere J1939-Bibliotheken würden wahrscheinlich auf diese Konstanten zurückgreifen, um spezifischere Nachrichten (PGNs) oder Parameter (SPNs) zu definieren.

## Fazit
Die `quarter`-Konstantenbibliothek ist ein nützliches Hilfsmittel für die Entwicklung von Steuerungssoftware im Umfeld von SAE J1939 und anderen Systemen, die 2-Bit-Status- und Steuerfelder verwenden. Sie fördert standardisierte, selbsterklärende Programmierung und reduziert die Fehleranfälligkeit durch die Verwendung von "Magic Numbers". Ihre Integration in das `logiBUS::utils`-Paket macht sie zu einer grundlegenden Komponente für strukturierte logiBUS-Applikationen.