# ARRAY2VALUES_2_LREAL

```{index} single: ARRAY2VALUES_2_LREAL
```

<img width="1227" height="178" alt="image" src="https://github.com/user-attachments/assets/1fda84e9-cd29-43f7-a566-6a8e259fa26f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARRAY2VALUES_2_LREAL` ist ein Dienstschnittstellen-Baustein, der darauf ausgelegt ist, ein Array von zwei `LREAL`-Werten in zwei separate `LREAL`-Ausgangsvariablen aufzuteilen. Er dient der einfachen Umwandlung von einem strukturierten Array-Format in individuelle Datenpunkte.

![ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Ein Service-Anforderungsereignis, das die Konvertierung initiiert. Es ist mit dem Daten-Eingang `IN` assoziiert.

### **Ereignis-Ausgänge**
*   **CNF**: Ein Bestätigungsereignis, das signalisiert, dass der angeforderte Dienst abgeschlossen wurde. Es ist mit den Daten-Ausgängen `OUT_1` und `OUT_2` assoziiert.

### **Daten-Eingänge**
*   **IN**: Ein Array-Eingang vom Typ `LREAL` mit einer Größe von 2 Elementen. Dieses Array enthält die zwei Werte, die aufgeteilt werden sollen.

### **Daten-Ausgänge**
*   **OUT_1**: Der erste Ausgangswert vom Typ `LREAL`, der dem ersten Element des `IN`-Arrays entspricht.
*   **OUT_2**: Der zweite Ausgangswert vom Typ `LREAL`, der dem zweiten Element des `IN`-Arrays entspricht.

### **Adapter**
Nicht vorhanden.

## Funktionsweise
Wenn das `REQ`-Ereignis empfangen wird, liest der `ARRAY2VALUES_2_LREAL`-Funktionsblock die beiden `LREAL`-Werte aus dem `IN`-Array. Das erste Element des `IN`-Arrays (`IN[0]`) wird dem Ausgang `OUT_1` zugewiesen, und das zweite Element (`IN[1]`) wird dem Ausgang `OUT_2` zugewiesen. Nach erfolgreicher Zuweisung wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
Der Funktionsblock ist darauf spezialisiert, genau ein Array von zwei `LREAL`-Werten zu verarbeiten und in zwei separate `LREAL`-Variablen aufzuteilen. Seine Implementierung ist direkt und auf diesen spezifischen Umwandlungszweck optimiert.

*   **Generische Implementierung:** Interessanterweise verweist das Attribut `eclipse4diac::core::GenericClassName` auf `'GEN_ARRAY2ARRAY'`. Dies deutet darauf hin, dass der Baustein möglicherweise von einer generischen Array-zu-Array-Klasse abgeleitet ist, auch wenn seine Funktion die Aufteilung in einzelne Werte ist. Dies könnte ein Detail der Implementierungsgeschichte sein.

## Zustandsübersicht
Dieser Funktionsblock ist zustandslos. Jede Auslösung des `REQ`-Ereignisses führt zu einer direkten Verarbeitung der aktuellen `IN`-Werte und einer Ausgabe über `OUT_1` und `OUT_2` ohne interne Zustandsänderungen, die über die aktuelle Transaktion hinausgehen würden.

## Anwendungsszenarien
*   **Datenaufbereitung**: Wenn Sensoren oder andere Bausteine Daten als Array von zwei `LREAL`-Werten liefern (z.B. X/Y-Koordinaten, Minimum/Maximum-Werte), aber nachfolgende Bausteine einzelne Variablen benötigen.
*   **Schnittstellenanpassung**: Anpassen von Schnittstellen, bei denen ein Quellbaustein Array-Daten sendet, der Zielbaustein jedoch diskrete Eingangsvariablen erwartet.
*   **Vereinfachung von Logik**: Erhöhung der Lesbarkeit und Vereinfachung der Logik, indem Array-Zugriffe in einzelne Variablen umgewandelt werden, die in weiteren Schritten leichter verarbeitet werden können.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Bausteine könnten generische Array-Splitter sein, die eine variable Anzahl von Array-Elementen in eine entsprechende Anzahl von Ausgängen aufteilen können. `ARRAY2VALUES_2_LREAL` ist jedoch für den spezifischen Fall eines `LREAL`-Arrays der Größe 2 optimiert, was ihn einfacher in der Konfiguration und möglicherweise effizienter für diesen konkreten Anwendungsfall macht als einen flexibleren, aber potenziell komplexeren generischen Baustein.

## Metadaten

| Attribut | Wert |

| :--- | :--- |

| Copyright | (c) 2014 Profactor GmbH |

| Lizenz | EPL-2.0 |

| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-07-09, Matthias Plasch) |

| 4diac-Paket | eclipse4diac::convert |

## Fazit

Der `ARRAY2VALUES_2_LREAL`-Funktionsblock ist ein nützliches Werkzeug für die gezielte Umwandlung eines `LREAL`-Arrays der Größe 2 in zwei separate `LREAL`-Ausgänge. Er bietet eine einfache und effiziente Lösung für die Datenaufbereitung und Schnittstellenanpassung in 4diac-Anwendungen, bei denen diese spezifische Konvertierung erforderlich ist.