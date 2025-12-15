# AND_10_BOOL

<img width="1199" height="417" alt="image" src="https://github.com/user-attachments/assets/4d96025b-aaf4-4e39-9442-2b07e0257699" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_10_BOOL` ist ein generischer Baustein zur Berechnung der logischen UND-Verknüpfung. Er führt eine bitweise UND-Operation über bis zu zehn separate BOOL-Eingänge durch. Der Baustein ist nach der Norm IEC 61131-3 klassifiziert und gehört zur Kategorie der Standard-Booleschen Funktionen. Er wird typischerweise in Steuerungslogik eingesetzt, um Bedingungen zu verknüpfen, bei denen alle Eingangssignale wahr (TRUE) sein müssen, um ein Ausgangssignal zu aktivieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Bei seinem Eintreffen werden die Werte aller zehn Daten-Eingänge (`IN1` bis `IN10`) gelesen und die UND-Operation berechnet.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1 (AND input 1):** Boolescher Eingang 1.
*   **IN2 (AND input 2):** Boolescher Eingang 2.
*   **IN3 (AND input 3):** Boolescher Eingang 3.
*   **IN4 (AND input 4):** Boolescher Eingang 4.
*   **IN5 (AND input 5):** Boolescher Eingang 5.
*   **IN6 (AND input 6):** Boolescher Eingang 6.
*   **IN7 (AND input 7):** Boolescher Eingang 7.
*   **IN8 (AND input 8):** Boolescher Eingang 8.
*   **IN9 (AND input 9):** Boolescher Eingang 9.
*   **IN10 (AND input 10):** Boolescher Eingang 10.

### **Daten-Ausgänge**
*   **OUT (AND result):** Das Ergebnis der UND-Verknüpfung aller zehn Eingänge. Der Ausgang ist nur TRUE, wenn **alle** Eingänge `IN1` bis `IN10` den Wert TRUE haben. In allen anderen Fällen ist der Ausgang FALSE.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und ereignisgesteuert. Bei jedem Eintreffen des Ereignisses `REQ` wird die folgende logische Operation ausgeführt:
`OUT = IN1 AND IN2 AND IN3 AND IN4 AND IN5 AND IN6 AND IN7 AND IN8 AND IN9 AND IN10`

Anschließend wird das Ergebnis am Datenausgang `OUT` bereitgestellt und das Bestätigungsereignis `CNF` ausgelöst, um nachfolgende Blöcke über die Verfügbarkeit des neuen Ergebnisses zu informieren.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Baustein implementiert (Attribut `GenericClassName = 'GEN_AND'`). Dies bedeutet, dass seine Funktionalität möglicherweise auf eine andere Anzahl von Eingängen parametrisiert werden kann, wobei diese spezielle Instanz fest auf zehn Eingänge ausgelegt ist.
*   **Package:** Der Baustein ist im Package `iec61131::bitwiseOperators` enthalten.
*   **Vollständige Auswertung:** Alle zehn Eingänge werden bei jeder Ausführung ausgewertet.

## Zustandsübersicht
Der `AND_10_BOOL`-Block besitzt keinen internen Zustand (speicherlos). Sein Ausgang hängt ausschließlich von den aktuellen Werten der Eingänge zum Zeitpunkt der Auslösung durch `REQ` ab. Es gibt keine Verzögerungen, Filter oder Hysterese.

## Anwendungsszenarien
*   **Sicherheitsverknüpfungen:** In Maschinensicherheitskreisen, wo mehrere Sicherheitsschalter (Not-Aus, Lichtschranken, Türkontakte) alle geschlossen sein müssen, bevor ein gefährlicher Vorgang starten darf.
*   **Mehrfachbedingungen:** In Prozesssteuerungen, um zu prüfen, ob mehrere Voraussetzungen (z.B. Füllstand, Temperatur, Druck) gleichzeitig innerhalb ihrer Sollbereiche liegen.
*   **Freigabelogik:** Als Teil einer Freigabekette, bei der mehrere Stationen oder Bediener ihre Zustimmung (TRUE-Signal) geben müssen.

## Vergleich mit ähnlichen Bausteinen
*   **`AND` (mit 2 Eingängen):** Der Standard-AND-Baustein nach IEC 61131-3 hat typischerweise nur zwei Eingänge. `AND_10_BOOL` erweitert diese Funktionalität auf zehn Eingänge ohne die Notwendigkeit, mehrere Zwei-Eingangs-AND-Blöcke zu verschalten. Siehe: [AND_10](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_10.md)
*   **`OR_10_BOOL`:** Führt eine logische ODER-Verknüpfung durch. Das Ergebnis ist TRUE, wenn mindestens ein Eingang TRUE ist, während `AND_10_BOOL` verlangt, dass alle Eingänge TRUE sind.
*   **`XOR` / `XNOR`:** Berechnen die exklusive ODER- bzw. die Äquivalenz-Verknüpfung, die sich auf die Parität der TRUE-Signale beziehen, nicht auf eine Alles-oder-Nichts-Bedingung wie das UND.
*   **Generische Blöcke (`GEN_AND`):** Der `AND_10_BOOL` ist eine spezifische Instanz eines generischen UND-Blocks. In anderen Umgebungen könnte ein konfigurierbarer `GEN_AND`-Block verwendet werden, dem die gewünschte Anzahl an Eingängen parametrisiert zugewiesen wird.

## Fazit
Der `AND_10_BOOL` ist ein spezialisierter, zuverlässiger und einfach zu verwendender Funktionsblock für Anwendungen, die eine logische UND-Verknüpfung über eine größere, feste Anzahl von Bedingungen erfordern. Seine ereignisgesteuerte, zustandslose Natur macht ihn vorhersehbar und einfach in bestehende Steuerungsabläufe zu integrieren. Für Szenarien mit einer variablen Anzahl an Bedingungen sollten flexible, parametrierbare Blöcke in Betracht gezogen werden.
