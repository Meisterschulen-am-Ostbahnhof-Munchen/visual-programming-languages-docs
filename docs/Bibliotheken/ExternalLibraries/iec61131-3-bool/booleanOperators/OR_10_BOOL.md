# OR_10_BOOL

```{index} single: OR_10_BOOL
```

<img width="1189" height="416" alt="image" src="https://github.com/user-attachments/assets/fcefab43-d591-4163-96ce-61260ebfac5d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_10_BOOL` ist ein generischer Baustein zur Berechnung der logischen ODER-Verknüpfung. Er führt die ODER-Operation über bis zu zehn separate boolesche Eingangswerte aus und gibt das Ergebnis auf einem einzigen Ausgang aus. Dieser Baustein ist gemäß der Norm IEC 61131-3 klassifiziert und dient als Standardfunktion für bitweise Operationen in Steuerungsanwendungen.

## Schnittstellenstruktur
Der Funktionsblock folgt dem standardmäßigen E/A- und Ereignismodell der 4diac-IDE.

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Bei seinem Eintreffen werden alle zehn Daten-Eingänge (`IN1` bis `IN10`) ausgelesen und die ODER-Operation berechnet.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1 (OR input 1):** Boolescher Eingang 1.
*   **IN2 (OR input 2):** Boolescher Eingang 2.
*   **IN3 (OR input 3):** Boolescher Eingang 3.
*   **IN4 (OR input 4):** Boolescher Eingang 4.
*   **IN5 (OR input 5):** Boolescher Eingang 5.
*   **IN6 (OR input 6):** Boolescher Eingang 6.
*   **IN7 (OR input 7):** Boolescher Eingang 7.
*   **IN8 (OR input 8):** Boolescher Eingang 8.
*   **IN9 (OR input 9):** Boolescher Eingang 9.
*   **IN10 (OR input 10):** Boolescher Eingang 10.

### **Daten-Ausgänge**
*   **OUT (OR result):** Boolesches Ergebnis der ODER-Verknüpfung aller zehn Eingänge. Der Ausgang ist `TRUE` (1), wenn mindestens einer der Eingänge `TRUE` ist. Er ist nur `FALSE` (0), wenn alle zehn Eingänge `FALSE` sind.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und ereignisgesteuert:
1.  Das Eintreffen des Ereignisses `REQ` startet die Ausführung.
2.  Die aktuellen Werte aller zehn booleschen Eingänge (`IN1` bis `IN10`) werden ausgelesen.
3.  Es wird die logische ODER-Verknüpfung `OUT = IN1 OR IN2 OR IN3 OR ... OR IN10` berechnet.
4.  Das Ergebnis wird am Datenausgang `OUT` verfügbar gemacht.
5.  Das Ereignis `CNF` wird ausgelöst, um den erfolgreichen Abschluss der Operation an nachfolgende Blöcke zu signalisieren.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Funktionsblock (`GEN_OR`) implementiert, was eine flexible Wiederverwendung in verschiedenen Kontexten ermöglicht.
*   **Feste Eingangsanzahl:** Im Gegensatz zu Bausteinen mit variabler Eingangsanzahl besitzt `OR_10_BOOL` exakt zehn fest definierte Eingänge. Nicht benötigte Eingänge sollten auf `FALSE` gesetzt werden.
*   **Ereignisgesteuert:** Die Berechnung erfolgt nur bei Vorliegen eines `REQ`-Ereignisses, was eine energie- und rechenzeiteffiziente Abarbeitung im Steuerungssystem ermöglicht.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (speicherlos). Das Ausgangssignal `OUT` ist eine reine Funktion der aktuellen Eingangswerte zum Zeitpunkt der `REQ`-Anforderung. Es gibt keine Verzögerung, Hysterese oder Speicherung vorheriger Zustände.

## Anwendungsszenarien
*   **Überwachungslogik:** Zusammenfassen mehrerer Fehler- oder Warnsignale (z.B. von verschiedenen Sensoren) zu einem gemeinsamen Störmeldesignal.
*   **Freigabelogik:** Erzeugen einer Freigabe für einen Prozessschritt, wenn mindestens eine von mehreren Voraussetzungen erfüllt ist.
*   **Verknüpfung von Tastergruppen:** In einer Bedienstation, bei der ein Prozess durch Drücken mindestens eines von mehreren "Start"-Tastern initiiert werden kann.
*   **Redundante Sensorauswertung:** Auswerten mehrerer redundanter Sensoren, wobei das Signal eines beliebigen Sensors als gültig anerkannt wird.

## Vergleich mit ähnlichen Bausteinen
*   **`OR_2_BOOL` / `OR_4_BOOL`:** Diese Blöcke bieten die gleiche ODER-Funktionalität, jedoch für eine geringere Anzahl von Eingängen (2 bzw. 4). `OR_10_BOOL` ist für Anwendungen mit einer höheren Anzahl zu verknüpfender Signale vorgesehen. Siehe: [OR_10](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_10.md)
*   **`AND_10_BOOL`:** Führt die logische UND-Verknüpfung durch. Das Ergebnis ist nur `TRUE`, wenn *alle* Eingänge `TRUE` sind, während es bei `OR_10_BOOL` ausreicht, wenn *mindestens ein* Eingang `TRUE` ist. 
*   **`XOR_10_BOOL`:** Führt die exklusive ODER-Verknüpfung durch. Das Ergebnis ist `TRUE`, wenn eine ungerade Anzahl an Eingängen `TRUE` ist, was sich grundlegend von der inklusiven ODER-Logik unterscheidet.
*   **Bausteine mit variabler Eingangsanzahl:** Einige Bibliotheken bieten ODER-Bausteine an, bei denen die Anzahl der Eingänge konfigurierbar ist. `OR_10_BOOL` bietet hingegen eine feste, explizite Schnittstelle.

## Fazit
Der `OR_10_BOOL` ist ein robuster und einfach zu verwendender Grundbaustein für die logische Signalverknüpfung in IEC 61131-3-basierten Steuerungsapplikationen. Seine Stärke liegt in der klaren Schnittstelle mit zehn Eingängen und der zuverlässigen, ereignisgesteuerten Berechnung der inklusiven ODER-Funktion. Für Anwendungen, die das Zusammenfassen mehrerer boolescher Quellen zu einem gemeinsamen Signal erfordern, stellt er eine optimale Lösung dar.
