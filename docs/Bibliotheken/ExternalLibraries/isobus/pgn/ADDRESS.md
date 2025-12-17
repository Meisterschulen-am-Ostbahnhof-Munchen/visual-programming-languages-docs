# ADDRESS

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ADDRESS` ist ein globaler Konstantenblock, der spezielle Adresskonstanten für die Verwendung in ISOBUS-basierten Anwendungen definiert. Er stellt vordefinierte Werte für Quell- und Zieladressen (Source Address, SA) bereit, die in der ISOBUS-Kommunikation eine besondere Bedeutung haben. Dieser Block dient dazu, den Quellcode lesbarer und wartbarer zu machen, indem magische Zahlen durch aussagekräftige Namen ersetzt werden.

## Schnittstellenstruktur
Dieser Block ist ein `GlobalConstants`-Block und besitzt daher keine klassischen Ereignis- oder Datenschnittstellen. Stattdessen definiert er Konstanten, die global in anderen Funktionsblöcken des Pakets `isobus::pgn` verwendet werden können.

### **Ereignis-Eingänge**
*Nicht vorhanden.*

### **Ereignis-Ausgänge**
*Nicht vorhanden.*

### **Daten-Eingänge**
*Nicht vorhanden.*

### **Daten-Ausgänge**
*Nicht vorhanden.*

### **Adapter**
*Nicht vorhanden.*

## Funktionsweise
Der Block `ADDRESS` deklariert zwei Konstanten:
1.  `NULL_A` (Typ: `BYTE`, Wert: `254`): Diese Konstante repräsentiert die NULL-Adresse (`0xFE`). Nachrichten mit dieser Quelladresse (SA) dürfen nur von einem Sender gesendet werden, der über einen Netzwerk-Manager verfügt.
2.  `GLOBAL_A` (Typ: `INT`, Wert: `255`): Diese Konstante repräsentiert die globale Adresse (`0xFF`). Diese Adresse wird ausschließlich im Zieladressfeld (Destination Address Field) verwendet, um eine Nachricht an alle Teilnehmer im Netzwerk zu broadcasten.

Diese Konstanten werden zur Compile-Zeit in den Code eingefügt und können nicht zur Laufzeit geändert werden.

## Technische Besonderheiten
*   **Typunterschied:** Auffällig ist, dass `NULL_A` als `BYTE` und `GLOBAL_A` als `INT` deklariert ist. Beide Werte liegen jedoch im darstellbaren Bereich beider Datentypen. Die Verwendung von `INT` für `GLOBAL_A` könnte auf eine spätere Erweiterbarkeit oder Kompatibilität mit anderen Teilen des Systems hindeuten.
*   **Paketzuordnung:** Der Block ist Teil des Pakets `isobus::pgn`, was auf seine Verwendung in der Parametergruppennummer (PGN)-Kommunikation des ISOBUS-Protokolls hindeutet.

## Zustandsübersicht
Da es sich um einen Konstantenblock handelt, besitzt er keinen Zustandsautomaten und keine internen Zustände.

## Anwendungsszenarien
Der `ADDRESS`-Block wird in ISOBUS-Anwendungen verwendet, beispielsweise in der Landtechnik (Traktoren, Anbaugeräte). Typische Szenarien sind:
*   **Konfiguration von Nachrichten:** Beim Aufbau von PGN-Nachrichten (Parameter Group Number) werden diese Konstanten verwendet, um das Quell- oder Zieladressfeld zu belegen.
*   **Netzwerkmanagement:** Die `NULL_A`-Adresse wird in speziellen Netzwerkmanagement-Nachrichten verwendet.
*   **Broadcast-Kommunikation:** Die `GLOBAL_A`-Adresse wird genutzt, um Befehle oder Daten an alle angeschlossenen Geräte im ISOBUS-Netz zu senden.

## Vergleich mit ähnlichen Bausteinen
In der IEC 61499-Standardbibliothek gibt es keinen direkten äquivalenten Baustein, da globale Konstanten eine sprachspezifische Erweiterung (hier abgeleitet von Structured Text) innerhalb der 4diac-IDE sind. Ein ähnlicher Zweck könnte erreicht werden durch:
*   **Direkte Werteingabe (Magic Numbers):** Das direkte Schreiben der Werte `254` oder `255` im Code ist möglich, aber schlechter Stil, da es die Lesbarkeit und Wartbarkeit beeinträchtigt.
*   **Konstanten-Blöcke in anderen Sprachen:** In Funktionsblock-Programmiersprachen wie CFC oder SFC werden vergleichbare Konstanten oft in separaten Header-Dateien oder globalen Variablenlisten definiert.

Der Vorteil des `ADDRESS`-Blocks liegt in der zentralen, paketgebundenen Definition und der semantischen Klarheit.

## Fazit
Der `ADDRESS`-Funktionsblock ist ein einfacher, aber essentieller Hilfsbaustein für die Entwicklung von ISOBUS-konformen Applikationen in der 4diac-IDE. Er erhöht die Codequalität, indem er numerische Spezialwerte durch selbsterklärende Bezeichner ersetzt und so Fehler vermeidet sowie die Wartung erleichtert. Seine Verwendung ist insbesondere bei der Implementierung von Netzwerkmanagement und Broadcast-Funktionalitäten empfohlen.