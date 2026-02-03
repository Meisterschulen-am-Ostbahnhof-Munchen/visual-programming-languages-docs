# ST08X_TO_ARR08X

```{index} single: ST08X_TO_ARR08X
```

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/d556a75a-b21c-4bf2-b1c3-909baea1e51e" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock (FB) dient dazu, eine spezifische Struktur vom Typ `ST08X`, die acht einzelne BOOL-Werte enthält, in ein Array von ebenfalls acht BOOL-Werten umzuwandeln. Er ermöglicht eine nahtlose Anpassung der Datenrepräsentation in Automatisierungsanwendungen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis wird verwendet, um die Konvertierungsoperation zu initiieren. Bei Empfang dieses Ereignisses werden die Daten vom Eingang `IN` verarbeitet und in den Ausgang `OUT` geschrieben.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis wird ausgelöst, nachdem die Daten erfolgreich vom `IN`-Eingang in das `OUT`-Array konvertiert und der Ausgang aktualisiert wurde.

### **Daten-Eingänge**
*   **IN** (`logiBUS::utils::conversion::types::ST08X`): Dies ist der Eingang für die Struktur vom Typ `ST08X`. Diese Struktur enthält acht benannte BOOL-Felder (X_00 bis X_07), die umgewandelt werden sollen.

### **Daten-Ausgänge**
*   **OUT** (`BOOL[0..7]`): Dies ist der Ausgang für das Array von BOOL-Werten. Das Array hat eine feste Größe von 8 Elementen, die die konvertierten Daten aus der Eingangsstruktur enthalten.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock `ST08X_TO_ARR08X` führt eine direkte und deterministische Umwandlung der Eingangsdaten durch. Wenn das `REQ`-Ereignis empfangen wird, werden die einzelnen BOOL-Felder der Eingangsstruktur `IN` dem entsprechenden Index des `OUT`-Arrays zugewiesen:
*   `IN.X_00` wird `OUT[0]` zugewiesen.
*   `IN.X_01` wird `OUT[1]` zugewiesen.
*   ...
*   `IN.X_07` wird `OUT[7]` zugewiesen.

Nach Abschluss dieser Zuweisungen wird das `CNF`-Ereignis ausgegeben, um anzuzeigen, dass der Ausgang `OUT` aktualisiert wurde und die konvertierten Daten zur Verfügung stehen.

## Technische Besonderheiten
*   **Spezifische Typen**: Der Funktionsblock ist speziell für die Konvertierung zwischen dem benutzerdefinierten Typ `logiBUS::utils::conversion::types::ST08X` und einem `BOOL[0..7]`-Array konzipiert.
*   **Feste Zuordnung**: Die Zuordnung der Strukturfelder zu den Array-Indizes ist statisch und kann nicht zur Laufzeit konfiguriert werden.
*   **Atomare Operation**: Die Konvertierung ist eine einzelne, abgeschlossene Operation, die durch ein Eingangserhöhungsereignis ausgelöst wird.

## Zustandsübersicht
Der Funktionsblock `ST08X_TO_ARR08X` ist zustandslos (stateless). Er speichert keine internen Zustände oder Daten zwischen den Ausführungen. Jede Ausführung, die durch ein `REQ`-Ereignis ausgelöst wird, verarbeitet die aktuell an `IN` anliegenden Daten vollständig und unabhängig von früheren Operationen.

## Anwendungsszenarien
*   **Schnittstellenanpassung**: Ideal, um Daten von einer Komponente, die 8 BOOL-Werte als Struktur (`ST08X`) bereitstellt, an eine andere Komponente anzupassen, die ein `BOOL`-Array mit 8 Elementen erwartet (z.B. für Visualisierungen, externe Geräte oder generische Schleifenverarbeitung).
*   **Vereinheitlichung der Datenformate**: Wenn in einem Projekt verschiedene Konventionen für die Gruppierung von 8 BOOL-Werten verwendet werden, kann dieser FB dazu beitragen, die Daten in ein konsistentes Format zu bringen.
*   **Kompatibilität mit älteren Systemen**: Kann verwendet werden, um Daten aus moderneren Strukturen in array-basierte Formate zu überführen, die von älteren oder einfacheren Systemen besser verarbeitet werden können.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Während 4diac-IDE und der IEC 61499-Standard generische Datenkonvertierungsmechanismen und Funktionen zur Manipulation von Arrays bereitstellen, ist der `ST08X_TO_ARR08X` ein hochspezialisierter Baustein. Allgemeine Konvertierungs-FBs würden möglicherweise eine flexiblere Handhabung verschiedener Datentypen oder Array-Größen bieten, müssten aber oft konfiguriert werden oder würden zusätzliche Logik erfordern. Dieser Baustein bietet eine dedizierte, einfache und effiziente Lösung für genau diesen einen spezifischen Konvertierungsfall ohne Konfigurationsaufwand.

## Fazit
Der Funktionsblock `ST08X_TO_ARR08X` ist ein präzises Werkzeug zur Umwandlung einer 8-BOOL-Struktur in ein 8-BOOL-Array. Seine Einfachheit und Spezialisierung machen ihn zu einer effizienten Lösung für die Schnittstellenanpassung und Datenformatierung in 4diac-basierten Automatisierungsanwendungen, die eine solche Umwandlung erfordern.