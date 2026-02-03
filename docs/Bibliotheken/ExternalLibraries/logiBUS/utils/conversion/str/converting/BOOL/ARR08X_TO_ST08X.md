# ARR08X_TO_ST08X

```{index} single: ARR08X_TO_ST08X
```

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/f6ca4174-d362-4551-a80d-487df811f414" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock (FB) dient dazu, ein Array von 8 BOOL-Werten (ARR08X) in eine entsprechende Struktur von 8 BOOL-Werten (ST08X) umzuwandeln. Er ermöglicht eine einfache Konvertierung zwischen diesen beiden Datenformaten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Ein Ereignis, das die Konvertierung auslöst. Wenn REQ empfangen wird, wird der Wert des Eingangs `IN` verarbeitet und das Ergebnis am Ausgang `OUT` bereitgestellt.

### **Ereignis-Ausgänge**
*   **CNF**: Ein Bestätigungsereignis, das ausgelöst wird, sobald die Konvertierung abgeschlossen ist und der Ausgang `OUT` aktualisiert wurde.

### **Daten-Eingänge**
*   **IN**: Ein Array von 8 BOOL-Werten (BOOL[0..7]), das die Quelldaten für die Konvertierung darstellt.

### **Daten-Ausgänge**
*   **OUT**: Eine Struktur vom Typ `logiBUS::utils::conversion::types::ST08X`, die die konvertierten 8 BOOL-Werte enthält.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock `ARR08X_TO_ST08X` führt eine direkte elementweise Zuweisung der Werte aus dem Eingangs-Array `IN` auf die entsprechenden Felder der Ausgangsstruktur `OUT` durch. Bei jedem `REQ`-Ereignis wird der Wert des `IN`-Arrays gelesen und die einzelnen Elemente des Arrays `IN[0]` bis `IN[7]` den Feldern `X_00` bis `X_07` der `ST08X`-Struktur zugewiesen. Nach der Zuweisung wird das `CNF`-Ereignis ausgelöst.

Die Zuweisungen erfolgen wie folgt:
*   `OUT.X_00 := IN[0];`
*   `OUT.X_01 := IN[1];`
*   `OUT.X_02 := IN[2];`
*   `OUT.X_03 := IN[3];`
*   `OUT.X_04 := IN[4];`
*   `OUT.X_05 := IN[5];`
*   `OUT.X_06 := IN[6];`
*   `OUT.X_07 := IN[7];`

## Technische Besonderheiten
*   **Datentyp-Konvertierung**: Der Baustein spezialisiert sich auf die Konvertierung eines generischen BOOL-Arrays in eine spezifische BOOL-Struktur vom Typ `ST08X`. Dieser Strukturtyp muss im System bekannt sein (mittels `IMPORT logiBUS::utils::conversion::types::ST08X;`).
*   **Feste Größe**: Der Baustein ist für Arrays und Strukturen mit genau 8 BOOL-Elementen ausgelegt. Er ist nicht variabel für andere Array-Größen.
*   **Determinismus**: Die Konvertierung ist direkt und deterministisch. Die Ausführung erfolgt sofort bei Empfang des `REQ`-Ereignisses.

## Zustandsübersicht
Der Funktionsblock `ARR08X_TO_ST08X` ist ein zustandsloser (stateless) Baustein. Er speichert keine internen Zustände zwischen den Aufrufen. Jede Ausführung des Bausteins ist unabhängig von vorherigen Ausführungen und basiert ausschließlich auf den aktuellen Eingangswerten.

## Anwendungsszenarien
*   **Schnittstellenanpassung**: Ideal, um Datenformate zwischen verschiedenen Systemteilen anzupassen, insbesondere wenn ein Teil ein Array und ein anderer eine Struktur bevorzugt oder erwartet.
*   **Vereinheitlichung von Datenzugriffen**: Ermöglicht den Zugriff auf einzelne Bool-Werte über benannte Felder (`X_00`, `X_01`, etc.) anstatt über Array-Indizes, was die Lesbarkeit des Codes verbessern kann.
*   **Visualisierung**: Vereinfacht die Anbindung an Visualisierungssysteme, die möglicherweise eine strukturierte Darstellung von Bool-Signalen gegenüber einem Array bevorzugen.
*   **Legacy-Systeme**: Kann als Brücke zwischen älteren Systemen, die eventuell Bool-Arrays verwenden, und neueren Komponenten, die mit Strukturen arbeiten, dienen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **Manuelle Zuweisung**: Die Funktion könnte auch durch direkte Zuweisungen im Code des Steuerprogramms (z.B. in einem `ST`-Baustein) realisiert werden. Der `ARR08X_TO_ST08X` kapselt diese Logik jedoch in einem wiederverwendbaren Funktionsblock, was die Modularität und Übersichtlichkeit erhöht.
*   **Generische Konverter**: Im Gegensatz zu einem generischen Konverter, der beliebige Array-Größen oder Typen verarbeiten könnte, ist dieser Baustein spezifisch auf 8-BOOL-Arrays und die `ST08X`-Struktur zugeschnitten. Dies vereinfacht die Implementierung, macht ihn aber weniger flexibel für andere Größen.

## Fazit
Der `ARR08X_TO_ST08X` Funktionsblock ist ein nützlicher, spezialisierter Baustein zur effizienten und klaren Umwandlung von 8-elementigen BOOL-Arrays in eine 8-elementige BOOL-Struktur. Er trägt zur Verbesserung der Code-Lesbarkeit und der Modularen Architektur in 4diac-Anwendungen bei, insbesondere in Szenarien, die eine Anpassung von Datenformaten erfordern.