# XOR_10_BOOL

```{index} single: XOR_10_BOOL
```

<img width="1397" height="485" alt="image" src="https://github.com/user-attachments/assets/2a69233b-010f-46f7-af45-759eb7f7fdb4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_10_BOOL` ist ein generischer Baustein zur Berechnung der logischen Exklusiv-ODER-Verknüpfung (XOR) über bis zu zehn boolesche Eingangssignale. Er folgt dem IEC 61131-3 Standard und ist für den Einsatz in der 4diac-IDE konzipiert. Der Baustein wertet bei jeder Anforderung alle verbundenen Eingänge aus und liefert das entsprechende Ergebnis.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Berechnung der XOR-Funktion aus. Es ist mit allen zehn Dateneingängen (`IN1` bis `IN10`) verknüpft.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1 (XOR input 1):** Boolescher Eingang 1.
*   **IN2 (XOR input 2):** Boolescher Eingang 2.
*   **IN3 (XOR input 3):** Boolescher Eingang 3.
*   **IN4 (XOR input 4):** Boolescher Eingang 4.
*   **IN5 (XOR input 5):** Boolescher Eingang 5.
*   **IN6 (XOR input 6):** Boolescher Eingang 6.
*   **IN7 (XOR input 7):** Boolescher Eingang 7.
*   **IN8 (XOR input 8):** Boolescher Eingang 8.
*   **IN9 (XOR input 9):** Boolescher Eingang 9.
*   **IN10 (XOR input 10):** Boolescher Eingang 10.

### **Daten-Ausgänge**
*   **OUT (XOR result):** Boolesches Ergebnis der XOR-Verknüpfung aller aktiven Eingänge.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Empfang des `REQ`-Ereignisses liest der Baustein die Werte aller zehn booleschen Dateneingänge (`IN1`...`IN10`) ein. Anschließend berechnet er das logische XOR über alle diese Eingänge. Die XOR-Funktion liefert genau dann ein `TRUE`-Signal (1) am Ausgang `OUT`, wenn eine ungerade Anzahl der Eingänge `TRUE` ist. Sind null, zwei, vier, sechs, acht oder zehn Eingänge `TRUE`, ist das Ergebnis `FALSE`. Nach der Berechnung wird das `CNF`-Ereignis zusammen mit dem aktuellen Ergebniswert ausgelöst.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Baustein gekennzeichnet (`GEN_XOR`). Dies ermöglicht eine flexible Wiederverwendung und eventuelle Spezialisierung.
*   **Feste Eingangsanzahl:** Im Gegensatz zu Bausteinen mit variabler Eingangsanzahl bietet dieser Block genau zehn fest definierte Eingänge. Nicht benötigte Eingänge sollten auf einen definierten Logikpegel (z.B. `FALSE`) gesetzt werden.
*   **Ereignisgesteuerte Ausführung:** Die Berechnung erfolgt ausschließlich ereignisgesteuert durch den `REQ`-Eingang. Es gibt keine zyklische Ausführung.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist rein kombinatorisch und von den aktuellen Eingangswerten abhängig. Der einzige "Zustand" ist das Warten auf ein `REQ`-Ereignis. Nach dessen Empfang wird sofort berechnet und das `CNF`-Ereignis gesendet.

## Anwendungsszenarien
*   **Paritätsprüfung:** Erkennung, ob eine ungerade Anzahl von Signalen (z.B. Fehlermeldungen, Schalterpositionen) aktiv ist.
*   **Steuerungslogik:** Implementierung von speziellen Verknüpfungslogiken in Ablaufsteuerungen, wo eine Zustandsänderung nur bei einem ungeraden Aktivierungsmuster erfolgen soll.
*   **Codierung/Decodierung:** Einfache kryptographische oder Codierungsaufgaben, die auf der XOR-Operation basieren.

## Vergleich mit ähnlichen Bausteinen
*   **Standard XOR-Blöcke (z.B., XOR mit 2 Eingängen):** Dieser Block erweitert die klassische 2-Eingang-XOR-Funktion auf bis zu zehn Eingänge in einem einzigen Baustein, was die Übersichtlichkeit bei vielen Signalen erhöht. Siehe: [XOR_10](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_10.md)
*   **Bausteine mit variabler Eingangsanzahl:** Einige Bibliotheken bieten XOR-Blöcke an, denen dynamisch Eingänge hinzugefügt werden können. `XOR_10_BOOL` hat eine feste, dafür explizit deklarierte Schnittstelle, was die Code-Analyse vereinfachen kann.
*   **Kombinatorische Logik in SFC/ST:** Die gleiche Funktion könnte auch in Structured Text (ST) mit einem Ausdruck wie `OUT := IN1 XOR IN2 XOR ... XOR IN10;` implementiert werden. Der Vorteil des FBs liegt in der klaren Kapselung und der ereignisgesteuerten Schnittstelle, die besser in FBNetzwerke integrierbar ist.

## Fazit
Der `XOR_10_BOOL` ist ein spezialisierter und nützlicher Funktionsblock für Anwendungen, die die XOR-Verknüpfung über mehr als zwei Signale erfordern. Seine feste, gut dokumentierte Schnittstelle mit zehn Eingängen und das ereignisgesteuerte IEC 61499-Modell machen ihn zu einem zuverlässigen Baustein für die Implementierung von Paritätsprüfungen und speziellen Steuerlogiken. Für einfachere Verknüpfungen mit weniger Eingängen oder für maximale Flexibilität sollten jedoch alternative Implementierungen in Betracht gezogen werden.
