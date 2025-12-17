# AND_3_BOOL

<img width="1383" height="275" alt="image" src="https://github.com/user-attachments/assets/e4d9d0a5-5b7b-41c6-9187-4cb9a9380a03" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_3_BOOL` ist ein standardisierter Baustein zur Berechnung der logischen UND-Verknüpfung für drei boolesche Eingangssignale. Er folgt dem IEC 61131-3 Standard für grundlegende boolesche Funktionen und arbeitet nach dem Echtzeit-Execution-Control-Modell von 4diac, bei dem die Berechnung durch ein eingehendes Ereignis gestartet wird.

## Schnittstellenstruktur
Die Schnittstelle des `AND_3_BOOL`-Blocks ist klar und einfach aufgebaut, bestehend aus einem Ereigniseingang, einem Ereignisausgang, drei Dateneingängen und einem Datenausgang.

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses eingehende Ereignis löst die Ausführung des Funktionsblocks aus. Beim Eintreffen von `REQ` werden die aktuellen Werte an den Dateneingängen `IN1`, `IN2` und `IN3` gelesen und die logische UND-Operation durchgeführt.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis wird nach Abschluss der Berechnung erzeugt. Es signalisiert, dass das Ergebnis an den Datenausgang `OUT` ausgegeben wurde und nun gültig ist.

### **Daten-Eingänge**
*   **IN1 (BOOL):** Erstes boolesches Eingangssignal für die UND-Verknüpfung.
*   **IN2 (BOOL):** Zweites boolesches Eingangssignal für die UND-Verknüpfung.
*   **IN3 (BOOL):** Drittes boolesches Eingangssignal für die UND-Verknüpfung.

### **Daten-Ausgänge**
*   **OUT (BOOL):** Das Ergebnis der logischen UND-Verknüpfung aller drei Eingänge. `OUT` ist nur dann `TRUE` (1), wenn **alle** Eingänge `IN1`, `IN2` und `IN3` gleichzeitig `TRUE` sind. In allen anderen Fällen ist `OUT` `FALSE` (0).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und folgt einer einfachen Abfolge:
1.  **Auslösung:** Das eingehende Ereignis `REQ` aktiviert den Block.
2.  **Lesen der Eingänge:** Die aktuellen Werte der drei booleschen Dateneingänge (`IN1`, `IN2`, `IN3`) werden eingelesen.
3.  **Berechnung:** Die logische UND-Operation wird ausgeführt: `OUT := IN1 AND IN2 AND IN3`.
4.  **Ausgabe:** Das berechnete Ergebnis wird an den Datenausgang `OUT` geschrieben.
5.  **Bestätigung:** Das Ausgangsereignis `CNF` wird erzeugt, um den erfolgreichen Abschluss der Operation an nachfolgende Blöcke zu signalisieren.

## Technische Besonderheiten
*   **Generischer FB:** Der Block ist als generischer Funktionsblock (`GEN_AND`) gekennzeichnet, was bedeutet, dass er als Basis für die Erstellung ähnlicher UND-Bausteine mit einer anderen Anzahl von Eingängen dienen kann.
*   **Echtzeitfähig:** Durch das Execution-Control-Modell (Ereignissteuerung) ist der Block für deterministische Echtzeitanwendungen geeignet.
*   **Einfache Logik:** Enthält keine internen Zustände oder Speicher. Die Ausgabe ist eine reine Kombinatorikfunktion der aktuellen Eingänge.

## Zustandsübersicht
Der `AND_3_BOOL`-Block ist ein **kombinatorischer** Funktionsblock ohne internen Zustand (zustandslos). Sein Verhalten ist bei jedem Aufruf (`REQ`) ausschließlich von den aktuellen Werten an den Dateneingängen abhängig. Es gibt keine vorherigen Berechnungen oder Zustände, die das Ergebnis beeinflussen.

## Anwendungsszenarien
Typische Anwendungen sind Steuerungslogiken, bei denen eine Aktion nur dann ausgeführt werden darf, wenn mehrere Sicherheits- oder Freigabebedingungen gleichzeitig erfüllt sind:
*   **Zweihand-Bedienung:** Eine Maschine startet nur, wenn drei separate Taster gleichzeitig gedrückt werden (`IN1`, `IN2`, `IN3`).
*   **Sicherheitskreis:** Aktivierung eines Prozesses nur bei geschützter Schutztür (`IN1`), aktivierter Not-Aus-Umgehung (`IN2`) und vorhandener Materialzufuhr (`IN3`).
*   **Verkettung von Bedingungen:** Als Teil einer komplexeren logischen Gleichung innerhalb eines Algorithmus.

## Vergleich mit ähnlichen Bausteinen
*   **`AND_2_BOOL`:** Führt die UND-Verknüpfung für nur zwei Eingänge durch. `AND_3_BOOL` ist eine direkte Erweiterung für drei Eingänge.
*   **`AND_n_BOOL` (theoretisch):** Ein generischer Block für eine variable Anzahl `n` von Eingängen. `AND_3_BOOL` ist eine spezifische, fest verdrahtete Instanz für `n=3`. Siehe: [AND_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_3.md)
*   **`OR_3_BOOL`:** Berechnet die logische ODER-Verknüpfung (Ausgang ist `TRUE`, wenn mindestens ein Eingang `TRUE` ist). Dies ist die komplementäre Funktion.
*   **Kombinatorische Logik in SFC/ST:** Die gleiche Funktion könnte auch in Structured Text (ST) als `OUT := IN1 & IN2 & IN3;` oder in einer SFC-Aktion implementiert werden. Der Vorteil des FB ist die Wiederverwendbarkeit, klare Kapselung und die einfache Integration in das 4diac-Ereignissystem.

## Fazit
Der `AND_3_BOOL` ist ein fundamentaler, zuverlässiger und einfach zu verwendender Baustein für die boolesche Logik in 4diac-basierten Steuerungsanwendungen. Seine strenge Ereignissteuerung gewährleistet deterministisches Verhalten, und die klare Schnittstelle ermöglicht eine intuitive Integration in Funktionsbaustein-Netzwerke. Für alle Steuerungsaufgaben, die eine dreifache UND-Verknüpfung erfordern, ist dieser Block die Standardlösung.
