# XOR_7_BOOL

<img width="1378" height="391" alt="image" src="https://github.com/user-attachments/assets/731f9ca4-e163-4c46-8eda-5b826a199574" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_7_BOOL` ist ein generischer Baustein zur Berechnung der logischen Exklusiv-ODER (XOR) Verknüpfung. Er verarbeitet sieben boolesche Eingangssignale und liefert das Ergebnis der XOR-Operation als ein boolesches Ausgangssignal. Der Block folgt dem IEC 61131-3 Standard und ist für den Einsatz in Steuerungsanwendungen konzipiert, bei denen eine ungerade Paritätsprüfung oder eine logische Antivalenz über mehrere Signale erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Bei seinem Eintreffen werden alle sieben Daten-Eingänge (`IN1` bis `IN7`) ausgelesen und die XOR-Berechnung durchgeführt.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1 (XOR input 1):** Boolescher Eingang 1.
*   **IN2 (XOR input 2):** Boolescher Eingang 2.
*   **IN3 (XOR input 3):** Boolescher Eingang 3.
*   **IN4 (XOR input 4):** Boolescher Eingang 4.
*   **IN5 (XOR input 5):** Boolescher Eingang 5.
*   **IN6 (XOR input 6):** Boolescher Eingang 6.
*   **IN7 (XOR input 7):** Boolescher Eingang 7.

### **Daten-Ausgänge**
*   **OUT (XOR result):** Boolesches Ergebnis der XOR-Verknüpfung aller sieben Eingänge.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Eintreffen des Ereignisses `REQ` führt der Block die logische XOR-Operation über alle sieben booleschen Eingänge `IN1` bis `IN7` durch. Das Ergebnis `OUT` ist genau dann `TRUE` (1), wenn eine ungerade Anzahl der Eingänge den Wert `TRUE` aufweist. Ist die Anzahl der `TRUE`-Eingänge gerade (0, 2, 4, 6), ist das Ergebnis `FALSE` (0).

Mathematisch ausgedrückt: `OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5 XOR IN6 XOR IN7`

Unmittelbar nach der Berechnung wird das Abschlussereignis `CNF` zusammen mit dem gültigen Ergebnis `OUT` ausgelöst.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Funktionsblock (`GEN_XOR`) implementiert, was eine flexible Wiederverwendung in verschiedenen Kontexten ermöglicht.
*   **Feste Eingangsanzahl:** Im Gegensatz zu Bausteinen mit variabler Eingangsanzahl besitzt dieser Block exakt sieben fest definierte Eingänge.
*   **Ereignisgesteuerte Ausführung:** Die Operation wird ausschließlich durch ein eingehendes Ereignis (`REQ`) getriggert, was eine deterministische und energieeffiziente Abarbeitung im Echtzeitsystem ermöglicht.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist rein kombinatorisch und ausschließlich von den aktuellen Werten an den Eingängen zum Zeitpunkt des `REQ`-Ereignisses abhängig. Nach der Ausgabe von `CNF` verharrt der Block in einem wartenden Zustand bis zum nächsten `REQ`.

## Anwendungsszenarien
*   **Paritätsprüfung:** Überwachung, ob eine ungerade Anzahl von Sensoren (z.B. Grenztaster, Lichtschranken) in einem bestimmten Zustand (`TRUE`) ist.
*   **Sicherheitskritische Verknüpfungen:** In Sicherheitsschaltungen, wo eine Antivalenz-Bedingung über mehrere Sicherheitseinrichtungen erforderlich ist.
*   **Steuerungslogik:** Implementierung von speziellen logischen Verknüpfungen in Ablaufsteuerungen oder Verknüpfungssteuerungen, die eine XOR-Funktion mit genau sieben Operanden benötigen.

## Vergleich mit ähnlichen Bausteinen
*   **`XOR` (2 Eingänge):** Der Standard-XOR-Baustein verknüpft nur zwei Eingänge. Für eine Verknüpfung von sieben Signalen müsste dieser Block mehrfach verschachtelt werden, was die Lesbarkeit des Programms verringert. `XOR_7_BOOL` bietet eine direkte und übersichtliche Lösung. Siehe: [XOR_7](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_7.md)
*   **`GEN_XOR` (Generisch, n Eingänge):** Der zugrundeliegende generische Baustein `GEN_XOR` kann mit einer variablen Anzahl von Eingängen instanziiert werden. `XOR_7_BOOL` ist eine spezifische, vorkonfigurierte Instanz mit sieben Eingängen, die direkt verwendet werden kann, ohne die Anzahl der Eingänge parametrieren zu müssen.
*   **`PARITY_CHECK`:** Ein reiner Paritätsprüfblock könnte ähnliche Ergebnisse liefern, ist aber konzeptionell oft auf die Fehlererkennung in Datenströmen ausgelegt, während `XOR_7_BOOL` als allgemeiner logischer Operator in der Steuerungslogik dient.

## Fazit
Der `XOR_7_BOOL` Funktionsblock ist ein spezialisierter und effizienter Baustein für die logische Antivalenz-Verknüpfung von sieben booleschen Signalen. Durch seine ereignisgesteuerte, zustandslose Arbeitsweise und die klare Schnittstelle eignet er sich ideal für den Einsatz in strukturierten IEC 61131-3-basierten Steuerungsprogrammen, wo eine solche feste Verknüpfung benötigt wird. Er vereinfacht die Programmierung im Vergleich zur Verschachtelung mehrerer Zwei-Eingangs-XOR-Blöcke und bietet eine sofort einsatzbereite, zuverlässige Komponente.
